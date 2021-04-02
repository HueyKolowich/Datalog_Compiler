//Huey Kolowich
//CS_236

#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>

#include"Token.h"

class Parser
{
private:
    vector<Token*> tokens;

    int currentTokenNum;

    void checkToken(string);
    void checkStatus(string);

    void parseDatalogProgram();

    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();

    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();

    void parseHeadPredicate();
    void parsePredicate();

    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();

    void parseParameter();
    void parseExpression();
    void parseOperator();

public:
    Parser(vector<Token*>);
    // virtual ~Parser() {};

    bool run();
};

#endif
