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

#include <random>
#include "../include/nes.h"
#include "../include/nes_type.h"

namespace NES {

	nes_ptr nes::m_instance = NULL;

	_nes::_nes(void) :
		m_initialized(false),
		m_instance_cpu(nes_cpu::acquire()),
		m_instance_memory(nes_memory::acquire()),
		m_instance_rom(nes_rom::acquire())
	{
		std::atexit(nes::_delete);
	}

	_nes::~_nes(void)
	{

		if(m_initialized) {
			uninitialize();
		}
	}

	void 
	_nes::_delete(void)
	{

		if(nes::m_instance) {
			delete nes::m_instance;
			nes::m_instance = NULL;
		}
	}

	_nes *
	_nes::acquire(void)
	{

		if(!nes::m_instance) {

			nes::m_instance = new nes;
			if(!nes::m_instance) {
				THROW_NES_EXCEPTION(NES_EXCEPTION_ALLOCATED);
			}
		}

		return nes::m_instance;
	}

	nes_cpu_ptr 
	_nes::acquire_cpu(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_instance_cpu;
	}

	nes_memory_ptr 
	_nes::acquire_memory(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_instance_memory;
	}

	nes_rom_ptr 
	_nes::acquire_rom(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_instance_rom;
	}

	void 
	_nes::initialize(void)
	{
		ATOMIC_CALL_RECUR(m_lock);

		if(m_initialized) {
			THROW_NES_EXCEPTION(NES_EXCEPTION_INITIALIZED);
		}

		m_initialized = true;
		m_instance_memory->initialize();
		m_instance_cpu->initialize();
		m_instance_rom->initialize();

		// TODO: initialize components
	}

	bool 
	_nes::is_allocated(void)
	{
		return (nes::m_instance != NULL);
	}

	bool 
	_nes::is_initialized(void)
	{
		ATOMIC_CALL_RECUR(m_lock);
		return m_initialized;
	}

	void 
	_nes::run(
		__in const std::string &input,
		__in_opt bool debug
		)
	{
		ATOMIC_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_NES_EXCEPTION(NES_EXCEPTION_UNINITIALIZED);
		}

		// TODO: run session
	}

#ifndef NDEBUG
	bool 
	_nes::run_tests(
		__in std::stringstream &stream,
		__inout size_t &success,
		__inout size_t &failure,
		__inout size_t &inconclusive
		)
	{
		bool result = true;

		std::srand((uint32_t) std::time(NULL));
		success = 0;
		failure = 0;
		inconclusive = 0;
		stream.clear();
		stream.str(std::string());
		nes_test_set test_set_mem = nes_test_memory::set_generate();
		test_set_mem.run_all(success, failure, inconclusive);
		stream << test_set_mem.to_string() << std::endl;
		nes_test_set test_set_cpu = nes_test_cpu::set_generate();
		test_set_cpu.run_all(success, failure, inconclusive);
		stream << test_set_cpu.to_string() << std::endl;
		nes_test_set test_set_rom = nes_test_rom::set_generate();
		test_set_rom.run_all(success, failure, inconclusive);
		stream << test_set_rom.to_string() << std::endl;

		// TODO: run test sets

		stream << "Total: " << success << "/" << failure << "/" << inconclusive 
			<< std::endl << "Verdict: ";

		if(failure) {
			stream << NES_TEST_RESULT_STRING(NES_TEST_FAILURE);
			result = false;
		} else if(inconclusive) {
			stream << NES_TEST_RESULT_STRING(NES_TEST_INCONCLUSIVE);
			result = false;
		} else {
			stream << NES_TEST_RESULT_STRING(NES_TEST_SUCCESS);
		}

		return result;
	}
#endif // NDEBUG

	std::string 
	_nes::to_string(
		__in_opt uint16_t address,
		__in_opt uint16_t offset,
		__in_opt bool verbose
		)
	{
		std::stringstream result;

		ATOMIC_CALL_RECUR(m_lock);

		result << "<" << NES_HEADER << "> (" 
			<< (m_initialized ? INITIALIZED : UNINITIALIZED); 

		if(verbose) {
			result << ", ptr. 0x" << VALUE_AS_HEX(nes_ptr, this);
		}

		result << ")"
			<< std::endl << m_instance_memory->to_string(address, offset, verbose)
			<< std::endl << m_instance_cpu->to_string(verbose)
			<< std::endl << m_instance_rom->to_string(verbose);

		// TODO: print components

		return result.str();
	}

	void 
	_nes::uninitialize(void)
	{
		ATOMIC_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_NES_EXCEPTION(NES_EXCEPTION_UNINITIALIZED);
		}

		m_instance_rom->uninitialize();
		m_instance_cpu->uninitialize();
		m_instance_memory->uninitialize();

		// TODO: uninitialize components

		m_initialized = false;
	}

	std::string 
	_nes::version(void)
	{
		return VERSION_STR();
	}
}
