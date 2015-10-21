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
#ifndef NES_TEST_PPU_H_
#define NES_TEST_PPU_H_

namespace NES {

	namespace TEST {

		typedef class _nes_test_ppu {

			public:

				static nes_test_t acquire(
					__in void *context
					);

				// TODO

				static nes_test_set set_generate(void);

				static nes_test_t test_initialize(
					__in void *context
					);

				static nes_test_t test_uninitialize(
					__in void *context
					);

		} nes_test_ppu, *nes_test_ppu_ptr;
	}
}

#endif // NES_TEST_PPU_H_
#endif // NDEBUG
