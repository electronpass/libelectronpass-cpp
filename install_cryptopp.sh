#!/bin/bash
mkdir cryptopp_build
cd cryptopp_build
wget https://github.com/weidai11/cryptopp/archive/CRYPTOPP_5_6_5.tar.gz
tar -xzf CRYPTOPP_5_6_5.tar.gz

cd cryptopp-CRYPTOPP_5_6_5
make libcryptopp.a -j4
cd ../..

mkdir cryptopp
mkdir cryptopp/cryptopp
mv cryptopp_build/cryptopp-CRYPTOPP_5_6_5/libcryptopp.a cryptopp/libcryptopp.a
mv cryptopp_build/cryptopp-CRYPTOPP_5_6_5/*.h cryptopp/cryptopp

rm -rf cryptopp_build
