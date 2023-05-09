#include <windows.h>
#include <intrin.h>

typedef unsigned int u32;
typedef unsigned long long int u64;

#pragma optimize("", off) // Disable optimizations 
// Do not inline this function
u32 __declspec(noinline) SingleScalar(  u32 Count,   u32 *Input) 
{
    u32 Sum = 0;
    #pragma loop( no_vector )
    for(u32 Index = 0; Index < Count; ++Index)
    {
        Sum += Input[Index];
    }
    return Sum;
}

u32 __declspec(noinline) Unroll2Scalar(u32 Count, u32 *Input)
{
    u32 Sum = 0;
    #pragma loop( no_vector )
    for(u32 Index = 0; Index < Count; Index += 2)
    {
        Sum += Input[Index];
        Sum += Input[Index + 1];
    }

    return Sum;
}

u32 __declspec(noinline) Unroll4Scalar(u32 Count, u32 *Input)
{
    u32 Sum = 0;
    #pragma loop( no_vector )
    for(u32 Index = 0; Index < Count; Index += 4)
    {
        Sum += Input[Index];
        Sum += Input[Index + 1];
        Sum += Input[Index + 2];
        Sum += Input[Index + 3];
    }

    return Sum;
}


int main(int ArgsCount, char **Args)
{
    u32 Count = 4096;
    u32 Input[4096];
    for(u32 Index = 0; Index < Count; ++Index)
    {
        Input[Index] = Index;
    }

    u32 TryCount = 100000;
    u64 MinCyclesElapsed = INT_MAX;
    u64 BeginCycles;
    u64 EndCycles;
    u64 CyclesElapsed;
    u32 Result;

    for(u32 Try = 0; Try < TryCount; ++Try)
    {
        // QueryPerformanceCounter(&BeginCycles);
        BeginCycles = __rdtsc();
        SingleScalar(Count, Input);    
        EndCycles = __rdtsc();

        CyclesElapsed = EndCycles - BeginCycles;
        if(CyclesElapsed < MinCyclesElapsed)
        {
            MinCyclesElapsed = CyclesElapsed;
        }
    }
    double CyclesPerAdd = MinCyclesElapsed / Count;
    double AddsPerCycle = 1/CyclesPerAdd;
    printf("Simple loop:\n");
    printf("\tCycles Elapsed: %d\n", MinCyclesElapsed);
    printf("\tCycles/Add: %f\n", CyclesPerAdd);
    printf("\tAdds/Cycle: %f\n", AddsPerCycle);


    MinCyclesElapsed = INT_MAX;
    for(u32 Try = 0; Try < TryCount; ++Try)
    {
        // QueryPerformanceCounter(&BeginCycles);
        BeginCycles = __rdtsc();
        Unroll2Scalar(Count, Input);    
        EndCycles = __rdtsc();

        CyclesElapsed = EndCycles - BeginCycles;
        if(CyclesElapsed < MinCyclesElapsed)
        {
            MinCyclesElapsed = CyclesElapsed;
        }
    }
    CyclesPerAdd = MinCyclesElapsed / Count;
    AddsPerCycle = 1/CyclesPerAdd;
    printf("Unrolled loop 2x:\n");
    printf("\tCycles Elapsed: %d\n", MinCyclesElapsed);
    printf("\tCycles/Add: %f\n", CyclesPerAdd);
    printf("\tAdds/Cycle: %f\n", AddsPerCycle);

    MinCyclesElapsed = INT_MAX;
    for(u32 Try = 0; Try < TryCount; ++Try)
    {
        // QueryPerformanceCounter(&BeginCycles);
        BeginCycles = __rdtsc();
        Unroll4Scalar(Count, Input);    
        EndCycles = __rdtsc();

        CyclesElapsed = EndCycles - BeginCycles;
        if(CyclesElapsed < MinCyclesElapsed)
        {
            MinCyclesElapsed = CyclesElapsed;
        }
    }
    CyclesPerAdd = MinCyclesElapsed / Count;
    AddsPerCycle = 1/CyclesPerAdd;
    printf("Unrolled loop 4x:\n");
    printf("\tCycles Elapsed: %d\n", MinCyclesElapsed);
    printf("\tCycles/Add: %f\n", CyclesPerAdd);
    printf("\tAdds/Cycle: %f\n", AddsPerCycle);

    return 0;
}

/*
Simple Loop:
    Cycles Elapsed: 42114
    Cycles/Add:     10
    Adds/Cycle:     0.1
Unrolled Loop 2x:
    Cycles Elapsed: 33224
    Cycles/Add:     8
    Adds/Cycle:     0.125
*/