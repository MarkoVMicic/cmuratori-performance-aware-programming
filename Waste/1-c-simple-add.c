int __declspec(noinline) add(int A, int B) // Do not inline this function
{
    return A + B;
}

#pragma optimize("", off) // Disable optimizations 
int main(int ArgCount, char **Args)
{
    return add(1234, 6578);
}

// Corresponding assembly:
/*
int __declspec(noinline) add(int A, int B) // Do not inline this function
{
000000013F796C20  mov         dword ptr [B],edx  
000000013F796C24  mov         dword ptr [A],ecx  
    return A + B;
000000013F796C28  mov         eax,dword ptr [B]  
000000013F796C2C  mov         ecx,dword ptr [A]  
000000013F796C30  add         ecx,eax  
000000013F796C32  mov         eax,ecx  
}
000000013F796C34  ret  
*/