// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H
#define CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H

#include "conceptrodon/regularities/clxyosteon/copy_lvalue_to_prvalue_while_forward_others.hpp"
#include <iostream>
#include <utility>

#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

namespace Conceptrodon {
namespace Clxyosteon {
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
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing XValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing PRValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing XValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing PRValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(Argument{}));
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