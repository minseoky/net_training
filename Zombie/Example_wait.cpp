#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int stat;
    pid = fork();

    if(pid == 0) // CHILD
    {
        int sum = 0;
        int ret_val = 100;
        for(int i = 0 ; i < 789654321 ; i++)
        {
            sum++;
        }
        printf("[CHILD] sum = %d, return %d\n", sum, ret_val);
        return ret_val;
    }
    else if(pid > 0) // PARENT
    {
        int sum = 0;
        for(int i = 0 ; i < 100000000 ; i++)
        {
            sum++;
        }
        printf("[PARENT] sum = %d\n", sum);
        wait(&stat);
        if(WIFEXITED(stat))
        {
            printf("[PARENT] state = %d\n", WEXITSTATUS(stat));
        }
    }


    return 0;
}