#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

sem_t agentSem = 1, tobacco = 0, paper = 0, match = 0;
int isTobacco = 0, isPaper = 0, isMatch = 0;
sem_t tobaccoSem = 0, paperSem = 0, matchSem = 0, mutex = 1;

//all functions for pthreads

void agentOne(){
  while(1){
    sem_wait(agentSem);
    sem_post(tobacco);
    sem_post(paper);
  }
}

void agentTwo(){
  while(1){
    sem_wait(agentSem);
    sem_post(match);
    sem_post(paper);
  }
}

void agentThree(){
  while(1){
    sem_wait(agentSem);
    sem_post(match);
    sem_post(tobacco);
  }
}

void tobaccoPusher(){
  while (1) {
    sem_wait(tobacco);
    sem_wait(mutex);
    if (isPaper) {
        isPaper = 0;
        sem_post(matchSem);
    }
    else if (isMatch) {
      isMatch = 1;
      sem_post(paperSem);
    }
    else isTobacco = 1;
    sem_post(mutex);
  }
}

void matchPusher(){
  while (1) {
    sem_wait(matchSem);
    sem_wait(mutex);
    if (isPaper) {
        isPaper = 0;
        sem_post(tobaccoSem);
    }
    else if (isTobacco) {
      isTobacco = 0;
      sem_post(paperSem);
    }
    else isMatch = 1;
    sem_post(mutex);
  }
}

void paperPusher(){
  while (1) {
    sem_wait(paperSem);
    sem_wait(mutex);
    if (isMatch) {
        isMatch = 0;
        sem_post(tobaccoSem);
    }
    else if (isTobacco) {
      isTobacco = 0;
      sem_post(matchSem);
    }
    else isPaper = 1;
    sem_post(mutex);
  }
}

void tobaccoSmoker(){
  srand(time(NULL));   // Initialization, should only be called once.
  while (1) {
   sem_wait(tobaccoSem);
   //Make a cigarette
   sem_post(agentSem);
   Sleep(rand() % 3 * .001); //sleep some time between 0 and 200 ms
  }
}

void matchSmoker(){
  srand(time(NULL));   // Initialization, should only be called once.
  while (1) {
   sem_wait(matchSem);
   //Make a cigarette
   sem_post(agentSem);
   Sleep(rand() % 3* .001); //sleep some time between 0 and 200 ms
  }
}

void paperSmoker(){
  srand(time(NULL));   // Initialization, should only be called once.
  while (1) {
   sem_wait(paperSem);
   //Make a cigarette
   sem_post(agentSem);
   Sleep(rand() % 3 * .001); //sleep some time between 0 and 200 ms
  }
}

int main(){
  //declare all pthreads
  pthread_t smokerOne, smokerTwo, smokerThree;
  pthread_t paperPush, matchPush, tobaccoPush;
  pthread_t agent1, agent2, agent3;

  //create all pthreads
  pthread_create(agent1, NULL, agentOne, NULL);
  pthread_create(agent2, NULL, agentTwo, NULL);
  pthread_create(agent3, NULL, agentThree, NULL);
  pthread_create(paperPush, NULL, paperPusher, NULL);
  pthread_create(matchPush, NULL, matchPusher, NULL);
  pthread_create(tobaccoPush, NULL, tobaccoPusher, NULL);
  pthread_create(smokerOne, NULL, tobaccoSmoker, NULL);
  pthread_create(smokerTwo, NULL, matchSmoker, NULL);
  pthread_create(smokerThree, NULL, paperSmoker, NULL);

  //terminate all pthreads
  pthread_join(agent1, NULL);
  pthread_join(agent2, NULL);
  pthread_join(agent3, NULL);
  pthread_join(paperPush, NULL);
  pthread_join(matchPush, NULL);
  pthread_join(tobaccoPush, NULL);
  pthread_join(smokerOne, NULL);
  pthread_join(smokerTwo, NULL);
  pthread_join(smokerThree, NULL);

  return 0;
}
