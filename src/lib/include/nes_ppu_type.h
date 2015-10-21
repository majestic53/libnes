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

#ifndef NES_PPU_TYPE_H_
#define NES_PPU_TYPE_H_

#include "nes_type.h"

namespace NES {

	namespace COMP {

		#define NES_PPU_HEADER NES_HEADER "::PPU"

		#ifndef NDEBUG
		#define NES_PPU_EXCEPTION_HEADER NES_PPU_HEADER
		#else
		#define NES_PPU_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			NES_PPU_EXCEPTION_ALLOCATED = 0,
			NES_PPU_EXCEPTION_INITIALIZED,
			NES_PPU_EXCEPTION_UNINITIALIZED,
		};

		#define NES_PPU_EXCEPTION_MAX NES_PPU_EXCEPTION_UNINITIALIZED

		static const std::string NES_PPU_EXCEPTION_STR[] = {
			"Failed to allocate ppu component",
			"Ppu component is initialized",
			"Ppu component is uninitialized",
			};

		#define NES_PPU_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > NES_PPU_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
			CHECK_STR(NES_PPU_EXCEPTION_STR[_TYPE_]))

		#define THROW_NES_PPU_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(NES_PPU_EXCEPTION_HEADER, \
			NES_PPU_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_NES_PPU_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(NES_PPU_EXCEPTION_HEADER, \
			NES_PPU_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _nes_ppu;
		typedef _nes_ppu nes_ppu, *nes_ppu_ptr;
	}
}

#endif // NES_PPU_TYPE_H_
