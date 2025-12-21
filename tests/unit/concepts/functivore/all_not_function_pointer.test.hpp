// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H

#include "conceptrodon/concepts/functivore/all_not_function_pointer.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestAllNotFunctionPointer {




/******************************************************************************************************/
/**** functions ****/
inline int fun_0(int, double){ return 0; }
inline int fun_1(int, double...){ return 0; }
inline int fun_2(int const, double...){ return 0; }
inline int fun_3(int const, double&...){ return 0; }

/**** function pointers ****/
inline auto FunP_0 { fun_0 };
inline auto FunP_1 { fun_1 };
inline auto FunP_2 { fun_2 };
inline auto FunP_3 { fun_3 };

inline auto FunAddr_0 { &fun_0 };
inline auto FunAddr_1 { &fun_1 };
inline auto FunAddr_2 { &fun_2 };
inline auto FunAddr_3 { &fun_3 };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun_0(int, double){ return 0; }
    inline int fun_1(int, double...){ return 0; }
    inline int fun_2(int const, double...){ return 0; }
    inline int fun_3(int const, double&...){ return 0; }

    inline int gun_0(int const, double&...) const { return 0; }
    inline int gun_1(int const, double&...) const volatile { return 0; }
    inline int gun_2(int const, double&...) const volatile noexcept { return 0; }
    inline int gun_3(int const, double&...) const volatile & noexcept { return 0; }
    inline int gun_4(int const, double&...) const volatile && noexcept { return 0; }
};

/**** function objects ****/
struct FO_0
{
    int operator()(int, double){ return 0; }
};

struct FO_1
{
    int operator()(int, double...){ return 0; }
};

struct FO_2
{
    int operator()(int const, double...){ return 0; }
};

struct FO_3
{
    int operator()(int const, double&...){ return 0; }
};

struct FO_4
{
    int operator()(int const, double&...) const { return 0; }
};

struct FO_5
{
    int operator()(int const, double&...) const volatile { return 0; }
};

struct FO_6
{
    int operator()(int const, double&...) const volatile noexcept { return 0; }
};

struct FO_7
{
    int operator()(int const, double&...) const volatile & noexcept { return 0; }
};

struct FO_8
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
};

/**** lambda expressions ****/
inline auto Lambda_0
{
    [](int, double)
    { return 0; }
};

inline auto Lambda_1
{
    [](int, double...)
    { return 0; }
};

inline auto Lambda_2
{
    [](int const, double...)
    { return 0; }
};

inline auto Lambda_3
{
    [](int const, double&...)
    { return 0; }
};

inline auto Lambda_4
{
    [](int const, double&...) noexcept
    { return 0; }
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert
(
    ! AllNotFunctionPointer
    <
        decltype(FunP_0),
        decltype(fun_0),
        decltype(fun_1),
        decltype(fun_2),
        decltype(fun_3),
        decltype(&Tester::fun_0),
        decltype(&Tester::fun_1),
        decltype(&Tester::fun_2),
        decltype(&Tester::fun_3),
        decltype(&Tester::gun_0),
        decltype(&Tester::gun_1),
        decltype(&Tester::gun_2),
        decltype(&Tester::gun_3),
        decltype(&Tester::gun_4),
        FO_0,
        FO_1,
        FO_2,
        FO_3,
        FO_4,
        FO_5,
        FO_6,
        FO_7,
        FO_8,
        decltype(Lambda_0),
        decltype(Lambda_1),
        decltype(Lambda_2),
        decltype(Lambda_3),
        decltype(Lambda_4)
    >
);

static_assert
(
    AllNotFunctionPointer
    <
        decltype(fun_0),
        decltype(fun_1),
        decltype(fun_2),
        decltype(fun_3),
        decltype(&Tester::fun_0),
        decltype(&Tester::fun_1),
        decltype(&Tester::fun_2),
        decltype(&Tester::fun_3),
        decltype(&Tester::gun_0),
        decltype(&Tester::gun_1),
        decltype(&Tester::gun_2),
        decltype(&Tester::gun_3),
        decltype(&Tester::gun_4),
        FO_0,
        FO_1,
        FO_2,
        FO_3,
        FO_4,
        FO_5,
        FO_6,
        FO_7,
        FO_8,
        decltype(Lambda_0),
        decltype(Lambda_1),
        decltype(Lambda_2),
        decltype(Lambda_3),
        decltype(Lambda_4)
    >
);
/******************************************************************************************************/




}}}}

#endif