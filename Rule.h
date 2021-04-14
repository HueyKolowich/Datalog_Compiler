//Huey Kolowich
//CS_236

#ifndef RULE_H
#define RULE_H

class Rule
{
private:
    vector<string> inputs;
    unsigned int iterator; 

public:
    Rule(vector<string> _inputs)
    {
        this->inputs = _inputs;
    }
    
    void toString();
};

inline void Rule::toString()
{   
    // cout << "\nCalled Rule::toString()!" << endl;
    
    iterator = 0;
    
    while ((iterator < inputs.size()) && (inputs[iterator] != ":-"))
    {
        iterator++;
    }
    
    cout << "  ";

    for (unsigned int i = 0; i < inputs.size(); i++)
    {
        if (i == iterator) { cout << " "; }
        if (i == (iterator + 1)) { cout << " "; }
        cout << inputs[i];
    }

    // cout << "Finished Rule::toString()!\n" << endl;
}

#endif