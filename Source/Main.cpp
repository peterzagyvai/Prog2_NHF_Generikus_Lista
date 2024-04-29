#include <iostream>
#include <string>
#include <cstring>

#include "Tests.h"
#include "List.hpp"
#include "TestClass.h"

#include "memtrace.h"


#define HOST_WINDOWS

//#define HOST_LINUX



std::string projectDir = "E:\\School\\VI_Semester\\Prog2\\HW\\Prog2_NHF_Generikus_Lista\\";

void ClearConsole()
{
#ifdef HOST_WINDOWS
    system("cls");
#endif // HOST_WINDOWS
#ifdef HOST_LINUX
    system("clear");
#endif
}

void PrintMainMenuMessage()
{
    std::cout << "Fomenu" << std::endl;
    std::cout << "1.) Szamok beolvasasa es kiirasa (Nem teszt)" << std::endl;
    std::cout << "2.) Minden teszt futtatasa" << std::endl;
    std::cout << "3.) Integerek-en teszt" << std::endl;
    std::cout << "4.) C-Stringen teszt" << std::endl;
    std::cout << "5.) TestClass-on teszt" << std::endl;
    std::cout << "0.) Kilep" << std::endl;
}

enum class InputType
{
    KILEP = 0,
    NORMAL = 1,
    OSSZES_TESZT = 2,
    INTEGER = 3,
    CSTRING = 4,
    TESTCLASS = 5,
    UNDEFINED
};

namespace ZaPe {
    void NormalMode()
    {

    }
}

int main()
{
#ifdef HOST_WINDOWS
#ifdef HOST_LINUX
    // CANT'T DEFINE BOTH...
    std::cerr << "Nem lehet ketto op. rendszer..." << std::endl;
    return 1;
#endif // HOST_LINUX
#endif // HOST_WINDOWS



    std::string input;
    InputType inputValue;
    do {
        inputValue = InputType::UNDEFINED;
        // Print Main menu
        PrintMainMenuMessage();
        
        // Get input
        std::getline(std::cin, input);
        
        // Test input
        if (input.size() != 1)
        {
            ClearConsole();
            std::cerr << "A bemenet nem megfelelo" << std::endl << std::endl;;
            continue;
        }

        if (!isdigit(input.c_str()[0]))
        {
            ClearConsole();
            std::cerr << "A bemenet nem megfelelo" << std::endl << std::endl;;
            continue;
        }

        int inputInt = atoi(input.c_str());

        if (inputInt > 5)
        {
            ClearConsole();
            std::cerr << "A bemenet nem megfelelo" << std::endl << std::endl;;
            continue;
        }

        inputValue = static_cast<InputType>(inputInt);

        //Init for testing
        ZaPe::InitGtest();

        switch (inputValue)
        {
        case InputType::KILEP:
            break;
        case InputType::NORMAL:
            
            break;
        case InputType::OSSZES_TESZT:
            ZaPe::TestAll();
            break;
        case InputType::INTEGER:
            ZaPe::TestInt();
            break;
        case InputType::CSTRING:
            ZaPe::TestCString();
            break;
        case InputType::TESTCLASS:
            ZaPe::TestOnClass();
            break;
        case InputType::UNDEFINED:
            ClearConsole();
            std::cerr << "Something went wrong with the input" << std::endl;
            break;
        default:
            ClearConsole();
            std::cerr << "Something really went wrong with the input" << std::endl;
            break;
        }

    } while (inputValue != InputType::KILEP);

    return 0;
}