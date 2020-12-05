#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "json/json.h"

namespace xmsg {
using MethodId = uint16_t;
}

template <typename... Args> class Method {
  public:
    using Serializer = std::function<void(Json::Value &value, Args...)>;
    Method(xmsg::MethodId method_id, Serializer serializer) : serializer_(serializer) {
    ~Method() {}

    int operator()(Args... args) {
        Json::Value value;
        serializer_(value, args...);
        std::cout << value.toStyledString() << std::endl;
        return 0;
    }

  private:
    Serializer serializer_;
};

void forward_test() {
    std::vector<int> vec;
    Method<std::string, int, std::vector<int>> method1(
        1, [](Json::Value &value, std::string a, int b, std::vector<int> c) {
            value.append(a);
            value.append(b);
        });

    std::string str("stringvalue");
    int result = method1(str, 101, vec);
}
