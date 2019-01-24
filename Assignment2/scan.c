/**********************************************
 * Last Name:   Dou
 * First Name:  Zhi Chao
 * Student ID:  30023286
 * Course:      CPSC 457
 * Tutorial:    01
 * Assignment:  2
 * Question:    Q3
 *
 * File name: scan.c
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define sizeFileName 500
#define filesMax 5000

struct fileHolder {
  char *name;
  __off_t size;
};


int cmpfunc_aux(struct fileHolder const *a, struct fileHolder const *b) {
  if (a->size > b->size) {
    return -1;
  } else if (a->size < b->size) {
    return 1;
  } else {
    return 0;
  }
}
int cmpfunc(void const *a, void const *b) { return cmpfunc_aux(a, b); }


int main( int argc, char ** argv) {
  FILE * fp = popen( "find . -type f", "r");
  char * type = argv[1];
  char * extension = ".";

  char* tExtension;
  tExtension = malloc(strlen(type)+1+4);
  strcpy(tExtension, extension); 
  strcat(tExtension, type);
  // printf("%s\n",tExtension);
  
  int amount = atoi(argv[2]);
  //printf("%d\n",amount);
  
  char buff[sizeFileName];
  size_t nFiles = 0;
  char * files[filesMax];
  while(fgets(buff,sizeFileName,fp)) {
    int leng = strlen(buff) - 1;
    if (strncmp(buff + leng - 4, tExtension, 4) == 0){
      files[nFiles] = strndup(buff,leng);
      //printf("\t%s\n", files[nFiles]);
      nFiles ++;
    }
  }
  fclose(fp);
  //printf("Found %d files, will take the top %d\n", nFiles,amount);

  long long totalBytes = 0;
  struct stat st;

  struct fileHolder fileHolds[filesMax];
  
  for(int i = 0;i< nFiles; i ++) {
    if(0!= stat(files[i],&st)){
      perror("stat failed:");
      exit(-1);
    }
    fileHolds[i].name = files[i];
    fileHolds[i].size = st.st_size;
  }
  
  qsort(fileHolds , nFiles, sizeof *fileHolds, &cmpfunc);
  for(int i = 0;i< amount; i++){
    if(fileHolds[i].name != NULL){
      printf("%s : %ld\n",fileHolds[i].name,fileHolds[i].size);
      totalBytes = totalBytes + fileHolds[i].size;
    }else{continue;}
  }
  
  printf("Total size: %lld\n", totalBytes);

  // clean up
  for(int i = 0; i < nFiles ; i ++ ) {
    free(files[i]);
  }
  return 0;
}
