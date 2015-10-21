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

#include <cctype>
#include <cstring>
#include <fstream>
#include "../include/nes.h"
#include "../include/nes_rom_type.h"

namespace NES {

	namespace COMP {

		#define TV_MODE_DUAL "DUAL"

		static const std::string FLAG_6_MIRRORING_STR[] = {
			"Vert. arrange/Horz. mirror",
			"Horz. arrange/Vert. mirror",
			};

		#define FLAG_6_MIRRORING_STRING(_TYPE_) \
			((_TYPE_) > FLAG_6_MIRRORING_MAX ? UNKNOWN : \
			CHECK_STR(FLAG_6_MIRRORING_STR[_TYPE_]))

		static const std::string FLAG_9_1_TV_MODE_STR[] = {
			"NTSC", "PAL",
			};

		#define FLAG_9_1_TV_MODE_STRING(_TYPE_) \
			((_TYPE_) > FLAG_9_1_TV_MODE_MAX ? TV_MODE_DUAL : \
			CHECK_STR(FLAG_9_1_TV_MODE_STR[_TYPE_]))

		static const std::string FLAG_10_1_TV_MODE_STR[] = {
			"NTSC", TV_MODE_DUAL, TV_MODE_DUAL, "PAL",
			};

		#define FLAG_10_1_TV_MODE_STRING(_TYPE_) \
			((_TYPE_) > FLAG_10_1_TV_MODE_MAX ? TV_MODE_DUAL : \
			CHECK_STR(FLAG_10_1_TV_MODE_STR[_TYPE_]))

		static const std::string FLAG_12_2_TV_MODE_STR[] = {
			"NTSC", "PAL",
			};

		#define FLAG_12_2_TV_MODE_STRING(_TYPE_) \
			((_TYPE_) > FLAG_12_2_TV_MODE_MAX ? TV_MODE_DUAL : \
			CHECK_STR(FLAG_12_2_TV_MODE_STR[_TYPE_]))

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
			__out nes_memory_block &block,
			__in size_t index
			)
		{
			nes_rom_header head;
			size_t blocks, offset = sizeof(nes_rom_header);

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			header(head);
			blocks = head.rom_character;

			if(index >= blocks) {
				THROW_NES_ROM_EXCEPTION_MESSAGE(NES_ROM_EXCEPTION_INVALID_INDEX,
					"idx. %lu (max. %lu)", index, blocks - 1);
			}

			if(head.flag_6.trainer) {
				offset += ROM_TRAINER_LEN;
			}

			offset += ((head.rom_program * ROM_PROGRAM_LEN) 
				+ (index * ROM_CHARACTER_LEN));

			if(offset >= m_block.size() 
					|| ((offset + ROM_CHARACTER_LEN) > m_block.size())) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			block.clear();
			block.insert(block.begin(), m_block.begin() + offset, 
				m_block.begin() + offset + ROM_CHARACTER_LEN);

			return block.size();
		}

		size_t 
		_nes_rom::block_program(
			__out nes_memory_block &block,
			__in size_t index
			)
		{
			nes_rom_header head;
			size_t blocks, offset = sizeof(nes_rom_header);

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			header(head);
			blocks = head.rom_program;

			if(index >= blocks) {
				THROW_NES_ROM_EXCEPTION_MESSAGE(NES_ROM_EXCEPTION_INVALID_INDEX,
					"idx. %lu (max. %lu)", index, blocks - 1);
			}

			if(head.flag_6.trainer) {
				offset += ROM_TRAINER_LEN;
			}

			offset += (index * ROM_PROGRAM_LEN);

			if(offset >= m_block.size() 
					|| ((offset + ROM_PROGRAM_LEN) > m_block.size())) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			block.clear();
			block.insert(block.begin(), m_block.begin() + offset, 
				m_block.begin() + offset + ROM_PROGRAM_LEN);

			return block.size();
		}

		size_t 
		_nes_rom::header(
			__out nes_rom_header &head
			)
		{
			size_t result;

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(!m_loaded) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNLOADED);
			}

			if(m_block.size() < sizeof(nes_rom_header)) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			result = sizeof(nes_rom_header);
			std::memcpy((uint8_t *) &head, (uint8_t *) &m_block[0], 
				result);

			return result;
		}

		std::string 
		_nes_rom::header_as_string(
			__in const nes_rom_header &header,
			__in_opt bool verbose
			)
		{
			size_t iter = 0;
			uint32_t mapper = 0, rom_character = 0, rom_program = 0;
			std::stringstream result;

			if(!validate(header)) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			result << "header: \'";

			for(; iter < ROM_MAGIC_LEN; ++iter) {
				result << (std::isprint((char) header.magic[iter]) ? (char) header.magic[iter] : ' ');
			}

			rom_character = header.rom_character;
			rom_program = header.rom_program;
			result << "\'" << std::endl << "program rom: " << rom_program << " (x" << ROM_PROGRAM_LEN << ")" 
				<< std::endl << "character rom: " << rom_character << " (x" << ROM_CHARACTER_LEN << ")";

			if(verbose) {
				mapper = (((header.flag_7.mapper_high << BITS_PER_NIBBLE) & 0xf0)
					| (header.flag_6.mapper_low & 0xf));

				result << std::endl << "format: " << ((header.flag_7.format == ROM_INES_2) ? 2 : 1) 
					<< std::endl << "mapper: " << mapper
					<< std::endl << "[flag_6]"
					<< std::endl << "--- mirroring: " << FLAG_6_MIRRORING_STRING(header.flag_6.mirroring) 
					<< " (" << (int) header.flag_6.mirroring << ")"
 					<< std::endl << "--- sram present: " << (int) header.flag_6.sram
					<< std::endl << "--- trainer present: " << (int) header.flag_6.trainer
					<< std::endl << "--- four-scrren mode: "<< (int) header.flag_6.four_screen_mode
					<< std::endl << "[flag_7]"
					<< std::endl << "--- vs. unisystem: " << (int) header.flag_7.vs
					<< std::endl << "--- playchoice-10: " << (int) header.flag_7.pc;

				if(header.flag_7.format == ROM_INES_2) {
					mapper |= ((header.extension.ines_2.flag_8.mapper_high << BITS_PER_BYTE) 
						& 0xf00);
					rom_character |= ((header.extension.ines_2.flag_9.rom_character_high << BITS_PER_BYTE)
						& 0xf00);
					rom_program |= ((header.extension.ines_2.flag_9.rom_program_high << BITS_PER_BYTE)
						& 0xf00);

					result << std::endl << "[flag_8]" 
						<< std::endl << "--- mapper (ext): " << mapper
						<< std::endl << "--- submapper: " 
						<< (int) header.extension.ines_2.flag_8.mapper_sub
						<< std::endl << "[flag_9]"
						<< std::endl << "--- program rom (ext): " << rom_program
						<< std::endl << "--- character rom (ext): " << rom_character
						<< std::endl << "[flag_10]"
						<< std::endl << "--- program non-sram: "
						<< (int) header.extension.ines_2.flag_10.rom_program_non_sram
						<< std::endl << "--- program sram: "
						<< (int) header.extension.ines_2.flag_10.rom_program_sram
						<< std::endl << "[flag_11]"
						<< std::endl << "--- character non-sram: "
						<< (int) header.extension.ines_2.flag_11.rom_character_non_sram
						<< std::endl << "--- character sram: "
						<< (int) header.extension.ines_2.flag_11.rom_character_sram
						<< std::endl << "[flag_12]"
						<< std::endl << "--- tv mode: "
						<< FLAG_12_2_TV_MODE_STRING(header.extension.ines_2.flag_12.mode)
						<< " (" << (int) header.extension.ines_2.flag_12.mode << ")"
						<< std::endl << "[flag_13]"
						<< std::endl << "--- vs. ppu: "
						<< (int) header.extension.ines_2.flag_13.vs_ppu
						<< std::endl << "--- vs. mode: "
						<< (int) header.extension.ines_2.flag_13.vs_mode; 
				} else {
					result << std::endl << "[flag_8]" 
						<< std::endl << "--- program ram: " 
						<< (int) header.extension.ines_1.block_program_ram
						<< " (x" << RAM_PROGRAM_LEN << ")"
						<< std::endl << "[flag_9]" 
						<< std::endl << "--- tv mode: " 
						<< FLAG_9_1_TV_MODE_STRING(header.extension.ines_1.flag_9.mode)
						<< " (" << (int) header.extension.ines_1.flag_9.mode << ")"
						<< std::endl << "flag_10]" 
						<< std::endl << "--- tv mode: " 
						<< FLAG_10_1_TV_MODE_STRING(header.extension.ines_1.flag_10.mode)
						<< " (" << (int) header.extension.ines_1.flag_10.mode << ")"
						<< std::endl << "--- program ram present: " 
						<< (int) header.extension.ines_1.flag_10.ram
						<< std::endl << "--- bus conflict present: "
						<< (int) header.extension.ines_1.flag_10.bus_conflict;
				}
			}

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

			if(m_loaded) {
				unload();
			}
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
			return (m_initialized && m_loaded);
		}

		void 
		_nes_rom::load(
			__in const nes_memory_block &block
			)
		{
			nes_rom_header head;

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(block.size() < sizeof(nes_rom_header)) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			m_block = block;
			m_loaded = true;
			header(head);

			if(!validate(head)) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_MALFORMED);
			}

			if(head.flag_7.format == ROM_INES_2) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNSUPPORTED);
			}
		}

		void 
		_nes_rom::load(
			__in const std::string &input
			)
		{
			size_t len;
			nes_memory_block block;

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			std::fstream file(input.c_str(), std::ios::in | std::ios::binary);
			if(!file) {
				THROW_NES_ROM_EXCEPTION_MESSAGE(NES_ROM_EXCEPTION_FILE_NOT_FOUND,
					"%s", CHECK_STR(input));
			}

			file.seekg(0, std::ios::end);
			len = file.tellg();
			block.resize(len);
			file.seekg(0, std::ios::beg);
			file.read((char *) &block[0], len);
			file.close();
			load(block);
		}

		size_t 
		_nes_rom::size(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			return m_block.size();
		}

		std::string 
		_nes_rom::to_string(
			__in_opt bool verbose
			)
		{
			nes_rom_header head;
			std::stringstream result;

			ATOMIC_CALL_RECUR(m_lock);

			result << "<" << NES_ROM_HEADER << "> ("
				<< (m_initialized ? INITIALIZED : UNINITIALIZED) << ", "
				<< (m_loaded ? "LOADED" : "UNLOADED");

			if(verbose) {
				result << "ptr. 0x" << VALUE_AS_HEX(nes_rom_ptr, this);
			}

			result << ")";

			if(m_initialized && m_loaded) {
				header(head);
				result << ", SZ: " << (m_block.size() / BYTES_PER_KBYTE) << " KB (" 
					<< m_block.size() << " BTYES)" << std::endl 
					<< nes_rom::header_as_string(head, verbose);
			}

			return result.str();
		}

		void 
		_nes_rom::uninitialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_ROM_EXCEPTION(NES_ROM_EXCEPTION_UNINITIALIZED);
			}

			if(m_loaded) {
				unload();
			}

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

			m_block.clear();
			m_loaded = false;
		}

		bool 
		_nes_rom::validate(
			__in const nes_rom_header &header
			)
		{
			return !std::memcmp(header.magic, ROM_MAGIC, ROM_MAGIC_LEN);
		}
	}
}
