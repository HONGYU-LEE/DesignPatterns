#pragma once
#include"Template.hpp"

class WesternStyle : public BuildTemplate
{
protected:
    void Design() override
    {
        std::cout << "设计出西式风格的装修计划" << std::endl;
    }

    
    void Renovation() override
    {
        std::cout << "将房屋装修为西式风格" << std::endl;                                                                                                                                                
    }
};

class ChineseStyle : public BuildTemplate
{
protected:
    void Design() override
    {
        std::cout << "设计出中式风格的装修计划" << std::endl;
    }

    void Renovation() override
    {
        std::cout << "将房屋装修为中式风格" << std::endl;                                                                                                                                                
    }
};
