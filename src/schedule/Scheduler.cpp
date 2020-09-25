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

#include "Scheduler.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#define SCHEDULE_ENGINE_NAME ResourcePredictEngine
#define SCHEDULE_ENGINE_NAME_STR "ResourcePredictEngine"

namespace vesyla {
namespace schedule {

using namespace boost;
using namespace boost::property_tree;

Scheduler::Scheduler() {
    _id_counter = 0;
    _graph_counter = 0;
    _sn_counter = 0;
}

Scheduler::Scheduler(string xml_file){
	// Write your code here 
	//how to read from xml , transfer to descrip , boost lib process- property tree,  
  ptree pt;
  read_xml(xml_file,pt);

  _desc.load(pt);





  
  



}

void Scheduler::schedule() {
  vector<string> name_list = _desc.get_all_operation_names();
  LOG(INFO) << "Using schedule engine : " << SCHEDULE_ENGINE_NAME_STR;
  SCHEDULE_ENGINE_NAME eng(&_desc);
  if (!eng.schedule_graph(name_list)) {
    LOG(FATAL) << "Failed!";
  }
  LOG(INFO) << "Schedule subgraph done! ";
}

} // namespace schedule
} // namespace vesyla
