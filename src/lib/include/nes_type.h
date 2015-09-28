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

#ifndef NES_TYPE_H_
#define NES_TYPE_H_

namespace NES {

	#define NES_HEADER "NES"

	#ifndef NDEBUG
	#define NES_EXCEPTION_HEADER NES_HEADER
	#else
	#define NES_EXCEPTION_HEADER EXCEPTION_HEADER
	#endif // NDEBUG

	enum {
		NES_EXCEPTION_ALLOCATED = 0,
		NES_EXCEPTION_INITIALIZED,
		NES_EXCEPTION_UNINITIALIZED,
	};

	#define NES_EXCEPTION_MAX NES_EXCEPTION_UNINITIALIZED

	static const std::string NES_EXCEPTION_STR[] = {
		"Failed to allocate library",
		"Library is initialized",
		"Library is uninitialized",
		};

	#define NES_EXCEPTION_STRING(_TYPE_) \
		((_TYPE_) > NES_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
		CHECK_STR(NES_EXCEPTION_STR[_TYPE_]))

	#define THROW_NES_EXCEPTION(_EXCEPT_) \
		THROW_EXCEPTION(NES_EXCEPTION_HEADER, \
		NES_EXCEPTION_STRING(_EXCEPT_))
	#define THROW_NES_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION_MESSAGE(NES_EXCEPTION_HEADER, \
		NES_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	class _nes;
	typedef class _nes nes, *nes_ptr;
}

#endif // NES_TYPE_H_
