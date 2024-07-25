#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <sstream>
using namespace std;

int dec(char c)
{
    switch (c)
    {
        case 'A':
        return 10;
        case 'B':
        return 11;
        case 'C':
        return 12;
        case 'D':
        return 13;
        case 'E':
        return 14;
        case 'F':
        return 15;
        default:
        return stoi(to_string(c))-48;   //ascii value to magnitude
    }
}

int hextodec(string hex)
{
    int len = hex.length();
    int base = 1;
    int dec_num = 0;
    for (int i = len-1; i>=0; i--)
    {
        dec_num += dec(hex[i])*base;
        base = base*16;
    }
    return dec_num;
}

string hex(int d)
{
    switch (d)
    {
        case 10:
        return "A";
        case 11:
        return "B";
        case 12:
        return "C";
        case 13:
        return "D";
        case 14:
        return "E";
        case 15:
        return "F";
        default:
        return to_string(d);
    }
}

string dectohex(int dec_num)
{
    string hex_str = "";
    stack<int> stack;

    int div, rem;
    div = dec_num;
    rem = div % 16;
    //cout << "rem:" << rem << endl;
    stack.push(rem);
    div = (div)/16;
    //cout << "div:" << div << endl;
    while(div > 15)
    {
        rem = div % 16;
        //cout << "rem:" << rem << endl;
        stack.push(rem);
        div = (div)/16;
        //cout << "div:" << div << endl;
    }
    stack.push(div);
    while(!stack.empty())
    {
        //cout << stack.top();
        
        hex_str = hex_str + hex(stack.top());
        stack.pop();
    }
    return hex_str;

}

std::string padWithZeros(const std::string& input, int desiredLength) {
       if (input.length() >= desiredLength) {
        return input;
    } else {
        std::stringstream ss;
        ss << std::string(desiredLength - input.length(), '0') << input;
        return ss.str();
    }
}

std::string padWithSpaces(const std::string& input, int desiredLength) {
       if (input.length() >= desiredLength) {
        return input;
    } else {
        std::stringstream ss;
        ss << input << std::string(desiredLength - input.length(), ' ');
        return ss.str();
    }
}

/*std::vector<std::string> split(std::string str, char del) {
    std::vector<std::string> v;
    std::string temp = "";

    bool prev_del = false; // Flag to track if the previous character was a delimiter

    for (char c : str) {
        if (c != del) {
            temp += c;
            prev_del = false;
        } else {
            if (!prev_del) { // Only add to vector if the previous character wasn't a delimiter
                v.push_back(temp);
                temp = "";
            }
            prev_del = true;
        }
    }

    // Add the last token if it's not empty
    if (!temp.empty()) {
        v.push_back(temp);
    }

    return v;
}*/

vector<string> split(string str, char del)
{
      vector<string> v;
      string temp = "";
   
      for(int i=0; i<str.size(); i++)
        {
            if(str[i] != del)
            {
                temp += str[i];
            }
            else
            {
                v.push_back(temp);
                temp = "";
            }
        }
       
      v.push_back(temp);
      return v;
}


/*
int main()
{
    int dec = 1234;
    string hex_str = "";
    stack<int> stack;

    int div, rem;
    div = dec;
    rem = div % 16;
    cout << "rem:" << rem << endl;
    stack.push(rem);
    div = (div)/16;
    cout << "div:" << div << endl;
    while(div > 15)
    {
        rem = div % 16;
        cout << "rem:" << rem << endl;
        stack.push(rem);
        div = (div)/16;
        cout << "div:" << div << endl;
    }
    stack.push(div);
    while(!stack.empty())
    {
        cout << stack.top();
        
        hex_str = hex_str + hex(stack.top());
        stack.pop();
    }
    cout << "Hex String : " << hex_str << endl; 
    
    return 0;
}
*/