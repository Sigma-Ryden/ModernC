#include "UberGirl.h"

int main() {
    Girl* girl = CONSTRUCT(Girl)("Sonya", 19);

    IHuman* human = CAST(girl, IHuman);
    human->PrintName(girl);

    IRunable* runable = CAST(girl, IRunable);
    runable->Run(runable);

    {
        UberGirl* ubergirl = CONSTRUCT(UberGirl)("Ayesha", girl->GetAge(girl)+2);

        Girl* parent = CAST(ubergirl, Girl);
        parent->PrintName(parent);

        DESTRUCT(UberGirl)(ubergirl);
    }

    Girl* other = DOWNCAST(human, IHuman, Girl);
    DESTRUCT(Girl)(other);

    return 0;
}
