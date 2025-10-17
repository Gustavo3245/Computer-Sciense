#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SCATTERING_POINTS 100000
#define NUMBER_OF_THREADS 20

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double circlePoints = 0;

typedef struct Monte_carlo{
    int ThreadsWorking;
    double sideSize;
} Monte;


double GenerateInsideNumber(int sideSize){
    return ((double) random() / RAND_MAX) * sideSize; 
}

/*Monte Carlo Aproximation of PI by randomly scattering points within a square
 * and determining the ratio os points that land inside a circle inscribed */
void *MonteCarloMethod(struct Monte_carlo *Square){
    double x,y; 
    long int correctPoints = 0;

    double sideSize_squared = (double)Square->sideSize * Square->sideSize;

    for (int value = 0; value < Square->ThreadsWorking; value++) {
        y = GenerateInsideNumber(Square->sideSize);
        x = GenerateInsideNumber(Square->sideSize);

        if((x*x) + (y*y) < sideSize_squared){
            correctPoints++;
        }
    }

    pthread_mutex_lock(&mutex);
    circlePoints += correctPoints;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main(int argc, char *argv[]){
    pthread_t threadArray[NUMBER_OF_THREADS];
    srandom((unsigned)time(NULL));

     struct Monte_carlo Square;
        Square.ThreadsWorking = SCATTERING_POINTS / NUMBER_OF_THREADS;
        Square.sideSize = 4;

    for (int value = 0; value < NUMBER_OF_THREADS; value++) {
        pthread_create(&threadArray[value], NULL, (void*) MonteCarloMethod, (void *) &Square);
    }

    for (int value = 0; value < NUMBER_OF_THREADS; value++){
        pthread_join(threadArray[value], NULL);
    }

    double estimated = 4 * (circlePoints / SCATTERING_POINTS);

    printf("pi estimado: %f \n", estimated);
}
