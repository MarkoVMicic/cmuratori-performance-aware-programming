#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hw2.h"

enum op_code GetOpCode(const char Byte)
{
    enum op_code Check;
    // Check first 4 bits
    Check = ((Byte >> 4) & 0b00001111);
    if(Check == MOV_IMMEDIATE_TO_REGISTER) // 0b1011 w r r r
    {
        return Check;
    }

    // Check first 6 bits
    Check = ((Byte >> 2) & 0b00111111);
    if(Check == MOV_REGISTER_MEMORY_TO_FROM_REGISTER) // 0b100010 d w
    {
        return Check;
    }

    // Check first 7 bits
    Check = ((Byte >> 1) & 0b01111111);
    if(Check == MOV_IMMEDIATE_TO_REGISTER_MEMORY) // 0b1100011 w
    {
        return Check;
    }
    if(Check == MOV_MEMORY_TO_ACCUMULATOR) // 0b1010000 w
    {
        return Check;
    }
    if(Check == MOV_ACCUMULATOR_TO_MEMORY) // 0b1010001 w
    {
        return Check;
    }

    // Check entire byte
    // TODO
    return 0;
}

struct m_string *CreateEmptyMString()
{
    struct m_string *Result = malloc( (sizeof *Result) );
    Result->Length = 0;
    Result->Allocated = 0;
    Result->Contents = malloc( M_STRING_CREATION_SIZE );
    if(Result->Contents)
    {
        Result->Allocated = M_STRING_CREATION_SIZE;
    }

    return Result;
}


void AppendConstCStringToMStringWithGrow(const char *CString, struct m_string *MString)
{
    while(*CString)
    {
        if(MString->Length >= MString->Allocated)
        {
            while(MString->Length >= MString->Allocated)
            {
                MString->Allocated *= 2;
            }
            MString->Contents = realloc(MString->Contents, MString->Allocated);
        }
        MString->Contents[MString->Length] = *CString;
        MString->Length++;
        CString++;
    }
}

enum mod_field GetMovInstructionModField(const char Byte)
{
    return ((Byte >> 6) & 0b00000011);
}

int GetMovRegField(const char Byte)
{
    return ((Byte >> 3) & 0b00000111);
}

int GetMovRMField(const char Byte)
{
    return (Byte & 0b00000111);
}

void DecodeNonWideRegisterToRegisterMov( enum reg_field_encoding_non_wide Dest, enum reg_field_encoding_non_wide Source, struct m_string *OutputMString)
{
    switch(Dest)
    {
        case REG_AL:
        {
            AppendConstCStringToMStringWithGrow("al, ", OutputMString);
        } break;
        case REG_CL:
        {
            AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
        } break;
        case REG_DL:
        {
            AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
        } break;
        case REG_BL:
        {
            AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
        } break;
        case REG_AH:
        {
            AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
        } break;
        case REG_CH:
        {
            AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
        } break;
        case REG_DH:
        {
            AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
        } break;
        case REG_BH:
        {
            AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
        } break;
    }
    switch(Source)
    {
        case REG_AL:
        {
            AppendConstCStringToMStringWithGrow("al\n", OutputMString);
        } break;
        case REG_CL:
        {
            AppendConstCStringToMStringWithGrow("cl\n", OutputMString);
        } break;
        case REG_DL:
        {
            AppendConstCStringToMStringWithGrow("dl\n", OutputMString);
        } break;
        case REG_BL:
        {
            AppendConstCStringToMStringWithGrow("bl\n", OutputMString);
        } break;
        case REG_AH:
        {
            AppendConstCStringToMStringWithGrow("ah\n", OutputMString);
        } break;
        case REG_CH:
        {
            AppendConstCStringToMStringWithGrow("ch\n", OutputMString);
        } break;
        case REG_DH:
        {
            AppendConstCStringToMStringWithGrow("dh\n", OutputMString);
        } break;
        case REG_BH:
        {
            AppendConstCStringToMStringWithGrow("bh\n", OutputMString);
        } break;
    }
}


void DecodeWideRegisterToRegisterMov( enum reg_field_encoding_wide Dest, enum reg_field_encoding_wide Source, struct m_string *OutputMString)
{
    switch(Dest)
    {
        case REG_AX:
        {
            AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
        } break;
        case REG_CX:
        {
            AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
        } break;
        case REG_DX:
        {
            AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
        } break;
        case REG_BX:
        {
            AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
        } break;
        case REG_SP:
        {
            AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
        } break;
        case REG_BP:
        {
            AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
        } break;
        case REG_SI:
        {
            AppendConstCStringToMStringWithGrow("si, ", OutputMString);
        } break;
        case REG_DI:
        {
            AppendConstCStringToMStringWithGrow("di, ", OutputMString);
        } break;
    }
    switch(Source)
    {
        case REG_AX:
        {
            AppendConstCStringToMStringWithGrow("ax\n", OutputMString);
        } break;
        case REG_CX:
        {
            AppendConstCStringToMStringWithGrow("cx\n", OutputMString);
        } break;
        case REG_DX:
        {
            AppendConstCStringToMStringWithGrow("dx\n", OutputMString);
        } break;
        case REG_BX:
        {
            AppendConstCStringToMStringWithGrow("bx\n", OutputMString);
        } break;
        case REG_SP:
        {
            AppendConstCStringToMStringWithGrow("sp\n", OutputMString);
        } break;
        case REG_BP:
        {
            AppendConstCStringToMStringWithGrow("bp\n", OutputMString);
        } break;
        case REG_SI:
        {
            AppendConstCStringToMStringWithGrow("si\n", OutputMString);
        } break;
        case REG_DI:
        {
            AppendConstCStringToMStringWithGrow("di\n", OutputMString);
        } break;
    }
}


void DecodeRegisterToRegisterMove( int D, int W, int Reg, int RM, struct m_string *OutputMString )
{
    if(W == 0)
    {
        enum reg_field_encoding_non_wide Source;
        enum reg_field_encoding_non_wide Dest;
        if(D == 0)
        {
            // non_wide, reg = source
            Source = Reg;
            Dest   = RM;            
        }
        else // D == 1
        {
            // non_wide, reg = dest
            Dest   = Reg;
            Source = RM;
        }
        DecodeNonWideRegisterToRegisterMov(Dest, Source, OutputMString);
    }
    else // W == 1
    {
        enum reg_field_encoding_wide Source;
        enum reg_field_encoding_wide Dest;
        if(D == 0)
        {
            // wide, reg = source
            Source = Reg;
            Dest   = RM;            
        }
        else // D == 1
        {
            // wide, reg = dest
            Dest   = Reg;
            Source = RM;
        }
        DecodeWideRegisterToRegisterMov(Dest, Source, OutputMString);
    }
}


void DecodeNonWideImmediateToRegisterMov(int8_t Data, int Reg, struct m_string *OutputMString)
{
    enum reg_field_encoding_non_wide Dest = Reg;
    switch(Dest)
    {
        case REG_AL:
        {
            AppendConstCStringToMStringWithGrow("al, ", OutputMString);
        } break;
        case REG_CL:
        {
            AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
        } break;
        case REG_DL:
        {
            AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
        } break;
        case REG_BL:
        {
            AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
        } break;
        case REG_AH:
        {
            AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
        } break;
        case REG_CH:
        {
            AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
        } break;
        case REG_DH:
        {
            AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
        } break;
        case REG_BH:
        {
            AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
        } break;        
    }

    // Create the data string from the 8-bit int:
    char DataString[8]; // Largest possible is 5 bytes e.g. ['-','1','2','3','\0']
    snprintf(DataString, 8, "%d", Data);
    AppendConstCStringToMStringWithGrow(DataString, OutputMString);
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}

void DecodeWideImmediateToRegisterMov(int16_t Data, int Reg, struct m_string *OutputMString)
{
    enum reg_field_encoding_wide Dest = Reg;
    switch(Dest)
    {
        case REG_AX:
        {
            AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
        } break;
        case REG_CX:
        {
            AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
        } break;
        case REG_DX:
        {
            AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
        } break;
        case REG_BX:
        {
            AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
        } break;
        case REG_SP:
        {
            AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
        } break;
        case REG_BP:
        {
            AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
        } break;
        case REG_SI:
        {
            AppendConstCStringToMStringWithGrow("si, ", OutputMString);
        } break;
        case REG_DI:
        {
            AppendConstCStringToMStringWithGrow("di, ", OutputMString);
        } break;
    }
    char DataString[8]; // Largest possible is 7 bytes e.g. ['-','3','2','7','6','8','\0']
    snprintf(DataString, 8, "%d", Data);
    AppendConstCStringToMStringWithGrow(DataString, OutputMString);
    AppendConstCStringToMStringWithGrow("\n", OutputMString);    
}

void DecodeNonWideRegisterMemoryMove(int D, int Reg, int RM, struct m_string *OutputMString)
{
    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_non_wide Dest = Reg;
        enum effective_address_mem_mode Source = RM;
        switch(Dest)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al, ", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
            } break;        
        }
        switch(Source)
        {
            case BX_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bx + si]", OutputMString);
            } break;

            case BX_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bx + di]", OutputMString);
            } break;

            case BP_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bp + si]", OutputMString);
            } break;  

            case BP_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bp + di]", OutputMString);
            } break;  

            case SI:
            {
                AppendConstCStringToMStringWithGrow("[si]", OutputMString);
            } break;   

            case DI:
            {
                AppendConstCStringToMStringWithGrow("[di]", OutputMString);
            } break;   

            case DIRECT_ADDRESS:
            {
                printf("Shouldn't see this\n");

            } break; 

            case BX:
            {
                AppendConstCStringToMStringWithGrow("[bx]", OutputMString);
            } break;   
        }

    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_non_wide Source = Reg;
        enum effective_address_mem_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bx + si], ", OutputMString);
            } break;

            case BX_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bx + di], ", OutputMString);
            } break;

            case BP_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bp + si], ", OutputMString);
            } break;  

            case BP_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bp + di], ", OutputMString);
            } break;  

            case SI:
            {
                AppendConstCStringToMStringWithGrow("[si], ", OutputMString);
            } break;   

            case DI:
            {
                AppendConstCStringToMStringWithGrow("[di], ", OutputMString);
            } break;   

            case DIRECT_ADDRESS:
            {
                printf("Shouldn't see this\n");

            } break; 

            case BX:
            {
                AppendConstCStringToMStringWithGrow("[bx], ", OutputMString);
            } break;   
        }
        switch(Source)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break;        
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}

void DecodeWideRegisterMemoryMove(int D, int Reg, int RM, struct m_string *OutputMString)
{
    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_wide Dest = Reg;
        enum effective_address_mem_mode Source = RM;
        switch(Dest)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax, ", OutputMString);

            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx, ", OutputMString);

            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx, ", OutputMString);

            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx, ", OutputMString);

            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp, ", OutputMString);

            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp, ", OutputMString);

            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si, ", OutputMString);

            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di, ", OutputMString);

            } break;
        }
        switch(Source)
        {
            case BX_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bx + si]", OutputMString);
            } break;

            case BX_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bx + di]", OutputMString);
            } break;

            case BP_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bp + si]", OutputMString);
            } break;  

            case BP_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bp + di]", OutputMString);
            } break;  

            case SI:
            {
                AppendConstCStringToMStringWithGrow("[si]", OutputMString);
            } break;   

            case DI:
            {
                AppendConstCStringToMStringWithGrow("[di]", OutputMString);
            } break;   

            case DIRECT_ADDRESS:
            {
                printf("Shouldn't see this\n");

            } break; 

            case BX:
            {
                AppendConstCStringToMStringWithGrow("[bx]", OutputMString);
            } break;
        }
    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_wide Source = Reg;
        enum effective_address_mem_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bx + si], ", OutputMString);
            } break;

            case BX_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bx + di], ", OutputMString);
            } break;

            case BP_PLUS_SI:
            {
                AppendConstCStringToMStringWithGrow("[bp + si], ", OutputMString);
            } break;  

            case BP_PLUS_DI:
            {
                AppendConstCStringToMStringWithGrow("[bp + di], ", OutputMString);
            } break;  

            case SI:
            {
                AppendConstCStringToMStringWithGrow("[si], ", OutputMString);
            } break;   

            case DI:
            {
                AppendConstCStringToMStringWithGrow("[di], ", OutputMString);
            } break;   

            case DIRECT_ADDRESS:
            {
                printf("Shouldn't see this\n");

            } break; 

            case BX:
            {
                AppendConstCStringToMStringWithGrow("[bx], ", OutputMString);
            } break;
        }
        switch(Source)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax", OutputMString);

            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx", OutputMString);

            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx", OutputMString);

            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx", OutputMString);

            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp", OutputMString);

            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp", OutputMString);

            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si", OutputMString);

            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di", OutputMString);

            } break;
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}

void DecodeRegisterMemoryMove(int D, int W, int Reg, int RM, struct m_string *OutputMString)
{
    if(W == 0)
    {
        DecodeNonWideRegisterMemoryMove(D, Reg, RM, OutputMString);
    }
    else // W == 1
    {
        DecodeWideRegisterMemoryMove(D, Reg, RM, OutputMString);
    }
}

void DecodeRegisterMemoryDirectAddressNonWideMove(int D, int Reg, int16_t MemoryAddress, struct m_string *OutputMString)
{
    char MemoryAddressString[8]; 
    snprintf(MemoryAddressString, 8, "%d", MemoryAddress);

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_non_wide Dest = Reg;
        switch(Dest)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al, ", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
            } break;        
        }
        AppendConstCStringToMStringWithGrow("[", OutputMString);
        AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        AppendConstCStringToMStringWithGrow("[", OutputMString);
        AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        enum reg_field_encoding_non_wide Dest = Reg;
        switch(Dest)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break;        
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}



void DecodeRegisterMemoryDirectAddressWideMove(int D, int Reg, int16_t MemoryAddress, struct m_string *OutputMString)
{
    char MemoryAddressString[8]; 
    snprintf(MemoryAddressString, 8, "%d", MemoryAddress);

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_wide Dest = Reg;
        switch(Dest)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si, ", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di, ", OutputMString);
            } break;        
        }
        AppendConstCStringToMStringWithGrow("[", OutputMString);
        AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        AppendConstCStringToMStringWithGrow("[", OutputMString);
        AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        enum reg_field_encoding_wide Dest = Reg;
        switch(Dest)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di", OutputMString);
            } break;        
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeRegisterMemoryDirectAddressMove(int D, int W, int Reg, int16_t MemoryAddress, struct m_string *OutputMString)
{
    if(W == 0)
    {
        DecodeRegisterMemoryDirectAddressNonWideMove(D, Reg, MemoryAddress, OutputMString);
    }
    else // W == 1
    {
        DecodeRegisterMemoryDirectAddressWideMove(D, Reg, MemoryAddress, OutputMString);        
    }
}


void DecodeNonWideRegisterMemoryMove8(int D, int Reg, int RM, int8_t Displacement, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        // Remove the minus sign from the beginning of the number
        // by negating the negative number.
        // Switch it back immediately afterward so we know which 
        // sign to print. 
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }
    if(!Displacement)
    {
        // Don't put anything if the displacement is 0
        DisplacementString[0] = '\0';
    }

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_non_wide Dest = Reg;
        enum effective_address_mem_8_mode Source = RM;
        switch(Dest)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al, ", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
            } break; 
        }
        switch(Source)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_non_wide Source = Reg;
        enum effective_address_mem_8_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        switch(Source)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break; 
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeWideRegisterMemoryMove8(int D, int Reg, int RM, int8_t Displacement, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        // Remove the minus sign from the beginning of the number
        // by negating the negative number.
        // Switch it back immediately afterward so we know which 
        // sign to print. 
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_wide Dest = Reg;
        enum effective_address_mem_8_mode Source = RM;
        switch(Dest)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si, ", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di, ", OutputMString);
            } break; 
        }
        switch(Source)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_wide Source = Reg;
        enum effective_address_mem_8_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si + ", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di + ", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si + ", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di + ", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si + ", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di + ", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + ", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + ", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        switch(Source)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di", OutputMString);
            } break; 
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}

void DecodeRegisterMemoryMove8(int D, int W, int Reg, int RM, int8_t Displacement, struct m_string *OutputMString)
{
    if(W == 0)
    {
        DecodeNonWideRegisterMemoryMove8(D, Reg, RM, Displacement, OutputMString);
    }
    else // W == 1
    {
        DecodeWideRegisterMemoryMove8(D, Reg, RM, Displacement, OutputMString);        
    }
}


void DecodeNonWideRegisterMemoryMove16(int D, int Reg, int RM, int16_t Displacement, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        // Remove the minus sign from the beginning of the number
        // by negating the negative number.
        // Switch it back immediately afterward so we know which 
        // sign to print. 
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_non_wide Dest = Reg;
        enum effective_address_mem_8_mode Source = RM;
        switch(Dest)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("al, ", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
            } break; 
        }
        switch(Source)
        {
            case BX_PLUS_SI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D16:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        // TODO(Marko): Is it a problem if this is signed? Hmmm... Maybe displacement should be signed?
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_non_wide Source = Reg;
        enum effective_address_mem_8_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        switch(Source)
        {
            case REG_AL:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CL:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DL:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BL:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break;
            case REG_AH:
            {
                AppendConstCStringToMStringWithGrow("ah", OutputMString);
            } break;
            case REG_CH:
            {
                AppendConstCStringToMStringWithGrow("ch", OutputMString);
            } break;
            case REG_DH:
            {
                AppendConstCStringToMStringWithGrow("dh", OutputMString);
            } break;
            case REG_BH:
            {
                AppendConstCStringToMStringWithGrow("bh", OutputMString);
            } break; 
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeWideRegisterMemoryMove16(int D, int Reg, int RM, int16_t Displacement, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        // Remove the minus sign from the beginning of the number
        // by negating the negative number.
        // Switch it back immediately afterward so we know which 
        // sign to print. 
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }

    if(D == 1)
    {
        // Dest = Reg
        enum reg_field_encoding_wide Dest = Reg;
        enum effective_address_mem_8_mode Source = RM;
        switch(Dest)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si, ", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di, ", OutputMString);
            } break; 
        }
        switch(Source)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("]", OutputMString);
    }
    else // D == 0
    {
        // Source = Reg
        enum reg_field_encoding_wide Source = Reg;
        enum effective_address_mem_8_mode Dest = RM;
        switch(Dest)
        {
            case BX_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

            } break;
            case BX_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

            } break;
            case BP_PLUS_SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

            } break;
            case BP_PLUS_DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

            } break;
            case SI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[si", OutputMString);

            } break;
            case DI_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[di", OutputMString);

            } break;
            case BP_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bp", OutputMString);

            } break;
            case BX_PLUS_D8:
            {
                AppendConstCStringToMStringWithGrow("[bx", OutputMString);

            } break;
        }
        if(Displacement)
        {
            if(Displacement > 0)
            {
                AppendConstCStringToMStringWithGrow(" + ", OutputMString);
            }
            else // Displacement < 0
            {
                AppendConstCStringToMStringWithGrow(" - ", OutputMString);
            }
            AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
        }
        AppendConstCStringToMStringWithGrow("], ", OutputMString);
        switch(Source)
        {
            case REG_AX:
            {
                AppendConstCStringToMStringWithGrow("ax", OutputMString);
            } break;
            case REG_CX:
            {
                AppendConstCStringToMStringWithGrow("cx", OutputMString);
            } break;
            case REG_DX:
            {
                AppendConstCStringToMStringWithGrow("dx", OutputMString);
            } break;
            case REG_BX:
            {
                AppendConstCStringToMStringWithGrow("bx", OutputMString);
            } break;
            case REG_SP:
            {
                AppendConstCStringToMStringWithGrow("sp", OutputMString);
            } break;
            case REG_BP:
            {
                AppendConstCStringToMStringWithGrow("bp", OutputMString);
            } break;
            case REG_SI:
            {
                AppendConstCStringToMStringWithGrow("si", OutputMString);
            } break;
            case REG_DI:
            {
                AppendConstCStringToMStringWithGrow("di", OutputMString);
            } break; 
        }
    }
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeRegisterMemoryMove16(int D, int W, int Reg, int RM, int16_t Displacement, struct m_string *OutputMString)
{
    if(W == 0)
    {
        DecodeNonWideRegisterMemoryMove16(D, Reg, RM, Displacement, OutputMString);
    }
    else // W == 1
    {
        DecodeWideRegisterMemoryMove16(D, Reg, RM, Displacement, OutputMString);        
    }
}


void DecodeImmediateToRegisterMemoryMov(int W, enum effective_address_mem_mode RM, int16_t MemoryAddress, struct m_string *OutputMString)
{
    switch(RM)
    {
        case BX_PLUS_SI:
        {
            AppendConstCStringToMStringWithGrow("[bx + si], ", OutputMString);
        } break;

        case BX_PLUS_DI:
        {
            AppendConstCStringToMStringWithGrow("[bx + di], ", OutputMString);
        } break;

        case BP_PLUS_SI:
        {
            AppendConstCStringToMStringWithGrow("[bp + si], ", OutputMString);
        } break;  

        case BP_PLUS_DI:
        {
            AppendConstCStringToMStringWithGrow("[bp + di], ", OutputMString);
        } break;  

        case SI:
        {
            AppendConstCStringToMStringWithGrow("[si], ", OutputMString);
        } break;   

        case DI:
        {
            AppendConstCStringToMStringWithGrow("[di], ", OutputMString);
        } break;   

        case DIRECT_ADDRESS:
        {
            printf("Shouldn't see this\n");

        } break; 

        case BX:
        {
            AppendConstCStringToMStringWithGrow("[bx], ", OutputMString);
        } break;   
    }
    if(W == 0)
    {
        AppendConstCStringToMStringWithGrow("byte ", OutputMString);
    }
    else // W == 1
    {
        AppendConstCStringToMStringWithGrow("word ", OutputMString);
    }
    char MemoryAddressString[8];
    snprintf(MemoryAddressString, 8, "%d", MemoryAddress);
    AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeImmediateToRegisterMemoryMov8(int W, enum effective_address_mem_8_mode RM, int16_t Displacement, int16_t MemoryAddress, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else if(Displacement > 0)
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }
    else // Displacement == 0
    {
        DisplacementString[0] = '\0';
    }
    switch(RM)
    {
        case BX_PLUS_SI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

        } break;
        case BX_PLUS_DI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

        } break;
        case BP_PLUS_SI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

        } break;
        case BP_PLUS_DI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

        } break;
        case SI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[si", OutputMString);

        } break;
        case DI_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[di", OutputMString);

        } break;
        case BP_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bp", OutputMString);

        } break;
        case BX_PLUS_D8:
        {
            AppendConstCStringToMStringWithGrow("[bx", OutputMString);

        } break;
    }

    if(Displacement != 0)
    {
        if(Displacement < 0)
        {
            AppendConstCStringToMStringWithGrow(" - ", OutputMString);
        }
        else // Displacement > 0
        {
            AppendConstCStringToMStringWithGrow(" + ", OutputMString);
        }
        AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
    }
    AppendConstCStringToMStringWithGrow("], ", OutputMString);

    if(W == 0)
    {
        AppendConstCStringToMStringWithGrow("byte ", OutputMString);
    }
    else // W == 1
    {
        AppendConstCStringToMStringWithGrow("word ", OutputMString);
    }
    char MemoryAddressString[8];
    snprintf(MemoryAddressString, 8, "%d", MemoryAddress);
    AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}


void DecodeImmediateToRegisterMemoryMov16(int W, enum effective_address_mem_16_mode RM, int16_t Displacement, int16_t MemoryAddress, struct m_string *OutputMString)
{
    char DisplacementString[8];
    if(Displacement < 0)
    {
        Displacement = -Displacement;
        snprintf(DisplacementString, 8, "%d", Displacement);
        Displacement = -Displacement;
    }
    else if(Displacement > 0)
    {
        snprintf(DisplacementString, 8, "%d", Displacement);
    }
    else // Displacement == 0
    {
        DisplacementString[0] = '\0';
    }

    switch(RM)
    {
        case BX_PLUS_SI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bx + si", OutputMString);

        } break;
        case BX_PLUS_DI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bx + di", OutputMString);

        } break;
        case BP_PLUS_SI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bp + si", OutputMString);

        } break;
        case BP_PLUS_DI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bp + di", OutputMString);

        } break;
        case SI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[si", OutputMString);

        } break;
        case DI_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[di", OutputMString);

        } break;
        case BP_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bp", OutputMString);

        } break;
        case BX_PLUS_D16:
        {
            AppendConstCStringToMStringWithGrow("[bx", OutputMString);

        } break;
    }

    if(Displacement != 0)
    {
        if(Displacement < 0)
        {
            AppendConstCStringToMStringWithGrow(" - ", OutputMString);
        }
        else // Displacement > 0
        {
            AppendConstCStringToMStringWithGrow(" + ", OutputMString);
        }
        AppendConstCStringToMStringWithGrow(DisplacementString, OutputMString);
    }
    AppendConstCStringToMStringWithGrow("], ", OutputMString);

    if(W == 0)
    {
        AppendConstCStringToMStringWithGrow("byte ", OutputMString);
    }
    else // W == 1
    {
        AppendConstCStringToMStringWithGrow("word ", OutputMString);
    }
    char MemoryAddressString[8];
    snprintf(MemoryAddressString, 8, "%d", MemoryAddress);
    AppendConstCStringToMStringWithGrow(MemoryAddressString, OutputMString);
    AppendConstCStringToMStringWithGrow("\n", OutputMString);
}



int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Usage: hw1.exe [binary file path] [output file path]\n");
        return(1);
    }

    char *BinaryFilePath = argv[1];
    char *OutputFilePath = argv[2];

    struct m_string *OutputMString = CreateEmptyMString();
    AppendConstCStringToMStringWithGrow("bits 16\n\n", OutputMString);

    FILE *BinaryFileHandle = fopen(BinaryFilePath, "r");
    if(BinaryFileHandle)
    {
        int FGetCResult;
        while( (FGetCResult = fgetc(BinaryFileHandle)) != EOF) 
        {
            char CurrentByte = (unsigned char)FGetCResult;
            enum op_code OpCode = GetOpCode(CurrentByte);
            switch(OpCode)
            {
                case MOV_REGISTER_MEMORY_TO_FROM_REGISTER:
                {
                    AppendConstCStringToMStringWithGrow("mov ", OutputMString);
                    int D = (CurrentByte >> 1) & 0b00000001;
                    int W = CurrentByte & 0b00000001;
                    // Advance to second byte of mov instruction
                    FGetCResult = fgetc(BinaryFileHandle);
                    CurrentByte = (char)FGetCResult;
                    enum mod_field Mod = GetMovInstructionModField( CurrentByte );
                    int Reg = GetMovRegField( CurrentByte );
                    int RM = GetMovRMField( CurrentByte );
                    switch(Mod)
                    {
                        case REG_MODE:
                        {
                            // Only 2 bytes total involved in register-to-register mov
                            DecodeRegisterToRegisterMove( D, W, Reg, RM, OutputMString );
                        } break;

                        case MEM_MODE:
                        {
                            if((enum effective_address_mem_mode)RM == DIRECT_ADDRESS)
                            {
                                // Direct Memory Address is encoded in the next two bytes.                                
                                int16_t MemoryAddress = 0;
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= (CurrentByte << 8);                                
                                DecodeRegisterMemoryDirectAddressMove(D, W, Reg, MemoryAddress, OutputMString);
                            }
                            else
                            {
                                // Only two bytes total involved in reg-mem with no displacement.
                                DecodeRegisterMemoryMove( D, W, Reg, RM, OutputMString );  
                            }

                        } break;

                        case MEM_MODE_8:
                        {
                            // 8-bit displacement comes in the next byte. 
                            int8_t Displacement = 0;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement = (int8_t)CurrentByte;
                            DecodeRegisterMemoryMove8( D, W, Reg, RM, Displacement, OutputMString );
                        } break;

                        case MEM_MODE_16:
                        {
                            // 16-bit displacement comes in the next two bytes. 
                            int16_t Displacement = 0;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement |= (int8_t)CurrentByte;
                            Displacement &= 0x00FF;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement |= (CurrentByte << 8);                            
                            DecodeRegisterMemoryMove16( D, W, Reg, RM, Displacement, OutputMString );
                        } break;
                    }
                } break;

                case MOV_IMMEDIATE_TO_REGISTER:
                {                    
                    AppendConstCStringToMStringWithGrow("mov ", OutputMString);
                    int W = (CurrentByte >> 3) & 0b00000001;
                    int Reg = CurrentByte & 0b00000111;
                    if(W == 0)
                    {
                        // Data is the next byte
                        FGetCResult = fgetc(BinaryFileHandle);
                        CurrentByte = (char)FGetCResult;
                        int8_t Data = (int8_t)CurrentByte;
                        DecodeNonWideImmediateToRegisterMov(Data, Reg, OutputMString);
                    }
                    else // W == 1
                    {
                        // Data is next two bytes, arranged low-high
                        int16_t Data = 0;
                        FGetCResult = fgetc(BinaryFileHandle);
                        CurrentByte = (char)FGetCResult;
                        Data |= CurrentByte;
                        Data &= 0x00FF; // Clear high bits in case 1 propagates from bitshift. 
                        FGetCResult = fgetc(BinaryFileHandle);
                        CurrentByte = (char)FGetCResult;
                        Data |= (CurrentByte << 8);
                        DecodeWideImmediateToRegisterMov(Data, Reg, OutputMString);
                    }

                } break;

                case MOV_IMMEDIATE_TO_REGISTER_MEMORY:
                {
                    AppendConstCStringToMStringWithGrow("mov ", OutputMString);
                    int W = CurrentByte & 0b00000001;
                    FGetCResult = fgetc(BinaryFileHandle);
                    CurrentByte = (char)FGetCResult;
                    enum mod_field Mod = (CurrentByte >> 6) & 0b00000011;
                    int RM = CurrentByte & 0b00000111;

                    switch(Mod)
                    {
                        case MEM_MODE:
                        {
                            // No displacement
                            int16_t MemoryAddress = 0;
                            if(W == 1)
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= (CurrentByte << 8);
                            }
                            else // W == 0
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                            }
                            DecodeImmediateToRegisterMemoryMov(W, RM, MemoryAddress, OutputMString);
                        } break;

                        case MEM_MODE_8:
                        {
                            // 8-bit Displacement, sign-extended to 16 bits
                            int8_t Displacement8 = 0;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement8 = (int8_t)CurrentByte;
                            int16_t Displacement16 = (int16_t)Displacement8;

                            int16_t MemoryAddress = 0;
                            if(W == 1)
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= (CurrentByte << 8);
                            }
                            else // W == 0
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                            }
                            DecodeImmediateToRegisterMemoryMov8(W, RM, Displacement16, MemoryAddress, OutputMString);                            

                        } break;

                        case MEM_MODE_16:
                        {
                            // 16-bit Displacement
                            int16_t Displacement16 = 0;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement16 |= CurrentByte;
                            Displacement16 &= 0x00FF;
                            FGetCResult = fgetc(BinaryFileHandle);
                            CurrentByte = (char)FGetCResult;
                            Displacement16 |= (CurrentByte << 8);

                            int16_t MemoryAddress = 0;
                            if(W == 1)
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= (CurrentByte << 8);
                            }
                            else // W == 0
                            {
                                FGetCResult = fgetc(BinaryFileHandle);
                                CurrentByte = (char)FGetCResult;
                                MemoryAddress |= CurrentByte;
                                MemoryAddress &= 0x00FF;
                            }
                            DecodeImmediateToRegisterMemoryMov16(W, RM, Displacement16, MemoryAddress, OutputMString);                            

                        } break;

                    }

                } break;

                case MOV_MEMORY_TO_ACCUMULATOR:
                {
                    int W = CurrentByte & 0b00000001;
                    if(W == 1)
                    {
                        
                    }
                    else // W == 0
                    {
                        
                    }

                } break;

                default:
                {
                    printf("Unknown Op Code.\n");          
                }
            }

        }
        fclose(BinaryFileHandle);
    }
    else
    {
        printf("File in location %s failed to open.\n", BinaryFilePath);
        return(1);
    }

    // Finalize the string by null-terminating it. 
    OutputMString->Contents[OutputMString->Length] = '\0';

    // Write to file
    FILE *OutputFileHandle = fopen(OutputFilePath, "w");
    if(OutputFileHandle)
    {
        fputs(OutputMString->Contents, OutputFileHandle);
        fclose(OutputFileHandle);
    }

    return(0);
}