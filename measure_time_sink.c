#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns current time in microseconds, compared with start of epoch, an inbuilt function of sdk hopefully
u_int64_t CdiOsGetMicroseconds() {
  // Returns time in microseconds
  u_int64_t currentTime = 28;
  return currentTime;
}


//Returns command to copy time log file
char * getScpCommand() {
  //Make it arbitrarily long so it doesn't get all filled up
  char DNSName[50];
  //Asks for DNS name
  char DNSQuestion[] = "What is the public DNS name of the source instance?\n";
  printf(DNSQuestion);
  //Takes input from command line
  scanf("%s", DNSName);
  //Form string for system() command, create memory allocation of large enough size
  char *scpCommand = malloc(200 * sizeof(char));
  if(scpCommand == NULL) return NULL;
  char scpCommandStart[] = "scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@";
  char scpCommandEnd[] = ":/home/ec2-user/file_source/time_log_file.csv /home/ec2-user/file_sink/";
  //Combine three parts into scpCommand
  snprintf(scpCommand,200,"%s%s%s",scpCommandStart,DNSName,scpCommandEnd);
  return scpCommand;
}

//Gets start time from time log file
u_int64_t getStartTime(char * scpCommand) {
  //Run command in shell
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

int main() {
  //Record finish time
  u_int64_t timeEnd = CdiOsGetMicroseconds();
  //Get scp command string
  char * scpCommand = getScpCommand();
  //Get start time
  u_int64_t timeStart = getStartTime(scpCommand);
  //Free up memory allocation
  free(scpCommand);
  //Print difference between start and end times for latency
  u_int64_t latency = timeEnd-timeStart;
  printf("Latency is: %lu%s",latency," microseconds!\n");
  return 0;
}
