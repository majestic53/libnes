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

#ifndef LIBNES_H_
#define LIBNES_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum {
	NES_ERR_NONE = 0,
	NES_ERR_FAILURE = 0x8000000UL,
	NES_ERR_INVALID_ARGUMENT,
	NES_ERR_INVALID_STATE,
} neserr_t;

#define NES_SUCCESS(_ERR_) (((signed) _ERR_) >= NES_ERR_NONE)

typedef struct {
	int major;
	int minor;
	void *session;
} nes_context;

neserr_t nes_initialize(
	nes_context *context
	);

int nes_is_valid(
	nes_context *context
	);

neserr_t nes_uninitialize(
	nes_context *context
	);

const char *nes_version(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIBNES_H_
