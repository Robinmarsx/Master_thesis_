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

#ifndef __PragmaExpression_h__
#define __PragmaExpression_h__

#include "Pragma.hpp"
#include "Expression.hpp"

namespace VIR
{
// class Pragma;
class PragmaExpression;
} // namespace VIR

namespace VIR
{
class PragmaExpression : public VIR::Pragma
{
private:
	string _name;

private:
	VIR::Expression *_row;

private:
	VIR::Expression *_column;

public:
	string name() const;

public:
	void name(const string &name_);

public:
	VIR::Expression *row() const;

public:
	void row(Expression *row_);

public:
	VIR::Expression *column() const;

public:
	void column(Expression *column_);
};
} // namespace VIR

#endif
