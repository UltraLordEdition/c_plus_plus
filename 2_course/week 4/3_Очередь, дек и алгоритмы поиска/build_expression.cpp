#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main()
{
    int x;
    cin >> x;

    int n;
    cin >> n;

    deque<string> formula;
    string symbol;
    
    if (n < 1)
    {
        cout << x << endl;
    }
    else
    {
        formula.push_back(to_string(x));            
        for (int i = 0; i < n; ++i)
        {
            formula.push_front("(");
            formula.push_back(")");
            cin >> symbol;
            cin >> x;
            formula.push_back(" " + symbol + " " + to_string(x));
        }
        for (auto it : formula)
        {
            cout << it;
        }        
    }
    
    return 0;
}