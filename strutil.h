/**
 *
 * Copyright (C) 2012-2015 Hiroyuki Baba, All Rights Reserved.
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

#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>
#include <vector>


namespace strutil
{

/**
 * Remove white space, tab, \n and \r from right side of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string rtrim(const std::string& s);

/**
 * Remove white space, tab, \n and \r from left side of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string ltrim(const std::string& s);

/**
 * Remove white space, tab, \n and \r from both right and left sides of the specified string
 *
 * @param s Input string
 * @return Trimed string
 */
std::string trim(const std::string& s);

/**
 * Join specified strings with delimiter
 *
 * @param delim Delimiter string
 * @param s Array of input strings
 * @param Size of s
 * @return Joined string
 */
std::string join(const std::string& delim, const std::string* s, int size);

/**
 * Join specified strings with delimiter
 *
 * @param delim Delimiter string
 * @param s Array of input strings
 * @param Size of s
 * @return Joined string
 */
std::string join(const std::string& delim, const std::vector<std::string>& s);
/**
 * Test if s0 is contained in s1
 *
 * return true if contained, otherwise false
 */
bool contained(const std::string& s0, const std::string& s1);

/**
 * Test if c is contained in s1
 *
 * return true if contained, otherwise false
 */
bool contained(char c, const std::string& s1);

/**
 * Split specified string with specified delimiter
 *
 * @param s Input string
 * @param delim Delimiter string
 * @return vector of string
 *
 * @note Each characters in delim is considered as delimiter character
 */
std::vector<std::string> split(const std::string& s, const std::string& delim);

struct parsecontext
{
    int i;
    std::string tmp;
};

static void split_ibs0(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret);

static  void split_ibs1(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret);

static void split_inq(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret);

static void split_st(parsecontext& pc, const std::string& s, const std::string& delim, char quote, std::vector<std::string>& ret);

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
std::vector<std::string> split(const std::string& s, const std::string& delim, char quote);


/**
 * Convert string to double
 *
 * @param s String
 * @param success true if conversion succeed, otherwise false.
 *
 * @return Converted value if succeed, otherwise 0
 */
double toDouble(const std::string& s, bool& success);


/**
 * Convert string to decimal integer
 *
 * @param s String
 * @param success true if conversion succeed, otherwise false.
 *
 * @return Converted value if succeed, otherwise 0
 */
int toInt(const std::string& s, bool& success);


/**
 * Format string of double value
 *
 * @param f Format string ( printf form )
 * @param v Value to convert
 *
 * @return Formatted string
 */
std::string format(const std::string& f, double v);

/**
 * Format string of integer value
 *
 * @param f Format string ( printf form )
 * @param v Value to convert
 *
 * @return Formatted string
 */
std::string format(const std::string& f, int v);

/**
 * Convert double value to string
 *
 * @param v Value to convert
 *
 * @return String
 */
std::string toString(double v);

/**
 * Convert integer value to string
 *
 * @param v Value to convert
 *
 * @return String
 */
std::string toString(int v);


} // namespace strutil

#endif

