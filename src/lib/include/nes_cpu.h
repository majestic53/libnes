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

				void interrupt(
					__in uint16_t address,
					__in uint8_t status
					);

				void interrupt_return(
					__in uint16_t address
					);

				uint8_t load(
					__in uint16_t address
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
