template <typename T> class Base {
  public:
    void bar() {}
};

template <typename T> class Derived : Base<T> {
  public:
    void foo() {
        Base<T>::bar(); // calls external bar() or error
    }
};

void test_template_specialization() {
    Derived<int> de;
    de.foo();
}
