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
    pid_t p;
    p = fork();
    if (p == -1){
        perror("fork fail"); //output to stderr instead of stdout
        err();
    }
    else if (p == 0){
        printf("Hello from Child!\n");
    } 
    else {
        printf("%d about to create 2 child processes\n", getpid());
    }
    
}