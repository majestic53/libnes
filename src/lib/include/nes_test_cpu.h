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

#ifndef NDEBUG
#ifndef NES_TEST_CPU_H_
#define NES_TEST_CPU_H_

namespace NES {

	namespace TEST {

		typedef struct _nes_cpu_state {
			uint8_t a;
			uint32_t cycles;
			uint8_t p;
			uint16_t pc;
			uint8_t sp;
			uint8_t x;
			uint8_t y;
		} nes_cpu_state, *nes_cpu_state_ptr;

		typedef class _nes_test_cpu {

			public:

				static nes_test_t acquire(
					__in void *context
					);

				static nes_test_t clear(
					__in void *context
					);

				static nes_test_t cycles(
					__in void *context
					);

				static nes_test_t execute_bcc(
					__in void *context
					);

				static nes_test_t execute_bcs(
					__in void *context
					);

				static nes_test_t execute_beq(
					__in void *context
					);

				static nes_test_t execute_bit(
					__in void *context
					);

				static nes_test_t execute_bmi(
					__in void *context
					);

				static nes_test_t execute_bne(
					__in void *context
					);

				static nes_test_t execute_bpl(
					__in void *context
					);

				static nes_test_t execute_brk(
					__in void *context
					);

				static nes_test_t execute_bvc(
					__in void *context
					);

				static nes_test_t execute_bvs(
					__in void *context
					);

				static nes_test_t execute_clc(
					__in void *context
					);

				static nes_test_t execute_cld(
					__in void *context
					);

				static nes_test_t execute_cli(
					__in void *context
					);

				static nes_test_t execute_clv(
					__in void *context
					);

				static nes_test_t execute_dex(
					__in void *context
					);

				static nes_test_t execute_dey(
					__in void *context
					);

				static nes_test_t execute_inx(
					__in void *context
					);

				static nes_test_t execute_iny(
					__in void *context
					);

				static nes_test_t execute_jmp(
					__in void *context
					);

				static nes_test_t execute_jsr(
					__in void *context
					);

				static nes_test_t execute_lda(
					__in void *context
					);

				static nes_test_t execute_ldx(
					__in void *context
					);

				static nes_test_t execute_ldy(
					__in void *context
					);

				static nes_test_t execute_nop(
					__in void *context
					);

				static nes_test_t execute_pha(
					__in void *context
					);

				static nes_test_t execute_php(
					__in void *context
					);

				static nes_test_t execute_pla(
					__in void *context
					);

				static nes_test_t execute_plp(
					__in void *context
					);

				static nes_test_t execute_rti(
					__in void *context
					);

				static nes_test_t execute_rts(
					__in void *context
					);

				static nes_test_t execute_sec(
					__in void *context
					);

				static nes_test_t execute_sed(
					__in void *context
					);

				static nes_test_t execute_sei(
					__in void *context
					);

				static nes_test_t execute_tax(
					__in void *context
					);

				static nes_test_t execute_tay(
					__in void *context
					);

				static nes_test_t execute_tsx(
					__in void *context
					);

				static nes_test_t execute_txa(
					__in void *context
					);

				static nes_test_t execute_txs(
					__in void *context
					);

				static nes_test_t execute_tya(
					__in void *context
					);

				static nes_test_t initialize(
					__in void *context
					);

				static nes_test_t irq(
					__in void *context
					);

				static nes_test_t is_allocated(
					__in void *context
					);

				static nes_test_t is_initialized(
					__in void *context
					);

				static nes_test_t nmi(
					__in void *context
					);

				static nes_test_t reset(
					__in void *context
					);

				static nes_test_set set_generate(void);

				static nes_test_t step(
					__in void *context
					);

				static nes_test_t test_initialize(
					__in void *context
					);

				static nes_test_t test_uninitialize(
					__in void *context
					);

				static nes_test_t uninitialize(
					__in void *context
					);

			protected:

				static nes_test_t cache_state(
					__in void *context,
					__inout nes_cpu_state &state
					);

				static bool compare_state(
					__in void *context,
					__in const nes_cpu_state &state
					);

				static nes_test_t random_state(
					__in void *context
					);

				static nes_test_t reset_state(
					__in void *context
					);

		} nes_test_cpu, *nes_test_cpu_ptr;
	}
}

#endif // NES_TEST_CPU_H_
#endif // NDEBUG
