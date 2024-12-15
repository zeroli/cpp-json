#include <gtest/gtest.h>

#include "json.h"

using namespace json;

TEST(Json, test_ctor)
{
    {
        Json json;
        EXPECT_TRUE(json.is_null());
        json.clear();
    }
    {
        Json json(Json::Type::JSON_BOOL);
        EXPECT_TRUE(json.is_bool());
        json.clear();
    }
    {
        Json json = true;
        EXPECT_EQ(true, (bool)json);
        EXPECT_EQ(true, json.as_bool());
        json.clear();
    }
    {
        Json json = 10;
        EXPECT_EQ(10, (int)json);
        EXPECT_EQ(10, json.as_int());
        json.clear();
    }
    {
        Json json{30};
        EXPECT_EQ(30, (int)json);
        EXPECT_EQ(30, json.as_int());
        Json json1(30);
        EXPECT_EQ(json, json1);
        json.clear();
        json1.clear();
    }
    {
        Json json{1.2};
        EXPECT_FLOAT_EQ(1.2, (double)json);
        EXPECT_FLOAT_EQ(1.2, json.as_double());
        json.clear();
    }
    {
        Json json{"hello"};
        EXPECT_EQ("hello", (std::string)json);
        EXPECT_EQ("hello", json.as_string());
        json.clear();
    }
    {
        Json json;
        json.to_array();
        json[0] = true;
        json[1] = 30;
        json[2] = 2.3;
        json[3] = "hello";
        EXPECT_EQ(true, (bool)json[0]);
        EXPECT_EQ(30, (int)json[1]);
        EXPECT_EQ(2.3, (double)json[2]);
        EXPECT_EQ("hello", (std::string)json[3]);

        json.clear();
        EXPECT_TRUE(json.is_null());
        json.to_array();
        json.append(true);
        EXPECT_EQ(true, (bool)json[0]);
    }
    {
        Json json;
        json.to_object();
        json["k1"] = true;
        json["k2"] = 30;
        json["k3"] = 2.3;
        json["k4"] = "hello";
        EXPECT_EQ(true, (bool)json["k1"]);
        EXPECT_EQ(30, (int)json["k2"]);
        EXPECT_EQ(2.3, (double)json["k3"]);
        EXPECT_EQ("hello", (std::string)json["k4"]);

        json.clear();
        EXPECT_TRUE(json.is_null());
    }
}
