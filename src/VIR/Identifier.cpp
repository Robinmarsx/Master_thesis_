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
#include <string>
using namespace std;

#include "Identifier.hpp"
#include "Name.hpp"
#include "DependencyType.hpp"

VIR::Identifier::Identifier()
{
	_object = 0;
	_dependentTo = 0;
	_dependencyType = VIR::VirEnumerations::dtNone;
	_indexDependency = 0;
	is_temp_var = false;
}

string VIR::Identifier::name() const
{
	return _name;
}

void VIR::Identifier::name(const string &name_)
{
	_name = name_;
}

VIR::ObjectDeclaration *VIR::Identifier::object() const
{
	return _object;
}

void VIR::Identifier::object(VIR::ObjectDeclaration *object_)
{
	_object = object_;
}

VIR::AssignmentStatement *VIR::Identifier::dependentTo() const
{
	return _dependentTo;
}

void VIR::Identifier::dependentTo(VIR::AssignmentStatement *dependentTo_)
{
	_dependentTo = dependentTo_;
}

VIR::VirEnumerations::DependencyType VIR::Identifier::dependencyType() const
{
	return _dependencyType;
}

void VIR::Identifier::dependencyType(
		VIR::VirEnumerations::DependencyType dependencyType_)
{
	_dependencyType = dependencyType_;
}

VIR::Statement *VIR::Identifier::indexDependency() const
{
	return _indexDependency;
}

void VIR::Identifier::indexDependency(VIR::Statement *indexDependency_)
{
	_indexDependency = indexDependency_;
}
