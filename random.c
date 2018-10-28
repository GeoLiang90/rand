#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int gen(){
  int * ran = malloc(sizeof(char));
  int dev = open("/dev/random",O_RDONLY);
  read(dev,ran,sizeof(int));
  return *ran;
}

int main(){
  int * numbers = calloc(10, sizeof(int));
  printf("Generating random numbers \n");
  for(int i = 0; i < 10; i++){
    int random = gen();
    printf("random %d: %d \n", i , random);
    numbers[i] = random;
  }

  printf("Now opening writing numbers to file...\n");
  int writing = open("stuff.txt",O_WRONLY);
  if (writing < 0){
    perror("Error opening file to write");
  }
  else{
    write(writing, numbers, 10 * sizeof(int));
  }

  printf("Now opening file to read...\n");

  int * obtained = calloc(10, sizeof(int));

  int reading = open("stuff.txt",O_RDONLY);
  if (reading < 0){
    perror("Error opening file to read\n");
  }
  else{
    read(reading,obtained,10 * sizeof(int));
  }

  printf("Now verifying that values are the same\n");
  for (int x = 0; x < 10 ; x++){
    if (numbers[x] == obtained[x]){
      printf("random %d: %d \n",x,obtained[x]);
    }
    else{
      printf("Something was not equal\n");
    }
  }

  return 0;
}
