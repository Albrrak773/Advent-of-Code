#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

int strToInt(string str);
string wordToNumStr(string str);
int findFirstWordNum(string str);
int findLastWordNum(string str);
string getWordNum(string str, int Sindex);


int main(){
    string line, strNum1, strNum2;
    int total;
    int firstIntIdx, LastIntIdx, firstStrIdx, lastStrIdx; // these hold the index of the first int or the last int...
    fstream file ("input.txt", fstream::in);
    while (file.good())
    {
        getline(file,line);
        // line = 4nineeightseven2
        firstIntIdx = (line.find_first_of("123456789") != string::npos ? line.find_first_of("123456789") : line.length());
        LastIntIdx = (line.find_last_of("123456789") != string::npos ? line.find_last_of("123456789") : 0);
        firstStrIdx = findFirstWordNum(line);
        lastStrIdx = findLastWordNum(line);

        if (firstStrIdx < firstIntIdx )
        {
            strNum1 = getWordNum(line,firstStrIdx);
        }else{
            strNum1 = line[firstIntIdx];
        }

        if (lastStrIdx > LastIntIdx)
        {
            strNum2 = getWordNum(line,lastStrIdx);
        }else{
            strNum2 = line[LastIntIdx];
        }

        cout << "\n========== \n " << "The Line is : " << line<< "\nadding " << strNum1 << " and " << strNum2 << " which is = " << strToInt(strNum1 + strNum2) << "\n==========\n";
        total += strToInt(strNum1 + strNum2);

    }
    
    
    file.close();
    cout << "THE TOTAL IS = " << total;
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

string wordToNumStr(string str){
    if (str == "one"){
        return "1";
    }else if (str == "two"){
        return "2";
    }else if (str == "three"){
        return "3";
    }else if (str == "four"){
        return "4";
    }else if (str == "five"){
        return "5";
    }else if (str == "six"){
        return "6";
    }else if (str == "seven"){
        return "7";
    }else if (str == "eight"){
        return "8";
    }else if (str == "nine"){
        return "9";
    }
    cout  << "\n\n\n\n\n\n FOUND ERRRRRRRRRRRRRRRORRRR \n\n\n\n\n";
    return "-1";
}

int findFirstWordNum(string str){
    string arr[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int firstIdx = 0;
    int min = str.length();
    for (int i = 0; i < 9; i++){

        if (str.find(arr[i]) != string::npos){
            firstIdx = str.find(arr[i]);
            cout << "current Max is : " << min << endl;
            if (firstIdx < min){
                min = firstIdx;
            }
        }
    
    }
    return min;
}
int findLastWordNum(string str){
    // 4nineeightseven2
    // 0123456789
    string arr[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int firstIdx = 0;
    int max = 0;
    for (int i = 0; i < 9; i++){

        if (str.rfind(arr[i]) != string::npos){
            firstIdx = str.rfind(arr[i]);
            cout << "current Max is : " << firstIdx << endl;
            if (firstIdx > max){
                max = firstIdx;
            }
        }
    
    }
    return max;
}

string getWordNum(string str, int Sindex){
    string arr[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string found;
    cout << "I WAS GIVEN THE STRING: " << str << endl;
    cout << "AND THE STARTING INDEX OF = " << Sindex << endl;
    for (int i = 0; i < 9; i++){
        if (str.substr(Sindex, arr[i].length()).find(arr[i]) != string::npos)
        {
            cout << "Currently looking at: " << arr[i] << endl;
            found = str.substr(Sindex,arr[i].length());
        }
    }
    cout << "sending: " << found; 
    found = wordToNumStr(found);

    return found;
}



