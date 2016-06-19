#ifndef TRACEBIT
#define TRACEBIT


#include <set>
#include <iostream>


class TraceBit;

#define ZERO TraceBit()
#define ONE TraceBit(0)

#define MIN(x,y) ((x) < (y) ? (x) : (y))

#include "tracebit_mod2.h"
//#include "tracebit_opcount.h"

template<int N, typename T>
class TraceUint;

typedef TraceUint<8, unsigned char> Tuint8;
typedef TraceUint<16, unsigned short> Tuint16;
typedef TraceUint<32, unsigned int> Tuint32;
typedef TraceUint<64, unsigned long long> Tuint64;

/* Template that defines a 1 to 8 byte integer using tracing bits
 * The type of tracing is defined by the include above
 * N = the number of bits
 * T = the underlying unit type
 */
template<int N, typename T>
class TraceUint {


public:
    TraceBit bits[N];

    TraceUint()
    {
    }

    // Initialize from the underlying uint type
    TraceUint(const T& value)
    {
        for(int n =0; n < N; n++)
        {
            if (((value >> n) & 1) == 1)
                bits[n] = ONE;
            else
                bits[n] = ZERO;
        }
    }


    // Returns the underlying uint value
    // Only possible if this contains no variable references
    T Value() const {
        T res = 0;
        for(int n=0; n < N; n++)
        {
            int v = bits[n].Value();
            if (v == 1)
                res |= (1 << n);
            else if (v <0)
                throw "Can't create value from expression";
        }
        return res;
    }

    // Casting
    // We're doing this unchecked

    operator Tuint8() const {
        Tuint8 result;
        for(int n=0; n < 8; n++)
            result.bits[n] = bits[n];
        return result;
    }
    operator Tuint16() const {
        Tuint16 result;

        for(int n=0; n < MIN(16,N); n++)
            result.bits[n] = bits[n];
        return result;
    }
    operator Tuint32() const {
        Tuint32 result;

        for(int n=0; n < MIN(32,N); n++)
            result.bits[n] = bits[n];
        return result;
    }
    operator Tuint64() const {
        Tuint64 result;

        for(int n=0; n < MIN(64,N); n++)
            result.bits[n] = bits[n];
        return result;
    }

    
    // replaces a bit with a variable
    // variable should be 1-15 refered to as x1 to x15
    void SetVariable(int bit, int variable)
    {
        bits[bit] = TraceBit(variable);
    }


    // define bitwise operators

    TraceUint operator&(const TraceUint &other) const {
        TraceUint result = TraceUint();
        for(int n=0; n < N; n++)
            result.bits[n] = this->bits[n] & other.bits[n];

        return result;
    }

    TraceUint operator|(const TraceUint &other) const {
        TraceUint result = TraceUint();
        for(int n=0; n < N; n++)
            result.bits[n] = this->bits[n] | other.bits[n];

        return result;
    }

    TraceUint operator^(const TraceUint &other) const {
        TraceUint result = TraceUint();
        for(int n=0; n < N; n++)
            result.bits[n] = this->bits[n] ^ other.bits[n];

        return result;
    }

    TraceUint operator>>(const int shift) const {
        TraceUint result = TraceUint();
        for(int n=0; n < (N-shift); n++)
            result.bits[n] = this->bits[n + shift];

        return result;
    }

    TraceUint operator<<(const int shift) const {
        TraceUint result = TraceUint();
        for(int n=shift; n < N; n++)
            result.bits[n] = this->bits[n - shift];

        return result;
    }

    TraceUint operator~() const {
        TraceUint result = TraceUint();
        for(int n=0; n < N; n++)
        {
            result.bits[n] = ~this->bits[n];
        }
        return result;
    }

    TraceUint operator+(const TraceUint &other) const {
        TraceUint result = TraceUint();

        // we need to apply the binary adder
        TraceBit carry = ZERO;
        for(int n=0; n < N; n++)
        {
            result.bits[n] = (this->bits[n] ^ other.bits[n])
                    ^ carry;
            carry = (this->bits[n] & other.bits[n])
                    | (carry & (this->bits[n] ^ other.bits[n]));
        }
        return result;
    }



};

// Stream implementation
// Creates a binary-string with the content,
// embedding formulas where needed
template<int N, typename T>
std::ostream& operator<<(std::ostream& os, const TraceUint<N, T>& obj)
{
    for(int n=N-1; n >=0; n--)
    {
        os <<  obj.bits[n].to_str();
    }

    return os;
}



// helper function for direct packing
static void tracebit_pack(Tuint32 *target, const Tuint8 * source)
{
    for(int n=0;n<8; n++)
        target->bits[n] = source[3].bits[n];
    for(int n=0;n<8; n++)
        target->bits[n+8] = source[2].bits[n];
    for(int n=0;n<8; n++)
        target->bits[n+16] = source[1].bits[n];
    for(int n=0;n<8; n++)
        target->bits[n+24] = source[0].bits[n];
}

static void tracebit_unpack(Tuint8 *target, const Tuint32 source)
{
    for(int n=0;n<8; n++)
        target[3].bits[n] = source.bits[n];
    for(int n=0;n<8; n++)
        target[2].bits[n] = source.bits[n+8];
    for(int n=0;n<8; n++)
        target[1].bits[n] = source.bits[n+16];
    for(int n=0;n<8; n++)
        target[0].bits[n] = source.bits[n+24];
}



#endif // TRACEBIT
//#define TEST_TRACEBIT
