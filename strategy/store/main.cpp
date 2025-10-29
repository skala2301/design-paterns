#include <iostream>
#include "lib/Store/store.h"

int main() {
    auto simple = std::make_shared<SimpleShopping>();
    Store store(simple);
    std::cout<<store.shop();
    return 0;
}