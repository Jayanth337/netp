#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int main_parent_pid = getpid();
    printf("Main Parent Process ID: %d\n\n", main_parent_pid);

    pid_t first_child = fork();
    pid_t first_child_pid, second_child_pid;
    int child_status1, child_status2;

    if (first_child == -1) {
        perror("Error: Could not create first child");
        exit(EXIT_FAILURE);
    }

    if (getpid() != main_parent_pid) {
        first_child_pid = getpid();
        printf("First Child Process ID: %d\n", first_child_pid);
        sleep(1);
        exit(1);
    } else {
        pid_t second_child = fork();

        if (second_child == -1) {
            perror("Error: Could not create second child");
            exit(EXIT_FAILURE);
        }

        if (getpid() != main_parent_pid) {
            second_child_pid = getpid();
            printf("Second Child Process ID: %d\n\n", second_child_pid);
            sleep(2);
            exit(2);
        }

        first_child_pid = wait(&child_status1);
        printf("First child completed after 1 sec, PID: %d, Exit Code: %d\n", 
               first_child_pid, (child_status1 & 0xff00) >> 8);

        second_child_pid = wait(&child_status2);
        printf("Second child completed after 2 sec, PID: %d, Exit Code: %d\n\n", 
               second_child_pid, (child_status2 & 0xff00) >> 8);
    }

    printf("Main Parent Process (PID: %d) is terminating.\n", main_parent_pid);
    return 0;
}
