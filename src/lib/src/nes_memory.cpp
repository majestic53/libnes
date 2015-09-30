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

namespace NES {

	namespace COMP {

		#define NES_MEMORY_MAX UINT16_MAX

		_nes_memory *_nes_memory::m_instance = NULL;

		_nes_memory::_nes_memory(void) :
			m_initialized(false)
		{
			std::atexit(nes_memory::_delete);
		}

		_nes_memory::~_nes_memory(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_nes_memory::_delete(void)
		{

			if(nes_memory::m_instance) {
				delete nes_memory::m_instance;
				nes_memory::m_instance = NULL;
			}
		}

		_nes_memory *
		_nes_memory::acquire(void)
		{

			if(!nes_memory::m_instance) {

				nes_memory::m_instance = new nes_memory;
				if(!nes_memory::m_instance) {
					THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_ALLOCATED);
				}
			}

			return nes_memory::m_instance;
		}

		std::string 
		_nes_memory::address_as_string(
			__in uint16_t address,
			__in_opt bool verbose
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return nes_memory::address_as_string(m_block, address, verbose);
		}

		std::string 
		_nes_memory::address_as_string(
			__in const nes_memory_block &block,
			__in uint16_t address,
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			uint8_t iter = BITS_PER_BYTE, value;

			if(address >= block.size()) {
				THROW_NES_MEMORY_EXCEPTION_MESSAGE(NES_MEMORY_EXCEPTION_INVALID_ADDRESS,
					"addr. 0x%x (max. 0x%x)", address, block.size() - 1);
			}

			value = block.at(address);

			if(verbose) {
				result << "0x" << VALUE_AS_HEX(uint16_t, address) << ": ";
			}

			result << "0x" << VALUE_AS_HEX(uint8_t, block.at(address)) << " [0b";

			while(iter--) {
				result << ((value & 0x80) ? "1" : "0");
				value <<= 1;
			}

			result << "]";

			return result.str();
		}

		uint8_t &
		_nes_memory::at(
			__in uint16_t address
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= m_block.size()) {
				THROW_NES_MEMORY_EXCEPTION_MESSAGE(NES_MEMORY_EXCEPTION_INVALID_ADDRESS,
					"addr. 0x%x (max. 0x%x)", address, NES_MEMORY_MAX);
			}

			return m_block.at(address);
		}

		std::string 
		_nes_memory::block_as_string(
			__in const nes_memory_block &block,
			__in uint16_t address,
			__in uint16_t offset,
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			uint16_t fill, iter, length;

			if(address >= block.size()) {
				THROW_NES_MEMORY_EXCEPTION_MESSAGE(NES_MEMORY_EXCEPTION_INVALID_ADDRESS,
					"addr. {0x%x - 0x%x} (max. 0x%x)", address, address + offset, 
					block.size() - 1);
			}

			result << "[Sz. " << (offset / BYTES_PER_KBYTE) << " KB (" 
				<< offset << " bytes)]";

			length = std::min(address + offset, NES_MEMORY_MAX + 1);

			fill = (address - (address % BLOCK_WIDTH));
			if(fill) {
				result << std::endl << "0x" << VALUE_AS_HEX(uint16_t, fill) 
					<< " |";

				for(iter = fill; iter < address; ++iter) {
					result << " --";
				}
			}

			for(iter = address; iter < length; ++iter) {

				if(!(iter % BLOCK_WIDTH)) {
					result << std::endl << "0x" << VALUE_AS_HEX(uint16_t, iter) 
						<< " |";
				}

				result << " " << VALUE_AS_HEX(uint8_t, block.at(iter));
			}

			if(iter % BLOCK_WIDTH) {

				fill = (iter + (BLOCK_WIDTH - (iter % BLOCK_WIDTH)));
				if(fill) {

					for(; iter < fill; ++iter) {
						result << " --";
					}
				}
			}

			return result.str();
		}

		void 
		_nes_memory::clear(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			m_block.clear();
			m_block.resize(NES_MEMORY_MAX + 1, 0);
		}

		bool 
		_nes_memory::flag_check(
			__in uint16_t address,
			__in uint8_t flag
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (at(address) & flag);
		}

		void 
		_nes_memory::flag_clear(
			__in uint16_t address,
			__in uint8_t flag
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			at(address) &= ~flag;
		}

		void 
		_nes_memory::flag_set(
			__in uint16_t address,
			__in uint8_t flag
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			at(address) |= flag;
		}

		void 
		_nes_memory::initialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_INITIALIZED);
			}

			m_initialized = true;
			clear();
		}

		bool 
		_nes_memory::is_allocated(void)
		{
			return (nes_memory::m_instance != NULL);
		}

		bool 
		_nes_memory::is_initialized(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_initialized;
		}

		std::string 
		_nes_memory::to_string(
			__in uint16_t address,
			__in uint16_t offset,
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			ATOMIC_CALL_RECUR(m_lock);

			result << "<" << NES_MEMORY_HEADER << "> (" 
				<< (m_initialized ? INITIALIZED : UNINITIALIZED); 

			if(verbose) {
				result << ", ptr. 0x" << VALUE_AS_HEX(nes_memory_ptr, this);
			}

			result << ")";

			if(m_initialized) {
				result << std::endl 
					<< nes_memory::block_as_string(m_block, address, offset, 
						verbose);
			}

			return result.str();
		}

		void 
		_nes_memory::uninitialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			m_block.clear();
			m_initialized = false;
		}

		void 
		_nes_memory::write(
			__in uint16_t address,
			__in const nes_memory_block &block
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_MEMORY_EXCEPTION(NES_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= m_block.size()) {
				THROW_NES_MEMORY_EXCEPTION_MESSAGE(NES_MEMORY_EXCEPTION_INVALID_ADDRESS,
					"addr. 0x%x", address);
			}

			m_block.insert(m_block.begin() + address, block.begin(), block.end());
		}
	}
}
