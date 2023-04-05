#define _POSIX_C_SOURCE 200112L

/* time_server.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())
#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif

int main(void)
{
    #if defined(_WIN32)
        WSADATA d;
        if (WSAStartup(MAKEWORD(2,2), &d)) {
            fprintf(stderr, "Failed to initialize.\n");
            return 1;
        }
    #endif

    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d):(%s)\n", GETSOCKETERRNO(), strerror(GETSOCKETERRNO()));
        return 1;
    }

    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d):(%s)\n", GETSOCKETERRNO(), strerror(GETSOCKETERRNO()));
        CLOSESOCKET(socket_listen);
        return 1;
    }
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d):(%s)\n", GETSOCKETERRNO(), strerror(GETSOCKETERRNO()));
        CLOSESOCKET(socket_listen);
        return 1;
    }

    printf("Waiting for connection...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    /* With this call to accept() our program will block until client makes a connection to port 8080 */
    /* socket_listen will still have 10-<x> connections open for additional clients */
    SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
    /* Client has connected...check if that conneciton is valid. 
     * This socket_client contains address info for client
     */
    if (!ISVALIDSOCKET(socket_client)) {
        fprintf(stderr, "listen() failed. (%d):(%s)\n", GETSOCKETERRNO(), strerror(GETSOCKETERRNO()));
        CLOSESOCKET(socket_listen);
        return 1;
    }

    printf("Client is connected...");
    char address_buffer[100];
    getnameinfo((struct sockaddr *) &client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    printf("%s\n", address_buffer);

    printf("Reading client request...\n");
    char request[1024];
    /* recv() will block until the client sends some data. */
    int bytes_recieved = recv(socket_client, request, 1024, 0);
    if (bytes_recieved <= 0) {
        fprintf(stderr, "listen() failed. (%d):(%s)\n", GETSOCKETERRNO(), strerror(GETSOCKETERRNO()));
        CLOSESOCKET(socket_client);
        CLOSESOCKET(socket_listen);
    }
    printf("Received %d bytes\n", bytes_recieved);
    /* Note that we use the printf() format string, "%.*s". This tells printf() that we want to
     * print a specific number of characters—bytes_received. It is a common mistake to try
     * printing data that's received from recv() directly as a C string. There is no guarantee that
     * the data received from recv() is null terminated! If you try to print it with
     * printf(request) or printf("%s", request), you will likely receive a segmentation
     * fault error (or at best it will print some garbage). 
     */
    printf("%.*s", bytes_recieved, request);

    printf("Sending response...\n");
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local time is: ";
    int bytes_sent = send(socket_client, response, strlen(response), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

    time_t timer;
    time(&timer);
    char *time_msg = ctime(&timer);
    bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));

    printf("Closing client connection...\n");
    CLOSESOCKET(socket_client);
    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

    #if defined(_WIN32)
        WSACleanup();
    #endif

    printf("Finished.\n");

    return 0;
}