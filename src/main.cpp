#include "decrypt.hpp"
#include "StringAnalysis.hpp"


int main(int argc, char** argv)
{
    //Caesar: "IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ"
    DecryptEngine caesar ("IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ");
    caesar.analyze_ciphertext();
    caesar.print_deciphered_caesars();

    //Vigenere: "UPRCW IHSGY OXQJR IMXTW AXVEB DREGJ AFNIS EECAG SSBZR TVEZU RJCXT OGPCY OOACS EDBGF ZIFUB KVMZU FXCAD CAXGS FVNKM SGOCG FIOWN KSXTS ZNVIZ HUVME DSEZU LFMBL PIXWR MSPUS FJCCA IRMSR FINCZ CXSNI BXAHE LGXZC BESFG HLFIV ESYWO RPGBD SXUAR JUSAR GYWRS GSRZP MDNIH WAPRK HIDHU ZBKEQ NETEX ZGFUI FVRI"
    DecryptEngine vigenere ("UPRCW IHSGY OXQJR IMXTW AXVEB DREGJ AFNIS EECAG SSBZR TVEZU RJCXT OGPCY OOACS EDBGF ZIFUB KVMZU FXCAD CAXGS FVNKM SGOCG FIOWN KSXTS ZNVIZ HUVME DSEZU LFMBL PIXWR MSPUS FJCCA IRMSR FINCZ CXSNI BXAHE LGXZC BESFG HLFIV ESYWO RPGBD SXUAR JUSAR GYWRS GSRZP MDNIH WAPRK HIDHU ZBKEQ NETEX ZGFUI FVRI");
    vigenere.analyze_ciphertext();

    return 0;
}