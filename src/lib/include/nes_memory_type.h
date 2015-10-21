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

#ifndef NES_MEMORY_TYPE_H_
#define NES_MEMORY_TYPE_H_

#include "nes_type.h"

namespace NES {

	namespace COMP {

		#define NES_MMU_MAX UINT16_MAX
		#define NES_PPU_MAX 0x3fff
		#define NES_PPU_OAM_MAX UINT8_MAX

		#define NES_MEMORY_HEADER NES_HEADER "::MEM"

		#ifndef NDEBUG
		#define NES_MEMORY_EXCEPTION_HEADER NES_MEMORY_HEADER
		#else
		#define NES_MEMORY_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			NES_MEMORY_EXCEPTION_ALLOCATED = 0,
			NES_MEMORY_EXCEPTION_INVALID_ADDRESS,
			NES_MEMORY_EXCEPTION_INVALID_TYPE,
			NES_MEMORY_EXCEPTION_INITIALIZED,
			NES_MEMORY_EXCEPTION_UNINITIALIZED,
		};

		#define NES_MEMORY_EXCEPTION_MAX NES_MEMORY_EXCEPTION_UNINITIALIZED

		static const std::string NES_MEMORY_EXCEPTION_STR[] = {
			"Failed to allocate memory component",
			"Invalid memory address",
			"Invalid memory type",
			"Memory component is initialized",
			"Memory component is uninitialized",
			};

		#define NES_MEMORY_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > NES_MEMORY_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
			CHECK_STR(NES_MEMORY_EXCEPTION_STR[_TYPE_]))

		#define THROW_NES_MEMORY_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(NES_MEMORY_EXCEPTION_HEADER, \
			NES_MEMORY_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_NES_MEMORY_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(NES_MEMORY_EXCEPTION_HEADER, \
			NES_MEMORY_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _nes_memory;
		typedef _nes_memory nes_memory, *nes_memory_ptr;
	}
}

#endif // NES_MEMORY_TYPE_H_
