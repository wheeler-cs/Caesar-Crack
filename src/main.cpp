#include "decrypt.hpp"


int main(int argc, char** argv)
{
    //DecryptEngine dc_engine = DecryptEngine("IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ");
    //dc_engine.decrypt_caesar_cipher();

    VigenereDecipher vd_engine = VigenereDecipher("UPRCW IHSGY OXQJR IMXTW AXVEB DREGJ AFNIS EECAG SSBZR TVEZU RJCXT OGPCY OOACS EDBGF ZIFUB KVMZU FXCAD CAXGS FVNKM SGOCG FIOWN KSXTS ZNVIZ HUVME DSEZU LFMBL PIXWR MSPUS FJCCA IRMSR FINCZ CXSNI BXAHE LGXZC BESFG HLFIV ESYWO RPGBD SXUAR JUSAR GYWRS GSRZP MDNIH WAPRK HIDHU ZBKEQ NETEX ZGFUI FVRI");
    vd_engine.calculate_char_instances();
    vd_engine.calculate_ioc();
    vd_engine.calculate_ioc_key_length();
    vd_engine.split_alphabet_iocs();

    return 0;
}