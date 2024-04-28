#include <iostream>
#include "Tests.h"
#include "List.hpp"

#include "memtrace.h"


std::string projectDir = "E:\\School\\VI_Semester\\Prog2\\HW\\Prog2_NHF_Generikus_Lista\\";

int main()
{
    //ZaPe::Tests();
    std::string filePath;
    std::string writeFilePath = projectDir + "Bin\\Write.txt";
    filePath += projectDir + "Bin\\Test.txt";
    filePath = writeFilePath;

    size_t size = 0;

    ZaPe::TestClass* tcArray = new ZaPe::TestClass[size = ZaPe::TestClass::read(filePath.c_str())];
    ZaPe::TestClass::read(filePath.c_str(), tcArray);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << tcArray[i].get_number() << ", " << tcArray[i].get_boolean() << std::endl;
    }

    delete[] tcArray;

    /*
    ZaPe::TestClass tc(14, false);
    tc.write(writeFilePath.c_str());
    */


    return 0;
}