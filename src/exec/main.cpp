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

#include "main.hpp"

using namespace std;
using namespace vesyla;

// Initialize logging system
INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
	// setup logger
	el::Configurations c;
	c.setToDefault();
	c.parseFromText(LOGGING_CONF);
	el::Loggers::reconfigureLogger("default", c);
	el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
	// + command read variable parameter arguments
	// schedule
	string xml_file_path = "/home/xu/Desktop/olll/testA.xml"; //xml prebvious one 
	vesyla::schedule::Scheduler s(xml_file_path);
	s.schedule();
	
	// print out schecule result here...

	return 0;
}
