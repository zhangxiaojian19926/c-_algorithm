#include "serialNetTools.h"

/**
 * serialNetTools 类的构造函数
 */
serialNetTools::serialNetTools()
{
    std::cout << "Hello world!" << std::endl;
}

/**
* 析构函数 ~serialNetTools()
*/
serialNetTools::~serialNetTools()
{
    std::cout << "de!" << std::endl;
}

int serialNetTools::add(const int &a, const int &b)
{
    return a + b;
}
