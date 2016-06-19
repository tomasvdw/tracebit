#ifndef TRACEBIT_MOD2
#define TRACEBIT_MOD2

#include <ostream>

// BitTracer using modulo-2 artithmetic

/* Stores a bit as a set of term with each term being a set of variables
 * Because x+x = 0, each term is unique
 * Becasue x.x = x, each factor within each term is unique
 *
 */


typedef __uint128_t varset;

// TraceBit represents a single-bit, either constant or as a inhomogeneous linear equation
// (x2.x3 + x1.x4 + 1)
class TraceBit {

private:

    // each term consist of the factors of distinct variables
    // stores as the bits of uint64
    // variable 0 is reserved for the constant 1
    std::set<varset> terms;


    char dbg[1024];

    void setdbg() {
       std::string s = to_str();
       auto len = s.copy(dbg, 1024);
       dbg[len] = 0;
    }

    void addTerm(varset v) {
        if (terms.find(v) != terms.end())
            terms.erase(v);
        else
            terms.insert(v);

    }

    bool isOne() const
    {
        return terms.size() == 1 && terms.find((varset)1) != terms.end();
    }

public:

    TraceBit(int variable)
    {
        terms.insert(((varset)1) | (((varset)1) << variable));
        setdbg();
    }

    TraceBit() {
        setdbg();
    }


    TraceBit operator&(const TraceBit &other) const {
        TraceBit result;

        // x AND y = xy
        // the result is each combination of the terms of both sides
        for(varset myterm : this->terms)
        {
            for(varset otherterm : other.terms)
            {
                result.addTerm(myterm | otherterm);
            }
        }
        result.setdbg();

        return result;
    }

    TraceBit operator^(const TraceBit &other) const {
        TraceBit result = *this;

        // x XOR y = x + y
        for(varset term : other.terms)
            result.addTerm(term);

        result.setdbg();
        return result;
    }

    TraceBit operator|(const TraceBit &other) const {
        TraceBit result = *this & other;

        for(varset term : other.terms)
            result.addTerm(term);

        for(varset term : this->terms)
            result.addTerm(term);

        result.setdbg();
        return result;
    }

    TraceBit operator~() const {
        TraceBit result = *this;

        // add 1
        result.addTerm(1);
        result.setdbg();
        return result;
    }


    int Value() const {
        if (terms.empty())
            return 0;
        else if (isOne())
            return 1;
        else
            return -1;
    }



    // return the bit as string or as mod2 formula
    std::string to_str() const {
        bool has_plusone = false;

        if (terms.empty())
            return "0";
        else if (isOne())
            return "1";

        std::string result = "{";
        for(varset term : terms)
        {
            if ((term&1)== 0)
                throw "Term does not contain 1!";

            if (term == 1)
                has_plusone = true;
            else
            {
                std::string sterm = "";
                for(int n=1; n < 64; n++)
                    if (term & (((varset)1) << n))
                    {
                        sterm += "x" + std::to_string(n) +".";
                    }

                result += sterm.substr(0,sterm.length()-1) + " + ";
            }

        }
        if (result.length()>0)
            result = result.substr(0, result.length()-3);

        if (has_plusone)
            result = result + " + 1";

        result += "}";
        return result;
    }


};




#endif // TRACEBIT_MOD2

