#include <string>
#include <iostream>
#include <array>

extern void forward_test();
extern void demo_test();
extern void test_virtualInheritance();
extern void test_ioStream();
extern void test_outputStream();
extern void test_template_specialization();

int main(int argc, const char *argv[]) {
    // test_outputStream();
    test_template_specialization();
    // test_ioStream();
    // test_virtualInheritance();
    // forward_test();
    // demo_test();
    return 0;
}
