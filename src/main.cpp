#include "decrypt.hpp"


int main(int argc, char** argv)
{
    DecryptEngine dc_engine = DecryptEngine("IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ");
    dc_engine.decrypt_caesar_cipher();

    return 0;
}