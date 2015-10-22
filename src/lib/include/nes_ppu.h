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

#ifndef NES_PPU_H_
#define NES_PPU_H_

namespace NES {

	namespace COMP {

		typedef class _nes_ppu {

			public:

				~_nes_ppu(void);

				static _nes_ppu *acquire(void);

				void clear(void);

				void clear(
					__in nes_memory_t type
					);

				uint32_t cycles(void);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				bool is_started(void);

				void reset(void);

				void start(void);

				void step(void);

				void stop(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

			protected:

				_nes_ppu(void);

				_nes_ppu(
					__in const _nes_ppu &other
					);

				_nes_ppu &operator=(
					__in const _nes_ppu &other
					);

				static void _delete(void);

				uint8_t load(
					__in nes_memory_t type,
					__in uint16_t address
					);

				uint16_t load_word(
					__in nes_memory_t type,
					__in uint16_t address
					);

				void store(
					__in nes_memory_t type,
					__in uint16_t address,
					__in uint8_t value
					);

				void store_word(
					__in nes_memory_t type,
					__in uint16_t address,
					__in uint16_t value
					);

#ifndef NDEBUG
				friend class NES::TEST::_nes_test_ppu;
#endif // NDEBUG

				uint32_t m_cycles;

				bool m_initialized;

				static _nes_ppu *m_instance;

				nes_memory_ptr m_memory;

				bool m_started;

			private:

				std::recursive_mutex m_lock;

		} nes_ppu, *nes_ppu_ptr;
	}
}

#endif // NES_PPU_H_
