#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEFAULT_TIME 5
#define DEFAULT_STATUS 0

int main(int argc, char **argv)
{
    int child_id;
    int seconds;
    int status;
    pid_t whodied;
    status = DEFAULT_STATUS;

    if (argc == 1) {
        seconds = DEFAULT_TIME;
    } else {
        seconds = atoi(argv[1]);
    }

    printf("Here I am in the program! Time to wait = %d\n", seconds);
    system("ps -l"); // show some useful information, pay attention to PID, PPID, CMD
                     // WARNING: when you run "ps -l" on Mac OS X, the output does not contain the process "ps" itself!

    child_id = fork();
    if (child_id) { // parent
        printf("I'm the parent at Line 33. My parent's process ID is %d, My process ID is %d, status = %d.\n",
            getppid(), getpid(), status); // check the PPID and PID of a.out, status = 0
        whodied = wait(&status);
        /* What does "wait" do here? Let's read the official description:
           (http://linux.die.net/man/2/wait)

           We see that

             pid_t wait(int *status);

           this system call suspends execution of the calling process until one of its children terminates.
           On success, returns the process ID of the terminated child; on error, -1 is returned. */
        printf("Child %d exited ", whodied); // child's PID

        /* WIFEXITED evaluates to true when the process exited by using an exit(2V) call.
           If WIFEXITED(status) is non-zero, WEXITSTATUS evaluates to the low-order byte of the
           argument that the child process passed to _exit() (see exit(2V)) or exit(3), or the value the
           child process returned from main() (see execve(2V)). */
        if (!WIFEXITED(status)) { // no such case in this problem
            printf("abnormally!\n");
        } else {
            printf("with status %d.\n", WEXITSTATUS(status)); // WEXITSTATUS(status) is the return code
        }
        printf("I'm the parent at Line 43. My parent's process ID is %d, My process ID is %d, status = %d.\n",
            getppid(), getpid(), WEXITSTATUS(status)); // everything is the same except status, now status = 17
        return status; // parent thread's return code = status
    } else { // child
        status = 17; // change status here
        sleep(seconds);
        printf("I'm the child. My parent's process ID is %d, My process ID is %d, status = %d.\n",
            getppid(), getpid(), status); // PPID = parent's PID, PID = largest PID in "ps -l" + 1, status = 17
                                          // Note: on Mac OS X, PID = largest PID in "ps -l" + 2, since
                                          // the PID of "ps" = largest PID in "ps -l" + 1!
        printf("Bye now!\n");
        return status; // child thread's return code = status
    }
}
