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

#ifndef __ComponentInfo_h__
#define __ComponentInfo_h__

#include <string>
#include "ComponentType.hpp"
#include "../VIR/Coordinate.hpp"

using namespace std;

namespace BIR
{
class ComponentInfo;
namespace BIREnumerations
{
// enum ComponentType;
}
} // namespace BIR
namespace VIR
{
class Coordinate;
}

namespace BIR
{
class ComponentInfo
{
public:
	BIR::BIREnumerations::ComponentType type;
	int portNo;
	VIR::Coordinate cellCoordinate;
	int statementNo;

public:
	ComponentInfo(const BIR::BIREnumerations::ComponentType type_, const int portNo_, const VIR::Coordinate &cellCoordinate_, int statementNo_);
	ComponentInfo();
	string to_string();
};
} // namespace BIR

#endif
