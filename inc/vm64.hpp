#ifndef VM64_HPP
#define VM64_HPP

#include <stdint.h>

/*
* System Specifications:
* * 64 MB of RAM
* * 64 registers
* * 64 bit instruction set
* * 640x480 resolution
* * 32 bit address space
*
* Register Layout:
*   __________________________________________________________________________________________________
*   |   8 bit   |   8 bit   |   8 bit   |   8 bit   |   8 bit   |   8 bit   |   8 bit   |   8 bit   |
*   |------------------------------------------------------------------------------------------------
*   |        16 bit         |        16 bit         |        16 bit         |        16 bit         |
*   |------------------------------------------------------------------------------------------------
*   |                     32 bit                    |                     32 bit                    |
*   |------------------------------------------------------------------------------------------------
*   |                                             64 bit                                            |
*   |------------------------------------------------------------------------------------------------
*
* Boot sequence:
* * On startup, the VM reads the first 512 bytes from the hard disk into the ram and starts executing
* * The bootloader must have the signature "__VM64__"
* 
*
*/

enum DISPLAY
{
    WIDTH  = 640,
    HEIGHT = 480
};

enum { RAM_SIZE = 64 * 1024 * 1024 };
enum { BOOT_LOADER_OFFSET = 0, BOOT_LOADER_SIZE = 512 };

enum OPCODE
{
    OP_NOP    = 0x01,
    OP_READ   = 0x02,
    OP_WRITE  = 0x03,
    OP_MOV    = 0x04,
    OP_ADD    = 0x05,
    OP_SUB    = 0x06,
    OP_MUL    = 0x07,
    OP_DIV    = 0x08,
    OP_JMP    = 0x09,
    OP_MAX    = 0xFF
};

enum ADDRESS_MODE
{
    ADDRESS_DIRECT   = 1,
    ADDRESS_INDIRECT = 2
};

enum OPERAND_TYPE
{
    OPERAND_REGISTER = 1,
    OPERAND_CONSTANT = 2
};

struct NOP
{
    struct
    {
        uint8_t  opcode; 
        uint8_t  reserved0;
        uint16_t reserved1;
        uint16_t reserved2;
    } header;
};

struct READ
{
    struct
    {
        uint8_t  opcode;
        uint16_t dst_reg;
        uint8_t  addr_mode;
        uint32_t reserved;
    } header;

    struct
    {
        uint32_t address;
        uint32_t reserved;
    } data;
};

struct WRITE
{
    struct
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t src_reg;
        uint8_t  addr_mode;
        uint8_t  reserved1;
    } header;

    struct
    {
        uint32_t address;
        uint32_t reserved;
    } data;
};

struct MOV
{
    struct
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t reg_src;
        uint16_t reg_dst;
        uint16_t reserved1;
    } header;
};

struct ADD
{
    struct header
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t reg_dst;
        uint8_t  type_op1;
        uint8_t  type_op2;
        uint16_t reserved1;
    } header;

    struct
    {
        uint64_t op;
    } data1;

    struct
    {
        uint64_t op;
    } data2;
};

struct SUB
{
    struct header
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t reg_dst;
        uint8_t  type_op1;
        uint8_t  type_op2;
        uint16_t reserved1;
    } header;

    struct
    {
        uint64_t op;
    } data1;

    struct
    {
        uint64_t op;
    } data2;
};

struct MUL
{
    struct header
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t reg_dst;
        uint8_t  type_op1;
        uint8_t  type_op2;
        uint16_t reserved1;
    } header;

    struct
    {
        uint64_t op;
    } data1;

    struct
    {
        uint64_t op;
    } data2;
};

struct DIV
{
    struct header
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint16_t reg_dst;
        uint8_t  type_op1;
        uint8_t  type_op2;
        uint16_t reserved1;
    } header;

    struct
    {
        uint64_t op;
    } data1;

    struct
    {
        uint64_t op;
    } data2;
};

struct JMP
{
    struct
    {
        uint8_t  opcode;
        uint8_t  reserved0;
        uint8_t  addr_mode;
        uint8_t  reserved1;
        uint32_t reserved2;
    } header;

    struct
    {
        uint32_t address;
        uint64_t reserved;
    } data;
};

#endif // VM64_HPP
