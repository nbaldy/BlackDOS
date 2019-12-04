// AUTHORS: Elena, Nicole, Tim
// Semaphore solution to chain smoker problem
// C program, must be compiled with gcc -pthread projy.c

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/* Main players - Agent, Smokers with tobacco, paper, match */
sem_t agentSem, tobaccoSem, paperSem, matchSem;

/* "helpers" - required */
int isTobacco = 0, isPaper = 0, isMatch = 0; // Supplies on the table
sem_t tobacco, paper, match; // Pushers (move supplies from agent to usert)
sem_t mutex; //Pushers must have exclusive access to supplies on the table


// Tobacco and Paper agent
void *agentOne(){
  printf("Tobacco and paper agent created.\n");
  for (int i = 0; i < 6; i++) {
    sleep((rand()%200)/100); //Sleep thread for up to 200 ms to mix things up
    sem_wait(&agentSem); //Wait until previous agent deal is finished
    sem_post(&tobacco); //wake up a tobacco pusher
    sem_post(&paper); //wake up a paper pusher
  }
}

// Paper and Match agent
void *agentTwo(){
  printf("Paper and match agent created.\n");
  for (int i = 0; i < 6; i++) {
    sleep((rand()%200)/100); //Sleep thread for up to 200 ms to mix things up
    sem_wait(&agentSem); //Wait until previous agent deal is finished
    sem_post(&paper); //wake up a paper pusher
    sem_post(&match); //wake up a match pusher
  }
}

// Match and Tobacco agent
void *agentThree(){
  printf("Match and tobacco agent created.\n");
  for (int i = 0; i < 6; i++) {
    sleep((rand()%200)/100); //Sleep thread for up to 200 ms to mix things up
    sem_wait(&agentSem); //Wait until previous agent deal is finished
    sem_post(&match); //wake up a match pusher
    sem_post(&tobacco); //wake up a tobacco pusher
  }
}

// Pusher thread which reacts to tobacco
void *tobaccoPusher(){
  for (int i = 0; i < 12; i++) {
    sem_wait(&tobacco);  // Wakes up when an agent provides tobacco
    printf("tobacco is provided by agent\n");
    sem_wait(&mutex); // Must have exclusive access to table from other pushers
    if (isPaper) {
        // Paper and Tobacco are on the table - wake up matches
        isPaper = 0;
        sem_post(&matchSem);
    }
    else if (isMatch) {
      // Matches and Tobacco are on the table - wake up paper
      isMatch = 0;
      sem_post(&paperSem);
    }
    else isTobacco = 1;
    //Nothing else on the table - put down tobacco, give back mutex
    sem_post(&mutex);
  }
}

// Pusher thread which reacts to matches
void *matchPusher(){
  for (int i = 0; i < 12; i++) {
    sem_wait(&match);  // Wakes up when an agent provides match
    printf("match is provided by agent\n");
    sem_wait(&mutex); // Must have exclusive access to table from other pushers
    if (isPaper) {
        // Paper and matches are on the table - wake up tobacco
        isPaper = 0;
        sem_post(&tobaccoSem);
    }
    else if (isTobacco) {
      // Matches and tobacco are on the table - wake up paper
      isTobacco = 0;
      sem_post(&paperSem);
    }
    //Nothing else on the table - put down matches, give back mutex
    else isMatch = 1;
    sem_post(&mutex);
  }
}

// Pusher thread which reacts to paper
void *paperPusher(){
  for (int i = 0; i < 12; i++) {
    sem_wait(&paper);  // Wakes up when an agent provides paper
    printf("paper is provided by agent\n");
    sem_wait(&mutex); // Must have exclusive access to table from other pushers
    if (isTobacco) {
        // Tobacco and paper are on the table - wake up matches
        isTobacco = 0;
        sem_post(&matchSem);
    }
    else if (isMatch) {
      // Matches and paper are on the table - wake up tobacco
      isMatch = 0;
      sem_post(&tobacco);
    }
    //Nothing else on the table - put down paper, give back mutex
    else isPaper = 1;
    sem_post(&mutex);
  }
}

void *tobaccoSmoker(void* arg){
  int num = *((int*)arg); //unpack arg
  for (int i = 0; i < 3; i++) {
    sem_wait(&tobaccoSem);
    printf("%d smoker (tobacco-holding) makes cigarette %d\n", num, i);
    sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
    sem_post(&agentSem); //need new agent to provide more ingredients
    printf("%d smoker (tobacco-holding) smokes cigarette %d\n", num, i);
    sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
  }
  printf("%d smoker (tobacco-holding) is hungry, exits\n", num);
}

void *matchSmoker(void* arg){
  int num = *((int*)arg); //unpack arg
  for (int i = 0; i < 3; i++) {
    sem_wait(&matchSem);
    printf("%d smoker (match-holding) makes cigarette %d\n", num, i);
    sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
    sem_post(&agentSem); //need new agent to provide more ingredients
    printf("%d smoker (match-holding) smokes cigarette %d\n", num, i);
    sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
  }
  printf("%d smoker (match-holding) is hungry, exits\n", num);
}

void *paperSmoker(void* arg){
  int num = *((int*)arg);
  for (int i = 0; i < 3; i++) {
   sem_wait(&paperSem);
   printf("%d smoker (paper-holding) makes cigarette %d\n", num, i);
   sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
   sem_post(&agentSem); //need new agent to provide more ingredients
   printf("%d smoker (paper-holding) smokes cigarette %d\n", num, i);
   sleep((rand()%50)/100); //Sleep thread for up to 50 ms to mix things up
  }
  printf("%d smoker (paper-holding) is hungry, exits\n", num);
}

int main(){
  printf("Hello, World\n"); // \n indicates a newline character
  srand(time(NULL));   // Seed random times

  /* initialize semiphores */
  printf("initialize semaphores.\n");
  sem_init(&agentSem, 0, 1); // 1 agent at the table
  // None of the smokers have supplies
  sem_init(&tobaccoSem, 0, 0);
  sem_init(&paperSem, 0, 0);
  sem_init(&matchSem, 0, 0);
  // No supplies on the table
  sem_init(&tobacco, 0, 0);
  sem_init(&paper, 0, 0);
  sem_init(&match, 0, 0);
  sem_init(&mutex, 0, 1);

  //declare all pthreads
  printf("initialize pthreads.\n");
  pthread_t smokers[6];
  pthread_t paperPush, matchPush, tobaccoPush;
  pthread_t agent1, agent2, agent3;

  //create all pthreads - 3 agents, 3 pushers, 6 smokers
  pthread_create(&agent1, NULL, agentOne, NULL);
  pthread_create(&agent2, NULL, agentTwo, NULL);
  pthread_create(&agent3, NULL, agentThree, NULL);
  pthread_create(&paperPush, NULL, paperPusher, NULL);
  pthread_create(&matchPush, NULL, matchPusher, NULL);
  pthread_create(&tobaccoPush, NULL, tobaccoPusher, NULL);

  // 6 smokers - 2 each of tobacco, matches, paper
  int arg[6] = {0,1,2,3,4,5};
  for (int i = 0; i < 6; i++)
  {
    if(i % 3 == 0)   pthread_create(&smokers[i], NULL, tobaccoSmoker, (void*)& arg[i]);
    if(i % 3 == 1)   pthread_create(&smokers[i], NULL, matchSmoker, (void*)& arg[i]);
    if(i % 3 == 2)   pthread_create(&smokers[i], NULL, paperSmoker, (void*)& arg[i]);
  }

  //terminate all pthreads
  pthread_join(agent1, NULL);
  pthread_join(agent2, NULL);
  pthread_join(agent3, NULL);
  pthread_join(paperPush, NULL);
  pthread_join(matchPush, NULL);
  pthread_join(tobaccoPush, NULL);
  for (int i = 0; i < 6; i++) pthread_join(smokers[i], NULL);

  printf("everybody's done!\n");

  return 0;
}
