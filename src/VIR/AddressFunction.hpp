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

#ifndef __VESYLA_VIR_ADDRESS_FUNCTION_HPP__
#define __VESYLA_VIR_ADDRESS_FUNCTION_HPP__

#include <util/Common.hpp>
#include "ForStatement.hpp"
#include "Identifier.hpp"
#include <algorithm>

//namespace vesyla{
namespace VIR
{
class AddressFunction : VIRBase
{
private:
	Identifier *_raccu_var;
	int _max_nonloop_level;
	int _b;
	vector<int> _a;
	vector<int> _n;
	vector<VIR::ForStatement *> _l;

public:
	AddressFunction(int max_nonloop_level_ = 0) : _max_nonloop_level(max_nonloop_level_)
	{
		CHECK_GE(max_nonloop_level_, 0);
		_b = 0;
		_raccu_var = NULL;
	}
	~AddressFunction() {}

	int b();
	void b(int b_);
	int level();
	int a(int i_);
	int n(int i_);
	VIR::ForStatement *l(int i_);
	void add_level(int a_, int n_, VIR::ForStatement *l_);
	Identifier *raccu_var()
	{
		return _raccu_var;
	}
	void raccu_var(Identifier *r_)
	{
		_raccu_var = r_;
	}
	bool is_raccu_var()
	{
		if (_raccu_var == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool is_constant()
	{
		if (_a.size() == 0 && _n.size() == 0 && _l.size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void disable_level(int i)
	{
		CHECK_LT(i, _a.size());
		_a[i] = 0;
		_n[i] = 0;
		_l[i] = NULL;
	}
	void minus(AddressFunction af_)
	{
		_b -= af_.b();
		for (int i = 0; i < af_.level(); i++)
		{
			if (af_.l(i) != NULL)
			{
				bool flag_found = false;
				for (int j = 0; j < _l.size(); j++)
				{
					if (af_.l(i) == _l[j])
					{
						_a[j] -= af_.a(i);
						af_.disable_level(i);
						flag_found = true;
						break;
					}
				}
				if (flag_found != true)
				{
					add_level(-af_.a(i), af_.n(i), af_.l(i));
				}
			}
		}
		vector<int> aa;
		vector<int> nn;
		vector<ForStatement *> ll;
		for (int i = 0; i < _a.size(); i++)
		{
			if (_a[i] != 0 && _l[i] != NULL)
			{
				aa.push_back(_a[i]);
				nn.push_back(_n[i]);
				ll.push_back(_l[i]);
			}
		}
		_a = aa;
		_n = nn;
		_l = ll;
	}

	void multiply(int x_)
	{
		_b *= x_;
		for (int i = 0; i < level(); i++)
		{
			_a[i] *= x_;
		}
	}
	void div(int x_)
	{
		_b /= x_;
		for (int i = 0; i < level(); i++)
		{
			_a[i] /= x_;
		}
	}

	void plus(int x_)
	{
		_b += x_;
	}

	void minus(int x_)
	{
		_b -= x_;
	}

	void dump()
	{
		cout << "-----------------------" << endl;
		if (is_raccu_var())
		{
			cout << "raccu_var=" << _raccu_var->name();
		}
		else
		{
			cout << "b=" << _b << endl;
			for (int i = 0; i < _a.size(); i++)
			{
				cout << "\ta=" << _a[i] << ", n=" << _n[i] << ", l=" << _l[i]->loopVariable()->name() << endl;
			}
		}
		cout << "-----------------------" << endl;
	}
};
} // namespace VIR
//}

#endif // __VESYLA_VIR_ADDRESS_FUNCTION_HPP__