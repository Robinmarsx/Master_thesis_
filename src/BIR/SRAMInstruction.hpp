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

#ifndef __SRAMInstruction_h__
#define __SRAMInstruction_h__

#include "ValueWithStaticFlag.hpp"
// #include "RefiInstruction.hpp"
// #include "RouteInstruction.hpp"
#include "MemoryInstruction.hpp"
#include "../VIR/Coordinate.hpp"

namespace BIR
{
class ValueWithStaticFlag;
class RefiInstruction;
class RouteInstruction;
// class MemoryInstruction;
class SRAMInstruction;
} // namespace BIR

namespace BIR
{
class SRAMInstruction : public BIR::MemoryInstruction
{
public:
	SRAMInstruction();
	SRAMInstruction(Instruction *instr_);
	BIR::ValueWithStaticFlag initialAddress;
	BIR::ValueWithStaticFlag initialDelay;
	BIR::ValueWithStaticFlag loop1Iterations;
	int loop1Increment;
	BIR::ValueWithStaticFlag loop1Delay;
	BIR::ValueWithStaticFlag loop2Iterations;
	BIR::ValueWithStaticFlag loop2Delay;
	int loop2Increment;
	bool isRead;
	int executionCycle;
	int hopNumber;
	BIR::RefiInstruction *correspondingRefiInst;
	BIR::RouteInstruction *correspondingRouteInst;
	VIR::Coordinate SRAMCoordinate;

	BIR::Instruction *corresponding_looph_l1;
	BIR::Instruction *corresponding_loopt_l1;
	BIR::Instruction *corresponding_looph_l2;
	BIR::Instruction *corresponding_loopt_l2;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
