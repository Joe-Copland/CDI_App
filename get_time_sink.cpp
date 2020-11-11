#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

//Returns current time in microseconds, compared with start of epoch
uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  // Returns time in microseconds
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

// Usage example: filePutContents("./yourfile.txt", "content", true);
void filePutContents(const std::string& name, const std::string& content, bool append = false) {
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app);
    else
        outfile.open(name);
    outfile << content;
}

void recordTime(){
  //Records time
  uint64_t timeStamp = timeSinceEpochMicrosec();
  std::string timeStampString = std::to_string(timeStamp) + ",";
  filePutContents("/home/ec2-user/file_sink/end_time_log.csv", timeStampString, true);
}

int main() {
  recordTime();
  return 0;
}
