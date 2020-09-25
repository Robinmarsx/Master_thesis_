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

#include "InstructionList.hpp"
#include "Instruction.hpp"
#include "BIRBase.hpp"

void BIR::InstructionList::addInstruction(BIR::Instruction * instruction_, bool setInstructionIndex_)
{
	if (setInstructionIndex_)
		instruction_->index = _elements.size();
	_elements.push_back(instruction_);
}

BIR::Instruction * BIR::InstructionList::instruction(int index_) const
{
	return _elements[index_];
}

int BIR::InstructionList::size() const
{
	return _elements.size();
}

void BIR::InstructionList::insert(int index_, BIR::Instruction * instruction_)
{
	_elements.insert(_elements.begin() + index_, instruction_);

	// Set the index of the inserted instruction
	instruction_->index = index_;

	// Update the index of the instructions following the inserted instruction.
	for (unsigned idx = index_+ 1; idx < _elements.size(); ++idx)
		_elements[idx]->index++;
}

BIR::Instruction * BIR::InstructionList::back() const
{
	return _elements.back();
}

void BIR::InstructionList::clear()
{
	return _elements.clear();
}

void BIR::InstructionList::push_back(Instruction* i_)
{
	return _elements.push_back(i_);
}

