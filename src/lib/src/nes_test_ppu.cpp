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

#include "../include/nes.h"
#include "../include/nes_ppu_type.h"

#ifndef NDEBUG

namespace NES {

	namespace TEST {

		enum {
			NES_TEST_PPU_ACQUIRE = 0,
		};

		#define NES_TEST_PPU_MAX NES_TEST_PPU_ACQUIRE

		static const std::string NES_TEST_PPU_STR[] = {
			NES_PPU_HEADER "::ACQUIRE",
			};

		#define NES_TEST_PPU_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_PPU_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_PPU_STR[_TYPE_]))

		static nes_test_cb NES_TEST_PPU_CB[] = {
			nes_test_ppu::acquire,
			};

		#define NES_TEST_PPU_CALLBACK(_TYPE_) \
			((_TYPE_) > NES_TEST_PPU_MAX ? NULL : \
			NES_TEST_PPU_CB[_TYPE_])

		nes_test_t 
		_nes_test_ppu::acquire(
			__in void *context
			)
		{
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		// TODO

		nes_test_set 
		_nes_test_ppu::set_generate(void)
		{
			size_t iter = 0;
			nes_test_set result(NES_PPU_HEADER);

			for(; iter <= NES_TEST_PPU_MAX; ++iter) {
				result.insert(nes_test(NES_TEST_PPU_STRING(iter),
					NES_TEST_PPU_CALLBACK(iter),
					nes_ppu::acquire(), nes_test_ppu::test_initialize,
					nes_test_ppu::test_uninitialize));
			}

			return result;
		}

		nes_test_t 
		_nes_test_ppu::test_initialize(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_ppu_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					inst->initialize();
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::test_uninitialize(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_ppu_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_initialized()) {
					inst->uninitialize();
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}
	}
}

#endif // NDEBUG
