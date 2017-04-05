# libelectronpass
[![Build Status](https://travis-ci.org/electronpass/libelectronpass.svg?branch=master)](https://travis-ci.org/electronpass/libelectronpass)

Core C++ library for ElectronPass.

## Dependencies

- [libsodium](https://libsodium.org) - A modern and easy-to-use crypto library
- [jsoncpp v1.8.0](https://github.com/open-source-parsers/jsoncpp) - Already included in source code
- [gtest](https://github.com/google/googletest) - Required for building tests. On Arch linux you can use ```gtest``` package, on debian and ubuntu based distros you can use ```libgtest-dev``` package for installing it.

## Building

    mkdir build; cd build
    cmake ..
    make -j8

To run tests:

    make check

## Installing

    sudo make install

Note: if the library doesn't link on linux you should run ```sudo ldconfig /usr/local/lib```.

## Documentation
Documentation is generated using doxygen:

    doxygen docs/Doxyfile


You can also use make to generate documentation with:

    make docs

## Examples
Simple usage examples are located in ```examples/``` folder. To build examples run from ```build/``` folder:

    make examples

## License
Code in this project is licensed under [GNU LGPLv3 license](https://github.com/electronpass/libelectronpass/blob/master/LICENSE.LESSER). Some third party files are subjective to their respective license.

### JsonCpp
[JsonCpp](https://github.com/open-source-parsers/jsoncpp) is licensed under the MIT license. Used files are:

- ```include/json/*```
- ```src/jsoncpp.cpp```
