// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_LAMBDA_CAPTURE_LIST_H
#define CONCEPTRODON_GENERAL_TESTS_LAMBDA_CAPTURE_LIST_H

#include <iostream>

namespace Conceptrodon {
namespace GeneralTests {
namespace LambdaCaptureList {


struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    { std::cout << "Argument copy constructed" << std::endl; }
    
    Argument(Argument && argument)
    { std::cout << "Argument move constructed" << std::endl; }
};

inline void test()
{
    Argument a;

    {
        auto b
        {
            [a=static_cast<Argument&&>(a)]()
            { return true; } ()
        };
    }

    std::cout << std::endl;

    {
        auto b
        {
            [a=static_cast<Argument&>(a)]()
            { return true; } ()
        };
    }

    std::cout << std::endl;

    {
        auto b
        {
            [a=std::forward<Argument>(a)]()
            { return true; } ()
        };
    }

    std::cout << std::endl;

    {
        auto b
        {
            [a=std::forward<Argument&>(a)]()
            { return true; } ()
        };
    }
}

}}}

#endif