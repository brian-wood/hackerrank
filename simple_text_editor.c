#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BUFFER 8192

struct node {
    int op;
    char *string;
    struct node *prev;
    struct node *next;    
};


// STE - simple text editor
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    FILE *fd = fopen("input403.txt", "r");

    char *ch = " ", *token, *tmp_str = NULL;
    int tot_ops = 0, oper_type = 0;
    size_t len = 2000;
    char *ste_str_buff = calloc(MAX_BUFFER, sizeof(char)); // ste string buffer
    struct node *root = calloc(1, sizeof(struct node));
    struct node *cur = root, *tmp;
    
    tmp_str = calloc(len, sizeof(char));
    //getline(&tmp_str, &len, stdin); // first line from stdin number of operations to process.
    getline(&tmp_str, &len, fd); // first line from stdin number of operations to process.
    tot_ops = strtol(strtok(tmp_str, "\n"), NULL, 10);
    //printf("total operations: %d\n", tot_ops);
    root->op = tot_ops; 
    root->string = NULL;
    root->prev = NULL;
    root->next = NULL;
    
    //while ((getline(&tmp_str, &len, stdin)) != -1) {
    while ((getline(&tmp_str, &len, fd)) != -1) {
        //printf("tmp_str: %s", tmp_str);
        oper_type = strtol(strtok(tmp_str, ch), NULL, 10);
        //printf("oper_type: %d\n", oper_type);
        
        switch (oper_type) {
        case 1: // append provided string to end of current string
            
            //printf("append string from stdin\n");
            /*
            printf("append string from file descriptor\n");
            printf("ste_str_buff: %s, strlen: %ld\n", ste_str_buff,
                    strlen(ste_str_buff));
            */
            token = strtok(NULL, "\n");
            //printf("token: %s\n", token);
            
            // Save the current state for operation/string before modification; 
            // to be used in undo operation below. This code block can be functionalized later.
            cur->next = calloc(1, sizeof(struct node));
            cur->next->prev = cur;
            cur = cur->next;
            cur->op = oper_type;
            cur->string = calloc(strlen(token)+1, sizeof(char));
            strncpy(cur->string, token, strlen(token));
            *(cur->string+strlen(token)) = '\0';
            cur->next = NULL;
            /*
            printf("cur->op: %d, cur->string: %s\n",cur->op ,cur->string);
            
            printf("length1.1: %ld, length1.2: %ld\n", strlen(ste_str_buff), strlen(token));
            printf("length1F: %ld\n", (strlen(ste_str_buff))+(strlen(token)));
            */
            
            // add <token> chars to end of string
            strncat(ste_str_buff, token, strlen(token));
            
            //printf("ste_str_buff: %s, strlen: %ld\n", ste_str_buff,
            //        strlen(ste_str_buff));
            
            //for (int i = 0; i < 40; i++)
            //    printf("ste_str_buff[%d]=%c\n", i, ste_str_buff[i]);

            //printf("\n");
            break;
        case 2: // delete the number (provided on cmdline) of characters from end of string
            token = strtok(NULL, "\n");
            /*
            printf("delete %ld char(s) from string: %s\n", strtol(token, NULL, 10),
                                                    ste_str_buff);
            */
                                                    
            // Save the current state for operation/string before modification; 
            // to be used in undo operation below. This code block can be functionalized later.
            cur->next = calloc(1, sizeof(struct node));
            cur->next->prev = cur;
            cur = cur->next;
            cur->op = oper_type;
            cur->string = calloc(strtol(token, NULL, 10)+1, sizeof(char));
            cur->next = NULL;            
            
            /*
            printf("length2.1: %ld, length2.2: %ld\n", strlen(ste_str_buff), strtol(token, NULL, 10));
            printf("length2: %ld\n", (strlen(ste_str_buff))-(strtol(token, NULL, 10)));
            */
            // delete <token> chars from end of string
            for (int i = ((strlen(ste_str_buff))-(strtol(token, NULL, 10))),
                            j = strlen(ste_str_buff); i < j; i++) {
                strncat(cur->string, ste_str_buff+i, 1);
                ste_str_buff[i] = 0;
                /*
                printf("ste_str_buff[%d]=%c\n", i, ste_str_buff[i]);
                printf("cur->op: %d, cur->string: %s\n", cur->op, cur->string);
                */
            }
            
            //printf("ste_str_buff: %s, strlen: %ld\n", ste_str_buff,
            //        strlen(ste_str_buff));
            
            //printf("\n");
                                                
            break;
        case 3: // print the Nth (provided on cmdline) character from string
            token = strtok(NULL, "\n");
            /*
            printf("print the number %ld char from string: %s\n", strtol(token, NULL, 10),
                                                    ste_str_buff);
            */
            printf("%c\n", ste_str_buff[strtol(token, NULL, 10)-1]);
            
            //printf("\n");
            break;
        case 4: // undo the last (not previously undone) operation of type 1 or 2, reverting string to prior state
            if (cur->op == root->op)
                break; // Someone is trying to undo more than there were append/delete operations
            /*
            printf("undo the last operation done to string ste_str_buff\n");
            
            printf("undo %s: cur->op: %d\n",
                    cur->op == 1 ? "append" : cur->op == 2 ? "delete" : "ERROR!!!",
                    cur->op);
            */
            tmp = cur;
            cur = cur->prev;
            cur->next = NULL;
            if (tmp->op == 1) {
                for (int i = 0, j = strlen(ste_str_buff)-1; i < (int)strlen(tmp->string); i++) {
                    //printf("i: %d, j: %d\n", i, j);
                    ste_str_buff[j-i] = 0;
                    //printf("ste_str_buff: %s\n", ste_str_buff);
                }
            }
            if (tmp->op == 2)
                strncat(ste_str_buff, tmp->string, strlen(tmp->string));

            //printf("ste_str_buff: %s\n", ste_str_buff);
            tmp->prev = NULL;
            tmp->next = NULL;
            if (tmp->string)
                free(tmp->string);
            
            free(tmp);
            
            //printf("\n");
            break;
        default:
            break;
        }
    }
    if (oper_type == EOF)
        //printf("oper_type == EOF, Good-bye!\n");

    if (tmp_str)
        free(tmp_str);
    
    free(ste_str_buff);
    free(root);
    free(tmp_str);
    fclose(fd);
    return 0;
}
