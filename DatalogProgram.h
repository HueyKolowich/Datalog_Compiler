//Huey Kolowich
//CS_236

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include<vector>
#include<algorithm>

#include"Rule.h"
#include"Predicate.h"
#include"Parameter.h"

class DatalogProgram
{
private:
    vector<Predicate> predicates;
    vector<Rule> rules;
    vector<Parameter> parameters;

    vector<string> stringParameters;
    bool isUnique;

public:
    void toString(unsigned int, unsigned int, unsigned int, unsigned int);

    void addRule(vector<string>, unsigned int);
    void addPredicate(vector<string>);
    void addParameter(string);

    void sortParams();
};

inline void DatalogProgram::toString(unsigned int _numSchemes, unsigned int _numFacts, unsigned int _numQueries, unsigned int _numRules)
{
    cout << "Schemes(" << _numSchemes << "):" << endl;
    for (unsigned int i = 0; i < _numSchemes; i++)
    {
        predicates[i].toString();
        cout << endl;
    }

    cout << "Facts(" << _numFacts << "):" << endl;
    for (unsigned int j = (_numSchemes); j < (_numFacts + _numSchemes); j++)
    {
        predicates[j].toString();
        cout << endl;
    }
    
    cout << "Rules(" << _numRules << "):" << endl;
    for (unsigned int l = 0; l < _numRules; l++)
    {
        rules[l].toString();
        cout << endl;
    }

    cout << "Queries(" << _numQueries << "):" << endl;
    for (unsigned int k = (_numFacts + _numSchemes); k < (_numQueries + _numFacts + _numSchemes); k++)
    {
        predicates[k].toString();
        cout << endl;
    }

    sortParams();
    cout << "Domain(" << stringParameters.size() << "):" << endl;
    for (unsigned int z = 0; z < stringParameters.size(); z++)
    {
        cout << "  ";
        cout << stringParameters[z];
        cout << endl;
    }
}  

inline void DatalogProgram::sortParams()
{
    // cout << "parameters.size(): " << parameters.size() << endl;
    for (unsigned int y = 0; y < parameters.size(); y++)
    {
        // cout << "parameters[y]->getString(): " << parameters[y]->getString() << endl;
        stringParameters.push_back(parameters[y].getString());
    }

    // cout << "stringParameters.size(): " << stringParameters.size() << endl;

    sort(stringParameters.begin(), stringParameters.end());
}

inline void DatalogProgram::addRule(vector<string> inputs, unsigned int _secondaryListLength)
{
    rules.push_back(Rule(inputs));
}

inline void DatalogProgram::addPredicate(vector<string> inputs)
{
    predicates.push_back(Predicate(inputs));
    // cout << "size: " << tokens.size() << endl;
}

inline void DatalogProgram::addParameter(string input)
{
    isUnique = true;
    for (unsigned int c = 0; c < parameters.size(); c++)
    {
        if (parameters[c].getString() == input)
        {
            isUnique = false;
        }
    }

    if (isUnique) 
    {
        parameters.push_back(Parameter(input));
    }
}

#endif