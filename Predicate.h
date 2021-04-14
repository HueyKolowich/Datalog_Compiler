//Huey Kolowich
//CS_236

#ifndef PREDICATE_H
#define PREDICATE_H

class Predicate
{
private:
    vector<string> inputs;
    
public:
    Predicate(vector<string> _inputs)
    {
        this->inputs = _inputs;
    }
    
    void toString();
};

inline void Predicate::toString()
{
    cout << "  ";

    for (unsigned int j = 0; j < inputs.size(); j++)
    {
        cout << inputs[j];
    }
}

#endif