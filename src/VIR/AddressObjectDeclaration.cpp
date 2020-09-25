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

#include "AddressObjectDeclaration.hpp"
#include "AssignmentStatement.hpp"
#include "Expression.hpp"
#include "ObjectDeclaration.hpp"
#include "BinaryOperatorType.hpp"

VIR::AssignmentStatement* VIR::AddressObjectDeclaration::addressIterator() const {
	return _addressIterator;
}

void VIR::AddressObjectDeclaration::addressIterator(
		VIR::AssignmentStatement* addressIterator_) {
	_addressIterator = addressIterator_;
}

VIR::Expression * VIR::AddressObjectDeclaration::iterationAmount() const {
	return _iterationAmount;
}

void VIR::AddressObjectDeclaration::iterationAmount(
		VIR::Expression * iterationAmount_) {
	_iterationAmount = iterationAmount_;
}

void VIR::AddressObjectDeclaration::operatorType(
		const VIR::VirEnumerations::BinaryOperatorType & operatorType_) {
	_operatorType = operatorType_;
}

VIR::VirEnumerations::BinaryOperatorType VIR::AddressObjectDeclaration::operatorType() const {
	return _operatorType;
}

