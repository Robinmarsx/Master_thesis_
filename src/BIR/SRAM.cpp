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

#include "SRAM.hpp"
#include "MemElement.hpp"
#include "BIRBase.hpp"

BIR::SRAM::SRAM(int depth_, int width_)
{
	_depth = depth_;
	_width = width_;
	_hasInitialLoad = false;
	
	_memory = new BIR::MemElement * [_depth];
	for (int index = 0; index < _depth; ++index)
		_memory[index] = new BIR::MemElement(_width);
}

BIR::SRAM::~SRAM()
{
	for (int index = 0; index < _depth; ++index)
		delete _memory[index];
	delete []_memory;
}

BIR::MemElement * BIR::SRAM::memory(int index_)
{
	return _memory[index_];
}

int BIR::SRAM::depth()
{
	return _depth;
}

bool BIR::SRAM::hasInitialLoad() const
{
	return _hasInitialLoad;
}

void BIR::SRAM::hasInitialLoad(bool hasInitialLoad_)
{
	_hasInitialLoad = hasInitialLoad_;
}

