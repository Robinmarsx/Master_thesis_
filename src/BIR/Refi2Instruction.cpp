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

#include "Refi2Instruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"

namespace BIR
{
Refi2Instruction::Refi2Instruction() : RegFileInstruction()
{
  middleDelay.isStatic = true;
  middleDelay.value = 0;
  numberOfRepetition.isStatic = true;
  numberOfRepetition.value = 0;
  repetitionOffset = 0;
  stepValue.isStatic = true;
  stepValue.value = 1;
}
Refi2Instruction::Refi2Instruction(BIR::Instruction *instr_) : RegFileInstruction(instr_)
{
  CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktRefi2Instruction);
  Refi2Instruction *ii = static_cast<Refi2Instruction *>(instr_);
  middleDelay = ii->middleDelay;
  numberOfRepetition = ii->numberOfRepetition;
  repetitionOffset = ii->repetitionOffset;
  stepValue = ii->stepValue;
}
string Refi2Instruction::to_bin()
{
  __NOT_IMPLEMENTED__;
}

string Refi2Instruction::to_str()
{
  __NOT_IMPLEMENTED__;
}

} // namespace BIR