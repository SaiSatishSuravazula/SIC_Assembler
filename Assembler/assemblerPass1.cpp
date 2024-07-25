#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Op_tab.h"
#include "functions.h"


using namespace std;

int main()
{
    int locctr;
    int start_add;
    int prog_len;
    int len;
    string line;
    vector<string> inst_fields;
    map <string, string> OpTab;
    map<string, string> SymTab;

    //map <string, string> SymTab;

    //Construction of optab
    OpTab = const_optab();

    ifstream fin("input.txt");
    ofstream fout("intermediate_file.txt");
    ofstream f2out("SymTab.txt");

    getline(fin, line);
    inst_fields = split(line,' ');
    string label = inst_fields[0];
    string opcode = inst_fields[1];
    string operand = inst_fields[2];
    
    if(opcode == "START")
    {
        start_add =  stoi(operand);
        locctr = hextodec(to_string(start_add)); //here locctr is already in hex
        fout << dectohex(locctr) << " " << line << endl;
        getline(fin, line);
        inst_fields = split(line,' ');
        if(inst_fields[0]!="")
        label = inst_fields[0];
        if(inst_fields[1]!="")
        opcode = inst_fields[1];
        if(inst_fields[2]!="")
        operand = inst_fields[2];
    }
    else
    {locctr = 0;}
    

    while(opcode != "END")
    {
        if (label != "")
        {
            if(SymTab[label]!="")
            {cout << locctr <<  "Error : Duplicate Symbol " << label << endl;}
            else
            {SymTab[label] = dectohex(locctr);}
        }

        fout << dectohex(locctr) << " " << line << endl;
        
        if(OpTab[opcode]!="")
            locctr = locctr + 3;
        else if (opcode == "WORD")
            locctr = locctr + 3;
        else if (opcode == "RESW")
            locctr = locctr + (3*stoi(operand));
        else if (opcode == "RESB")
            locctr = locctr + stoi(operand);
        else if (opcode == "BYTE")
        {
            if(operand[0] == 'C')
                len = (operand.length() - 3); // removing character {c,' , '}
            else 
                len = (operand.length() - 3)/2;  //removing the characters {X ' '}

            locctr = locctr + len;
        }
        else
            cout << "Error : Invalid operation code" << endl;
        
        //fout << locctr << " " << line << endl;
        label = "";
        getline(fin, line);
        inst_fields = split(line,' ');
        int length = inst_fields.size();
        if(length-- &&  inst_fields[0]!="")
        label = inst_fields[0];
        if(length-- &&  inst_fields[1]!="")
        opcode = inst_fields[1];
        if(length-- &&  inst_fields[2]!="")
        operand = inst_fields[2];
    }
    fout  << " " << line << endl;

    prog_len = locctr - start_add + 1;

    /*cout << "Program Length : " << dectohex(prog_len) << endl <<  "StartAdd : " << start_add << endl;

    for (auto i : SymTab) cout << i.first << " " << i.second << endl; //display SymTab*/

    if (!f2out.is_open()) {
        cerr << "Error: Unable to open SymTab.txt for writing." << endl;
        return 1;
    }

    for (const auto& pair : SymTab) {
        f2out << pair.first << " " << pair.second << endl;
    }

    fin.close();
    fout.close();
    f2out.close();
    
    return 0;
}