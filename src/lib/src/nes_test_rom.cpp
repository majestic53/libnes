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

#include <fstream>
#include "../include/nes.h"
#include "../include/nes_rom_header.h"
#include "../include/nes_rom_type.h"

#ifndef NDEBUG

namespace NES {

	namespace TEST {

		#define NES_TEST_ROM_BANKS_CHARACTER 1
		#define NES_TEST_ROM_BANKS_PROGRAM 2
		#define NES_TEST_ROM_INDEX_ZERO 0
		#define NES_TEST_ROM_INDEX_INVALID 10
		#define NES_TEST_ROM_PATH_INVALID "./test/rom_invalid.nes"
		#define NES_TEST_ROM_PATH_VALID_BANKS "./test/rom_valid_banks.nes"
		#define NES_TEST_ROM_PATH_VALID_BANKS_LEN 40976
		#define NES_TEST_ROM_PATH_VALID_HEADER "./test/rom_valid_header.nes"
		#define NES_TEST_ROM_PATH_VALID_HEADER_LEN 16

		enum {
			NES_TEST_ROM_ACQUIRE = 0,
			NES_TEST_ROM_BLOCK_CHARACTER,
			NES_TEST_ROM_BLOCK_PROGRAM,
			NES_TEST_ROM_HEADER,
			NES_TEST_ROM_INITIALIZE,
			NES_TEST_ROM_IS_ALLOCATED,
			NES_TEST_ROM_IS_INITIALIZED,
			NES_TEST_ROM_IS_LOADED,
			NES_TEST_ROM_LOAD,
			NES_TEST_ROM_SIZE,
			NES_TEST_ROM_UNINITIALIZE,
			NES_TEST_ROM_UNLOAD,
		};

		#define NES_TEST_ROM_MAX NES_TEST_ROM_UNLOAD

		static const std::string NES_TEST_ROM_STR[] = {
			NES_ROM_HEADER "::ACQUIRE",
			NES_ROM_HEADER "::BLOCK_CHARACTER",
			NES_ROM_HEADER "::BLOCK_PROGRAM",
			NES_ROM_HEADER "::HEADER",
			NES_ROM_HEADER "::INITIALIZE",
			NES_ROM_HEADER "::IS_ALLOCATED",
			NES_ROM_HEADER "::IS_INITIALIZED",
			NES_ROM_HEADER "::IS_LOADED",
			NES_ROM_HEADER "::LOAD",
			NES_ROM_HEADER "::SIZE",
			NES_ROM_HEADER "::UNINITIALIZE",
			NES_ROM_HEADER "::UNLOAD",
			};

		#define NES_TEST_ROM_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_ROM_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_ROM_STR[_TYPE_]))

		static const nes_test_cb NES_TEST_ROM_CB[] = {
			nes_test_rom::acquire,
			nes_test_rom::block_character,
			nes_test_rom::block_program,
			nes_test_rom::header,
			nes_test_rom::initialize,
			nes_test_rom::is_allocated,
			nes_test_rom::is_initialized,
			nes_test_rom::is_loaded,
			nes_test_rom::load,
			nes_test_rom::size,
			nes_test_rom::uninitialize,
			nes_test_rom::unload,
			};

		#define NES_TEST_ROM_CALLBACK(_TYPE_) \
			((_TYPE_) > NES_TEST_ROM_MAX ? NULL : \
			NES_TEST_ROM_CB[_TYPE_])

		nes_test_t 
		_nes_test_rom::acquire(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = nes_rom::acquire();
				if(!inst || (inst != context)) {
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
		_nes_test_rom::block_character(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			size_t ch_iter, iter = 0;
			nes_memory_block blk, blk_test;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_loaded()) {
					inst->unload();
				}

				try {
					inst->block_character(blk, NES_TEST_ROM_INDEX_ZERO);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->block_character(blk, NES_TEST_ROM_INDEX_ZERO);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				if(!inst->is_loaded()) {
					inst->load(NES_TEST_ROM_PATH_VALID_BANKS);
				}

				for(; iter < NES_TEST_ROM_BANKS_CHARACTER; ++iter) {

					if(inst->block_character(blk, iter) != ROM_CHARACTER_LEN) {
						result = NES_TEST_FAILURE;
						goto exit;
					}

					std::ifstream file(NES_TEST_ROM_PATH_VALID_BANKS, 
						std::ios::in | std::ios::binary);

					if(!file) {
						result = NES_TEST_INCONCLUSIVE;
						file.close();
						goto exit;
					}

					blk_test.resize(ROM_CHARACTER_LEN);
					file.seekg((ROM_CHARACTER_LEN * iter) 
						+ (ROM_PROGRAM_LEN * NES_TEST_ROM_BANKS_PROGRAM) 
						+ sizeof(nes_rom_header), std::ios::beg);
					file.read((char *) &blk_test[0], ROM_CHARACTER_LEN);
					file.close();

					for(ch_iter = 0; ch_iter < blk_test.size(); ++ch_iter) {

						if(blk.at(ch_iter) != blk_test.at(ch_iter)) {
							result = NES_TEST_FAILURE;
							goto exit;
						}
					}
				}

				try {
					inst->block_character(blk, iter);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_rom::block_program(
			__in void *context
			)
		{	
			nes_rom_ptr inst = NULL;
			size_t ch_iter, iter = 0;
			nes_memory_block blk, blk_test;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_loaded()) {
					inst->unload();
				}

				try {
					inst->block_program(blk, NES_TEST_ROM_INDEX_ZERO);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->block_program(blk, NES_TEST_ROM_INDEX_ZERO);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				if(!inst->is_loaded()) {
					inst->load(NES_TEST_ROM_PATH_VALID_BANKS);
				}

				for(; iter < NES_TEST_ROM_BANKS_PROGRAM; ++iter) {

					if(inst->block_program(blk, iter) != ROM_PROGRAM_LEN) {
						result = NES_TEST_FAILURE;
						goto exit;
					}

					std::ifstream file(NES_TEST_ROM_PATH_VALID_BANKS, 
						std::ios::in | std::ios::binary);

					if(!file) {
						result = NES_TEST_INCONCLUSIVE;
						file.close();
						goto exit;
					}

					blk_test.resize(ROM_PROGRAM_LEN);
					file.seekg((ROM_PROGRAM_LEN * iter) + sizeof(nes_rom_header), 
						std::ios::beg);
					file.read((char *) &blk_test[0], ROM_PROGRAM_LEN);
					file.close();

					for(ch_iter = 0; ch_iter < blk_test.size(); ++ch_iter) {

						if(blk.at(ch_iter) != blk_test.at(ch_iter)) {
							result = NES_TEST_FAILURE;
							goto exit;
						}
					}
				}

				try {
					inst->block_program(blk, iter);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_rom::header(
			__in void *context
			)
		{
			size_t iter = 0;
			nes_rom_header head;
			nes_memory_block blk;
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->header(head);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				inst->load(NES_TEST_ROM_PATH_VALID_HEADER);
				inst->header(head);
				std::ifstream file(NES_TEST_ROM_PATH_VALID_HEADER, 
					std::ios::in | std::ios::binary);

				if(!file) {
					result = NES_TEST_INCONCLUSIVE;
					file.close();
					goto exit;
				}

				blk.resize(sizeof(nes_rom_header));
				file.read((char *) &blk[0], sizeof(nes_rom_header));
				file.close();

				for(; iter < sizeof(nes_rom_header); ++iter) {

					if(((uint8_t *) &head)[iter] != blk.at(iter)) {
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

		nes_test_t 
		_nes_test_rom::initialize(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				try {
					inst->initialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_allocated() || !inst->is_initialized() 
						|| inst->is_loaded() 
						|| !inst->m_block.empty()) {
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
		_nes_test_rom::is_allocated(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_allocated()) {
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
		_nes_test_rom::is_initialized(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				if(inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					inst->initialize();
				}

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
		_nes_test_rom::is_loaded(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_loaded()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->load(NES_TEST_ROM_PATH_VALID_HEADER);

				if(!inst->is_loaded()) {
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
		_nes_test_rom::load(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					inst->load(NES_TEST_ROM_PATH_VALID_HEADER);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				try {
					inst->load(NES_TEST_ROM_PATH_INVALID);
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				inst->load(NES_TEST_ROM_PATH_VALID_BANKS);

				if(!inst->is_loaded()
						|| (inst->size() != NES_TEST_ROM_PATH_VALID_BANKS_LEN)) {
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

		nes_test_set 
		_nes_test_rom::set_generate(void)
		{
			size_t iter = 0;
			nes_test_set result(NES_ROM_HEADER);

			for(; iter <= NES_TEST_ROM_MAX; ++iter) {
				result.insert(nes_test(NES_TEST_ROM_STRING(iter), NES_TEST_ROM_CALLBACK(iter), 
					nes_rom::acquire(), nes_test_rom::test_initialize, 
					nes_test_rom::test_uninitialize));
			}

			return result;
		}

		nes_test_t 
		_nes_test_rom::size(
			__in void *context
			)
		{
			size_t size;
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				try {
					size = inst->size();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()) {
					inst->initialize();
				}

				if(inst->size()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->load(NES_TEST_ROM_PATH_VALID_BANKS);

				if(inst->size() != NES_TEST_ROM_PATH_VALID_BANKS_LEN) {
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
		_nes_test_rom::test_initialize(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			try {

				inst = (nes_rom_ptr) context;
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
		_nes_test_rom::test_uninitialize(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			try {

				inst = (nes_rom_ptr) context;
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
		_nes_test_rom::uninitialize(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

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

				inst->uninitialize();

				if(!inst->is_allocated() || inst->is_initialized() 
						|| inst->is_loaded() 
						|| !inst->m_block.empty()) {
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
		_nes_test_rom::unload(
			__in void *context
			)
		{
			nes_rom_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			try {

				inst = (nes_rom_ptr) context;
				if(!inst) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->is_loaded()) {
					inst->unload();
				}

				try {
					inst->unload();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_loaded()) {
					inst->load(NES_TEST_ROM_PATH_VALID_HEADER);
				}

				inst->unload();

				if(!inst->is_allocated() || !inst->is_initialized() 
						|| inst->is_loaded() 
						|| !inst->m_block.empty()) {
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
	}
}

#endif // NDEBUG
