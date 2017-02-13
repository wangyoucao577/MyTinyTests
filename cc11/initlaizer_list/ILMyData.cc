#include "ILMyData.h"



ILMyData::ILMyData()
{
}


ILMyData::~ILMyData()
{
}

ILMyData & ILMyData::operator[](initializer_list<int> l) {
    for (auto i = l.begin(); i != l.end(); ++i)
    {
        idx.push_back(*i);
    }
    return *this;
}

ILMyData & ILMyData::operator=(int v) {
    if (!idx.empty()) {
        for (auto i = idx.begin(); i != idx.end(); ++i)
        {
            if (*i + 1 > d.size()) {
                d.resize(*i + 1);
            }
            d[*i] = v;
        }
        idx.clear();
    }
    return *this;
}

void ILMyData::Print() {
    for (auto i = d.begin(); i != d.end(); ++i)
    {
        cout << __func__ << ": " << *i << endl;
    }
    cout << endl;
}