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

#ifndef __JumpInstruction_h__
#define __JumpInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class JumpInstruction;
} // namespace BIR

namespace BIR
{

class JumpInstruction : public Instruction
{
public:
	JumpInstruction();
	JumpInstruction(BIR::Instruction *instr_);
	Instruction *jumpAddressInstruction;
	int jump_pc;

public:
	void load(pt::ptree p_);
	pt::ptree dump();
	void load2(map<int, BIR::Instruction *> instr_list);
	string to_bin();
	string to_str();
};

} // namespace BIR

#endif
