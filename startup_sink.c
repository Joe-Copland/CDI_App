#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearFile(){
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/end_time_log.csv", "w+");
  fclose(fp);
}

void clearBigFile(){
  FILE * fp2;
  fp2 = fopen ("/home/ec2-user/file_sink/network_info_store.csv", "w+");
  fclose(fp2);
}

char * getDNSName() {
  //Make it arbitrarily long so it doesn't get all filled up
  char *DNSName= malloc(200 * sizeof(char));
  //Asks for DNS name
  char DNSQuestion[] = "What is the public DNS name of the source instance?\n";
  printf(DNSQuestion);
  //Takes input from command line
  scanf("%s", DNSName);
  return DNSName;
}

//Returns command to copy time log file
char * getScpCommand(char * DNSName, char * scpCommandEnd) {
  char *scpCommand = malloc(200 * sizeof(char));
  if(scpCommand == NULL) return NULL;
  char scpCommandStart[] = "scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@";
  //char scpCommandEnd[] = ":/home/ec2-user/file_source/start_time_log.csv /home/ec2-user/file_sink/";
  //Combine three parts into scpCommand
  snprintf(scpCommand,200,"%s%s%s",scpCommandStart,DNSName,scpCommandEnd);
  return scpCommand;
}

//Writing to scp command file
void saveScp(char * scpCommand, char * scpDirectory){
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/scpCommand.txt", "w+");
  fprintf(fp, "%s", scpCommand);
  fclose(fp);
}

//opening connection
void startTest(char * receiverIP, int frameRate){
  //Forming startup command
  signed long payloadSize = frameRate * 86400;
  char frameRateString[20];
  char payloadSizeString[20];
  sprintf(frameRateString, "%d", frameRate);
  sprintf(payloadSizeString, "%li", payloadSize);
  char testCommand[600];
  char testCommandOne[] = "/home/ec2-user/aws-cdi-sdk/build/debug/bin/cdi_test --adapter EFA --local_ip ";
  char testCommandTwo[] = " --stats_cloudwatch CDIStats eu-west-1 Stream1 -X --connection_name joec_one   --rx AVM --dest_port 2000 --rate "
  char testCommandThree[] = " --num_transactions 100 -S --id 1 --payload_size ";
  char testCommandFour[] = " --pattern INC --avm_video 1920 1080 YCbCr422 Unused 10bit "
  char testCommandFive[] = " 1 BT2020 true false PQ Narrow 16 9 0 1080 0 0";
  //Combining bits of command
  snprintf(testCommand,600,"%s%s%s%s%s%s%s%s%s",testCommandOne,receiverIP,testCommandTwo,frameRateString,testCommandThree,payloadSizeString,testCommandFour,frameRateString,testCommandFive);
  printf("Hold onto your hats, we're going in!\n");
  //Opening connection
  system(testCommand);
}

int main(){
  //Getting and running scp command to test connection
  clearBigFile();
  char * DNSName = getDNSName();
  char scpCommandEnd[] = ":/home/ec2-user/file_source/start_time_log.csv /home/ec2-user/file_sink/";
  char scpDirectory[] = "/home/ec2-user/file_sink/scpCommand.txt";
  char * scpCommand = getScpCommand(DNSName,scpCommandEnd);
  system(scpCommand);
  //saving scp command for later
  saveScp(scpCommand,scpDirectory);
  free(scpCommand);
  //getting receiver IP
  char receiverIP[11];
  char receiverIPQuestion[] = "What is the receiver IP?\n";
  printf(receiverIPQuestion);
  scanf("%s", receiverIP);
  //Starting test
  int i;
  for (i = 1; i < 41; ++i)
  {
    clearFile();
    printf("Running test! \n");
    int frameRate = i * 5;
    startTest(receiverIP, frameRate);
  }
  printf("I ran it! \n");
  return 0;
}
