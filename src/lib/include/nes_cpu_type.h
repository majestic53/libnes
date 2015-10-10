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

		#define CPU_CYCLES_INIT 0
		#define CPU_FLAG_BREAKPOINT 0x10
		#define CPU_FLAG_CARRY 0x1
		#define CPU_FLAG_DECIMAL 0x8
		#define CPU_FLAG_INTERRUPT_DISABLED 0x4
		#define CPU_FLAG_NEGATIVE 0x80
		#define CPU_FLAG_OVERFLOW 0x40
		#define CPU_FLAG_ZERO 0x2
		#define CPU_INTERRUPT_CYCLES 3
		#define CPU_INTERRUPT_IRQ_ADDRESS 0xfffe
		#define CPU_INTERRUPT_NMI_ADDRESS 0xfffa
		#define CPU_INTERRUPT_RESET_ADDRESS 0xfffc
		#define CPU_REGISTER_A_INIT 0
		#define CPU_REGISTER_P_INIT \
			(CPU_FLAG_INTERRUPT_DISABLED | CPU_FLAG_ZERO)
		#define CPU_REGISTER_PC_INIT 0
		#define CPU_REGISTER_SP_INIT 0xff
		#define CPU_REGISTER_SP_OFFSET 0x100
		#define CPU_REGISTER_X_INIT 0
		#define CPU_REGISTER_Y_INIT 0
		#define CPU_WORD_LENGTH 2

		#define CPU_FLAG_CHECK(_P_, _FLAG_) ((_P_) & (_FLAG_))
		#define CPU_FLAG_CLEAR(_P_, _FLAG_) ((_P_) &= ~(_FLAG_))
		#define CPU_FLAG_SET(_P_, _FLAG_) ((_P_) |= (_FLAG_))
		#define CPU_FLAG_SET_CONDITIONAL(_COND_, _P_, _FLAG_) { \
			if(_COND_) { \
				CPU_FLAG_SET(_P_, _FLAG_); \
			} else { \
				CPU_FLAG_CLEAR(_P_, _FLAG_); \
			} \
			}

		#define NES_CPU_HEADER NES_HEADER "::CPU"

		#ifndef NDEBUG
		#define NES_CPU_EXCEPTION_HEADER NES_CPU_HEADER
		#else
		#define NES_CPU_EXCEPTION_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			NES_CPU_EXCEPTION_ALLOCATED = 0,
			NES_CPU_EXCEPTION_EXPECTING_BIT_CODE,
			NES_CPU_EXCEPTION_EXPECTING_BRANCH_CODE,
			NES_CPU_EXCEPTION_EXPECTING_BRK_CODE,
			NES_CPU_EXCEPTION_EXPECTING_FLAG_CODE,
			NES_CPU_EXCEPTION_EXPECTING_JMP_CODE,
			NES_CPU_EXCEPTION_EXPECTING_JSR_CODE,
			NES_CPU_EXCEPTION_EXPECTING_LDA_CODE,
			NES_CPU_EXCEPTION_EXPECTING_NOP_CODE,
			NES_CPU_EXCEPTION_EXPECTING_REGISTER_CODE,
			NES_CPU_EXCEPTION_EXPECTING_RTI_CODE,
			NES_CPU_EXCEPTION_EXPECTING_RTS_CODE,
			NES_CPU_EXCEPTION_EXPECTING_STACK_CODE,
			NES_CPU_EXCEPTION_INITIALIZED,
			NES_CPU_EXCEPTION_UNINITIALIZED,
			NES_CPU_EXCEPTION_UNKNOWN_MODE,
			NES_CPU_EXCEPTION_UNSUPPORTED_CODE,
		};

		#define NES_CPU_EXCEPTION_MAX NES_CPU_EXCEPTION_UNSUPPORTED_CODE

		static const std::string NES_CPU_EXCEPTION_STR[] = {
			"Failed to allocate cpu component",
			"Expecting bit opcode",
			"Expecting branch opcode",
			"Expecting break opcode",
			"Expecting flag opcode",
			"Expecting jump opcode",
			"Expecting jump-to-subroutine opcode",
			"Expecting load-accumulator opcode",
			"Expecting no-op opcode",
			"Expecting register opcode",
			"Expecting return-from-interrupt opcode",
			"Expecting return-from-subroutine opcode",
			"Expecting stack opcode",
			"Cpu component is initialized",
			"Cpu component is uninitialized",
			"Unknown addressing mode",
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
