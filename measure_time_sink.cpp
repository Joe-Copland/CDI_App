#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>

uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  // Returns time in microseconds
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

std::string getSshCommand() {
  std::string DNSName;
  std::cout << "What is the public DNS name of the source instance?" << "\n";
  std::cin >> DNSName;
  std::string sshCommand = "scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@" + DNSName + ":/home/ec2-user/file_source/time_log_file.csv /home/ec2-user/file_sink/";
  return sshCommand;
}

uint64_t getStartTime() {
  std::string sshCommandString = getSshCommand();
  //std::cout << sshCommandString << "\n";
  const char * ssh = sshCommandString.c_str();
  system(ssh);
  std::fstream fin;
  fin.open("/home/ec2-user/file_sink/time_log_file.csv");
  std::string timeStart;
  std::getline(fin,timeStart);
  uint64_t timeStartInt = std::stoll(timeStart);
  return timeStartInt;
}

int main() {
  //Records time
  uint64_t timeEnd = timeSinceEpochMicrosec();
  uint64_t timeStart = getStartTime();
  //Prints out latency
  std::cout << timeEnd-timeStart << "\n";
  return 0;
}
