#include <iostream>
#include <fstream>
#include "include/Lexer.h"
using namespace std;
int main()
{
    ifstream fs("text.txt");
    Lexel lexel(fs);
    Token token = lexel.nextToken();
    while (token.getType() != TokenType::ENDOFFILE)
    {
        cout<<token.getValue()<<endl;
        token = lexel.nextToken();
    }
    return 0;
}