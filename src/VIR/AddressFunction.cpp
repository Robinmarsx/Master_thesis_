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

#include "AddressFunction.hpp"

namespace VIR
{

int AddressFunction::b()
{
	return _b;
}

void AddressFunction::b(int b_)
{
	_b = b_;
}

int AddressFunction::level()
{
	CHECK_EQ(_a.size(), _n.size());
	CHECK_EQ(_a.size(), _l.size());
	return _a.size();
}

int AddressFunction::a(int i_)
{
	CHECK_GE(i_, 0);
	CHECK_LT(i_, _a.size());
	return (_a[i_]);
}

int AddressFunction::n(int i_)
{
	CHECK_GE(i_, 0);
	CHECK_LT(i_, _n.size());
	return (_n[i_]);
}

VIR::ForStatement *AddressFunction::l(int i_)
{
	CHECK_GE(i_, 0);
	CHECK_LT(i_, _l.size());
	return (_l[i_]);
}

void AddressFunction::add_level(int a_, int n_, VIR::ForStatement *l_)
{
	if (l_ == NULL)
	{
		int nonloop_level_counter = 0;
		for (auto &l : _l)
		{
			if (l == NULL)
			{
				nonloop_level_counter++;
			}
		}
		CHECK_LT(nonloop_level_counter, _max_nonloop_level);
	}
	_a.push_back(a_);
	_n.push_back(n_);
	_l.push_back(l_);
}

} // namespace VIR