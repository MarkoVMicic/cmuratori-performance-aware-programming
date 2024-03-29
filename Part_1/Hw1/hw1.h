#if !defined(HW1_H)

// ---------
// Constants
// ---------
#define M_STRING_CREATION_SIZE 128

// -------
// Structs
// -------
struct m_string
{
    int Length;
    int Allocated;
    char *Contents;
};

// -----
// enums
// -----
enum op_code
{
    MOV_REGISTER_MEMORY_TO_FROM_REGISTER = 0b100010,
    MOV_IMMEDIATE_TO_REGISTER            = 0b1011,
};

enum mod_field
{
    MEM_MODE    = 0b00,
    MEM_MODE_8  = 0b01,
    MEM_MODE_16 = 0b10,
    REG_MODE    = 0b11
};

enum effective_address_mem_mode
{
    // Mod == 00
    BX_PLUS_CI     = 0b000,
    BX_PLUS_DI     = 0b001,
    BP_PLUS_SI     = 0b010,
    BP_PLUS_DI     = 0b011,
    SI             = 0b100,
    DI             = 0b101,
    DIRECT_ADDRESS = 0b110,
    BX             = 0b111
};

enum effective_address_mem_8_mode
{
    // Mod == 01
    BX_PLUS_CI_PLUS_D8     = 0b000,
    BX_PLUS_DI_PLUS_D8     = 0b001,
    BP_PLUS_SI_PLUS_D8     = 0b010,
    BP_PLUS_DI_PLUS_D8     = 0b011,
    SI_PLUS_D8             = 0b100,
    DI_PLUS_D8             = 0b101,
    BP_PLUS_D8             = 0b110,
    BX_PLUS_D8             = 0b111    
};

enum effective_address_mem_16_mode
{
    // Mod == 10
    BX_PLUS_CI_PLUS_D16     = 0b000,
    BX_PLUS_DI_PLUS_D16     = 0b001,
    BP_PLUS_SI_PLUS_D16     = 0b010,
    BP_PLUS_DI_PLUS_D16     = 0b011,
    SI_PLUS_D16             = 0b100,
    DI_PLUS_D16             = 0b101,
    BP_PLUS_D16             = 0b110,
    BX_PLUS_D16             = 0b111  
};

enum reg_field_encoding_non_wide // W = 0
{
    AL = 0b000,
    CL = 0b001,
    DL = 0b010,
    BL = 0b011,
    AH = 0b100,
    CH = 0b101,
    DH = 0b110,
    BH = 0b111
};

enum reg_field_encoding_wide // W = 1
{
    AX = 0b000,
    CX = 0b001,
    DX = 0b010,
    BX = 0b011,
    SP = 0b100,
    BP = 0b101,
    SI = 0b110,
    DI = 0b111
};

#define HW1_H
#endif