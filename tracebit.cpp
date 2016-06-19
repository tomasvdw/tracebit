
#include <string>

#include "traceuint.h"






#ifdef TEST_TRACEBIT
#include <cassert>
using std::endl;


void test8(Tuint8 t1, Tuint8 t2) {
    assert((t1 & t2).value() == (t1.value() & t2.value()));
    assert((t1 | t2).value() == (t1.value() | t2.value()));
    assert((t1 ^ t2).value() == (t1.value() ^ t2.value()));
    assert((t1 <<2).value() == (unsigned char)(t1.value() << 2));
    assert((t1 >>2).value() == (unsigned char)(t1.value() >> 2));

    assert((t1 + t2).value() == (unsigned char)(t1.value() + t2.value()));
}
void test32(Tuint32 t1, Tuint32 t2) {
    assert((t1 & t2).value() == (t1.value() & t2.value()));
    assert((t1 | t2).value() == (t1.value() | t2.value()));
    assert((t1 ^ t2).value() == (t1.value() ^ t2.value()));
    assert((t1 <<2).value() == (unsigned long)(t1.value() << 2));
    assert((t1 >>2).value() == (unsigned long)(t1.value() >> 2));

    assert((t1 + t2).value() == (unsigned long)(t1.value() + t2.value()));


}

int main() {

    test8(Tuint8(0xde), Tuint8(0x24));
    test8(Tuint8(0xff), Tuint8(0x01));
    test8(Tuint8(0xff), Tuint8(0x00));
    test8(Tuint8(0xaa), Tuint8(0xaa));

    test32(Tuint32(0xffffffff), Tuint32(0x1));
    test32(Tuint32(0x124311aa), Tuint32(0xaa001122));

    std::cout << "Tests ok" << std::endl;
}

#endif
