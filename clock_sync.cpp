#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <unistd.h>

//Returns current time in microseconds, compared with start of epoch
uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  // Returns time in microseconds
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

void recordTime(){
  //Records time
  uint64_t timeStamp = timeSinceEpochMicrosec();
  //opens file
  std::ofstream timeLog("/home/ec2-user/file_source/start_clock_sync.csv");
  // Send time to file
  timeLog << timeStamp << "\n";
  // Closes the file
  timeLog.close();
}

int main() {
  recordTime();
  return 0;
}
