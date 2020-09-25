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

#include "Timetable.hpp"

namespace vesyla
{
namespace schedule
{

string Timetable::dump()
{
	string s;
	for (auto &f : _table)
	{
		s += (f.dump() + " ");
	}
	return s;
}

void Timetable::shift(int offset_)
{
	for (auto &e : _table)
	{
		e.shift(offset_);
	}
}

bool Timetable::merge()
{
	sort(_table.begin(), _table.end(),
			 [](Frame a, Frame b) -> bool {
				 return (a.pos() < b.pos());
			 });

	vector<Frame> tb;
	for (auto &f : _table)
	{
		if (tb.size() == 0)
		{
			tb.push_back(f);
			continue;
		}
		Frame &f0 = tb.back();
		Frame &f1 = f;
		if (f0.type() == 1)
		{
			if (f1.type() == 1)
			{
				return false;
			}
			else if (f1.type() == 2)
			{
				if (f0.t1 >= f1.t0 && f0.sn == f1.sn)
				{
					f0.t0 = f1.t0;
				}
				else if (f0.t1 < f1.t0 && f0.sn != f1.sn)
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else if (f1.type() == 3)
			{
				if (f0.t1 < f1.t0 && f1.t0 <= f1.t1)
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (f0.type() == 2)
		{
			if (f1.type() == 1)
			{
				if (f0.t0 <= f1.t1 && f0.sn == f1.sn)
				{
					f0.t1 = f1.t1;
				}
				else if (f0.t0 > f1.t1 && f0.sn != f1.sn)
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else if (f1.type() == 2)
			{
				return false;
			}
			else if (f1.type() == 3)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		else if (f0.type() == 3)
		{
			if (f1.type() == 1)
			{
				return false;
			}
			else if (f1.type() == 2)
			{
				if (f0.t1 == f1.t0 - 1)
				{
					f0.t1 = f1.t1;
					f0.sn = f1.sn;
				}
				else if (f0.t1 < (f1.t0 - 1))
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else if (f1.type() == 3)
			{
				if (f0.t1 == (f1.t0 - 1))
				{
					f0.t1 = f1.t1;
				}
				else if (f0.t1 < (f1.t0 - 1))
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	_table = tb;
	return true;
}

} // namespace schedule
} // namespace vesyla
