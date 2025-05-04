#include "Token.h"
#include <unordered_set>
enum State 
{
    START,
    IDENTIFIER,
    NUMBER,
    FLOAT,
    SYMBOL,
    ACCEPT,
    OPERATOR,
    ERROR,
    COMMENTONE,
    COMMENTMANY,
};
class Lexel
{
public:
    Lexel(std::istream& _is = std::cin);
    Token nextToken();
    static void setUnorderedSet();
    bool isKeyword(const std::string& word) const;
    bool isOperator(char& c)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/') return true;
        return false;
    }
private:
    std::istream& is;
    int line;
    int column;
    inline static std::unordered_set<std::string> keywords = {
        "char", "short", "int", "long", "float", "double",
        "if", "else", "while", "for", "return", "break",
        "continue", "switch", "case", "default", "do", "goto",
        "auto", "register", "static", "extern", "const", "volatile",
        "signed", "unsigned", "void", "struct", "union", "enum",
        "typedef", "sizeof"
    };
};

