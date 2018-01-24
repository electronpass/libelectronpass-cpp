#!/bin/bash
mkdir cryptopp_build
cd cryptopp_build
wget https://github.com/weidai11/cryptopp/archive/CRYPTOPP_6_0_0.tar.gz
tar -xzf CRYPTOPP*.tar.gz

cd cryptopp-CRYPTOPP*
make libcryptopp.a -j4
cd ../..

mkdir cryptopp
mkdir cryptopp/cryptopp
mv cryptopp_build/cryptopp-CRYPTOPP*/libcryptopp.a cryptopp/libcryptopp.a
mv cryptopp_build/cryptopp-CRYPTOPP*/*.h cryptopp/cryptopp

rm -rf cryptopp_build
