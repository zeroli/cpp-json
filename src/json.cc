#include "json.h"

#include <cassert>
#include <cmath>

namespace json {
Json::Json(bool value)
 : _type(Type::JSON_BOOL)
{
    _value.val_bool = value;
}

Json::Json(int32_t value)
 : _type(Type::JSON_INTEGER)
{
    _value.val_int = value;
}

Json::Json(double value)
 : _type(Type::JSON_DOUBLE)
{
    _value.val_double = value;
}

Json::Json(const char* value)
 : _type(Type::JSON_STRING)
{
    _value.val_str = new std::string(value);
}

Json::Json(const std::string& value)
 : _type(Type::JSON_STRING)
{
    _value.val_str = new std::string(value);
}

Json::Json(Type type)
    : _type(type)
{
    switch (_type) {
    case Type::JSON_NULL:
        break;
    case Type::JSON_BOOL:
        _value.val_bool = false;
        break;
    case Type::JSON_INTEGER:
        _value.val_int = 0;
        break;
    case Type::JSON_DOUBLE:
        _value.val_double = 0.;
        break;
    case Type::JSON_STRING:
        _value.val_str = new std::string();
        break;
    case Type::JSON_ARRAY:
        _value.val_arr = new std::vector<Json>();
        break;
    case Type::JSON_OBJECT:
        _value.val_obj = new std::map<std::string, Json>();
        break;
    default:
        assert(0 && "unknown type");
    }
}

Json::~Json()
{
    /// user need call clear to manually free memory
}

void Json::clear()
{
    switch (_type) {
    case Type::JSON_NULL:
        break;
    case Type::JSON_BOOL:
        _value.val_bool = false;
        break;
    case Type::JSON_INTEGER:
        _value.val_int = 0;
        break;
    case Type::JSON_DOUBLE:
        _value.val_double = 0.;
        break;
    case Type::JSON_STRING:
        delete _value.val_str;
        break;
    case Type::JSON_ARRAY:
        for (auto& v : *(_value.val_arr)) {
            v.clear();
        }
        delete _value.val_arr;
        _value.val_arr = nullptr;
        break;
    case Type::JSON_OBJECT:
        for (auto& kv : *(_value.val_obj)) {
            kv.second.clear();
        }
        delete _value.val_obj;
        _value.val_obj = nullptr;
        break;
    default:
        assert(0 && "unknown type");
    }
    _type = Type::JSON_NULL;
}

Json::operator bool() const
{
    if (!check_type(Type::JSON_BOOL)) {
        assert(0 && "json is not bool type");
    }
    return _value.val_bool;
}

Json::operator int() const
{
    if (!check_type(Type::JSON_INTEGER)) {
        assert(0 && "json is not integer type");
    }
    return _value.val_int;
}

Json::operator double() const
{
    if (!check_type(Type::JSON_DOUBLE)) {
        assert(0 && "json is not double type");
    }
    return _value.val_double;
}

Json::operator std::string() const
{
    if (!check_type(Type::JSON_STRING)) {
        assert(0 && "json is not string type");
    }
    return *_value.val_str;
}

bool Json::as_bool() const
{
    return (bool)(*this);
}

int Json::as_int() const
{
    return (int)(*this);
}

double Json::as_double() const
{
    return (double)(*this);
}

std::string Json::as_string() const
{
    return (std::string)(*this);
}

std::string Json::str() const
{
    std::ostringstream oss;

    return oss.str();
}

void Json::to_array()
{
    if (check_type(Type::JSON_ARRAY)) {
        return;
    }
    clear();
    *this = Json(Type::JSON_ARRAY);
}

void Json::to_object()
{
    if (check_type(Type::JSON_OBJECT)) {
        return;
    }
    clear();
    *this = Json(Type::JSON_OBJECT);
}

Json& Json::operator [](int idx)
{
    assert(check_type(Type::JSON_ARRAY));

    auto size = _value.val_arr->size();
    _value.val_arr->resize(std::max(size, (size_t)idx+1));
    return (*_value.val_arr)[idx];
}

const Json& Json::operator [](int idx) const
{
    assert(check_type(Type::JSON_ARRAY));

    return _value.val_arr->at(idx);
}

void Json::append(const Json& value)
{
    assert(check_type(Type::JSON_ARRAY));
    operator [](_value.val_arr->size()) = value;
}

Json& Json::operator [](const std::string& key)
{
    assert(check_type(Type::JSON_OBJECT));

    return (*_value.val_obj)[key];
}

const Json& Json::operator [](const std::string& key) const
{
    assert(check_type(Type::JSON_ARRAY));

    return _value.val_obj->at(key);
}

bool Json::operator ==(const Json& other) const
{
    if (_type != other._type) {
        return false;
    }

    switch (_type) {
    case Type::JSON_NULL:
        return true;
    case Type::JSON_BOOL:
        return _value.val_bool == other._value.val_bool;
    case Type::JSON_INTEGER:
        return _value.val_int == other._value.val_int;
    case Type::JSON_DOUBLE:
        return _value.val_double == other._value.val_double;
    case Type::JSON_STRING:
        return *(_value.val_str) == *(other._value.val_str);
    case Type::JSON_ARRAY:  // pointer equal?
        return _value.val_arr == other._value.val_arr;
    case Type::JSON_OBJECT:
        return _value.val_obj == other._value.val_obj;
    default:
        assert(0 && "unknown type");
    }
    return false;
}
}  // namespace json
