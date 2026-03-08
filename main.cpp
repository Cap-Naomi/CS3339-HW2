#include <iostream>
#include <float.h>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;

void print_bits(int start, int length) // each section of IEEE format 
{
    for (int i = length - 1; i >= 0; i--) {

        if ((start >> i) & 1)
            cout << "1";
        else
            cout << "0";
    }
}

union my_float{

    float num;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;

    } raw;
};

void print_IEEE(my_float num)
{
    cout << num.raw.sign << " ";
    print_bits(num.raw.exponent, 8);
    cout << " ";
    print_bits(num.raw.mantissa, 23);
    cout << "\n";
}


int main(int argc, char* argv[]){

    if (argc != 3) {
        cout << "Error: program requires two float inputs\n";
        return 1;
    }

    float threshold; 
    uint32_t bound_exp;
    uint32_t counter_exp;
    my_float bound, counter, threshold_bits;

    bound.num = stof(argv[1]);
    counter.num = stof(argv[2]);

    // storing bit exponent of bound and counter 
    memcpy(&bound_exp, &bound.num, sizeof(bound_exp));
    bound_exp = (bound_exp >> 23) & 0xFF;
    memcpy(&counter_exp, &counter.num, sizeof(counter_exp));
    counter_exp = (counter_exp >> 23) & 0xFF;

    threshold = pow(2, (counter_exp + 24) - 127);
    threshold_bits.num = threshold;

    // overflow calculation complete
    cout << "\nLoop bound:   ";
    print_IEEE(bound); 
    cout << "Loop counter: ";
    print_IEEE(counter);

    if (bound_exp - counter_exp >= 24){ // mantissa has 24 bits of precision 
        cout << "\nWarning: Possible overflow!\n";
        cout << "Overflow threshold:\n";
        cout << "\t" << scientific << threshold << endl;
        cout << "\t";
        print_IEEE(threshold_bits); 
    }
    else{
        cout << "\nThere is no overflow!\n";
    }

    return 0;
}
