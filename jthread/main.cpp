#include "Manager.h"

int main() {
    Manager::instance().add_work(1);
    Manager::instance().add_work(3);
    Manager::instance().add_work(2);
    Manager::instance().finish();
}