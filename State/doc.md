[TOC]

--------
# 案例：马里奥积分竞赛
喜欢马里奥的小伙伴们都应该知道，前不久马里奥为了庆祝35周年，推出了一款以多人对抗大逃杀为核心的超级马里奥兄弟35
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110116034213.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
~~此处仅为举例，并无此开发计划~~ 

由于新颖的游戏模式带来了巨大的热度，于是任天堂决定趁热打铁，推出一款马里奥竞技游戏，在一定时间内获得积分最多的玩家将获得胜利。考虑到游戏并非正传，于是任天堂将游戏的开发工作外包给了小明所在的游戏公司来进行制作。

游戏的核心玩法就是在一定时间内获取最高的积分，为了增加游戏的难度，我们设定只有获取道具才能够获得积分，而一旦遭受伤害就会损失积分，而死亡后积分就会清空。同时为了给落后的玩家反击的机会，以及给领先的玩家造成压迫感，玩家死亡后并不会退出游戏，而是积分清空后重新挑战。

在最初的版本中，我们只开放了蘑菇、太阳花两种道具，以及简单的设置了造成伤害的陷阱，于是马里奥的状态和行为如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101160856985.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
状态具有四种，分别是普通马里奥、超级马里奥、火焰马里奥、死亡马里奥
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101161918214.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

由于开放的道具不多，所以行为只有获得蘑菇、获得太阳花、受到伤害、复活四种。并且不同的行为都会带来不同的状态/分数变化。

根据状态和行为，画出状态转移图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101160939365.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
从上面可以看出，如果我们要实现这些逻辑的转换，其实就是去实现一个**状态机**，为了照顾到不了解状态机的同学，下面我会简单的描述一下什么是状态机

-----
# 有限状态机
有限状态机简写为FSM（Finite State Machine），我们通常将其简称为状态机。状态机由以下三个部分组成：**状态(State)、事件(Event)、动作(Action)**，其中事件也被叫做**转移条件(Transition Condition)**

**状态机的作用就是根据不同的事件来触发状态的转移以及动作的执行**

例如上面提到的马里奥中的形态转变，就是一个状态机。其中马里奥的不同形态(如超级马里奥，火焰马里奥)就是状态机中的状态。游戏中触发的事件(获得蘑菇、遭受伤害)就是状态机中的事件。触发事件后的积分变化就是状态机的动作。而其中由事件(吃蘑菇)带来的状态变化(普通马里奥变为超级马里奥)就是状态转移。

那么我们如何用代码来实现上面所说的状态机呢？下面我会分别介绍三种方法，分别是**分支逻辑法、查表法、状态模式**

首先给出一个通用的自动机骨架，我们使用枚举来表示四种状态， 同时为状态机提供触发事件以及获取信息的接口，代码如下

```cpp
//状态
enum State
{
    NORMAL, //普通状态
    SUPER,  //超级状态
    FIRE,   //火焰状态
    DEAD    //死亡状态
};

//状态机
class MarioStateMachine
{
public:
    MarioStateMachine()
        : _score(0)
        , _state(NORMAL)
    {}

    void getRevive();       //复活
    void getMushroom();     //获得蘑菇
    void getSunFlower();    //获得太阳花
    void getHurt();         //受到伤害
    int getScore() const;   //获取当前分数
    State getState() const; //获取当前状态

private:
    int _score;     //当前分数
    State _state;   //当前状态
};
```

-----
## 分支逻辑法
要想实现状态机，最容易的方法就是**直接参照状态转移图，直接将每种事件中每种状态变化翻译成代码**，由于这样的代码中存在大量的分支逻辑判断，所以这种方法又叫做**分支逻辑法**。

代码实现如下
```cpp
//获取当前分数
int MarioStateMachine::getScore() const
{
    return _score;
}

//获取当前状态
State MarioStateMachine::getState() const
{
    return _state;
}

//复活
void MarioStateMachine::getRevive()
{
    if(_state == FIRE)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;        
    }
    else if(_state == SUPER)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;   
    }
    else if(_state == NORMAL)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;   
    }
    else if(_state == DEAD)
    {
        _state = NORMAL;
        _score = 0;
        std::cout << "复活马里奥，会到普通状态，分数重新计算" << std::endl;
    }
}
    
//获得蘑菇
void MarioStateMachine::getMushroom()
{
    if(_state == FIRE)
    {
        _score += 100;
        std::cout << "获得蘑菇，增加一百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _score += 100;
        std::cout << "获得蘑菇，增加一百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = SUPER;
        _score += 100;
        std::cout << "获得蘑菇，由普通马里奥变为超级马里奥，增加一百分" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }
};     

//获得太阳花
void MarioStateMachine::getSunFlower()
{
    if(_state == FIRE)
    {
        _score += 200;
        std::cout << "获得太阳花，增加两百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _state = FIRE;
        _score += 200;
        std::cout << "获得太阳花，由超级马里奥变为火焰马里奥，增加两百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = FIRE;
        _score += 200;

        std::cout << "获得太阳花，由普通马里奥变为火焰马里奥，增加两百分" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }
};  

//遭受伤害
void MarioStateMachine::getHurt()
{
    if(_state == FIRE)
    {
        _state = SUPER;
        _score -= 100;
        std::cout << "受到伤害，由火焰马里奥变为超级马里奥，扣一百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _state = NORMAL;
        _score -= 100;
        std::cout << "受到伤害，由超级马里奥变为普通马里奥，扣一百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = DEAD;
        _score = 0;

        std::cout << "受到伤害，马里奥死亡，分数清空" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能受到伤害，不存在该逻辑" << std::endl;
    }
}; 
```
简单的写一段代码测试状态机是否正确

```cpp
int main()
{
    MarioStateMachine Mario;
    Mario.getMushroom();    //马里奥获取蘑菇
    Mario.getSunFlower();   //马里奥获取太阳花
    Mario.getSunFlower();   //马里奥获取太阳花
    std::cout << Mario.getScore() << std::endl; //查看得分情况

    Mario.getRevive();  //尝试复活

    Mario.getHurt();
    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //检查受伤后是否扣分

    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //死亡分数清空
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101165147734.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
代码执行没有错误。

对于简单且不需拓展的状态机来说，分支逻辑的缺点并不明显。但是对于复杂的状态机来说，随着状态越来越多，代码中就会充斥着大量的分支判断逻辑，极易漏写或错写某个状态。不仅仅可读性差，可维护性也差，如果我们需要新增或者修改某个状态，就需要去修改一系列的代码来保证逻辑的正常执行，不仅麻烦还容易出错。

为了让代码更加可读且方便拓展，我们可以考虑使用**查表法**来实现状态机。

------
## 查表法
查表法并非本章讲解的重点，只是因为提到状态机后顺带提一提这个知识点，如果不需要了解可以直接跳过到下面的状态模式。

除了用状态转移图外，我们还可以用二维的**状态转移表**来表示状态机。其中**第一维为状态，第二维是事件，值表示发生的行动以及状态的转移**

**查表法，就是依赖按照状态转移表，维护一个状态转移数组以及行为数组，根据不同的事件来触发数组中的对应元素**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101173806511.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
如上图，此时我们需要引入行为表和状态转移表，并且提供一个查表函数，根据当前遭遇的事件以及当前状态，自动去查表来获取当前转移状态和行为，所以新的骨架如下

```cpp
//用枚举表示遭遇的事件
enum Event
{
    GET_MUSHROOM,   //获得蘑菇
    GET_SUNFLOWER,  //获得太阳花
    GET_HURT,       //遭受伤害
    GET_REVIVE,     //复活
};

class MarioStateMachine
{
public:
    MarioStateMachine()
        : _score(0)
        , _state(NORMAL)
    {}

    void getRevive();       //复活
    void getMushroom();     //获得蘑菇
    void getSunFlower();    //获得太阳花
    void getHurt();         //受到伤害
    int getScore() const;   //获取当前分数
    State getState() const; //获取当前状态

private:
    void executeEvent(Event event); //执行事件
    int _score;     //当前分数
    State _state;   //当前状态
    static std::vector<std::vector<int>> _actionTable;    //行为表
    static std::vector<std::vector<State>> _stateTable;   //状态表
};
```
填写转移表和行为表
```cpp
//用INT_MIN表示清空，用0表示不符合逻辑的忽略情况
std::vector<std::vector<int>> MarioStateMachine::_actionTable = 
{
    {100, 200, INT_MIN, 0},
    {100, 200, -100, 0},
    {200, 200, -100, 0},
    {0, 0, 0, INT_MIN},
};

std::vector<std::vector<State>> MarioStateMachine::_stateTable = 
{
    {SUPER, FIRE, DEAD, NORMAL},
    {SUPER, FIRE, NORMAL, SUPER},
    {FIRE, FIRE, SUPER, FIRE},
    {DEAD, DEAD, DEAD, NORMAL},
};
```

接下来用查表法来实现我们的新骨架，我们提供了一个executeEvent接口，当执行各种事件函数的时候就会根据事件去查询表来获取结果

```cpp
void MarioStateMachine::executeEvent(Event event)
{
    int score = _actionTable[_state][event];    //查询表中对应的动作
    
    _score = (score == INT_MIN) ? _score = 0 : _score + score;   //如果为INT_MIN,则说明需要清空 
    _state = _stateTable[_state][event];        //查询表中对应的状态
}

void MarioStateMachine::getRevive()
{
    executeEvent(GET_REVIVE);
}
    
void MarioStateMachine::getMushroom()
{
    executeEvent(GET_MUSHROOM);
};     

void MarioStateMachine::getSunFlower()
{
    executeEvent(GET_SUNFLOWER);
};  

void MarioStateMachine::getHurt()
{
    executeEvent(GET_HURT);
};        
```

用上面的测试代码再次进行测试
```cpp
int main()
{
    MarioStateMachine Mario;
    Mario.getMushroom();    //马里奥获取蘑菇
    Mario.getSunFlower();   //马里奥获取太阳花
    Mario.getSunFlower();   //马里奥获取太阳花
    std::cout << Mario.getScore() << std::endl; //查看得分情况

    Mario.getRevive();  //尝试复活

    Mario.getHurt();
    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //检查受伤后是否扣分

    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //死亡分数清空
    return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101173748968.png#pic_center)
相较于分支逻辑法，查表法的代码更加简洁、清晰，可读性和可维护性更高。**当我们需要修改状态机的时候，就只需要修改行为表和转移表**。我们甚至可以将这两个表保存到配置文件中，这样修改的时候就只需要修改配置文件，而不需要修改任何代码。

但是从上面的实现我们也可以看到，如果我们的动作只是简单的积分变化，就可以使用行为表表示，倘若其中是一些复杂的逻辑呢？例如上面代码中的输出日志，行为表就没办法将其执行，因此查表法具有一定的局限性。

虽然分支逻辑不存在这个问题，但是我们前面也提到了它存在大量的逻辑判断，导致维护性和可读性不高，既然它们两者都有一定的缺点，那是否还有第三种方法能够更好的实现状态机呢？

答案是肯定的，铺垫了这么久，接下来就到**状态模式**大显身手的时候了

---
# 状态模式
**状态模式允许对象在内部状态改变的时候改变它的行为，让对象看起来好像修改了它的类**

我们不再使用枚举来表示状态，而是将每个状态封装为一个类，并在该类中实现其对应事件的动作及状态转移。由于行为会随着内部状态而改变，所以我们将状态机处理事件的行为委托到代表当前状态的对象中，**这样我们就通过组合简单引用不同的状态对象来造成类改变的假象**

状态模式的类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201102113816530.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
将其转换为我们案例的类图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201102114835759.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
此时我们的**状态转换不再像之前一样由状态机进行，而是由状态对象进行**，例如下图

假设我们一开始是普通马里奥
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201102115149180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
此时获得蘑菇
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201102115341333.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
此时内部的状态对象变为超级马里奥
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110211542893.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
讲解完了思路，下面开始分别实现这几部分

马里奥的状态接口如下
```cpp
class MarioState
{
public:
    virtual ~MarioState() = default;
    virtual MarioState* getState(); 	//获取当前状态
    virtual std::string getStateName(); //获取状态名
    virtual void getRevive();       	//复活
    virtual void getMushroom();     	//获得蘑菇
    virtual void getSunFlower();    	//获得太阳花
    virtual void getHurt();         	//受到伤害
};
```
接着我们将每个状态封装为一个类，并实现状态接口。下面仅实现一个，其他的放在末尾的链接中。

每个具体状态类中都需要保存一个状态机的指针，来进行状态的转移和动作的执行。
```cpp
class NormalMario : public MarioState
{
public:
    NormalMario(MarioStateMachine* stateMachine)
        : _stateMachine(stateMachine)
    {}

    void getRevive() override
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;  
    }    

    void getMushroom() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 100);
        _stateMachine->setState(_stateMachine->getSuperMario());
        std::cout << "获得蘑菇，由普通马里奥变为超级马里奥，增加一百分" << std::endl;
    }

    void getSunFlower() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 200);
        _stateMachine->setState(_stateMachine->getFireMario());
        std::cout << "获得太阳花，由普通马里奥变为火焰马里奥，增加两百分" << std::endl;
    }

    void getHurt() override
    {
        _stateMachine->setScore(0);
        _stateMachine->setState(_stateMachine->getDeadMario());
        std::cout << "受到伤害，马里奥死亡，分数清空" << std::endl;
    }    

    std::string getStateName() override
    {
        return "普通马里奥";
    }

private:
    MarioStateMachine* _stateMachine;   //状态机
};
```

接着我们用策略模式来改写状态机，其中**为了避免大量生成状态对象，我提前将所有状态缓存到状态机中，并提供获取状态实例的接口**(我们也可以采用将状态与**单例模式**相结合的做法，保证每个状态只有一个实例)，代码如下
```cpp
class MarioStateMachine
{
public:
    MarioStateMachine()
        : _score(0)
    {
        //提前缓存各种状态
        _normalMario = new NormalMario(this);
        _superMario = new SuperMario(this);
        _fireMario = new FireMario(this);
        _deadMario = new DeadMario(this);

        _state = _normalMario;
    }

    ~MarioStateMachine()
    {
        delete _normalMario, _superMario, _fireMario, _deadMario;
    }

    void getRevive();                   //复活
    void getMushroom();                 //获得蘑菇
    void getSunFlower();                //获得太阳花
    void getHurt();                     //受到伤害
    int getScore() const;               //获取当前分数
    MarioState* getState() const;       //获取当前状态
    void setScore(int score);           //获取当前分数
    void setState(MarioState* state);   //获取当前状态

    MarioState* getNormalMario();       //获取缓存的状态
    MarioState* getSuperMario();
    MarioState* getFireMario();
    MarioState* getDeadMario();

private:
    int _score;                 //当前分数
    MarioState* _state;         //当前状态
    
    MarioState* _superMario;    //缓存所有的状态
    MarioState* _normalMario;
    MarioState* _fireMario;    
    MarioState* _deadMario;
};
```
由于状态机会将事件发生后的行为与状态转移**委托**给当前的状态对象，因此我们只需要调用状态对象的方法即可
```cpp
void MarioStateMachine::getRevive()
{
    _state->getRevive();
}

void MarioStateMachine::getMushroom()
{
    _state->getMushroom();
}

void MarioStateMachine::getSunFlower()
{
    _state->getSunFlower();
}

void MarioStateMachine::getHurt()
{
    _state->getHurt();
}   

int MarioStateMachine::getScore() const
{
    return _score;
}

MarioState* MarioStateMachine::getState() const
{
    return _state;
}

void MarioStateMachine::setScore(int score) 
{
    _score = score;
}

void MarioStateMachine::setState(MarioState* state) 
{
    _state = state;
}

MarioState* MarioStateMachine::getNormalMario()  
{
    return _normalMario;
}  

MarioState* MarioStateMachine::getSuperMario()
{
    return _superMario;
}

MarioState* MarioStateMachine::getFireMario()
{
    return _fireMario;
}

MarioState* MarioStateMachine::getDeadMario()
{
    return _deadMario;
}
```

接着继续使用开头的代码进行测试，由于我们是在一开始搭建的状态机骨架上进行拓展的，因此不需要修改任何代码

```cpp
int main()
{
    MarioStateMachine Mario;
    
    Mario.getMushroom();    //马里奥获取蘑菇
    Mario.getSunFlower();   //马里奥获取太阳花
    Mario.getSunFlower();   //马里奥获取太阳花
    std::cout << Mario.getScore() << std::endl; //查看得分情况

    Mario.getRevive();  //尝试复活

    Mario.getHurt();
    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //检查受伤后是否扣分

    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //死亡分数清空
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110211342617.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

-------
# 状态模式与策略模式
如果不了解策略模式，可以参考我的往期博客
[趣谈设计模式 | 策略模式(Strategy)：你还在使用冗长的if-else吗？](https://blog.csdn.net/qq_35423154/article/details/109388643)

在上面，我给出了状态模式的类图，我们惊奇的发现它的类图竟然和策略模式一模一样，并且他们的思路也存在相似的地方，它们都可以用来消除大量的条件判断，并且都可以在允许时动态切换行为
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201102125013203.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
**虽然类图相同，但是它们的意图截然不同，策略模式会控制对象使用什么策略，而状态模式会自动改变状态**


以策略模式而言，虽然他也能够通过组合不同的策略对象来动态的切换行为，但是这些都需要**决策者自己控制使用的策略对象**，其中没有良好的状态转换

而对于状态模式，状态机则将状态转换的任务委托给了当前的状态对象，**当前状态对象会根据不同的事件自动而切换到其他的状态对象**，状态机本身的行为也会随着状态对象的切换而变化，但是这些都是自动的，并不需要它自己处理

简单的总结一下就是，**策略模式使用策略来主动配置Context而改变行为，状态模式则让Context随着状态的改变自动改变行为**

----------
# 总结
## 分支逻辑法
**特点**
- 利用if-else或者switch-case进行逻辑分支逻辑判断，直接将状态转移图的每个状态转移翻译成代码

**应用场景**
- 简单、不考虑拓展的状态机

-----
## 查表法
**特点**
- 维护了一个动作表和状态转移表，根据具体事件以及当前状态进行查表，来实现状态转移和动作

**应用场景**
- 条件、分支语句的替代
- 状态很多、状态转移复杂，但是事件触发后执行动作简单的状态机

--------
## 状态模式
**特点**
- 状态模式允许一个对象基于内部状态而拥有不同行为
- 状态机会将行为委托给当前状态对象，所以状态机会随着状态的改变而改变行为
- 和其他方法实现的状态机不同，状态模式用类来表示状态。但是也会导致设计中类的数目大量增加，因此最好在状态少，状态转移简单时使用
- 由于状态类可以被多个状态机共享，所以通常以单例模式实现
- 状态的改变局部化，需要增加新状态时只需要实现状态接口，并完成具体事件的行为即可

**应用场景**
- 行为随着状态改变而改变的情景
- 条件、分支语句的替代
- 状态不多、状态转移简单，但是事件触发后执行动作复杂的状态机。如：游戏、电商下单
