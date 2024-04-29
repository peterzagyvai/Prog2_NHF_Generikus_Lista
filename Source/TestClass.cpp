#include "TestClass.h"
#include <cstring>
#include <iostream>
#include <fstream>

void ZaPe::TestClass::write(const char* filePath) const
{
    size_t size = 0;
    TestClass* tcArray = NULL;
    bool fileExists = true;
    try
    {
        size = TestClass::read(filePath);
        tcArray = new TestClass[size];
        TestClass::read(filePath, tcArray);
    }
    catch (std::out_of_range e)
    {
        delete[] tcArray;
        if (strcmp(e.what(), "Unable to open file") != 0) // Létezik a fájl, de mégis hibát dob
        {
            std::cout << e.what() << std::endl;
        }
        else // Ha nem létezik a fájl
        {
            fileExists = false;
        }
    }

    if (fileExists)
    {
        if (std::remove(filePath) != 0);
    }

    size++;
    std::ofstream file(filePath);

    if (file.is_open())
    {
        file << size << "\n";
        for (size_t i = 0; i < size - 1; i++)
        {
            file << tcArray[i].get_number() << " " << (tcArray[i].get_boolean() ? "true" : "false") << "\n";
        }
        file << number << " " << (boolean ? "true" : "false") << "\n";
    }

    if (tcArray != NULL) delete[] tcArray;
}

size_t ZaPe::TestClass::read(const char* filePath, TestClass* tcArray)
{
    std::ifstream file(filePath);
    size_t counter = 0;

    if (file.is_open())
    {
        file >> counter;

        if (counter < 1)
        {
            file.close();
            throw std::out_of_range("File is not in the correct format or counter is smaller than 0");
        }

        if (tcArray == NULL)
        {
            file.close();
            return counter;
        }

        for (size_t i = 0; i < counter; i++)
        {
            int number;
            bool boolean;

            file >> number >> std::boolalpha >> boolean;

            tcArray[i].set_number(number);
            tcArray[i].set_boolean(boolean);
        }
    }
    else throw std::out_of_range("Unable to open file");


    return counter;
}


namespace ZaPe
{
    bool Compare::TestSortFunctor::operator()(const TestClass& tc1, const TestClass& tc2)
    {
        return tc1.get_number() < tc2.get_number();
    }

    bool Compare::TestEqualFunctor::operator()(const TestClass& tc1, const TestClass& tc2)
    {
        return (tc1.get_number() == tc2.get_number() && tc1.get_boolean() == tc2.get_boolean());
    }
}
