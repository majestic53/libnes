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
#include "../include/nes_cpu_code.h"
#include "../include/nes_cpu_type.h"

namespace NES {

	namespace COMP {

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
		_nes_cpu::execute_adc(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_and(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_asl(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_branch(
			__in uint8_t code
			)
		{
			int8_t offset;
			bool branch = false;

			ATOMIC_CALL_RECUR(m_lock);

			offset = load(m_register_pc++);

			switch(code) {
				case CPU_CODE_BCC_RELATIVE:
					branch = !CPU_FLAG_CHECK(m_register_p, CPU_FLAG_CARRY);
					break;
				case CPU_CODE_BCS_RELATIVE:
					branch = CPU_FLAG_CHECK(m_register_p, CPU_FLAG_CARRY);
					break;
				case CPU_CODE_BEQ_RELATIVE:
					branch = CPU_FLAG_CHECK(m_register_p, CPU_FLAG_ZERO);
					break;
				case CPU_CODE_BMI_RELATIVE:
					branch = CPU_FLAG_CHECK(m_register_p, CPU_FLAG_NEGATIVE);
					break;
				case CPU_CODE_BNE_RELATIVE:
					branch = !CPU_FLAG_CHECK(m_register_p, CPU_FLAG_ZERO);
					break;
				case CPU_CODE_BPL_RELATIVE:
					branch = !CPU_FLAG_CHECK(m_register_p, CPU_FLAG_NEGATIVE);
					break;
				case CPU_CODE_BVC_RELATIVE:
					branch = !CPU_FLAG_CHECK(m_register_p, CPU_FLAG_OVERFLOW);
					break;
				case CPU_CODE_BVS_RELATIVE:
					branch = CPU_FLAG_CHECK(m_register_p, CPU_FLAG_OVERFLOW);
					break;
				default:
					THROW_NES_CPU_EXCEPTION_MESSAGE(NES_CPU_EXCEPTION_EXPECTING_BRANCH_CODE,
						"0x%x", code);
			}

			if(branch) {

				if(((m_register_pc & UINT8_MAX) + offset) > UINT8_MAX) {
					++m_cycles;
				}

				m_register_pc += offset;
				++m_cycles;
			}

			m_cycles += CPU_CODE_BRANCH_CYCLES;
		}

		void 
		_nes_cpu::execute_bit(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_brk(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO: call interrupt with breakpoint flag set to true

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_flag(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_cmp(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_cpx(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_cpy(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_dec(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_eor(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_inc(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_jmp(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_jsr(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_lda(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_ldx(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_ldy(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_lsr(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_nop(
			__in uint8_t code
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_cycles += CPU_CODE_NOP_CYCLES;
		}

		void 
		_nes_cpu::execute_ora(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_register(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_rol(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_ror(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_rti(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO: call interrupt_return

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_rts(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_sbc(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_sta(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_stack(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_stx(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
		}

		void 
		_nes_cpu::execute_sty(
			__in uint8_t code
			)
		{
			size_t cycles = 0;

			ATOMIC_CALL_RECUR(m_lock);

			// TODO

			m_cycles += cycles;
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
			uint8_t p;

			ATOMIC_CALL_RECUR(m_lock);
			CPU_FLAG_SET(m_register_p, CPU_FLAG_INTERRUPT_ENABLED);
			p = m_register_p;

			if(breakpoint) {
				CPU_FLAG_SET(p, CPU_FLAG_BREAKPOINT);
			} else {
				CPU_FLAG_CLEAR(p, CPU_FLAG_BREAKPOINT);
			}

			push_word(m_register_pc);
			push(p);
			m_register_pc = load_word(address);
			m_cycles += CPU_INTERRUPT_CYCLES;
		}

		void 
		_nes_cpu::interrupt_return(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_register_p = pop();
			m_register_pc = pop_word();
		}

		void 
		_nes_cpu::irq(void)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_NES_CPU_EXCEPTION(NES_CPU_EXCEPTION_UNINITIALIZED);
			}

			if(!CPU_FLAG_CHECK(m_register_p, CPU_FLAG_INTERRUPT_ENABLED)) {
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

			switch(code) {
				case CPU_CODE_ADC_ABSOLUTE:
				case CPU_CODE_ADC_ABSOLUTE_X:
				case CPU_CODE_ADC_ABSOLUTE_Y:
				case CPU_CODE_ADC_IMMEDIATE:
				case CPU_CODE_ADC_INDIRECT_X:
				case CPU_CODE_ADC_INDIRECT_Y:
				case CPU_CODE_ADC_ZERO_PAGE:
				case CPU_CODE_ADC_ZERO_PAGE_X:
					execute_adc(code);
					break;
				case CPU_CODE_AND_ABSOLUTE:
				case CPU_CODE_AND_ABSOLUTE_X:
				case CPU_CODE_AND_ABSOLUTE_Y:
				case CPU_CODE_AND_IMMEDIATE:
				case CPU_CODE_AND_INDIRECT_X:
				case CPU_CODE_AND_INDIRECT_Y:
				case CPU_CODE_AND_ZERO_PAGE:
				case CPU_CODE_AND_ZERO_PAGE_X:
					execute_and(code);
					break;
				case CPU_CODE_ASL_ABSOLUTE:
				case CPU_CODE_ASL_ABSOLUTE_X:
				case CPU_CODE_ASL_ACCUMULATOR:
				case CPU_CODE_ASL_ZERO_PAGE:
				case CPU_CODE_ASL_ZERO_PAGE_X:
					execute_asl(code);
					break;
				case CPU_CODE_BCC_RELATIVE:
				case CPU_CODE_BCS_RELATIVE:
				case CPU_CODE_BEQ_RELATIVE:
				case CPU_CODE_BMI_RELATIVE:
				case CPU_CODE_BNE_RELATIVE:
				case CPU_CODE_BPL_RELATIVE:
				case CPU_CODE_BVC_RELATIVE:
				case CPU_CODE_BVS_RELATIVE:
					execute_branch(code);
					break;
				case CPU_CODE_BIT_ABSOLUTE:
				case CPU_CODE_BIT_ZERO_PAGE:
					execute_bit(code);
					break;
				case CPU_CODE_BRK_IMPLIED:
					execute_brk(code);
					break;
				case CPU_CODE_CLC_IMPLIED:
				case CPU_CODE_CLD_IMPLIED:
				case CPU_CODE_CLI_IMPLIED:
				case CPU_CODE_CLV_IMPLIED:
				case CPU_CODE_SEC_IMPLIED:
				case CPU_CODE_SED_IMPLIED:
				case CPU_CODE_SEI_IMPLIED:
					execute_flag(code);
					break;
				case CPU_CODE_CMP_ABSOLUTE:
				case CPU_CODE_CMP_ABSOLUTE_X:
				case CPU_CODE_CMP_ABSOLUTE_Y:
				case CPU_CODE_CMP_IMMEDIATE:
				case CPU_CODE_CMP_INDIRECT_X:
				case CPU_CODE_CMP_INDIRECT_Y:
				case CPU_CODE_CMP_ZERO_PAGE:
				case CPU_CODE_CMP_ZERO_PAGE_X:
					execute_cmp(code);
					break;
				case CPU_CODE_CPX_ABSOLUTE:
				case CPU_CODE_CPX_IMMEDIATE:
				case CPU_CODE_CPX_ZERO_PAGE:
					execute_cpx(code);
					break;
				case CPU_CODE_CPY_ABSOLUTE:
				case CPU_CODE_CPY_IMMEDIATE:
				case CPU_CODE_CPY_ZERO_PAGE:
					execute_cpy(code);
					break;
				case CPU_CODE_DEC_ABSOLUTE:
				case CPU_CODE_DEC_ABSOLUTE_X:
				case CPU_CODE_DEC_ZERO_PAGE:
				case CPU_CODE_DEC_ZERO_PAGE_X:
					execute_dec(code);
					break;
				case CPU_CODE_DEX_IMPLIED:
				case CPU_CODE_DEY_IMPLIED:
				case CPU_CODE_INX_IMPLIED:
				case CPU_CODE_INY_IMPLIED:
				case CPU_CODE_TAX_IMPLIED:
				case CPU_CODE_TAY_IMPLIED:
				case CPU_CODE_TXA_IMPLIED:
				case CPU_CODE_TYA_IMPLIED:
					execute_register(code);
					break;
				case CPU_CODE_EOR_ABSOLUTE:
				case CPU_CODE_EOR_ABSOLUTE_X:
				case CPU_CODE_EOR_ABSOLUTE_Y:
				case CPU_CODE_EOR_IMMEDIATE:
				case CPU_CODE_EOR_INDIRECT_X:
				case CPU_CODE_EOR_INDIRECT_Y:
				case CPU_CODE_EOR_ZERO_PAGE:
				case CPU_CODE_EOR_ZERO_PAGE_X:
					execute_eor(code);
					break;
				case CPU_CODE_INC_ABSOLUTE:
				case CPU_CODE_INC_ABSOLUTE_X:
				case CPU_CODE_INC_ZERO_PAGE:
				case CPU_CODE_INC_ZERO_PAGE_X:
					execute_inc(code);
					break;
				case CPU_CODE_JMP_ABSOLUTE:
				case CPU_CODE_JMP_INDIRECT:
					execute_jmp(code);
					break;
				case CPU_CODE_JSR_ABSOLUTE:
					execute_jsr(code);
					break;
				case CPU_CODE_LDA_ABSOLUTE:
				case CPU_CODE_LDA_ABSOLUTE_X:
				case CPU_CODE_LDA_ABSOLUTE_Y:
				case CPU_CODE_LDA_IMMEDIATE:
				case CPU_CODE_LDA_INDIRECT_X:
				case CPU_CODE_LDA_INDIRECT_Y:
				case CPU_CODE_LDA_ZERO_PAGE:
				case CPU_CODE_LDA_ZERO_PAGE_X:
					execute_lda(code);
					break;
				case CPU_CODE_LDX_ABSOLUTE:
				case CPU_CODE_LDX_ABSOLUTE_Y:
				case CPU_CODE_LDX_IMMEDIATE:
				case CPU_CODE_LDX_ZERO_PAGE:
				case CPU_CODE_LDX_ZERO_PAGE_Y:
					execute_ldx(code);
					break;
				case CPU_CODE_LDY_ABSOLUTE:
				case CPU_CODE_LDY_ABSOLUTE_X:
				case CPU_CODE_LDY_IMMEDIATE:
				case CPU_CODE_LDY_ZERO_PAGE:
				case CPU_CODE_LDY_ZERO_PAGE_X:
					execute_ldy(code);
					break;
				case CPU_CODE_LSR_ABSOLUTE:
				case CPU_CODE_LSR_ABSOLUTE_X:
				case CPU_CODE_LSR_ACCUMULATOR:
				case CPU_CODE_LSR_ZERO_PAGE:
				case CPU_CODE_LSR_ZERO_PAGE_X:
					execute_lsr(code);
					break;
				case CPU_CODE_NOP_IMPLIED:
					++m_cycles;
					break;
				case CPU_CODE_ORA_ABSOLUTE:
				case CPU_CODE_ORA_ABSOLUTE_X:
				case CPU_CODE_ORA_ABSOLUTE_Y:
				case CPU_CODE_ORA_IMMEDIATE:
				case CPU_CODE_ORA_INDIRECT_X:
				case CPU_CODE_ORA_INDIRECT_Y:
				case CPU_CODE_ORA_ZERO_PAGE:
				case CPU_CODE_ORA_ZERO_PAGE_X:
					execute_ora(code);
					break;
				case CPU_CODE_PHA_IMPLIED:
				case CPU_CODE_PHP_IMPLIED:
				case CPU_CODE_PLA_IMPLIED:
				case CPU_CODE_PLP_IMPLIED:
				case CPU_CODE_TSX_IMPLIED:
				case CPU_CODE_TXS_IMPLIED:
					execute_stack(code);
					break;
				case CPU_CODE_ROL_ABSOLUTE:
				case CPU_CODE_ROL_ABSOLUTE_X:
				case CPU_CODE_ROL_ACCUMULATOR:
				case CPU_CODE_ROL_ZERO_PAGE:
				case CPU_CODE_ROL_ZERO_PAGE_X:
					execute_rol(code);
					break;
				case CPU_CODE_ROR_ABSOLUTE:
				case CPU_CODE_ROR_ABSOLUTE_X:
				case CPU_CODE_ROR_ACCUMULATOR:
				case CPU_CODE_ROR_ZERO_PAGE:
				case CPU_CODE_ROR_ZERO_PAGE_X:
					execute_ror(code);
					break;
				case CPU_CODE_RTI_IMPLIED:
					execute_rti(code);
					break;
				case CPU_CODE_RTS_IMPLIED:
					execute_rts(code);
					break;
				case CPU_CODE_SBC_ABSOLUTE:
				case CPU_CODE_SBC_ABSOLUTE_X:
				case CPU_CODE_SBC_ABSOLUTE_Y:
				case CPU_CODE_SBC_IMMEDIATE:
				case CPU_CODE_SBC_INDIRECT_X:
				case CPU_CODE_SBC_INDIRECT_Y:
				case CPU_CODE_SBC_ZERO_PAGE:
				case CPU_CODE_SBC_ZERO_PAGE_X:
					execute_sbc(code);
					break;
				case CPU_CODE_STA_ABSOLUTE:
				case CPU_CODE_STA_ABSOLUTE_X:
				case CPU_CODE_STA_ABSOLUTE_Y:
				case CPU_CODE_STA_INDIRECT_X:
				case CPU_CODE_STA_INDIRECT_Y:
				case CPU_CODE_STA_ZERO_PAGE:
				case CPU_CODE_STA_ZERO_PAGE_X:
					execute_sta(code);
					break;
				case CPU_CODE_STX_ABSOLUTE:
				case CPU_CODE_STX_ZERO_PAGE:
				case CPU_CODE_STX_ZERO_PAGE_Y:
					execute_stx(code);
					break;
				case CPU_CODE_STY_ABSOLUTE:
				case CPU_CODE_STY_ZERO_PAGE:
				case CPU_CODE_STY_ZERO_PAGE_X:
					execute_sty(code);
					break;
				default:
					THROW_NES_CPU_EXCEPTION_MESSAGE(NES_CPU_EXCEPTION_UNSUPPORTED_CODE,
						"0x%x", code);
			}
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
