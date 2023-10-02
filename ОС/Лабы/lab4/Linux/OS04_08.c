#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* OS04_07_T1()
{
    for (int i = 0; i < 75; i++)
    {
        if (i == 50)
        {
            sleep(10);
        }
        
        printf("OS_04_07_T1 PID: %d\n", getpid());
        sleep(1);
    }

    pthread_exit(NULL);
}


int main() 
{
    pthread_t thread;

    int result = pthread_create(&thread, NULL, OS04_07_T1, NULL);

    if (result != 0) 
    {
        printf("Error thread\n");
        return 1;
    }
    
    for (int i = 0; i<100; i++)
    {
        if (i == 30)
        {
            sleep(15);
        }
        
        printf("%d. PID: %d\n", i,getpid());
        
        sleep(1);
    }

    pthread_join(thread, NULL);
    
    return 0;
}


