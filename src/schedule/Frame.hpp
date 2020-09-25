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

#ifndef __VESYLA_SCHEDULE_FRAME_HPP__
#define __VESYLA_SCHEDULE_FRAME_HPP__

#include "util/Common.hpp"

namespace vesyla
{
namespace schedule
{

//! A class that represent a resource occupation time frame in resource occupation table.
class Frame
{
public:
	enum Type
	{
		ILLEGAL,
		KEY,
		LOCK,
		PERIOD
	};

public:
	//! Lock/Key pair serial number. It's used to distinguish which lock and key are paired. This field will be ignored by period frame.
	int sn;

	//! The start time of source occupation. In case it's a key, this field is INT_MIN.
	int t0;

	//! The end time of source occupation. In case it's a lock, this field is INT_MAX. t1 >= t0.
	int t1;

public:
	/**
	 * \brief Constructor
	 */
	Frame(int t0_, int t1_, int sn_ = 0) : t0(t0_), t1(t1_), sn(sn_) {}
	Frame(vector<int> v_)
	{
		CHECK_GE(v_.size(), 2) << "Frame is not valid!";
		t0 = v_[0];
		t1 = v_[1];
		if (v_.size() >= 3)
		{
			sn = v_[2];
		}
		else
		{
			sn = 0;
		}
	}

	/**
	 * \brief Return the type of frame.
	 * - [INT_MIN, t1] is a key frame, type is "1"
	 * - [t0, INT_MAX] is a lock frame, type is "2"
	 * - [t0, t1] is a period frame, type is "3"
	 * - Other combination such as [INT_MIN, INT_MAX] is illegal, will return "0"
	 * 
	 * \return The frame type in integer number format.
	 */
	int type();

	/**
	 * \brief Return the position of each frame
	 * - return start postion (t0) if it's lock frame or period frame.
	 * - return end postion (t1) if it's key frame.
	 * 
	 * \return The postion of frame.
	 */
	int pos();

	/**
	 * \brief Return the max position of each frame
	 * - return start postion (t0) if it's lock frame.
	 * - return end postion (t1) if it's key frame or period frame.
	 * 
	 * \return The postion of frame.
	 */
	int max_pos();

	/**
	 * \brief Shift the frame by constant clock
	 * \param offset_ The offset to be shifted, can be negative;
	 */
	void shift(int offset_);

	/**
	 * \brief Check whether the current frame is later than the given frame "f_".
	 * \param offset_ The offset to be shifted, can be negative;
	 * \return True if current frame's position is later than the given position.
	 */
	bool is_later_than(Frame f_);

	/**
	 * \brief Dump the frame to a string for debugging.
	 */
	string dump();
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_FRAME_HPP__
