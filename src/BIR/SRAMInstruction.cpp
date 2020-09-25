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

#include "SRAMInstruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "RefiInstruction.hpp"
#include "RouteInstruction.hpp"
#include "MemoryInstruction.hpp"

namespace BIR
{
SRAMInstruction::SRAMInstruction() : MemoryInstruction()
{
	correspondingRefiInst = nullptr;
	correspondingRouteInst = nullptr;
}
SRAMInstruction::SRAMInstruction(Instruction *instr_) : MemoryInstruction(instr_)
{
	CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktSRAMInstruction);
	SRAMInstruction *ii = static_cast<SRAMInstruction *>(instr_);
	initialAddress = ii->initialAddress;
	initialDelay = ii->initialDelay;
	loop1Iterations = ii->loop1Iterations;
	loop1Increment = ii->loop1Increment;
	loop1Delay = ii->loop1Delay;
	loop2Iterations = ii->loop2Iterations;
	loop2Delay = ii->loop2Delay;
	loop2Increment = ii->loop2Increment;
	isRead = ii->isRead;
	executionCycle = ii->executionCycle;
	hopNumber = ii->hopNumber;
	correspondingRefiInst = ii->correspondingRefiInst;
	correspondingRouteInst = ii->correspondingRouteInst;
}

pt::ptree SRAMInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("initialAddressValue", initialAddress.value);
	p.put("initialAddressFlag", initialAddress.isStatic);

	p.put("initialDelayValue", initialDelay.value);
	p.put("initialDelayFlag", initialDelay.isStatic);

	p.put("loop1IterationsValue", loop1Iterations.value);
	p.put("loop1IterationsFlag", loop1Iterations.isStatic);

	p.put("loop1Increment", loop1Increment);

	p.put("loop1DelayValue", loop1Delay.value);
	p.put("loop1DelayFlag", loop1Delay.isStatic);

	p.put("loop2IterationsValue", loop2Iterations.value);
	p.put("loop2IterationsFlag", loop2Iterations.isStatic);

	p.put("loop2DelaysValue", loop2Delay.value);
	p.put("loop2DelayFlag", loop2Delay.isStatic);

	p.put("loop2Increment", loop2Increment);
	p.put("isRead", isRead);

	p.put("executionCycle", executionCycle);
	p.put("hopNumber", hopNumber);

	//instruction id of the node pointed by dependentTo ptr
	if (correspondingRefiInst != NULL)
		p.put("correspondingRefiInst", correspondingRefiInst->id());

	//instruction id of the node pointed by dependentTo ptr
	if (correspondingRouteInst != NULL)
		p.put("correspondingRouteInst", correspondingRouteInst->id());

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

void SRAMInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	initialAddress(p.get<int>("initialAddressValue"), p.get<bool>("initialAddressFlag"));
	initialDelay(p.get<int>("initialDelayValue"), p.get<bool>("initialDelayFlag"));
	loop1Iterations(p.get<int>("loop1IterationsValue"), p.get<bool>("loop1IterationsFlag"));

	loop1Increment = p.get<int>("loop1Increment");

	loop1Delay(p.get<int>("loop1DelayValue"), p.get<bool>("loop1DelayFlag"));
	loop2Iterations(p.get<int>("loop2IterationsValue"), p.get<bool>("loop2IterationsFlag"));
	loop2Delay(p.get<int>("loop2DelaysValue"), p.get<bool>("loop2DelayFlag"));

	loop2Increment = p.get<int>("loop2Increment");
	isRead = p.get<bool>("isRead");

	executionCycle = p.get<int>("executionCycle");
	hopNumber = p.get<int>("hopNumber");

	//instruction id of the node pointed by dependentTo ptr
	opt_child = p.get_child_optional("correspondingRefiInst");
	if (opt_child)
		correspondingRefiInst = (BIR::RefiInstruction *)p.get<int>("correspondingRefiInst");
	else
		correspondingRefiInst = NULL;

	//instruction id of the node pointed by dependentTo ptr
	opt_child = p.get_child_optional("correspondingRouteInst");
	if (opt_child)
		correspondingRouteInst = (BIR::RouteInstruction *)p.get<int>("correspondingRouteInst");
	else
		correspondingRouteInst = NULL;

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
			timelabels[i] = arr[i];
		}
		else
		{
			break;
		}
	}
}

void SRAMInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (correspondingRefiInst != NULL)
	{
		intptr_t index1 = reinterpret_cast<intptr_t>(correspondingRefiInst);
		correspondingRefiInst = (BIR::RefiInstruction *)instr_list[index1];
	}

	if (correspondingRouteInst != NULL)
	{
		intptr_t index2 = reinterpret_cast<intptr_t>(correspondingRouteInst);
		correspondingRouteInst = (BIR::RouteInstruction *)instr_list[index2];
	}
}

string SRAMInstruction::to_bin()
{
	__NOT_IMPLEMENTED__;
}
string SRAMInstruction::to_str()
{
	__NOT_IMPLEMENTED__;
}

} // namespace BIR
