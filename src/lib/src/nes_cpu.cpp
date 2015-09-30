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
#include "../include/nes_cpu_type.h"

namespace NES {

	namespace COMP {


		#define CPU_CYCLES_INIT 0
		#define CPU_FLAG_BREAKPOINT 0x10
		#define CPU_FLAG_CARRY 0x1
		#define CPU_FLAG_INTERRUPT_ENABLED 0x4
		#define CPU_FLAG_NEGATIVE 0x80
		#define CPU_FLAG_OVERFLOW 0x40
		#define CPU_FLAG_ZERO 0x2
		#define CPU_INTERRUPT_IRQ_ADDRESS 0xfffe
		#define CPU_INTERRUPT_NMI_ADDRESS 0xfffa
		#define CPU_INTERRUPT_RESET_ADDRESS 0xfffc
		#define CPU_REGISTER_A_INIT 0
		#define CPU_REGISTER_P_INIT \
			(CPU_FLAG_INTERRUPT_ENABLED | CPU_FLAG_ZERO)
		#define CPU_REGISTER_PC_INIT 0
		#define CPU_REGISTER_SP_INIT 0xff
		#define CPU_REGISTER_SP_OFFSET 0x100
		#define CPU_REGISTER_X_INIT 0
		#define CPU_REGISTER_Y_INIT 0

		#define CPU_FLAG_CHECK(_P_, _FLAG_) ((_P_) & (_FLAG_))
		#define CPU_FLAG_CLEAR(_P_, _FLAG_) ((_P_) &= ~(_FLAG_))
		#define CPU_FLAG_SET(_P_, _FLAG_) ((_P_) |= (_FLAG_))

		_nes_cpu *_nes_cpu::m_instance = NULL;

		_nes_cpu::_nes_cpu(void) :
			m_cycles(CPU_CYCLES_INIT),
			m_initialized(false),
			m_memory(nes_memory::acquire()),
			m_register_a(CPU_REGISTER_A_INIT),
			m_register_p(CPU_REGISTER_P_INIT),
			m_register_sp(CPU_REGISTER_SP_INIT),
			m_register_x(CPU_REGISTER_X_INIT),
			m_register_y(CPU_REGISTER_Y_INIT),
			m_register_pc(CPU_REGISTER_PC_INIT)
		{
			std::atexit(nes_cpu::_delete);
		}

		_nes_cpu::~_nes_cpu(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}

		void 
		_nes_cpu::_delete(void)
		{

			if(nes_cpu::m_instance) {
				delete nes_cpu::m_instance;
				nes_cpu::m_instance = NULL;
			}
		}

		_nes_cpu *
		_nes_cpu::acquire(void)
		{

			if(!nes_cpu::m_instance) {

				nes_cpu::m_instance = new nes_cpu;
				if(!nes_cpu::m_instance) {
					THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_ALLOCATED);
				}
			}

			return nes_cpu::m_instance;
		}

		void 
		_nes_cpu::clear(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			m_cycles = CPU_CYCLES_INIT;
			m_register_a = CPU_REGISTER_A_INIT;
			m_register_p = CPU_REGISTER_P_INIT;
			m_register_pc = CPU_REGISTER_PC_INIT;
			m_register_sp = CPU_REGISTER_SP_INIT;
			m_register_x = CPU_REGISTER_X_INIT;
			m_register_y = CPU_REGISTER_Y_INIT;
		}

		uint32_t 
		_nes_cpu::cycles(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			return m_cycles;
		}

		void 
		_nes_cpu::initialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_INITIALIZED);
			}

			m_initialized = true;
			clear();
		}

		void 
		_nes_cpu::interrupt(
			__in uint16_t address,
			__in_opt bool breakpoint
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			push_word(m_register_pc);
			m_register_pc = address;

			if(breakpoint) {
				CPU_FLAG_SET(m_register_p, CPU_FLAG_BREAKPOINT);
			}

			push(m_register_p);	
		}

		void 
		_nes_cpu::interrupt_return(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_register_p = pop();
			CPU_FLAG_CLEAR(m_register_p, CPU_FLAG_BREAKPOINT);
			m_register_pc = pop_word();
		}

		void 
		_nes_cpu::irq(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			if(CPU_FLAG_CHECK(m_register_p, CPU_FLAG_INTERRUPT_ENABLED)) {
				interrupt(CPU_INTERRUPT_IRQ_ADDRESS);
			}
		}

		bool 
		_nes_cpu::is_allocated(void)
		{
			return (nes_cpu::m_instance != NULL);
		}

		bool 
		_nes_cpu::is_initialized(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_initialized;
		}

		uint8_t 
		_nes_cpu::load(
			__in uint16_t address
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_memory->at(address);
		}

		uint16_t 
		_nes_cpu::load_word(
			__in uint16_t address
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (load(address) | (load(address + 1) << BITS_PER_BYTE));
		}

		void 
		_nes_cpu::nmi(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			interrupt(CPU_INTERRUPT_NMI_ADDRESS);
		}

		uint8_t 
		_nes_cpu::pop(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			++m_register_sp;
			return load(m_register_sp + CPU_REGISTER_SP_OFFSET);
		}

		uint16_t 
		_nes_cpu::pop_word(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (pop() | (pop() << BITS_PER_BYTE));
		}

		void 
		_nes_cpu::push(
			__in uint8_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			store(m_register_sp + CPU_REGISTER_SP_OFFSET, value);
			--m_register_sp;
		}

		void 
		_nes_cpu::push_word(
			__in uint16_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			push((value >> BITS_PER_BYTE) & UINT8_MAX);
			push(value & UINT8_MAX);
		}

		void 
		_nes_cpu::reset(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			clear();
			m_register_pc = load_word(CPU_INTERRUPT_RESET_ADDRESS);
		}

		void 
		_nes_cpu::step(void)
		{
			uint8_t code;

			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			code = load(m_register_pc);
			++m_register_pc;

			// TODO: on brk instruction, call interrupt with breakpoint flag set to true
			// TODO: on rti instruction, call interrupt_return
		}

		void 
		_nes_cpu::store(
			__in uint16_t address,
			__in uint8_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_memory->at(address) = value;
		}

		void 
		_nes_cpu::store_word(
			__in uint16_t address,
			__in uint16_t value
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			store(address, value & UINT8_MAX);
			store(address + 1, (value >> BITS_PER_BYTE) & UINT8_MAX);
		}

		std::string 
		_nes_cpu::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			uint8_t p = m_register_p, iter = BITS_PER_BYTE;

			ATOMIC_CALL_RECUR(m_lock);

			result << "<" << NES_CPU_HEADER << "> (" 
				<< (m_initialized ? INITIALIZED : UNINITIALIZED); 

			if(verbose) {
				result << ", ptr. 0x" << VALUE_AS_HEX(nes_cpu_ptr, this);
			}

			result << ")";

			if(m_initialized) {
				result << std::endl 
					<< "A: 0x" << VALUE_AS_HEX(uint8_t, m_register_a)
					<< ", X: 0x" << VALUE_AS_HEX(uint8_t, m_register_x)
					<< ", Y: 0x" << VALUE_AS_HEX(uint8_t, m_register_y)
					<< ", P: [0b";

				while(iter--) {
					result << (CPU_FLAG_CHECK(p, 0x80) ? "1" : "0");
					p <<= 1;
				}

				result << "] (0x" << VALUE_AS_HEX(uint8_t, m_register_p) << ")"
					<< std::endl
					<< "SP: 0x" << VALUE_AS_HEX(uint16_t, m_register_sp + CPU_REGISTER_SP_OFFSET)
					<< ", PC: 0x" << VALUE_AS_HEX(uint16_t, m_register_pc)
					<< ", CYC: " << m_cycles;
			}

			return result.str();
		}

		void 
		_nes_cpu::uninitialize(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			clear();
			m_initialized = false;
		}
	}
}
