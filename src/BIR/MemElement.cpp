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
#include <vector>
using namespace std;

#include "MemElement.hpp"
#include "BIRBase.hpp"

BIR::MemElement::MemElement(int width_)
{
	_correspondingObject = 0;
	_hasInitialValue = false;
	_isFixedPoint = false;
	
	// 16 is the memory word split factor according to the register file word size
	_intValues.resize(width_/16, 0);
	_realValues.resize(width_/16, 0);
}

VIR::ObjectDeclaration * BIR::MemElement::correspondingObject() const
{
	return _correspondingObject;
}

void BIR::MemElement::correspondingObject(VIR::ObjectDeclaration * correspondingObject_)
{
	_correspondingObject = correspondingObject_;
}

vector<int>& BIR::MemElement::intValues()
{
	return _intValues;
}

bool BIR::MemElement::hasInitialValue() const
{
	return _hasInitialValue;
}

void BIR::MemElement::hasInitialValue(bool hasInitialValue_)
{
	_hasInitialValue = hasInitialValue_;
}

bool BIR::MemElement::isFixedPoint() const
{
	return _isFixedPoint;
}

void BIR::MemElement::isFixedPoint(bool isFixedPoint_)
{
	_isFixedPoint = isFixedPoint_;
}

vector<float>& BIR::MemElement::realValues()
{
	return _realValues;
}

