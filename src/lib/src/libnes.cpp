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

#include <cstring>
#include "../include/libnes.h"
#include "../include/nes.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

neserr_t 
nes_initialize(
	__inout nes_context *context
	)
{
	nes_ptr inst = NULL;
	neserr_t result = NES_ERR_NONE;

	if(!context) {
		result = NES_ERR_INVALID_ARGUMENT;
		goto exit;
	}

	if(context->session) {
		result = NES_ERR_INVALID_STATE;
		goto exit;
	}

	try {

		inst = nes::acquire();
		if(!inst) {
			result = NES_ERR_FAILURE;
			goto exit;
		}

		if(!inst->is_initialized()) {
			inst->initialize();
		}
	} catch(...) {
		result = NES_ERR_FAILURE;
		goto exit;
	}

	context->major = VERSION_MAJ;
	context->minor = VERSION_MIN;
	context->session = inst;
	
exit:
	return result;
}

int 
nes_is_valid(
	__in nes_context *context
	)
{
	int result = 1;
	nes_ptr inst = NULL;

	if(!context) {
		result = 0;
		goto exit;
	}

	if(context->session) {

		inst = (nes_ptr) context->session;
		if(!inst || !inst->is_initialized()) {
			result = 0;
			goto exit;
		}
	}

exit:
	return result;
}

neserr_t 
nes_run(
	__inout nes_context *context,
	__in const char *input,
	__in int debug
	)
{
	neserr_t result = NES_ERR_NONE;

	if(!context || !input) {
		result = NES_ERR_INVALID_ARGUMENT;
		goto exit;
	}

	if(!context->session) {
		result = NES_ERR_INVALID_STATE;
		goto exit;
	}

	try {
		((nes_ptr) context->session)->run(input, debug != NES_NO_DEBUG);
	} catch(...) {
		result = NES_ERR_FAILURE;
		goto exit;
	}

exit:
	return result;
}

neserr_t 
nes_uninitialize(
	__inout nes_context *context
	)
{
	nes_ptr inst = NULL;
	neserr_t result = NES_ERR_NONE;

	if(!context) {
		result = NES_ERR_INVALID_ARGUMENT;
		goto exit;
	}

	if(!context->session) {
		result = NES_ERR_INVALID_STATE;
		goto exit;
	}

	try {

		inst = (nes_ptr) context->session;
		if(!inst) {
			result = NES_ERR_FAILURE;
			goto exit;
		}

		if(inst->is_initialized()) {
			inst->uninitialize();
		}
	} catch(...) {
		result = NES_ERR_FAILURE;
		goto exit;
	}

	memset(context, 0, sizeof(nes_context));
	
exit:
	return result;
}

const char *
nes_version(void)
{
	return CHECK_STR(nes::version());
}

#ifdef __cplusplus
}
#endif // __cplusplus
