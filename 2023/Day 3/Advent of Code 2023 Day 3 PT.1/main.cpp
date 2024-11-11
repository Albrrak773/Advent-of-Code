#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
void printFile();
int getSum(int* linesSchema[] , string lines[], int numofLines);
bool isSymbol(char c);
int getOffSet(string numBlock);

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    int numofLines = 0;
    string line, currLine, nextLine, prevLine;
    string sybmols = "#/*-+&$=@%";
    string digits = "1234567890";
    fstream file ("input.txt", fstream::in);

    int symbolIndex;

    while (file.good()){
    
        getline(file,line);
        numofLines++;
        
    }

    file.seekg(0); // go back to the start of the file.
    string* lines = new string[numofLines];
    int** linesSchema = new int*[numofLines]; // pointer to a pointer 
    for (int i = 0; i < numofLines; i++){
        getline(file,lines[i]);
        linesSchema[i] = new int[numofLines]; // this is where we declare the second dimntion of the array lineSchema.
    }
    for (int i = 0; i < numofLines; i++)
    {
        for (int j = 0; j < numofLines; j++)
        {
            linesSchema[i][j] = 0;
        }
        
    }
    
    for (int i = 0; i < numofLines; i++)
    {
        
        if (i == 0){
            currLine = lines[i];
            symbolIndex = currLine.find_first_of(sybmols);
            while (symbolIndex != string::npos)
            {
                
                linesSchema[i][symbolIndex - 1] = 1;
                linesSchema[i][symbolIndex + 1] = 1;
                for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
                {
                    linesSchema[i + 1][symbolIndex + j] = 1;
                }
                symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
            }
            continue;
        }
        if (i == numofLines - 1){
            currLine = lines[i];
            
            symbolIndex = currLine.find_first_of(sybmols);
            while (symbolIndex != string::npos)
            {
                
                linesSchema[i][symbolIndex - 1] = 1;
                linesSchema[i][symbolIndex + 1] = 1;
                for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
                {
                    linesSchema[i - 1][symbolIndex + j] = 1;
                }
                symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
            }
            continue;
        }

        currLine = lines[i];

        symbolIndex = currLine.find_first_of(sybmols);
        while (symbolIndex != string::npos)
        {
            linesSchema[i][symbolIndex - 1] = 1;
            linesSchema[i][symbolIndex + 1] = 1;
            for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
            {
                linesSchema[i - 1][symbolIndex + j] = 1;
                linesSchema[i + 1][symbolIndex + j] = 1;
            }
            
            symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
        }
    }

    file.close();
    //                  THIS IS THE MASK OF 1's AND 0's 
    // for (int i = 0; i < numofLines; i++)
    // {
    //     for (int j = 0; j < numofLines; j++)
    //     {
    //         if (linesSchema[i][j] == 1)
    //         {
    //             printf("\033[42m%d\033[0m", linesSchema[i][j]);
    //         }else{
    //         cout << linesSchema[i][j];
    //         }
    //     }
    //     cout << '\n';
    // }
    long tot =  getSum(linesSchema , lines, numofLines);
    cout << "\nTHE FINAL TOTAL IS: " << tot<< endl;
// ------------------------------------------------------------
    for (int i = 0; i < numofLines; ++i) {
        delete[] linesSchema[i];
    }
    delete[] linesSchema; 
    delete[] lines;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto time = duration.count();
    printf("\n\033[34mTime Taken: %dms\033[0m",time);
    return 0;
}


int getSum(int* linesSchema[] , string lines[], int numofLines){
    int found = 0;
    string currLine, numBlock;
    int numIndex = 0, ofSet = 0;
    long long total = 0;
    string digits = "1234567890";
    int* currLineSchema;
    for (int i = 0; i < numofLines; i++)
    {
        for (int j = 0; j < numofLines; j++)
        {
            if (linesSchema[i][j] == 1)
            {
                printf("\033[42m%c\033[0m", lines[i][j]);
            }else{
            cout << lines[i][j];
            }
        }
        cout << " :" << i << "\n";
    }
    cout << "\n\n\n\n\n\n";
    for (int i = 0; i < numofLines; i++)
    {
        currLine = lines[i];
        numIndex = 0;
        numIndex = currLine.find_first_of(digits, numIndex);
        while (numIndex != string::npos)
        {
            ofSet = getOffSet(currLine.substr(numIndex)); // this checks the third character --> (XX#) and if the it's a sybmol then set the offSet to not include it (2)
            numBlock = currLine.substr(numIndex, ofSet);
            for (int j = numIndex; j < (numIndex + ofSet); j++)
            {
                if (linesSchema[i][j] == 1)
                {
                    total += stoi(numBlock);
                    printf("Adding the numbe Block \033[42m%s\033[0m, Line: %d, total: %d", numBlock.c_str(), i, total);
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                printf("Adding the numbe Block \033[41m%d\033[0m, Line: %d, total: %d", stoi(numBlock), i, total);
            }
            found = 0;
            cout << '\n';

            
            numIndex = currLine.find_first_of(digits, (numIndex + ofSet + 1));
        }   
    }


    return total;

}

bool isSymbol(char c){
    char symbols[11] = {'#', '/', '*', '-', '+', '&', '$', '=', '@', '%', '.'};

    for (int i = 0; i < 11; i++)
    {
        if (c == symbols[i])
        {
            return true;
        }
    }
    return false;
    
    
}

int getOffSet(string numBlock){

    for (int i = 0; i < numBlock.length() - 1; i++)
    {
        if (isSymbol(numBlock[i]))
        {
            return i;
        }
        
    }
    return numBlock.length();
    
}


