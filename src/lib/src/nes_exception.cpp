/**
 * libnes
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libnes is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdarg>
#include "../include/nes.h"

namespace NES {

	enum {
		NES_EXCEPTION_EMPTY = 0,
		NES_EXCEPTION_MALFORMED,
	};

	#define NES_EXCEPTION_MAX NES_EXCEPTION_MALFORMED

	static const std::string NES_EXCEPTION_STR[] = {
		"Empty exception",
		"Malformed exception",
		};

	#define NES_EXCEPTION_STRING(_TYPE_) \
		((_TYPE_) > NES_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
		CHECK_STR(NES_EXCEPTION_STR[_TYPE_]))

	_nes_exception::_nes_exception(
		__in_opt const std::string &message,
		__in_opt const std::string &function,
		__in_opt const std::string &file,
		__in_opt size_t line
		) :
			std::runtime_error(message),
			m_file(file),
			m_function(function),
			m_line(line)
	{
		return;
	}

	_nes_exception::_nes_exception(
		__in const _nes_exception &other
		) :
			std::runtime_error(other),
			m_file(other.m_file),
			m_function(other.m_function),
			m_line(other.m_line)
	{
		return;
	}

	_nes_exception::~_nes_exception(void)
	{
		return;
	}

	_nes_exception &
	_nes_exception::operator=(
		__in const _nes_exception &other
		)
	{
		ATOMIC_CALL_RECUR(m_lock);

		if(this != &other) {
			std::runtime_error::operator=(other);
			m_file = other.m_file;
			m_function = other.m_function;
			m_line = other.m_line;
		}

		return *this;
	}

	std::string 
	_nes_exception::file(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_file;
	}

	std::string 
	_nes_exception::function(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_function;
	}

	void 
	_nes_exception::generate(
		__in const std::string &header,
		__in const std::string &message,
		__in const std::string &function,
		__in const std::string &file,
		__in size_t line,
		__in const char *format,
		...
		)
	{
		int length;
		va_list list;
		std::string buffer;
		std::stringstream result;

		if(format) {
			va_start(list, format);

			length = vsnprintf(NULL, 0, format, list);
			if(length < 0) {
				buffer = NES_EXCEPTION_STRING(NES_EXCEPTION_EMPTY);
			} else if(!length) {
				buffer = NES_EXCEPTION_STRING(NES_EXCEPTION_MALFORMED);
			} else {
				va_end(list);
				va_start(list, format);
				buffer.resize(++length);
				
				length = vsnprintf((char *) &buffer[0], length, format, list);
				if(length < 0) {
					buffer = NES_EXCEPTION_STRING(NES_EXCEPTION_EMPTY);
				} else if(!length) {
					buffer = NES_EXCEPTION_STRING(NES_EXCEPTION_MALFORMED);
				}
			}

			va_end(list);
		}

		if(!header.empty()) {
			result << header;
		}

		if(!message.empty()) {
			result << ": " << message;
		}

		if(!buffer.empty()) {

			if(!result.str().empty()) {
				result << ": ";
			}

			result << buffer;
		}

		throw nes_exception(result.str(), function, file, line);
	}

	size_t 
	_nes_exception::line(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_line;
	}

	std::string 
	_nes_exception::to_string(
		__in_opt bool verbose
		)
	{
		std::stringstream result;

		ATOMIC_CALL_RECUR(m_lock);

		result << std::runtime_error::what();

		if(verbose) {
			result << " (";

			if(!m_function.empty()) {
				result << m_function << ":";
			}

			if(!m_file.empty()) {
				result << m_file << ":";
			}

			result << m_line << ")";
		}

		return result.str();
	}
}
