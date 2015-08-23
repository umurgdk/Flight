#include "TestDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int main(int argc, char *argv[])
{
    TestDelegate app{argc, argv};
    return Application::getInstance()->run();
}