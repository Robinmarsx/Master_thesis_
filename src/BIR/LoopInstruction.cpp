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

#include "LoopInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{
LoopInstruction::LoopInstruction() : Instruction()
{
	correspondingLoopTailInst = nullptr;
	upperLoop = nullptr;
	end_instr = nullptr;
	begin_instr = nullptr;
	begin_pc = 0;
	end_pc = 0;
	extend = 0;
	step = 0;
}
LoopInstruction::LoopInstruction(BIR::Instruction *instr_) : Instruction(instr_)
{
	CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktLoopInstruction);
	LoopInstruction *ii = static_cast<LoopInstruction *>(instr_);
	loopId = ii->loopId;
	startValue = ii->startValue;
	isStatic = ii->isStatic;
	iterationNumber = ii->iterationNumber;
	correspondingLoopTailInst = ii->correspondingLoopTailInst;
	upperLoop = ii->upperLoop;
	innerLoops = ii->innerLoops;
	loopExecution = ii->loopExecution;
	end_instr = ii->end_instr;
	begin_instr = ii->begin_instr;
	begin_pc = ii->begin_pc;
	end_pc = ii->end_pc;
	extend = ii->extend;
	step = ii->step;
}

pt::ptree LoopInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("loopId", loopId);
	p.put("startValue", startValue);
	p.put("isStatic", isStatic);

	p.put("iterationNumber", iterationNumber);

	if (correspondingLoopTailInst)
		p.put("correspondingLoopTailInst", correspondingLoopTailInst->id());

	if (upperLoop)
		p.put("upperLoop", upperLoop->id());

	vector<BIR::LoopInstruction *>::iterator innerLoopIt;
	pt::ptree innerLoopTree;
	for (innerLoopIt = innerLoops.begin(); innerLoopIt != innerLoops.end(); innerLoopIt++)
	{
		pt::ptree pi;
		pi.put("Id", (*innerLoopIt)->id());
		innerLoopTree.add_child("innerLoop", pi);
	}
	p.add_child("innerLoops", innerLoopTree);

	p.put("loopExecution", loopExecution);

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

void LoopInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	loopId = p.get<int>("loopId");
	startValue = p.get<int>("startValue");
	isStatic = p.get<bool>("isStatic");
	iterationNumber = p.get<int>("iterationNumber");

	opt_child = p.get_child_optional("upperLoop");
	if (opt_child)
	{
		upperLoop = (BIR::LoopInstruction *)p.get<int>("upperLoop");
	}
	else
	{
		upperLoop = NULL;
	}

	for (pt::ptree::value_type &v : p.get_child("innerLoops"))
	{
		if (v.first == "innerLoop")
		{
			innerLoops.push_back((BIR::LoopInstruction *)v.second.get<int>("Id"));
		}
	}

	loopExecution = p.get<int>("loopExecution");

	string arr[3] = {""};
	for (pt::ptree::value_type &v : p.get_child("labels"))
	{
		if (v.first == "label")
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

void LoopInstruction::load2(map<int, BIR::Instruction *> instr_list)
{

	if (upperLoop)
	{
		index = reinterpret_cast<intptr_t>(upperLoop);
		upperLoop = (LoopInstruction *)instr_list[index];
	}

	int i = 0;
	vector<BIR::LoopInstruction *>::iterator it;
	for (it = innerLoops.begin(); it != innerLoops.end(); it++, i++)
	{
		index = reinterpret_cast<intptr_t>(*it);
		if (index)
		{
			innerLoops[i] = (BIR::LoopInstruction *)(instr_list[index]);
		}
		else
		{
			innerLoops[i] = NULL;
		}
	}
}

string LoopInstruction::to_bin()
{
	string instr = "1000";
	instr += std::bitset<4>(loopId).to_string();
	instr += std::bitset<6>(startValue).to_string();
	instr += std::bitset<1>(isStatic ? 0 : 1).to_string();
	instr += std::bitset<6>(iterationNumber).to_string();
	instr += std::bitset<27 - 4 - 4 - 6 - 1 - 6 - 6>(0).to_string();
	return instr;
}

string LoopInstruction::to_str()
{
	string instr = "LOOPH";
	instr += " " + to_string(loopId);
	instr += " " + to_string(startValue);
	instr += " " + to_string(isStatic ? 0 : 1);
	instr += " " + to_string(iterationNumber);
	return instr;
}

} // namespace BIR
