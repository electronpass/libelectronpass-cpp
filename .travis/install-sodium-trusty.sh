#!/bin/bash
# installs libsodium on Ubuntu 14.04 (travis ci env)
sudo add-apt-repository ppa:chris-lea/libsodium -y;
sudo echo "deb http://ppa.launchpad.net/chris-lea/libsodium/ubuntu trusty main" >> /etc/apt/sources.list;
sudo echo "deb-src http://ppa.launchpad.net/chris-lea/libsodium/ubuntu trusty main" >> /etc/apt/sources.list;
sudo apt-get update && sudo apt-get install -y libsodium-dev;
