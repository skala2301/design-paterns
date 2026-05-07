#include <iostream>
#include <pqxx/pqxx>
#include <cstdlib>

#include "env_extractor.hpp"
#include "employee.hpp"

std::string get_db_url() {
    load_env(".env");

    const char* env_pgdb   = std::getenv("PGDB");
    const char* env_pghost = std::getenv("PGHOST");
    const char* env_pgport = std::getenv("PGPORT");
    const char* env_pguser = std::getenv("PGUSER");
    const char* env_pgpass = std::getenv("PGPASS");

    if (!env_pgdb || !env_pghost || !env_pgport || !env_pguser || !env_pgpass)
        throw std::runtime_error("Missing one or more required DB environment variables");

    return std::format("postgresql://{}:{}@{}:{}/{}",
        env_pguser,
        env_pgpass,
        env_pghost,
        env_pgport,
        env_pgdb
    );
}


int main(int, char *argv[])
{
  // (Normally you'd check for valid command-line arguments.)
  char const *const name = argv[1];

  std::string db_url = get_db_url();
  pqxx::connection cx{db_url};
  pqxx::work tx{cx};

  Employee emp;

  // SELECT id FROM employees WHERE first_name = $1
  Query select_query;
  select_query
      .select(emp.id.name)
      .from(emp)
      .where(emp.first_name, std::string(name));

  int employee_id = tx.query_value<int>(select_query.sql(), select_query.params());
  std::cout << "Updating employee #" << employee_id << '\n';

  // UPDATE employees SET salary = salary + 1 WHERE id = $1
  Query update_query;
  update_query
      .update(emp)
      .set(emp.salary, employee_id)   // you'd extend this for expressions
      .where(emp.id, employee_id);

  tx.exec(update_query.sql(), update_query.params()).no_rows();

  tx.commit();
}