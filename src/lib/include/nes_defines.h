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

#ifndef NES_DEFINES_H_
#define NES_DEFINES_H_

#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace NES {

	#ifndef __in
	#define __in
	#endif // __in
	#ifndef __in_opt
	#define __in_opt
	#endif // __in_opt
	#ifndef __inout
	#define __inout
	#endif // __inout
	#ifndef __inout_opt
	#define __inout_opt
	#endif // __inout_opt
	#ifndef __out
	#define __out
	#endif // __out
	#ifndef __out_opt
	#define __out_opt
	#endif // __out_opt

	#define BITS_PER_BYTE (8)
	#define BLOCK_WIDTH (0x10)
	#define BYTES_PER_KBYTE (1024.0)

	#define EMPTY "EMPTY"
	#define INITIALIZED "INITIALIZED"
	#define INVALID "INVALID"
	#define UNINITIALIZED "UNINITIALIZED"
	#define UNKNOWN "UNKNOWN"

	#define VERSION_MAJ 0
	#define VERSION_MIN 1
	#define VERSION_REV 5
	#define VERSION_WEEK 1540

	#define CHECK_STR(_STR_) (!_STR_.empty() ? _STR_.c_str() : EMPTY)

	#define INVALID_TYPE(_TYPE_) ((_TYPE_) -1)

	#define _ATOMIC_CALL(_TYPE_, _MUTEX_) \
		std::lock_guard<_TYPE_> __LOCK ## _MUTEX_(_MUTEX_)
	#define ATOMIC_CALL(_MUTEX_) \
		_ATOMIC_CALL(std::mutex, _MUTEX_)
	#define ATOMIC_CALL_RECUR(_MUTEX_) \
		_ATOMIC_CALL(std::recursive_mutex, _MUTEX_)

	#define _CONCAT_STR(_STR_) # _STR_
	#define CONCAT_STR(_STR_) _CONCAT_STR(_STR_)

	#define UNREF_PARAM(_PARAM_) (void) _PARAM_

	#define VALUE_AS_HEX(_TYPE_, _VALUE_) \
		std::setw(sizeof(_TYPE_) * 2) << std::setfill('0') << std::hex \
		<< (uintmax_t) ((_TYPE_) (_VALUE_)) << std::dec

	#define VERSION_STR() \
		CONCAT_STR(VERSION_MAJ) "." CONCAT_STR(VERSION_MIN) "." \
		CONCAT_STR(VERSION_WEEK) "." CONCAT_STR(VERSION_REV)
}

#endif // NES_DEFINES_H_
