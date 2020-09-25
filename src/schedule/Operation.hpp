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

#ifndef __VESYLA_SCHEDULE_OPERATION_HPP__
#define __VESYLA_SCHEDULE_OPERATION_HPP__

#include <climits>
#include <util/Common.hpp>
#include "Rot.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

namespace vesyla
{
namespace schedule
{

class Operation
{
private:
	string _name;

public:
	int scheduled_time;
	Rot rot;
	vector<string> children0;
	vector<string> children1;
	bool is_bulk;
	int shift_factor;
	bool expand_loop;
	string issue_slot;
	bool ignore_children;
	bool dont_touch;

	Operation(const string name_ = "", int scheduled_time_ = -1, map<string, vector<vector<int>>> rot_ = {}, vector<string> children0_ = {}, vector<string> children1_ = {}, bool is_bulk_ = false, int shift_factor_ = 0) : _name(name_), scheduled_time(scheduled_time_), rot(rot_), children0(children0_), children1(children1_), is_bulk(is_bulk_), shift_factor(shift_factor_)
	{
		ignore_children = false;
		expand_loop = false;
		issue_slot = "";
		dont_touch = false;
	}
	void load(pt::ptree p);
	pt::ptree dump();
	void add_child(const string name_, int children_list = 0);
	void add_children(vector<string> name_list_, int children_list = 0);
	string name();
	bool has_child()
	{
		if (children0.size() > 0 || children1.size() > 0)
		{
			return true;
		}
		return false;
	}
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_OPERATION_HPP__
