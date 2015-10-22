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

#include "../lib/include/libnes.h"
#include "../lib/include/nes.h"

#define USAGE_ARG_MIN 3
#define USAGE_ARG_STR " [INPUT] [DEBUG]"

int 
main(
	__in int argc,
	__in const char **argv
	)
{
	neserr_t result = NES_ERR_NONE;
#ifndef NDEBUG
	std::stringstream stream;
	size_t failure, inconclusive, success;
#else
	nes_context context = { 0 };
#endif // NDEBUG

	try {
		std::cout << "NES " << nes_version() << std::endl;

#ifndef NDEBUG
		if(!nes::run_tests(stream, success, failure, inconclusive)) {
			std::cout << "---" << std::endl << stream.str() << std::endl;
		}
#else

		if(argc < USAGE_ARG_MIN) {
			std::cerr << "USAGE: " << argv[0] << USAGE_ARG_STR << std::endl;
			result = NES_ERR_INVALID_ARGUMENT;
		} else {

			result = nes_initialize(&context);
			if(!NES_SUCCESS(result)) {
				std::cerr << "nes_initialize failed, status 0x" 
					<< VALUE_AS_HEX(neserr_t, result) << std::endl;
			} else {

				result = nes_run(&context, argv[1], std::atoi(argv[2]));
				if(!NES_SUCCESS(result)) {
					std::cerr << "nes_run failed, status 0x" 
						<< VALUE_AS_HEX(neserr_t, result) << std::endl;
				}

				result = nes_uninitialize(&context);
				if(!NES_SUCCESS(result)) {
					std::cerr << "nes_uninitialize failed, status 0x" 
						<< VALUE_AS_HEX(neserr_t, result) << std::endl;
				}
			}
		}
#endif // NDEBUG		
	} catch(nes_exception &exc) {
		std::cerr << exc.to_string(true) << std::endl;
		result = NES_ERR_FAILURE;
	} catch(std::exception &exc) {
		std::cerr << exc.what() << std::endl;
		result = NES_ERR_FAILURE;
	}

	return result;
}
