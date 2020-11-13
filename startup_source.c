#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearFile(){
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_source/start_time_log.csv", "w+");
  fclose(fp);
}

void startTest(){
  //Making big command
  char testCommand[600];
  char testCommandStart[] = "/home/ec2-user/aws-cdi-sdk/build/debug/bin/cdi_test --adapter EFA --local_ip ";
  char testCommandMiddle[] = " -X --tx AVM --remote_ip ";
  char testCommandEnd[] = " --dest_port 2000 --rate 60 --num_transactions 100 -S --id 1 --payload_size 2592000 --pattern INC --avm_video 960 1080 YCbCr422 Unused 10bit 60 1 BT2020 true false PQ Narrow 16 9 0 1080 0 0";
  char receiverIP[11];
  //Getting receiver IP
  char receiverIPQuestion[] = "What is the receiver IP?\n";
  printf(receiverIPQuestion);
  scanf("%s", receiverIP);
  char transmitterIP[11];
  //Getting transmitter IP
  char transmitterIPQuestion[] = "What is the transmitter IP?\n";
  printf(transmitterIPQuestion);
  scanf("%s", transmitterIP);
  //Combining bits of command
  snprintf(testCommand,600,"%s%s%s%s%s",testCommandStart,transmitterIP,testCommandMiddle,receiverIP,testCommandEnd);
  printf("Hold onto your hats, we're going in!\n");
  //Running command
  system(testCommand);
}

int main(){
  clearFile();
  startTest();
  return 0;
}

