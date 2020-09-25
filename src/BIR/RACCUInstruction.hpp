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

#ifndef __RACCUInstruction_h__
#define __RACCUInstruction_h__

#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"
#include "RACCUMode.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class Instruction;
class RACCUInstruction;
namespace BIREnumerations
{
// enum RACCUMode;
}
} // namespace BIR

namespace BIR
{
class RACCUInstruction : public BIR::Instruction
{
public:
	RACCUInstruction();
	RACCUInstruction(Instruction *instr_);
	BIR::BIREnumerations::RACCUMode raccuMode;
	BIR::ValueWithStaticFlag operand1;
	BIR::ValueWithStaticFlag operand2;
	int resultAddress;
	BIR::Instruction *dependentTo;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
