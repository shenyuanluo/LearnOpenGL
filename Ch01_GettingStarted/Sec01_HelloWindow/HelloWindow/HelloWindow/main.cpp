//
//  main.cpp
//  HelloWindow
//
//  Created by shenyuanluo on 2017/8/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, (GLchar*)"Hello Window");
    
    window.render();
    
    return 0;
}
