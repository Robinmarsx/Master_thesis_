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

#ifndef __RouteInstruction_h__
#define __RouteInstruction_h__

#include "MemoryInstruction.hpp"
#include "../VIR/Coordinate.hpp"

namespace BIR
{
// class MemoryInstruction;
class RouteInstruction;
} // namespace BIR
namespace VIR
{
class Coordinate;
}

namespace BIR
{
class RouteInstruction : public BIR::MemoryInstruction
{
public:
	RouteInstruction() {}
	RouteInstruction(Instruction *instr_);
	int drraSelect;
	bool isFromSource;
	VIR::Coordinate sourceCoordinate;
	VIR::Coordinate destCoordinate;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();
	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
