#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

int getSum(int** mask , string lines[], int numOfLines);
bool isSymbol(char c);
int getOffSet(string numBlock);
int getNumLines(const char* fileName);
int** createBlankMask(int size);
void printMask(int** mask, int size);
void printMaskedOn(string* arr, int** mask, int size, bool withLines = true);
string* fileToArray(const char* fileName, int numLines  = -1);
int** createMask(int** mask,string* lines, int numOfLines);
int** createIdArray(string* lines, int numofLines);
int getIdCount(string* lines, int numOfLines);
bool isArray2(int* arr);


int main(){

    auto start = std::chrono::high_resolution_clock::now();
    int numOfLines = 0;
    string line, currLine;
    string digits = "1234567890";
    int symbolIndex;


    numOfLines = getNumLines("input.txt");
    string* lines = fileToArray("input.txt", numOfLines); // lines[]
    int** mask = createBlankMask(numOfLines); // blank mask[][]
    mask = createMask(mask, lines, numOfLines); // filled mask[][] 

    // printMask(mask, numOfLines);
    // printMaskedOn(lines, mask, numOfLines, 0);
 
    long tot =  getSum(mask , lines, numOfLines);
    std::cout << "\nTHE FINAL TOTAL IS: " << tot<< endl;

// ------------------------------------------------------------
    for (int i = 0; i < numOfLines; ++i) {
        delete[] mask[i];
    }

    delete[] mask; 
    delete[] lines;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto time = duration.count();
    printf("\n\033[34mTime Taken: %dms\033[0m",time);
    return 0;
}


int getSum(int** mask , string lines[], int numOfLines){
    int found = 0, numIndex = 0, ofSet = 0;
    string currLine, numBlock;
    long long total = 0;
    string digits = "1234567890";
    int idCount = getIdCount(lines, numOfLines);
    int** idArray = createIdArray(lines, numOfLines);
    int idNumber;

    
    for (int i = 0; i < numOfLines; i++) // loops over each lines in the file.
    {
        currLine = lines[i];
        numIndex = 0;
        numIndex = currLine.find_first_of(digits, numIndex);
        while (numIndex != string::npos) // loops over a single line for each numberBlock
        {
            ofSet = getOffSet(currLine.substr(numIndex)); 
            numBlock = currLine.substr(numIndex, ofSet);
            for (int j = numIndex; j < (numIndex + ofSet); j++) // loops over the number to see if anyone of them is matches the mask --> [252]
            {
                idNumber = mask[i][j];
                if (idNumber != 0)
                {
                    // cout << "\nAdding the number block: " << numBlock << " TO ID: " << (idNumber) << endl;  
                    for (int f = 0; f < 6; f++) // this loops over each element in the array idArray[i] --> {0,0,0,0,0,0}
                    {
                        if (idArray[idNumber - 1][f] == 0)
                        {
                            idArray[idNumber - 1][f] = stoi(numBlock);
                            break;
                        }
                        
                    }
                    break;
                }
            }

            numIndex = currLine.find_first_of(digits, (numIndex + ofSet + 1));
        }   
    }
    for (int i = 0; i < idCount; i++)
    {
        cout << "{";
        for (size_t j = 0; j < 6; j++)
        {
            cout << idArray[i][j] << ", ";
        }
        cout << "} : " << i << "\n";
        
    }
    
    for (int i = 0; i < idCount; i++)
    {
        if (isArray2(idArray[i]))
        {
            cout << "Multiplying " << idArray[i][0] << " * " << idArray[i][1] << endl;
            total += (idArray[i][0] * idArray[i][1]);
        }
        
    }
    

    for (size_t i = 0; i < idCount; i++)
    {
        delete[] idArray[i];
    }
    delete[] idArray;
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

int** createBlankMask(int size){
    int** mask = new int*[size];
    for (int i = 0; i < size; i++){
        mask[i] = new int[size]; 
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            mask[i][j] = 0;
        }
        
    }
    return mask;
}

int** createMask(int** mask,string* lines, int numOfLines){
    string currLine, sybmols = "*";
    int symbolIndex = 0;
    long long int _ID = 0;
    for (int i = 0; i < numOfLines; i++)
    {

        if (i == 0){
            currLine = lines[i];
            symbolIndex = currLine.find_first_of(sybmols);
            while (symbolIndex != string::npos)
            {
                _ID++;
                mask[i][symbolIndex - 1] = _ID;
                mask[i][symbolIndex + 1] = _ID;
                for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
                {
                    mask[i + 1][symbolIndex + j] = _ID;
                }
                symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
            }
            continue;
        }
        if (i == numOfLines - 1){
            currLine = lines[i];
            
            symbolIndex = currLine.find_first_of(sybmols);
            while (symbolIndex != string::npos)
            {
                _ID++;
                mask[i][symbolIndex - 1] = _ID;
                mask[i][symbolIndex + 1] = _ID;
                for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
                {
                    mask[i - 1][symbolIndex + j] = _ID;
                }
                symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
            }
            continue;
        }

        currLine = lines[i];
        symbolIndex = currLine.find_first_of(sybmols);
        while (symbolIndex != string::npos)
        {
            _ID++;
            mask[i][symbolIndex - 1] = _ID;
            mask[i][symbolIndex + 1] = _ID;
            for (int j = -1; j < 2; j++) // this goes {index -1, index, index + 1}
            {
                mask[i - 1][symbolIndex + j] = _ID;
                mask[i + 1][symbolIndex + j] = _ID;
            }
            
            symbolIndex = currLine.find_first_of(sybmols,symbolIndex + 1);
        }
    }

    return mask;
}

void printMask(int** mask, int size){
    cout << "I GOT SIZE : " << size << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mask[i][j] != 0)
            {
                printf("\033[42m%d\033[0m", mask[i][j]);
            }else{
            cout << mask[i][j];
            }
        }
        cout << '\n';
    }
}

string* fileToArray(const char* fileName, int numLines){

    if (numLines == 0)
    {
        numLines = getNumLines(fileName);
    }
    string line;
    string* arr = new string[numLines];
    fstream file (fileName, std::fstream::in);
    for (size_t i = 0; i < numLines; i++)
    {
        getline(file, line);
        arr[i] = line;
    }
            
    file.close();
    return arr;
}

int getNumLines(const char* fileName){

    char c;
    int total = 1;
    fstream file (fileName, std::fstream::in);
    
    while (file.good())
    {
        file.get(c);
        if (c == '\n')
        {
            total++;
        }
        
    }
    file.close();
    return total;
}

void printMaskedOn(string* arr, int** mask, int size, bool withLines){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mask[i][j] != 0)
            {
                printf("\033[42m%c\033[0m", arr[i][j]);
            }else{
            cout << arr[i][j];
            }
        }
        if (withLines)
            cout << " :" << i << "\n";
        else  
            cout << '\n';
        
        
    }
    cout << "\n\n\n";
}

int** createIdArray(string* lines, int numofLines){
    int idCount = getIdCount(lines, numofLines);
    int** idArray = new int*[idCount];
    for (int i = 0; i < idCount ; i++)
    {
        idArray[i] = new int[6];
    }
    for (size_t i = 0; i < idCount; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            idArray[i][j] = 0;
        }
    }

    return idArray;
    
}

int getIdCount(string* lines, int numOfLines){

    string currLine;
    int nextIndex, total = 0;
    for (int i = 0; i < (numOfLines - 1); i++)
    {
        nextIndex = 0;
        currLine = lines[i];

        nextIndex = currLine.find_first_of("*", nextIndex);
        while (nextIndex != string::npos)
        {
            total += 1;
            nextIndex = currLine.find_first_of("*", nextIndex + 1);
        }
        
        
    }
    return total;
}

bool isArray2(int* arr){
    int total = 0;
    for (int i = 0; i < 6; i++)
    {
        if (arr[i] != 0)
        {
            total++;
        }
        
    }
    if (total == 2)
    {
        return true;
    }else{
        return false;
    }
    
    
}

