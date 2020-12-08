#include"ConcreteHandler.hpp"

using namespace std;

int main()
{
    Handler* legal = new LegalHandler;
    Handler* business = new BusinessHandler;
    Handler* personnel = new PersonnelHandler;
    Handler* miscellaneous = new MiscellaneousHandler;
    legal->setSussessor(business);
    business->setSussessor(personnel);
    personnel->setSussessor(miscellaneous);

    legal->HandlerRequest({"法务信息", "XXX法院传票"});
    legal->HandlerRequest({"商务信息", "XXX商业合作"});
    legal->HandlerRequest({"人事信息", "XXX投递简历"});
    legal->HandlerRequest({"杂务信息", "XXX无关信息"});

    delete legal, business, personnel, miscellaneous;
}