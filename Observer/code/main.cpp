#include"Douban.hpp"
#include"Zhihu.hpp"
#include"ScienceFictionPusher.hpp"

using namespace std;

int main()
{
    ScienceFictionPusher* _subject = new ScienceFictionPusher;
    Douban* douban = new Douban(_subject);
    Zhihu* zhihu = new Zhihu(_subject);

    _subject->setNewFiction("www.aaaaaaa.com", "三体", "作品讲述了地球人类文明和三体文明的信息交流、生死搏杀及两个文明在宇宙中的兴衰历程。");
    _subject->setNewFiction("www.bbbbbbb.com", "球形闪电", "描述了一个历经球状闪电的男主角对其历尽艰辛的研究历程，向我们展现了一个独特、神秘而离奇的世界");


    delete zhihu;
    delete douban;
    delete _subject;
    
    return 0;
}