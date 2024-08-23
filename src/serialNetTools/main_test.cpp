#include <iostream>
#include "serialNetTools.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello world!" << std::endl;
    serialNetTools sn;
    std::cout << sn.add(1, 2) << std::endl;
    return 0;
}