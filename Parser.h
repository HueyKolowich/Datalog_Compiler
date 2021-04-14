//Huey Kolowich
//CS_236

#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>

#include"Token.h"
#include"DatalogProgram.h"

class Parser
{
private:
    vector<Token*> tokens;
    vector<string> memory;
    DatalogProgram* datalogProgram;

    unsigned int currentTokenNum;
    unsigned int secondaryRulesListLength;
    unsigned int numSchemes;
    unsigned int numFacts;
    unsigned int numQueries;
    unsigned int numRules;

    void checkToken(string);
    void checkStatus(string);
    void viewStructure(vector<Token*>);

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

    void addMem(string);
    void clearMem();

public:
    Parser(vector<Token*>);
    // virtual ~Parser() {};

    bool run();
};

#endif
