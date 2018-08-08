#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int n;
	cin >> n;
	map<string, set<string>> sinonims;
	
	for (int i = 0; i<n; ++i)
	{
		string operation_code;
		cin >> operation_code;
		if (operation_code == "ADD")
		{
			string word1, word2;
			cin >> word1 >> word2;

			sinonims[word1].insert(word2);
			sinonims[word2].insert(word1);
		}
		else if (operation_code == "COUNT")
		{
			string word;
			cin >> word;
			int i=0;
			 
			cout << sinonims[word].size() << endl;
		}
		else if (operation_code == "CHECK")
		{
			string word1, word2;
			cin >> word1 >> word2;

			if (sinonims[word1].count(word2))
			{
				cout << "YES" << endl;
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}
