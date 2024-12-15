#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace json {

class Json {
public:
    enum class Type {
        JSON_NULL = 0,
        JSON_BOOL,
        JSON_INTEGER,
        JSON_DOUBLE,
        JSON_STRING,
        JSON_ARRAY,
        JSON_OBJECT,
    };

    /// constructors
    Json() = default;
    Json(bool value);
    Json(int32_t value);
    Json(double value);
    Json(const char* value);
    Json(const std::string& value);
    Json(Type type);

    // destructor
    ~Json();

    /// free memory and reset type to null
    void clear();

    void to_array();
    void to_object();

    operator bool() const;
    operator int() const;
    operator double() const;
    operator std::string() const;

    bool as_bool() const;
    int as_int() const;
    double as_double() const;
    std::string as_string() const;

    // is_XXX check
    bool is_null()      const  { return _type == Type::JSON_NULL;       }
    bool is_bool()      const  { return _type == Type::JSON_BOOL;       }
    bool is_int()       const  { return _type == Type::JSON_INTEGER;    }
    bool is_double()    const  { return _type == Type::JSON_DOUBLE;     }
    bool is_string()    const  { return _type == Type::JSON_STRING;     }
    bool is_array()     const  { return _type == Type::JSON_ARRAY;      }
    bool is_object()    const  { return _type == Type::JSON_OBJECT;     }

    /// print json to a string
    std::string str() const;

    /// array indexing access, iff Json is an array
    Json& operator [](int idx);
    const Json& operator [](int idx) const;
    void append(const Json& value);

    /// key indexing access, iff Json is an object
    Json& operator [](const char* key) {
        return operator[](std::string(key));
    }
    Json& operator [](const std::string& key);

    const Json& operator [](const char* key) const {
        return operator [](std::string(key));
    }
    const Json& operator [](const std::string& key) const;

    /// comparison equality
    bool operator ==(const Json& other) const;
    bool operator !=(const Json& other) const {
        return !(*this == other);
    }

private:
    bool check_type(Type type) const {
        return _type == type;
    }

private:
    union Value {
        bool val_bool;
        int32_t val_int;
        double val_double;
        std::string* val_str;
        std::vector<Json>* val_arr;
        std::map<std::string, Json>* val_obj;
    };

    Type _type {Type::JSON_NULL};
    Value _value;
};

inline std::ostream& operator <<(std::ostream& os, const Json& json)
{
    return os << json.str();
}

}  // namespace json
