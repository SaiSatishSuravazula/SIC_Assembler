#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define tokens
enum class TokenType {
    READ,
    ID,
    COMMA,
    LEFT_PAREN,
    RIGHT_PAREN,
    INVALID
};

// Token structure
struct Token {
    TokenType type;
    std::string lexeme;
};

// Tokenize the input string
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < input.size()) {
        if (std::isspace(input[i])) {
            // Skip whitespace characters
            i++;
        } else if (input[i] == 'R' && input.substr(i, 4) == "READ") {
            tokens.push_back({TokenType::READ, "READ"});
            i += 4;
        } else if (std::isalpha(input[i])) {
            // Tokenize IDs
            size_t j = i;
            while (j < input.size() && std::isalnum(input[j])) {
                j++;
            }
            tokens.push_back({TokenType::ID, input.substr(i, j - i)});
            i = j;
        } else if (input[i] == ',') {
            tokens.push_back({TokenType::COMMA, ","});
            i++;
        } else if (input[i] == '(') {
            tokens.push_back({TokenType::LEFT_PAREN, "("});
            i++;
        } else if (input[i] == ')') {
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

// Recursive descent parser for IDLIST
bool parseIDList(std::vector<Token>& tokens, size_t& index) {
    // Check for ID
    if (tokens[index].type == TokenType::ID) {
        index++; // Consume ID
    } else {
        return false; // Invalid syntax
    }

    // Check for comma and more IDs
    if (tokens[index].type == TokenType::COMMA) {
        index++; // Consume comma
        return parseIDList(tokens, index); // Recursive call for more IDs
    }

    return true; // IDLIST parsed successfully
}

// Parser for READ
bool parseRead(std::vector<Token>& tokens, size_t& index) {
    // Check for READ keyword
    if (tokens[index].type == TokenType::READ) {
        index++; // Consume READ
    } else {
        return false; // Invalid syntax
    }

    // Check for left parenthesis
    if (tokens[index].type == TokenType::LEFT_PAREN) {
        index++; // Consume left parenthesis
    } else {
        return false; // Invalid syntax
    }

    // Parse IDLIST
    if (!parseIDList(tokens, index)) {
        return false; // Failed to parse IDLIST
    }

    // Check for right parenthesis
    if (tokens[index].type == TokenType::RIGHT_PAREN) {
        index++; // Consume right parenthesis
    } else {
        return false; // Invalid syntax
    }

    return true; // READ parsed successfully
}

int main() {
    //std::string input = "READ(id1, id2)";
    string input;
    cout << "Enter some text of the form 'READ(id1, id2)'" << endl;
    getline(cin, input);
    
    std::vector<Token> tokens = tokenize(input);

    size_t index = 0;
    if (parseRead(tokens, index) && index == tokens.size()) {
        std::cout << "Input is valid." << std::endl;
    } else {
        std::cout << "Input is invalid." << std::endl;
    }

    return 0;
}
