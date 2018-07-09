//
//  Scene.hpp
//  MultipleLights_Ex01
//
//  Created by shenyuanluo on 2018/4/21.
//  Copyright © 2018年 shenyuanluo. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>


/* 场景类型 枚举 */
typedef enum _sceneType{
    Scene_desert            = 0,        // 沙漠
    Scene_factory           = 1,        // 工厂
    Scene_horror            = 2,        // 惊悚
    Scene_biochemicalLab    = 3,        // 生化实验室
}SceneType;


class Scene
{
private:
    
public:
    Scene();
    
    ~Scene();
    
    glm::vec3 dirLightDirection(SceneType sType);
    
    glm::vec3 dirLightAmbient(SceneType sType);
    
    glm::vec3 dirLightDiffuse(SceneType sType);
    
    glm::vec3 dirLightSpecular(SceneType sType);
    
    
    glm::vec3* pointLightPosition(SceneType sType);
    
    GLfloat* pointLightConstant(SceneType sType);
    
    GLfloat* pointLightLinear(SceneType sType);
    
    GLfloat* pointLightQuadratic(SceneType sType);
    
    glm::vec3 pointLightAmbient(SceneType sType);
    
    glm::vec3 pointLightDiffuse(SceneType sType);
    
    glm::vec3 pointLightSpecular(SceneType sType);
    
    glm::vec3* pointLightColor(SceneType sType);
    
    
    GLfloat spotLightCutOff(SceneType sType);
    
    GLfloat spotLightOuterCutOff(SceneType sType);
    
    GLfloat spotLightConstant(SceneType sType);
    
    GLfloat spotLightLinear(SceneType sType);
    
    GLfloat spotLightQuadratic(SceneType sType);
    
    glm::vec3 spotLightAmbient(SceneType sType);
    
    glm::vec3 spotLightDiffuse(SceneType sType);
    
    glm::vec3 spotLightSpecular(SceneType sType);
    
    glm::vec4 bgClearColor(SceneType sType);
    
};

#endif /* Scene_hpp */
