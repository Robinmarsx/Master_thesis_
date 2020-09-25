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
#include <vector>
using namespace std;

#ifndef __InstructionList_h__
#define __InstructionList_h__

// #include "Instruction.hpp"
#include "BIRBase.hpp"

namespace BIR
{
	class Instruction;
	// class BIRBase;
	class InstructionList;
}

namespace BIR{
class InstructionList: public BIR::BIRBase{
public:
	vector<BIR::Instruction*> _elements;
public:
	void addInstruction(BIR::Instruction * instruction_, bool setInstructionIndex_ = false);
	BIR::Instruction * instruction(int index_) const;
	int size() const;
	void insert(int index_, BIR::Instruction * instruction_);
	BIR::Instruction * back() const;
	void clear();
	void push_back(BIR::Instruction* i_);
};

}

#endif
