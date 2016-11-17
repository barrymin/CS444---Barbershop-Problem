#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 20

int resourceCount = 0;
bool reachedMax = false;

// Function calls
void executeThread();

int main()
{
    srand(time(NULL));

    int i;
    pthread_t tid;

    // Let us create three threads
    for (i = 0; i < NUM_THREADS; i++){
        pthread_create(&tid, NULL, executeThread, NULL);
        sleep(1);
    }

    pthread_exit(NULL);
    return 0;
}


// The function to be executed by all threads
void executeThread()
{
    if (resourceCount<3 && reachedMax == false){
        printf("New thread (%d) using thread ", resourceCount+1);

        // Increment resource usage count
        resourceCount++;

        // Sleep random amount of time
        int time = rand() % 8;
        printf("(%ds)\n", time);
        sleep(time);

        resourceCount--;
        printf("\t Thread exiting...\n");

        return;
    } else {
        if (resourceCount == 3)
            printf("\t\t\tREACHED MAX\n");

        reachedMax = true;

        if(resourceCount == 0){
            reachedMax = false;
        }
    }

}
