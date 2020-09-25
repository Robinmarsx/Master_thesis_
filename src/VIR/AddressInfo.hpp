// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

#include <exception>
using namespace std;

#ifndef __AddressInfo_h__
#define __AddressInfo_h__

#include "util/Common.hpp"
#include "Identifier.hpp"

// #include "ForStatement.hpp"

namespace VIR
{
class ForStatement;
class AddressInfo;
} // namespace VIR

namespace VIR
{
class AddressInfo
{
public:
	int startAddress;
	int increment;
	int numberOfAddress;
	int numberOfRepetitions;
	int repetitionOffset;
	bool is1stLevelDynamic;
	bool is2ndLevelDynamic;
	VIR::ForStatement *firstLevelLoop;
	VIR::ForStatement *secondLevelLoop;

public:
	AddressInfo();
};
} // namespace VIR

#endif
