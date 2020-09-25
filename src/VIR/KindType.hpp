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

#ifndef __KindType_h__
#define __KindType_h__

#include <string>
using std::string;

namespace VIR
{
namespace VirEnumerations
{
// enum KindType;
}
} // namespace VIR

namespace VIR
{
namespace VirEnumerations
{
// Note: By any change in here also change the implementation of the kindStr function
enum KindType
{
	ktAddressObjectDeclaration,
	ktAddressPragma,
	ktArray,
	ktAssignmentStatement,
	ktBinaryExpression,
	ktBlockPragma,
	ktComplex,
	ktDebugStatement,
	ktDPUChainPragma,
	ktDPUPragma,
	ktFloatingPoint,
	ktForStatement,
	ktFunctionDeclaration,
	ktFunctionCall,
	ktIdentifier,
	ktIfStatement,
	ktIfThenElseStatement,
	ktIndexInfo,
	ktInteger,
	ktLoopObjectDeclaration,
	ktMainProgram,
	ktObjectDeclaration,
	ktParenthesizedExpression,
	ktPragmaConstant,
	ktPragmaExpression,
	ktPragmaStatement,
	ktPrimitiveFunctionCall,
	ktRaccuPragma,
	ktRangeExpression,
	ktSliceName,
	ktStoragePragma,
	ktStringLiteral,
	ktTempVarPragma,
	ktUnaryExpression,
	ktFunctionCallStatement,
	ktRenamePragma
};

string kindStr(KindType kind_);
} // namespace VirEnumerations
} // namespace VIR

#endif
