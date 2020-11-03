#pragma once
#include<iostream>
#include<string>

class Image
{
public:
    virtual ~Image() = default;
    virtual void display() = 0; //实现图片
};

class RealImage : public Image
{
public:
    RealImage(const std::string& imageName)
        : _imageName(imageName)
    {
        loadImage();    //加载图片
    }

    void display() override
    {
        std::cout << "显示图片" << _imageName << std::endl;
    }

    void loadImage()
    {
        std::cout << "加载图片" << _imageName << std::endl;
    }
private:
    std::string _imageName;
};

class ImageProxy : public Image
{
public:
    ImageProxy(const std::string& imageName)
        : _imageName(imageName)
        , _image(nullptr)
    {}

    ~ImageProxy()
    {
        if(_image)
        {
            delete _image;
        }
    }
    
    void display() override
    {
        //直到第一次访问，才去让目标加载图片
        if(_image == nullptr)
        {
           _image = new RealImage(_imageName);
        }
        _image->display(); //显示图片
    }

private:
    Image* _image;  
    std::string _imageName;
};

int main()
{
    Image* proxy = new ImageProxy("test.jpg");
    proxy->display();

    delete proxy;
    return 0;
}