#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Op_tab.h"
#include "functions.h"

using namespace std;


int main()
{
    string line;
    vector<string> inst_fields;
    map <string, string> OpTab;
    map<string, string> SymTab;

    ifstream fin2("SymTab.txt");

    if (!fin2.is_open()) {
        cerr << "Error: Unable to open SymTab.txt for reading." << endl;
        return 1;
    }
      
    string line2;
    while (getline(fin2, line2)) {
        // Split each line into key and value
        size_t pos = line2.find(' ');
        if (pos != string::npos) {
            string key = line2.substr(0, pos);
            string value = line2.substr(pos + 1);
            SymTab[key] = value;
        } else {
            cerr << "Error: Invalid line format in SymTab.txt" << endl;
        }
    }

    ifstream fin("intermediate_file.txt");
    ofstream fout("obj_prog.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return 1;
    }

    string locctr;
    string label;
    string opcode;
    string operand;

    // Store the position of the first line
    streampos firstLinePos = fin.tellg();

    getline(fin, line);
    inst_fields = split(line,' ');
    locctr = inst_fields[0];
    label = inst_fields[1];
    opcode = inst_fields[2];
    operand = inst_fields[3];

    int start_add = hextodec(locctr); //here locctr is already in hex

    string prevLine;
    string prevAddress;
    while (getline(fin, line)) {
        // Trim leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t")); // trim leading whitespace
        line.erase(line.find_last_not_of(" \t") + 1); // trim trailing whitespace

        // Store the address from the previous line
        if (!prevLine.empty()) {
            size_t pos = prevLine.find_first_of(" \t");
            prevAddress = prevLine.substr(0, pos);
        }

        // Store the current line as the previous line
        prevLine = line;
    }  

    // Go back to the first line
    fin.clear(); // Clear any error flags
    fin.seekg(firstLinePos);
    getline(fin, line); // reads first line which is not required
  
    int last_add = hextodec(prevAddress);

    int length =  last_add-start_add+1;
    string l = dectohex(length);
    l = padWithZeros(l, 6);

    if(opcode == "START")
    {
        fout << "H^" <<  padWithSpaces(label, 6) << "^" << padWithZeros(locctr, 6) << "^" <<  l;
    }


    OpTab = const_optab();
    getline(fin, line); // reads second line from which we need object code
        
        inst_fields = split(line, ' ');
        locctr = inst_fields[0];
        label = inst_fields[1];
        opcode = inst_fields[2];
        if (inst_fields.size() >= 4) {
        operand = inst_fields[3];
        } else {
        operand = ""; // Set operand to empty string if it's not present
        }

    int text_length;

    while(opcode != "END"){//text_length > 6){
        text_length = 60;
        fout << '\n' << "T^" << padWithZeros(locctr , 6);
        while (text_length > 0){//opcode != "END") {
            int opAddress;
            string objCode ="";
            if(OpTab.find(opcode)!=OpTab.end())
            {
                if(operand[operand.length()-1] == 'X' && operand[operand.length()-2] == ',')
                {
                int l = hextodec(SymTab[operand.substr(0, operand.length()-2)]);
                l = l+32768;
                objCode = OpTab[opcode] + dectohex(l);
                }
                else
                {
                    if(SymTab.find(operand) == SymTab.end())
                        objCode = OpTab[opcode] + "0000";
                    else
                        objCode = OpTab[opcode] + SymTab[operand];
                }
                if(text_length >= 6){
                    text_length -= 6;
                    fout << "^" << objCode;
                }
                else
                    break;
            }else if(opcode == "BYTE")
            {
                if(operand[0] == 'C')
                {
                    for(int i=2; i< operand.length()-1; i++)
                    {
                        char c = operand[i];
                        int asciiValue = c;
                        objCode += (dectohex(asciiValue));
                    }
                }
                else 
                {
                    for(int i=2; i< operand.length()-1; i++)
                    {
                        objCode += operand[i];
                    }
                }
                if(objCode.length() < text_length)
                {
                    text_length -= objCode.length();
                    fout << "^" << objCode;
                }
                else{
                    break;
                }        
            }
            else if(opcode == "WORD")
            {
                objCode = dectohex(stoi(operand));
                objCode = padWithZeros(objCode, 6);
                if(text_length >= 6){
                    text_length -= 6;
                    fout << "^" << objCode;
                }
            }
            else if(opcode == "RESW" || opcode == "RESB")
            {
                while(opcode == "RESW" || opcode == "RESB")
                {
                    if (!getline(fin, line)) {
                    cerr << "Error: Unexpected end of file." << endl;
                    break;
                    }
                    inst_fields = split(line, ' ');
                    locctr = inst_fields[0];
                    label = inst_fields[1];
                    opcode = inst_fields[2];
                    if (inst_fields.size() >= 4) {
                    operand = inst_fields[3];
                    } else {
                    operand = ""; // Set operand to empty string if it's not present
                    }
                }
                break;
            }

            if (!getline(fin, line)) {
                cerr << "Error: Unexpected end of file." << endl;
                break;
                }
                inst_fields = split(line, ' ');
                locctr = inst_fields[0];
                label = inst_fields[1];
                opcode = inst_fields[2];
                if (inst_fields.size() >= 4) {
                operand = inst_fields[3];
                } else {
                operand = ""; // Set operand to empty string if it's not present
                }
        }
    }

    fout << '\n' << "E^" << padWithZeros(dectohex(start_add), 6) << endl;

    fin2.close();
    fin.close();
    fout.close();


//for adding length of each record
    ifstream fin3("obj_prog.txt");
    ofstream fout2("temp.txt");
    getline(fin3, line); // reads the header record
    fout2 << line << endl;

    vector<string> v;
    int text_size;
    while(getline(fin3, line) && line[0] == 'T'){
        v = split(line, '^');
        text_size = 0;
        for(int i=2; i< v.size(); i++)
        {
            text_size += v[i].length();
        }
        line.insert(8, "^"+dectohex(text_size/2));
        fout2 << line << endl;
        v.erase(v.begin());
    }

    fout2 << line;

    fin3.close();
    fout2.close();

    remove("obj_prog.txt");
    rename("temp.txt", "obj_prog.txt");
    return 0;
}