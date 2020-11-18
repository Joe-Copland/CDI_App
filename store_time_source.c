#include <stdio.h>
#include <stdlib.h>

//Records the current time using c++ code
void recordTime(){
 char getTime[] = "./get_time_source";
 system(getTime);
}

int main() {
  recordTime();
  return 0;
}
