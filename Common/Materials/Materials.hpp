//
//  Materials.hpp
//  
//
//  Created by shenyuanluo on 2017/8/19.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Materials_hpp
#define Materials_hpp

#include <glad/glad.h>
#include <iostream>


/* 材质类型 枚举 */
typedef enum __materialType{
    Material_emerald            = 0x00,     /* 绿宝石 */
    Material_jade               = 0x01,     /* 翡翠 */
    Material_obsidian           = 0x02,     /* 黑曜石 */
    Material_pearl              = 0x03,     /* 珍珠 */
    Material_ruby               = 0x04,     /* 红宝石 */
    Material_turquoise          = 0x05,     /* 绿松石 */
    Material_brass              = 0x06,     /* 黄铜 */
    Material_bronze             = 0x07,     /* 青铜 */
    Material_chrome             = 0x08,     /* 铬 */
    Material_copper             = 0x09,     /* 铜 */
    Material_gold               = 0x0A,     /* 金 */
    Material_silver             = 0x0B,     /* 银 */
    Material_blackPlastic       = 0x0C,     /* 黑色塑料 */
    Material_cyanPlastic        = 0x0D,     /* 蓝绿色塑料 */
    Material_greenPlastic       = 0x0E,     /* 绿色塑料 */
    Material_redPlastic         = 0x0F,     /* 红色塑料 */
    Material_whitePlastic       = 0x10,     /* 白色塑料 */
    Material_yellowPlastic      = 0x11,     /* 黄色塑料 */
    Material_blackRubber        = 0x12,     /* 黑色橡胶 */
    Material_cyanRubber         = 0x13,     /* 蓝绿色橡胶 */
    Material_greenRubber        = 0x14,     /* 绿色橡胶 */
    Material_redRubber          = 0x15,     /* 红色橡胶 */
    Material_whiteRubber        = 0x16,     /* 白色橡胶 */
    Material_yellowRubber       = 0x17,     /* 黄色橡胶 */
}MaterialType;


class Materials
{
private:
    
public:
    Materials();
    
    ~Materials();
    
    /**
     获取材质属性

     @param mType 材质类型
     @return 材质属性值
     */
    GLfloat* info(MaterialType mType);
};

#endif /* Materials_hpp */
