#ifndef STORE
#define STORE

#include <memory>

class IShopping{
    protected:
        std::string caption;
    public:
        IShopping();

        virtual ~IShopping();

        virtual std::string shop();
};

class SimpleShopping: public IShopping{
    public:
        std::string shop() override;
};

class ComplexShopping: public IShopping{
    public:
        std::string shop() override;
};

class BasicShopping: public IShopping{
    
};


class Store {
    private:
        std::shared_ptr<IShopping> shopping;

    public: 
        Store(std::shared_ptr<IShopping> shopping);
        std::string shop();
};


#endif