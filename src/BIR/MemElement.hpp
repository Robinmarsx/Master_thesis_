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

#ifndef __MemElement_h__
#define __MemElement_h__

#include "BIRBase.hpp"
#include "VIR/ObjectDeclaration.hpp"

namespace BIR
{
	// class BIRBase;
	class MemElement;
}

namespace BIR
{
	class MemElement: public BIR::BIRBase
	{
		private: VIR::ObjectDeclaration * _correspondingObject;
		private: vector<int> _intValues;
		private: bool _hasInitialValue;
		private: vector<float> _realValues;
		private: bool _isFixedPoint;

		public: MemElement(int width_);

		public: VIR::ObjectDeclaration * correspondingObject() const;

		public: void correspondingObject(VIR::ObjectDeclaration * correspondingObject_);

		public: vector<int>& intValues();

		public: bool hasInitialValue() const;

		public: void hasInitialValue(bool hasInitialValue_);

		public: bool isFixedPoint() const;

		public: void isFixedPoint(bool isFixedPoint_);

		public: vector<float>& realValues();
	};
}

#endif
