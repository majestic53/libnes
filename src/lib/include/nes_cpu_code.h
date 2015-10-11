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

#ifndef NES_CPU_CODE_H_
#define NES_CPU_CODE_H_

namespace NES {

	typedef enum {
		CPU_MODE_ABSOLUTE = 0,
		CPU_MODE_ABSOLUTE_X,
		CPU_MODE_ABSOLUTE_Y,
		CPU_MODE_ACCUMULATOR,
		CPU_MODE_IMMEDIATE,
		CPU_MODE_IMPLIED,
		CPU_MODE_INDIRECT,
		CPU_MODE_INDIRECT_X,
		CPU_MODE_INDIRECT_Y,
		CPU_MODE_RELATIVE,
		CPU_MODE_ZERO_PAGE,
		CPU_MODE_ZERO_PAGE_X,
		CPU_MODE_ZERO_PAGE_Y,
	} cpu_mode_t;

	#define CPU_CODE_ADC_ABSOLUTE 0x6d
	#define CPU_CODE_ADC_ABSOLUTE_X 0x7d
	#define CPU_CODE_ADC_ABSOLUTE_Y 0x79
	#define CPU_CODE_ADC_IMMEDIATE 0x69
	#define CPU_CODE_ADC_INDIRECT_X 0x61
	#define CPU_CODE_ADC_INDIRECT_Y 0x71
	#define CPU_CODE_ADC_ZERO_PAGE 0x65
	#define CPU_CODE_ADC_ZERO_PAGE_X 0x75
	#define CPU_CODE_AND_ABSOLUTE 0x2d
	#define CPU_CODE_AND_ABSOLUTE_X 0x3d
	#define CPU_CODE_AND_ABSOLUTE_Y 0x39
	#define CPU_CODE_AND_IMMEDIATE 0x29
	#define CPU_CODE_AND_INDIRECT_X 0x21
	#define CPU_CODE_AND_INDIRECT_Y 0x31
	#define CPU_CODE_AND_ZERO_PAGE 0x25
	#define CPU_CODE_AND_ZERO_PAGE_X 0x35
	#define CPU_CODE_ASL_ABSOLUTE 0xe
	#define CPU_CODE_ASL_ABSOLUTE_X 0x1e
	#define CPU_CODE_ASL_ACCUMULATOR 0xa
	#define CPU_CODE_ASL_ZERO_PAGE 0x6
	#define CPU_CODE_ASL_ZERO_PAGE_X 0x16
	#define CPU_CODE_BCC_RELATIVE 0x90
	#define CPU_CODE_BCS_RELATIVE 0xb0
	#define CPU_CODE_BEQ_RELATIVE 0xf0
	#define CPU_CODE_BIT_ABSOLUTE 0x2c
	#define CPU_CODE_BIT_ZERO_PAGE 0x24
	#define CPU_CODE_BMI_RELATIVE 0x30
	#define CPU_CODE_BNE_RELATIVE 0xd0
	#define CPU_CODE_BPL_RELATIVE 0x10
	#define CPU_CODE_BRK_IMPLIED 0
	#define CPU_CODE_BVC_RELATIVE 0x50
	#define CPU_CODE_BVS_RELATIVE 0x70
	#define CPU_CODE_CLC_IMPLIED 0x18
	#define CPU_CODE_CLD_IMPLIED 0xd8
	#define CPU_CODE_CLI_IMPLIED 0x58
	#define CPU_CODE_CLV_IMPLIED 0xb8
	#define CPU_CODE_CMP_ABSOLUTE 0xcd
	#define CPU_CODE_CMP_ABSOLUTE_X 0xdd
	#define CPU_CODE_CMP_ABSOLUTE_Y 0xd9
	#define CPU_CODE_CMP_IMMEDIATE 0xc9
	#define CPU_CODE_CMP_INDIRECT_X 0xc1
	#define CPU_CODE_CMP_INDIRECT_Y 0xd1
	#define CPU_CODE_CMP_ZERO_PAGE 0xc5
	#define CPU_CODE_CMP_ZERO_PAGE_X 0xd5
	#define CPU_CODE_CPX_ABSOLUTE 0xec
	#define CPU_CODE_CPX_IMMEDIATE 0xe0
	#define CPU_CODE_CPX_ZERO_PAGE 0xe4
	#define CPU_CODE_CPY_ABSOLUTE 0xcc
	#define CPU_CODE_CPY_IMMEDIATE 0xc0
	#define CPU_CODE_CPY_ZERO_PAGE 0xc4
	#define CPU_CODE_DEC_ABSOLUTE 0xce
	#define CPU_CODE_DEC_ABSOLUTE_X 0xde
	#define CPU_CODE_DEC_ZERO_PAGE 0xc6
	#define CPU_CODE_DEC_ZERO_PAGE_X 0xd6
	#define CPU_CODE_DEX_IMPLIED 0xca
	#define CPU_CODE_DEY_IMPLIED 0x88
	#define CPU_CODE_EOR_ABSOLUTE 0x4d
	#define CPU_CODE_EOR_ABSOLUTE_X 0x5d
	#define CPU_CODE_EOR_ABSOLUTE_Y 0x59
	#define CPU_CODE_EOR_IMMEDIATE 0x49
	#define CPU_CODE_EOR_INDIRECT_X 0x41
	#define CPU_CODE_EOR_INDIRECT_Y 0x51
	#define CPU_CODE_EOR_ZERO_PAGE 0x45
	#define CPU_CODE_EOR_ZERO_PAGE_X 0x55
	#define CPU_CODE_INC_ABSOLUTE 0xee
	#define CPU_CODE_INC_ABSOLUTE_X 0xfe
	#define CPU_CODE_INC_ZERO_PAGE 0xe6
	#define CPU_CODE_INC_ZERO_PAGE_X 0xf6
	#define CPU_CODE_INX_IMPLIED 0xe8
	#define CPU_CODE_INY_IMPLIED 0xc8
	#define CPU_CODE_JMP_ABSOLUTE 0x4c
	#define CPU_CODE_JMP_INDIRECT 0x6c
	#define CPU_CODE_JSR_ABSOLUTE 0x20
	#define CPU_CODE_LDA_ABSOLUTE 0xad
	#define CPU_CODE_LDA_ABSOLUTE_X 0xbd
	#define CPU_CODE_LDA_ABSOLUTE_Y 0xb9
	#define CPU_CODE_LDA_IMMEDIATE 0xa9
	#define CPU_CODE_LDA_INDIRECT_X 0xa1
	#define CPU_CODE_LDA_INDIRECT_Y 0xb1
	#define CPU_CODE_LDA_ZERO_PAGE 0xa5
	#define CPU_CODE_LDA_ZERO_PAGE_X 0xb5
	#define CPU_CODE_LDX_ABSOLUTE 0xae
	#define CPU_CODE_LDX_ABSOLUTE_Y 0xbe
	#define CPU_CODE_LDX_IMMEDIATE 0xa2
	#define CPU_CODE_LDX_ZERO_PAGE 0xa6
	#define CPU_CODE_LDX_ZERO_PAGE_Y 0xb6
	#define CPU_CODE_LDY_ABSOLUTE 0xac
	#define CPU_CODE_LDY_ABSOLUTE_X 0xbc
	#define CPU_CODE_LDY_IMMEDIATE 0xa0
	#define CPU_CODE_LDY_ZERO_PAGE 0xa4
	#define CPU_CODE_LDY_ZERO_PAGE_X 0xb4
	#define CPU_CODE_LSR_ABSOLUTE 0x4e
	#define CPU_CODE_LSR_ABSOLUTE_X 0x5e
	#define CPU_CODE_LSR_ACCUMULATOR 0x4a
	#define CPU_CODE_LSR_ZERO_PAGE 0x46
	#define CPU_CODE_LSR_ZERO_PAGE_X 0x56
	#define CPU_CODE_NOP_IMPLIED 0xea
	#define CPU_CODE_ORA_ABSOLUTE 0xd
	#define CPU_CODE_ORA_ABSOLUTE_X 0x1d
	#define CPU_CODE_ORA_ABSOLUTE_Y 0x19
	#define CPU_CODE_ORA_IMMEDIATE 0x9
	#define CPU_CODE_ORA_INDIRECT_X 0x1
	#define CPU_CODE_ORA_INDIRECT_Y 0x11
	#define CPU_CODE_ORA_ZERO_PAGE 0x5
	#define CPU_CODE_ORA_ZERO_PAGE_X 0x15
	#define CPU_CODE_PHA_IMPLIED 0x48
	#define CPU_CODE_PHP_IMPLIED 0x8
	#define CPU_CODE_PLA_IMPLIED 0x68
	#define CPU_CODE_PLP_IMPLIED 0x28
	#define CPU_CODE_ROL_ABSOLUTE 0x2e
	#define CPU_CODE_ROL_ABSOLUTE_X 0x3e
	#define CPU_CODE_ROL_ACCUMULATOR 0x2a
	#define CPU_CODE_ROL_ZERO_PAGE 0x26
	#define CPU_CODE_ROL_ZERO_PAGE_X 0x36
	#define CPU_CODE_ROR_ABSOLUTE 0x6e
	#define CPU_CODE_ROR_ABSOLUTE_X 0x7e
	#define CPU_CODE_ROR_ACCUMULATOR 0x6a
	#define CPU_CODE_ROR_ZERO_PAGE 0x66
	#define CPU_CODE_ROR_ZERO_PAGE_X 0x76
	#define CPU_CODE_RTI_IMPLIED 0x40
	#define CPU_CODE_RTS_IMPLIED 0x60
	#define CPU_CODE_SBC_ABSOLUTE 0xed
	#define CPU_CODE_SBC_ABSOLUTE_X 0xfd
	#define CPU_CODE_SBC_ABSOLUTE_Y 0xf9
	#define CPU_CODE_SBC_IMMEDIATE 0xe9
	#define CPU_CODE_SBC_INDIRECT_X 0xe1
	#define CPU_CODE_SBC_INDIRECT_Y 0xf1
	#define CPU_CODE_SBC_ZERO_PAGE 0xe5
	#define CPU_CODE_SBC_ZERO_PAGE_X 0xf5
	#define CPU_CODE_SEC_IMPLIED 0x38
	#define CPU_CODE_SED_IMPLIED 0xf8
	#define CPU_CODE_SEI_IMPLIED 0x78
	#define CPU_CODE_STA_ABSOLUTE 0x8d
	#define CPU_CODE_STA_ABSOLUTE_X 0x9d
	#define CPU_CODE_STA_ABSOLUTE_Y 0x99
	#define CPU_CODE_STA_INDIRECT_X 0x81
	#define CPU_CODE_STA_INDIRECT_Y 0x91
	#define CPU_CODE_STA_ZERO_PAGE 0x85
	#define CPU_CODE_STA_ZERO_PAGE_X 0x95
	#define CPU_CODE_STX_ABSOLUTE 0x8e
	#define CPU_CODE_STX_ZERO_PAGE 0x86
	#define CPU_CODE_STX_ZERO_PAGE_Y 0x96
	#define CPU_CODE_STY_ABSOLUTE 0x8c
	#define CPU_CODE_STY_ZERO_PAGE 0x84
	#define CPU_CODE_STY_ZERO_PAGE_X 0x94
	#define CPU_CODE_TAX_IMPLIED 0xaa
	#define CPU_CODE_TAY_IMPLIED 0xa8
	#define CPU_CODE_TSX_IMPLIED 0xba
	#define CPU_CODE_TXA_IMPLIED 0x8a
	#define CPU_CODE_TXS_IMPLIED 0x9a
	#define CPU_CODE_TYA_IMPLIED 0x98

	#define CPU_CODE_ADC_ABSOLUTE_CYLCES 4
	#define CPU_CODE_ADC_ABSOLUTE_X_CYLCES 4
	#define CPU_CODE_ADC_ABSOLUTE_Y_CYLCES 4
	#define CPU_CODE_ADC_IMMEDIATE_CYLCES 2
	#define CPU_CODE_ADC_INDIRECT_X_CYLCES 6
	#define CPU_CODE_ADC_INDIRECT_Y_CYLCES 5
	#define CPU_CODE_ADC_ZERO_PAGE_CYLCES 3
	#define CPU_CODE_ADC_ZERO_PAGE_X_CYLCES 4
	#define CPU_CODE_AND_ABSOLUTE_CYCLES 4
	#define CPU_CODE_AND_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_AND_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_AND_IMMEDIATE_CYCLES 2
	#define CPU_CODE_AND_INDIRECT_X_CYCLES 6
	#define CPU_CODE_AND_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_AND_ZERO_PAGE_CYCLES 2
	#define CPU_CODE_AND_ZERO_PAGE_X_CYCLES 3
	#define CPU_CODE_ASL_ABSOLUTE_CYCLES 6
	#define CPU_CODE_ASL_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_ASL_ACCUMULATOR_CYCLES 2
	#define CPU_CODE_ASL_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_ASL_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_BIT_ABSOLUTE_CYCLES 4
	#define CPU_CODE_BIT_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_BRANCH_RELATIVE_CYCLES 2
	#define CPU_CODE_BRK_IMPLIED_CYCLES 7
	#define CPU_CODE_CMP_ABSOLUTE_CYCLES 4
	#define CPU_CODE_CMP_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_CMP_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_CMP_IMMEDIATE_CYCLES 2
	#define CPU_CODE_CMP_INDIRECT_X_CYCLES 6
	#define CPU_CODE_CMP_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_CMP_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_CMP_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_CPX_ABSOLUTE_CYCLES 4
	#define CPU_CODE_CPX_IMMEDIATE_CYCLES 2
	#define CPU_CODE_CPX_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_CPY_ABSOLUTE_CYCLES 4
	#define CPU_CODE_CPY_IMMEDIATE_CYCLES 2
	#define CPU_CODE_CPY_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_DEC_ABSOLUTE_CYCLES 6
	#define CPU_CODE_DEC_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_DEC_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_DEC_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_EOR_ABSOLUTE_CYCLES 4
	#define CPU_CODE_EOR_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_EOR_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_EOR_IMMEDIATE_CYCLES 2
	#define CPU_CODE_EOR_INDIRECT_X_CYCLES 6
	#define CPU_CODE_EOR_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_EOR_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_EOR_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_FLAG_IMPLIED_CYCLES 2
	#define CPU_CODE_INC_ABSOLUTE_CYCLES 6
	#define CPU_CODE_INC_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_INC_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_INC_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_JMP_ABSOLUTE_CYCLES 3
	#define CPU_CODE_JMP_INDIRECT_CYCLES 5
	#define CPU_CODE_JSR_ABSOLUTE_CYCLES 6
	#define CPU_CODE_LDA_ABSOLUTE_CYCLES 4
	#define CPU_CODE_LDA_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_LDA_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_LDA_IMMEDIATE_CYCLES 2
	#define CPU_CODE_LDA_INDIRECT_X_CYCLES 6
	#define CPU_CODE_LDA_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_LDA_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_LDA_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_LDX_ABSOLUTE_CYCLES 4
	#define CPU_CODE_LDX_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_LDX_IMMEDIATE_CYCLES 2
	#define CPU_CODE_LDX_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_LDX_ZERO_PAGE_Y_CYCLES 4
	#define CPU_CODE_LDY_ABSOLUTE_CYCLES 4
	#define CPU_CODE_LDY_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_LDY_IMMEDIATE_CYCLES 2
	#define CPU_CODE_LDY_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_LDY_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_LSR_ABSOLUTE_CYCLES 6
	#define CPU_CODE_LSR_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_LSR_ACCUMULATOR_CYCLES 2
	#define CPU_CODE_LSR_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_LSR_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_NOP_IMPLIED_CYCLES 2
	#define CPU_CODE_ORA_ABSOLUTE_CYCLES 4
	#define CPU_CODE_ORA_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_ORA_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_ORA_IMMEDIATE_CYCLES 2
	#define CPU_CODE_ORA_INDIRECT_X_CYCLES 6
	#define CPU_CODE_ORA_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_ORA_ZERO_PAGE_CYCLES 2
	#define CPU_CODE_ORA_ZERO_PAGE_X_CYCLES 3
	#define CPU_CODE_PHA_IMPLIED_CYCLES 3
	#define CPU_CODE_PHP_IMPLIED_CYCLES 3
	#define CPU_CODE_PLA_IMPLIED_CYCLES 4
	#define CPU_CODE_PLP_IMPLIED_CYCLES 4
	#define CPU_CODE_REGISTER_IMPLIED_CYCLES 2
	#define CPU_CODE_ROL_ABSOLUTE_CYCLES 6
	#define CPU_CODE_ROL_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_ROL_ACCUMULATOR_CYCLES 2
	#define CPU_CODE_ROL_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_ROL_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_ROR_ABSOLUTE_CYCLES 6
	#define CPU_CODE_ROR_ABSOLUTE_X_CYCLES 7
	#define CPU_CODE_ROR_ACCUMULATOR_CYCLES 2
	#define CPU_CODE_ROR_ZERO_PAGE_CYCLES 5
	#define CPU_CODE_ROR_ZERO_PAGE_X_CYCLES 6
	#define CPU_CODE_RTI_IMPLIED_CYCLES 6
	#define CPU_CODE_RTS_IMPLIED_CYCLES 6
	#define CPU_CODE_SBC_ABSOLUTE_CYCLES 4
	#define CPU_CODE_SBC_ABSOLUTE_X_CYCLES 4
	#define CPU_CODE_SBC_ABSOLUTE_Y_CYCLES 4
	#define CPU_CODE_SBC_IMMEDIATE_CYCLES 2
	#define CPU_CODE_SBC_INDIRECT_X_CYCLES 6
	#define CPU_CODE_SBC_INDIRECT_Y_CYCLES 5
	#define CPU_CODE_SBC_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_SBC_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_STA_ABSOLUTE_CYCLES 4
	#define CPU_CODE_STA_ABSOLUTE_X_CYCLES 5
	#define CPU_CODE_STA_ABSOLUTE_Y_CYCLES 5
	#define CPU_CODE_STA_INDIRECT_X_CYCLES 6
	#define CPU_CODE_STA_INDIRECT_Y_CYCLES 6
	#define CPU_CODE_STA_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_STA_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_STX_ABSOLUTE_CYCLES 4
	#define CPU_CODE_STX_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_STX_ZERO_PAGE_Y_CYCLES 4
	#define CPU_CODE_STY_ABSOLUTE_CYCLES 4
	#define CPU_CODE_STY_ZERO_PAGE_CYCLES 3
	#define CPU_CODE_STY_ZERO_PAGE_X_CYCLES 4
	#define CPU_CODE_TSX_IMPLIED_CYCLES 2
	#define CPU_CODE_TXS_IMPLIED_CYCLES 2

	#define CPU_CODE_ADC_ABSOLUTE_LENGTH 3
	#define CPU_CODE_ADC_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_ADC_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_ADC_IMMEDIATE_LENGTH 2
	#define CPU_CODE_ADC_INDIRECT_X_LENGTH 2
	#define CPU_CODE_ADC_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_ADC_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_ADC_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_AND_ABSOLUTE_LENGTH 3
	#define CPU_CODE_AND_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_AND_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_AND_IMMEDIATE_LENGTH 2
	#define CPU_CODE_AND_INDIRECT_X_LENGTH 2
	#define CPU_CODE_AND_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_AND_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_AND_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_ASL_ABSOLUTE_LENGTH 3
	#define CPU_CODE_ASL_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_ASL_ACCUMULATOR_LENGTH 1
	#define CPU_CODE_ASL_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_ASL_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_BIT_ABSOLUTE_LENGTH 3
	#define CPU_CODE_BIT_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_BRANCH_RELATIVE_LENGTH 2
	#define CPU_CODE_BRK_IMPLIED_LENGTH 2
	#define CPU_CODE_CMP_ABSOLUTE_LENGTH 3
	#define CPU_CODE_CMP_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_CMP_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_CMP_IMMEDIATE_LENGTH 2
	#define CPU_CODE_CMP_INDIRECT_X_LENGTH 2
	#define CPU_CODE_CMP_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_CMP_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_CMP_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_CPX_ABSOLUTE_LENGTH 3
	#define CPU_CODE_CPX_IMMEDIATE_LENGTH 2
	#define CPU_CODE_CPX_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_CPY_ABSOLUTE_LENGTH 3
	#define CPU_CODE_CPY_IMMEDIATE_LENGTH 2
	#define CPU_CODE_CPY_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_DEC_ABSOLUTE_LENGTH 3
	#define CPU_CODE_DEC_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_DEC_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_DEC_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_EOR_ABSOLUTE_LENGTH 3
	#define CPU_CODE_EOR_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_EOR_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_EOR_IMMEDIATE_LENGTH 2
	#define CPU_CODE_EOR_INDIRECT_X_LENGTH 2
	#define CPU_CODE_EOR_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_EOR_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_EOR_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_FLAG_IMPLIED_LENGTH 1
	#define CPU_CODE_INC_ABSOLUTE_LENGTH 3
	#define CPU_CODE_INC_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_INC_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_INC_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_JMP_ABSOLUTE_LENGTH 3
	#define CPU_CODE_JMP_INDIRECT_LENGTH 3
	#define CPU_CODE_JSR_ABSOLUTE_LENGTH 3
	#define CPU_CODE_LDA_ABSOLUTE_LENGTH 3
	#define CPU_CODE_LDA_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_LDA_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_LDA_INDIRECT_X_LENGTH 2
	#define CPU_CODE_LDA_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_LDA_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_LDA_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_LDA_IMMEDIATE_LENGTH 2
	#define CPU_CODE_LDX_ABSOLUTE_LENGTH 3
	#define CPU_CODE_LDX_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_LDX_IMMEDIATE_LENGTH 2
	#define CPU_CODE_LDX_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_LDX_ZERO_PAGE_Y_LENGTH 2
	#define CPU_CODE_LDY_ABSOLUTE_LENGTH 3
	#define CPU_CODE_LDY_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_LDY_IMMEDIATE_LENGTH 2
	#define CPU_CODE_LDY_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_LDY_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_LSR_ABSOLUTE_LENGTH 3
	#define CPU_CODE_LSR_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_LSR_ACCUMULATOR_LENGTH 1
	#define CPU_CODE_LSR_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_LSR_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_NOP_IMPLIED_LENGTH 1
	#define CPU_CODE_ORA_ABSOLUTE_LENGTH 3
	#define CPU_CODE_ORA_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_ORA_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_ORA_IMMEDIATE_LENGTH 2
	#define CPU_CODE_ORA_INDIRECT_X_LENGTH 2
	#define CPU_CODE_ORA_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_ORA_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_ORA_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_REGISTER_IMPLIED_LENGTH 1
	#define CPU_CODE_ROL_ABSOLUTE_LENGTH 3
	#define CPU_CODE_ROL_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_ROL_ACCUMULATOR_LENGTH 1
	#define CPU_CODE_ROL_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_ROL_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_ROR_ABSOLUTE_LENGTH 3
	#define CPU_CODE_ROR_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_ROR_ACCUMULATOR_LENGTH 1
	#define CPU_CODE_ROR_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_ROR_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_RTI_IMPLIED_LENGTH 1
	#define CPU_CODE_RTS_IMPLIED_LENGTH 1
	#define CPU_CODE_SBC_ABSOLUTE_LENGTH 3
	#define CPU_CODE_SBC_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_SBC_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_SBC_IMMEDIATE_LENGTH 2
	#define CPU_CODE_SBC_INDIRECT_X_LENGTH 2
	#define CPU_CODE_SBC_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_SBC_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_SBC_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_STACK_IMPLIED_LENGTH 1
	#define CPU_CODE_STA_ABSOLUTE_LENGTH 3
	#define CPU_CODE_STA_ABSOLUTE_X_LENGTH 3
	#define CPU_CODE_STA_ABSOLUTE_Y_LENGTH 3
	#define CPU_CODE_STA_INDIRECT_X_LENGTH 2
	#define CPU_CODE_STA_INDIRECT_Y_LENGTH 2
	#define CPU_CODE_STA_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_STA_ZERO_PAGE_X_LENGTH 2
	#define CPU_CODE_STX_ABSOLUTE_LENGTH 3
	#define CPU_CODE_STX_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_STX_ZERO_PAGE_Y_LENGTH 2
	#define CPU_CODE_STY_ABSOLUTE_LENGTH 3
	#define CPU_CODE_STY_ZERO_PAGE_LENGTH 2
	#define CPU_CODE_STY_ZERO_PAGE_X_LENGTH 2
}

#endif // NES_CPU_OPCODE_H_
