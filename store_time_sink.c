#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Records the time using c++ code
void recordTime(){
 char getTime[] = "./get_time_sink";
 system(getTime);
}

//Copies start_time_log file from source instance
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
  fgets(scpCommand,200,fp);
  fclose(fp);
  printf("%s%s",scpCommand,"\n");
  system(scpCommand);
}

//Plots graph
void plotGraph(){
sleep(1);
system("python3 /home/ec2-user/CDI_App/latency_plot.py");  
system("display network_speed_plot.png")
}

int main() {
  recordTime();
  grabStartTimes();
  plotGraph();
  return 0;
}
