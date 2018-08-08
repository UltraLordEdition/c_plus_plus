#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>


using namespace std;

struct Lecture
{
	string title;
	int duration;
	string author;
};

void PrintLecture(const Lecture& lecture)
{
	cout << "Title: " << lecture.title <<
		", duration: " << lecture.duration <<
		", author: " << lecture.author << "\n";
}

void PrintCourse(const vector<Lecture>& lectures)
{
	for (const Lecture& lecture : lectures)
	{
		PrintLecture(lecture);
	}
}

int main()
{
	Lecture lecture1;
	lecture1.title = "00P";
	lecture1.duration = 5400;
	lecture1.author = "Anton";

	Lecture lecture2 = { "01P", 5400, "Anton" };

	PrintLecture({ "00P",5400,"Anton" });
}