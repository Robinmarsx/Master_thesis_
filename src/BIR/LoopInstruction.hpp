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

#include <vector>
using namespace std;

#ifndef __LoopInstruction_h__
#define __LoopInstruction_h__

// #include "LoopTailInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class LoopInstruction;
} // namespace BIR

namespace BIR
{
class LoopInstruction : public BIR::Instruction
{
public:
	LoopInstruction();
	LoopInstruction(BIR::Instruction *instr_);
	int loopId;
	int startValue;
	bool isStatic;
	int iterationNumber;
	BIR::LoopInstruction *correspondingLoopTailInst;
	BIR::LoopInstruction *upperLoop;
	vector<BIR::LoopInstruction *> innerLoops;
	int loopExecution;
	BIR::Instruction *end_instr;
	BIR::Instruction *begin_instr;
	int begin_pc;
	int end_pc;
	int step;
	int extend;
	int stepValue;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
