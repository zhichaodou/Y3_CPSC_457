/**********************************************
 * Last Name:   Dou
 * First Name:  Zhi Chao
 * Student ID:  30023286
 * Course:      CPSC 457
 * Tutorial:    01
 * Assignment:  2
 * Question:    Q5
 *
 * File name: sum.c
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
  int threadValue;
};


int main( int argc, char ** argv){

  char * fileName = argv[1];
  int amountThreads = atoi(argv[2]);
  FILE *myFile;
  myFile = fopen(fileName, "r");

  //read file into array
  int numberArray[nIntegers];
  int arraySize = 0;
  while (arraySize < nIntegers && fscanf(myFile, "%d", numberArray + arraySize) == 1) {
        arraySize++;
    }

  //test contents of array and size
  // printf("Size of array is: %d\n",arraySize);
  //for (int i = 0; i < arraySize; i++){
  //printf("Number is: %d\n", numberArray[i]);
  //}

  //test number of threads
  // printf("Number of threads is: %d\n",amountThreads);
    
  int cutter = (arraySize%amountThreads);
  int arrayGroupOneSize = ((arraySize/amountThreads)+1);
  int arrayGroupTwoSize = (arraySize/amountThreads);
  //test print to check int values
  //printf("Split point is at:%d\nFirst group is size: %d\nSecond group is size:%d\n",cutter,arrayGroupOneSize,arrayGroupTwoSize);

  struct threadHolder threads[amountThreads];
  int counter;
  int j = 0;
  for (int i = 0; i < amountThreads; i++) {
    if(i < cutter){
      counter = 0;
      threads[i].threadValue = 0;
      while(counter < arrayGroupOneSize){
	threads[i].threadValue = threads[i].threadValue + numberArray[j];
	counter = counter + 1;
        j = j + 1;
      }
    }else if (i >= cutter) {
      //printf("%d\n",j);
      counter = 0;
      threads[i].threadValue = 0;
      while(counter < arrayGroupTwoSize){
	threads[i].threadValue = threads[i].threadValue + numberArray[j];
	counter = counter + 1;
	j = j + 1;
      } 
    }    
  }
  
  int threadTotal = 0; 
  for(int i = 0; i <= (amountThreads-1);i++){
    int p = 0;
    printf("Thread %d: %d\n", (i+1), threads[i].threadValue);
    threadTotal = threadTotal + threads[i].threadValue;
  }
  printf("Sum = %d\n",threadTotal); 
}
