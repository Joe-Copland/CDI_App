#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>

uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  // Returns time in microseconds
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int recordTime(){
  //Records time
  uint64_t timeStamp = timeSinceEpochMicrosec();
  std::ofstream timeLog("/home/ec2-user/file_source/time_log_file.csv");
  // Send data to the stream
  timeLog << timeStamp << "\n";
  // Close the file
  timeLog.close();
  return 0;
}

int main() {
  recordTime();
  return 0;
}


