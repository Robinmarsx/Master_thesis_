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
#include "ComponentInfo.hpp"
#include "ComponentType.hpp"
#include "../VIR/Coordinate.hpp"

BIR::ComponentInfo::ComponentInfo(const BIR::BIREnumerations::ComponentType type_, const int portNo_, const VIR::Coordinate &cellCoordinate_, int statementNo_)
{
	type = type_;
	portNo = portNo_;
	cellCoordinate = cellCoordinate_;
	statementNo = statementNo_;
}

BIR::ComponentInfo::ComponentInfo()
{
}

string BIR::ComponentInfo::to_string()
{
	string s = "";
	s += std::to_string(cellCoordinate.row) + "_" + std::to_string(cellCoordinate.column);
	s += "_";
	if (type == BIR::BIREnumerations::ctDPU)
	{
		s += "DPU";
	}
	else if (type == BIR::BIREnumerations::ctRegFile)
	{
		s += "REG";
	}
	else
	{
		s += "MEM";
	}
	s += "_" + std::to_string(portNo);
	return s;
}
