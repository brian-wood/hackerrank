#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    size_t len = 50;
    char *line = (char*)calloc(len, sizeof(char));
    int q_size = 0;
    int l_index = 0;
    int f_index = 0;
    
    fgets(line, len, stdin);
    q_size = strtol(line, NULL, 10);
    //printf("q_size: %d\n", q_size);
    
    long long int *queue = (long long int *)calloc(q_size, sizeof(long long int));
    while (fgets(line, len, stdin)) {
        //printf("line: %s\n", line);
        switch (strtol(strtok(line, " "), NULL, 10)) {
        case 1: // add to queue
            queue[l_index++] = strtol(strtok(NULL, "\n"), NULL, 10);
            //printf("add to queue: %lld\n", queue[l_index-1]);
        break;
        case 2: // remove front element from queue
            //printf("remove front element: %lld\n", queue[f_index]);
            queue[f_index++] = 0;
            //if (f_index > (q_size/2)) // front-half of queue is empty; realloc to move elements forward
        break;
        case 3: // print the front element of queue
            printf("%lld\n", queue[f_index]);
        break;
        default:
            //printf("ERROR\n");
        break;
        }
        
    }
    free(line);
    free(queue);  
    return 0;
}
