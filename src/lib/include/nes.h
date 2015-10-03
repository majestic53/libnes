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

#ifndef NES_H_
#define NES_H_

//#define NDEBUG

#ifndef NES
#define NES libnes
#endif // NES

#include "nes_defines.h"
#include "nes_exception.h"

using namespace NES;

#ifndef COMP
#define COMP component
#endif // COMP

#include "nes_memory.h"
#include "nes_cpu.h"

using namespace NES::COMP;

#ifndef NDEBUG
#ifndef TEST
#define TEST test
#endif // TEST

#include "nes_test.h"
#include "nes_test_cpu.h"
#include "nes_test_memory.h"

using namespace NES::TEST;

#endif // NDEBUG

namespace NES {

	typedef class _nes {

		public:

			~_nes(void);

			static _nes *acquire(void);

			nes_cpu_ptr acquire_cpu(void);

			nes_memory_ptr acquire_memory(void);

			void initialize(void);

			static bool is_allocated(void);

			bool is_initialized(void);

#ifndef NDEBUG
			static bool run_tests(
				__in std::stringstream &stream,
				__inout size_t &success,
				__inout size_t &failure,
				__inout size_t &inconclusive
				);
#endif // NDEBUG

			std::string to_string(
				__in_opt uint16_t address = 0,
				__in_opt uint16_t offset = 0,
				__in_opt bool verbose = false
				);

			void uninitialize(void);

			static std::string version(void);

		protected:

			_nes(void);

			_nes(
				__in const _nes &other
				);

			_nes &operator=(
				__in const _nes &other
				);

			static void _delete(void);

			bool m_initialized;

			static _nes *m_instance;

			nes_cpu_ptr m_instance_cpu;

			nes_memory_ptr m_instance_memory;

		private:

			std::recursive_mutex m_lock;

	} nes, *nes_ptr;
}

#endif // NES_H_
