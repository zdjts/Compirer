#include "../include/Lexer.h"

bool Lexel::isKeyword(const std::string &word) const
{
    return keywords.count(word) > 0;
}

Lexel::Lexel(std::istream &_is) : is(_is)
{
    line = 1;
    column = 0;
}
Token Lexel::nextToken()
{
    State state = START;
    char c;
    std::string buffer;
    TokenType tokenType;
    int startLine = line;
    int startColumn = column;
    Token error_token(TokenType::ERROR, "", line, column);
    while (is.get(c))
    {
        column++;
        if (isspace(c))
        {
            if (c == '\n')
            {
                line++;
                column = 0;
                startLine = line;
                startColumn = column;
            }
            if (state == START)
            {
                continue;
            }
        }
        char prev = ' ';
        if (c == '/')
        {
            char next;
            is.get(next);
            if (next == '/')
            {
                state = COMMENTONE;
                column++;
            }
            else if (next == '*')
            {
                state = COMMENTMANY;
                column++;
            }
            else
            {
                is.putback(next);
            }
        }
        switch (state)
        {
        case State::START:
            if (std::isalpha(c))
            {
                state = IDENTIFIER;
                buffer += c;
                tokenType = TokenType::IDENTIFIER;
            }
            else if (std::isdigit(c))
            {
                state = NUMBER;
                buffer += c;
                tokenType = TokenType::INTEGER;
            }
            else if (std::ispunct(c))
            {
                state = SYMBOL;
                buffer += c;
                tokenType = TokenType::PUNCTUATION;
                if (isOperator(c))
                {
                    tokenType = TokenType::OPERATOR;
                }
            }
            else
            {
                tokenType = TokenType::ERROR;
                state = ERROR;
            }
            break;
        case State::COMMENTONE:
            while (is.get(c))
            {
                if (c == '\n')
                {
                    line++;
                    column = 0;
                    state = START;
                    break;
                }
            }
            startLine = line;
            startColumn = column;
            break;
        case State::COMMENTMANY:
            while (is.get(c))
            {
                column++;
                if (prev == '*' && c == '/')
                {
                    state = START;
                    break;
                }
                if (c == '\n')
                {
                    line++;
                    column = 0;
                }
                prev = c;
            }
            startColumn = column;
            startLine = line;
            break;
        case State::IDENTIFIER:
            if (std::isalpha(c) || c == '_')
            {
                buffer += c;
            }
            else
            {
                is.putback(c);
                column--;
                state = ACCEPT;
                if (isKeyword(buffer))
                {
                    tokenType = TokenType::KEYWORD;
                }
            }
            break;
        case State::NUMBER:
            if (c == '.')
            {
                state = FLOAT;
                buffer += c;
                tokenType = TokenType::FLOAT;
                break;
            }
            else if (std::isdigit(c))
            {
                buffer += c;
            }
            else
            {
                is.putback(c);
                column--;
                state = ACCEPT;
            }
            break;
        case State::FLOAT:
            if (isdigit(c))
            {
                buffer += c;
            }
            else
            {
                is.putback(c);
                column--;
                state = ACCEPT;
            }
            break;
        case State::SYMBOL:
            is.putback(c);
            column--;
            state = ACCEPT;
            break;
        case State::ACCEPT:
            column--;
            is.putback(c);
            return Token(tokenType, buffer, startLine, startColumn);
        case State::ERROR:
            is.putback(c);
            column--;
            error_token.setValue(buffer);
            std::cout << error_token << std::endl;
            return error_token;
        default:
            break;
        }
    }
    if (buffer == "")
        return Token(TokenType::ENDOFFILE, "", startLine, startColumn);
    else
        return Token(tokenType, buffer, startLine, startColumn);
}