// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_UNIT_TESTS_TEST_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H
#define CONCEPTRODON_FUNYOSTEON_UNIT_TESTS_TEST_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H

#include "conceptrodon/regularities/funyosteon/copy_lvalue_to_prvalue_while_forward_others.hpp"
#include <iostream>
#include <utility>

#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

namespace Conceptrodon {
namespace Funyosteon {
namespace UnitTests {
namespace TestCopyLvalueToRvalueWhileForwardOthers {




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

    /**** Argument ****/

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing XValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing PRValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing XValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing PRValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument ****/

    {
        std::cout << "/**** std::forward<Argument>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument>: Passing XValue ****/" << std::endl;
        check(std::forward<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument>: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument>(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** std::forward<Argument&>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(std::forward<Argument&>(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(std::forward<Argument&>(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** std::forward<Argument&&>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument&&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&&>: Passing XValue ****/" << std::endl;
        check(std::forward<Argument&&>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&&>: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument&&>(Argument{}));
    }
}
/******************************************************************************************************/




}}}}

#undef BLANKET
#undef CHECK_VIABILITY

#endif