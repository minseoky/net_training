#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void child_handler(int sig)
{
    int stat;
    pid_t pid = waitpid(-1, &stat, WNOHANG);;
    if(WIFEXITED(stat))
        printf("child [%d] returned: %d\n", pid, WEXITSTATUS(stat)); //WEXITSTATUS는 하위 8비트만 추출 가능하다. (0~255)
}

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    signal(SIGCHLD, child_handler);

    if(pid == 0) // CHILD
    {
        return 123;
    }
    else if(pid > 0) // PARENT
    {
        for(int i = 0 ; i < 3 ; i++)
            sleep(1);
    }
    return 0;
}
