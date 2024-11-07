    int total = 0;
    fstream file ("input.txt", fstream::in);
    string line;
    while (file.good()){
        
        getline(file, line);
        if (isGameValid(line))
        {
            // total += line[5] - '0'; WRONG!!!!
        }    
    }
    cout << total << endl;
    file.close();