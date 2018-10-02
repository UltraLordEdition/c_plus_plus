#include <iostream>
#include <string>
#include <deque>
#include <stack>

using namespace std;

int main()
{
    int x;
    cin >> x;

    int n;
    cin >> n;

    deque<string> formula;
    stack<string> stack_opr;
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
            cin >> symbol;
            if (stack_opr.size() != 0)
            {
                if ((stack_opr.top() == "-") && (symbol == "*" || symbol == "/") ||
                    (stack_opr.top() == "+") && (symbol == "*" || symbol == "/"))
                {
                    formula.push_front("(");
                    formula.push_back(")");
                }
            }
            stack_opr.push(symbol);
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