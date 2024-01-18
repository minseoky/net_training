#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void child_handler(int sig)
{
    if(sig == SIGCHLD)
    {
        int stat;
        pid_t id = waitpid(-1, &stat, WNOHANG);
        if(WIFEXITED(stat))
        {
            printf("CHILD [%d] end, returned : %d\n", id, WEXITSTATUS(stat));
        }
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();
    struct sigaction act;
    act.sa_handler=child_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    if(pid == 0) // CHILD
    {
        sleep(1);
        return 123;
    }
    else // PARENT
    {
        int i;
        for(i = 0 ; i < 3 ; i++)
        {
            puts("wait...");
            sleep(2);
        }
    }

    return 0;
}