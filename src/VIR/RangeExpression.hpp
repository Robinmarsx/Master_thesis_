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

#ifndef __RangeExpression_h__
#define __RangeExpression_h__

#include "Expression.hpp"

namespace VIR {
// class Expression;
class RangeExpression;
}

namespace VIR {
class RangeExpression: public VIR::Expression {
private:
	VIR::Expression * _begin;
private:
	VIR::Expression * _end;
private:
	VIR::Expression * _increment;

public:
	VIR::Expression * begin() const;

public:
	void begin(Expression * begin_);

public:
	VIR::Expression * end() const;

public:
	void end(Expression * end_);

public:
	VIR::Expression * increment() const;

public:
	void increment(Expression * increment_);
};
}

#endif
