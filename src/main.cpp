#include "../include/multithreading.h"
#include <iostream>

using namespace ReadWriteFile;

int main(int argc, char** argv)
{
    try{
        string s1 = "", s2 = "", s3 = "", s4 = "";
        s1 += argv[1];
        s2 = s2 + argv[2];
        s3 = s3 + argv[3];
        s4 = s4 + argv[4];
        int c1 = stoi(s1);

        // Calling functions which will pass threads to reader and writer files.
        Task t(c1, s2, s3,s4);
        read_write_file(t, c1, s2, s3, s4);

    }
    catch (exception &e){
        cout << "Error: "<< e.what() <<endl;
    
    }
        
    return 0;
}