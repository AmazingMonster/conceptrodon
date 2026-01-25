// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_UNIT_TESTS_TEST_MOVE_RVALUE_WHILE_COPY_LVALUE_H
#define CONCEPTRODON_FUNYOSTEON_UNIT_TESTS_TEST_MOVE_RVALUE_WHILE_COPY_LVALUE_H

#include "conceptrodon/regularities/funyosteon/move_rvalue_while_copy_lvalue.hpp"
#include <iostream>
#include <utility>

namespace Conceptrodon {
namespace Funyosteon {
namespace UnitTests {
namespace TestMoveRvalueWhileCopyLvalue {




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
        std::cout << "/**** ::move_rvalue_while_copy_lvalue: Passing LValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** ::move_rvalue_while_copy_lvalue: Passing XValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** ::move_rvalue_while_copy_lvalue: Passing PRValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(Argument{}));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing LValue ****/" << std::endl;
        check(std::forward<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing XValue ****/" << std::endl;
        check(std::forward<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument>(Argument{}));
    }
}
/******************************************************************************************************/




}}}}

#endif