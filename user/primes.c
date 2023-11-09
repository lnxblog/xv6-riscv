#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{

    int pipefd[2];
    int pipefd2[2];
    int num,prime;
    bool toggle=false;
    int rd_fd,wr_fd;

    if(pipe(pipefd) == -1)
    {
        printf("pipe failed\n");
        return 1;
    }


    if(pipe(pipefd2) == -1)
    {
        printf("pipe failed\n");
        return 1;
    }

    if(fork())
    {
        printf("process %d\n",getpid());
        close(pipefd[0]);
        int i = 2;
        while(i<=6)
        {
            if(write(pipefd[1],(void*)&i,4) == -1)
            {
                printf("write failed\n");
                return 1;
            }
            i++;
        }
        close(pipefd[1]);
        wait(0);
    }
    else
    {
       // while(1)
       // {
            if(!toggle)
            {
                rd_fd = pipefd[0];
                wr_fd = pipefd2[1];
                close(pipefd[1]);
                close(pipefd2[0]);
            }
            else
            {
                rd_fd = pipefd2[0];
                wr_fd = pipefd[1];
                close(pipefd[0]);
                close(pipefd2[1]);
            }
            toggle = !toggle;

            if(read(rd_fd,(void*)&num,4) == 0)  // read prime
            {
                close(rd_fd);
                exit(0);
            }
            else
            {
                if(fork())  // pipe the numbers to next process
                {
                    int prime = num;
                    printf("prime %d\n",prime);
                    while(read(rd_fd,(void*)&num,4) != 0)
                    {

                        if(num % prime)
                        {
                            write(wr_fd,(void*)&num,4);
                        }

                    }
                    close(wr_fd);
                    close(rd_fd);
                    exit(0);
                }

            }
      //  }
    }
}