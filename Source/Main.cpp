#include "Menus.h"

#include "memtrace.h"

int main(int argc, char** argv)
{
#ifdef HOST_WINDOWS
#ifdef HOST_LINUX
    // CANT'T DEFINE BOTH...
    std::cerr << "Nem lehet ketto op. rendszer..." << std::endl;
    return 1;
#endif // HOST_LINUX
#endif // HOST_WINDOWS

    ZaPe::Menus::MainMenu(argc, argv);

    return 0;
}