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
    for(  u32 Index = 0; Index < Count; ++Index)
    {
        Sum += Input[Index];
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
    printf("Cycles Elapsed: %d\n", MinCyclesElapsed);
    printf("Cycles/Add: %f\n", CyclesPerAdd);
    printf("Adds/Cycle: %f\n", AddsPerCycle);

    return 0;
}

/*
Cycles Elapsed: 42109
Cycles/Add:     10
Adds/Cycle:     0.1
*/