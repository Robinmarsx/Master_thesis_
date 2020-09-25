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

#ifndef __BIRBase_h__
#define __BIRBase_h__

#include "util/Common.hpp"
#include "BIRKindType.hpp"

namespace MemorySpace
{
class MemoryManager;
}

namespace BIR
{
class BIRBase
{
	friend class MemorySpace::MemoryManager;

private:
	int _id;

private:
	BIR::BIREnumerations::BIRKindType _kind;

public:
	int id() const;

public:
	void id(int id_);
	void kind(BIR::BIREnumerations::BIRKindType kind_);

public:
	BIR::BIREnumerations::BIRKindType kind() const;

public:
	string kindStr() const;

public:
	virtual ~BIRBase() = 0;
};
} // namespace BIR

#endif
