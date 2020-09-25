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

#include "GlobalVar.hpp"

namespace vesyla
{
namespace util
{

map<string, GlobalVar::glvar_t> GlobalVar::_pool;

bool GlobalVar::get(const string key, glvar_t &val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	if (it != _pool.end())
	{
		val = it->second;
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::getb(const string key, bool &val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	if (it != _pool.end())
	{
		val = it->second.b;
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::geti(const string key, int &val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	if (it != _pool.end())
	{
		val = it->second.i;
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::getf(const string key, float &val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	if (it != _pool.end())
	{
		val = it->second.f;
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::gets(const string key, string &val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	if (it != _pool.end())
	{
		val = it->second.s;
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::put(const string key, const glvar_t val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	_pool[key] = val;
	if (it != _pool.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::putb(const string key, const bool val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	glvar_t v;
	v.b = val;
	_pool[key] = v;
	if (it != _pool.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::puti(const string key, const int val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	glvar_t v;
	v.i = val;
	_pool[key] = v;
	if (it != _pool.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::putf(const string key, const float val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	glvar_t v;
	v.f = val;
	_pool[key] = v;
	if (it != _pool.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalVar::puts(const string key, const string val)
{
	std::map<string, glvar_t>::iterator it;
	it = _pool.find(key);
	glvar_t v;
	strncpy(v.s, val.c_str(), sizeof(v.s));
	_pool[key] = v;
	if (it != _pool.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

} // namespace util
} // namespace vesyla
