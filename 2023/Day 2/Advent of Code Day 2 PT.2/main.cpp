#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool isCountValid(string str);
bool isGameValid(string str);
int main()
{
    int total = 0;
    fstream file ("input.txt", fstream::in);
    string line;
    while (file.good()){
        
        getline(file, line);
        if (isGameValid(line))
        {
            total += stoi(line.substr(5,line.find(":") - 5)) ; 
        }    
    }
    cout << total << endl;
    file.close();

    return 0;
}

bool isCountValid(string str){
    string colur = str.substr(str.find(" ") + 1);
    if (colur == "green"){
        if (stoi(str.substr(0, str.find(" "))) > 13){ 
            cout << "FOUND A FALSE COUNT AT COLUR (green) GIVEN THE STRING <" << str << ">";
            return false;
        }
        return true;
    }
    else if (colur == "blue"){
        if (stoi(str.substr(0, str.find(" "))) > 14){
            cout << "FOUND A FALSE COUNT AT COLUR (blue) GIVEN THE STRING <" << str << ">";
            return false;
        }
        return true;

    }
    else if (colur == "red"){
        if (stoi(str.substr(0, str.find(" "))) > 12){
            cout << "FOUND A FALSE COUNT AT COLUR (red) GIVEN THE STRING <" << str << ">";
            return false;
        }
        return true;
    }
    cout << "\nERROOR got a wrong input \nThe string <" << str << "> " << "\nTHE colur checked <" << colur << ">\n";
    return false;
}

bool isGameValid(string game){
    const string gameOrignal = game;
    game = game.substr(game.find(" ", game.find(" ") +1));
    string cube; // hold a count and a colur i.e (12 red)
    int startingIdx = 0;
    int found;
    while (found != string::npos){ // looping over each cube i.e(12 red) checking if it's valid

        found = game.find_first_of(",;", startingIdx); 
        cube = game.substr(startingIdx + 1, (found - (startingIdx + 1)));

        if (!isCountValid(cube)){
            cout << " --- > " << gameOrignal.substr(0, gameOrignal.find(":")) << endl;
            return false;
        }
        // cout <<  cube << "." << endl << "substring index = " << startingIdx + 1 << "/" << game.length() << endl;
        if (found != string::npos)
            startingIdx = found + 1;

    }
    
    return true;
}