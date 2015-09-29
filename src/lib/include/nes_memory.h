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

#ifndef NES_MEMORY_H_
#define NES_MEMORY_H_

namespace NES {

	namespace COMP {

		typedef std::vector<uint8_t> nes_memory_block;

		typedef class _nes_memory {

			public:

				~_nes_memory(void);

				static _nes_memory *acquire(void);

				std::string address_as_string(
					__in uint16_t address,
					__in_opt bool verbose = false
					);

				static std::string address_as_string(
					__in const nes_memory_block &block,
					__in uint16_t address,
					__in_opt bool verbose = false
					);

				uint8_t &at(
					__in uint16_t address
					);

				static std::string block_as_string(
					__in const nes_memory_block &block,
					__in uint16_t address,
					__in uint16_t offset,
					__in_opt bool verbose = false
					);

				void clear(void);

				bool flag_check(
					__in uint16_t address,
					__in uint8_t flag
					);

				void flag_clear(
					__in uint16_t address,
					__in uint8_t flag
					);

				void flag_set(
					__in uint16_t address,
					__in uint8_t flag
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				std::string to_string(
					__in uint16_t address,
					__in uint16_t offset,
					__in_opt bool verbose = false
					);

				void uninitialize(void);

				void write(
					__in uint16_t address,
					__in const nes_memory_block &block
					);

			protected:

				_nes_memory(void);

				_nes_memory(
					__in const _nes_memory &other
					);

				_nes_memory &operator=(
					__in const _nes_memory &other
					);

				static void _delete(void);

				nes_memory_block m_block;

				bool m_initialized;

				static _nes_memory *m_instance;

			private:

				std::recursive_mutex m_lock;

		} nes_memory, *nes_memory_ptr;
	}
}

#endif // NES_MEMORY_H_
