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

#include "Operation.hpp"

namespace vesyla
{
namespace schedule
{

void Operation::load(pt::ptree p)
{
	_name = p.get("name", "");
	//const string name = p.get("name", "");
	//Operation AA(name);
	CHECK_NE(_name, "");
	scheduled_time = p.get<int>("Operation.scheduled_time", 0);
	for (pt::ptree::value_type &v : p.get_child(""))
	{
		if (v.first == "Rot")
		{
			for (pt::ptree::value_type &v1 : v.second.get_child(""))
			{
				if (v1.first == "Timetable")
				{
					string rs = v1.second.get("<xmlattr>.rs", "");
					Timetable tb;
					for (pt::ptree::value_type &v2 : v1.second.get_child(""))
					{
						if (v2.first == "Frame")
						{
							int t0 = v2.second.get<int>("<xmlattr>.t0", 0);
							int t1 = v2.second.get<int>("<xmlattr>.t1", 0);
							int sn = v2.second.get<int>("<xmlattr>.sn", 0);
							Frame f(t0, t1, sn);
							tb.push_back(f);
						}
					}
					tb.merge();
					rot[rs] = tb;
				}
			}
		}
		else if (v.first == "Children0")
		{
			for (pt::ptree::value_type &v1 : v.second.get_child(""))
			{
				if (v1.first == "Child")
				{
					add_child(v1.second.get("<xmlattr>.name", ""), 0);
					
				}
			}
		}
		else if (v.first == "Children1")
		{
			for (pt::ptree::value_type &v1 : v.second.get_child(""))
			{
				if (v1.first == "Child")
				{
					add_child(v1.second.get("<xmlattr>.name", ""), 1);
				}
			}
		}
	}
}

pt::ptree Operation::dump()
{
	pt::ptree po;
	po.put("name", _name);
	if (scheduled_time >= 0)
	{
		po.put("scheduled_time", scheduled_time);
	}

	pt::ptree prot;
	for (auto &r : rot)
	{
		pt::ptree ptb;
		ptb.put("<xmlattr>.rs", r.first);
		for (auto &f : r.second)
		{
			pt::ptree pframe;
			pframe.put<int>("<xmlattr>.t0", f.t0);
			pframe.put<int>("<xmlattr>.t1", f.t1);
			if (f.sn != 0)
			{
				pframe.put<int>("<xmlattr>.sn", f.sn);
			}
			ptb.add_child("Frame", pframe);
		}
		prot.add_child("Timetable", ptb);
	}
	po.add_child("Rot", prot);

	pt::ptree pchildren0;
	for (auto &c : children0)
	{
		pt::ptree pchild;
		pchild.put("<xmlattr>.name", c);
		pchildren0.add_child("Child", pchild);
	}
	po.add_child("Children0", pchildren0);
	pt::ptree pchildren1;
	for (auto &c : children1)
	{
		pt::ptree pchild;
		pchild.put("<xmlattr>.name", c);
		pchildren0.add_child("Child", pchild);
	}
	po.add_child("Children1", pchildren1);

	return po;
}

void Operation::add_child(const string name_, int children_list_id_)
{
	if (name_ == "")
	{
		return;
	}
	if (children_list_id_ != 0 && children_list_id_ != 1)
	{
		return;
	}
	if (children_list_id_ == 0)
	{
		bool flag = false;
		for (auto &c : children0)
		{
			if (c == name_)
			{
				flag = true;
			}
		}
		if (!flag)
		{
			children0.push_back(name_);
		}
	}
	else if (children_list_id_ == 1)
	{
		bool flag = false;
		for (auto &c : children1)
		{
			if (c == name_)
			{
				flag = true;
			}
		}
		if (!flag)
		{
			children1.push_back(name_);
		}
	}
}

void Operation::add_children(vector<string> name_list_, int children_list_id_)
{
	for (auto &n : name_list_)
	{
		add_child(n, children_list_id_);
	}
}

string Operation::name()
{
	return _name;
}

} // namespace schedule
} // namespace vesyla
