//Huey Kolowich
//CS_236

#include "Parser.h"

Parser::Parser(vector<Token*> _tokens)
{
    this->tokens = _tokens;
    this->currentTokenNum = 0;
};

bool Parser::run()
{
    // NEED TO CHECK FOR CASE WITH 0 TOKENS

    numSchemes = 0;
    numFacts = 0;
    numQueries = 0;
    numRules = 0;

    // cout << "Tokens:" << endl;
    // for (unsigned int i = 0; i < tokens.size(); i++)
    // {
    //     tokens[i]->outputToken();
    // }

    // cout << "\n########################################################\n" << endl;

    try {
        datalogProgram = new DatalogProgram();
        
        parseDatalogProgram();

        cout << "Success!" << endl;

        datalogProgram->toString(numSchemes, numFacts, numQueries, numRules);

        delete datalogProgram;
    } catch (Token error) {
        cout << "Failure!" << endl;
        cout << "  ";
        error.outputToken();
    }

    return true;
}

void Parser::checkToken(string _correctType) 
{
    // cout << "Checking token (" << tokens[currentTokenNum]->getTokenType() << ") against (" << _correctType << ")" << endl;

    if (tokens[currentTokenNum]->getTokenType() == "COMMENT")
    {
        while (tokens[currentTokenNum]->getTokenType() == "COMMENT")
        {
        // cout << "Clearing COMMENT" << endl;
        currentTokenNum++;
        }

        if (_correctType == "COMMENT")
        {
            return;
        }

        // cout << "Checking token (" << tokens[currentTokenNum]->getTokenType() << ") against (" << _correctType << ")" << endl;
    } else if (_correctType == "COMMENT")
    {
        return;
    }
    
    if (tokens[currentTokenNum]->getTokenType() == _correctType)
    {
        // cout << "Correct Token found!" << endl;
        currentTokenNum++;
    } else
    {
        // cout << "Incorrect Token found!" << endl;
        throw *tokens[currentTokenNum];
    }
}

void Parser::checkStatus(string _nonterminal)
{
    cout << endl;
    cout << "In " << _nonterminal << " --- Next tokens: " << endl;

    for (unsigned int j = currentTokenNum; j < (currentTokenNum + 5); j++)
    {
        if (j >= tokens.size())
        {
            cout << endl;
            return;
        } else 
        {
            tokens[j]->outputToken();
        }
    }

    cout << endl;
}

void Parser::viewStructure(vector<Token*> _tokens)
{
    for (unsigned int i = 0; i < _tokens.size(); i++)
    {
        tokens[i]->outputToken();
    }
}

void Parser::parseDatalogProgram()
{
    // SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    
    // cout << "parseDatalogProgram:" << endl;

    checkToken("SCHEMES");
    checkToken("COLON");
    parseScheme();
    parseSchemeList();
    checkToken("FACTS");
    checkToken("COLON");
    parseFactList();
    checkToken("RULES");
    checkToken("COLON");
    parseRuleList();
    checkToken("QUERIES");
    checkToken("COLON");
    parseQuery();
    parseQueryList();
    checkToken("EOF");
} 

void Parser::parseSchemeList()
{
    // scheme schemeList | lambda

    // checkStatus("parseSchemeList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        parseScheme();
        parseSchemeList();
    } else 
    {
        return;
    }
}

void Parser::parseFactList()
{
    // fact factList | lambda

    // checkStatus("parseFactList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        parseFact();
        parseFactList();
    } else 
    {
        return;
    }
}

void Parser::parseRuleList()
{
    // rule ruleList | lambda

    // checkStatus("parseRuleList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        parseRule();
        parseRuleList();
    } else 
    {
        return;
    }
}

void Parser::parseQueryList()
{
    // query queryList | lambda
    
    // checkStatus("parseQueryList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        parseQuery();
        parseQueryList();
    } else 
    {
        return;
    }
}

void Parser::parseScheme()
{
    // ID LEFT_PAREN ID idList RIGHT_PAREN
    
    // checkStatus("parseScheme");

    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("LEFT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    parseIdList();
    checkToken("RIGHT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());

    // viewStructure(memory);
    datalogProgram->addPredicate(memory);
    numSchemes++;

    clearMem();
}

void Parser::parseFact()
{
    // ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

    // checkStatus("parseFact");

    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("LEFT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("STRING");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    datalogProgram->addParameter(tokens[(currentTokenNum - 1)]->getTokenInput());
    parseStringList();
    checkToken("RIGHT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("PERIOD");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());

    // viewStructure(memory);
    datalogProgram->addPredicate(memory);
    numFacts++;

    clearMem();
}

void Parser::parseRule()
{
    // headPredicate COLON_DASH predicate predicateList PERIOD

    // checkStatus("parseRule");

    secondaryRulesListLength = 0;

    parseHeadPredicate();
    checkToken("COLON_DASH");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    parsePredicate();
    secondaryRulesListLength++;
    parsePredicateList();
    checkToken("PERIOD");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());

    datalogProgram->addRule(memory, secondaryRulesListLength);
    numRules++;

    clearMem();
}

void Parser::parseQuery()
{
    // predicate Q_MARK
    
    // checkStatus("parseQuery");

    parsePredicate();
    checkToken("Q_MARK");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());

    // viewStructure(memory);
    datalogProgram->addPredicate(memory);
    numQueries++;

    clearMem();
}

void Parser::parseHeadPredicate()
{
    // ID LEFT_PAREN ID idList RIGHT_PAREN

    // checkStatus("parseHeadPredicate");

    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("LEFT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    parseIdList();
    checkToken("RIGHT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
}

void Parser::parsePredicate()
{
    // ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    
    // checkStatus("parsePredicate");

    checkToken("ID");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    checkToken("LEFT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    parseParameter();
    parseParameterList();
    checkToken("RIGHT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
}

void Parser::parsePredicateList()
{
    // COMMA predicate predicateList | lambda
    
    // checkStatus("parsePredicateList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        parsePredicate();
        secondaryRulesListLength++;
        parsePredicateList();
    } else 
    {
        return;
    }
}

void Parser::parseParameterList()
{
    // COMMA parameter parameterList | lambda
    
    // checkStatus("parseParameterList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        parseParameter();
        parseParameterList();
    } else 
    {
        return;
    }
}

void Parser::parseStringList()
{
    // COMMA STRING stringList | lambda
    
    // checkStatus("parseStringList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        checkToken("STRING");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        datalogProgram->addParameter(tokens[(currentTokenNum - 1)]->getTokenInput());
        parseStringList();
    } else 
    {
        return;
    }
}

void Parser::parseIdList()
{
    // COMMA ID idList | lambda
    
    // checkStatus("parseIdList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        checkToken("ID");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
        parseIdList();
    } else 
    {
        return;
    }
}

void Parser::parseParameter()
{
    // STRING | ID | expression

    // checkStatus("parseParameter");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "STRING")
    {
        checkToken("STRING");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    } else if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        checkToken("ID");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    } else if (tokens[currentTokenNum]->getTokenType() == "LEFT_PAREN")
    {
        parseExpression();
    } else 
    {
        throw *tokens[currentTokenNum];
    }
}

void Parser::parseExpression()
{
    // LEFT_PAREN parameter operator parameter RIGHT_PAREN

    // checkStatus("parseExpression");

    checkToken("LEFT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    parseParameter();
    parseOperator();
    parseParameter();
    checkToken("RIGHT_PAREN");
    addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
}

void Parser::parseOperator()
{
    // ADD | MULTIPLY

    // checkStatus("parseOperator");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ADD")
    {
        checkToken("ADD");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    } else if (tokens[currentTokenNum]->getTokenType() == "MULTIPLY")
    {
        checkToken("MULTIPLY");
        addMem(tokens[(currentTokenNum - 1)]->getTokenInput());
    } else 
    {
        throw *tokens[currentTokenNum];
    }
}

void Parser::addMem(string _tokenInput)
{
    // cout << "addMem: " << token->getTokenType() << endl;
    memory.push_back(_tokenInput);
}

void Parser::clearMem()
{
    // cout << "clearMem" << endl;
    memory.clear();
}
