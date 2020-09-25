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

#include "Statement.hpp"
#include "VIRBase.hpp"

VIR::Statement::Statement() {
	_controlDependentTo = 0;
	_statementNo = 0;
}

VIR::Statement::~Statement() {
//	throw "Not yet implemented";
}

VIR::Statement * VIR::Statement::controlDependentTo() const {
	return _controlDependentTo;
}

void VIR::Statement::controlDependentTo(VIR::Statement * controlDependentTo_) {
	_controlDependentTo = controlDependentTo_;
}

int VIR::Statement::statementNo() const {
	return _statementNo;
}

void VIR::Statement::statementNo(int statementNo_) {
	_statementNo = statementNo_;
}

