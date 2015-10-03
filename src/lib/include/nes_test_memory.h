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

#ifndef NDEBUG
#ifndef NES_TEST_MEMORY_H_
#define NES_TEST_MEMORY_H_

namespace NES {

	namespace TEST {

		typedef class _nes_test_memory {

			public:

				static nes_test_t acquire(
					__in void *context
					);

				static nes_test_t at(
					__in void *context
					);

				static nes_test_t clear(
					__in void *context
					);

				static nes_test_t flag_check(
					__in void *context
					);

				static nes_test_t flag_clear(
					__in void *context
					);

				static nes_test_t flag_set(
					__in void *context
					);

				static nes_test_t initialize(
					__in void *context
					);

				static nes_test_t is_allocated(
					__in void *context
					);

				static nes_test_t is_initialized(
					__in void *context
					);

				static nes_test_t read(
					__in void *context
					);

				static nes_test_set set_generate(void);

				static nes_test_t set_initialize(
					__in void *context
					);

				static nes_test_t set_uninitialize(
					__in void *context
					);

				static nes_test_t uninitialize(
					__in void *context
					);

				static nes_test_t write(
					__in void *context
					);

		} nes_test_memory, *nes_test_memory_ptr;
	}
}

#endif // NES_TEST_MEMORY_H_
#endif // NDEBUG
