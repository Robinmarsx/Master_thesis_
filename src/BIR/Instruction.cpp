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
using namespace std;

#include "Instruction.hpp"
#include "BIRBase.hpp"

BIR::Instruction::Instruction()
{
	minScheduledClkCycle = 0;
	maxScheduledClkCycle = 0;
	isVector = false;
	twinStatementNo = -1;
	isInResSharingRegion = false;
	timelabels.resize(TOTAL_TIME);
	timestamps.resize(TOTAL_TIME);
	active_shadow_register = true;
}

BIR::Instruction::Instruction(Instruction *instr_)
{
	Instruction *ii = instr_;
	index = ii->index;
	isInResSharingRegion = ii->isInResSharingRegion;
	statementNo = ii->statementNo;
	twinStatementNo = ii->statementNo;
	unrolledStatementNo = ii->unrolledStatementNo;
	minScheduledClkCycle = ii->minScheduledClkCycle;
	maxScheduledClkCycle = ii->maxScheduledClkCycle;
	offset = ii->offset;
	isVector = ii->isVector;
	exec_trace = ii->exec_trace;

	timelabels = ii->timelabels;
	timestamps = ii->timestamps;

	kind(instr_->kind());

	active_shadow_register = ii->active_shadow_register;
}

BIR::Instruction::~Instruction()
{
	//	throw "Not yet implemented";
}