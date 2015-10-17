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
#include "../include/nes_rom_type.h"

namespace NES {

	namespace COMP {

		_nes_rom *_nes_rom::m_instance = NULL;

		_nes_rom::_nes_rom(void) :
			m_initialized(false),
			m_loaded(false)
		{
			std::atexit(nes_rom::_delete);
		}

		_nes_rom::~_nes_rom(void)
		{

			if(is_initialized()) {
				uninitialize();
			}
		}

		void 
		_nes_rom::_delete(void)
		{

			if(nes_rom::m_instance) {
				delete nes_rom::m_instance;
				nes_rom::m_instance = NULL;
			}
		}

		_nes_rom *
		_nes_rom::acquire(void)
		{

			if(!nes_rom::m_instance) {

				nes_rom::m_instance = new nes_rom;
				if(!nes_rom::m_instance) {
					THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_ALLOCATED);
				}
			}

			return nes_rom::m_instance;
		}

		size_t 
		_nes_rom::block_character(
			__in nes_memory_block &block,
			__in size_t index
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			// TODO

			return block.size();
		}

		size_t 
		_nes_rom::block_program(
			__in nes_memory_block &block,
			__in size_t index
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			// TODO

			return block.size();
		}

		nes_rom_header 
		_nes_rom::header(void)
		{
			nes_rom_header result;

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			// TODO

			return result;
		}

		std::string 
		_nes_rom::header_as_string(
			__in const nes_rom_header &header
			)
		{
			std::stringstream result;

			// TODO

			return result.str();
		}

		void 
		_nes_rom::initialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_INITIALIZED);
			}

			m_initialized = true;
			m_loaded = false;
			m_rom.clear();

			// TODO
		}

		bool 
		_nes_rom::is_allocated(void)
		{
			return (nes_rom::m_instance != NULL);
		}

		bool 
		_nes_rom::is_initialized(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_initialized;
		}

		bool 
		_nes_rom::is_loaded(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			return m_loaded;
		}

		void 
		_nes_rom::load(
			__in const std::string &input
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			// TODO

			m_loaded = true;
		}

		size_t 
		_nes_rom::size(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			return m_rom.size();
		}

		std::string 
		_nes_rom::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			ATOMIC_CALL_RECUR(m_lock);

			result << "<" << NES_ROM_HEADER << "> ("
				<< (m_initialized ? INITIALIZED : UNINITIALIZED) << ", "
				<< (m_loaded ? "LOADED" : "UNLOADED");

			if(verbose) {
				result << ", ptr. 0x" << VALUE_AS_HEX(nes_rom_ptr, this);
			}

			result << ")";

			// TODO

			return result.str();
		}

		void 
		_nes_rom::uninitialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			// TODO

			m_rom.clear();
			m_loaded = false;
			m_initialized = false;
		}

		void 
		_nes_rom::unload(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			m_rom.clear();
			m_loaded = false;
		}
	}
}
