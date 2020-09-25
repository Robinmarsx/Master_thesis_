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

#include "Refi1Instruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"

namespace BIR
{
Refi1Instruction::Refi1Instruction() : RegFileInstruction()
{
  initialDelay.isStatic = true;
  initialDelay.value = 0;
  numberOfAddress.isStatic = true;
  numberOfAddress.value = 0;
  portNo = 0;
  startAddress.isStatic = true;
  startAddress.value = 0;
  numberOfSubseqInst = 0;
}
Refi1Instruction::Refi1Instruction(BIR::Instruction *instr_) : RegFileInstruction(instr_)
{
  CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktRefi1Instruction);
  Refi1Instruction *ii = static_cast<Refi1Instruction *>(instr_);
  initialDelay = ii->initialDelay;
  numberOfAddress = ii->numberOfAddress;
  portNo = ii->portNo;
  startAddress = ii->startAddress;
  numberOfSubseqInst = ii->numberOfSubseqInst;
}

string Refi1Instruction::to_bin()
{
  __NOT_IMPLEMENTED__;
}

string Refi1Instruction::to_str()
{
  __NOT_IMPLEMENTED__;
}

} // namespace BIR