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

#ifndef __VESYLA_SCHEDULE_DESCRIPTOR_HPP__
#define __VESYLA_SCHEDULE_DESCRIPTOR_HPP__

#include <climits>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include <boost/property_tree/ptree.hpp>
#include "Operation.hpp"
#include "Constraint.hpp"

#include <boost/graph/transitive_closure.hpp>
#include <boost/graph/transitive_reduction.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>

namespace pt = boost::property_tree;
using namespace BIR;
using namespace BIR::BIREnumerations;

namespace vesyla
{
namespace schedule
{

class Descriptor
{
private:
	map<string, Operation> _operations;
	map<string, Constraint> _constraints;
	map<string, vector<Constraint *>> _src_constraint_index;
	map<string, vector<Constraint *>> _dest_constraint_index;
	map<string, vector<BIR::Instruction *>> _instr_lists;
	string _entry;
	std::unordered_map<string, int> _id_counters;

public:
	Descriptor(string entry_ = "root") : _entry(entry_){};

	void load(pt::ptree p);
	pt::ptree dump();
	int count_operations() { return _operations.size(); }
	int count_constraints() { return _constraints.size(); }
	void add_operation(Operation op_);
	void add_constraint(Constraint c_);
	Operation get_operation(const string name_);
	Operation &get_mutable_operation(const string name_);
	Constraint get_constraint(const string src_, const string dest_);
	Constraint &get_mutable_constraint(const string src_, const string dest_);
	vector<Constraint *> get_src_constraints(const string dest_);
	vector<Constraint *> get_dest_constraints(const string src_);
	vector<Constraint *> get_all_constraints();
	bool check_operation(const string name_);
	bool check_constraint(const string src_, const string dest_);
	void remove_constraint(const string src_, const string dest_);
	vector<string> get_all_operation_names();
	string entry() { return _entry; }
	void set_entry(string name_)
	{
		_entry = name_;
	}
	int get_max_schedule_time()
	{
		int t = -1;
		for (auto &e : _operations)
		{
			if (t < e.second.scheduled_time)
			{
				t = e.second.scheduled_time;
			}
		}
		CHECK_GE(t, 0);
		return t;
	}

	string gen_signature(string parent_ = "root")
	{
		if (_id_counters.find(parent_) == _id_counters.end())
		{
			_id_counters[parent_] = 1;
			string s = parent_ + "/0";
			return s;
		}
		string s = parent_ + "/" + to_string(_id_counters[parent_]);
		_id_counters[parent_]++;
		return s;
	}

	void add_instruction(string signature_, BIR::Instruction *instr_)
	{
		if (_instr_lists.find(signature_) != _instr_lists.end())
		{
			_instr_lists[signature_].push_back(instr_);
			return;
		}
		else
		{
			_instr_lists[signature_] = {instr_};
			return;
		}
	}

	void fill_timestamp();
	void fill_mark(map<BIR::Instruction *, string> &mark_map, string vertex_name = "", string mark_id = "0");
	map<string, vector<BIR::Instruction *>> get_instr_lists()
	{
		return _instr_lists;
	}

	string generate_dot_graph_for_operation(string operation_, std::set<string> &operation_set_);
	string generate_dot_graph();
	string generate_dot_graph(string name_);
	string generate_dot_graph(std::set<string> names_);
	string generate_schedule_table();
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_DESCRIPTOR_HPP__
