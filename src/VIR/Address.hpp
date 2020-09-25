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

#ifndef __VESYLA_VIR_ADDRESS_HPP__
#define __VESYLA_VIR_ADDRESS_HPP__

#include "AddressFunction.hpp"

//namespace vesyla{
namespace VIR
{
class Address
{
public:
	AddressFunction b;
	AddressFunction a0;
	AddressFunction n0;
	AddressFunction a1;
	AddressFunction n1;

public:
	Address()
	{
		b.b(0);
		a0.b(0);
		n0.b(1);
		a1.b(0);
		n1.b(1);
	}
	~Address() {}
};
} // namespace VIR
//}

#endif // __VESYLA_VIR_ADDRESS_HPP__