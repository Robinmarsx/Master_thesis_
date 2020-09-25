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
#include <map>
using namespace std;

#include "IndexInfo.hpp"
#include "AddressInfo.hpp"
#include "UnrolledAddressInfo.hpp"
#include "ForStatement.hpp"
#include "Unrolling.hpp"
#include "Pragma.hpp"

VIR::IndexInfo::~IndexInfo() {

	for (auto& element : _unrolling) {
		delete element.second;
	}

	_unrolling.clear();

	isARaccuVariable = false;
}

void VIR::IndexInfo::addUnrolling(VIR::ForStatement * forStatement_,
		int numberOfRepetitions_, int unrollingOffset_, bool isDynamic_) {
	Unrolling * unrolling = new Unrolling;

	unrolling->numberOfRepetitions = numberOfRepetitions_;
	unrolling->unrollingOffset = unrollingOffset_;
	unrolling->isDynamic = isDynamic_;

	_unrolling[forStatement_] = unrolling;
}

VIR::Unrolling * VIR::IndexInfo::unrolling(
		VIR::ForStatement * forStatement_) const {
	return _unrolling.at(forStatement_);
}

map<VIR::ForStatement*, VIR::Unrolling*, VIR::IndexInfo::CompareMapElements>& VIR::IndexInfo::unrollingMap() {
	return _unrolling;
}

bool VIR::IndexInfo::CompareMapElements::operator()(const VIR::ForStatement * a,
		const VIR::ForStatement * b) const {
	return a->degree() < b->degree();
}
