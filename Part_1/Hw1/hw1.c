#include <stdio.h>
#include <stdlib.h>
#include "hw1.h"

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
    // TODO

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
        case AL:
        {
            AppendConstCStringToMStringWithGrow("al, ", OutputMString);
        } break;
        case CL:
        {
            AppendConstCStringToMStringWithGrow("cl, ", OutputMString);
        } break;
        case DL:
        {
            AppendConstCStringToMStringWithGrow("dl, ", OutputMString);
        } break;
        case BL:
        {
            AppendConstCStringToMStringWithGrow("bl, ", OutputMString);
        } break;
        case AH:
        {
            AppendConstCStringToMStringWithGrow("ah, ", OutputMString);
        } break;
        case CH:
        {
            AppendConstCStringToMStringWithGrow("ch, ", OutputMString);
        } break;
        case DH:
        {
            AppendConstCStringToMStringWithGrow("dh, ", OutputMString);
        } break;
        case BH:
        {
            AppendConstCStringToMStringWithGrow("bh, ", OutputMString);
        } break;
    }
    switch(Source)
    {
        case AL:
        {
            AppendConstCStringToMStringWithGrow("al\n", OutputMString);
        } break;
        case CL:
        {
            AppendConstCStringToMStringWithGrow("cl\n", OutputMString);
        } break;
        case DL:
        {
            AppendConstCStringToMStringWithGrow("dl\n", OutputMString);
        } break;
        case BL:
        {
            AppendConstCStringToMStringWithGrow("bl\n", OutputMString);
        } break;
        case AH:
        {
            AppendConstCStringToMStringWithGrow("ah\n", OutputMString);
        } break;
        case CH:
        {
            AppendConstCStringToMStringWithGrow("ch\n", OutputMString);
        } break;
        case DH:
        {
            AppendConstCStringToMStringWithGrow("dh\n", OutputMString);
        } break;
        case BH:
        {
            AppendConstCStringToMStringWithGrow("bh\n", OutputMString);
        } break;
    }
}

void DecodeWideRegisterToRegisterMov( enum reg_field_encoding_wide Dest, enum reg_field_encoding_wide Source, struct m_string *OutputMString)
{
    switch(Dest)
    {
        case AX:
        {
            AppendConstCStringToMStringWithGrow("ax, ", OutputMString);
        } break;
        case CX:
        {
            AppendConstCStringToMStringWithGrow("cx, ", OutputMString);
        } break;
        case DX:
        {
            AppendConstCStringToMStringWithGrow("dx, ", OutputMString);
        } break;
        case BX:
        {
            AppendConstCStringToMStringWithGrow("bx, ", OutputMString);
        } break;
        case SP:
        {
            AppendConstCStringToMStringWithGrow("sp, ", OutputMString);
        } break;
        case BP:
        {
            AppendConstCStringToMStringWithGrow("bp, ", OutputMString);
        } break;
        case SI:
        {
            AppendConstCStringToMStringWithGrow("si, ", OutputMString);
        } break;
        case DI:
        {
            AppendConstCStringToMStringWithGrow("di, ", OutputMString);
        } break;
    }
    switch(Source)
    {
        case AX:
        {
            AppendConstCStringToMStringWithGrow("ax\n", OutputMString);
        } break;
        case CX:
        {
            AppendConstCStringToMStringWithGrow("cx\n", OutputMString);
        } break;
        case DX:
        {
            AppendConstCStringToMStringWithGrow("dx\n", OutputMString);
        } break;
        case BX:
        {
            AppendConstCStringToMStringWithGrow("bx\n", OutputMString);
        } break;
        case SP:
        {
            AppendConstCStringToMStringWithGrow("sp\n", OutputMString);
        } break;
        case BP:
        {
            AppendConstCStringToMStringWithGrow("bp\n", OutputMString);
        } break;
        case SI:
        {
            AppendConstCStringToMStringWithGrow("si\n", OutputMString);
        } break;
        case DI:
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
                            // Only 2 bytes involved in register-to-register mov
                            DecodeRegisterToRegisterMove( D, W, Reg, RM, OutputMString );
                        } break;

                        case MEM_MODE:
                        {

                        } break;

                        case MEM_MODE_8:
                        {

                        } break;

                        case MEM_MODE_16:
                        {

                        } break;
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