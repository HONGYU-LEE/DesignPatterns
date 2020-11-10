#pragma once
#include<iostream>

class BuildTemplate
{
public:
    virtual ~BuildTemplate() = default;
    virtual void TemplateMethod() final
    {
        Foundation();
        Build();
        Design();
        Renovation();
    }

protected:
    virtual void Design() = 0;
    virtual void Renovation() = 0;

    virtual void Foundation() final
    {
        std::cout << "打地基" << std::endl;
    }

    virtual void Build() final
    {
        std::cout << "建筑房屋" << std::endl;
    }
};