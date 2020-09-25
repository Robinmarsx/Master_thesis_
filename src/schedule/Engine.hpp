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

#ifndef __VESYLA_SCHEDULE_ENGINE_HPP__
#define __VESYLA_SCHEDULE_ENGINE_HPP__

#include "Descriptor.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>

namespace vesyla {
namespace schedule {
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                              Operation, Constraint>
    Graph;
class Engine {
protected:
  Descriptor *_ptr_desc;

public:
  Engine();
  Engine(Descriptor *ptr_desc_);
  ~Engine();

public:
  virtual bool schedule_graph(vector<string> name_list_) = 0;
  bool check_graph(vector<string> name_list_);
  Descriptor *desc();
};
} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_ENGINE_HPP__