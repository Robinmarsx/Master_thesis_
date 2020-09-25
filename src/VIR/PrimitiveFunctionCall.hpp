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

#ifndef __PrimitiveFunctionCall_h__
#define __PrimitiveFunctionCall_h__

#include "FunctionCall.hpp"
#include "FunctionType.hpp"

namespace VIR
{
// class FunctionCall;
class PrimitiveFunctionCall;
namespace VirEnumerations
{
// enum FunctionType;
}
} // namespace VIR

namespace VIR
{
class PrimitiveFunctionCall : public VIR::FunctionCall
{
public:
	string primitive_func_name;

private:
	VIR::VirEnumerations::FunctionType _type;

public:
	PrimitiveFunctionCall();
	VIR::VirEnumerations::FunctionType type() const;
	void type(VIR::VirEnumerations::FunctionType type_);
};
} // namespace VIR

#endif
