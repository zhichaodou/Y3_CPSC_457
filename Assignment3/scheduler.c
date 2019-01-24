/**********************************************
 * Last Name:   Dou
 * First Name:  Zhi Chao
 * Student ID:  30023286
 * Course:      CPSC 457
 * Tutorial:    01
 * Assignment:  3
 * Question:    Q7
 *
 * File name: scheduler.c
 *********************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define nIntegers 1000000
#define nThreads 999999

struct threadHolder {
  int arrival;
  int burst;
  int burstMod;
  int start;
  int finish;
  int turnAround;
  int wait;
};

void roundRobin(struct threadHolder * thread);
void firstCome(struct threadHolder *thread);

int main( int argc, char ** argv){

  char * fileName = argv[1];
  char * typeSort = argv[2];
  printf("%s\n",typeSort);
  int qTime  = atoi(argv[3]);

  FILE *myFile;
  myFile = fopen(fileName, "r");

  //read file into array
  int numberArray[nIntegers];
  int arraySize = 0;
  while (arraySize < nIntegers && fscanf(myFile, "%d", numberArray + arraySize) == 1) {
        arraySize++;
    }

  //test contents of array and size
  /***
  printf("Size of array is: %d\n",arraySize);
   for (int i = 0; i < arraySize; i++){
   printf("Number is: %d\n", numberArray[i]);
  }
  ***/

   int numOfProcess = arraySize/2;
  int pa = 0;
  int pb = pa + 1;
  int totalTime = 0;
  struct threadHolder threads[numOfProcess];
  for (int i = 0 ; i < numOfProcess; i++){
    threads[i].arrival = numberArray[pa];
    //printf("arrival:%d\t", threads[i].arrival);
    threads[i].burst = numberArray[pb];
    //printf("burst:%d\n", threads[i].burst);

    //initialize the rest
    threads[i].burstMod = numberArray[pb];
    threads[i].start = 0;
    threads[i].finish = 0;
    threads[i].turnAround = 0;
    threads[i].wait = 0;
    totalTime = totalTime + threads[i].burst;
    pa = pb + 1;
    pb = pa + 1;
  }

  //checks type
  printf("about the print %s\n",typeSort);
  char * RR = "RR";
  char * SJF = "SJF";
  if (typeSort == RR){
    roundRobin(threads);
  }else if(typeSort == SJF) {
    firstCome(threads);
  }else{
    printf("Please pick a type\n");
  }
  return 0;
}


///***
void roundRobin(struct threadHolder *threads){
  printf("burst:%d\n", threads[1].burst);
}

void firstCome(struct threadHolder *threads){

  printf("burst:%d\n", threads[0].burst);

}
//***/
