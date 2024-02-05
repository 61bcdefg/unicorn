/*
 * Tiny Code Generator for QEMU
 *
 * Copyright (c) 2009, 2011 Stefan Weil
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * This code implements a TCG which does not generate machine code for some
 * real target machine but which generates virtual machine code for an
 * interpreter. Interpreted pseudo code is slow, but it works on any host.
 *
 * Some remarks might help in understanding the code:
 *
 * "target" or "TCG target" is the machine which runs the generated code.
 * This is different to the usual meaning in QEMU where "target" is the
 * emulated machine. So normally QEMU host is identical to TCG target.
 * Here the TCG target is a virtual machine, but this virtual machine must
 * use the same word size like the real machine.
 * Therefore, we need both 32 and 64 bit virtual machines (interpreter).
 */

#ifndef TCG_TARGET_H
#define TCG_TARGET_H

#if UINTPTR_MAX == UINT32_MAX
# error We only support AArch64 running in 64B mode.
#elif UINTPTR_MAX == UINT64_MAX
# define TCG_TARGET_REG_BITS 64
#else
# error Unknown pointer size for tcti target
#endif

#define TCG_TARGET_INSN_UNIT_SIZE        1
#define TCG_TARGET_TLB_DISPLACEMENT_BITS 32

// We're an interpreted target; even if we're JIT-compiling to our interpreter's
// weird psuedo-native bytecode. We'll indicate that we're intepreted.
#define TCG_TARGET_INTERPRETER 1

// Specify we'll handle direct jumps.
#define TCG_TARGET_HAS_direct_jump      1

//
// Supported optional scalar instructions.
//

// Divs.
#define TCG_TARGET_HAS_div_i32          1
#define TCG_TARGET_HAS_rem_i32          1
#define TCG_TARGET_HAS_div_i64          1
#define TCG_TARGET_HAS_rem_i64          1

// Extends.
#define TCG_TARGET_HAS_ext8s_i32        1
#define TCG_TARGET_HAS_ext16s_i32       1
#define TCG_TARGET_HAS_ext8u_i32        1
#define TCG_TARGET_HAS_ext16u_i32       1
#define TCG_TARGET_HAS_ext8s_i64        1
#define TCG_TARGET_HAS_ext16s_i64       1
#define TCG_TARGET_HAS_ext32s_i64       1
#define TCG_TARGET_HAS_ext8u_i64        1
#define TCG_TARGET_HAS_ext16u_i64       1
#define TCG_TARGET_HAS_ext32u_i64       1

// Register extractions.
#define TCG_TARGET_HAS_extrl_i64_i32    1
#define TCG_TARGET_HAS_extrh_i64_i32    1

// Negations.
#define TCG_TARGET_HAS_neg_i32          1
#define TCG_TARGET_HAS_not_i32          1
#define TCG_TARGET_HAS_neg_i64          1
#define TCG_TARGET_HAS_not_i64          1

// Logicals.
#define TCG_TARGET_HAS_andc_i32         1
#define TCG_TARGET_HAS_orc_i32          1
#define TCG_TARGET_HAS_eqv_i32          1
#define TCG_TARGET_HAS_rot_i32          1
#define TCG_TARGET_HAS_nand_i32         1
#define TCG_TARGET_HAS_nor_i32          1
#define TCG_TARGET_HAS_andc_i64         1
#define TCG_TARGET_HAS_eqv_i64          1
#define TCG_TARGET_HAS_orc_i64          1
#define TCG_TARGET_HAS_rot_i64          1
#define TCG_TARGET_HAS_nor_i64          1
#define TCG_TARGET_HAS_nand_i64         1

// Bitwise operations.
#define TCG_TARGET_HAS_clz_i32          1
#define TCG_TARGET_HAS_ctz_i32          1
#define TCG_TARGET_HAS_clz_i64          1
#define TCG_TARGET_HAS_ctz_i64          1

// Swaps.
#define TCG_TARGET_HAS_bswap16_i32      1
#define TCG_TARGET_HAS_bswap32_i32      1
#define TCG_TARGET_HAS_bswap16_i64      1
#define TCG_TARGET_HAS_bswap32_i64      1
#define TCG_TARGET_HAS_bswap64_i64      1
#define TCG_TARGET_HAS_MEMORY_BSWAP     1

//
// Supported optional vector instructions.
//

#define TCG_TARGET_HAS_v64              1
#define TCG_TARGET_HAS_v128             1
#define TCG_TARGET_HAS_v256             0

#define TCG_TARGET_HAS_andc_vec         1
#define TCG_TARGET_HAS_orc_vec          1
#define TCG_TARGET_HAS_not_vec          1
#define TCG_TARGET_HAS_neg_vec          1
#define TCG_TARGET_HAS_abs_vec          1
#define TCG_TARGET_HAS_roti_vec         0
#define TCG_TARGET_HAS_rots_vec         0
#define TCG_TARGET_HAS_rotv_vec         0
#define TCG_TARGET_HAS_shi_vec          0
#define TCG_TARGET_HAS_shs_vec          0
#define TCG_TARGET_HAS_shv_vec          1
#define TCG_TARGET_HAS_mul_vec          1
#define TCG_TARGET_HAS_sat_vec          1
#define TCG_TARGET_HAS_minmax_vec       1
#define TCG_TARGET_HAS_bitsel_vec       1
#define TCG_TARGET_HAS_cmpsel_vec       0

//
// Unsupported instructions.
//

// There's no direct instruction with which to count the number of ones,
// so we'll leave this implemented as other instructions.
#define TCG_TARGET_HAS_ctpop_i32        0
#define TCG_TARGET_HAS_ctpop_i64        0

// We don't currently support gadgets with more than three arguments,
// so we can't yet create movcond, deposit, or extract gadgets.
#define TCG_TARGET_HAS_movcond_i32      0
#define TCG_TARGET_HAS_movcond_i64      0
#define TCG_TARGET_HAS_deposit_i32      0
#define TCG_TARGET_HAS_deposit_i64      0
#define TCG_TARGET_HAS_extract_i32      0
#define TCG_TARGET_HAS_sextract_i32     0
#define TCG_TARGET_HAS_extract_i64      0
#define TCG_TARGET_HAS_sextract_i64     0

// GOTO_PTR is too complex to emit a simple gadget for, since it can
// target either interpreted code or our non-existent epilogue.
#define TCG_TARGET_HAS_goto_ptr         0

// This operation exists specifically to allow us to provide differing register
// constraints for 8-bit loads and stores. We don't need to do so, so we'll leave
// this unimplemented, as we gain nothing by it.
#define TCG_TARGET_HAS_qemu_st8_i32     0

// These should always be zero on our 64B platform.
#define TCG_TARGET_HAS_muls2_i64        0
#define TCG_TARGET_HAS_add2_i32         0
#define TCG_TARGET_HAS_sub2_i32         0
#define TCG_TARGET_HAS_mulu2_i32        0
#define TCG_TARGET_HAS_add2_i64         0
#define TCG_TARGET_HAS_sub2_i64         0
#define TCG_TARGET_HAS_mulu2_i64        0
#define TCG_TARGET_HAS_muluh_i64        0
#define TCG_TARGET_HAS_mulsh_i64        0
#define TCG_TARGET_HAS_extract2_i32     0
#define TCG_TARGET_HAS_muls2_i32        0
#define TCG_TARGET_HAS_muluh_i32        0
#define TCG_TARGET_HAS_mulsh_i32        0
#define TCG_TARGET_HAS_extract2_i64     0

//
// Platform metadata.
//

// Number of registers available.
#define TCG_TARGET_NB_REGS 64

// Number of general purpose registers.
#define TCG_TARGET_GP_REGS 16

/* List of registers which are used by TCG. */
typedef enum {

    // General purpose registers.
    // Note that we name every _host_ register here; but don't 
    // necessarily use them; that's determined by the allocation order
    // and the number of registers setting above. These just give us the ability
    // to refer to these by name.
    TCG_REG_R0, TCG_REG_R1, TCG_REG_R2, TCG_REG_R3,
    TCG_REG_R4, TCG_REG_R5, TCG_REG_R6, TCG_REG_R7,
    TCG_REG_R8, TCG_REG_R9, TCG_REG_R10, TCG_REG_R11,
    TCG_REG_R12, TCG_REG_R13, TCG_REG_R14, TCG_REG_R15,
    TCG_REG_R16, TCG_REG_R17, TCG_REG_R18, TCG_REG_R19,
    TCG_REG_R20, TCG_REG_R21, TCG_REG_R22, TCG_REG_R23,
    TCG_REG_R24, TCG_REG_R25, TCG_REG_R26, TCG_REG_R27,
    TCG_REG_R28, TCG_REG_R29, TCG_REG_R30, TCG_REG_R31,

    // Register aliases.
    TCG_AREG0             = TCG_REG_R14,
    TCG_REG_CALL_STACK    = TCG_REG_R15,

    // Mask that refers to the GP registers.
    TCG_MASK_GP_REGISTERS = 0xFFFFul, 

    // Vector registers.
    TCG_REG_V0 = 32, TCG_REG_V1, TCG_REG_V2, TCG_REG_V3,
    TCG_REG_V4, TCG_REG_V5, TCG_REG_V6, TCG_REG_V7,
    TCG_REG_V8, TCG_REG_V9, TCG_REG_V10, TCG_REG_V11,
    TCG_REG_V12, TCG_REG_V13, TCG_REG_V14, TCG_REG_V15,
    TCG_REG_V16, TCG_REG_V17, TCG_REG_V18, TCG_REG_V19,
    TCG_REG_V20, TCG_REG_V21, TCG_REG_V22, TCG_REG_V23,
    TCG_REG_V24, TCG_REG_V25, TCG_REG_V26, TCG_REG_V27,
    TCG_REG_V28, TCG_REG_V29, TCG_REG_V30, TCG_REG_V31,

    // Mask that refers to the vector registers.
    TCG_MASK_VECTOR_REGISTERS = 0xFFFF000000000000ul, 

} TCGReg;

// Specify the shape of the stack our runtime will use.
#define TCG_TARGET_CALL_STACK_OFFSET    0
#define TCG_TARGET_STACK_ALIGN          16

// We're interpreted, so we'll use our own code to run TB_EXEC.
#define HAVE_TCG_QEMU_TB_EXEC

// We'll need to enforce memory ordering with barriers.
#define TCG_TARGET_DEFAULT_MO  (0)

void tci_disas(uint8_t opc);

void tb_target_set_jmp_target(uintptr_t, uintptr_t, uintptr_t, uintptr_t);


#endif /* TCG_TARGET_H */
