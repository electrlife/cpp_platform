#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#if 0
template <typename T> class Visitor {
  public:
    virtual void visit(T *visit) = 0;
};

class VisitorToken {
  public:
    virtual ~VisitorToken() = default;
};

class BasicVisitable {
  public:
    virtual void accept(VisitorToken *visitor) = 0;
};

template <typename T> class Visitable : public BasicVisitable {
  public:
    void accept(VisitorToken *visitor_token) override {
        Visitor<T> *visitor = dynamic_cast<Visitor<T> *>(visitor_token);
        visitor->visit(static_cast<T *>(this));
    }
};

class Dog : public Visitable<Dog> {
  public:
    void Clamp() {}
};

class Fish : public Visitable<Fish> {
  public:
    void Swiming() {}
};

template <typename... Args>
class MultiVisitor : public VisitorToken, public Visitor<Args>... {
  public:
    using Visitor<Args>::visit...;
};

class VisitorA : public MultiVisitor<Dog, Fish> {
  public:
    void visit(Dog *dog) override {
        std::cout << "Visit dog started" << std::endl;
    };

    void visit(Fish *fish) override {
        std::cout << "Visit fish started" << std::endl;
    };
};

int main(int argc, const char *argv[]) {
    std::unique_ptr<Dog> dog = std::make_unique<Dog>();
    std::unique_ptr<VisitorToken> visitor = std::make_unique<VisitorA>();
    dog->accept(visitor.get());

    return 0;
}

#else

template <typename T> class Visitor {
  public:
    virtual void visit(T *) = 0;
};

class VisitorToken {
  public:
    virtual ~VisitorToken() = default;
};

class BasicVisitable {
  public:
    virtual void accept(VisitorToken *visitor_token) = 0;
};

template <typename T> class Visitable : public BasicVisitable {
  public:
    void accept(VisitorToken *visitor_token) override {
        Visitor<T> *visitor = dynamic_cast<Visitor<T> *>(visitor_token);
        visitor->visit(static_cast<T *>(this));
    }
};

template <typename... Visitors>
class MultiVisitor : public VisitorToken, public Visitor<Visitors>... {
  public:
    using Visitor<Visitors>::visit...;
};

class Sphere : public Visitable<Sphere> {
  public:
};

class Polygon : public Visitable<Polygon> {
  public:
};

class Serializer : public MultiVisitor<Sphere, Polygon> {
  public:
    void visit(Sphere *sphere) override {
        std::cout << "serialize sphere" << std::endl;
    }

    void visit(Polygon *polygon) override {
        std::cout << "serialize polygon" << std::endl;
    }
};

class Drawer : public MultiVisitor<Polygon> {
    void visit(Polygon *polygon) override {
        std::cout << "draw polygon" << std::endl;
    }
};

void demo_test() {
    std::unique_ptr<Polygon> polygon = std::make_unique<Polygon>();
    std::unique_ptr<VisitorToken> serialize_visitor = std::make_unique<Serializer>();
    polygon->accept(serialize_visitor.get());

    std::unique_ptr<VisitorToken> draw_visitor = std::make_unique<Drawer>();
    polygon->accept(draw_visitor.get());
}

#endif
