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

#ifndef NES_ROM_H_
#define NES_ROM_H_

namespace NES {

	namespace COMP {

		typedef class _nes_rom {

			public:

				~_nes_rom(void);

				static _nes_rom *acquire(void);

				size_t block_character(
					__in nes_memory_block &block,
					__in size_t index
					);

				size_t block_program(
					__in nes_memory_block &block,
					__in size_t index
					);

				nes_rom_header header(void);

				static std::string header_as_string(
					__in const nes_rom_header &header
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				bool is_loaded(void);

				void load(
					__in const std::string &input
					);

				size_t size(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

				void uninitialize(void);

				void unload(void);

			protected:

				_nes_rom(void);

				_nes_rom(
					__in const _nes_rom &other
					);

				_nes_rom &operator=(
					__in const _nes_rom &other
					);

				static void _delete(void);

				bool m_initialized;

				static _nes_rom *m_instance;

				bool m_loaded;

				nes_memory_block m_rom;

			private:

				std::recursive_mutex m_lock;

		} nes_rom, *nes_rom_ptr;
	}
}

#endif // NES_ROM_H_
