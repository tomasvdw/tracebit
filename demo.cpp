#include <iostream>

using std::string;
using std::cout;
using std::endl;


#include <stdexcept>
#include <cstring>
#include <fstream>

#include "traceuint.h"


// Let's test a simple hashing function
Tuint32 simple_hash(const Tuint8 *buf, size_t buflength) {
    const Tuint8 *buffer = (const Tuint8*)buf;

    Tuint32 s1 = 1;
    Tuint32 s2 = 0;

    for (size_t n = 0; n < buflength; n++) {
        Tuint32 tt = (Tuint32)buffer[n]; 
        s1 = ((s1 + tt) & 0xFEFE) | (s2 >> 4);
        s2 = ((s2 + s1) & 0xFEFE) | (s1 >> 4);
    }     
    return (s2 << 16) | s1;
}

int main(int argc, char *argv[])
{

    // random input
    Tuint8 input[] = { 0x12, 0x13, 0xdd, 0x21};
    int len = sizeof(input) / sizeof(Tuint8);

    // test without variable replacement
    Tuint32 res = simple_hash(input, len);
    cout << "Hashing result without variables: " << endl
        << "INPUT : ";
    for(int n=0; n < len; n++) cout << input[n];

    cout << endl
        << "OUTPUT: " << res <<  endl << endl;

    
    
    cout << "Replacing bits 4-6 with variables x1-x3" << endl;

    input[0].SetVariable(4, 1);
    input[0].SetVariable(5, 2);
    input[0].SetVariable(6, 3);

    res = simple_hash(input, len);
    cout << "Hashing result with variables: " << endl << "INPUT :";

    for(int n=0; n < len; n++) cout << input[n];

    cout << endl << "OUTPUT: " << res <<  endl;

    return 0;
}

