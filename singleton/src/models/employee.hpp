#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "../lib/db/model.hpp"

class Employee : public Model {
    public:
        Column id         = col("id");
        Column first_name = col("first_name");
        Column last_name  = col("last_name");
        Column salary     = col("salary");

        Employee() : Model("employees") {}
};

#endif