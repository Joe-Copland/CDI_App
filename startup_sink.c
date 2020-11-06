#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char scpCommandEnd[] = ":/home/ec2-user/file_source/test_connection.txt /home/ec2-user/file_sink/";
  //Combine three parts into scpCommand
  snprintf(scpCommand,200,"%s%s%s",scpCommandStart,DNSName,scpCommandEnd);
  return scpCommand;
}

void saveScp(char * scpCommand){
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_sink/scpCommand.txt", "w+");
  //Writes timestamp to file
  fprintf(fp, "%s", scpCommand);
  fclose(fp);
}

void startTest(){
  char testCommand[200];
  char testCommandStart[] = "./build/debug/bin/cdi_test --adapter EFA --local_ip ";
  char testCommandEnd[] = " --stats_cloudwatch CDIStats eu-west-1 Stream1 -X --connection_name joec_one   --rx AVM --dest_port 2000 --rate 60 --num_transactions 10000 -S --id 1 --payload_size 5184000 --pattern INC --avm_video 1920 1080 YCbCr422 Unused 10bit 60 1 BT2020 true false PQ Narrow 16 9 0 1080 0 0";
  char receiverIP[11];
  char receiverIPQuestion[] = "What is the receiver IP?\n";
  printf(receiverIPQuestion);
  scanf("%s", receiverIP);
  snprintf(testCommand,200,"%s%s%s",testCommandStart,receiverIP,testCommandEnd);
  printf("Hold onto your hats, we're going in!\n");
  system(testCommand);
}

int main(){
  char * scpCommand = getScpCommand();
  system(scpCommand);
  saveScp(scpCommand);
  startTest();
  return 0;
}
