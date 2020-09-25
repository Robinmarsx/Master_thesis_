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

#ifndef __VESYLA_SCHEDULE_SCHEDULER_HPP__
#define __VESYLA_SCHEDULE_SCHEDULER_HPP__

#include "Descriptor.hpp"
#include "Frame.hpp"
#include "ResourcePredictEngine.hpp"
#include "Rot.hpp"
#include "Timetable.hpp"
#include <util/Common.hpp>
#include <util/Interval.hpp>
#include <util/bglex/simple_cycles.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <boost/graph/transitive_reduction.hpp>

namespace vesyla {
namespace schedule {

typedef string Vertex;
typedef pair<string, string> Edge;

class Scheduler {

private:
  Descriptor _desc;
  int _id_counter;
  int _graph_counter;
  int _sn_counter;

public:
  Scheduler();
  Scheduler(string xml_file);

  void schedule();

private:
  void to_dot_graph(Descriptor &d_, int stage_);
  void gen_script();

};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_SCHEDULER_HPP__
