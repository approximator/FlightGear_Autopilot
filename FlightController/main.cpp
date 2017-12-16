
#include <string>
#include <iostream>

// #include "flightgear/fgserver.h"

//fgfs --native-fdm=socket,out,10,127.0.0.1,50001,udp --console --geometry=1366x768 --timeofday=morning --disable-terrasync

int main(int /* argc */, char ** /* argv[] */)
{
    try
    {
        // boost::asio::io_service io_service;
        // FGServer server(io_service);
        // io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
