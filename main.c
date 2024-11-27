#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
int rand_int(int *buff, int n) {
    int r_file = open("/dev/random", O_RDONLY, 0);
    if (r_file == -1) err();
    int bytes = read(r_file, buff, n);
    if (bytes == -1) err();
    return *buff;
}
int main() {
    printf("%d about to create 2 child processes\n", getpid());
    pid_t p = fork();
    if (p == -1){
        perror("fork fail"); //output to stderr instead of stdout
        err();
    }
    else if (p == 0){ //child
        unsigned int x0;
        rand_int(&x0, 4);
        int x = x0 % 5 + 1;
        printf("%d %d sec\n", getpid(), x);
        sleep(x);
        printf("%d finished after %d sec\n", getpid(), x);
        return x;
    } 
    else {
        pid_t c = fork();
        if (c == -1){
            perror("fork fail"); //output to stderr instead of stdout
            err();
        }
        else if (c == 0){ //child
            unsigned int y0;
            rand_int(&y0, 4);
            int y = y0 % 5 + 1;
            printf("%d %d sec\n", getpid(), y);
            sleep(y);
            printf("%d finished after %d sec\n", getpid(), y);
            return y;
        } 
        else {
            int status;
            int exited = wait(&status);
            printf("Main Process %d is done. Child %d slept for %d sec\n", getpid(), exited, WEXITSTATUS(status));
        }
    }
    
}