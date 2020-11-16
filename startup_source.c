#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clearFile(){
  FILE * fp;
  fp = fopen ("/home/ec2-user/file_source/start_time_log.csv", "w+");
  fclose(fp);
}

void startTest(char * receiverIP, char * transmitterIP, int pixelWidth){
  
  //Getting pixel parameters to vary
  signed long payloadSize = pixelWidth * 2700;
  char pixelWidthString[20];
  char payloadSizeString[20];
  sprintf(pixelWidthString, "%d", pixelWidth);
  sprintf(payloadSizeString, "%li", payloadSize);
  
  //Making big command
  char testCommand[600];
  char testCommandOne[] = "/home/ec2-user/aws-cdi-sdk/build/debug/bin/cdi_test --adapter EFA --local_ip ";
  char testCommandTwo[] = " -X --tx AVM --remote_ip ";
  char testCommandThree[] = " --dest_port 2000 --rate 60 --num_transactions 100 -S --id 1 --payload_size ";
  char testCommandFour[] = " --pattern INC --avm_video ";
  char testCommandFive[] = " 1080 YCbCr422 Unused 10bit 60 1 BT2020 true false PQ Narrow 16 9 0 1080 0 0";
 
  //Combining bits of command
  snprintf(testCommand,600,"%s%s%s%s%s%s%s%s%s",testCommandOne,transmitterIP,testCommandTwo,receiverIP,testCommandThree,payloadSizeString,testCommandFour,pixelWidthString,testCommandFive);
  printf("Hold onto your hats, we're going in!\n");
  //Running command
  system(testCommand);
}

int main(){
  
   //Getting receiver IP
  char receiverIP[11];
  char receiverIPQuestion[] = "What is the receiver IP?\n";
  printf(receiverIPQuestion);
  scanf("%s", receiverIP);
  char transmitterIP[11];
  
  //Getting transmitter IP
  char transmitterIPQuestion[] = "What is the transmitter IP?\n";
  printf(transmitterIPQuestion);
  scanf("%s", transmitterIP);
  
  //Starting test
  int i;
  for (i = 1; i < 41; ++i)
  {
    clearFile();
    printf("Running test! \n");
    int pixelWidth = i * 480;
    startTest(receiverIP, transmitterIP, pixelWidth);
    sleep(10);
  }
  
  return 0;
}

