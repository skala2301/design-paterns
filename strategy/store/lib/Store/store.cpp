#include <string>
#include <iostream>
#include <memory>
#include "store.h"


IShopping::IShopping(): caption("Basic shopping."){

};

IShopping::~IShopping() {}

std::string IShopping::shop() {  // Should be virtual, and needs return statement
    return this->caption;
}

std::string SimpleShopping::shop() {
    std::string caption = "Simple Shopping.";
    //std::cout<<caption<<std::endl;
    return caption;
};



std::string ComplexShopping::shop() {
    std::string caption = "Complex Shopping.";
    //std::cout<<caption;
    return caption;
};


Store::Store(std::shared_ptr<IShopping> shopping) : shopping(shopping)
{};

std::string Store::shop(){
    return shopping->shop();
};

