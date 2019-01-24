/**********************************************
 * Last Name:   Dou
 * First Name:  Zhi Chao
 * Student ID:  30023286
 * Course:      CPSC 457
 * Tutorial:    01
 * Assignment:  3
 * Question:    Q5
 *
 * File name: count.c
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

#define maxIntArraySize 10000

int64_t listOfNums[maxIntArraySize];

struct sum_struct{
  long long answer;
  int64_t start;
  int64_t end;
};


/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
     if( n <= 1) return 0; // small numbers are not primes
     if( n <= 3) return 1; // 2 and 3 are prime
     if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
     int64_t i = 5;
     int64_t max = sqrt(n);
     while( i <= max) {
         if (n % i == 0 || n % (i+2) == 0) return 0;
         i += 6;
     }
     return 1;
}


//Thread function to generate the # of primes in said thread
void* sum_runner(void* arg)
{
  struct sum_struct *arg_struct = (struct sum_struct*) arg;

  long long sum = 0;
  //int countTakeNum = sizeof(arg_struct->takeNum)/sizeof(int);
  //countTakeNum += 2;
  //printf("%d\n",countTakeNum);
  for(int64_t b = arg_struct->start; b <= arg_struct->end; b++) {
    //printf("%11d\n", b);
    if( isPrime(listOfNums[b])== 1) {sum = sum + 1;}

  }
  arg_struct->answer = sum;
  pthread_exit(0);
}

// Main Function
int main( int argc, char ** argv)
{

    int nThreads = atoi(argv[1]);
    //int listOfNums[maxIntArraySize];
    int currentSize = 0;
    int listCounter = 0;
    /// count the primes
    printf("Counting primes using %d thread%s.\n", nThreads, nThreads == 1 ? "s" : "");
    int count = 0;
    while( 1) {
        int64_t num;
        if( 1 != scanf("%ld", & num)) break;
	//printf("%d\n",num);
	listOfNums[listCounter] = num;
	currentSize += 1;
	listCounter += 1;
        //if( isPrime(num)) count ++;
    }

    struct sum_struct args[nThreads];
    //int * removeNums = listOfNums;
    int divider = currentSize/nThreads;
    //divider = divider -1;
    //printf("divider is: %d\n",divider);
    int lastThread = nThreads -1;

    //initialize first thread
    args[0].start = 0;
    args[0].end = args[0].start + divider;
    //printf("At first thread %d: start is: %d  end is: %d\n", 0, args[0].start, args[0].end);
    int k = 0;
    for (int j = 1 ; j < nThreads; j++) {
      if(j == lastThread){
        args[j].start = args[k].end + 1;
        args[j].end = currentSize - 1;
        //printf("At final thread %d: start is: %d  end is: %d\n", j, args[j].start, args[j].end);
      }else{
        args[j].start = args[k].end + 1;
        args[j].end = args[j].start + divider;
        //printf("At thread %d: start is: %d  end is: %d\n", j, args[j].start, args[j].end);
      }
      k = k +1;
    }


    // Launcher Thread
    pthread_t tids[nThreads];
    for (int i = 0; i < nThreads; i++){
	      pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, sum_runner, &args[i]);
    }

    for (int i = 0; i < nThreads; i++) {
      pthread_join(tids[i], NULL);
      //printf("\nSum for thread %d is %11d\n", i, args[i].answer);
      count += args[i].answer;
    }
    printf("Found %ld primes.\n", count);

    return 0;
}
