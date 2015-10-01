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

#ifndef NES_CPU_TYPE_H_
#define NES_CPU_TYPE_H_

#include "nes_type.h"

namespace NES {

	namespace COMP {

		#define NES_CPU_HEADER NES_HEADER "::CPU"

		#ifndef NDEBUG
		#define NES_CPU_EXCEPTION_HEADER NES_CPU_HEADER
		#else
		#define NES_CPU_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			NES_CPU_EXCEPTION_ALLOCATED = 0,
			NES_CPU_EXCEPTION_INITIALIZED,
			NES_CPU_EXCEPTION_UNINITIALIZED,
			NES_CPU_EXCEPTION_UNSUPPORTED_CODE,
		};

		#define NES_CPU_EXCEPTION_MAX NES_CPU_EXCEPTION_UNSUPPORTED_CODE

		static const std::string NES_CPU_EXCEPTION_STR[] = {
			"Failed to allocate cpu component",
			"Cpu component is initialized",
			"Cpu component is uninitialized",
			"Unsupported opcode",
			};

		#define NES_CPU_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > NES_CPU_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
			CHECK_STR(NES_CPU_EXCEPTION_STR[_TYPE_]))

		#define THROW_NES_CPU_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(NES_CPU_EXCEPTION_HEADER, \
			NES_CPU_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_NES_CPU_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(NES_CPU_EXCEPTION_HEADER, \
			NES_CPU_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _nes_cpu;
		typedef _nes_cpu nes_cpu, *nes_cpu_ptr;
	}
}

#endif // NES_CPU_TYPE_H_
