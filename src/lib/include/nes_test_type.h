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
#ifndef NES_TEST_TYPE_H_
#define NES_TEST_TYPE_H_

#include "nes_type.h"

namespace NES {

	namespace TEST {

		#define NES_TEST_HEADER NES_HEADER "::TEST"

		enum {
			NES_TEST_EXCEPTION_FOUND = 0,
			NES_TEST_EXCEPTION_INVALID_NAME_TEST,
			NES_TEST_EXCEPTION_INVALID_NAME_TEST_SET,
			NES_TEST_EXCEPTION_NOT_FOUND,
			NES_TEST_EXCEPTION_UNDEFINED_CALLBACK,
			NES_TEST_EXCEPTION_UNKNOWN_RESULT,
		};

		#define NES_TEST_EXCEPTION_MAX NES_TEST_EXCEPTION_UNKNOWN_RESULT

		static const std::string NES_TEST_EXCEPTION_STR[] = {
			"Test exists",
			"Invalid test name",
			"Invalid test set name",
			"Test does not exist",
			"Undefined test callback",
			"Unknown test result",
			};

		#define NES_TEST_EXCEPTION_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_EXCEPTION_MAX ? EXCEPTION_UNKNOWN : \
			CHECK_STR(NES_TEST_EXCEPTION_STR[_TYPE_]))

		#define THROW_NES_TEST_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(NES_TEST_HEADER, \
			NES_TEST_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_NES_TEST_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(NES_TEST_HEADER, \
			NES_TEST_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _nes_test;
		typedef _nes_test nes_test, *nes_test_ptr;

		class _nes_test_set;
		typedef _nes_test_set nes_test_set, *nes_test_set_ptr;
			
	}
}

#endif // NES_TEST_TYPE_H_
#endif // NDEBUG
