/*
This file is part of libelectronpass.

Libelectronpass is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libelectronpass is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libelectronpass.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "passgenerator.hpp"
#include <random>
#include <functional>

int trueRandomInt(int min, int max){
    std::mt19937 prng;
    std::mt19937::result_type seed = std::random_device{}();
    prng.seed(seed);
    auto randGen = std::bind(std::uniform_int_distribution<int>(min, max),
                               std::mt19937(seed));
    return randGen();
}

std::string electronpass::passgenerator::generate_pass(int len, bool digits, bool symbols, bool uppercase) {
    return "random " + std::to_string(trueRandomInt(0, 99));
}