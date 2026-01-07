// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_FORWARD_IF_RVALUE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_FORWARD_IF_RVALUE_H

#include "conceptrodon/metafunctions/functivore/forward_if_rvalue.hpp"
#include <iostream>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestForwardIfRvalue {




/******************************************************************************************************/
struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    {
        std::cout << "Argument copy constructed" << std::endl;
    }
    
    Argument(Argument && argument)
    {
        std::cout << "Argument move constructed" << std::endl;
    }
};

inline void check(Argument){}
/******************************************************************************************************/




/******************************************************************************************************/
inline void test()
{
    Argument arg{};

    {
        std::cout << "/**** Passing LValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing XValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing PRValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(Argument{}));
    }
}
/******************************************************************************************************/




}}}}

#endif