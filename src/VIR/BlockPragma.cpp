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

#include "BlockPragma.hpp"
#include "Pragma.hpp"
#include "BlockPragmaType.hpp"

bool VIR::BlockPragma::isBlockBegin() const
{
	return _isBlockBegin;
}

void VIR::BlockPragma::isBlockBegin(bool isBlockBegin_)
{
	_isBlockBegin = isBlockBegin_;
}

VIR::VirEnumerations::BlockPragmaType VIR::BlockPragma::blockProgramType() const
{
	return _blockProgramType;
}

void VIR::BlockPragma::blockProgramType(
		VIR::VirEnumerations::BlockPragmaType blockProgramType_)
{
	_blockProgramType = blockProgramType_;
}
