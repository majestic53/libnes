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
			NES_TEST_PPU_CLEAR,
			NES_TEST_PPU_CYCLES,
			NES_TEST_PPU_INITIALIZE,
			NES_TEST_PPU_IS_ALLOCATED,
			NES_TEST_PPU_IS_INITIALIZED,
			NES_TEST_PPU_RESET,
			NES_TEST_PPU_START,
			NES_TEST_PPU_STEP,
			NES_TEST_PPU_STOP,
			NES_TEST_PPU_UNINITIALIZE,
		};

		#define NES_TEST_PPU_MAX NES_TEST_PPU_UNINITIALIZE

		static const std::string NES_TEST_PPU_STR[] = {
			NES_PPU_HEADER "::ACQUIRE",
			NES_PPU_HEADER "::CLEAR",
			NES_PPU_HEADER "::CYCLES",
			NES_PPU_HEADER "::INITIALIZE",
			NES_PPU_HEADER "::IS_ALLOCATED",
			NES_PPU_HEADER "::IS_INITIALIZED",
			NES_PPU_HEADER "::RESET",
			NES_PPU_HEADER "::START",
			NES_PPU_HEADER "::STEP",
			NES_PPU_HEADER "::STOP",
			NES_PPU_HEADER "::UNINITIALIZE",
			};

		#define NES_TEST_PPU_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_PPU_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_PPU_STR[_TYPE_]))

		static nes_test_cb NES_TEST_PPU_CB[] = {
			nes_test_ppu::acquire,
			nes_test_ppu::clear,
			nes_test_ppu::cycles,
			nes_test_ppu::initialize,
			nes_test_ppu::is_allocated,
			nes_test_ppu::is_initialized,
			nes_test_ppu::reset,
			nes_test_ppu::start,
			nes_test_ppu::step,
			nes_test_ppu::stop,
			nes_test_ppu::uninitialize,
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

		nes_test_t 
		_nes_test_ppu::clear(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->clear();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::cycles(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->cycles();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::initialize(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				try {
					inst->initialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::is_allocated(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

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

		nes_test_t 
		_nes_test_ppu::is_initialized(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

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

		nes_test_t 
		_nes_test_ppu::reset(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->reset();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

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
		_nes_test_ppu::start(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->start();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::step(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->step();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_ppu::stop(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->stop();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
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

		nes_test_t 
		_nes_test_ppu::uninitialize(
			__in void *context
			)
		{
			nes_ppu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			inst = (nes_ppu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->uninitialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				// TODO

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
