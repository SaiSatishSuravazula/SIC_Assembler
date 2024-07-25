#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <string>

using namespace std;

map <string, string> const_optab()
{
    map <string, string> optab;

        optab["ADD"] = "18";
        optab["ADDF"] = "58";
        optab["ADDR"] = "90";
        optab["AND"] = "40";
        optab["CLEAR"] = "B4";
        optab["COMP"] = "28";
        optab["COMPF"] = "88";
        optab["COMPR"] = "A0";
        optab["DIV"] = "24";
        optab["DIVF"] = "64";
        optab["DIVR"] = "9C";
        optab["FIX"] = "C4";
        optab["FLOAT"] = "C0";
        optab["HIO"] = "F4";
        optab["J"] = "3C";
        optab["JEQ"] = "30";
        optab["JGT"] = "34";
        optab["JLT"] = "38";
        optab["JSUB"] = "48";
        optab["LDA"] = "00";
        optab["LDB"] = "68";
        optab["LDCH"] = "50";
        optab["LDF"] = "70";
        optab["LDL"] = "08";
        optab["LDS"] = "6C";
        optab["LDT"] = "74";
        optab["LDX"] = "04";
        optab["LPS"] = "D0";
        optab["MUL"] = "20";
        optab["MULF"] = "60";
        optab["MULR"] = "98";
        optab["NORM"] = "C8";
        optab["OR"] = "44";
        optab["RD"] = "D8";
        optab["RMO"] = "AC";
        optab["RSUB"] = "4C";
        optab["SHIFTL"] = "A4";
        optab["SHIFTR"] = "A8";
        optab["SIO"] = "F0";
        optab["SSK"] = "EC";
        optab["STA"] = "0C";
        optab["STB"] = "78";
        optab["STCH"] = "54";
        optab["STF"] = "80";
        optab["STI"] = "D4";
        optab["STL"] = "14";
        optab["STS"] = "7C";
        optab["STSW"] = "E8";
        optab["STT"] = "84";
        optab["STX"] = "10";
        optab["SUB"] = "1C";
        optab["SUBF"] = "5C";
        optab["SUBR"] = "94";
        optab["SVC"] = "B0";
        optab["TD"] = "E0";
        optab["TIO"] = "F8";
        optab["TIX"] = "2C";
        optab["TIXR"] = "B8";
        optab["WD"] = "DC";

        return optab;
}