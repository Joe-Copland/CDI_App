#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns current time in microseconds, compared with start of epoch
u_int64_t CdiOsGetMicroseconds() {
  // Returns time in microseconds
  u_int64_t currentTime = 1256341;
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
  //Repeats input
  //printf( "You entered: %s %s", DNSName, "\n");
  //Form string for system() command, create memory allocation of large enough size
  char *scpCommand = malloc(200 * sizeof(char));
  if(scpCommand == NULL) return NULL;
  char scpCommandStart[] = "scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@";
  char scpCommandEnd[] = ":/home/ec2-user/file_source/time_log_file.csv /home/ec2-user/file_sink/";
  //Combine three parts into scpCommand
  snprintf(scpCommand,200,"%s%s%s",scpCommandStart,DNSName,scpCommandEnd);
  //Prints command
  //printf( "The SCP command is: %s%s",scpCommand,"\n");
  return scpCommand;
}

//Gets start time from time log file
u_int64_t getStartTime(char * scpCommand) {
  //runs command
  u_int64_t timeStart;
  system(scpCommand);
  //int got = fscanf("/home/ec2-user/file_sink/time_log_file.csv", "%lu", timeStart);
  FILE * fp;
  fp = fopen ("file.txt", "w+");
  //rewind(fp);
  fscanf(fp, "%lu", timeStart);
  fclose(fp);

  //get start time from file
  //std::fstream fin;
  //fin.open("/home/ec2-user/file_sink/time_log_file.csv");
  //std::string timeStart;
  //std::getline(fin,timeStart);
  //uint64_t timeStartInt = std::stoll(timeStart);
  return timeStart;
}

int main() {
  u_int64_t timeEnd = CdiOsGetMicroseconds();
  //Gets scp command string
  char * scpCommand = getScpCommand();
  //printf("Returned command is: %s%s", scpCommand,"\n");
  u_int64_t timeStart = getStartTime(scpCommand);
  printf("Start time is: %lu%s", timeStart, "\n");
  free(scpCommand);
  //Free up memory allocation
  printf("Latency is: %lu%s",timeEnd-timeStart," microseconds!\n");
  return 0;
}
