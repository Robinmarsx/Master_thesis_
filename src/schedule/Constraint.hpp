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

#ifndef __VESYLA_SCHEDULE_CONSTRAINT_HPP__
#define __VESYLA_SCHEDULE_CONSTRAINT_HPP__

#include "util/Common.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

namespace vesyla
{
namespace schedule
{

class Constraint
{
public:
	enum Hook
	{
		HOOK_BEGIN,
		HOOK_END
	};

public:
	string _src;
	string _dest;

public:
	int d_lo;
	int d_hi;

public:
	Hook src_hook;
	Hook dest_hook;

	Constraint(
			const string src_ = "",
			const string dest_ = "",
			int d_lo_ = INT_MIN,
			int d_hi_ = INT_MAX,
			Hook src_hook_ = HOOK_BEGIN,
			Hook dest_hook_ = HOOK_BEGIN)
			: _src(src_),
				_dest(dest_),
				d_lo(d_lo_),
				d_hi(d_hi_),
				src_hook(src_hook_),
				dest_hook(dest_hook_) {}
	void load(pt::ptree p);
	pt::ptree dump();
	string src();
	string dest();
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_CONSTRAINT_HPP__
