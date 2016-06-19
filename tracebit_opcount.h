#ifndef TRACEBIT_OPCOUNT
#define TRACEBIT_OPCOUNT


/* Bit tracer that only counts the total operations on each bit
 *
 *
 */
class TraceBit {

private:

    // total logical operations for this bit
    unsigned long long op_count = 0;


    char dbg[1024];

    void setdbg() {
       // std::string s = to_str();
       // auto len = s.copy(dbg, 1024);
       // dbg[len] = 0;
    }


public:

    TraceBit(int variable)
    {

    }

    TraceBit() {
        setdbg();
    }


    TraceBit operator&(const TraceBit &other) const {
        TraceBit result;

        result.op_count = this->op_count + other.op_count + 1;
        return result;
    }

    TraceBit operator^(const TraceBit &other) const {
        TraceBit result;

        result.op_count = this->op_count + other.op_count + 1;
        return result;
    }

    TraceBit operator|(const TraceBit &other) const {
        TraceBit result;

        result.op_count = this->op_count + other.op_count + 1;
        return result;
    }

    TraceBit operator~() const {
        TraceBit result;

        result.op_count = this->op_count + 1;
        return result;
    }

    int Value() {
        return -1;
    }


    std::string to_str() const {
        std::string result = "{" + std::to_string(op_count) + "}";

        return result;
    }


};







#endif // TRACEBIT_OPCOUNT

