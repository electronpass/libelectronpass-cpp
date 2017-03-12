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

#ifndef ELECTRONPASS_DATA_HPP
#define ELECTRONPASS_DATA_HPP

#include <json/value.h>
#include <json/reader.h>
#include <iostream>

namespace electronpass {
    namespace serialization {
        void deserialize(const char* const);
        void serialize();
    }
}



#endif //ELECTRONPASS_DATA_HPP
