#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <iostream>
#include <unordered_set>
#include <map>
// 枚举类，用于表示标记的类型
enum class TokenType
{
    IDENTIFIER,  // 标识符，例如变量名或函数名
    INTEGER,     // 整数，例如 123
    FLOAT,       // 浮点数，例如 3.14
    KEYWORD,     // 关键字，例如 IF、WHILE、RETURN 等
    OPERATOR,    // 操作符，例如 +、-、*、/ 等
    PUNCTUATION, // 标点符号，例如 ;、,、() 等
    ENDOFFILE,   // 文件结束标记，用于表示输入流的结束
    ERROR,       // 错误标记
};

// Token 类的声明
class Token
{
private:
    TokenType type;    // 标记类型
    std::string value; // 标记的值
    int line;          // 标记所在的行号
    int column;        // 标记所在的列号
    inline static std::map<TokenType, std::string> typeMap = {
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::INTEGER, "INTEGER"},
        {TokenType::FLOAT, "FLOAT"},
        {TokenType::KEYWORD, "KEYWORD"},
        {TokenType::OPERATOR, "OPERATOR"},
        {TokenType::PUNCTUATION, "PUNCTUATION"},
        {TokenType::ENDOFFILE, "ENDOFFILE"},
        {TokenType::ERROR, "ERROR"}
    };


public:
    // 构造函数
    Token(TokenType _type, std::string _value, int _line, int _column);
    static std::map<TokenType, std::string> getTypeMap();
    // Getter 函数
    TokenType getType() const;
    std::string getValue() const;
    int getLine() const;
    int getColumn() const;

    // Setter 函数
    void setValue(std::string str);

    // 重载输出运算符
    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

#endif // __TOKEN_H__