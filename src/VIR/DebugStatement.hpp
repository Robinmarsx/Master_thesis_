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



#ifndef __DebugStatement_h__
#define __DebugStatement_h__

#include <exception>
#include <string>
using namespace std;
#include "Statement.hpp"

namespace VIR
{
// class Statement;
class DebugStatement;
} // namespace VIR

namespace VIR
{
class DebugStatement : public VIR::Statement
{
private:
	string _debugStr;

public:
	string debugStr() const;

public:
	void debugStr(const string &debugStr_);
};
} // namespace VIR

#endif
