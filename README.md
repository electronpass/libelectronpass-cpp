# libelectronpass
Core C++ library for ElectronPass.

## Dependencies

- [jsoncpp v1.8.0](https://github.com/open-source-parsers/jsoncpp)
- [openssl](https://www.openssl.org)

## Building

    mkdir build; cd build
    cmake ..
    make libelectronpass -j8

## Documentation
Documentation is generated using doxygen:

    doxygen docs/Doxyfile


You can also use make to generate documentation with:

    make docs

## License
Code in this project is licensed under [GNU LGPLv3 license](https://github.com/electronpass/libelectronpass/blob/master/LICENSE.LESSER). Some third party files are subjective to their respective license.

###JsonCpp
[JsonCpp](https://github.com/open-source-parsers/jsoncpp) is licensed under the MIT license. Used files are:

- ```include/json/*```
- ```src/jsoncpp.cpp```