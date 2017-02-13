#include "ILPeople.h"



ILPeople::ILPeople()
{
}


ILPeople::~ILPeople()
{
}

ILPeople::ILPeople(initializer_list<pair<string, Gender>> l) {
    
    for (auto i = l.begin(); i != l.end(); ++i)
    {
        data.push_back(*i);
    }
}