int __declspec(noinline) add(int A, int B) // Do not inline this function
{
    return A + B;
}

#pragma optimize("", off) // Disable optimizations 
int main(int ArgCount, char **Args)
{
    return add(1234, 6578);
}
