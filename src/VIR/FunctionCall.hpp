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

#ifndef __FunctionCall_h__
#define __FunctionCall_h__

#include "Expression.hpp"
#include "Identifier.hpp"

namespace VIR {
// class Expression;
class FunctionCall;
}

namespace VIR {
class FunctionCall: public VIR::Expression {
public:
	VIR::Identifier * _name;
	vector<Expression*> _parameters;
	vector<Expression*> _parametersSplit;

public:
	VIR::Identifier* name(){
		return _name;
	}
	void name(Identifier* name_){
		_name=name_;
	}
	vector<Expression*> & parameters(){
		return _parameters;
	}
	vector<Expression*> & parametersSplit(){
		return _parametersSplit;
	}
};
}

#endif
