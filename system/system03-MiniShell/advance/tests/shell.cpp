#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using Command = std::string;
using Token = std::string;
using TokenStream = std::vector<Token>;

Token cleanToken(Token token) {
    auto rubbish_char = [](char ch)->bool {
        return (ch == '\n') || (ch == '\r') || (ch == '\f') || (ch == '\v') || (ch == '\t');
    };
    while (token.size() && rubbish_char(token.back())) {
        token.pop_back();
    }
    return token;
}
TokenStream getTokenStream(Command command) {
    std::istringstream istr(command);
    Token tok;
    TokenStream tokstr{};
    while (istr >> tok) {
        tokstr.push_back(cleanToken(tok));
    }
    return tokstr;
}

int main() {
    Command command;
    while (true) {
        getline(std::cin, command);
        TokenStream token_stream = getTokenStream(command);
        
    }
    return 0;
}