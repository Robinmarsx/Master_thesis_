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

#include "UnaryOperatorType.hpp"

#define OP_STR(op, opStr) case(op): str = opStr; break;
#define OP_TYPE_STR(op) case(op): str = #op; break;

string VIR::VirEnumerations::unaryOperatorStr(UnaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_STR(uotPlus, "+")
		;
	OP_STR(uotMinus, "-")
		;
	OP_STR(uotNot, "~")
		;
	OP_STR(uotTranspose, ".'")
		;
	OP_STR(uotCTranspose, "'")
		;
	}

	return str;
}

string VIR::VirEnumerations::unaryOperatorTypeStr(UnaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_TYPE_STR(uotPlus)
		;
	OP_TYPE_STR(uotMinus)
		;
	OP_TYPE_STR(uotNot)
		;
	OP_TYPE_STR(uotTranspose)
		;
	OP_TYPE_STR(uotCTranspose)
		;
	}

	return str.substr(3);
}
