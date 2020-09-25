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
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <bitset>

namespace pt = boost::property_tree;
using namespace std;

#ifndef __Instruction_h__
#define __Instruction_h__

#include "BIRBase.hpp"

namespace BIR
{
// class BIRBase;
class Instruction;
} // namespace BIR

namespace BIR
{
class Instruction : public BIR::BIRBase
{
public:
	enum
	{
		FETCH_TIME,
		ISSUE_TIME,
		ARRIVE_TIME,
		ACTIVE_TIME,
		END_TIME,
		TOTAL_TIME
	};

public:
	int index;
	bool isInResSharingRegion;
	int statementNo;
	int twinStatementNo;
	string unrolledStatementNo;
	int minScheduledClkCycle;
	int maxScheduledClkCycle;
	int offset;
	bool isVector;
	vector<int> exec_trace;
	bool active_shadow_register;

	vector<string> timelabels;
	vector<int> timestamps;

public:
	Instruction();
	Instruction(Instruction *instr_);

public:
	virtual ~Instruction() = 0;

public:
	virtual void load(pt::ptree p_) = 0;
	virtual pt::ptree dump() = 0;
	virtual void load2(map<int, BIR::Instruction *> instr_list) = 0;
	virtual string to_bin() = 0;
	virtual string to_str() = 0;
};
} // namespace BIR

#endif
