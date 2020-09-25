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

#ifndef __DPUInstruction_h__
#define __DPUInstruction_h__

// #include "RefiInstruction.hpp"
// #include "SWBInstruction.hpp"
#include "Instruction.hpp"
//#include "DPUMode.hpp"
#include "DpuIOChange.hpp"
#include "DpuParameterType.hpp"

namespace BIR
{
class RefiInstruction;
class SWBInstruction;
// class Instruction;
class DPUInstruction;
namespace BIREnumerations
{
// enum DPUMode;
// enum DpuIOChange;
}
} // namespace BIR

namespace BIR
{
class DPUInstruction : public BIR::Instruction
{
public:
	DPUInstruction();
	DPUInstruction(BIR::Instruction *instr_);
	string mode;
	int modeValue;
	int executionCycle;
	int repetition;
	vector<BIR::DPUInstruction *> correspondingChainedDpus;
	vector<BIR::RefiInstruction *> correspondingRefiInsts;
	vector<BIR::SWBInstruction *> correspondingSWBInsts;
	BIR::BIREnumerations::DpuIOChange ioChange;
	int constantValue;
	int int_imm_data;
	float float_imm_data;
	bool saturation;
	bool fixedPointMode;
	BIR::BIREnumerations::DpuParameterType parameter_type;
	bool reductive;
	bool output_register;

public:
	void load(pt::ptree p_);
	pt::ptree dump();
	void load2(map<int, BIR::Instruction *> instr_list);

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
