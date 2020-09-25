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

#include "RACCUInstruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"
#include "RACCUMode.hpp"

namespace BIR
{
RACCUInstruction::RACCUInstruction() : Instruction()
{
	dependentTo = nullptr;
}

RACCUInstruction::RACCUInstruction(BIR::Instruction *instr_) : Instruction(instr_)
{
	CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktRACCUInstruction);
	RACCUInstruction *ii = static_cast<RACCUInstruction *>(instr_);
	raccuMode = ii->raccuMode;
	operand1 = ii->operand1;
	operand2 = ii->operand2;
	resultAddress = ii->resultAddress;
	dependentTo = ii->dependentTo;
}

pt::ptree RACCUInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("raccuMode", raccuMode);

	p.put("operand1Value", operand1.value);
	p.put("operand1Flag", operand1.isStatic);

	p.put("operand2Value", operand2.value);
	p.put("operand2Flag", operand2.isStatic);

	p.put("resultAddress", resultAddress);
	if (dependentTo)
	{
		p.put("dependentTo", dependentTo->id());
	}

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

void RACCUInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	raccuMode = (BIREnumerations::RACCUMode)p.get<int>("raccuMode");
	operand1(p.get<int>("operand1Value"), p.get<bool>("operand1Flag"));
	operand2(p.get<int>("operand2Value"), p.get<bool>("operand2Flag"));
	resultAddress = p.get<int>("resultAddress");

	opt_child = p.get_child_optional("dependentTo");
	if (opt_child)
	{
		dependentTo = (BIR::Instruction *)p.get<int>("dependentTo");
	}
	else
	{
		dependentTo = NULL;
	}

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
void RACCUInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (dependentTo)
	{
		intptr_t index = reinterpret_cast<intptr_t>(dependentTo);
		dependentTo = (BIR::Instruction *)instr_list[index];
	}
}

string RACCUInstruction::to_bin()
{
	int raccuMode;

	// Obtained from the FABRIC implementation
	switch (raccuMode)
	{
	case BIR::BIREnumerations::rmAdd:
		raccuMode = 3;
		break;
	case BIR::BIREnumerations::rmAddWithLoopIndex:
		raccuMode = 7;
		break;
	case BIR::BIREnumerations::rmShiftLeft:
		raccuMode = 6;
		break;
	case BIR::BIREnumerations::rmLoopHeader:
		raccuMode = 1;
		break;
	case BIR::BIREnumerations::rmLoopTail:
		raccuMode = 2;
		break;
	case BIR::BIREnumerations::rmShiftRight:
		raccuMode = 5;
		break;
	case BIR::BIREnumerations::rmSub:
		raccuMode = 4;
		break;
	default:
		raccuMode = 0;
		break;
	}
	string instr = "1010";
	instr += std::bitset<3>(raccuMode).to_string();
	instr += std::bitset<1>((int)!operand1.isStatic).to_string();
	instr += std::bitset<7>(operand1.value).to_string();
	instr += std::bitset<1>((int)!operand2.isStatic).to_string();
	instr += std::bitset<7>(operand2.value).to_string();
	instr += std::bitset<4>(resultAddress).to_string();
	return instr;
}

string RACCUInstruction::to_str()
{
	int raccuMode;

	// Obtained from the FABRIC implementation
	switch (raccuMode)
	{
	case BIR::BIREnumerations::rmAdd:
		raccuMode = 3;
		break;
	case BIR::BIREnumerations::rmAddWithLoopIndex:
		raccuMode = 7;
		break;
	case BIR::BIREnumerations::rmShiftLeft:
		raccuMode = 6;
		break;
	case BIR::BIREnumerations::rmLoopHeader:
		raccuMode = 1;
		break;
	case BIR::BIREnumerations::rmLoopTail:
		raccuMode = 2;
		break;
	case BIR::BIREnumerations::rmShiftRight:
		raccuMode = 5;
		break;
	case BIR::BIREnumerations::rmSub:
		raccuMode = 4;
		break;
	default:
		raccuMode = 0;
		break;
	}
	string instr = "RACCU";
	instr += " " + to_string(raccuMode);
	instr += " " + to_string((int)!operand1.isStatic);
	instr += " " + to_string(operand1.value);
	instr += " " + to_string((int)!operand2.isStatic);
	instr += " " + to_string(operand2.value);
	instr += " " + to_string(resultAddress);
	return instr;
}

} // namespace BIR
