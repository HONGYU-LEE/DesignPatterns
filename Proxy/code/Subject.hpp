#pragma once
#include<iostream>
/*
class Subject
{
public:
    virtual ~Subject() = default;
    virtual void rentingHouse() = 0;
};
*/
class Tenant
{
public:
    virtual ~Tenant() = default;
    virtual void rentingHouse() = 0;	//租房
};
