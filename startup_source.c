#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startTest(){
  //Making big command
  char testCommand[200];
  char testCommandStart[] = "./build/debug/bin/cdi_test --adapter EFA --local_ip ";
  char testCommandMiddle[] = " -X --tx AVM --remote_ip ";
  char testCommandEnd[] = " --dest_port 2000 --rate 60 --num_transactions 10000 -S --id 1 --payload_size 5184000 --pattern INC --avm_video 1920 1080 YCbCr422 Unused 10bit 60 1 BT2020 true false PQ Narrow 16 9 0 1080 0 0";
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
  snprintf(testCommand,200,"%s%s%s%s%s",testCommandStart,transmitterIP,testCommandMiddle,receiverIP,testCommandEnd);
  printf("Hold onto your hats, we're going in!\n");
  //Running command
  system(testCommand);
}

int main(){
  startTest();
  return 0;
}

