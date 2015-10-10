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

#ifndef NES_CPU_H_
#define NES_CPU_H_

namespace NES {

	namespace COMP {

		typedef class _nes_cpu {

			public:

				~_nes_cpu(void);

				static _nes_cpu *acquire(void);

				void clear(void);

				uint32_t cycles(void);

				void initialize(void);

				void irq(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				void nmi(void);

				void reset(void);

				void step(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

			protected:

				_nes_cpu(void);

				_nes_cpu(
					__in const _nes_cpu &other
					);

				_nes_cpu &operator=(
					__in const _nes_cpu &other
					);

				static void _delete(void);

				void execute_adc(
					__in uint8_t code
					);

				void execute_and(
					__in uint8_t code
					);

				void execute_asl(
					__in uint8_t code
					);

				void execute_branch(
					__in uint8_t code
					);

				void execute_bit(
					__in uint8_t code
					);

				void execute_brk(
					__in uint8_t code
					);

				void execute_flag(
					__in uint8_t code
					);

				void execute_cmp(
					__in uint8_t code
					);

				void execute_cpx(
					__in uint8_t code
					);

				void execute_cpy(
					__in uint8_t code
					);

				void execute_dec(
					__in uint8_t code
					);

				void execute_eor(
					__in uint8_t code
					);

				void execute_inc(
					__in uint8_t code
					);

				void execute_jmp(
					__in uint8_t code
					);

				void execute_jsr(
					__in uint8_t code
					);

				void execute_lda(
					__in uint8_t code
					);

				void execute_ldx(
					__in uint8_t code
					);

				void execute_ldy(
					__in uint8_t code
					);

				void execute_lsr(
					__in uint8_t code
					);

				void execute_nop(
					__in uint8_t code
					);

				void execute_ora(
					__in uint8_t code
					);

				void execute_register(
					__in uint8_t code
					);

				void execute_rol(
					__in uint8_t code
					);

				void execute_ror(
					__in uint8_t code
					);

				void execute_rti(
					__in uint8_t code
					);

				void execute_rts(
					__in uint8_t code
					);

				void execute_sbc(
					__in uint8_t code
					);

				void execute_sta(
					__in uint8_t code
					);

				void execute_stack(
					__in uint8_t code
					);

				void execute_stx(
					__in uint8_t code
					);

				void execute_sty(
					__in uint8_t code
					);

				void interrupt(
					__in uint16_t address,
					__in_opt bool breakpoint = false
					);

				void interrupt_return(void);

				uint8_t load(
					__in uint16_t address
					);

				uint16_t load_operand(
					__in cpu_mode_t mode,
					__out bool &boundary
					);

				uint16_t load_word(
					__in uint16_t address
					);

				uint8_t pop(void);

				uint16_t pop_word(void);

				void push(
					__in uint8_t value
					);

				void push_word(
					__in uint16_t value
					);

				void store(
					__in uint16_t address,
					__in uint8_t value
					);

				void store_word(
					__in uint16_t address,
					__in uint16_t value
					);

				void subroutine(
					__in uint16_t address
					);

				void subroutine_return(void);

#ifndef NDEBUG
				friend class NES::TEST::_nes_test_cpu;
#endif // NDEBUG

				uint32_t m_cycles;

				static _nes_cpu *m_instance;

				bool m_initialized;

				nes_memory_ptr m_memory;

				uint8_t m_register_a, m_register_p, m_register_sp, 
					m_register_x, m_register_y;

				uint16_t m_register_pc;

			private:

				std::recursive_mutex m_lock;

		} nes_cpu, *nes_cpu_ptr;
	}
}

#endif // NES_CPU_H_
