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

		enum {
			NES_MEMORY_TEST_ACQUIRE = 0,
			NES_MEMORY_TEST_AT,
			NES_MEMORY_TEST_CLEAR,
			NES_MEMORY_TEST_FLAG_CHECK,
			NES_MEMORY_TEST_FLAG_CLEAR,
			NES_MEMORY_TEST_FLAG_SET,
			NES_MEMORY_TEST_INITIALIZE,
			NES_MEMORY_TEST_IS_ALLOCATED,
			NES_MEMORY_TEST_IS_INITIALIZE,
			NES_MEMORY_TEST_READ,
			NES_MEMORY_TEST_UNINITIALIZE,
			NES_MEMORY_TEST_WRITE,
		};

		#define NES_MEMORY_TEST_MAX NES_MEMORY_TEST_WRITE

		static const std::string NES_MEMORY_TEST_STR[] = {
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

		#define NES_MEMORY_TEST_STRING(_TYPE_) \
			((_TYPE_) > NES_MEMORY_TEST_MAX ? UNKNOWN : \
			CHECK_STR(NES_MEMORY_TEST_STR[_TYPE_]))

		static const nes_test_cb NES_MEMORY_TEST_CB[] = {
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

		#define NES_MEMORY_TEST_CALLBACK(_TYPE_) \
			((_TYPE_) > NES_MEMORY_TEST_MAX ? NULL : \
			NES_MEMORY_TEST_CB[_TYPE_])

		nes_test_t 
		_nes_test_memory::acquire(
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
		_nes_test_memory::at(
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
		_nes_test_memory::clear(
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
		_nes_test_memory::flag_check(
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
		_nes_test_memory::flag_clear(
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
		_nes_test_memory::flag_set(
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
		_nes_test_memory::initialize(
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
		_nes_test_memory::is_allocated(
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
		_nes_test_memory::is_initialized(
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
		_nes_test_memory::read(
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

		nes_test_set 
		_nes_test_memory::set_generate(void)
		{
			size_t iter = 0;
			nes_test_set result(NES_MEMORY_HEADER);

			for(; iter <= NES_MEMORY_TEST_MAX; ++iter) {
				result.insert(nes_test(NES_MEMORY_TEST_STRING(iter), NES_MEMORY_TEST_CALLBACK(iter), 
					nes_memory::acquire(), nes_test_memory::set_initialize, 
					nes_test_memory::set_uninitialize));
			}

			return result;
		}

		nes_test_t 
		_nes_test_memory::set_initialize(
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
		_nes_test_memory::set_uninitialize(
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
		_nes_test_memory::uninitialize(
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
		_nes_test_memory::write(
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
	}
}

#endif // NDEBUG
