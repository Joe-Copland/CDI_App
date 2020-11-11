#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns current time in microseconds, compared with start of epoch
u_int64_t CdiOsGetMicroseconds() {
  // Returns time in microseconds
  u_int64_t currentTime = 97;
  return currentTime;
}

void recordTime(){
  //Records time
  u_int64_t timeStamp = CdiOsGetMicroseconds();
  //Opens file
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/end_time_log.csv", "a");
  //Writes timestamp to file
  fprintf(fp, "%lu%s", timeStamp,",");
  fclose(fp);
}

void clockSync(){
  //Records time
  char cdCommand[] = "cd /home/ec2-user/CDI_App";
  char syncCommand[] = "./clock_sync_sink";
  u_int64_t timeStamp = CdiOsGetMicroseconds();
  system(cdCommand);
  system(syncCommand);
  //Opens file
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/end_clock_sync.csv", "a");
  //Writes timestamp to file
  fprintf(fp, "%lu%s", timeStamp,",");
  fclose(fp);
}

//Gets start time from time log file
void grabStartTimes() {
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
}

void grabSyncTimes(){
  //Run command in shell
  char scpCommand[200];
  //Open file
  FILE *fp;
  if ((fp = fopen("/home/ec2-user/file_sink/scpSyncCommand.txt","r")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  //fscanf(fp,"%[^\n]s", &scpCommand);
  fgets(scpCommand,200,fp);
  fclose(fp);
  printf("%s%s",scpCommand,"\n");
  system(scpCommand);
}

int main() {
  recordTime();
  clockSync();
  grabStartTimes();
  grabSyncTimes();
  return 0;
}
