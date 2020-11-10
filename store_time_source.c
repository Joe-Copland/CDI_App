#include <stdio.h>
#include <stdlib.h>

//Returns current time in microseconds, compared with start of epoch
u_int64_t CdiOsGetMicroseconds() {
  // Returns time in microseconds
  u_int64_t currentTime = 21;
  return currentTime;
}

void recordTime(){
  //Records time
  u_int64_t timeStamp = CdiOsGetMicroseconds();
  //Opens file
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_source/start_time_log.csv", "a");
  //Writes timestamp to file
  fprintf(fp, "%lu%s", timeStamp,",");
  fclose(fp);
}

void clockSync(){
  //Records time
  char cdCommand[] = "cd /home/ec2-user/CDI_App";
  char syncCommand[] = "./clock_sync_source";
  u_int64_t timeStamp = CdiOsGetMicroseconds();
  system(cdCommand);
  system(syncCommand);
  //Opens file
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_source/start_clock_sync.csv", "a");
  //Writes timestamp to file
  fprintf(fp, "%lu%s", timeStamp,",");
  fclose(fp);
}

int main() {
  recordTime();
  clockSync();
  return 0;
}
