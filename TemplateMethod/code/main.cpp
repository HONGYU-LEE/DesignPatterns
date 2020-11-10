#include"ConcreteClass.hpp"

using namespace std;

int main()
{
    BuildTemplate* chinese = new ChineseStyle;
    BuildTemplate* western = new WesternStyle;
    chinese->TemplateMethod();
    cout << endl;
    western->TemplateMethod();

    delete chinese, western;
    return 0;
}