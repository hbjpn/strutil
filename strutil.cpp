/**
 *
 * Copyright (C) 2012-2013 Hiroyuki Baba, All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License or any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR POURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"

namespace strutil
{

/**
 * Remove white space, tab, \n and \r from right side of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string rtrim(const std::string& s)
{
    int i = s.size() - 1;

    while ( i >= 0 && ( s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r') ) i--;

    return s.substr(0, i+1);
}

/**
 * Remove white space, tab, \n and \r from left side of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string ltrim(const std::string& s)
{
    int i = 0;
    while ( i < s.size() && ( s[i] == ' ' || s[i] == '\t'  || s[i] == '\n' || s[i] == '\r') ) i++;

    return s.substr(i, s.size() - i);
}

/**
 * Remove white space, tab, \n and \r from both right and left sides of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string trim(const std::string& s)
{
	return ltrim(rtrim(s));
}

/**
 * Join specified strings with delimiter
 *
 * @param delim Delimiter string
 * @param s Array of input strings
 * @param Size of s
 * @return Joined string
 */
std::string join(const std::string& delim, const std::string* s, int size)
{
	int retLen = 0;
	for(int i = 0; i < size; ++i)
	{
		retLen += s[i].size();
	}
	retLen += delim.size() * (size-1);

	std::string ret;
	ret.reserve(retLen);

	for(int i = 0; i < size; ++i)
	{
		ret += s[i];
		if( i < size-1 )
		{
			ret += delim;
		}
	}
	return ret;
}

/**
 * Join specified strings with delimiter
 *
 * @param delim Delimiter string
 * @param s Array of input strings
 * @param Size of s
 * @return Joined string
 */
std::string join(const std::string& delim, const std::vector<std::string>& s)
{
	return join(delim, &s[0], s.size());
}

/**
 * Test if s0 is contained in s1
 *
 * return true if contained, otherwise false
 */
bool contained(const std::string& s0, const std::string& s1)
{
	return std::string::npos != s1.find(s0, 0);
}

/**
 * Test if c is contained in s1
 *
 * return true if contained, otherwise false
 */
bool contained(char c, const std::string& s1)
{
	return std::string::npos != s1.find(c, 0);
}

/**
 * Split specified string with specified delimiter
 *
 * @param s Input string
 * @param delim Delimiter string
 * @return vector of string
 *
 * @note Each characters in delim is considered as delimiter character
 */
std::vector<std::string> split(const std::string& s, const std::string& delim)
{
    std::vector<std::string> strings;
    std::string tmp;

    for(int i = 0; i < s.size(); ++i)
    {
        if(contained(s[i], delim))
        {
            if(tmp.length() != 0)
            {
                strings.push_back(tmp);
            }
            tmp = "";
        }else
        {
            tmp += s[i];
        }
    }

    if(tmp.length() != 0)
    {
        strings.push_back(tmp);
    }

    return strings;
}

static void split_ibs0(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret)
{
	if(pc.i == s.size())
	{
		throw "Parse error";
	}
	else if(s[pc.i] == quote || s[pc.i] == '\\' || contained(s[pc.i], delim))
	{
		pc.tmp += s[pc.i];
		pc.i++;
		split_st(pc, s, delim, quote, ret);
	}else
	{
		throw "Parse error";
	}
}

static  void split_ibs1(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret)
{
	if(pc.i == s.size())
	{
		throw "Parse error";
	}
	else if(s[pc.i] == quote || s[pc.i] == '\\' || contained(s[pc.i], delim))
	{
		pc.tmp += s[pc.i];
		pc.i++;
		split_inq(pc, s, delim, quote, ret);
	}else
	{
		throw "Parse error";
	}
}


static void split_inq(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret)
{
	if(pc.i == s.size())
	{
		throw "Parse error";
	}else if(s[pc.i] == '\\')
	{
		pc.i++;
		split_ibs1(pc, s, delim, quote, ret);
	}else if(s[pc.i] == quote)
	{
		pc.i++;
		split_st(pc, s, delim, quote, ret);
	}else
	{
		pc.tmp += s[pc.i];
		pc.i++;
		split_inq(pc, s, delim, quote, ret);
	}
}

static void split_st(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret)
{
    if( pc.i == s.size() || contained(s[pc.i], delim) )
    {
		if(pc.tmp.length() != 0)
		{
			ret.push_back(pc.tmp);
		}
		pc.tmp = "";
		if(pc.i == s.size())
		{
			// Parse end
			return;
		}else
		{
			pc.i++;
			split_st(pc, s, delim, quote, ret);
		}
    }else if(s[pc.i] == '\\')
    {
    	pc.i++;
    	split_ibs0(pc, s, delim, quote, ret);
    }else if(s[pc.i] == quote)
    {
    	pc.i++;
    	split_inq(pc, s, delim, quote, ret);
    }else
    {
    	pc.tmp += s[pc.i];
    	pc.i++;
    	split_st(pc, s, delim, quote, ret);
    }
}

/**
 * Split specified string with specified delimiter considering quote symbol
 *
 * @param s Input string
 * @param delim Delimiter string
 * @param quote Single caracter used as quote
 * @return vector of string
 *
 * @note Each characters in delim is considered as delimiter character
 */
std::vector<std::string> split(const std::string& s, const std::string& delim, char quote)
{
	std::vector<std::string> ret;
	parsecontext pc;
	pc.i = 0;
	split_st(pc, s, delim, quote, ret);
	return ret;
}

/**
 * Convert string to double
 *
 * @param s String
 * @param success true if conversion succeed, otherwise false.
 *
 * @return Converted value if succeed, otherwise 0
 */
double toDouble(const std::string& s, bool& success)
{
    char* e;
    double v = strtod(s.c_str(), &e);

    if(*e == '\0')
    {
        success = true;
    }else
    {
        success = false;
    }

    return v;
}


/**
 * Convert string to decimal integer
 *
 * @param s String
 * @param success true if conversion succeed, otherwise false.
 *
 * @return Converted value if succeed, otherwise 0
 */
int toInt(const std::string& s, bool& success)
{
    char* e;
    int v = strtol(s.c_str(), &e, 10);

    if(*e == '\0')
    {
        success = true;
    }else
    {
        success = false;
    }

    return v;
}


/**
 * Format string of double value
 *
 * @param f Format string ( printf form )
 * @param v Value to convert
 *
 * @return Formatted string
 */
std::string format(const std::string& f, double v)
{
	char buf[128];
	snprintf(buf, sizeof(buf), f.c_str(), v);
	return std::string(buf);
}

/**
 * Format string of integer value
 *
 * @param f Format string ( printf form )
 * @param v Value to convert
 *
 * @return Formatted string
 */
std::string format(const std::string& f, int v)
{
	char buf[128];
	snprintf(buf, sizeof(buf), f.c_str(), v);
	return std::string(buf);
}

/**
 * Convert double value to string
 *
 * @param v Value to convert
 *
 * @return String
 */
std::string toString(double v)
{
	return format("%f", v);
}

/**
 * Convert integer value to string
 *
 * @param v Value to convert
 *
 * @return String
 */
std::string toString(int v)
{
	return format("%d", v);
}


} // namespace strutil


#if 1
#include <iostream>
int main(int argc, char** argv)
{
	char in[1024];
	std::cin.getline(in, sizeof(in));
	std::vector<std::string> ret = strutil::split(in, ",", '\"');
	std::cout << "input:[" << in << "]" << std::endl;
	for(int i = 0; i < ret.size(); ++i)
	{
		std::cout << i << " : " << ret[i] << std::endl;
	}
}
#endif
