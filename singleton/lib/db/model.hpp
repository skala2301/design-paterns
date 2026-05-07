#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <pqxx/pqxx>

// Represents a column in a table
struct Column {
    std::string table;
    std::string name;

    std::string qualified() const { return table + "." + name; }
    std::string placeholder(int n) const { return "$" + std::to_string(n); }
};

// Base class for all models
class Model {
    protected:
        std::string m_table;
    public:
        Model(const std::string& table) : m_table(table) {}
        const std::string& table() const { return m_table; }

        Column col(const std::string& name) const {
            return Column{m_table, name};
        }
};

// Query builder
class Query {
    private:
        std::string m_select;
        std::string m_from;
        std::string m_where;
        std::string m_set;
        std::string m_type; // "SELECT" or "UPDATE"
        pqxx::params m_params;
        int m_param_count{0};

    public:
        // SELECT id FROM employees
        Query& select(const std::string& col) {
            m_type = "SELECT";
            m_select = col;
            return *this;
        }

        Query& from(const Model& model) {
            m_from = model.table();
            return *this;
        }

        Query& update(const Model& model) {
            m_type = "UPDATE";
            m_from = model.table();
            return *this;
        }

        template<typename T>
        Query& where(const Column& col, const T& value) {
            m_param_count++;
            m_where = col.name + " = $" + std::to_string(m_param_count);
            m_params.append(value);
            return *this;
        }

        template<typename T>
        Query& set(const Column& col, const T& value) {
            m_param_count++;
            m_set = col.name + " = $" + std::to_string(m_param_count);
            m_params.append(value);
            return *this;
        }

        std::string sql() const {
            if (m_type == "SELECT")
                return "SELECT " + m_select + " FROM " + m_from + " WHERE " + m_where;
            if (m_type == "UPDATE")
                return "UPDATE " + m_from + " SET " + m_set + " WHERE " + m_where;
            return "";
        }

        const pqxx::params& params() const { return m_params; }
};

#endif