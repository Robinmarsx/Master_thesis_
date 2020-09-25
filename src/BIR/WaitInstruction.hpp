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

#ifndef __WaitInstruction_h__
#define __WaitInstruction_h__

#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class Instruction;
class WaitInstruction;
} // namespace BIR

namespace BIR
{
class WaitInstruction : public BIR::Instruction
{
public:
	WaitInstruction();
	WaitInstruction(Instruction *instr_);
	BIR::ValueWithStaticFlag numberOfCycles;
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();
	bool dont_touch;

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
