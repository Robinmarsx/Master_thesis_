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

#include "RouteInstruction.hpp"
#include "MemoryInstruction.hpp"
#include "../VIR/Coordinate.hpp"

namespace BIR
{
RouteInstruction::RouteInstruction(Instruction *instr_) : MemoryInstruction(instr_)
{
	CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktRouteInstruction);
	RouteInstruction *ii = static_cast<RouteInstruction *>(instr_);
	drraSelect = ii->drraSelect;
	isFromSource = ii->isFromSource;
	sourceCoordinate = ii->sourceCoordinate;
	destCoordinate = ii->destCoordinate;
}

pt::ptree RouteInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("drraSelect", drraSelect);
	p.put("isFromSource", isFromSource);

	p.put("srcRow", sourceCoordinate.row);
	p.put("srcCol", sourceCoordinate.column);
	p.put("srcBank", sourceCoordinate.bank);

	p.put("destRow", destCoordinate.row);
	p.put("destCol", destCoordinate.column);
	p.put("destBank", destCoordinate.bank);

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

void RouteInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	drraSelect = p.get<int>("drraSelect");
	isFromSource = p.get<bool>("isFromSource");
	sourceCoordinate.row = p.get<int>("srcRow");
	sourceCoordinate.column = p.get<int>("srcCol");
	sourceCoordinate.bank = p.get<int>("srcBank");
	destCoordinate.row = p.get<int>("destRow");
	destCoordinate.column = p.get<int>("destCol");
	destCoordinate.bank = p.get<int>("destBank");

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

string RouteInstruction::to_bin()
{
	__NOT_IMPLEMENTED__;
}
string RouteInstruction::to_str()
{
	__NOT_IMPLEMENTED__;
}

} // namespace BIR
