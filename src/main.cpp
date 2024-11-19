#include <iostream>

#include "interface/interface.hpp"

int main()
{
    try
    {
        Interface::Initialize();
        Interface &interface = Interface::GetInstance();
        interface.Run();
        Interface::Shutdown();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
