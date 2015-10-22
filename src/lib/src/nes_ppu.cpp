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
#include "../include/nes_ppu_type.h"

namespace NES {

	namespace COMP {

		_nes_ppu *_nes_ppu::m_instance = NULL;

		_nes_ppu::_nes_ppu(void) :
			m_cycles(0),
			m_initialized(false),
			m_memory(nes_memory::acquire()),
			m_started(false)
		{
			std::atexit(nes_ppu::_delete);
		}

		_nes_ppu::~_nes_ppu(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_nes_ppu::_delete(void)
		{

			if(nes_ppu::m_instance) {
				delete nes_ppu::m_instance;
				nes_ppu::m_instance = NULL;
			}
		}

		_nes_ppu *
		_nes_ppu::acquire(void)
		{

			if(!nes_ppu::m_instance) {

				nes_ppu::m_instance = new nes_ppu;
				if(!nes_ppu::m_instance) {
					THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_ALLOCATED);
				}
			}

			return nes_ppu::m_instance;
		}

		void 
		_nes_ppu::clear(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			clear(NES_MEM_PPU);
			clear(NES_MEM_PPU_OAM);
		}

		void 
		_nes_ppu::clear(
			__in nes_memory_t type
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			reset();

			switch(type) {
				case NES_MEM_PPU:
				case NES_MEM_PPU_OAM:
					m_memory->clear(type);
					break;
				default:
					THROW_NES_PPU_EXCEPTION_MESSAGE(NES_PPU_EXCEPTION_INVALID_TYPE,
						"type. %lu", type);
			}
		}

		uint32_t 
		_nes_ppu::cycles(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			return m_cycles;
		}

		void 
		_nes_ppu::initialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_INITIALIZED);
			}

			m_initialized = true;
			m_cycles = 0;

			if(m_started) {
				stop();
			}
		}

		bool 
		_nes_ppu::is_allocated(void)
		{
			return (nes_ppu::m_instance != NULL);
		}

		bool 
		_nes_ppu::is_initialized(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_initialized;
		}

		bool 
		_nes_ppu::is_started(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (m_initialized && m_started);
		}

		uint8_t 
		_nes_ppu::load(
			__in nes_memory_t type,
			__in uint16_t address
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_memory->at(type, address);
		}

		uint16_t 
		_nes_ppu::load_word(
			__in nes_memory_t type,
			__in uint16_t address
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (load(type, address) | (load(type, address + 1) << BITS_PER_BYTE));
		}

		void 
		_nes_ppu::reset(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			m_cycles = 0;
		}

		void 
		_nes_ppu::start(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			if(m_started) {
				THROW_NES_PPU_EXCEPTION(NES_PUU_EXCEPTION_STARTED);
			}

			m_started = true;
		}

		void 
		_nes_ppu::step(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			if(!m_started) {
				THROW_NES_PPU_EXCEPTION(NES_PUU_EXCEPTION_STOPPED);
			}

			// TODO

			++m_cycles;
		}

		void 
		_nes_ppu::stop(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			if(!m_started) {
				THROW_NES_PPU_EXCEPTION(NES_PUU_EXCEPTION_STOPPED);
			}

			m_started = false;
		}

		void 
		_nes_ppu::store(
			__in nes_memory_t type,
			__in uint16_t address,
			__in uint8_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_memory->at(type, address) = value;
		}

		void 
		_nes_ppu::store_word(
			__in nes_memory_t type,
			__in uint16_t address,
			__in uint16_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			store(type, address, value & UINT8_MAX);
			store(type, address + 1, (value >> BITS_PER_BYTE) & UINT8_MAX);
		}

		std::string 
		_nes_ppu::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			ATOMIC_CALL_RECUR(m_lock);

			result << "<" << NES_PPU_HEADER << "> ("
				<< (m_initialized ? INITIALIZED : UNINITIALIZED);

			if(verbose) {
				result << "ptr. 0x" << VALUE_AS_HEX(nes_ppu_ptr, this);
			}

			result << ")";

			if(m_initialized) {
				result << ", CYC: " << m_cycles;
			}

			return result.str();
		}

		void 
		_nes_ppu::uninitialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_PPU_EXCEPTION(NES_PPU_EXCEPTION_UNINITIALIZED);
			}

			if(m_started) {
				stop();
			}

			m_cycles = 0;
			m_initialized = false;
		}
	}
}
