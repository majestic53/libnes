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
#include "../include/nes_cpu_code.h"
#include "../include/nes_cpu_type.h"

#ifndef NDEBUG

namespace NES {

	namespace TEST {

		#define TEST_CPU_ADDRESS 0x3344
		#define TEST_CPU_ADDRESS_INDIRECT 0x4455
		#define TEST_CPU_ADDRESS_RELATIVE_ADD 0x10
		#define TEST_CPU_ADDRESS_RELATIVE_SUB 0xa5
		#define TEST_CPU_ADDRESS_ZERO_PAGE 0x10
		#define TEST_CPU_CODE_INVALID 0x3a
		#define TEST_CPU_INTERRUPT_VECTOR 0xabcd
		#define TEST_CPU_REGISTER_INIT 0x3d
		#define TEST_CPU_REGISTER_INIT_HIGH 0x7f
		#define TEST_CPU_REGISTER_INIT_MAX 0xff
		#define TEST_CPU_REGISTER_INDEX_OFFSET 3
		#define TEST_CPU_REGISTER_INIT_ONE 1
		#define TEST_CPU_REGISTER_INIT_ZERO 0
		#define TEST_CPU_SP_INTERRUPT_OFFSET 3
		#define TEST_CPU_SP_SUBROUTINE_OFFSET 2

		enum {
			NES_TEST_CPU_ACQUIRE = 0,
			NES_TEST_CPU_CLEAR,
			NES_TEST_CPU_CYCLES,
			NES_TEST_CPU_EXECUTE_ADC,
			NES_TEST_CPU_EXECUTE_AND,
			NES_TEST_CPU_EXECUTE_ASL,
			NES_TEST_CPU_EXECUTE_BCC,
			NES_TEST_CPU_EXECUTE_BCS,
			NES_TEST_CPU_EXECUTE_BEQ,
			NES_TEST_CPU_EXECUTE_BIT,
			NES_TEST_CPU_EXECUTE_BMI,
			NES_TEST_CPU_EXECUTE_BNE,
			NES_TEST_CPU_EXECUTE_BPL,
			NES_TEST_CPU_EXECUTE_BRK,
			NES_TEST_CPU_EXECUTE_BVC,
			NES_TEST_CPU_EXECUTE_BVS,
			NES_TEST_CPU_EXECUTE_CLC,
			NES_TEST_CPU_EXECUTE_CLD,
			NES_TEST_CPU_EXECUTE_CLI,
			NES_TEST_CPU_EXECUTE_CLV,
			NES_TEST_CPU_EXECUTE_CMP,
			NES_TEST_CPU_EXECUTE_CPX,
			NES_TEST_CPU_EXECUTE_CPY,
			NES_TEST_CPU_EXECUTE_DEC,
			NES_TEST_CPU_EXECUTE_DEX,
			NES_TEST_CPU_EXECUTE_DEY,
			NES_TEST_CPU_EXECUTE_EOR,
			NES_TEST_CPU_EXECUTE_INC,
			NES_TEST_CPU_EXECUTE_INX,
			NES_TEST_CPU_EXECUTE_INY,
			NES_TEST_CPU_EXECUTE_JMP,
			NES_TEST_CPU_EXECUTE_JSR,
			NES_TEST_CPU_EXECUTE_LDA,
			NES_TEST_CPU_EXECUTE_LDX,
			NES_TEST_CPU_EXECUTE_LDY,
			NES_TEST_CPU_EXECUTE_LSR,
			NES_TEST_CPU_EXECUTE_NOP,
			NES_TEST_CPU_EXECUTE_ORA,
			NES_TEST_CPU_EXECUTE_PHA,
			NES_TEST_CPU_EXECUTE_PHP,
			NES_TEST_CPU_EXECUTE_PLA,
			NES_TEST_CPU_EXECUTE_PLP,
			NES_TEST_CPU_EXECUTE_ROL,
			NES_TEST_CPU_EXECUTE_ROR,
			NES_TEST_CPU_EXECUTE_RTI,
			NES_TEST_CPU_EXECUTE_RTS,
			NES_TEST_CPU_EXECUTE_SBC,
			NES_TEST_CPU_EXECUTE_SEC,
			NES_TEST_CPU_EXECUTE_SED,
			NES_TEST_CPU_EXECUTE_SEI,
			NES_TEST_CPU_EXECUTE_STA,
			NES_TEST_CPU_EXECUTE_STX,
			NES_TEST_CPU_EXECUTE_STY,
			NES_TEST_CPU_EXECUTE_TAX,
			NES_TEST_CPU_EXECUTE_TAY,
			NES_TEST_CPU_EXECUTE_TSX,
			NES_TEST_CPU_EXECUTE_TXA,
			NES_TEST_CPU_EXECUTE_TXS,
			NES_TEST_CPU_EXECUTE_TYA,
			NES_TEST_CPU_INITIALIZE,
			NES_TEST_CPU_IRQ,
			NES_TEST_CPU_IS_ALLOCATED,
			NES_TEST_CPU_IS_INITIALIZED,
			NES_TEST_CPU_NMI,
			NES_TEST_CPU_RESET,
			NES_TEST_CPU_STEP,
			NES_TEST_CPU_UNINITIALIZE,
		};

		#define NES_TEST_CPU_MAX NES_TEST_CPU_UNINITIALIZE

		static const std::string NES_TEST_CPU_STR[] = {
			NES_CPU_HEADER "::ACQUIRE",
			NES_CPU_HEADER "::CLEAR",
			NES_CPU_HEADER "::CYCLES",
			NES_CPU_HEADER "::ADC",
			NES_CPU_HEADER "::AND",
			NES_CPU_HEADER "::ASL",
			NES_CPU_HEADER "::BCC",
			NES_CPU_HEADER "::BCS",
			NES_CPU_HEADER "::BEQ",
			NES_CPU_HEADER "::BIT",
			NES_CPU_HEADER "::BMI",
			NES_CPU_HEADER "::BNE",
			NES_CPU_HEADER "::BPL",
			NES_CPU_HEADER "::BRK",
			NES_CPU_HEADER "::BVC",
			NES_CPU_HEADER "::BVS",
			NES_CPU_HEADER "::CLC",
			NES_CPU_HEADER "::CLD",
			NES_CPU_HEADER "::CLI",
			NES_CPU_HEADER "::CLV",
			NES_CPU_HEADER "::CMP",
			NES_CPU_HEADER "::CPX",
			NES_CPU_HEADER "::CPY",
			NES_CPU_HEADER "::DEC",
			NES_CPU_HEADER "::DEX",
			NES_CPU_HEADER "::DEY",
			NES_CPU_HEADER "::EOR",
			NES_CPU_HEADER "::INC",
			NES_CPU_HEADER "::INX",
			NES_CPU_HEADER "::INY",
			NES_CPU_HEADER "::JMP",
			NES_CPU_HEADER "::JSR",
			NES_CPU_HEADER "::LDA",
			NES_CPU_HEADER "::LDX",
			NES_CPU_HEADER "::LDY",
			NES_CPU_HEADER "::LSR",
			NES_CPU_HEADER "::NOP",
			NES_CPU_HEADER "::ORA",
			NES_CPU_HEADER "::PHA",
			NES_CPU_HEADER "::PHP",
			NES_CPU_HEADER "::PLA",
			NES_CPU_HEADER "::PLP",
			NES_CPU_HEADER "::ROL",
			NES_CPU_HEADER "::ROR",
			NES_CPU_HEADER "::RTI",
			NES_CPU_HEADER "::RTS",
			NES_CPU_HEADER "::SBC",
			NES_CPU_HEADER "::SEC",
			NES_CPU_HEADER "::SED",
			NES_CPU_HEADER "::SEI",
			NES_CPU_HEADER "::STA",
			NES_CPU_HEADER "::STX",
			NES_CPU_HEADER "::STY",
			NES_CPU_HEADER "::TAX",
			NES_CPU_HEADER "::TAY",
			NES_CPU_HEADER "::TSX",
			NES_CPU_HEADER "::TXA",
			NES_CPU_HEADER "::TXS",
			NES_CPU_HEADER "::TYA",
			NES_CPU_HEADER "::INITIALIZE",
			NES_CPU_HEADER "::IRQ",
			NES_CPU_HEADER "::IS_ALLOCATED",
			NES_CPU_HEADER "::IS_INITIALIZED",
			NES_CPU_HEADER "::NMI",
			NES_CPU_HEADER "::RESET",
			NES_CPU_HEADER "::STEP",
			NES_CPU_HEADER "::UNINITIALIZE",
			};

		#define NES_TEST_CPU_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_CPU_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_CPU_STR[_TYPE_]))

		static const nes_test_cb NES_TEST_CPU_CB[] = {
			nes_test_cpu::acquire,
			nes_test_cpu::clear,
			nes_test_cpu::cycles,
			nes_test_cpu::execute_adc,
			nes_test_cpu::execute_and,
			nes_test_cpu::execute_asl,
			nes_test_cpu::execute_bcc,
			nes_test_cpu::execute_bcs,
			nes_test_cpu::execute_beq,
			nes_test_cpu::execute_bit,
			nes_test_cpu::execute_bmi,
			nes_test_cpu::execute_bne,
			nes_test_cpu::execute_bpl,
			nes_test_cpu::execute_brk,
			nes_test_cpu::execute_bvc,
			nes_test_cpu::execute_bvs,
			nes_test_cpu::execute_clc,
			nes_test_cpu::execute_cld,
			nes_test_cpu::execute_cli,
			nes_test_cpu::execute_clv,
			nes_test_cpu::execute_cmp,
			nes_test_cpu::execute_cpx,
			nes_test_cpu::execute_cpy,
			nes_test_cpu::execute_dec,
			nes_test_cpu::execute_dex,
			nes_test_cpu::execute_dey,
			nes_test_cpu::execute_eor,
			nes_test_cpu::execute_inc,
			nes_test_cpu::execute_inx,
			nes_test_cpu::execute_iny,
			nes_test_cpu::execute_jmp,
			nes_test_cpu::execute_jsr,
			nes_test_cpu::execute_lda,
			nes_test_cpu::execute_ldx,
			nes_test_cpu::execute_ldy,
			nes_test_cpu::execute_lsr,
			nes_test_cpu::execute_nop,
			nes_test_cpu::execute_ora,
			nes_test_cpu::execute_pha,
			nes_test_cpu::execute_php,
			nes_test_cpu::execute_pla,
			nes_test_cpu::execute_plp,
			nes_test_cpu::execute_rol,
			nes_test_cpu::execute_ror,
			nes_test_cpu::execute_rti,
			nes_test_cpu::execute_rts,
			nes_test_cpu::execute_sbc,
			nes_test_cpu::execute_sec,
			nes_test_cpu::execute_sed,
			nes_test_cpu::execute_sei,
			nes_test_cpu::execute_sta,
			nes_test_cpu::execute_stx,
			nes_test_cpu::execute_sty,
			nes_test_cpu::execute_tax,
			nes_test_cpu::execute_tay,
			nes_test_cpu::execute_tsx,
			nes_test_cpu::execute_txa,
			nes_test_cpu::execute_txs,
			nes_test_cpu::execute_tya,
			nes_test_cpu::initialize,
			nes_test_cpu::irq,
			nes_test_cpu::is_allocated,
			nes_test_cpu::is_initialized,
			nes_test_cpu::nmi,
			nes_test_cpu::reset,
			nes_test_cpu::step,
			nes_test_cpu::uninitialize,
			};

		#define NES_TEST_CPU_CALLBACK(_TYPE_) \
			((_TYPE_) > NES_TEST_CPU_MAX ? NULL : \
			NES_TEST_CPU_CB[_TYPE_])

		nes_test_t 
		_nes_test_cpu::acquire(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(!nes_cpu::acquire()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(!nes_cpu::is_allocated()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::cache_state(
			__in void *context,
			__inout nes_cpu_state &state
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			state.a = inst->m_register_a;
			state.cycles = inst->m_cycles;
			state.p = inst->m_register_p;
			state.pc = inst->m_register_pc;
			state.sp = inst->m_register_sp;
			state.x = inst->m_register_x;
			state.y = inst->m_register_y;
			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::clear(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->clear();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				result = nes_test_cpu::random_state(context);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->clear();

				if((inst->m_cycles != CPU_CYCLES_INIT)
						|| (inst->m_register_a != CPU_REGISTER_A_INIT)
						|| (inst->m_register_p != CPU_REGISTER_P_INIT)
						|| (inst->m_register_pc != CPU_REGISTER_PC_INIT)
						|| (inst->m_register_sp != CPU_REGISTER_SP_INIT)
						|| (inst->m_register_x != CPU_REGISTER_X_INIT)
						|| (inst->m_register_y != CPU_REGISTER_Y_INIT)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}	
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		bool 
		_nes_test_cpu::compare_state(
			__in void *context,
			__in const nes_cpu_state &state
			)
		{
			bool result = false;
			nes_cpu_ptr inst = NULL;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			if((state.a != inst->m_register_a)
					|| (state.cycles != inst->m_cycles)
					|| (state.p != inst->m_register_p)
					|| (state.pc != inst->m_register_pc)
					|| (state.sp != inst->m_register_sp)
					|| (state.x != inst->m_register_x)
					|| (state.y != inst->m_register_y)) {

				std::cout << "A: " << VALUE_AS_HEX(uint8_t, state.a) << ", " << VALUE_AS_HEX(uint8_t, inst->m_register_a) << std::endl
					<< "CYCLES: " << VALUE_AS_HEX(uint32_t, state.cycles) << ", " << VALUE_AS_HEX(uint32_t, inst->m_cycles) << std::endl
					<< "P: " << nes_memory::flag_as_string(state.p, true) << ", " 
						<< nes_memory::flag_as_string(inst->m_register_p, true) << std::endl
					<< "PC: " << VALUE_AS_HEX(uint16_t, state.pc) << ", " << VALUE_AS_HEX(uint16_t, inst->m_register_pc) << std::endl
					<< "SP: " << VALUE_AS_HEX(uint8_t, state.sp) << ", " << VALUE_AS_HEX(uint8_t, inst->m_register_sp) << std::endl
					<< "X: " << VALUE_AS_HEX(uint8_t, state.x) << ", " << VALUE_AS_HEX(uint8_t, inst->m_register_x) << std::endl
					<< "Y: " << VALUE_AS_HEX(uint8_t, state.y) << ", " << VALUE_AS_HEX(uint8_t, inst->m_register_y) << std::endl;

				goto exit;
			}

			result = true;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::cycles(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->cycles();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				if(inst->m_cycles != CPU_CYCLES_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}
 
		nes_test_t 
		_nes_test_cpu::execute_adc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_ADC_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_ADC_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_ADC_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_ADC_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_ADC_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_ADC_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_ADC_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_ADC_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_ADC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_ADC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ADC_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ADC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_ADC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ADC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT + 1);
				st.cycles += CPU_CODE_ADC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_ADC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY | CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_and(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_AND_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_AND_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_AND_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_AND_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_AND_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_AND_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_AND_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_AND_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_AND_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_AND_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a &= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_AND_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_AND_ZERO_PAGE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						& TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_asl(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_ASL_ABSOLUTE
				// TODO

				// CPU_CODE_ASL_ABSOLUTE_X
				// TODO

				// CPU_CODE_ASL_ACCUMULATOR
				// TODO

				// CPU_CODE_ASL_ZERO_PAGE
				// TODO

				// CPU_CODE_ASL_ZERO_PAGE_X
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bcc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bcs(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BCS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_beq(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BEQ_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BEQ_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BEQ_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BEQ_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bit(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_BIT_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BIT_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT_ONE);
				inst->step();
				st.cycles += CPU_CODE_BIT_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_BIT_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BIT_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT_HIGH);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_OVERFLOW);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.cycles += CPU_CODE_BIT_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_BIT_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_BIT_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BIT_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.cycles += CPU_CODE_BIT_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_BIT_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BIT_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT_ZERO);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				st.cycles += CPU_CODE_BIT_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_BIT_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bmi(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BMI_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BMI_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BMI_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BMI_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bne(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BNE_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BNE_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BNE_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_ZERO);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BNE_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bpl(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BPL_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BPL_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BPL_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BPL_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_brk(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(CPU_INTERRUPT_IRQ_ADDRESS, TEST_CPU_INTERRUPT_VECTOR);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BRK_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_BRK_IMPLIED_CYCLES;
				st.pc = inst->load_word(CPU_INTERRUPT_IRQ_ADDRESS);
				st.sp -= TEST_CPU_SP_INTERRUPT_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 1)
						!= (inst->m_register_p | CPU_FLAG_BREAKPOINT)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load_word(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 2)
						!= (TEST_CPU_INTERRUPT_VECTOR + CPU_CODE_BRK_IMPLIED_LENGTH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bvc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVC_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_bvs(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += CPU_CODE_BRANCH_RELATIVE_CYCLES;
				st.pc += CPU_CODE_BRANCH_RELATIVE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_SUB);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - TEST_CPU_ADDRESS_RELATIVE_SUB)));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_RELATIVE_ADD);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 1);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH + TEST_CPU_ADDRESS_RELATIVE_ADD);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BVS_RELATIVE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, INT8_MAX + 1);
				inst->step();
				st.cycles += (CPU_CODE_BRANCH_RELATIVE_CYCLES + 2);
				st.pc += (CPU_CODE_BRANCH_RELATIVE_LENGTH 
						- (((UINT8_MAX + 1) - (INT8_MAX + 1))));

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_clc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLC_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLC_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_cld(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_DECIMAL);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLD_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_DECIMAL);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLD_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_DECIMAL);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_cli(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLI_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLI_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_INTERRUPT_DISABLED);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_clv(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLV_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_OVERFLOW);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_CLV_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_OVERFLOW);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_cmp(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_CMP_ABSOLUTE
				// TODO

				// CPU_CODE_CMP_ABSOLUTE_X
				// TODO

				// CPU_CODE_CMP_ABSOLUTE_Y
				// TODO

				// CPU_CODE_CMP_IMMEDIATE
				// TODO

				// CPU_CODE_CMP_INDIRECT_X
				// TODO

				// CPU_CODE_CMP_INDIRECT_Y
				// TODO

				// CPU_CODE_CMP_ZERO_PAGE
				// TODO

				// CPU_CODE_CMP_ZERO_PAGE_X
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_cpx(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_CPX_ABSOLUTE
				// TODO

				// CPU_CODE_CPX_IMMEDIATE
				// TODO

				// CPU_CODE_CPX_ZERO_PAGE
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_cpy(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_CPY_ABSOLUTE
				// TODO

				// CPU_CODE_CPY_IMMEDIATE
				// TODO

				// CPU_CODE_CPY_ZERO_PAGE
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_dec(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_DEC_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_DEC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_DEC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS) != (TEST_CPU_REGISTER_INIT - 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_DEC_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_DEC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_DEC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= (TEST_CPU_REGISTER_INIT - 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_DEC_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_DEC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_DEC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE) != (TEST_CPU_REGISTER_INIT - 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_DEC_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEC_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_DEC_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_DEC_ZERO_PAGE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= (TEST_CPU_REGISTER_INIT - 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_dex(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_x = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEX_IMPLIED);
				inst->step();
				--st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_x = TEST_CPU_REGISTER_INIT_ONE;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				--st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_x = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				--st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_dey(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_y = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEY_IMPLIED);
				inst->step();
				--st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_y = TEST_CPU_REGISTER_INIT_ONE;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEY_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				--st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->m_register_y = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_DEY_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				--st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_eor(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_EOR_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_EOR_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_EOR_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_EOR_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_EOR_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_EOR_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_EOR_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_EOR_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_EOR_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_EOR_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a ^= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_EOR_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_EOR_ZERO_PAGE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						^ TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_inc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_INC_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_INC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_INC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS) != (TEST_CPU_REGISTER_INIT + 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_INC_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_INC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_INC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= (TEST_CPU_REGISTER_INIT + 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_INC_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_INC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_INC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE) != (TEST_CPU_REGISTER_INIT + 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_INC_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INC_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_INC_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_INC_ZERO_PAGE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= (TEST_CPU_REGISTER_INIT + 1)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_inx(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INX_IMPLIED);
				inst->step();
				++st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INX_IMPLIED);
				inst->step();
				++st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INX_IMPLIED);
				inst->step();
				++st.x;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_iny(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INY_IMPLIED);
				inst->step();
				++st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INY_IMPLIED);
				inst->step();
				++st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_INY_IMPLIED);
				inst->step();
				++st.y;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_jmp(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_JMP_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_JMP_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_JMP_ABSOLUTE_CYCLES;
				st.pc = TEST_CPU_ADDRESS;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_JMP_INDIRECT
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_JMP_INDIRECT);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_INDIRECT);
				inst->store_word(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_JMP_INDIRECT_CYCLES;
				st.pc = TEST_CPU_ADDRESS;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_jsr(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_JSR_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_JSR_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_JSR_ABSOLUTE_CYCLES;
				st.pc = TEST_CPU_ADDRESS;
				st.sp -= TEST_CPU_SP_SUBROUTINE_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_lda(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st  = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_LDA_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_LDA_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x += TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_LDA_ABSOLUTE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y += TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_LDA_ABSOLUTE_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_IMMEDIATE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_LDA_IMMEDIATE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_LDA_INDIRECT_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_LDA_INDIRECT_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_LDA_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDA_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDA_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDA_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_LDA_ZERO_PAGE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_ldx(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st  = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_LDX_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDX_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDX_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_LDX_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDX_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y += TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDX_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDX_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_LDX_ABSOLUTE_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDX_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDX_IMMEDIATE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDX_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_LDX_IMMEDIATE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDX_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDX_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDX_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_LDX_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDX_ZERO_PAGE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDX_ZERO_PAGE_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDX_ZERO_PAGE_Y_CYCLES;
				st.pc += CPU_CODE_LDX_ZERO_PAGE_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_ldy(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st  = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_LDY_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDY_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDY_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_LDY_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDY_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x += TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDY_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDY_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_LDY_ABSOLUTE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDY_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDY_IMMEDIATE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDY_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_LDY_IMMEDIATE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDY_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDY_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDY_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_LDY_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_LDY_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_LDY_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_LDY_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_LDY_ZERO_PAGE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_lsr(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_LSR_ABSOLUTE
				// TODO

				// CPU_CODE_LSR_ABSOLUTE_X
				// TODO

				// CPU_CODE_LSR_ACCUMULATOR
				// TODO

				// CPU_CODE_LSR_ZERO_PAGE
				// TODO

				// CPU_CODE_LSR_ZERO_PAGE_X
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_nop(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_NOP_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_NOP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_NOP_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_ora(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_ORA_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_ORA_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_ORA_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_ORA_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_ORA_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_ORA_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_ORA_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_ORA_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_ORA_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_ORA_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a |= TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_ORA_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_ORA_ZERO_PAGE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->m_register_a != (TEST_CPU_REGISTER_INIT 
						| TEST_CPU_REGISTER_INIT_HIGH)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_pha(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PHA_IMPLIED);
				inst->step();
				--st.sp;
				st.cycles += CPU_CODE_PHA_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 1) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_php(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_p = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PHP_IMPLIED);
				inst->step();
				--st.sp;
				st.cycles += CPU_CODE_PHP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 1) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_pla(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = 0;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLA_IMPLIED);
				inst->step();
				++st.sp;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_PLA_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT_ZERO);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLA_IMPLIED);
				inst->step();
				++st.sp;
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.a = TEST_CPU_REGISTER_INIT_ZERO;
				st.cycles += CPU_CODE_PLA_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT_MAX);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLA_IMPLIED);
				inst->step();
				++st.sp;
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = TEST_CPU_REGISTER_INIT_MAX;
				st.cycles += CPU_CODE_PLA_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_plp(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_p = 0;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLP_IMPLIED);
				inst->step();
				++st.sp;
				st.p = TEST_CPU_REGISTER_INIT;
				st.cycles += CPU_CODE_PLP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_p = TEST_CPU_REGISTER_INIT;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT_ZERO);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLP_IMPLIED);
				inst->step();
				++st.sp;
				st.p = TEST_CPU_REGISTER_INIT_ZERO;
				st.cycles += CPU_CODE_PLP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_p = TEST_CPU_REGISTER_INIT;
				inst->store(inst->m_register_sp + CPU_REGISTER_SP_OFFSET,
					TEST_CPU_REGISTER_INIT_MAX);
				--inst->m_register_sp;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_PLP_IMPLIED);
				inst->step();
				++st.sp;
				st.p = TEST_CPU_REGISTER_INIT_MAX;
				st.cycles += CPU_CODE_PLP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_rol(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_ROL_ABSOLUTE
				// TODO

				// CPU_CODE_ROL_ABSOLUTE_X
				// TODO

				// CPU_CODE_ROL_ACCUMULATOR
				// TODO

				// CPU_CODE_ROL_ZERO_PAGE
				// TODO

				// CPU_CODE_ROL_ZERO_PAGE_X
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_ror(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			//nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_ROR_ABSOLUTE
				// TODO

				// CPU_CODE_ROR_ABSOLUTE_X
				// TODO

				// CPU_CODE_ROR_ACCUMULATOR
				// TODO

				// CPU_CODE_ROR_ZERO_PAGE
				// TODO

				// CPU_CODE_ROR_ZERO_PAGE_X
				// TODO

			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_rti(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->push_word(TEST_CPU_INTERRUPT_VECTOR + 1);
				inst->push(inst->m_register_p);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_SET(st.p, CPU_FLAG_INTERRUPT_DISABLED);
				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_RTI_IMPLIED);
				inst->step();
				st.sp += TEST_CPU_SP_INTERRUPT_OFFSET;
				st.pc = (TEST_CPU_INTERRUPT_VECTOR + 1);
				st.cycles += CPU_CODE_RTI_IMPLIED_CYCLES;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_rts(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->push_word(TEST_CPU_INTERRUPT_VECTOR);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_RTS_IMPLIED);
				inst->step();
				st.sp += TEST_CPU_SP_SUBROUTINE_OFFSET;
				st.pc = (TEST_CPU_INTERRUPT_VECTOR + CPU_CODE_RTS_IMPLIED_LENGTH);
				st.cycles += CPU_CODE_RTS_IMPLIED_CYCLES;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sbc(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_SBC_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS - TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS - TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_SBC_ABSOLUTE_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_IMMEDIATE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_SBC_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_IMMEDIATE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_REGISTER_INIT);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_IMMEDIATE_CYCLES;
				st.pc += CPU_CODE_SBC_IMMEDIATE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_SBC_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_SBC_INDIRECT_X_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_SBC_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_SBC_INDIRECT_Y_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_SBC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_SBC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_SBC_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT - 1);
				st.cycles += CPU_CODE_SBC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_SBC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_HIGH;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SBC_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.a = (TEST_CPU_REGISTER_INIT_HIGH - TEST_CPU_REGISTER_INIT);
				st.cycles += CPU_CODE_SBC_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_SBC_ZERO_PAGE_LENGTH;
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sec(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SEC_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_CARRY);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SEC_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_SET(st.p, CPU_FLAG_CARRY);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sed(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_DECIMAL);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SED_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_DECIMAL);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SED_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_SET(st.p, CPU_FLAG_DECIMAL);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sei(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SEI_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_SEI_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_FLAG_IMPLIED_CYCLES;
				st.pc += CPU_CODE_FLAG_IMPLIED_LENGTH;
				CPU_FLAG_SET(st.p, CPU_FLAG_INTERRUPT_DISABLED);

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sta(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_STA_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_STA_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_STA_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_ABSOLUTE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS, 0);	

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_ABSOLUTE_X);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_STA_ABSOLUTE_X_CYCLES;
				st.pc += CPU_CODE_STA_ABSOLUTE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_ABSOLUTE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS, 0);	

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_REGISTER_INIT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_ABSOLUTE_Y);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_STA_ABSOLUTE_Y_CYCLES;
				st.pc += CPU_CODE_STA_ABSOLUTE_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_INDIRECT_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS_INDIRECT, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET, 
					TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_INDIRECT_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STA_INDIRECT_X_CYCLES;
				st.pc += CPU_CODE_STA_INDIRECT_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_INDIRECT) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_INDIRECT_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(TEST_CPU_ADDRESS_ZERO_PAGE, TEST_CPU_ADDRESS_INDIRECT);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_INDIRECT_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STA_INDIRECT_Y_CYCLES;
				st.pc += CPU_CODE_STA_INDIRECT_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_INDIRECT + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STA_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_STA_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STA_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STA_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STA_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_STA_ZERO_PAGE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(nes_exception &exc) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_stx(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_STX_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STX_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_STX_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_STX_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STX_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STX_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STX_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_STX_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STX_ZERO_PAGE_Y
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT;
				inst->m_register_y = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STX_ZERO_PAGE_Y);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STX_ZERO_PAGE_Y_CYCLES;
				st.pc += CPU_CODE_STX_ZERO_PAGE_Y_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_sty(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			 nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				// CPU_CODE_STY_ABSOLUTE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STY_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_STY_ABSOLUTE_CYCLES;
				st.pc += CPU_CODE_STY_ABSOLUTE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STY_ZERO_PAGE
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STY_ZERO_PAGE);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STY_ZERO_PAGE_CYCLES;
				st.pc += CPU_CODE_STY_ZERO_PAGE_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE) != TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// CPU_CODE_STY_ZERO_PAGE_X
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT;
				inst->m_register_x = TEST_CPU_REGISTER_INDEX_OFFSET;
				inst->store(TEST_CPU_ADDRESS_ZERO_PAGE, 0);

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_STY_ZERO_PAGE_X);
				inst->store(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS_ZERO_PAGE);
				inst->step();
				st.cycles += CPU_CODE_STY_ZERO_PAGE_X_CYCLES;
				st.pc += CPU_CODE_STY_ZERO_PAGE_X_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				if(inst->load(TEST_CPU_ADDRESS_ZERO_PAGE + TEST_CPU_REGISTER_INDEX_OFFSET) 
						!= TEST_CPU_REGISTER_INIT) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_tax(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAX_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.x = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.x = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_tay(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAY_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.y = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAY_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.y = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_a = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TAY_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.y = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_tsx(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TSX_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.x = inst->m_register_sp;
				st.cycles += CPU_CODE_TSX_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TSX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.x = inst->m_register_sp;
				st.cycles += CPU_CODE_TSX_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TSX_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.x = inst->m_register_sp;
				st.cycles += CPU_CODE_TSX_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_txa(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXA_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXA_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_x = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXA_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_txs(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXS_IMPLIED);
				inst->step();
				st.sp = inst->m_register_x;
				st.cycles += CPU_CODE_TXS_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXS_IMPLIED);
				inst->step();
				st.sp = inst->m_register_x;
				st.cycles += CPU_CODE_TXS_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_sp = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TXS_IMPLIED);
				inst->step();
				st.sp = inst->m_register_x;
				st.cycles += CPU_CODE_TXS_IMPLIED_CYCLES;
				st.pc += CPU_CODE_STACK_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::execute_tya(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TYA_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE | CPU_FLAG_ZERO);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT_ZERO;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TYA_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_ZERO);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_NEGATIVE);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->m_register_y = TEST_CPU_REGISTER_INIT_MAX;

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_TYA_IMPLIED);
				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_NEGATIVE);
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_ZERO);
				st.a = inst->m_register_a;
				st.cycles += CPU_CODE_REGISTER_IMPLIED_CYCLES;
				st.pc += CPU_CODE_REGISTER_IMPLIED_LENGTH;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::initialize(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				try {
					inst->initialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				inst->initialize();

				if(!inst->is_initialized()
						|| (inst->m_cycles != CPU_CYCLES_INIT)
						|| (inst->m_register_a != CPU_REGISTER_A_INIT)
						|| (inst->m_register_p != CPU_REGISTER_P_INIT)
						|| (inst->m_register_pc != CPU_REGISTER_PC_INIT)
						|| (inst->m_register_sp != CPU_REGISTER_SP_INIT)
						|| (inst->m_register_x != CPU_REGISTER_X_INIT)
						|| (inst->m_register_y != CPU_REGISTER_Y_INIT)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::irq(
			__in void *context
			)
		{
			uint16_t pc;
			uint32_t cycles;
			uint8_t a, p, sp, x, y;
			nes_cpu_ptr inst = NULL;
			nes_memory_ptr mem_inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->irq();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				mem_inst = nes_memory::acquire();
				if(!mem_inst) {
					goto exit;
				}

				if(!mem_inst->is_initialized()) {
					mem_inst->initialize();
				}

				result = nes_test_cpu::reset_state(context);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_SET(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);
				a = inst->m_register_a;
				cycles = inst->m_cycles;
				pc = inst->m_register_pc;
				sp = inst->m_register_sp;
				x = inst->m_register_x;
				y = inst->m_register_y;
				p = inst->m_register_p;
				inst->irq();

				if((inst->m_cycles != cycles)
						|| (inst->m_register_a != a)
						|| (inst->m_register_p != p)
						|| (inst->m_register_pc != pc)
						|| (inst->m_register_sp != sp)
						|| (inst->m_register_x != x)
						|| (inst->m_register_y != y)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);
				p = inst->m_register_p;
				CPU_FLAG_SET(p, CPU_FLAG_INTERRUPT_DISABLED);
				inst->store_word(CPU_INTERRUPT_IRQ_ADDRESS, TEST_CPU_INTERRUPT_VECTOR);
				inst->irq();

				if((inst->m_cycles != (cycles + CPU_INTERRUPT_CYCLES))
						|| (inst->m_register_a != a)
						|| (inst->m_register_p != p)
						|| (inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR)
						|| (inst->m_register_sp != (sp - TEST_CPU_SP_INTERRUPT_OFFSET))
						|| (inst->m_register_x != x)
						|| (inst->m_register_y != y)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				CPU_FLAG_CLEAR(p, CPU_FLAG_INTERRUPT_DISABLED);

				if((mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 1) != p)
						|| (mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 2)
							!= (pc & UINT8_MAX))
						|| (mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 3) 
							!= ((pc >> BITS_PER_BYTE) & UINT8_MAX))) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			if(mem_inst && mem_inst->is_initialized()) {
				mem_inst->uninitialize();
			}

			return result;
		}

		nes_test_t 
		_nes_test_cpu::is_allocated(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(!nes_cpu::is_allocated()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::is_initialized(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(!inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->uninitialize();

				if(inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->initialize();

				if(!inst->is_initialized()) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::nmi(
			__in void *context
			)
		{
			uint16_t pc;
			uint32_t cycles;
			uint8_t a, p, sp, x, y;
			nes_cpu_ptr inst = NULL;
			nes_memory_ptr mem_inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->nmi();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				mem_inst = nes_memory::acquire();
				if(!mem_inst) {
					goto exit;
				}

				if(!mem_inst->is_initialized()) {
					mem_inst->initialize();
				}

				result = nes_test_cpu::reset_state(context);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				CPU_FLAG_CLEAR(inst->m_register_p, CPU_FLAG_INTERRUPT_DISABLED);
				a = inst->m_register_a;
				cycles = inst->m_cycles;
				pc = inst->m_register_pc;
				sp = inst->m_register_sp;
				x = inst->m_register_x;
				y = inst->m_register_y;
				p = inst->m_register_p;
				CPU_FLAG_SET(p, CPU_FLAG_INTERRUPT_DISABLED);
				inst->store_word(CPU_INTERRUPT_NMI_ADDRESS, TEST_CPU_INTERRUPT_VECTOR);
				inst->nmi();				

				if((inst->m_cycles != (cycles + CPU_INTERRUPT_CYCLES))
						|| (inst->m_register_a != a)
						|| (inst->m_register_p != p)
						|| (inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR)
						|| (inst->m_register_sp != (sp - TEST_CPU_SP_INTERRUPT_OFFSET))
						|| (inst->m_register_x != x)
						|| (inst->m_register_y != y)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				CPU_FLAG_CLEAR(p, CPU_FLAG_INTERRUPT_DISABLED);

				if((mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 1) != p)
						|| (mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 2)
							!= (pc & UINT8_MAX))
						|| (mem_inst->at(inst->m_register_sp + CPU_REGISTER_SP_OFFSET + 3) 
							!= ((pc >> BITS_PER_BYTE) & UINT8_MAX))) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			if(mem_inst && mem_inst->is_initialized()) {
				mem_inst->uninitialize();
			}

			return result;
		}

		nes_test_t 
		_nes_test_cpu::random_state(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {
				inst->m_cycles = rand() % UINT16_MAX;
				inst->m_register_a = rand() % UINT8_MAX;
				inst->m_register_p = rand() % UINT8_MAX;
				inst->m_register_pc = rand() % UINT16_MAX;
				inst->m_register_sp = rand() % UINT8_MAX;
				inst->m_register_x = rand() % UINT8_MAX;
				inst->m_register_y = rand() % UINT8_MAX;
			} catch(...) {
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::reset(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_memory_ptr mem_inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->reset();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				result = nes_test_cpu::random_state(context);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				mem_inst = nes_memory::acquire();
				if(!mem_inst) {
					goto exit;
				}

				if(!mem_inst->is_initialized()) {
					mem_inst->initialize();
				}

				inst->store_word(CPU_INTERRUPT_RESET_ADDRESS, TEST_CPU_INTERRUPT_VECTOR);
				inst->reset();

				if((inst->m_cycles != CPU_CYCLES_INIT)
						|| (inst->m_register_a != CPU_REGISTER_A_INIT)
						|| (inst->m_register_p != CPU_REGISTER_P_INIT)
						|| (inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR)
						|| (inst->m_register_sp != CPU_REGISTER_SP_INIT)
						|| (inst->m_register_x != CPU_REGISTER_X_INIT)
						|| (inst->m_register_y != CPU_REGISTER_Y_INIT)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::reset_state(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_memory_ptr mem_inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			mem_inst = nes_memory::acquire();
			if(!mem_inst->is_initialized()) {
				mem_inst->initialize();
			}

			inst->store_word(CPU_INTERRUPT_RESET_ADDRESS, TEST_CPU_INTERRUPT_VECTOR);
			inst->reset();
			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_set 
		_nes_test_cpu::set_generate(void)
		{
			size_t iter = 0;
			nes_test_set result(NES_CPU_HEADER);

			for(; iter < NES_TEST_CPU_MAX; ++iter) {
				result.insert(nes_test(NES_TEST_CPU_STRING(iter), NES_TEST_CPU_CALLBACK(iter), 
					nes_cpu::acquire(), nes_test_cpu::test_initialize, 
					nes_test_cpu::test_uninitialize));
			}

			return result;
		}

		nes_test_t 
		_nes_test_cpu::step(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_cpu_state st = { 0 };
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();

					try {
						inst->step();
						result = NES_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
				}

				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, TEST_CPU_CODE_INVALID);

				try {
					inst->step();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				// Subroutine (JSR -> RTS)
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}
				
				inst->store(TEST_CPU_ADDRESS, CPU_CODE_RTS_IMPLIED);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_JSR_ABSOLUTE);
				inst->store_word(TEST_CPU_INTERRUPT_VECTOR + 1, TEST_CPU_ADDRESS);
				inst->step();
				st.cycles += CPU_CODE_JSR_ABSOLUTE_CYCLES;
				st.pc = TEST_CPU_ADDRESS;
				st.sp -= TEST_CPU_SP_SUBROUTINE_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->step();
				st.cycles += CPU_CODE_RTS_IMPLIED_CYCLES;
				st.pc = (TEST_CPU_INTERRUPT_VECTOR + CPU_CODE_JSR_ABSOLUTE_LENGTH + 1);
				st.sp += TEST_CPU_SP_SUBROUTINE_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				// Interrupt (BRK -> RTI)
				result = nes_test_cpu::reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = nes_test_cpu::cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store_word(CPU_INTERRUPT_IRQ_ADDRESS, TEST_CPU_ADDRESS);
				inst->store(TEST_CPU_ADDRESS, CPU_CODE_RTI_IMPLIED);
				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_BRK_IMPLIED);
				inst->step();
				CPU_FLAG_CLEAR(st.p, CPU_FLAG_BREAKPOINT);
				st.cycles += CPU_CODE_BRK_IMPLIED_CYCLES;
				st.pc = TEST_CPU_ADDRESS;
				st.sp -= TEST_CPU_SP_INTERRUPT_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}

				inst->step();
				CPU_FLAG_SET(st.p, CPU_FLAG_BREAKPOINT);
				st.cycles += CPU_CODE_RTI_IMPLIED_CYCLES;
				st.pc = (TEST_CPU_INTERRUPT_VECTOR + CPU_CODE_RTI_IMPLIED_LENGTH + 1);
				st.sp += TEST_CPU_SP_INTERRUPT_OFFSET;

				if(!nes_test_cpu::compare_state(inst, st)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::test_initialize(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}

				inst->initialize();
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::test_uninitialize(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

				if(inst->is_initialized()) {
					inst->uninitialize();
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}

		nes_test_t 
		_nes_test_cpu::uninitialize(
			__in void *context
			)
		{
			nes_cpu_ptr inst = NULL;
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {
				inst->uninitialize();

				try {
					inst->uninitialize();
					result = NES_TEST_FAILURE;
					goto exit;
				} catch(...) { }

				if(!inst->is_initialized()
						|| (inst->m_cycles != CPU_CYCLES_INIT)
						|| (inst->m_register_a != CPU_REGISTER_A_INIT)
						|| (inst->m_register_p != CPU_REGISTER_P_INIT)
						|| (inst->m_register_pc != CPU_REGISTER_PC_INIT)
						|| (inst->m_register_sp != CPU_REGISTER_SP_INIT)
						|| (inst->m_register_x != CPU_REGISTER_X_INIT)
						|| (inst->m_register_y != CPU_REGISTER_Y_INIT)) {
					result = NES_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = NES_TEST_FAILURE;
				goto exit;
			}

			result = NES_TEST_SUCCESS;

exit:
			return result;
		}
	}
}

#endif // NDEBUG
