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

#include "../lib/include/nes.h"

int 
main(void)
{
	int result = 0;
	std::stringstream stream;

	try {
		std::cout << "NES " << nes::version() << std::endl;

#ifndef NDEBUG
		if(!nes::run_tests(stream)) {
			std::cout << "---" << std::endl << stream.str() << std::endl;
		} else {
#endif // NDEBUG

			// TODO
#ifndef NDEBUG
		}
#endif // NDEBUG
	} catch(nes_exception &exc) {
		std::cerr << exc.to_string(true) << std::endl;
		result = INVALID_TYPE(int);
	} catch(std::exception &exc) {
		std::cerr << exc.what() << std::endl;
		result = INVALID_TYPE(int);
	}

	return result;
}
