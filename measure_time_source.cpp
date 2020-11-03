#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <thread>
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
  std::ofstream timeLog("/home/ec2-user/file_source/time_log_file.csv");
  // Send time to file
  timeLog << timeStamp << "\n";
  // Closes the file
  timeLog.close();
}

void doNothing(){
  sleep(5);
}

int main() {
  //start measuring recordTime execution time, must be below 1ms
  uint64_t start = timeSinceEpochMicrosec();
  //start thread for recordTime
  std::thread recordTimeThread (recordTime);
  //start thread for data transfer
  std::thread doNothingThread (doNothing);
  //join thread
  recordTimeThread.join();
  uint64_t end = timeSinceEpochMicrosec();
  std::cout << "recordTime function execution time: " << end-start << " microseconds! \n";
  doNothingThread.join();
  return 0;
}


