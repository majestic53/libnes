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

#ifndef NES_ROM_TYPE_H_
#define NES_ROM_TYPE_H_

#include "nes_type.h"

namespace NES {

	namespace COMP {

		#define NES_ROM_HEADER NES_HEADER "::ROM"

		#ifndef NDEBUG
		#define NES_ROM_EXCEPTION_HEADER NES_ROM_HEADER
		#else
		#define NES_ROM_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			NES_ROM_EXCEPTION_ALLOCATED = 0,
			NES_ROM_EXCEPTION_INITIALIZED,
			NES_ROM_EXCEPTION_MALFORMED,
			NES_ROM_EXCEPTION_UNINITIALIZED,
			NES_ROM_EXCEPTION_UNLOADED,
		};

		#define NES_ROM_EXCEPTION_MAX NES_ROM_EXCEPTION_UNLOADED

		static const std::string NES_ROM_EXCEPTION_STR[] = {
			"Failed to allocate rom component",
			"Rom component is initialized",
			"Rom is malformed",
			"Rom component is uninitialized",
			"Rom component is unloaded",
			};

		#define NES_ROM_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > NES_ROM_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
			CHECK_STR(NES_ROM_EXCEPTION_STR[_TYPE_]))

		#define THROW_NES_ROM_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(NES_ROM_EXCEPTION_HEADER, \
			NES_ROM_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_NES_ROM_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(NES_ROM_EXCEPTION_HEADER, \
			NES_ROM_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _nes_rom;
		typedef _nes_rom nes_rom, *nes_rom_ptr;
	}
}

#endif // NES_ROM_TYPE_H_
