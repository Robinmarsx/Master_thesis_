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

#ifndef __VESYLA_SCHEDULE_ROT_HPP__
#define __VESYLA_SCHEDULE_ROT_HPP__

#include "util/Common.hpp"
#include "Timetable.hpp"

namespace vesyla
{
namespace schedule
{

//! A class that describes the resource occupation of an atomic opertaoin.
class Rot
{
public:
	map<string, Timetable> _rot;

public:
	/**
	 * \brief Constructor
	 */
	Rot(map<string, Timetable> rot_ = {}) : _rot(rot_) {}

	/**
	 * \brief Constructor
	 */
	Rot(map<string, vector<vector<int>>> rot_)
	{
		for (auto &r : rot_)
		{
			Timetable t(r.second);
			_rot[r.first] = t;
		}
	}

	/**
	 * \brief Merge two ROTs with verify the compatiblity.
	 * \param rot2 The ROT that will merge.
	 * \param offset_ The offset that will applied on rot2.
	 * \return True if all Frame is compatible, otherwise false.
	 */
	void merge(Rot rot2, int offset_);

	/**
	 * \brief Check the validation of Timetable of each resource.
	 * \return True if all Frame is compatible, otherwise false.
	 */
	bool verify();

	/**
	 * \brief Merging two ROTs
	 * \param rot2 The ROT that will merge.
	 * \param offset_lo the lower bound of offset applied on each timetable of rot2.
	 * \param offset_hi the higher bound of offset applied on each timetable of rot2.
	 * \return The final minimal offset applied in order to merge the ROTs. If it's INT_MIN, the merge fails.
	 * \warning Please notice that this merge_and_verify() is NOT equavalent to applied merge() and verify(). merge_and_verify() will try to find the correct offset value to try to make the merge success. While merge() will only use the fixed offset value and it always success.
	 */
	int merge_and_verify(Rot rot2, int offset_lo, int offset_hi = INT_MIN);

	bool unite(Rot rot2_, int offset_);

	/**
	 * \brief Dump the ROT for debugging.
	 * \return The dumped string.
	 */
	string dump();

	using iterator = std::map<string, Timetable>::iterator;
	using const_iterator = std::map<string, Timetable>::const_iterator;

	/**
	 * \brief Interface for iteration
	 */
	iterator begin()
	{
		return _rot.begin();
	}

	/**
	 * \brief Interface for iteration
	 */
	iterator end()
	{
		return _rot.end();
	}

	/**
	 * \brief Interface for iteration
	 */
	const_iterator cbegin() const
	{
		return _rot.cbegin();
	}

	/**
	 * \brief Interface for iteration
	 */
	const_iterator cend() const
	{
		return _rot.cend();
	}

	/**
	 * \brief Interface for map like size access.
	 */
	int size()
	{
		return _rot.size();
	}

	/**
	 * \brief Interface for map like slicing.
	 */
	Timetable &operator[](const string i)
	{
		return _rot[i];
	}

	/**
	 * \brief Interface for map like find function.
	 */
	iterator find(const string i)
	{
		return _rot.find(i);
	}

	/**
	 * \brief Interface for clone.
	 */
	void operator=(Rot r)
	{
		_rot = r._rot;
	}
	void convert_from_map(map<string, vector<vector<int>>> rot_)
	{
		rot_.clear();
		for (auto &r : rot_)
		{
			Timetable t(r.second);
			_rot[r.first] = t;
		}
	}

	map<string, vector<vector<int>>> convert_to_map()
	{
		map<string, vector<vector<int>>> m;
		for (auto &r : _rot)
		{
			string name = r.first;
			vector<vector<int>> vtb;
			Timetable &tb = r.second;
			tb.merge();
			for (auto &f : r.second)
			{
				vector<int> v({f.t0, f.t1});
				if (f.sn != 0)
				{
					v.push_back(f.sn);
				}
				vtb.push_back(v);
			}
			m[name] = vtb;
		}
		return m;
	}

	/**
	 * \brief Access the internal ROT storage
	 * \return The internal ROT reference.
	 */
	map<string, Timetable> &rot()
	{
		return _rot;
	}
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_ROT_HPP__
