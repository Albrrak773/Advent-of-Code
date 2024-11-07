#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "Game 100: 1 blue, 13 green, 14 red; 11 green, 11 blue, 7 red; 2 red, 1 blue, 2 green; 10 blue, 15 red";
    cout << stoi(s.substr(5,s.find(":") - 5)) << ".";
    return 0;
}