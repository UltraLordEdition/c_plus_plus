#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<char, int> BuildCharCounters(const string& words)
{
	map<char, int> glossary;

	for (const char& s : words)
	{
		++glossary[s];
	}
	return glossary;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string first_word, second_word;
		cin >> first_word >> second_word;
		if (BuildCharCounters(first_word) == BuildCharCounters(second_word))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}