# CDI App

Some code to get some metrics out of the AWS CDI SDK

## Description

* A number of tests of varying payload size are ran, with timestamps taken at various point 
* The network latency, packet rate and transmission rate measured using these time stamps and are plotted


## Getting Started

### Dependencies

* Two EFA enabled EC2 instances, with the AWS-CDI-SDK installed.
* A C and C++ compiler
* Python, along with various python libraries seen in the latency.py file


### Installing

* To get the AWS-CDI-SDK set up:
```
sudo yum update -y --skip-broken
curl -O https://efa-installer.amazonaws.com/aws-efa-installer-1.10.0.tar.gz
tar -xf aws-efa-installer-1.10.0.tar.gz
cd aws-efa-installer
sudo ./efa_installer.sh -y --minimal
reboot
sudo yum install git
git clone https://github.com/aws/aws-cdi-sdk
git clone --single-branch --branch v1.9.x-cdi https://github.com/aws/libfabric
```
It may say libfabric is already installed
```
aws configure
```
Enter keys from "Keys for CDI" file, region as "eu-west-1" and output format as json
```
sudo yum groupinstall "Development Tools"
wget https://cmake.org/files/v3.18/cmake-3.18.0.tar.gz
tar -xvzf cmake-3.18.0.tar.gz
cd cmake-3.18.0
./bootstrap
sudo make
sudo make install
cd
sudo yum install libcurl-devel openssl-devel libuuid-devel pulseaudio-libs-devel
cd
git clone -b 1.8.46 https://github.com/aws/aws-sdk-cpp.git
sudo yum -y install gcc-c++ make libnl3-devel autoconf automake libtool doxygen ncurses-devel
```

* Then clone this repo on both machines, compile the startup_sink.c and get_time_sink.cpp on the sink instance and startup_source.c and get_time_source.cpp on the source instance

* Make a directory in /home/ec2-user/ called file_source or file_sink depending on the machine

* Copy across the pem file to the home directory of each so that the scp commands work

* Copy test_receiver.c on the sink instance and test_transmitter.c on the source instance to "/home/ec2-user/aws-cdi-sdk/src/test/", overwriting the files there

* Build the sdk code using:
```
make DEBUG=y AWS_SDK=/home/ec2-user/aws-sdk-cpp
```

* If it complains, you may need to create some empty files in file_sink and file_source, for example network_file_store.csv but probably not

Some command hints:

To grab a csv file from other instance:
```
scp -i /home/ec2-user/joec_cdi_ireland.pem ec2-user@ec2-34-255-117-169.eu-west-1.compute.amazonaws.com:/home/ec2-user/file_source/file_to_copy.txt /home/ec2-user/file_sink/
```
To build c++ code:
```
g++ measure_time_source.cpp -o measure_time_source
```
To build c code:
```
gcc measure_time_source.c -o measure_time_source
```

### Executing program

* Just run the startup sink file, followed by the source and follow the steps

* To view the plots, copy them across to a different machine as I can't get any graphics to work on the EC2 instances

## Help

You ain't gettin' no help

## Authors

* Me

## Version History

* 0.2
    * Solved world hunger
* 0.1
    * Initial Release

## License

This project is licensed under the Joe License - don't see a file for details

## Acknowledgments

Inspiration, code snippets, etc.
* https://github.com/aws/aws-cdi-sdk
* [Pingu]https://en.wikipedia.org/wiki/Pingu
