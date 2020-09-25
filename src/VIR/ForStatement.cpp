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

#include "ControlStatement.hpp"
#include "ParallelMode.hpp"
#include "ForStatement.hpp"

VIR::ForStatement::ForStatement() {
	_degree = 1;
	_isConstant = true;
	_needDynamicHandling = false;
}

VIR::RangeExpression * VIR::ForStatement::loopRange() const {
	return _loopRange;
}

void VIR::ForStatement::loopRange(RangeExpression * loopRange_) {
	_loopRange = loopRange_;
}

VIR::Identifier * VIR::ForStatement::loopVariable() const {
	return _loopVariable;
}

void VIR::ForStatement::loopVariable(Identifier * loopVariable_) {
	_loopVariable = loopVariable_;
}

vector<VIR::Statement*> & VIR::ForStatement::loopBody() {
	return _loopBody;
}

VIR::VirEnumerations::ParallelMode VIR::ForStatement::parallelMode() const {
	return _parallelMode;
}

void VIR::ForStatement::parallelMode(
		const VIR::VirEnumerations::ParallelMode & parallelMode_) {
	_parallelMode = parallelMode_;
}

int VIR::ForStatement::degree() const {
	return _degree;
}

void VIR::ForStatement::degree(int degree_) {
	_degree = degree_;
}

int VIR::ForStatement::repetition() const {
	return _repetition;
}

void VIR::ForStatement::repetition(int repetition_) {
	_repetition = repetition_;
}

bool VIR::ForStatement::isConstant() const {
	return _isConstant;
}

void VIR::ForStatement::isConstant(bool isConstant_) {
	_isConstant = isConstant_;
}

bool VIR::ForStatement::needDynamicHandling() const {
	return _needDynamicHandling;
}

void VIR::ForStatement::needDynamicHandling(bool needDynamicHandling_) {
	_needDynamicHandling = needDynamicHandling_;
}

map<string, int>& VIR::ForStatement::unrolledRepetitionsMap() {
	return _unrolledRepetitionsMap;
}

