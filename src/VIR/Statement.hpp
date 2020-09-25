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

#ifndef __Statement_h__
#define __Statement_h__

#include "VIRBase.hpp"

namespace VIR {
// class VIRBase;
class Statement;
}

namespace VIR {
class Statement: public VIR::VIRBase {
private:
	VIR::Statement * _controlDependentTo;
private:
	int _statementNo;

public:
	Statement();

public:
	virtual ~Statement() = 0;

public:
	VIR::Statement * controlDependentTo() const;

public:
	void controlDependentTo(VIR::Statement * controlDependentTo_);

public:
	int statementNo() const;

public:
	void statementNo(int statementNo_);
};
}

#endif
