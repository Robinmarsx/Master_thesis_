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

#include "Engine.hpp"

namespace vesyla {
namespace schedule {
Engine::Engine() { _ptr_desc = NULL; }
Engine::Engine(Descriptor *ptr_desc_) { _ptr_desc = ptr_desc_; }
Engine::~Engine() {}
bool Engine::schedule_graph(vector<string> name_list_) {}
bool Engine::check_graph(vector<string> name_list_) {
  return schedule_graph(name_list_);
}
Descriptor *Engine::desc() { return _ptr_desc; }
} // namespace schedule
} // namespace vesyla
