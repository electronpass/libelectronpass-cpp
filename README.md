# libelectronpass
[![Build Status](https://travis-ci.org/electronpass/libelectronpass.svg?branch=master)](https://travis-ci.org/electronpass/libelectronpass)

Core C++ library for ElectronPass.

## Dependencies

- [libsodium](https://libsodium.org) - A modern and easy-to-use crypto library
- [jsoncpp v1.8.0](https://github.com/open-source-parsers/jsoncpp) - Already included in source code

## Building

    mkdir build; cd build
    cmake ..
    make libelectronpass -j8
    make check

## Documentation
Documentation is generated using doxygen:

    doxygen docs/Doxyfile


You can also use make to generate documentation with:

    make docs
    
and run tests with:

    make check

## License
Code in this project is licensed under [GNU LGPLv3 license](https://github.com/electronpass/libelectronpass/blob/master/LICENSE.LESSER). Some third party files are subjective to their respective license.

### JsonCpp
[JsonCpp](https://github.com/open-source-parsers/jsoncpp) is licensed under the MIT license. Used files are:

- ```include/json/*```
- ```src/jsoncpp.cpp```
