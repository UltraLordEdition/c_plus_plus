#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Реализуйте этот макрос так, чтобы функция main компилировалась
#define ID1(line)  NUMBER##line
#define ID2(line)   ID1(line)
#define UNIQ_ID     ID2(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}

//Еще пример
/*
#include <stdio.h>
#define f(a,b) a##b         12
#define g(a)   #a           1
#define h(a) g(a)           1

int main()
{
    printf("%s\n", h(f(1, 2))); -> h(12) -> g(12) -> 12
    printf("%s\n", g(f(1, 2))); -> "f(1,2)"
    return 0;
}
*/