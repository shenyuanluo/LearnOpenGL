//
//  GLErrorCheck.hpp
//  
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef GLErrorCheck_hpp
#define GLErrorCheck_hpp

#include <glad/glad.h>


#define glCheckError() glCheckError_(__FILE__, __LINE__)


/**
 检查 OpenGL 是否出错
 
 @param file 文件名
 @param line 行号
 @return 错误类型
 */
GLenum glCheckError_(const GLchar *file, GLint line);

#endif /* GLErrorCheck_hpp */
