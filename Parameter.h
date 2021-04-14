//Huey Kolowich
//CS_236

#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
private:
    string param;

public:
    Parameter(string _param)
    {
        this->param = _param;
    }
    
    void toString();
    string getString() { return param; }
};

inline void Parameter::toString()
{
    cout << "  " << param;
}

#endif