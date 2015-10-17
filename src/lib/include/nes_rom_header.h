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

#ifndef NES_ROM_HEADER_H_
#define NES_ROM_HEADER_H_

namespace NES {

	#define ROM_INES_2 2
	#define ROM_INES_2_RES_LEN 2
	#define ROM_INES_RES_LEN 5
	#define ROM_MAGIC "\x4E\x45\x53\x1A"
	#define ROM_MAGIC_LEN 4
	#define ROM_RAM_PROGRAM_LEN 0x2000
	#define ROM_ROM_CHARACTER_LEN 0x2000
	#define ROM_ROM_PROGRAM_LEN 0x4000

	enum {
		FLAG_6_MIRRORING_HORZ = 0,
		FLAG_6_MIRRORING_VERT,
	};

	enum {
		FLAG_9_1_TV_MODE_NTSC = 0,
		FLAG_9_1_TV_MODE_PAL,
	};

	enum {
		FLAG_10_1_TV_MODE_NTSC = 0,
		FLAG_10_1_TV_MODE_PAL = 2,
	};

	enum {
		FLAG_12_2_TV_MODE_NTSC = 0,
		FLAG_12_2_TV_MODE_PAL = 1,
	};

	typedef struct {
		uint8_t mirroring : 1;			// mirroring (0=horz, 1=vert)
		uint8_t sram : 1;			// sram present
		uint8_t trainer : 1;			// trainer present
		uint8_t four_screen_mode : 1;		// four-screen mode active
		uint8_t mapper_lower : 4;		// mapper low nibble
	} nes_rom_header_flag_6;

	typedef struct {
		uint8_t vs : 1;				// vs. unisystem cartridge
		uint8_t pc : 1;				// playchoice-10 cartridge
		uint8_t format : 2;			// rom format (0b10=ines2)
		uint8_t mapper_high : 4;		// mapper high nibble
	} nes_rom_header_flag_7;

	typedef struct {
		uint8_t mode : 1;			// tv mode (0=ntsc, 1=pal)
		uint8_t reserved : 7;
	} nes_rom_header_flag_9_1;

	typedef struct {
		uint8_t mode : 2;			// tv mode (0=ntsc, 2=pal, 1/3=dual)
		uint8_t reserved : 2;
		uint8_t ram : 1;			// prg ram present
		uint8_t bus_conflict : 1;		// bus conflict present
	} nes_rom_header_flag_10_1;

	typedef struct {
		uint8_t mapper_highest : 4;		// mapper highest nibble
		uint8_t mapper_sub : 4;			// submapper
	} nes_rom_header_flag_8_2;

	typedef struct {
		uint8_t rom_program_high : 4;		// number of prg rom blocks high
		uint8_t rom_character_high : 4;		// number of chr rom blocks high
	} nes_rom_header_flag_9_2;

	typedef struct {
		uint8_t rom_program_non_sram : 4;	// number of non-sram prg rom blocks
		uint8_t rom_program_sram : 4;		// number of sram prg rom blocks
	} nes_rom_header_flag_10_2;

	typedef struct {
		uint8_t rom_character_non_sram : 4;	// number of non-sram chr rom blocks
		uint8_t rom_character_sram : 4;		// number of sram chr rom blocks
	} nes_rom_header_flag_11_2;

	typedef struct {
		uint8_t mode : 2;			// tv mode (0=ntsc, 1=pal, >1=dual)
		uint8_t reserved : 6;
	} nes_rom_header_flag_12_2;

	typedef struct {
		uint8_t vs_ppu : 4;			// vs. unisystem ppu type
		uint8_t vs_mode : 4;			// vs. unisystem mode
	} nes_rom_header_flag_13_2;

	typedef struct {
		uint8_t block_program_ram;		// number of prg ram blocks (x8KB)
		nes_rom_header_flag_9_1 flag_9;
		nes_rom_header_flag_10_1 flag_10;
		uint8_t reserved[ROM_INES_RES_LEN];
	} nes_rom_header_ines_1;

	typedef struct {
		nes_rom_header_flag_8_2 flag_8;
		nes_rom_header_flag_9_2 flag_9;
		nes_rom_header_flag_10_2 flag_10;
		nes_rom_header_flag_11_2 flag_11;
		nes_rom_header_flag_12_2 flag_12;
		nes_rom_header_flag_13_2 flag_13;
		uint8_t reserved[ROM_INES_2_RES_LEN];
	} nes_rom_header_ines_2;

	typedef struct {
		uint8_t magic[ROM_MAGIC_LEN];		// magic string
		uint8_t rom_program;			// number of prg rom blocks (x16KB)
		uint8_t rom_character;			// number of chr rom blocks (x8KB)
		nes_rom_header_flag_6 flag_6;		// flag 6
		nes_rom_header_flag_7 flag_7;		// flag 7
		union {
			nes_rom_header_ines_1 ines_1;
			nes_rom_header_ines_2 ines_2;
		} extension;
	} nes_rom_header;
}

#endif // NES_ROM_HEADER_H_
