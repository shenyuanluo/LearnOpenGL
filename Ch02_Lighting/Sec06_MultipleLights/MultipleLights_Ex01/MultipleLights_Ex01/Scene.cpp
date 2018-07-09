//
//  Scene.cpp
//  MultipleLights_Ex01
//
//  Created by shenyuanluo on 2018/4/21.
//  Copyright © 2018年 shenyuanluo. All rights reserved.
//

#include "Scene.hpp"

#pragma mark - Public
Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

glm::vec3 Scene::dirLightDirection(SceneType sType)
{
    glm::vec3 direction;
    switch (sType)
    {
        case Scene_desert:        direction = glm::vec3(-0.2f, -1.0f, -0.3f);  break;
        case Scene_factory:       direction = glm::vec3(-0.2f, -1.0f, -0.3f);  break;
        case Scene_horror:        direction = glm::vec3(-0.2f, -1.0f, -0.3f);  break;
        case Scene_biochemicalLab:direction = glm::vec3(-0.2f, -1.0f, -0.3f);  break;
        default:  break;
    }
    return direction;
}

glm::vec3 Scene::dirLightAmbient(SceneType sType)
{
    glm::vec3 ambient;
    switch (sType)
    {
        case Scene_desert:        ambient = glm::vec3(0.3f,  0.24f, 0.14f); break;
        case Scene_factory:       ambient = glm::vec3(0.05f, 0.05f, 0.1f);  break;
        case Scene_horror:        ambient = glm::vec3(0.0f,  0.0f,  0.0f);  break;
        case Scene_biochemicalLab:ambient = glm::vec3(0.5f,  0.5f,  0.5f);  break;
        default:  break;
    }
    return ambient;
}

glm::vec3 Scene::dirLightDiffuse(SceneType sType)
{
    glm::vec3 diffuse;
    switch (sType)
    {
        case Scene_desert:        diffuse = glm::vec3(0.7f,  0.42f, 0.26f); break;
        case Scene_factory:       diffuse = glm::vec3(0.2f,  0.2f,  0.7);   break;
        case Scene_horror:        diffuse = glm::vec3(0.05f, 0.05f, 0.05);  break;
        case Scene_biochemicalLab:diffuse = glm::vec3(1.0f,  1.0f,  1.0f);  break;
        default:  break;
    }
    return diffuse;
}

glm::vec3 Scene::dirLightSpecular(SceneType sType)
{
    glm::vec3 specular;
    switch (sType)
    {
        case Scene_desert:        specular = glm::vec3(0.5f, 0.5f, 0.5f);  break;
        case Scene_factory:       specular = glm::vec3(0.7f, 0.7f, 0.7f);  break;
        case Scene_horror:        specular = glm::vec3(0.2f, 0.2f, 0.2f);  break;
        case Scene_biochemicalLab:specular = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        default:  break;
    }
    return specular;
}

glm::vec3* Scene::pointLightPosition(SceneType sType)
{
    glm::vec3* position;
    glm::vec3 positions[] =
    {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    return position = positions;
}

GLfloat* Scene::pointLightConstant(SceneType sType)
{
    GLfloat* constant;
    switch (sType)
    {
        case Scene_desert:
        {
            GLfloat constants[] = {1.0f, 1.0f, 1.0f, 1.0f};
            constant = constants;
        }
            break;
        case Scene_factory:
        {
            GLfloat constants[] = {1.0f, 1.0f, 1.0f, 1.0f};
            constant = constants;
        }
            break;
        case Scene_horror:
        {
            GLfloat constants[] = {1.0f, 1.0f, 1.0f, 1.0f};
            constant = constants;
        }
            break;
        case Scene_biochemicalLab:
        {
            GLfloat constants[] = {1.0f, 1.0f, 1.0f, 1.0f};
            constant = constants;
        }
            break;
        default:  break;
    }
    return constant;
}

GLfloat* Scene::pointLightLinear(SceneType sType)
{
    GLfloat* linear;
    switch (sType)
    {
        case Scene_desert:
        {
            GLfloat lineas[] = {0.09f, 0.09f, 0.09f, 0.09f};
            linear = lineas;
        }
            break;
        case Scene_factory:
        {
            GLfloat lineas[] = {0.09f, 0.09f, 0.09f, 0.09f};
            linear = lineas;
        }
            break;
        case Scene_horror:
        {
            GLfloat lineas[] = {0.14f, 0.14f, 0.14f, 0.14f};
            linear = lineas;
        }
            break;
        case Scene_biochemicalLab:
        {
            GLfloat lineas[] = {0.07f, 0.07f, 0.07f, 0.07f};
            linear = lineas;
        }
            break;
        default:  break;
    }
    return linear;
}

GLfloat* Scene::pointLightQuadratic(SceneType sType)
{
    GLfloat* quadratic;
    switch (sType)
    {
        case Scene_desert:
        {
            GLfloat quadratics[] = {0.032f, 0.032f, 0.032f, 0.032f};
            quadratic = quadratics;
        }
            break;
        case Scene_factory:
        {
            GLfloat quadratics[] = {0.032f, 0.032f, 0.032f, 0.032f};
            quadratic = quadratics;
        }
            break;
        case Scene_horror:
        {
            GLfloat quadratics[] = {0.07f, 0.07f, 0.07f, 0.07f};
            quadratic = quadratics;
        }
            break;
        case Scene_biochemicalLab:
        {
            GLfloat quadratics[] = {0.017f, 0.017f, 0.017f, 0.017f};
            quadratic = quadratics;
        }
            break;
        default:  break;
    }
    return quadratic;
}

glm::vec3 Scene::pointLightAmbient(SceneType sType)
{
    glm::vec3 ambient;
    switch (sType)
    {
        case Scene_desert:        ambient = glm::vec3(0.5f, 0.5f, 0.5f);  break;
        case Scene_factory:       ambient = glm::vec3(0.7f, 0.7f, 0.7f);  break;
        case Scene_horror:        ambient = glm::vec3(0.2f, 0.2f, 0.2f);  break;
        case Scene_biochemicalLab:ambient = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        default:  break;
    }
    return ambient;
}

glm::vec3 Scene::pointLightDiffuse(SceneType sType)
{
    glm::vec3 diffuse;
    switch (sType)
    {
        case Scene_desert:        diffuse = glm::vec3(0.5f, 0.5f, 0.5f);  break;
        case Scene_factory:       diffuse = glm::vec3(0.7f, 0.7f, 0.7f);  break;
        case Scene_horror:        diffuse = glm::vec3(0.2f, 0.2f, 0.2f);  break;
        case Scene_biochemicalLab:diffuse = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        default:  break;
    }
    return diffuse;
}

glm::vec3 Scene::pointLightSpecular(SceneType sType)
{
    glm::vec3 specular;
    switch (sType)
    {
        case Scene_desert:        specular = glm::vec3(0.5f, 0.5f, 0.5f);  break;
        case Scene_factory:       specular = glm::vec3(0.7f, 0.7f, 0.7f);  break;
        case Scene_horror:        specular = glm::vec3(0.2f, 0.2f, 0.2f);  break;
        case Scene_biochemicalLab:specular = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        default:  break;
    }
    return specular;
}

glm::vec3* Scene::pointLightColor(SceneType sType)
{
    glm::vec3* color;
    switch (sType)
    {
        case Scene_desert:
        {
            glm::vec3 pointLightColors[] =
            {
                glm::vec3(1.0f, 0.6f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 0.0f),
                glm::vec3(0.2f, 0.2f, 1.0f)
            };
            color = pointLightColors;
        }
            break;
            
        case Scene_factory:
        {
            glm::vec3 pointLightColors[] =
            {
                glm::vec3(0.2f, 0.2f, 0.6f),
                glm::vec3(0.3f, 0.3f, 0.7f),
                glm::vec3(0.0f, 0.0f, 0.3f),
                glm::vec3(0.4f, 0.4f, 0.4f)
            };
            color = pointLightColors;
        }
            break;
            
        case Scene_horror:
        {
            glm::vec3 pointLightColors[] =
            {
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.3f, 0.1f, 0.1f)
            };
            color = pointLightColors;
        }
            break;
            
        case Scene_biochemicalLab:
        {
            glm::vec3 pointLightColors[] =
            {
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f)
            };
            color = pointLightColors;
        }
            break;
            
        default:
            break;
    }
    return color;
}

GLfloat Scene::spotLightCutOff(SceneType sType)
{
    GLfloat cutOff;
    switch (sType)
    {
        case Scene_desert:        cutOff = glm::cos(glm::radians(12.5f));  break;
        case Scene_factory:       cutOff = glm::cos(glm::radians(10.0f));  break;
        case Scene_horror:        cutOff = glm::cos(glm::radians(10.0f));  break;
        case Scene_biochemicalLab:cutOff = glm::cos(glm::radians(7.0f));   break;
        default:  break;
    }
    return cutOff;
}

GLfloat Scene::spotLightOuterCutOff(SceneType sType)
{
    GLfloat outerCutOff;
    switch (sType)
    {
        case Scene_desert:        outerCutOff = glm::cos(glm::radians(13.0f));  break;
        case Scene_factory:       outerCutOff = glm::cos(glm::radians(12.5f));  break;
        case Scene_horror:        outerCutOff = glm::cos(glm::radians(15.0f));  break;
        case Scene_biochemicalLab:outerCutOff = glm::cos(glm::radians(10.0f));  break;
        default:  break;
    }
    return outerCutOff;
}

GLfloat Scene::spotLightConstant(SceneType sType)
{
    GLfloat constant;
    switch (sType)
    {
        case Scene_desert:        constant = 1.0f;  break;
        case Scene_factory:       constant = 1.0f;  break;
        case Scene_horror:        constant = 1.0f;  break;
        case Scene_biochemicalLab:constant = 1.0f;  break;
        default:  break;
    }
    return constant;
}

GLfloat Scene::spotLightLinear(SceneType sType)
{
    GLfloat linear;
    switch (sType)
    {
        case Scene_desert:        linear = 0.9f;    break;
        case Scene_factory:       linear = 0.009f;  break;
        case Scene_horror:        linear = 0.09f;   break;
        case Scene_biochemicalLab:linear = 0.07f;   break;
        default:  break;
    }
    return linear;
}

GLfloat Scene::spotLightQuadratic(SceneType sType)
{
    GLfloat quadratic;
    switch (sType)
    {
        case Scene_desert:        quadratic = 0.032f;   break;
        case Scene_factory:       quadratic = 0.0032f;  break;
        case Scene_horror:        quadratic = 0.032f;   break;
        case Scene_biochemicalLab:quadratic = 0.017f;   break;
        default:  break;
    }
    return quadratic;
}

glm::vec3 Scene::spotLightAmbient(SceneType sType)
{
    glm::vec3 ambient;
    switch (sType)
    {
        case Scene_desert:        ambient = glm::vec3(0.0f, 0.0f, 0.0f);  break;
        case Scene_factory:       ambient = glm::vec3(0.0f, 0.0f, 0.0f);  break;
        case Scene_horror:        ambient = glm::vec3(0.0f, 0.0f, 0.0f);  break;
        case Scene_biochemicalLab:ambient = glm::vec3(0.0f, 0.0f, 0.0f);  break;
        default:  break;
    }
    return ambient;
}

glm::vec3 Scene::spotLightDiffuse(SceneType sType)
{
    glm::vec3 diffuse;
    switch (sType)
    {
        case Scene_desert:        diffuse = glm::vec3(0.8f, 0.8f, 0.0f);  break;
        case Scene_factory:       diffuse = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        case Scene_horror:        diffuse = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        case Scene_biochemicalLab:diffuse = glm::vec3(0.0f, 1.0f, 0.0f);  break;
        default:  break;
    }
    return diffuse;
}

glm::vec3 Scene::spotLightSpecular(SceneType sType)
{
    glm::vec3 specular;
    switch (sType)
    {
        case Scene_desert:        specular = glm::vec3(0.8f, 0.8f, 0.0f);  break;
        case Scene_factory:       specular = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        case Scene_horror:        specular = glm::vec3(1.0f, 1.0f, 1.0f);  break;
        case Scene_biochemicalLab:specular = glm::vec3(0.0f, 1.0f, 0.0f);  break;
        default:  break;
    }
    return specular;
}

glm::vec4 Scene::bgClearColor(SceneType sType)
{
    glm::vec4 bgColor;
    switch (sType)
    {
        case Scene_desert:        bgColor = glm::vec4(0.75f, 0.52f, 0.3f, 1.0f);  break;
        case Scene_factory:       bgColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);    break;
        case Scene_horror:        bgColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);    break;
        case Scene_biochemicalLab:bgColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);    break;
        default:  break;
    }
    return bgColor;
}
