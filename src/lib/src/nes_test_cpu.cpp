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

		#define TEST_CPU_INTERRUPT_VECTOR 0xabcd
		#define TEST_CPU_SP_INTERRUPT_OFFSET 3

		enum {
			NES_TEST_CPU_ACQUIRE = 0,
			NES_TEST_CPU_CLEAR,
			NES_TEST_CPU_CYCLES,
			NES_TEST_CPU_EXECUTE_BCC,
			NES_TEST_CPU_EXECUTE_BCS,
			NES_TEST_CPU_EXECUTE_BEQ,
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
			NES_TEST_CPU_EXECUTE_DEX,
			NES_TEST_CPU_EXECUTE_DEY,
			NES_TEST_CPU_EXECUTE_INX,
			NES_TEST_CPU_EXECUTE_INY,
			NES_TEST_CPU_EXECUTE_LDA,
			NES_TEST_CPU_EXECUTE_NOP,
			NES_TEST_CPU_EXECUTE_PHA,
			NES_TEST_CPU_EXECUTE_PHP,
			NES_TEST_CPU_EXECUTE_PLA,
			NES_TEST_CPU_EXECUTE_PLP,
			NES_TEST_CPU_EXECUTE_RTI,
			NES_TEST_CPU_EXECUTE_RTS,
			NES_TEST_CPU_EXECUTE_SEC,
			NES_TEST_CPU_EXECUTE_SED,
			NES_TEST_CPU_EXECUTE_SEI,
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
			NES_CPU_HEADER "::BCC",
			NES_CPU_HEADER "::BCS",
			NES_CPU_HEADER "::BEQ",
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
			NES_CPU_HEADER "::DEX",
			NES_CPU_HEADER "::DEY",
			NES_CPU_HEADER "::INX",
			NES_CPU_HEADER "::INY",
			NES_CPU_HEADER "::LDA",
			NES_CPU_HEADER "::NOP",
			NES_CPU_HEADER "::PHA",
			NES_CPU_HEADER "::PHP",
			NES_CPU_HEADER "::PLA",
			NES_CPU_HEADER "::PLP",
			NES_CPU_HEADER "::RTI",
			NES_CPU_HEADER "::RTS",
			NES_CPU_HEADER "::SEC",
			NES_CPU_HEADER "::SED",
			NES_CPU_HEADER "::SEI",
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
			nes_test_cpu::execute_bcc,
			nes_test_cpu::execute_bcs,
			nes_test_cpu::execute_beq,
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
			nes_test_cpu::execute_dex,
			nes_test_cpu::execute_dey,
			nes_test_cpu::execute_inx,
			nes_test_cpu::execute_iny,
			nes_test_cpu::execute_lda,
			nes_test_cpu::execute_nop,
			nes_test_cpu::execute_pha,
			nes_test_cpu::execute_php,
			nes_test_cpu::execute_pla,
			nes_test_cpu::execute_plp,
			nes_test_cpu::execute_rti,
			nes_test_cpu::execute_rts,
			nes_test_cpu::execute_sec,
			nes_test_cpu::execute_sed,
			nes_test_cpu::execute_sei,
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
		_nes_test_cpu::execute_bcc(
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
		_nes_test_cpu::execute_bcs(
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
		_nes_test_cpu::execute_beq(
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
		_nes_test_cpu::execute_bmi(
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
		_nes_test_cpu::execute_bne(
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
		_nes_test_cpu::execute_bpl(
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
		_nes_test_cpu::execute_brk(
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
		_nes_test_cpu::execute_bvc(
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
		_nes_test_cpu::execute_bvs(
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
		_nes_test_cpu::execute_clc(
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
		_nes_test_cpu::execute_cld(
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
		_nes_test_cpu::execute_cli(
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
		_nes_test_cpu::execute_clv(
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
		_nes_test_cpu::execute_dex(
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
		_nes_test_cpu::execute_dey(
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
		_nes_test_cpu::execute_inx(
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
		_nes_test_cpu::execute_iny(
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
		_nes_test_cpu::execute_lda(
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

				result = reset_state(inst);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				if(inst->m_register_pc != TEST_CPU_INTERRUPT_VECTOR) {
					goto exit;
				}

				result = cache_state(inst, st);
				if(!NES_TEST_SUCCESS(result)) {
					goto exit;
				}

				inst->store(TEST_CPU_INTERRUPT_VECTOR, CPU_CODE_NOP_IMPLIED);
				inst->step();
				st.cycles += CPU_CODE_NOP_IMPLIED_CYCLES;
				st.pc += CPU_CODE_NOP_IMPLIED_LENGTH;

				if(!compare_state(inst, st)) {
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
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

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
		_nes_test_cpu::execute_php(
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
		_nes_test_cpu::execute_pla(
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
		_nes_test_cpu::execute_plp(
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
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			try {

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
		_nes_test_cpu::execute_rts(
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
		_nes_test_cpu::execute_sec(
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
		_nes_test_cpu::execute_sed(
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
		_nes_test_cpu::execute_sei(
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
		_nes_test_cpu::execute_tax(
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
		_nes_test_cpu::execute_tay(
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
		_nes_test_cpu::execute_tsx(
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
		_nes_test_cpu::execute_txa(
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
		_nes_test_cpu::execute_txs(
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
		_nes_test_cpu::execute_tya(
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

				result = nes_test_cpu::random_state(context);
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

				result = nes_test_cpu::random_state(context);
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
			nes_test_t result = NES_TEST_INCONCLUSIVE;

			if(!context) {
				goto exit;
			}

			inst = (nes_cpu_ptr) context;
			if(!inst) {
				goto exit;
			}

			nes_memory::acquire()->initialize();
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
