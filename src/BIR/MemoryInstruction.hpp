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

#ifndef __MemoryInstruction_h__
#define __MemoryInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class MemoryInstruction;
} // namespace BIR

namespace BIR
{
class MemoryInstruction : public BIR::Instruction
{

public:
	MemoryInstruction();
	MemoryInstruction(Instruction *instr_);
	string variableName;

public:
	void load(pt::ptree p_) {}
	pt::ptree dump() {}
	void load2(map<int, BIR::Instruction *> instr_list) {}

	virtual string to_bin() = 0;
	virtual string to_str() = 0;
};
} // namespace BIR

#endif
