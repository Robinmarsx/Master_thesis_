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

#include "BinaryOperatorType.hpp"

#define OP_STR(op, opStr) case(op): str = opStr; break;
#define OP_TYPE_STR(op) case(op): str = #op; break;

string VIR::VirEnumerations::binaryOperatorStr(BinaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_STR(botAdd, "+")
		;
	OP_STR(botSub, "-")
		;
	OP_STR(botMPower, "^")
		;
	OP_STR(botEPower, ".^")
		;
	OP_STR(botMMul, "*")
		;
	OP_STR(botEMul, ".*")
		;
	OP_STR(botMDiv, "/")
		;
	OP_STR(botEDiv, "./")
		;
	OP_STR(botMLeftDiv, "\\")
		;
	OP_STR(botELeftDiv, ".\\")
		;
	OP_STR(botEqual, "==")
		;
	OP_STR(botUnEqual, "~=")
		;
	OP_STR(botGreaterThan, ">")
		;
	OP_STR(botGreaterOrEqual, ">=")
		;
	OP_STR(botLessThan, "<")
		;
	OP_STR(botLessOrEqual, "<=")
		;
	OP_STR(botAnd, "&")
		;
	OP_STR(botOr, "|")
		;
	}

	return str;
}

string VIR::VirEnumerations::binaryOperatorTypeStr(BinaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_TYPE_STR(botAdd)
		;
	OP_TYPE_STR(botSub)
		;
	OP_TYPE_STR(botMPower)
		;
	OP_TYPE_STR(botEPower)
		;
	OP_TYPE_STR(botMMul)
		;
	OP_TYPE_STR(botEMul)
		;
	OP_TYPE_STR(botMDiv)
		;
	OP_TYPE_STR(botEDiv)
		;
	OP_TYPE_STR(botMLeftDiv)
		;
	OP_TYPE_STR(botELeftDiv)
		;
	OP_TYPE_STR(botEqual)
		;
	OP_TYPE_STR(botUnEqual)
		;
	OP_TYPE_STR(botGreaterThan)
		;
	OP_TYPE_STR(botGreaterOrEqual)
		;
	OP_TYPE_STR(botLessThan)
		;
	OP_TYPE_STR(botLessOrEqual)
		;
	OP_TYPE_STR(botAnd)
		;
	OP_TYPE_STR(botOr)
		;
	}

	return str.substr(3);
}
