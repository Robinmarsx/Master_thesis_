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

#include "PragmaExpression.hpp"
#include "Pragma.hpp"

string VIR::PragmaExpression::name() const {
	return _name;
}

void VIR::PragmaExpression::name(const string & name_) {
	_name = name_;
}

VIR::Expression * VIR::PragmaExpression::row() const {
	return _row;
}

void VIR::PragmaExpression::row(Expression * row_) {
	_row = row_;
}

VIR::Expression * VIR::PragmaExpression::column() const {
	return _column;
}

void VIR::PragmaExpression::column(Expression * column_) {
	_column = column_;
}

