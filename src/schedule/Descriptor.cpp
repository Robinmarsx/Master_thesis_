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

#include "Descriptor.hpp"
using std::string;
using std::map;
using namespace std;
typedef list<string> LISTSTRING; 

namespace vesyla
{
namespace schedule
{

//void Descriptor::Operation::load(pt::ptree p){
//	_name = p.get<string>("name");
//
//	boost::optional<const pt::ptree&> opt_child;
//
//	opt_child = p.get_child_optional( "scheduled_time" );
//	if(opt_child){
//		scheduled_time = p.get<int>("scheduled_time");
//	}
//	opt_child = p.get_child_optional( "rot" );
//	if(opt_child){
//		for(pt::ptree::value_type &v : p.get_child("rot")){
//			string rs = v.second.get<string>("rs");
//			int t_start = v.second.get<int>("t_start");
//			int t_end = v.second.get<int>("t_end");
//			rot[rs] = {t_start, t_end};
//		}
//	}
//	opt_child = p.get_child_optional( "children" );
//	if(opt_child){
//		for(pt::ptree::value_type &v : p.get_child("children")){
//			string child = v.second.data();
//			children.push_back(child);
//		}
//	}
//}

//pt::ptree Descriptor::Operation::dump(){
//	pt::ptree p;
//	p.put("name", _name);
//	if(scheduled_time>=0){
//		p.put("scheduled_time", scheduled_time);
//	}
//	for(auto& r : rot){
//		pt::ptree pr;
//		pr.put("rs", r.first);
//		pr.put("t_start", r.second[0]);
//		pr.put("t_end", r.second[1]);
//		p.add_child("rot.resource", pr);
//	}
//	for(auto& c : children){
//		p.add("children.child", c);
//	}
//	return p;
//}

//void Descriptor::Constraint::load(pt::ptree p){
//	_src = p.get<string>("src");
//	_dest = p.get<string>("dest");
//
//	boost::optional<const pt::ptree&> opt_child;
//
//	opt_child = p.get_child_optional( "d_lo" );
//	if(opt_child){
//		d_lo = p.get<int>("d_lo");
//	}
//	opt_child = p.get_child_optional( "d_hi" );
//	if(opt_child){
//		d_hi = p.get<int>("d_hi");
//	}
//}

//pt::ptree Descriptor::Constraint::dump(){
//	pt::ptree p;
//	p.put("src", _src);
//	p.put("dest", _dest);
//	if(d_lo>INT_MIN){
//		p.put("d_lo", d_lo);
//	}
//	if(d_hi<INT_MAX){
//		p.put("d_hi", d_hi);
//	}
//	return p;
//}

//void Descriptor::Operation::add_child(const string name_){
//	bool flag=false;
//	for(auto& c:children){
//		if(c==name_){
//			flag=true;
//		}
//	}
//	if(!flag){
//		children.push_back(name_);
//	}
//}
//void Descriptor::Operation::add_children(vector<string> name_list_){
//	for(auto& n:name_list_){
//		add_child(n);
//	}
//}

void Descriptor::load(pt::ptree p) 
{
		 

	for (pt::ptree::value_type &v : p.get_child("Descriptor.Operations"))
	{
		LOG(DEBUG) << v.first;
		if (v.first == "Operation")
		{
			LOG(DEBUG)<< "sdsdsd" ;
			string _nameA = v.second.get<string>("name","");
			boost::optional <const pt::ptree&> opt_p; 
			int schedule_time = -1;
			Rot _rot;
			if(opt_p = v.second.get_child_optional("schedule_time"))
				{
					int schedule_time = v.second.get<int>("schedule_time",0);

				}
			for (pt::ptree::value_type &v1 :v.second.get_child("Rot"))
			{
				if(v1.first == "timetable")
				{
					string rs = v1.second.get<string>("<xmlattr>.rs","");
					Timetable tb;
					for (pt::ptree::value_type &v2 :v1.second.get_child(""))
					{
						if (v2.first == "Frame")
						{
							int t0 = v2.second.get<int>("<xmlattr>.t0",0);
							int t1 = v2.second.get<int>("<xmlattr>.t1",0);
							int sn = v2.second.get<int>("<xmlattr>.t2",0);
							Frame f(t0,t1,sn);
							tb.push_back(f);

						}
					}
					tb.merge();
					_rot[rs]= tb;
				}
			}
			//LOG(DEBUG) << _nameA ;
			//LOG(DEBUG) <<schedule_time;
			Operation operation_a(_nameA,schedule_time, _rot.convert_to_map());
			add_operation(operation_a);	
		}
	}
	for (pt::ptree::value_type &s :p.get_child("Descriptor.Constraints"))
	{
		if(s.first == "Constraint")
		{
			string _src = s.second.get<string>("src");
			string _dest = s.second.get<string>("dest");
			int d_lo = s.second.get<int>("d_lo",INT_MIN);
			int d_hi = s.second.get<int>("d_hi",INT_MAX);
			Constraint constraint_a(_src, _dest, d_lo, d_hi);
			add_constraint(constraint_a);
		}


	}
	
}



pt::ptree Descriptor::dump()
{
	pt::ptree p;
	return p;
}

void Descriptor::add_operation(Operation op_)
{
	auto find = _operations.find(op_.name());
	if (find != _operations.end())
	{
		LOG(WARNING) << "Overwrite operation " << op_.name();
	}
	_operations[op_.name()] = op_;
}

void Descriptor::add_constraint(Constraint c_)
{
	auto find_src = _operations.find(c_.src());
	auto find_dest = _operations.find(c_.dest());
	CHECK_NE(find_src, _operations.end()) << "Constraint " << c_.src() << "->" << c_.dest() << " is invalid, operation " << c_.src() << "does not exist!";
	CHECK_NE(find_dest, _operations.end()) << "Constraint " << c_.src() << "->" << c_.dest() << " is invalid, operation " << c_.dest() << "does not exist!";
	CHECK_GE(c_.d_hi, c_.d_lo) << "Constraint " << c_.src() << "->" << c_.dest() << " is invalid, illegl delay!";
	_constraints[c_.src() + "_" + c_.dest()] = c_;
	_src_constraint_index[c_.dest()].push_back(&_constraints[c_.src() + "_" + c_.dest()]);
	_dest_constraint_index[c_.src()].push_back(&_constraints[c_.src() + "_" + c_.dest()]);
}

Operation Descriptor::get_operation(const string name_)
{
	auto find = _operations.find(name_);
	CHECK_NE(find, _operations.end());
	return _operations[name_];
}
Operation &Descriptor::get_mutable_operation(const string name_)
{
	auto find = _operations.find(name_);
	CHECK_NE(find, _operations.end());
	return _operations[name_];
}
Constraint Descriptor::get_constraint(const string src_, const string dest_)
{
	auto find = _constraints.find(src_ + "_" + dest_);
	CHECK_NE(find, _constraints.end());
	return _constraints[src_ + "_" + dest_];
}
Constraint &Descriptor::get_mutable_constraint(const string src_, const string dest_)
{
	auto find = _constraints.find(src_ + "_" + dest_);
	CHECK_NE(find, _constraints.end());
	return _constraints[src_ + "_" + dest_];
}

vector<Constraint *> Descriptor::get_src_constraints(const string dest_)
{
	auto find = _src_constraint_index.find(dest_);
	if (find == _src_constraint_index.end())
	{
		return {};
	}
	else
	{
		return _src_constraint_index[dest_];
	}
}
vector<Constraint *> Descriptor::get_dest_constraints(const string src_)
{
	auto find = _dest_constraint_index.find(src_);
	if (find == _dest_constraint_index.end())
	{
		return {};
	}
	else
	{
		return _dest_constraint_index[src_];
	}
}

vector<Constraint *> Descriptor::get_all_constraints()
{
	vector<Constraint *> c_list;
	;
	for (auto &c : _constraints)
	{
		c_list.push_back(&(c.second));
	}
	return c_list;
}

bool Descriptor::check_operation(const string name_)
{
	auto find = _operations.find(name_);
	if (find == _operations.end())
	{
		return false;
	}
	return true;
}
bool Descriptor::check_constraint(const string src_, const string dest_)
{
	auto find = _constraints.find(src_ + "_" + dest_);
	if (find == _constraints.end())
	{
		return false;
	}
	return true;
}

void Descriptor::remove_constraint(const string src_, const string dest_)
{
	auto find = _constraints.find(src_ + "_" + dest_);
	if (find != _constraints.end())
	{
		_constraints.erase(src_ + "_" + dest_);
	}
}

void Descriptor::fill_mark(map<BIR::Instruction *, string> &mark_map, string vertex_name, string mark_id)
{
	if (vertex_name == "")
	{
		vertex_name = _entry;
	}

	Operation o = get_operation(vertex_name);
	for (auto &pair : mark_map)
	{
		if (pair.first->timelabels[0] == o.name())
		{
			mark_map[pair.first] = mark_id;
			break;
		}
	}
	for (auto &name : o.children0)
	{
		fill_mark(mark_map, name, mark_id + "0");
	}
	for (auto &name : o.children1)
	{
		fill_mark(mark_map, name, mark_id + "1");
	}
}

void Descriptor::fill_timestamp()
{
	for (auto &e : _instr_lists)
	{
		int size_before = e.second.size();
		map<int, BIR::Instruction *> instr_map;
		vector<BIR::Instruction *> instr_vec;
		map<BIR::Instruction *, string> mark_map;
		for (auto &instr_ : e.second)
		{
			for (int i = 0; i < BIR::Instruction::TOTAL_TIME; i++)
			{
				instr_->timestamps[i] = get_operation(instr_->timelabels[i]).scheduled_time;
			}

			if (instr_->timestamps[BIR::Instruction::FETCH_TIME] != instr_->timestamps[BIR::Instruction::ISSUE_TIME])
			{
				instr_->active_shadow_register = false;
			}

			instr_->minScheduledClkCycle = instr_->timestamps[BIR::Instruction::FETCH_TIME];
			instr_->maxScheduledClkCycle = instr_->timestamps[BIR::Instruction::END_TIME];
			if (instr_->kind() == bktRefiInstruction)
			{
				BIR::RefiInstruction *refi_instr = static_cast<BIR::RefiInstruction *>(instr_);
				refi_instr->initialDelay.value = instr_->timestamps[BIR::Instruction::ACTIVE_TIME] - instr_->timestamps[BIR::Instruction::ARRIVE_TIME];
				refi_instr->initialDelay.isStatic = true;
			}
			else if (instr_->kind() == bktSRAMInstruction)
			{
				BIR::SRAMInstruction *sram_instr = static_cast<BIR::SRAMInstruction *>(instr_);
				sram_instr->initialDelay.value = instr_->timestamps[BIR::Instruction::ACTIVE_TIME] - instr_->timestamps[BIR::Instruction::ARRIVE_TIME];
				sram_instr->initialDelay.isStatic = true;
			}
			else if (instr_->kind() == bktWaitInstruction)
			{
				BIR::WaitInstruction *wait_instr = static_cast<BIR::WaitInstruction *>(instr_);
				wait_instr->numberOfCycles.isStatic = true;
				wait_instr->numberOfCycles.value = instr_->timestamps[BIR::Instruction::END_TIME] - instr_->timestamps[BIR::Instruction::ACTIVE_TIME];
			}
			instr_map[instr_->timestamps[BIR::Instruction::FETCH_TIME]] = instr_;
			instr_vec.push_back(instr_);
			mark_map[instr_] = "-1";
		}
		std::sort(instr_vec.begin(), instr_vec.end(),
							[](const BIR::Instruction *a, const BIR::Instruction *b) {
								return a->timestamps[BIR::Instruction::FETCH_TIME] < b->timestamps[BIR::Instruction::FETCH_TIME];
							});
		fill_mark(mark_map);

		for (int i = instr_vec.size() - 1; i >= 0; i--)
		{
			BIR::Instruction *instr = instr_vec[i];
			if (instr->kind() == BIR::BIREnumerations::bktBranchInstruction)
			{
				BIR::BranchInstruction *branch_instr = static_cast<BIR::BranchInstruction *>(instr);
				BIR::JumpInstruction *jump_instr = static_cast<BIR::JumpInstruction *>(branch_instr->falseAddressInstruction);
				BIR::WaitInstruction *wait_instr = static_cast<BIR::WaitInstruction *>(jump_instr->jumpAddressInstruction);
				CHECK(branch_instr);
				CHECK(jump_instr);
				CHECK(wait_instr);
				string mark_0 = mark_map[branch_instr] + "0"; // prefix of then part
				string mark_1 = mark_map[branch_instr] + "1"; // prefix of else part
				int j = i;
				for (; j < instr_vec.size(); j++)
				{
					if (instr_vec[j] == wait_instr)
					{
						break;
					}
				}
				vector<BIR::Instruction *> instr_vec_tmp;
				for (int k = i + 1; k < j; k++)
				{
					if (strncmp(mark_map[instr_vec[k]].c_str(), mark_0.c_str(), strlen(mark_0.c_str())) == 0)
					{
						instr_vec_tmp.push_back(instr_vec[k]);
					}
				}
				for (int k = i + 1; k < j; k++)
				{
					if (strncmp(mark_map[instr_vec[k]].c_str(), mark_1.c_str(), strlen(mark_1.c_str())) == 0)
					{
						instr_vec_tmp.push_back(instr_vec[k]);
					}
				}
				CHECK_EQ(instr_vec_tmp.size(), j - i - 1);
				for (int k = 0; k < j - i - 1; k++)
				{
					instr_vec[k + i + 1] = instr_vec_tmp[k];
				}
			}
		}

		e.second = instr_vec;

		// int size_after = instr_map.size();
		// CHECK_EQ(size_before, size_after)
		// 		<< "Conflict scheduling time. Sorted list size doesn't match it unsorted size!"
		// 		<< size_before << "!=" << size_after;
		// std::sort(e.second.begin(), e.second.end(),
		// 					[](const BIR::Instruction *a, const BIR::Instruction *b) {
		// 						return a->issue_time < b->issue_time;
		// 					});
	}

	struct Prop
	{
		int start;
		int end;
		int iteration;
		int duration;
		int cursor;
	};

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, Prop> Tree;
	Tree loop_tree;
	map<LoopInstruction *, Tree::vertex_descriptor> loop2vertex;
	map<Tree::vertex_descriptor, LoopInstruction *> vertex2loop;
	for (auto &e : _instr_lists)
	{

		stack<LoopInstruction *> curr_loop_h;
		for (auto &instr : e.second)
		{
			if (instr->kind() == BIR::BIREnumerations::bktLoopInstruction)
			{
				BIR::LoopInstruction *ii = static_cast<BIR::LoopInstruction *>(instr);
				Prop p;
				if (ii->isStatic)
				{
					p.start = ii->timestamps[BIR::Instruction::FETCH_TIME];
					p.end = -1;
					p.iteration = ii->iterationNumber;
					p.duration = 0;
					p.cursor = ii->timestamps[BIR::Instruction::FETCH_TIME];
				}
				else
				{
					p.start = -1;
					p.end = -1;
					p.iteration = -1;
					p.duration = -1;
					p.cursor = -1;
				}

				Tree::vertex_descriptor vd = add_vertex(p, loop_tree);
				loop2vertex[ii] = vd;
				vertex2loop[vd] = ii;

				if (!curr_loop_h.empty())
				{
					add_edge(loop2vertex[curr_loop_h.top()], vd, loop_tree);
				}
				curr_loop_h.push(ii);
			}
		}
	}

	for (auto &e : _instr_lists)
	{
		for (auto &instr : e.second)
		{
			if (instr->kind() == BIR::BIREnumerations::bktRefiInstruction)
			{
				RefiInstruction *refi_instr = static_cast<RefiInstruction *>(instr);
				if (refi_instr->corresponding_looph_l1)
				{
					refi_instr->middleDelay.isStatic = true;
					refi_instr->middleDelay.value = loop_tree[loop2vertex[static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l1)]].duration - 1;
					CHECK_GT(static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l1)->isStatic, 0) << "Can't move REFI instruction across dynamic loop, something wrong!";
				}
				if (refi_instr->corresponding_looph_l2)
				{
					refi_instr->repetitionDelay.isStatic = true;
					refi_instr->repetitionDelay.value = loop_tree[loop2vertex[static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l2)]].duration - ((refi_instr->middleDelay.value + 1) * refi_instr->numberOfAddress.value + 1);
					CHECK_GT(static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l2)->isStatic, 0) << "Can't move REFI instruction across dynamic loop, something wrong!";
				}
			}
			else if (instr->kind() == BIR::BIREnumerations::bktSRAMInstruction)
			{
				SRAMInstruction *refi_instr = static_cast<SRAMInstruction *>(instr);
				if (refi_instr->corresponding_looph_l1)
				{
					refi_instr->loop1Delay.isStatic = true;
					refi_instr->loop1Delay.value = loop_tree[loop2vertex[static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l1)]].duration - 1;
					CHECK_GT(static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l1)->isStatic, 0) << "Can't move REFI instruction across dynamic loop, something wrong!";
				}
				if (refi_instr->corresponding_looph_l2)
				{
					refi_instr->loop2Delay.isStatic = true;
					refi_instr->loop2Delay.value = loop_tree[loop2vertex[static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l2)]].duration - ((refi_instr->loop1Delay.value + 1) * refi_instr->loop1Delay.value + 1);
					CHECK_GT(static_cast<LoopInstruction *>(refi_instr->corresponding_looph_l2)->isStatic, 0) << "Can't move REFI instruction across dynamic loop, something wrong!";
				}
			}
		}
	}
}

string Descriptor::generate_dot_graph_for_operation(string operation_, std::set<string> &operation_set_)
{
	string str = "";
	Operation o = get_operation(operation_);
	if (o.scheduled_time >= 0 && o.scheduled_time < INT_MAX)
	{
		return str;
	}

	if (o.children0.size() == 0 && o.children1.size() == 0)
	{
		if (o.dont_touch)
		{
			str += o.name() + "[shape=box, color=green, label=\"" + o.name() + "\"];\n";
		}
		else
		{
			str += o.name() + "[shape=box, color=blue, label=\"" + o.name() + "\"];\n";
		}
	}
	else
	{
		str += o.name() + "[shape=box, peripheries=2, color=lightblue, label=\"" + o.name() + "\"];\n";

		if (o.children0.size() > 0)
		{
			string new_str = "";
			for (int j = 0; j < o.children0.size(); j++)
			{
				operation_set_.insert(o.children0[j]);
				new_str += generate_dot_graph_for_operation(o.children0[j], operation_set_);
			}
			if (new_str != "")
			{
				str += "subgraph cluster_" + o.name() + "_0 {\n";
				str += "cluster_" + o.name() + "_0" + "_entry [shape=diamond, style=filled, fillcolor=yellow, label=0];\n";
				str += new_str;
				str += "}\n";
				str += o.name() + "->" + "cluster_" + o.name() + "_0" + "_entry" + "[color=lightblue];\n";
			}
		}
		if (o.children1.size() > 0)
		{
			string new_str = "";
			for (int j = 0; j < o.children1.size(); j++)
			{
				operation_set_.insert(o.children1[j]);
				str += generate_dot_graph_for_operation(o.children1[j], operation_set_);
			}
			if (new_str != "")
			{
				str += "subgraph cluster_" + o.name() + "_1 {\n";
				str += "cluster_" + o.name() + "_1" + "_entry [shape=diamond, style=filled, fillcolor=yellow, label=1];\n";
				str += new_str;
				str += "}\n";
				str += o.name() + "->" + "cluster_" + o.name() + "_1" + "_entry" + "[color=lightblue];\n";
			}
		}
	}
	return str;
}

string Descriptor::generate_dot_graph()
{
	std::set<string> operation_set;
	string str = "digraph g {\n";
	for (auto &o : _operations)
	{
		if (o.second.name() == _entry)
		{
			operation_set.insert(o.second.name());
			str += generate_dot_graph_for_operation(o.second.name(), operation_set);
		}
	}

	for (auto &c : _constraints)
	{
		if (operation_set.find(c.second.src()) != operation_set.end() && operation_set.find(c.second.dest()) != operation_set.end())
		{
			str += c.second.src() + " -> " + c.second.dest() + "[";
			string hi = "+INF";
			string lo = "-INF";
			if (c.second.d_lo > INT_MIN)
			{
				lo = to_string(c.second.d_lo);
			}
			if (c.second.d_hi < INT_MAX)
			{
				hi = to_string(c.second.d_hi);
			}
			str += "label=\"[" + lo + "," + hi + "]\"";
			str += ", style=dashed, color=red";
			if (c.second.src_hook == Constraint::HOOK_END)
			{
				str += ", taillabel=\"E\"";
			}
			if (c.second.dest_hook == Constraint::HOOK_END)
			{
				str += ", headlabel=\"E\"";
			}
			str += "];\n";
		}
	}

	str += "}";

	return str;
}

string Descriptor::generate_dot_graph(string name_)
{
	std::set<string> operation_set;
	string str = "digraph g {\n";
	str += generate_dot_graph_for_operation(name_, operation_set);

	for (auto &c : _constraints)
	{
		if (operation_set.find(c.second.src()) != operation_set.end() && operation_set.find(c.second.dest()) != operation_set.end())
		{
			str += c.second.src() + " -> " + c.second.dest() + "[";
			string hi = "+INF";
			string lo = "-INF";
			if (c.second.d_lo > INT_MIN)
			{
				lo = to_string(c.second.d_lo);
			}
			if (c.second.d_hi < INT_MAX)
			{
				hi = to_string(c.second.d_hi);
			}
			str += "label=\"[" + lo + "," + hi + "]\"";
			str += ", style=dashed, color=red";
			if (c.second.src_hook == Constraint::HOOK_END)
			{
				str += ", taillabel=\"E\"";
			}
			if (c.second.dest_hook == Constraint::HOOK_END)
			{
				str += ", headlabel=\"E\"";
			}
			str += "];\n";
		}
	}

	str += "}";

	return str;
}

string Descriptor::generate_dot_graph(std::set<string> names_)
{
	std::set<string> operation_set;
	string str = "digraph g {\n";

	for (auto name : names_)
	{
		operation_set.insert(name);
		str += generate_dot_graph_for_operation(name, operation_set);
	}

	for (auto &c : _constraints)
	{
		if (operation_set.find(c.second.src()) != operation_set.end() && operation_set.find(c.second.dest()) != operation_set.end())
		{
			str += c.second.src() + " -> " + c.second.dest() + "[";
			string hi = "+INF";
			string lo = "-INF";
			if (c.second.d_lo > INT_MIN)
			{
				lo = to_string(c.second.d_lo);
			}
			if (c.second.d_hi < INT_MAX)
			{
				hi = to_string(c.second.d_hi);
			}
			str += "label=\"[" + lo + "," + hi + "]\"";
			str += ", style=dashed, color=red";
			if (c.second.src_hook == Constraint::HOOK_END)
			{
				str += ", taillabel=\"E\"";
			}
			if (c.second.dest_hook == Constraint::HOOK_END)
			{
				str += ", headlabel=\"E\"";
			}
			str += "];\n";
		}
	}

	str += "}";

	return str;
}

string Descriptor::generate_schedule_table()
{
	string str = "";
	for (auto &il : _instr_lists)
	{
		str += "CELL " + il.first + "\n";
		str += "-------------------------------------------------------------------\n";
		for (int i = 0; i < il.second.size(); i++)
		{
			str += to_string(i) + "\t:\t" + il.second[i]->kindStr() + "\t\t" + to_string(il.second[i]->timestamps[BIR::Instruction::FETCH_TIME]) + "\t\t" + to_string(il.second[i]->timestamps[BIR::Instruction::ISSUE_TIME]) + "\t\t" + to_string(il.second[i]->timestamps[BIR::Instruction::ARRIVE_TIME]) + "\t\t" + to_string(il.second[i]->timestamps[BIR::Instruction::ACTIVE_TIME]) + "\t\t" + to_string(il.second[i]->timestamps[BIR::Instruction::END_TIME]) + "\n";
		}
		str += "\n";
	}
	return str;
}

vector<string> Descriptor::get_all_operation_names()
{
	vector<string> vec;
	for (auto &o : _operations)
	{
		vec.push_back(o.first);
	}
	return vec;
}

} // namespace schedule
} // namespace vesyla
