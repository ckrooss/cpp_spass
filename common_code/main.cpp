#include <iostream>
#define whoami()                                                                                                                                     \
    printf(__PRETTY_FUNCTION__);                                                                                                                     \
    printf("\n")

class CommonUtil {
  public:
    CommonUtil() {
        whoami();
    }

    virtual ~CommonUtil() {
        whoami();
    }

    virtual void a() {
        std::terminate();
    }
};

class SpecialUtil : public CommonUtil {
  public:
    SpecialUtil() {
        whoami();
    }

    ~SpecialUtil() {
        whoami();
    }

    void a() override {
        whoami();
    }
    void b() {
        whoami();
    }
};

class CommonManager {
  public:
    CommonManager(CommonUtil& util) : m_util(util) {
        whoami();
    }

    virtual ~CommonManager() {
        whoami();
    }

    void func_a() {
        whoami();
        m_util.a();
    }

    CommonUtil& m_util;
};

class SpecialManager : public CommonManager {
  public:
    SpecialManager() : CommonManager(m_util) {
        whoami();
        int* leak = new int[25];
        printf("%d", leak[25]);
    }

    ~SpecialManager() {
        whoami();
    }

    void func_b() {
        whoami();
        m_util.a();
        m_util.b();
    }

    SpecialUtil m_util;
};

int main() {
    SpecialManager* s = new SpecialManager();
    s->func_a();
    s->func_b();
    delete s;
}
