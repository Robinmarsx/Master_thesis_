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

#include "Constraint.hpp"

namespace vesyla
{
namespace schedule
{

void Constraint::load(pt::ptree p)
{
	_src = p.get("src", "");
	_dest = p.get("dest", "");
	d_lo = p.get("d_lo", INT_MIN);
	d_hi = p.get("d_hi", INT_MAX);
	CHECK_NE(_src, "");
	CHECK_NE(_dest, "");
	CHECK_LE(d_lo, d_hi);
	CHECK(!((d_lo == INT_MIN) && (d_hi == INT_MAX)));
}

pt::ptree Constraint::dump()
{
	pt::ptree po;
	po.put("src", _src);
	po.put("dest", _dest);
	if (d_lo > INT_MIN)
	{
		po.put("d_lo", d_lo);
	}
	if (d_hi < INT_MAX)
	{
		po.put("d_hi", d_hi);
	}
	return po;
}

string Constraint::src()
{
	return _src;
}

string Constraint::dest()
{
	return _dest;
}

} // namespace schedule
} // namespace vesyla
