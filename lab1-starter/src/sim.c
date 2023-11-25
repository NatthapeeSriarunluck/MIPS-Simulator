#include <stdio.h>
#include "shell.h"

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    /*IMPLEMENT THIS*/

    uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
    NEXT_STATE.PC += CURRENT_STATE.PC + 4;
    uint32_t opcode = instruction >> 26;
    uint32_t rs = (instruction >> 21) & 0x1F;
    uint32_t rt = (instruction >> 16) & 0x1F;
    uint32_t rd = (instruction >> 11) & 0x1F;
    uint32_t sa = (instruction >> 6) & 0x1F;
    uint32_t funct = instruction & 0x3F;
    uint32_t immediate = instruction & 0xFFFF;
    uint32_t address = instruction & 0x3FFFFFF;
    uint32_t temp;

    switch (opcode)
    {
    case 0x0: // Special Type
        switch (funct)
        {
        case 0x0: // sll
            printf("sll\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x2: // srl
            printf("srl\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;

        case 0x3: // sra
            printf("sra\n");
            NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x4: // sllv
            printf("sllv\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x5: // srav
            printf("srav\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x8: // jr
            printf("jr\n");
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
            break;
        case 0x9: // jalr
            printf("jalr\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
            break;
        case 0x20: // add
            printf("add\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x21: // addu
            printf("addu\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x22: // sub
            printf("sub\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x23: // subu
            printf("subu\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x24: // and
            printf("and\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x25: // or
            printf("or\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x26: // xor
            printf("xor\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x27: // nor
            printf("nor\n");
            NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x2A: // slt
            printf("slt\n");
            if (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt])
            {
                NEXT_STATE.REGS[rd] = 1;
            }
            else
            {
                NEXT_STATE.REGS[rd] = 0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x2B: // sltu
            printf("sltu\n");
            if (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt])
            {
                NEXT_STATE.REGS[rd] = 1;
            }
            else
            {
                NEXT_STATE.REGS[rd] = 0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x18: // mult
            printf("mult\n");
            int64_t result = (int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt];
            NEXT_STATE.HI = result >> 32;
            NEXT_STATE.LO = result & 0xFFFFFFFF;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x19: // multu
            printf("multu\n");
            uint64_t result = (uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt];
            NEXT_STATE.HI = result >> 32;
            NEXT_STATE.LO = result & 0xFFFFFFFF;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x10: // mfhi
            printf("mfhi\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x12: // mflo
            printf("mflo\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x11: // mthi
            printf("mthi\n");
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x13: // mtlo
            printf("mtlo\n");
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x1A: // div
            printf("div\n");
            int32_t dividend = (int32_t)CURRENT_STATE.REGS[rs];
            int32_t divisor = (int32_t)CURRENT_STATE.REGS[rt];
            NEXT_STATE.LO = dividend / divisor;
            NEXT_STATE.HI = dividend % divisor;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        case 0x1B: // divu
            printf("divu\n");
            uint32_t dividend = CURRENT_STATE.REGS[rs];
            uint32_t divisor = CURRENT_STATE.REGS[rt];
            NEXT_STATE.LO = dividend / divisor;
            NEXT_STATE.HI = dividend % divisor;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            break;
        // case 0xC: // syscall
        //     NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        //     break;
        default:
            break;
        }
        break;
    case 0x02: // j
        printf("j\n");
        NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | (address << 2);
        break;
    case 0x03: // jal
        printf("jal\n");
        NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | (address << 2);
        break;
    case 0x04: // beq
        printf("beq\n");
        if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt])
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (immediate << 2);
        }
        else
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        break;
    case 0x05: // bne
        printf("bne\n");
        if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt])
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (immediate << 2);
        }
        else
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        break;
    case 0x06: // blez
        printf("blez\n");
        if (CURRENT_STATE.REGS[rs] <= 0)
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (immediate << 2);
        }
        else
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        break;
    case 0x07: // bgtz
        printf("bgtz\n");
        if (CURRENT_STATE.REGS[rs] > 0)
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (immediate << 2);
        }
        else
        {
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        break;
    case 0x08: // addi
        printf("addi\n");
        NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rs] + (int32_t)immediate;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x09: // addiu
        printf("addiu\n");
        NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rs] + immediate;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x10: // slti
        printf("slti\n");
        if (CURRENT_STATE.REGS[rs] < immediate)
        {
            NEXT_STATE.REGS[rt] = 1;
        }
        else
        {
            NEXT_STATE.REGS[rt] = 0;
        }
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x11: // sltiu
        printf("sltiu\n");
        if (CURRENT_STATE.REGS[rs] < immediate)
        {
            NEXT_STATE.REGS[rt] = 1;
        }
        else
        {
            NEXT_STATE.REGS[rt] = 0;
        }
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x0C: // andi
        printf("andi\n");
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & immediate;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x0D: // ori
        printf("ori\n");
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | immediate;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x0E: // xori
        printf("xori\n");
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ immediate;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    case 0x0F: // lui
        printf("lui\n");
        NEXT_STATE.REGS[rt] = immediate << 16;
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        break;
    // case 0x20: // lb
    //     printf("lb\n");
    //     temp = mem_read_32(CURRENT_STATE.REGS[rs] + immediate);
    //     NEXT_STATE.REGS[rt] = (int8_t)temp;
    //     NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    //     break;
    case 0x21: // lh
        printf("lh\n");
        temp = mem_read_32(CURRENT_STATE.REGS[rs] + immediate);
        NEXT_STATE.REGS[rt] = (int16_t)temp;

    case 0x23: // lw
        printf("lw\n");
        NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate);

    case 0x24: // lbu
        printf("lbu\n");
        NEXT_STATE.REGS[rt] = 0xFF & mem_read_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate);

    case 0x25: // lhu
        printf("lhu\n");
        NEXT_STATE.REGS[rt] = 0xFFFF & mem_read_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate);

    case 0x28: // sb
        printf("sb\n");
        mem_write_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate, CURRENT_STATE.REGS[rt] & 0xFF);

    case 0x29: // sh
        printf("sh\n");
        mem_write_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate, CURRENT_STATE.REGS[rt] & 0xFFFF);

    case 0x2B: // sw
        printf("sw\n");
        mem_write_32(CURRENT_STATE.REGS[rs] + (int32_t)immediate, CURRENT_STATE.REGS[rt]);

    case 0x1:
        switch (rt)
        {
        case 0x0: // bltz
            printf("bltz\n");
            if ((int32_t)CURRENT_STATE.REGS[rs] < 0)
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (int32_t)(immediate << 2);
            }
            else
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
            break;
        case 0x1: // bgez
            printf("bgez\n");
            if ((int32_t)CURRENT_STATE.REGS[rs] >= 0)
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (int32_t)(immediate << 2);
            }
            else
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
            break;
        case 0x10: // bltzal
            printf("bltzal\n");
            if ((int32_t)CURRENT_STATE.REGS[rs] < 0)
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4 + ((int32_t)immediate << 2);
            }
            else
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
            break;
        case 0x11: // bgezal
            printf("bgezal\n");
            if ((int32_t)CURRENT_STATE.REGS[rs] >= 0)
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (immediate << 2);
            }
            else
            {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}
