#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

int strToInt(string);
int charToInt(char);
int getPositionalVal(char digit,int digitIndex, int strLen);

int main(){

    fstream file ("input.txt", fstream::in);
    string line;
    int total = 0;
    string numStr1;
    string numStr2;
    string numStr;
    while (file.good())
    {
        getline(file,line);
        cout << line << endl;
        int firstIdx = line.find_first_of("123456789");
        int lastIdx = line.find_last_of("123456789");
        numStr1 = line[firstIdx];
        numStr2 = line[lastIdx];
        numStr = numStr1 + numStr2;
        cout << "found the first number (" << line[firstIdx] <<") at index: " << firstIdx << " and the final number is : " << numStr <<  endl;
        cout << "found the last number (" << line[lastIdx] <<") at index: " << lastIdx << " and the final number is : " << numStr << endl;
        total += strToInt(numStr);
    }    
    cout << "THE FINAL TOTAL IS = " << total << endl;
    
    file.close();

    return 0;
}

int strToInt(string str){
    int strLen = str.length();
    int total = 0;
    int positionalVal = 0; // psotional Value means (tens, hundreds, thousands...)
    for (int i = 0; i <= (strLen -1); i++){ // looping over each index of the string (hence strLen - 1)

        positionalVal = (strLen - i - 1); 
        total += pow(10,positionalVal) * (str[i] - '0');

    }
    return total;
}
