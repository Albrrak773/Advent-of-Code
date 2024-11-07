#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int getGamePower(string str);
int main()
{
    int total = 0;
    fstream file ("input.txt", fstream::in);
    string line;
    while (file.good()){
        
        getline(file, line);
        total += getGamePower(line);
    }
    cout << "The total is: " << total << endl;
    file.close();

    return 0;
}

int getGamePower(string game){
    game = game.substr(game.find(" ", game.find(" ") +1));
    string cube; 
    string cubeCulor;
    int cubeCount;
    int redMax = 0, greenMax = 0, blueMax = 0;
    int startingIdx = 0;
    int found;
    while (found != string::npos){ 

        found = game.find_first_of(",;", startingIdx); 
        cube = game.substr(startingIdx + 1, (found - (startingIdx + 1)));
        cubeCulor = cube.substr(cube.find(" ") + 1);
        cubeCount = stoi(cube.substr(0, cube.find(" ")));
        
        cout << "currently checking --> " << cube << endl;

        if (cubeCulor == "blue")
        {
            if (cubeCount > blueMax)
            {
                blueMax = cubeCount;
            }
            
        }
        if (cubeCulor == "red")
        {
            if (cubeCount > redMax)
            {
                redMax = cubeCount;
            }
            
        }
        if (cubeCulor == "green"){
            if (cubeCount > greenMax){
                greenMax = cubeCount;
            }
        }

        if (found != string::npos)
            startingIdx = found + 1;

    }
    
    return (redMax * greenMax * blueMax);
}