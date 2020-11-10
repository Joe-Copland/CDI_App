#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Gets start time from time log file
void grab() {
  //Run command in shell
  char scpCommand[200];
  //Open file
  FILE *fp;
  if ((fp = fopen("/home/ec2-user/file_sink/scpCommand.txt","r")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  //fscanf(fp,"%[^\n]s", &scpCommand);
  fgets(scpCommand,200,fp);
  fclose(fp);
  printf("%s%s",scpCommand,"\n");
  system(scpCommand);
}

int main() {
  grab();
  return 0;
}
