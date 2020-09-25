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

#include <exception>
using namespace std;

#include "SliceName.hpp"
#include "Name.hpp"

VIR::SliceName::SliceName() {
	_indexInfo = 0;
}

VIR::Identifier * VIR::SliceName::prefix() const {
	return _prefix;
}

void VIR::SliceName::prefix(Identifier * prefix_) {
	_prefix = prefix_;
}

vector<VIR::Expression*> & VIR::SliceName::suffix() {
	return _suffix;
}

VIR::IndexInfo * VIR::SliceName::indexInfo() const {
	return _indexInfo;
}

void VIR::SliceName::indexInfo(VIR::IndexInfo * indexInfo_) {
	_indexInfo = indexInfo_;
}

