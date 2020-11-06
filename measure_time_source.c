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
  fp = fopen ("/home/ec2-user/file_source/time_log_file.csv", "w+");
  //Writes timestamp to file
  fprintf(fp, "%lu", timeStamp);
  fclose(fp);
}

int main() {
  recordTime();
  return 0;
}

