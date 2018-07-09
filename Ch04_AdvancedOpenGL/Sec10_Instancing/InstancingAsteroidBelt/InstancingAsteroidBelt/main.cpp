//
//  main.cpp
//  InstancingAsteroidBelt
//
//  Created by shenyuanluo on 2017/9/9.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Instancing Asteroid Belt");
    
    window.setCWD(argv[0]);
    
    window.render();
    
    return 0;
}
