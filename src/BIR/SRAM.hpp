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

#ifndef __SRAM_h__
#define __SRAM_h__

// #include "MemElement.hpp"
#include "BIRBase.hpp"

namespace BIR
{
class MemElement;
// class BIRBase;
class SRAM;
} // namespace BIR

namespace BIR
{
class SRAM : public BIR::BIRBase
{
private:
	int _depth;

private:
	int _width;

private:
	BIR::MemElement **_memory;

private:
	bool _hasInitialLoad;

public:
	SRAM(int depth_, int width_);

public:
	~SRAM();

public:
	BIR::MemElement *memory(int index_);

public:
	int depth();
	int width() { return _width; }

public:
	bool hasInitialLoad() const;

public:
	void hasInitialLoad(bool hasInitialLoad_);
};
} // namespace BIR

#endif
