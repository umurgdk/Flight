#include "TestDelegate.h"

USING_NS_CC;

TestDelegate::TestDelegate(int argc, char* argv[]) {
    this->argc = argc;
    this->argv = argv;
}

TestDelegate::~TestDelegate()
{
}

void TestDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool TestDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Flight - Testing");
        director->setOpenGLView(glview);
    }
    
    // run the tests
    bandit::run(argc, argv);
    
    director->end();

    return true;
}

void TestDelegate::applicationDidEnterBackground() {}
void TestDelegate::applicationWillEnterForeground() {}
