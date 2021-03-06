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
#include "../include/nes_memory_type.h"

#ifndef NDEBUG

namespace NES {

	namespace TEST {

		#define TEST_MEM_MMU_ADDRESS 0x100
		#define TEST_MEM_MMU_ADDRESS_HIGH (UINT16_MAX - 1)
		#define TEST_MEM_PPU_ADDRESS 0x100
		#define TEST_MEM_PPU_ADDRESS_HIGH 0x3ffe
		#define TEST_MEM_PPU_OAM_ADDRESS 0x10
		#define TEST_MEM_PPU_OAM_ADDRESS_HIGH (UINT8_MAX - 1)
		#define TEST_MEM_OFFSET 0x4
		#define TEST_MEM_OFFSET_HIGH 0x2
		#define TEST_MEM_VALUE 0x40

		static const nes_memory_block TEST_BLK = { 
			0xaa, 0xbb, 0xcc, 0xdd 
			};

		enum {
			NES_TEST_MEMORY_ACQUIRE = 0,
			NES_TEST_MEMORY_AT,
			NES_TEST_MEMORY_CLEAR,
			NES_TEST_MEMORY_FLAG_CHECK,
			NES_TEST_MEMORY_FLAG_CLEAR,
			NES_TEST_MEMORY_FLAG_SET,
			NES_TEST_MEMORY_INITIALIZE,
			NES_TEST_MEMORY_IS_ALLOCATED,
			NES_TEST_MEMORY_IS_INITIALIZE,
			NES_TEST_MEMORY_READ,
			NES_TEST_MEMORY_UNINITIALIZE,
			NES_TEST_MEMORY_WRITE,
		};

		#define NES_TEST_MEMORY_MAX NES_TEST_MEMORY_WRITE

		static const std::string NES_TEST_MEMORY_STR[] = {
			NES_MEMORY_HEADER "::ACQUIRE",
			NES_MEMORY_HEADER "::AT",
			NES_MEMORY_HEADER "::CLEAR",
			NES_MEMORY_HEADER "::FLAG_CHECK",
			NES_MEMORY_HEADER "::FLAG_CLEAR",
			NES_MEMORY_HEADER "::FLAG_SET",
			NES_MEMORY_HEADER "::INITIALIZE",
			NES_MEMORY_HEADER "::IS_ALLOCATED",
			NES_MEMORY_HEADER "::IS_INITIALIZED",
			NES_MEMORY_HEADER "::READ",
			NES_MEMORY_HEADER "::UNINITIALIZE",
			NES_MEMORY_HEADER "::WRITE",
			};

		#define NES_TEST_MEMORY_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_MEMORY_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_MEMORY_STR[_TYPE_]))

		static const nes_test_cb NES_TEST_MEMORY_CB[] = {
			nes_test_memory::acquire,
			nes_test_memory::at,
			nes_test_memory::clear,
			nes_test_memory::flag_check,
			nes_test_memory::flag_clear,
			nes_test_memory::flag_set,
			nes_test_memory::initialize,
			nes_test_memory::is_allocated,
			nes_test_memory::is_initialized,
			nes_test_memory::read,
			nes_test_memory::uninitialize,
			nes_test_memory::write,
			};

		#define NES_TEST_MEMORY_CALLBACK(_TYPE_) \
			((_TYPE_) > NES_TEST_MEMORY_MAX ? NULL : \
			NES_TEST_MEMORY_CB[_TYPE_])

		nes_test_t 
		_nes_test_memory::acquire(
			__in void *context
			)
		{
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				if(!nes_memory::acquire()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(!nes_memory::is_allocated()) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::at(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				if(inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) = TEST_MEM_VALUE;
				if(inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) != TEST_MEM_VALUE) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU
				if(inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) = TEST_MEM_VALUE;
				if(inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) != TEST_MEM_VALUE) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU_OAM
				if(inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) = TEST_MEM_VALUE;
				if(inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) != TEST_MEM_VALUE) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::clear(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->clear();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) = TEST_MEM_VALUE;
				inst->clear();

				if(inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU
				inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) = TEST_MEM_VALUE;
				inst->clear();

				if(inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU_OAM
				inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) = TEST_MEM_VALUE;
				inst->clear();

				if(inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) != 0) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::flag_check(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->flag_check(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, 
							TEST_MEM_VALUE);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) = TEST_MEM_VALUE;

				if(!inst->flag_check(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, 
						TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->flag_check(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, 0x1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU
				inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) = TEST_MEM_VALUE;

				if(!inst->flag_check(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, 
						TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->flag_check(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, 0x1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU_OAM
				inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) = TEST_MEM_VALUE;

				if(!inst->flag_check(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, 
						TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->flag_check(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, 0x1)) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::flag_clear(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->flag_clear(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, 
							TEST_MEM_VALUE);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				inst->at(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS) = TEST_MEM_VALUE;
				inst->flag_clear(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_VALUE);

				if(inst->flag_check(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU
				inst->at(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS) = TEST_MEM_VALUE;
				inst->flag_clear(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_VALUE);

				if(inst->flag_check(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU_OAM
				inst->at(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS) = TEST_MEM_VALUE;
				inst->flag_clear(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_VALUE);

				if(inst->flag_check(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::flag_set(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->flag_set(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, 
							TEST_MEM_VALUE);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				inst->flag_set(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_VALUE);

				if(!inst->flag_check(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU
				inst->flag_set(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_VALUE);

				if(!inst->flag_check(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// NES_MEM_PPU_OAM
				inst->flag_set(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_VALUE);

				if(!inst->flag_check(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_VALUE)) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::initialize(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				try {
					inst->initialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				inst->initialize();

				if(!inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::is_allocated(
			__in void *context
			)
		{
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			try {

				if(!nes_memory::is_allocated()) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::is_initialized(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				if(inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->initialize();

				if(!inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
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
		_nes_test_memory::read(
			__in void *context
			)
		{
			size_t iter = 0;
			nes_memory_block blk;
			nes_memory_ptr inst = NULL;
			nes_memory_block::iterator blk_iter;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_OFFSET, 
							blk);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				if(inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(blk_iter = blk.begin(); blk_iter != blk.end(); ++blk_iter) {

					if(*blk_iter != 0) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_BLK);

				if(inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_BLK.size()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS_HIGH, TEST_BLK);

				if(inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS_HIGH, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				blk.clear();

				// NES_MEM_PPU
				if(inst->read(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(blk_iter = blk.begin(); blk_iter != blk.end(); ++blk_iter) {

					if(*blk_iter != 0) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_BLK);

				if(inst->read(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_BLK.size()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS_HIGH, TEST_BLK);

				if(inst->read(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS_HIGH, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				blk.clear();

				// NES_MEM_PPU_OAM
				if(inst->read(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(blk_iter = blk.begin(); blk_iter != blk.end(); ++blk_iter) {

					if(*blk_iter != 0) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_BLK);

				if(inst->read(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_OFFSET, blk) 
						!= TEST_BLK.size()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				inst->write(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS_HIGH, TEST_BLK);

				if(inst->read(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS_HIGH, TEST_MEM_OFFSET, blk) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_set 
		_nes_test_memory::set_generate(void)
		{
			size_t iter = 0;
			nes_test_set result(NES_MEMORY_HEADER);

			for(; iter <= NES_TEST_MEMORY_MAX; ++iter) {
				result.insert(nes_test(NES_TEST_MEMORY_STRING(iter), 
					NES_TEST_MEMORY_CALLBACK(iter), 
					nes_memory::acquire(), nes_test_memory::test_initialize, 
					nes_test_memory::test_uninitialize));
			}

			return result;
		}

		nes_test_t 
		_nes_test_memory::test_initialize(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				inst->initialize();
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_memory::test_uninitialize(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

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
		_nes_test_memory::uninitialize(
			__in void *context
			)
		{
			nes_memory_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {
				inst->uninitialize();

				try {
					inst->uninitialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(inst->is_initialized()) { 
					result = NES_TEST_FAILURE;
				}

				inst->initialize();
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_memory::write(
			__in void *context
			)
		{
			size_t iter = 0;
			nes_memory_block blk;
			nes_memory_ptr inst = NULL;
			nes_memory_block::iterator blk_iter;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_memory_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->write(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_BLK);
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				// NES_MEM_MMU
				if(inst->write(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_BLK) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				if(inst->write(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS_HIGH, TEST_BLK) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_MMU, TEST_MEM_MMU_ADDRESS_HIGH, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				blk.clear();

				// NES_MEM_PPU
				if(inst->write(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_BLK) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				if(inst->write(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS_HIGH, TEST_BLK) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_PPU, TEST_MEM_PPU_ADDRESS_HIGH, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				blk.clear();

				// NES_MEM_PPU_OAM
				if(inst->write(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_BLK) 
						!= TEST_MEM_OFFSET) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_BLK.size(); ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
				}

				if(inst->write(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS_HIGH, TEST_BLK) 
						!= TEST_MEM_OFFSET_HIGH) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->read(NES_MEM_PPU_OAM, TEST_MEM_PPU_OAM_ADDRESS_HIGH, TEST_MEM_OFFSET, blk);

				for(iter = 0; iter < TEST_MEM_OFFSET_HIGH; ++iter) {

					if(blk.at(iter) != TEST_BLK.at(iter)) {
						result = NES_TEST_FAILURE;
						goto exit;
					}
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
