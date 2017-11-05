# libelectronpass
[![Build Status](https://travis-ci.org/electronpass/libelectronpass-cpp.svg?branch=develop)](https://travis-ci.org/electronpass/libelectronpass)

Backend for electronpass-desktop that can work with the wallet format writen in c++.

## Dependencies

- [crypto++](https://www.cryptopp.com/) - Crypto library.
- [jsoncpp v1.8.0](https://github.com/open-source-parsers/jsoncpp) - Already included in source code
- [gtest](https://github.com/google/googletest) - Required for building tests. Already included in source code
- [doxygen](http://www.stack.nl/~dimitri/doxygen/) - Required for building documentation

## Building
Before building you should download and build the Crypto++ library. Currently used version is ```5.6.5```. We link crypto++ as a static library. You should put the header files for crypto++ in ```cryptopp/cryptopp``` and the static library itself in ```cryptopp/libcryptopp.a```. For Unix/Linux systems there is a script provided ```install-cryptopp.sh```.

CMake configuration is used to create documentation and run tests.

The following will build examples and tests

    mkdir build; cd build
    cmake ..
    make -j8

## Usage
You can include libelectronpass in your project by linking with the ```libelectronpass.a``` that is outputed in the ```lib``` directory. Building the library is described in the Building section.  All the header you need to include are in ```include``` directory and you can copy them in your project. You can also build it as a dynamic library. To do so change the configuration in ```src/CMakeLists.txt``` file.

## Tests
You can run the tests with

```make check```

You can also compile and run the tests with

```
make tests
./bin/tests
```

## Documentation
Documentation is generated using doxygen:

    doxygen docs/Doxyfile


You can also use make to generate documentation with:

    make docs

## Examples
Simple usage examples are located in ```examples/``` folder. To build all examples run from ```build/``` folder:

    make examples

## License
Code in this project is licensed under [GNU LGPLv3 license](https://github.com/electronpass/libelectronpass/blob/release/LICENSE.LESSER). Some third party files are subjective to their respective license.

### JsonCpp
[JsonCpp](https://github.com/open-source-parsers/jsoncpp) is licensed under the MIT license. Used files are:

- ```include/json/*```
- ```src/jsoncpp.cpp```

## Crypto++
[Crypto++](https://github.com/weidai11/cryptopp/) is licensed under Boost software license.
