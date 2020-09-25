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
using namespace std;

#include "BIRBase.hpp"
#include "BIRKindType.hpp"

int BIR::BIRBase::id() const
{
	return _id;
}

void BIR::BIRBase::id(int id_)
{
	_id = id_;
}

void BIR::BIRBase::kind(BIR::BIREnumerations::BIRKindType kind_)
{
	_kind = kind_;
}

BIR::BIREnumerations::BIRKindType BIR::BIRBase::kind() const
{
	return _kind;
}

string BIR::BIRBase::kindStr() const
{
	string str = "unknown type";

	switch (_kind)
	{
	case BIR::BIREnumerations::bktAGU:
		str = "AGU";
		break;
	case BIR::BIREnumerations::bktBranchInstruction:
		str = "BranchInstruction";
		break;
	case BIR::BIREnumerations::bktContileCell:
		str = "ContileCell";
		break;
	case BIR::BIREnumerations::bktDiMArch:
		str = "DiMArch";
		break;
	case BIR::BIREnumerations::bktDiMArchCell:
		str = "DiMArchCell";
		break;
	case BIR::BIREnumerations::bktDPU:
		str = "DPU";
		break;
	case BIR::BIREnumerations::bktDRRACell:
		str = "DRRACell";
		break;
	case BIR::BIREnumerations::bktDRRACluster:
		str = "DRRACluster";
		break;
	case BIR::BIREnumerations::bktDPUInstruction:
		str = "DPUInstruction";
		break;
	case BIR::BIREnumerations::bktLoopInstruction:
		str = "LoopInstruction";
		break;
	case BIR::BIREnumerations::bktJumpInstruction:
		str = "JumpInstruction";
		break;
	case BIR::BIREnumerations::bktMemoryElement:
		str = "MemoryElement";
		break;
	case BIR::BIREnumerations::bktRACCU:
		str = "RACCU";
		break;
	case BIR::BIREnumerations::bktRACCUInstruction:
		str = "RACCUInstruction";
		break;
	case BIR::BIREnumerations::bktRefiInstruction:
		str = "RefiInstruction";
		break;
	case BIR::BIREnumerations::bktRefi1Instruction:
		str = "Refi1Instruction";
		break;
	case BIR::BIREnumerations::bktRefi2Instruction:
		str = "Refi2Instruction";
		break;
	case BIR::BIREnumerations::bktRefi3Instruction:
		str = "Refi3Instruction";
		break;
	case BIR::BIREnumerations::bktRegister:
		str = "Register";
		break;
	case BIR::BIREnumerations::bktRegFile:
		str = "RegFile";
		break;
	case BIR::BIREnumerations::bktRFILEInstruction:
		str = "RFILEInstruction";
		break;
	case BIR::BIREnumerations::bktRouteInstruction:
		str = "RouteInstruction";
		break;
	case BIR::BIREnumerations::bktSequencer:
		str = "Sequencer";
		break;
	case BIR::BIREnumerations::bktSRAM:
		str = "SRAM";
		break;
	case BIR::BIREnumerations::bktSRAMInstruction:
		str = "SRAMInstruction";
		break;
	case BIR::BIREnumerations::bktSWBInstruction:
		str = "SWBInstruction";
		break;
	case BIR::BIREnumerations::bktSwitchBox:
		str = "SwitchBox";
		break;
	case BIR::BIREnumerations::bktWaitInstruction:
		str = "WaitInstruction";
		break;
	default:
		break;
	}

	return str;
}

BIR::BIRBase::~BIRBase()
{
	//	throw "Not yet implemented";
}
