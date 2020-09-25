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

#ifndef __VESYLA_SCHEDULE_TIMETABLE_HPP__
#define __VESYLA_SCHEDULE_TIMETABLE_HPP__

#include "util/Common.hpp"
#include "Frame.hpp"

namespace vesyla{
namespace schedule{

//! A class that represent resource occupation status of one resource. It's a collection of Frame.
class Timetable{
private:
	vector<Frame> _table;
public:
	/**
	 * Constructor
	 */
	Timetable(vector<Frame> v_={}) : _table(v_){}
	Timetable(vector<vector<int> > v_){
		for(auto& e : v_){
			Frame f(e);
			_table.push_back(f);
		}
	}
	
	/**
	 * \brief Shift every frame in Timetable.
	 * \param offset_ The constant offset.
	 */
	void shift(int offset_);
	
	/**
	 * \brief Merge frame in Timetable if possible. If frames have conflict, report merge failure.
	 * \return True if merge is success, otherwise false.
	 */
	bool merge();
	
	/**
	 * \brief Dump the Timetable for debugging.
	 */
	string dump();
	
	using iterator = std::vector<Frame>::iterator;
	using const_iterator = std::vector<Frame>::const_iterator;

	/**
	 * \brief Interface for iteration
	 */
	iterator begin(){
		return _table.begin();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	iterator end(){
		return _table.end();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	const_iterator cbegin() const {
		return _table.cbegin();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	const_iterator cend() const {
		return _table.cend();
	}
	
	/**
	 * \brief Interface vector like push back
	 */
	void push_back(Frame f_){
		_table.push_back(f_);
	}
	
	/**
	 * \brief Interface for vector like size access.
	 */
	int size(){
		return _table.size();
	}
	
	/**
	 * \brief Interface for vector like slicing.
	 */
	Frame& operator[](const int i){
		return _table[i];
	}
	
};

}
}

#endif // __VESYLA_SCHEDULE_TIMETABLE_HPP__
