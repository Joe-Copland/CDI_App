# CDI App

A work in process of a some code to get some metrics out of the AWS CDI SDK

## Description

* Various iterations of the code have now been made and some older code is still included in the repository.
* The current effort takes timestamps whenever a packet is sent of received, these are stored in csv files and are compared to give network latency.

## Getting Started

### Dependencies

* Two EFA enabled EC2 instances, with the AWS-CDI-SDK installed.
* Probably some other stuff, I can't remember.

### Installing

To get the AWS-CDI-SDK set up:
'''
sudo yum update -y --skip-broken
curl -O https://efa-installer.amazonaws.com/aws-efa-installer-1.10.0.tar.gz
tar -xf aws-efa-installer-1.10.0.tar.gz
cd aws-efa-installer
sudo ./efa_installer.sh -y --minimal

reboot

sudo yum install git
git clone https://github.com/aws/aws-cdi-sdk
git clone --single-branch --branch v1.9.x-cdi https://github.com/aws/libfabric

It may say libfabric is already installed

aws configure

Enter keys from "Keys for CDI" file, region as "eu-west-1" and output format as json

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
'''

* Then clone this repo on both machines, compile the sink code on the sink instance and the source code on the source instance

* You then need to combine some code into test_transmitter.c and test_receiver.c, I will explain this later dw

* Make a directory called file_source or file_sink depending on the machine

* Copy across the pem file to the home directory of each so that the scp commands work

### Executing program

* Just run the startup source file, followed by the sink and follow the steps

## Help

You ain't gettin' no help

## Authors

* Me

## Version History

* 0.2
    *Solved world hunger
* 0.1
    * Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments

Inspiration, code snippets, etc.
* [Pingu]https://en.wikipedia.org/wiki/Pingu
