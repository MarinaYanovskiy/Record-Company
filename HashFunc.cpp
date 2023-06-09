#include "HashFunc.h"

HashFunc::HashFunc(int mod):
mod(mod)
{
}
int HashFunc::operator()(int key) const
{
    return key%mod;
}
void HashFunc::setMod(int newMod)
{
    mod=newMod;
}