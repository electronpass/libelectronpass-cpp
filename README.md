# libelectronpass
Core C++ library for ElectronPass.

## Dependencies

- [jsoncpp v1.8.0](https://github.com/open-source-parsers/jsoncpp)
- [openssl](https://www.openssl.org)

## Instalation

    mkdir build; cd build
    cmake ..
    make

## License
Code in this project is licensed under [GNU LGPLv3 license](https://github.com/electronpass/libelectronpass/blob/master/LICENSE.LESSER). Some third party files are subjective to their respective license.

###JsonCpp
[JsonCpp](https://github.com/open-source-parsers/jsoncpp) is licensed under the MIT license. Used files are:

- ```include/json/*```
- ```src/jsoncpp.cpp```