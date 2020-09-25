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

#include "DPUInstruction.hpp"
#include "RefiInstruction.hpp"
#include "SWBInstruction.hpp"
#include "Instruction.hpp"
#include "DPUMode.hpp"
#include "DpuIOChange.hpp"

namespace BIR
{

pt::ptree DPUInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("mode", mode);
	p.put("modeValue", modeValue);
	p.put("executionCycle", executionCycle);
	p.put("repetition", repetition);

	vector<BIR::DPUInstruction *>::iterator it1;
	pt::ptree dpuTree;
	for (it1 = correspondingChainedDpus.begin(); it1 != correspondingChainedDpus.end(); it1++)
	{
		pt::ptree pi;
		pi.put("Id", (*it1)->id());
		dpuTree.add_child("chainedDpu", pi);
	}
	p.add_child("correspondingChainedDpus", dpuTree);

	vector<BIR::RefiInstruction *>::iterator it2;
	pt::ptree refiTree;
	for (it2 = correspondingRefiInsts.begin(); it2 != correspondingRefiInsts.end(); it2++)
	{
		pt::ptree pi;
		pi.put("Id", (*it2)->id());
		refiTree.add_child("chainedRefi", pi);
	}
	p.add_child("correspondingRefiInsts", refiTree);

	vector<BIR::SWBInstruction *>::iterator it3;
	pt::ptree swbTree;
	for (it3 = correspondingSWBInsts.begin(); it3 != correspondingSWBInsts.end(); it3++)
	{
		pt::ptree pi;
		pi.put("Id", (*it3)->id());
		swbTree.add_child("chainedSwb", pi);
	}
	p.add_child("correspondingSWBInsts", swbTree);

	p.put("ioChange", ioChange);
	p.put("constantValue", constantValue);

	p.put("saturation", saturation);
	p.put("fixedPointMode", fixedPointMode);
	p.put("parameter_type", parameter_type);

	vector<string>::iterator it;
	int i = 0;
	for (it = timelabels.begin(); it != timelabels.end(); it++, i++)
	{
		pt::ptree pi;
		pi.put("order", i);
		pi.put("tag", *it);
		pd.add_child("timelabel", pi);
	}
	p.add_child("timelabels", pd);

	return p;
}

void DPUInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	mode = p.get<string>("mode");
	modeValue = p.get<int>("modeValue");
	executionCycle = p.get<int>("executionCycle");
	repetition = p.get<int>("repetition");

	for (pt::ptree::value_type &v : p.get_child("correspondingChainedDpus"))
	{
		if (v.first == "chainedDpu")
		{
			correspondingChainedDpus.push_back((BIR::DPUInstruction *)v.second.get<int>("Id"));
		}
	}

	for (pt::ptree::value_type &v : p.get_child("correspondingRefiInsts"))
	{
		if (v.first == "chainedRefi")
		{
			correspondingRefiInsts.push_back((BIR::RefiInstruction *)v.second.get<int>("Id"));
		}
	}

	for (pt::ptree::value_type &v : p.get_child("correspondingSWBInsts"))
	{
		if (v.first == "chainedSwb")
		{
			correspondingSWBInsts.push_back((BIR::SWBInstruction *)v.second.get<int>("Id"));
		}
	}

	ioChange = (BIR::BIREnumerations::DpuIOChange)p.get<int>("ioChange");
	constantValue = p.get<int>("constantValue");
	saturation = p.get<bool>("saturation");
	fixedPointMode = p.get<bool>("fixedPointMode");
	parameter_type = (BIR::BIREnumerations::DpuParameterType)p.get<int>("parameter_type");

	string arr[3] = {""};
	for (pt::ptree::value_type &v : p.get_child("timelabels"))
	{
		if (v.first == "timelabel")
		{
			int order = v.second.get<int>("order");
			string tag = v.second.get<string>("tag");
			arr[order] = tag;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (arr[i] != "")
		{
			timelabels.push_back(arr[i]);
		}
		else
		{
			break;
		}
	}
}

void DPUInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	intptr_t index;
	int i = 0;

	vector<BIR::DPUInstruction *>::iterator it;
	for (it = correspondingChainedDpus.begin(); it != correspondingChainedDpus.end(); it++, i++)
	{
		index = reinterpret_cast<intptr_t>(*it);
		correspondingChainedDpus[i] = (BIR::DPUInstruction *)(instr_list[index]);
	}

	i = 0;
	vector<BIR::RefiInstruction *>::iterator it1;
	for (it1 = correspondingRefiInsts.begin(); it1 != correspondingRefiInsts.end(); it1++, i++)
	{
		index = reinterpret_cast<intptr_t>(*it1);
		correspondingRefiInsts[i] = (BIR::RefiInstruction *)(instr_list[index]);
	}

	i = 0;
	vector<BIR::SWBInstruction *>::iterator it2;
	for (it2 = correspondingSWBInsts.begin(); it2 != correspondingSWBInsts.end(); it2++, i++)
	{
		index = reinterpret_cast<intptr_t>(*it2);
		correspondingSWBInsts[i] = (BIR::SWBInstruction *)(instr_list[index]);
	}
}

DPUInstruction::DPUInstruction() : Instruction()
{
}

DPUInstruction::DPUInstruction(BIR::Instruction *instr_) : Instruction(instr_)
{
	CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktDPUInstruction);
	DPUInstruction *ii = static_cast<DPUInstruction *>(instr_);
	mode = ii->mode;
	modeValue = ii->modeValue;
	executionCycle = ii->executionCycle;
	repetition = ii->repetition;
	correspondingChainedDpus = ii->correspondingChainedDpus;
	correspondingRefiInsts = ii->correspondingRefiInsts;
	correspondingSWBInsts = ii->correspondingSWBInsts;
	ioChange = ii->ioChange;
	constantValue = ii->constantValue;
	int_imm_data = ii->int_imm_data;
	float_imm_data = ii->float_imm_data;
	saturation = ii->saturation;
	fixedPointMode = ii->fixedPointMode;
	parameter_type = ii->parameter_type;
	reductive = ii->reductive;
	output_register = ii->reductive;
}

string DPUInstruction::to_bin()
{
	int dpuControl = 0;
	if (saturation)
		dpuControl |= 2;
	if (fixedPointMode)
		dpuControl |= 1;

	int dpu_acc_clear;
	if (mode == "silago_dpu_add_with_constant" || mode == "silago_dpu_load_constant" || mode == "silago_dpu_comparison_with_constant")
	{
		if (fixedPointMode)
		{
			constantValue = (int)(float_imm_data * (1 << 7));
		}
		else
		{
			constantValue = int_imm_data;
		}

		if (parameter_type == BIR::BIREnumerations::dptImmediate)
		{
			dpu_acc_clear = constantValue & 0x7f;
		}
		else
		{
			dpu_acc_clear = constantValue | 0x80;
		}
	}
	else
	{
		if (parameter_type == BIR::BIREnumerations::dptImmediate)
		{
			dpu_acc_clear = repetition & 0x7f;
		}
		else
		{
			dpu_acc_clear = repetition | 0x80;
		}
	}

	int ioChange;
	switch (ioChange)
	{
	case BIR::BIREnumerations::dicIn1Negation:
		ioChange = 1;
		break;
	case BIR::BIREnumerations::dicIn2Negation:
		ioChange = 2;
		break;
	case BIR::BIREnumerations::dicAbsoluteOfOutput:
		ioChange = 3;
		break;
	default:
		ioChange = 0;
		break;
	}

	string instr = "0100";
	instr += std::bitset<5>(modeValue).to_string();
	instr += std::bitset<2>(dpuControl).to_string();
	instr += std::bitset<2>(3).to_string();
	instr += std::bitset<2>(3).to_string();
	instr += std::bitset<1>(1).to_string();
	instr += std::bitset<1>(0).to_string();
	instr += std::bitset<8>(dpu_acc_clear).to_string();
	instr += std::bitset<2>(ioChange).to_string();
	return instr;
}

string DPUInstruction::to_str()
{
	int dpuControl = 0;
	if (saturation)
		dpuControl |= 2;
	if (fixedPointMode)
		dpuControl |= 1;

	int dpu_acc_clear;
	if (mode == "silago_dpu_add_with_constant" || mode == "silago_dpu_load_constant" || mode == "silago_dpu_comparison_with_constant")
	{
		if (fixedPointMode)
		{
			constantValue = (int)(float_imm_data * (1 << 7));
		}
		else
		{
			constantValue = int_imm_data;
		}

		if (parameter_type == BIR::BIREnumerations::dptImmediate)
		{
			dpu_acc_clear = constantValue & 0x7f;
		}
		else
		{
			dpu_acc_clear = constantValue | 0x80;
		}
	}
	else
	{
		if (parameter_type == BIR::BIREnumerations::dptImmediate)
		{
			dpu_acc_clear = repetition & 0x7f;
		}
		else
		{
			dpu_acc_clear = repetition | 0x80;
		}
	}

	int ioChange;
	switch (ioChange)
	{
	case BIR::BIREnumerations::dicIn1Negation:
		ioChange = 1;
		break;
	case BIR::BIREnumerations::dicIn2Negation:
		ioChange = 2;
		break;
	case BIR::BIREnumerations::dicAbsoluteOfOutput:
		ioChange = 3;
		break;
	default:
		ioChange = 0;
		break;
	}

	string instr = "DPU";
	instr += " " + to_string(modeValue);
	instr += " " + to_string(dpuControl);
	instr += " " + to_string(3);
	instr += " " + to_string(3);
	instr += " " + to_string(1);
	instr += " " + to_string(0);
	instr += " " + to_string(dpu_acc_clear);
	instr += " " + to_string(ioChange);
	return instr;
}

} // namespace BIR
