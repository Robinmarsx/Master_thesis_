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


#ifndef __DPUMode_h__
#define __DPUMode_h__

namespace BIR
{
	namespace BIREnumerations
	{
		// enum DPUMode;
	}
}

namespace BIR
{
	namespace BIREnumerations
	{
		enum DPUMode
		{
			dmUnspecified, dmAbsSubAcc, dmAdd, dmAddWithConstant, dmComparison, dmComparisonWithConstant, dmFFT1, dmFFT2, dmLoadConstant, dmMac, dmMax, dmMin, dmMult, dmPreservingMac, dmSub, dmSubAcc, dmSymMac, dmSymFirWithIMac, dmSymFirWithEMac, dmASymFirWithIMac, dmASymFirWithEMac, dmTwoAdders, dmTwoSubtractors, dmFourInputAdder, dmDiffOfSum, dmSumOfDiff, dmLFSR, dmShiftLeft, dmShiftRight, dmAndOr, dmAndOrWithStatusBit, dmReset,
			dmSigmoid, dmTanh
		};
	}
}

#endif
