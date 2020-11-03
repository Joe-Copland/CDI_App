#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>

//Returns time in microseconds, since start of epoch
uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

//Returns command to copy time log file
std::string getScpCommand() {
  std::string DNSName;
  //Asks for DNS name
  std::cout << "What is the public DNS name of the source instance?" << "\n";
  std::cin >> DNSName;
  //Forms string for system()
  std::string scpCommand = "scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@" + DNSName + ":/home/ec2-user/file_source/time_log_file.csv /home/ec2-user/file_sink/";
  return scpCommand;
}

//Gets start time from time log file
uint64_t getStartTime(std::string scpCommandString) {
  //converts to correct type
  const char * scp = scpCommandString.c_str();
  //runs command
  system(scp);
  //get start time from file
  std::fstream fin;
  fin.open("/home/ec2-user/file_sink/time_log_file.csv");
  std::string timeStart;
  std::getline(fin,timeStart);
  uint64_t timeStartInt = std::stoll(timeStart);
  return timeStartInt;
}

int main() {
  //Gets scp command string
  std::string scpCommandString = getScpCommand();
  //Records time
  uint64_t timeEnd = timeSinceEpochMicrosec();
  uint64_t timeStart = getStartTime(scpCommandString);
  //Prints out latency
  std::cout << timeEnd-timeStart << "\n";
  return 0;
}
