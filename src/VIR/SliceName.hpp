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

#ifndef __SliceName_h__
#define __SliceName_h__

#include "Name.hpp"
#include "Identifier.hpp"
#include "IndexInfo.hpp"
#include "Address.hpp"

namespace VIR
{
// class Name;
class SliceName;
} // namespace VIR

namespace VIR
{
class SliceName : public VIR::Name
{
private:
	VIR::Identifier *_prefix;
	vector<Expression *> _suffix;
	VIR::IndexInfo *_indexInfo;

public:
	VIR::Address addr;

public:
	bool is_function_call;

public:
	SliceName();

public:
	VIR::Identifier *prefix() const;

public:
	void prefix(Identifier *prefix_);

public:
	vector<Expression *> &suffix();

public:
	VIR::IndexInfo *indexInfo() const;

public:
	void indexInfo(VIR::IndexInfo *indexInfo_);
};
} // namespace VIR

#endif
