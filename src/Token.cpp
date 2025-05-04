#include "../include/Token.h"

// 构造函数
Token::Token(TokenType _type, std::string _value, int _line, int _column)
    : type(_type), value(_value), line(_line), column(_column)
{
}

std::map<TokenType, std::string> Token::getTypeMap()
{
    return Token::typeMap;
}

// Getter 函数实现
TokenType Token::getType() const
{
    return type;
}

std::string Token::getValue() const
{
    return value;
}

int Token::getLine() const
{
    return line;
}

int Token::getColumn() const
{
    return column;
}

// Setter 函数实现
void Token::setValue(std::string str)
{
    value = str;
}

// 重载输出运算符
std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << "[line = " << token.line
       << ", column = " << token.column
       << ", type = " << token.typeMap[token.type] // 假设 type 是 enum class，需要转成 int 或自定义输出
       << ", value = " << token.value << "]";
    return os;
}