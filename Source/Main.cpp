#include <iostream>
#include "Tests.h"

using namespace ZaPe;

int main()
{
    #ifdef TEST_CASES
        ZaPe::Tests();
    #endif
    #ifndef TEST_CASES
    
    #endif


    return 0;
}