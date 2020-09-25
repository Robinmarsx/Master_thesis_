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
#include <string>
using namespace std;

#ifndef __UnaryExpression_h__
#define __UnaryExpression_h__

#include "Expression.hpp"
#include "UnaryOperatorType.hpp"

namespace VIR {
// class Expression;
class UnaryExpression;
namespace VirEnumerations {
// enum UnaryOperatorType;
}
}

namespace VIR {
class UnaryExpression: public VIR::Expression {
private:
	VIR::Expression * _operand;
private:
	VIR::VirEnumerations::UnaryOperatorType _operatorType;

public:
	VIR::Expression * operand() const;

public:
	void operand(Expression * operand_);

public:
	VIR::VirEnumerations::UnaryOperatorType operatorType() const;

public:
	void operatorType(
			const VIR::VirEnumerations::UnaryOperatorType & operatorType_);

public:
	string operatorTypeStr() const;

public:
	string operatorStr() const;
};
}

#endif
