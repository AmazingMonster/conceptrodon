// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_ALL_NOT_NONOVERLOADED_FUNCTION_OBJECT_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_ALL_NOT_NONOVERLOADED_FUNCTION_OBJECT_H

#include "conceptrodon/concepts/functivore/all_not_nonoverloaded_function_object.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestAllNotNonoverloadedFunctionObject {




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

struct FO_9
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
    int operator()(double const, double&...) const volatile && noexcept { return 0; }
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
    AllNotNonoverloadedFunctionObject
    <
        decltype(fun_0),
        decltype(fun_1),
        decltype(fun_2),
        decltype(fun_3),
        decltype(FunP_0),
        decltype(FunP_1),
        decltype(FunP_2),
        decltype(FunP_3),
        decltype(FunAddr_0),
        decltype(FunAddr_1),
        decltype(FunAddr_2),
        decltype(FunAddr_3),
        decltype(&Tester::fun_0),
        decltype(&Tester::fun_1),
        decltype(&Tester::fun_2),
        decltype(&Tester::fun_3),
        decltype(&Tester::gun_0),
        decltype(&Tester::gun_1),
        decltype(&Tester::gun_2),
        decltype(&Tester::gun_3),
        decltype(&Tester::gun_4)
    >
);

static_assert
(
    ! AllNotNonoverloadedFunctionObject
    <
        FO_0,
        decltype(fun_0),
        decltype(fun_1),
        decltype(fun_2),
        decltype(fun_3),
        decltype(FunP_0),
        decltype(FunP_1),
        decltype(FunP_2),
        decltype(FunP_3),
        decltype(FunAddr_0),
        decltype(FunAddr_1),
        decltype(FunAddr_2),
        decltype(FunAddr_3),
        decltype(&Tester::fun_0),
        decltype(&Tester::fun_1),
        decltype(&Tester::fun_2),
        decltype(&Tester::fun_3),
        decltype(&Tester::gun_0),
        decltype(&Tester::gun_1),
        decltype(&Tester::gun_2),
        decltype(&Tester::gun_3),
        decltype(&Tester::gun_4)
    >
);
/******************************************************************************************************/




}}}}

#endif