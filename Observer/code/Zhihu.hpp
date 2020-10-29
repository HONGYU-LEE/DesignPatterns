#pragma once
#include"Observer.hpp"
#include"DisplayElement.hpp"
#include"Subject.hpp"

#include<string>
#include<iostream>

class Zhihu : public Observer, public DisplayElement
{
public:
    Zhihu(Subject* ScienceFictionPusher)
        : _ScienceFictionPusher(ScienceFictionPusher)
    {
        _ScienceFictionPusher->registerObserver(this);
    }

    ~Zhihu()
    {
        _ScienceFictionPusher->removeObserver(this);
    }

    void update(const std::string& url, const std::string& title, const std::string& desc) override
    {
        _url = url;
        _title = title;
        _desc = desc;

        display();
    }

    void display()
    {
        std::cout << "知乎每日书籍推荐：" << std::endl;
        std::cout << "链接：" << _url << std::endl;
        std::cout << "标题：" << _title << std::endl;
        std::cout << "简介：" << _desc << "\n" <<std::endl; 
    }
    
private:
    std::string _url;    //小说链接
    std::string _title;  //小说名
    std::string _desc;   //小说简介
    Subject* _ScienceFictionPusher; //主题对象，方便注册和删除
};