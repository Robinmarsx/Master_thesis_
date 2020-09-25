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

#include "IfStatement.hpp"
#include "ControlStatement.hpp"
#include "IfMode.hpp"

VIR::Expression *VIR::IfStatement::condition() const
{
	return _condition;
}

void VIR::IfStatement::condition(Expression *condition_)
{
	_condition = condition_;
}

vector<VIR::Statement *> &VIR::IfStatement::thenPart()
{
	return _thenPart;
}

vector<VIR::Statement *> &VIR::IfStatement::elsePart()
{
	return _elsePart;
}

VIR::VirEnumerations::IfMode VIR::IfStatement::mode() const
{
	return _mode;
}

void VIR::IfStatement::mode(VIR::VirEnumerations::IfMode mode_)
{
	_mode = mode_;
}

VIR::DPUPragma *VIR::IfStatement::conditionPragma() const
{
	return _conditionPragma;
}

void VIR::IfStatement::conditionPragma(VIR::DPUPragma *conditionPragma_)
{
	_conditionPragma = conditionPragma_;
}
