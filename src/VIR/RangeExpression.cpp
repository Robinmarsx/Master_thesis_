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

#include "RangeExpression.hpp"
#include "Expression.hpp"

VIR::Expression * VIR::RangeExpression::begin() const {
	return _begin;
}

void VIR::RangeExpression::begin(Expression * begin_) {
	_begin = begin_;
}

VIR::Expression * VIR::RangeExpression::end() const {
	return _end;
}

void VIR::RangeExpression::end(Expression * end_) {
	_end = end_;
}

VIR::Expression * VIR::RangeExpression::increment() const {
	return _increment;
}

void VIR::RangeExpression::increment(Expression * increment_) {
	_increment = increment_;
}

