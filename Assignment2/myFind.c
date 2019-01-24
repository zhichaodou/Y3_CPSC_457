/**********************************************
 * Last Name:   Dou
 * First Name:  Zhi Chao
 * Student ID:  30023286
 * Course:      CPSC 457
 * Tutorial:    01
 * Assignment:  2
 * Question:    Q2
 *
 * File name: myFind.c
 *********************************************/

#define _GNU_SOURCE 1
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void listdir(const char *name)
{ 

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path);
        } else {
            printf("%s/%s\n", name, entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char ** argv) {
  if(argc != 1){
    fprintf(stderr,"I don't take command line arguments.\n");
    exit(-1);
  }
  
  listdir(".");
  return 0;
}
