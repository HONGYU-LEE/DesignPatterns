#pragma once
#include<iostream>
#include"Implementor.hpp"

class Music : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动音乐播放器" << std::endl;
    }
};

class Vedio : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动视频播放器" << std::endl;
    }
};

class Text : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动文本阅读器" << std::endl;
    }
};