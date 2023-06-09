//
// Created by nrhbv on 09/06/2023.
//

#ifndef HASH_HASHFUNC_H
#define HASH_HASHFUNC_H


class HashFunc {
private:
    int mod;
public:
    explicit HashFunc(int mod);
    int operator()(int key) const;
    void setMod(int newMod);
};


#endif //HASH_HASHFUNC_H
