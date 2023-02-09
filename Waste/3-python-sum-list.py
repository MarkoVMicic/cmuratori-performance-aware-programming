import time
import sys

def SingleScalar(Count, Input):
    Sum = 0
    for Index in range(Count):
        Sum += Input[Index]
    return Sum

# NOTE: Everything below here is a testing harness. Notably, this is 
#       extracting the *best possible case* out of all attempts. 
# NOTE: Python doesn't natively support getting CPU cycle counts or clock 
#       speed, so we manually specify the clock speed here. Remember to set 
#       this appropriately for your own personal computer. 
CPUgHz = 2.2

print("Python: ", sys.version)
print("User-supplied clock frequency: ", CPUgHz, "gHz")

TryCount = 100000
MinCyclesElapsed = sys.maxsize
MinTimeNanoSeconds = sys.maxsize

Count = 4096
Input = [x for x in range(Count)]
for _ in range(TryCount):

    BeginTime = time.perf_counter_ns()
    ActualSum = SingleScalar(Count, Input)
    EndTime = time.perf_counter_ns()
    CyclesElapsed = (EndTime - BeginTime) * CPUgHz
    if CyclesElapsed < MinCyclesElapsed:
        MinTimeNanoSeconds = EndTime - BeginTime
        MinCyclesElapsed = CyclesElapsed

print()
print("Count: ", Count)
print("Sum: ", ActualSum)
print("Time: ", MinTimeNanoSeconds," nanoseconds")
print("Cycles: ", MinCyclesElapsed)
print("Cycles/Add: ", MinCyclesElapsed/Count, " cycles/add")
print("Adds/Cycle: ", Count/MinCyclesElapsed, " adds/cycle")

"""
Count:          4096
Sum:            8386560         
Time:           239785 nanoseconds
Cycles:         527527 cycles
Cycles/Add:     128.790771484375 cycles per ADD
Adds/Cycle:     0.007764531483696569 ADDs per cycle
"""