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

#include "Refi3Instruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"

namespace BIR
{
Refi3Instruction::Refi3Instruction() : RegFileInstruction()
{
  middleDelayExt = 0;
  numberOfRepetitionExt = 0;
  repetitionDelay.isStatic = true;
  repetitionDelay.value = 0;
  repetitionOffsetExt = 0;
  reverse_bits.isStatic = true;
  reverse_bits.value = 0;
}
Refi3Instruction::Refi3Instruction(BIR::Instruction *instr_) : RegFileInstruction(instr_)
{
  CHECK_EQ(instr_->kind(), BIR::BIREnumerations::bktRefi3Instruction);
  Refi3Instruction *ii = static_cast<Refi3Instruction *>(instr_);
  middleDelayExt = ii->middleDelayExt;
  numberOfRepetitionExt = ii->numberOfRepetitionExt;
  repetitionDelay = ii->repetitionDelay;
  repetitionOffsetExt = ii->repetitionOffsetExt;
  reverse_bits = ii->reverse_bits;
}
string Refi3Instruction::to_bin()
{
  __NOT_IMPLEMENTED__;
}

string Refi3Instruction::to_str()
{
  __NOT_IMPLEMENTED__;
}

} // namespace BIR