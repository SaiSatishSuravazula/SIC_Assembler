
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define tokens
enum class TokenType {
    ID,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    INT,
    LEFT_PAREN,
    RIGHT_PAREN,
    INVALID
};

// Token structure
struct Token {
    TokenType type;
    std::string lexeme;
};

bool parseEXP(vector<Token> &tokens, size_t &index);

// Tokenize the input string
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < input.size()) {
        if (std::isspace(input[i])) {
            // Skip whitespace characters
            i++;
        } else if (input[i] == 'D' && input.substr(i, 3) == "DIV" /*&& input[i+4] == ' '*/) {
            tokens.push_back({TokenType::DIV, "DIV"});
            i+=3;
        } else if(isdigit(input[i]))   {
            size_t j = i;
            while(j < input.size() && isdigit(input[j])) {
                j++;
            }
            tokens.push_back({TokenType::INT, input.substr(i, j-i)});
            i=j;
        } else if(isalnum(input[i]))   {
            size_t j = i;
            while(j < input.size() && (isalnum(input[j]) || input[j] == '_')) {
                j++;
            }
            tokens.push_back({TokenType::ID, input.substr(i, j-i)});
            i=j;
        } else if(input[i] == ':' && input[i+1] == '=') {
            tokens.push_back({TokenType::ASSIGN, input.substr(i, 2)});
            i = i+2;
        } else if (input[i] == '(') {
            tokens.push_back({TokenType::LEFT_PAREN, "("});
            i++;
        } else if (input[i] == '*') {
            tokens.push_back({TokenType::MUL, "*"});
            i++;
        } else if (input[i] == '+') {
            tokens.push_back({TokenType::ADD, "+"});
            i++;
        } else if (input[i] == '-') {
            tokens.push_back({TokenType::SUB, "-"});
            i++;
        } 
        else if (input[i] == ')') {
            tokens.push_back({TokenType::RIGHT_PAREN, ")"});
            i++;
        } else {
            // Handle invalid characters
            tokens.push_back({TokenType::INVALID, std::string(1, input[i])});
            i++;
        } 
    }
    return tokens;
}

bool parseFACTOR(vector<Token> &tokens, size_t &index)
{
    if(tokens[index].type == TokenType::ID || tokens[index].type == TokenType::INT)
    {
        index++;
    }

    else
    {
        if(tokens[index].type == TokenType::LEFT_PAREN) {
            index++;
            if(!parseEXP(tokens, index)) {
                return false;
            }
            else {
                if(tokens[index].type == TokenType::RIGHT_PAREN)
                {
                    index++;
                }
            }
        }
    }

    return true;
}

bool parseTERM(vector<Token> &tokens, size_t &index)
{
    //check for factor
    if (!parseFACTOR(tokens, index)) {
        return false; // Failed to parse factor
    }

    if(tokens[index].type == TokenType::MUL || tokens[index].type == TokenType::DIV) {
        index++; //Consume div or mul
        return parseTERM(tokens, index); //recursive call for more factors
    }

    return true; //Successfully parsed term tree    
}

bool parseEXP(vector<Token> &tokens, size_t &index)
{
    //check for Term
    if (!parseTERM(tokens, index)) {
        return false; // Failed to parse term
    } 

    // Check for +/- and more terms
    if (tokens[index].type == TokenType::ADD || tokens[index].type == TokenType::SUB) {
        index++; // Consume add or subtract;
        return parseEXP(tokens, index); //recursive call for more terms
    }

    return true; //successfully parsed Expression tree
}

//parse for Assignment
bool parseASSIGN(vector<Token> &tokens, size_t &index)
{
    // Check for id keyword
    if (tokens[index].type == TokenType::ID) {
        index++; // Consume id
    } else {
        return false; // Invalid syntax
    }

    //check for ASSIGN keyword
    if(tokens[index].type == TokenType::ASSIGN)
    {
        index++; // consume Assign
    } else {
        return false; // Invalid syntax
    }

    //check for Expression keyword
    if (!parseEXP(tokens, index)) {
        return false; // Failed to parse expression
    }

    return true; //successfully parsed Assignment tree
}

int main() {
    //std::string input = "READ(id1, id2)";
    string input;
    cout << "Enter some text of the form 'id := <exp>'" << endl;
    getline(cin, input);
    
    std::vector<Token> tokens = tokenize(input);
    for(auto i:tokens) cout << i.lexeme << endl; 
    size_t index = 0;
    if (parseASSIGN(tokens, index) && index == tokens.size() ) { //&& index == tokens.size()) eg: j := n := {
        std::cout << "Input is valid." << std::endl;
    } else {
        std::cout << "Input is invalid." << std::endl;
    }

    return 0;
}