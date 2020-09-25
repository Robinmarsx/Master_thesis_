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



#ifndef __BinaryExpression_h__
#define __BinaryExpression_h__

#include "Expression.hpp"
#include "BinaryOperatorType.hpp"
#include <exception>
#include <string>
using namespace std;

namespace VIR
{
// class Expression;
class BinaryExpression;
namespace VirEnumerations
{
// enum BinaryOperatorType;
}
} // namespace VIR

namespace VIR
{
class BinaryExpression : public VIR::Expression
{
private:
	VIR::Expression *_leftOperand;

private:
	VIR::Expression *_rightOperand;

private:
	VIR::VirEnumerations::BinaryOperatorType _operatorType;

public:
	VIR::Expression *leftOperand() const;

public:
	void leftOperand(Expression *leftOperand_);

public:
	VIR::Expression *rightOperand() const;

public:
	void rightOperand(Expression *rightOperand_);

public:
	VIR::VirEnumerations::BinaryOperatorType operatorType() const;

public:
	void operatorType(
			const VIR::VirEnumerations::BinaryOperatorType &operatorType_);

public:
	string operatorTypeStr() const;

public:
	string operatorStr() const;
};
} // namespace VIR

#endif
