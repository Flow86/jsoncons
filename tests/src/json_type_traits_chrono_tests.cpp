// Copyright 2020 Daniel Parker
// Distributed under Boost license

//#include <catch/catch.hpp>
//#include <jsoncons/json.hpp>
#include <chrono>
#include <string>
#include <type_traits>

//using namespace jsoncons;

namespace ns {

    template <class T>
    struct A
    {
        static void f()
        {
            static_assert(std::false_type::value, "f not implemented");
        }
    };
/*
    template<class T>
    struct A<std::chrono::duration<T>>
    {
        static void f()
        {
        }
    };
*/
    template <>
    struct A<std::chrono::seconds>
    {
        static void f()
        {
        }
    };
    template <>
    struct A<std::string>
    {
        static void f()
        {
        }
    };
}

void test_chrono()
{
    //A<std::chrono::seconds>::f();
    ns::A<std::string>::f();
}

#if 0
TEST_CASE("json_type_traits chron tests")
{
    SECTION("test 1")
    {
        uint64_t time = 1000;

        json j(time, semantic_tag::epoch_time);

        auto val = j.as<std::chrono::seconds>(); 

        CHECK(val.count() == std::chrono::seconds::rep(time));
    }
    SECTION("test 2")
    {
        double time = 1000.100;

        json j(time, semantic_tag::epoch_time);

        auto val = j.as<std::chrono::duration<double>>();

        CHECK(val.count() == time);
    }
}
#endif