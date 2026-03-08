#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <bitset>
using namespace std;

void print_IEEE(float val){

    uint32_t bits;
    memcpy(&bits, &val, sizeof(bits));
    bitset<32> b(bits);

    cout << b[31] << " ";  

    for (int i = 30; i >= 23; i--) 
        cout << b[i];

    cout << " ";

    for (int i = 22; i >= 0; i--) 
        cout << b[i];

    cout << endl;
}


int main(int argc, char* argv[]){

    if (argc != 3) {
        cout << "Error: program requires two float inputs\n";
        return 1;
    }

    float bound = stof(argv[1]);
    float counter = stof(argv[2]);

    float threshold; 
    int bound_exp;
    int counter_exp;

    // storing bit exponent of bound and counter 
    memcpy(&bound_exp, &bound, sizeof(bound_exp));
    bound_exp = (bound_exp >> 23) & 0xFF;
    memcpy(&counter_exp, &counter, sizeof(counter_exp));
    counter_exp = (counter_exp >> 23) & 0xFF;

    // overflow calculation complete
    cout << "\nLoop bound:   ";
    print_IEEE(bound); 
    cout << "Loop counter: ";
    print_IEEE(counter);

    // int expDiff = bound_exp - counter_exp;

    if (bound_exp - counter_exp >= 24){ // mantissa has 24 bits of precision 
        cout << "\nWarning: Possible overflow!\n";
        cout << "Overflow threshold:\n";

        threshold = pow(2, (counter_exp + 24) - 127);
        cout << "\t" << scientific << threshold << endl;
        cout << "\t";
        print_IEEE(threshold); 
    }
    else{
        cout << "\nThere is no overflow!\n";
    }

    return 0;
}
