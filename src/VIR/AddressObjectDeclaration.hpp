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

#ifndef __AddressObjectDeclaration_h__
#define __AddressObjectDeclaration_h__

// #include "AssignmentStatement.hpp"
// #include "Expression.hpp"
#include "ObjectDeclaration.hpp"
#include "BinaryOperatorType.hpp"

namespace VIR {
class AssignmentStatement;
class Expression;
// class ObjectDeclaration;
class AddressObjectDeclaration;
namespace VirEnumerations {
// enum BinaryOperatorType;
}
}

namespace VIR {
class AddressObjectDeclaration: public VIR::ObjectDeclaration {
private:
	VIR::AssignmentStatement* _addressIterator;
private:
	VIR::Expression* _iterationAmount;
private:
	VIR::VirEnumerations::BinaryOperatorType _operatorType;

public:
	VIR::AssignmentStatement* addressIterator() const;

public:
	void addressIterator(VIR::AssignmentStatement* addressIterator_);

public:
	VIR::Expression * iterationAmount() const;

public:
	void iterationAmount(VIR::Expression * iterationAmount_);

public:
	void operatorType(
			const VIR::VirEnumerations::BinaryOperatorType & operatorType_);

public:
	VIR::VirEnumerations::BinaryOperatorType operatorType() const;
};
}

#endif
