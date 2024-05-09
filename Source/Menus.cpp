#include "Menus.h"
#include "Tests.h"
#include "NormalMode.h"

#include <string>
#include <iostream>

#include "memtrace.h"


namespace ZaPe
{
	namespace Menus
	{
		void ClearConsole()
		{
#ifdef HOST_WINDOWS
			system("cls");
#endif // HOST_WINDOWS
#ifdef HOST_LINUX
			system("clear");
#endif
		}

		int TestInput(const std::string& input, int maxValue)
		{
			// Test input
			if (input.size() != 1)
			{
				return -1;
			}

			if (!isdigit(input.c_str()[0]))
			{
				return -1;
			}

			int inputInt = atoi(input.c_str());

			if (inputInt > maxValue)
			{
				return -1;
			}

			return inputInt;
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

		void PrintNormalModMenu()
		{
            std::cout << "Normal mod" << std::endl;
            std::cout << "Az alabbi modban egy listaba lehet felvenni integer tipusu adatokat" << std::endl;
            std::cout << "Kilepeskor (Normalmodbol) a lista tartalma kiirodik egy fajlba, amit ujra beolvas egy masik listaba es a lista tartalma megjelenik a kepernyon" << std::endl;
            std::cout << "Kilepeshez a \"q\" karaktert kell begepelni" << std::endl;
		}

		void MainMenu()
		{
            std::string input;
            Menus::MainMenuInputType inputValue;

            do {
                inputValue = Menus::MainMenuInputType::UNDEFINED;

                // Print Main menu
                Menus::PrintMainMenuMessage();

                // Get input
				std::getline(std::cin, input);

                int inputInt = Menus::TestInput(input, 5);
                if (inputInt == -1)
                {
                    Menus::ClearConsole();
                    std::cerr << "Fomenu: A bemenet nem megfelelo" << std::endl << std::endl;
                    continue;
                }

                inputValue = static_cast<Menus::MainMenuInputType>(inputInt);

                //Init for testing
                ZaPe::InitGtest();

                switch (inputValue)
                {
                case Menus::MainMenuInputType::KILEP:
                    break;
                case Menus::MainMenuInputType::NORMAL:
					NormalMode::Run();
                    Menus::ClearConsole();
                    break;
                case Menus::MainMenuInputType::OSSZES_TESZT:
                    Menus::ClearConsole();
                    ZaPe::TestAll();
                    break;
                case Menus::MainMenuInputType::INTEGER:
                    Menus::ClearConsole();
                    ZaPe::TestInt();
                    break;
                case Menus::MainMenuInputType::CSTRING:
                    Menus::ClearConsole();
                    ZaPe::TestCString();
                    break;
                case Menus::MainMenuInputType::TESTCLASS:
                    Menus::ClearConsole();
                    ZaPe::TestOnClass();
                    break;
                case Menus::MainMenuInputType::UNDEFINED:
                    Menus::ClearConsole();
                    std::cerr << "Valami baj történt a bemenet kezelésével" << std::endl;
                    break;
                default:
                    Menus::ClearConsole();
                    std::cerr << "Valami nagy baj történt a bemenet kezelésével" << std::endl;
                    break;
                }

                if (inputInt >= 2 && inputInt <= 5)
                {
                    std::cout << "Vissza a fomenube: [ENTER]" << std::endl;
                    std::getline(std::cin, input);

                    Menus::ClearConsole();
                }

            } while (inputValue != Menus::MainMenuInputType::KILEP);
		}
	}
}