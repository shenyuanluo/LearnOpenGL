//
//  Materials.cpp
//  
//
//  Created by shenyuanluo on 2017/8/19.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Materials.hpp"

#pragma mark -- Public
Materials::Materials()
{
    
}


Materials::~Materials()
{
    
}

#pragma mark -- 材质获取
GLfloat* Materials::info(MaterialType mType)
{
    /* 绿宝石 */
    GLfloat emerald[] =
    {
        0.0215,  0.1745,   0.0215,      /* 环境光 */
        0.07568, 0.61424,  0.07568,     /* 漫反射 */
        0.633,   0.727811, 0.633,       /* 镜面光 */
        0.6                             /* 反光度 */
    };
     /* 翡翠 */
    GLfloat jade[] =
    {
        0.135,    0.2225,   0.1575,
        0.54,     0.89,     0.63,
        0.316228, 0.316228, 0.316228,
        0.1
    };
    /* 黑曜石 */
    GLfloat obsidian[] =
    {
        0.05375,  0.05,     0.06625,
        0.18275,  0.17,     0.22525,
        0.332741, 0.328634, 0.346435,
        0.3
    };
    /* 珍珠 */
    GLfloat pearl[] =
    {
        0.25,     0.20725,  0.20725,
        1.0,      0.829,    0.829,
        0.296648, 0.296648, 0.296648,
        0.088
    };
    /* 红宝石 */
    GLfloat ruby[] =
    {
        0.1745,  0.01175,   0.01175,
        0.61424,  0.04136,  0.04136,
        0.727811, 0.626959, 0.626959,
        0.6
    };
    /* 绿松石 */
    GLfloat turquoise[] =
    {
        0.1,      0.18725, 0.1745,
        0.396,    0.74151, 0.69102,
        0.297254, 0.30829, 0.306678,
        0.1
    };
    /* 黄铜 */
    GLfloat brass[] =
    {
        0.329412, 0.223529, 0.027451,
        0.780392, 0.568627, 0.113725,
        0.992157, 0.941176, 0.807843,
        0.21794872
    };
    /* 青铜 */
    GLfloat bronze[] =
    {
        0.2125,   0.1275,   0.054,
        0.714,    0.4284,   0.18144,
        0.393548, 0.271906, 0.166721,
        0.2
    };
    /* 铬 */
    GLfloat chrome[] =
    {
        0.25,     0.25,     0.25,
        0.4,      0.4,      0.4,
        0.774597, 0.774597, 0.774597,
        0.6
        
    };
    /* 铜 */
    GLfloat copper[] =
    {
        0.19125,  0.0735,   0.0225,
        0.7038,   0.27048,  0.0828,
        0.256777, 0.137622, 0.086014,
        0.1
    };
    /* 金 */
    GLfloat gold[] =
    {
        0.24725,  0.1995,   0.0745,
        0.75164,  0.60648,  0.22648,
        0.628281, 0.555802, 0.366065,
        0.4
    };
    /* 银 */
    GLfloat silver[] =
    {
        0.19225,  0.19225,  0.19225,
        0.50754,  0.50754,  0.50754,
        0.508273, 0.508273, 0.508273,
        0.4
    };
    /* 黑色塑料 */
    GLfloat blackPlastic[] =
    {
        0.0,  0.0,  0.0,
        0.01, 0.01, 0.01,
        0.50, 0.50, 0.50,
        0.25
    };
    /* 蓝绿色塑料 */
    GLfloat cyanPlastic[] =
    {
        0.0,        0.1,        0.06,
        0.0,        0.50980392, 0.50980392,
        0.50196078, 0.50196078, 0.50196078,
        0.25
    };
    /* 绿色塑料 */
    GLfloat greenPlastic[] =
    {
        0.0,  0.0,  0.0,
        0.1,  0.35, 0.1,
        0.45, 0.55, 0.45,
        0.25
        
    };
    /* 红色塑料 */
    GLfloat redPlastic[] =
    {
        0.0, 0.0, 0.0,
        0.5, 0.0, 0.0,
        0.7, 0.6, 0.6,
        0.25
    };
    /* 白色塑料 */
    GLfloat whitePlastic[] =
    {
        0.0,  0.0,  0.0,
        0.55, 0.55, 0.55,
        0.70, 0.70, 0.70,
        0.25
        
    };
    /* 黄色塑料 */
    GLfloat yellowPlastic[] =
    {
        0.0,  0.0,  0.0,
        0.5,  0.5,  0.0,
        0.60, 0.60, 0.50,
        0.25
    };
    /* 黑色橡胶 */
    GLfloat blackRubber[] =
    {
        0.02, 0.02, 0.02,
        0.01, 0.01, 0.01,
        0.4,  0.4,  0.4,
        0.078125
    };
    /* 蓝绿色橡胶 */
    GLfloat cyanRubber[] =
    {
        0.0,  0.05, 0.05,
        0.4,  0.5,  0.5,
        0.04, 0.7,  0.7,
        0.078125
    };
    /* 绿色橡胶 */
    GLfloat greenRubber[] =
    {
        0.0,  0.05, 0.0,
        0.4,  0.5,  0.4,
        0.04, 0.7,  0.04,
        0.078125
        
    };
    /* 红色橡胶 */
    GLfloat redRubber[] =
    {
        0.05, 0.0,  0.0,
        0.5,  0.4,  0.4,
        0.7,  0.04, 0.04,
        0.078125
    };
    /* 白色橡胶 */
    GLfloat whiteRubber[] =
    {
        0.05, 0.05, 0.05,
        0.5,  0.5,  0.5,
        0.7,  0.7,  0.7,
        0.078125
    };
    /* 黄色橡胶 */
    GLfloat yellowRubber[] =
    {
        0.05, 0.05, 0.0,
        0.5,  0.5,  0.4,
        0.7,  0.7,  0.04,
        0.078125
    };
    GLfloat* material;
    switch (mType)
    {
        case Material_emerald:      material = emerald;         break;
        case Material_jade:         material = jade;            break;
        case Material_obsidian:     material = obsidian;        break;
        case Material_pearl:        material = pearl;           break;
        case Material_ruby:         material = ruby;            break;
        case Material_turquoise:    material = turquoise;       break;
        case Material_brass:        material = brass;           break;
        case Material_bronze:       material = bronze;          break;
        case Material_chrome:       material = chrome;          break;
        case Material_copper:       material = copper;          break;
        case Material_gold:         material = gold;            break;
        case Material_silver:       material = silver;          break;
        case Material_blackPlastic: material = blackPlastic;    break;
        case Material_cyanPlastic:  material = cyanPlastic;     break;
        case Material_greenPlastic: material = greenPlastic;    break;
        case Material_redPlastic:   material = redPlastic;      break;
        case Material_whitePlastic: material = whitePlastic;    break;
        case Material_yellowPlastic:material = yellowPlastic;   break;
        case Material_blackRubber:  material = blackRubber;     break;
        case Material_cyanRubber:   material = cyanRubber;      break;
        case Material_greenRubber:  material = greenRubber;     break;
        case Material_redRubber:    material = redRubber;       break;
        case Material_whiteRubber:  material = whiteRubber;     break;
        case Material_yellowRubber: material = yellowRubber;    break;
        default:                    material = emerald;         break;
    }
    
    return material;
}
