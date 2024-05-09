#ifndef MENUS_H
#define MENUS_H

#include <iostream>

//#define HOST_LINUX

#ifndef HOST_LINUX
#define HOST_WINDOWS
#endif // !HOST_LINUX

namespace ZaPe {
	namespace Menus
	{
        enum class MainMenuInputType
        {
            KILEP = 0,
            NORMAL = 1,
            OSSZES_TESZT = 2,
            INTEGER = 3,
            CSTRING = 4,
            TESTCLASS = 5,
            UNDEFINED
        };

		void ClearConsole();
		void PrintMainMenuMessage();
        void PrintNormalModMenu();

        void MainMenu(int argc, char** argv);

        int TestInput(const std::string& input, int maxValue);
	}
}


#endif