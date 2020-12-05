#include <iomanip>
#include <iostream>
#include <string>

class StreamDelegate {
  public:
    StreamDelegate(std::ostream &os) : m_stream(os) {}
    ~StreamDelegate() { m_stream << std::endl; }
    StreamDelegate(const StreamDelegate &sd) = delete;
    StreamDelegate &operator=(const StreamDelegate &sd) = delete;

    template <typename T> StreamDelegate &operator<<(T &&s) {
        m_stream << std::forward<T>(s);
        return *this;
    }

  private:
    std::ostream &m_stream;
};

class Stream {
  public:
    Stream(std::ostream &os) : m_stream(os) {}

    template <typename T> StreamDelegate operator<<(T &&s) {
        m_stream << std::forward<T>(s);
        return StreamDelegate(m_stream);
    }

  private:
    std::ostream &m_stream;
};

class MyStyle {
  public:
    MyStyle(const std::string &s) : m_value(s) {}
    MyStyle() {}
    ~MyStyle() {}
    std::string m_value;
};

std::ostream &operator<<(std::ostream &os, const MyStyle &style) {
    os << "mystyle prefix:" << style.m_value << std::endl;
    return os;
}

void test_ioStream() {
    std::cout << "------ " << __func__ << std::endl;
    Stream myout(std::cout);
    myout << "hello "
          << "world"
          << " no new line";

    myout << "new line enter";
    MyStyle style("aastyle");
    myout << style;
}
