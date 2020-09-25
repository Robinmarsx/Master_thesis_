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

#ifndef __FunctionDeclaration_h__
#define __FunctionDeclaration_h__

#include "Declaration.hpp"
#include "Statement.hpp"

namespace VIR {
// class Declaration;
class FunctionDeclaration;
}

namespace VIR {
class FunctionDeclaration: public VIR::Declaration {
private:
	vector<Statement*> _body;
private:
	string _name;
private:
	vector<Statement*> _totalAssignmentStatements;

public:
	vector<Statement*> & body();

public:
	string name() const;

public:
	void name(const string & name_);

public:
	vector<Statement*> & totalAssignmentStatements();
};
}

#endif
