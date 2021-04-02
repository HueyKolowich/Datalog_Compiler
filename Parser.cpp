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

    cout << "Parser RUN:" << endl;

    cout << "Tokens:" << endl;
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        tokens[i]->outputToken();
    }

    cout << "\n########################################################\n" << endl;

    try {
        parseDatalogProgram();

        cout << "Run Sucess!" << endl;
    } catch (Token error) {
        cout << "Run Failure!" << endl;
    }

    return true;
}

void Parser::checkToken(string _correctType) 
{
    cout << "Checking token (" << tokens[currentTokenNum]->getTokenType() << ") against (" << _correctType << ")" << endl;

    if (tokens[currentTokenNum]->getTokenType() == "COMMENT")
    {
        while (tokens[currentTokenNum]->getTokenType() == "COMMENT")
        {
        cout << "Clearing COMMENT" << endl;
        currentTokenNum++;
        }

        if (_correctType == "COMMENT")
        {
            return;
        }

        cout << "Checking token (" << tokens[currentTokenNum]->getTokenType() << ") against (" << _correctType << ")" << endl;
    } else if (_correctType == "COMMENT")
    {
        return;
    }
    
    if (tokens[currentTokenNum]->getTokenType() == _correctType)
    {
        cout << "Correct Token found!" << endl;
        currentTokenNum++;
    } else
    {
        cout << "Incorrect Token found!" << endl;
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

void Parser::parseDatalogProgram()
{
    // SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    
    cout << "parseDatalogProgram:" << endl;

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

    checkStatus("parseSchemeList");

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

    checkStatus("parseFactList");

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

    checkStatus("parseRuleList");

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
    
    checkStatus("parseQueryList");

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
    
    checkStatus("parseScheme");

    checkToken("ID");
    checkToken("LEFT_PAREN");
    checkToken("ID");
    parseIdList();
    checkToken("RIGHT_PAREN");
}

void Parser::parseFact()
{
    // ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

    checkStatus("parseFact");

    checkToken("ID");
    checkToken("LEFT_PAREN");
    checkToken("STRING");
    parseStringList();
    checkToken("RIGHT_PAREN");
    checkToken("PERIOD");
}

void Parser::parseRule()
{
    // headPredicate COLON_DASH predicate predicateList PERIOD

    checkStatus("parseRule");

    parseHeadPredicate();
    checkToken("COLON_DASH");
    parsePredicate();
    parsePredicateList();
    checkToken("PERIOD");
}

void Parser::parseQuery()
{
    // predicate Q_MARK
    
    checkStatus("parseQuery");

    parsePredicate();
    checkToken("Q_MARK");
}

void Parser::parseHeadPredicate()
{
    // ID LEFT_PAREN ID idList RIGHT_PAREN

    checkStatus("parseHeadPredicate");

    checkToken("ID");
    checkToken("LEFT_PAREN");
    checkToken("ID");
    parseIdList();
    checkToken("RIGHT_PAREN");
}

void Parser::parsePredicate()
{
    // ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    
    checkStatus("parsePredicate");

    checkToken("ID");
    checkToken("LEFT_PAREN");
    parseParameter();
    parseParameterList();
    checkToken("RIGHT_PAREN");
}

void Parser::parsePredicateList()
{
    // COMMA predicate predicateList | lambda
    
    checkStatus("parsePredicateList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        parsePredicate();
        parsePredicateList();
    } else 
    {
        return;
    }
}

void Parser::parseParameterList()
{
    // COMMA parameter parameterList | lambda
    
    checkStatus("parseParameterList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
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
    
    checkStatus("parseStringList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        checkToken("STRING");
        parseStringList();
    } else 
    {
        return;
    }
}

void Parser::parseIdList()
{
    // COMMA ID idList | lambda
    
    checkStatus("parseIdList");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "COMMA")
    {
        checkToken("COMMA");
        checkToken("ID");
        parseIdList();
    } else 
    {
        return;
    }
}

void Parser::parseParameter()
{
    // STRING | ID | expression

    checkStatus("parseParameter");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "STRING")
    {
        checkToken("STRING");
    } else if (tokens[currentTokenNum]->getTokenType() == "ID")
    {
        checkToken("ID");
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

    checkStatus("parseExpression");

    checkToken("LEFT_PAREN");
    parseParameter();
    parseOperator();
    parseParameter();
    checkToken("RIGHT_PAREN");
}

void Parser::parseOperator()
{
    // ADD | MULTIPLY

    checkStatus("parseOperator");

    checkToken("COMMENT");

    if (tokens[currentTokenNum]->getTokenType() == "ADD")
    {
        checkToken("ADD");
    } else if (tokens[currentTokenNum]->getTokenType() == "MULTIPLY")
    {
        checkToken("MULTIPLY");
    } else 
    {
        throw *tokens[currentTokenNum];
    }
}
