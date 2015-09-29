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

#ifndef NES_EXCEPTION_H_
#define NES_EXCEPTION_H_

#include <stdexcept>

namespace NES {

	#define EXCEPTION_HEADER "Exception"
	#define EXCEPTION_UNKNOWN "Unknown exception"

	#define THROW_EXCEPTION(_HEADER_, _EXCEPT_) \
		nes_exception::generate(_HEADER_, _EXCEPT_, __FUNCTION__, \
		__FILE__, __LINE__, NULL)
	#define THROW_EXCEPTION_MESSAGE(_HEADER_, _EXCEPT_, _FORMAT_, ...) \
		nes_exception::generate(_HEADER_, _EXCEPT_, __FUNCTION__, \
		__FILE__, __LINE__, _FORMAT_, __VA_ARGS__)

	typedef class _nes_exception :
			public std::runtime_error {

		public:

			_nes_exception(
				__in_opt const std::string &message = std::string(),
				__in_opt const std::string &function = std::string(),
				__in_opt const std::string &file = std::string(),
				__in_opt size_t line = 0
				);

			_nes_exception(
				__in const _nes_exception &other
				);

			virtual ~_nes_exception(void);

			_nes_exception &operator=(
				__in const _nes_exception &other
				);

			std::string file(void);

			std::string function(void);

			static void generate(
				__in const std::string &header,
				__in const std::string &message,
				__in const std::string &function,
				__in const std::string &file,
				__in size_t line,
				__in const char *format,
				...
				);

			size_t line(void);

			virtual std::string to_string(
				__in_opt bool verbose = false
				);

		protected:

			std::string m_file, m_function;

			size_t m_line;

		private:

			std::recursive_mutex m_lock;

	} nes_exception, *nes_exception_ptr;
}

#endif // NES_EXCEPTION_H_
