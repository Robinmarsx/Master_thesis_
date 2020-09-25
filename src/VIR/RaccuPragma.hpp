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

#ifndef __RaccuPragma_h__
#define __RaccuPragma_h__

#include "../BIR/RACCUMode.hpp"
#include "AssignmentPragma.hpp"
#include "RaccuOptions.hpp"

namespace BIR
{
namespace BIREnumerations
{
// enum RACCUMode;
}
} // namespace BIR
namespace VIR
{
// class AssignmentPragma;
class RaccuPragma;
namespace VirEnumerations
{
// enum RaccuOptions;
}
} // namespace VIR

namespace VIR
{
class RaccuPragma : public VIR::AssignmentPragma
{
public:
	BIR::BIREnumerations::RACCUMode raccuMode;

public:
	VIR::VirEnumerations::RaccuOptions raccuOptions;

public:
	RaccuPragma();
};
} // namespace VIR

#endif
