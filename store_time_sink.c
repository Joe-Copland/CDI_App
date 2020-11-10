#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Returns current time in microseconds, compared with start of epoch, an inbuil$
u_int64_t CdiOsGetMicroseconds() {
  // Returns time in microseconds
  u_int64_t currentTime = 28;
  return currentTime;
}

//Gets start time from time log file
u_int64_t getStartTime() {
  //Run command in shell
  char scpCommand[200];
  //Open file
  FILE *fp;
  if ((fp = fopen("/home/ec2-user/file_sink/scpCommand.txt","r")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  //fscanf(fp,"%[^\n]s", &scpCommand);
  fgets(scpCommand,200,fp);
  fclose(fp);
  printf("%s%s",scpCommand,"\n");
  system(scpCommand);
  u_int64_t timeStart;
  //Open file
  FILE *fptr;
  if ((fptr = fopen("/home/ec2-user/file_sink/time_log_file.csv","r")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  fscanf(fptr,"%lu", &timeStart);
  fclose(fptr);
  return timeStart;
}

void *recordTime(void *vargp){
  //Record finish time
  u_int64_t timeEnd = CdiOsGetMicroseconds();
  //Get start time
  u_int64_t timeStart = getStartTime();
  //Print difference between start and end times for latency
  u_int64_t latency = timeEnd-timeStart;
  printf("Latency is: %lu%s",latency," microseconds!\n");
  return NULL;
}

int main() {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, recordTime, NULL);
  pthread_join(thread_id, NULL);
  return 0;
}


