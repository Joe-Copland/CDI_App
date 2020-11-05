#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns current time in microseconds, compared with start of epoch, an inbuilt function of sdk hopefully
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
  char timeStart;
  //Run command in shell
  system(scpCommand);
  //Open file
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/time_log_file.csv", "r");
  //Grab int and place in timeStart
  //rewind(fp);
  fscanf(fp, "%s", timeStart);
  //Close file
  fclose(fp);
  // FILE *fp;
  //u_int64_t c;
  //fp = fopen("hi.csv","r");
  //while(1) {
  //  c = fgetc(fp);
  //  if( feof(fp) ) {
  //    break ;
  //    }
  //    printf("%lu", c);
  //}
  //fclose(fp);
  printf("%s",timeStart);
  const u_int64_t timeStart64 = (u_int64_t) timeStart;
  return timeStart64;
}

int main() {
  //Record finish time
  u_int64_t timeEnd = CdiOsGetMicroseconds();
  //Get scp command string
  char * scpCommand = getScpCommand();
  //printf("Returned command is: %s%s", scpCommand,"\n");
  //Get start time
  u_int64_t timeStart = getStartTime(scpCommand);
  //printf("Start time is: %lu%s", timeStart, "\n");
  //Free up memory allocation
  free(scpCommand);
  //Print difference between start and end times for latency
  printf("Latency is: %lu%s",timeStart," microseconds!\n");
  return 0;
}
