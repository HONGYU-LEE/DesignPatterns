#pragma once
#include"SubSystem.hpp"

class AutoAircraft
{
public:
    AutoAircraft()
        : _cooling(new CoolingSystem)
        , _dynamic(new DynamicSystem)
        , _engine(new EngineSystem)
        , _navigaton(new NavigationSystem)
    {}

    ~AutoAircraft()
    {
        delete _cooling, _dynamic, _engine, _navigaton;
    }

    void systemOn()
    {
        _engine->systemOn();
        _cooling->systemOn();
        _dynamic->systemOn();
        _navigaton->systemOn();
    }

    void systemOff()
    {
        _navigaton->systemOff();
        _dynamic->systemOff();
        _cooling->systemOff();
        _engine->systemOff();
    }

private:
    CoolingSystem* _cooling;
    DynamicSystem* _dynamic;
    EngineSystem* _engine;
    NavigationSystem* _navigaton;
};