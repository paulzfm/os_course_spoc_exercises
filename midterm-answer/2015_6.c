#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int globalVariable = 20;
int main(void)
{
    char sIdentifier[20];
    int iStackVariable = 20;
    pid_t pID = fork();
    if (pID == 0) { // child
        strcpy(sIdentifier, "Child Process: ");
        globalVariable++;
        iStackVariable--;
    } else if (pID < 0) { // failed to fork
        printf("Failed to fork\n");
        exit(1);
        // Throw exception
    } else { // parent
        strcpy(sIdentifier, "Parent Process:");
    }

    globalVariable++;
    iStackVariable--;
    printf("%s", sIdentifier);
    printf(" Global variable: %d", globalVariable);
    printf(" Stack variable: %d\n", iStackVariable);
}
