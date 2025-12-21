// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_LVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_LVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/concepts/functivore/lvalue_reference_qualified.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestLvalueReferenceQualified {




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
static_assert(! LvalueReferenceQualified<decltype(fun_0)>);
static_assert(! LvalueReferenceQualified<decltype(fun_1)>);
static_assert(! LvalueReferenceQualified<decltype(fun_2)>);
static_assert(! LvalueReferenceQualified<decltype(fun_3)>);
static_assert(! LvalueReferenceQualified<decltype(FunP_0)>);
static_assert(! LvalueReferenceQualified<decltype(FunP_1)>);
static_assert(! LvalueReferenceQualified<decltype(FunP_2)>);
static_assert(! LvalueReferenceQualified<decltype(FunP_3)>);
static_assert(! LvalueReferenceQualified<decltype(FunAddr_0)>);
static_assert(! LvalueReferenceQualified<decltype(FunAddr_1)>);
static_assert(! LvalueReferenceQualified<decltype(FunAddr_2)>);
static_assert(! LvalueReferenceQualified<decltype(FunAddr_3)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::fun_0)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::fun_1)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::fun_2)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::fun_3)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::gun_0)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::gun_1)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::gun_2)>);
static_assert(LvalueReferenceQualified<decltype(&Tester::gun_3)>);
static_assert(! LvalueReferenceQualified<decltype(&Tester::gun_4)>);
static_assert(! LvalueReferenceQualified<FO_0>);
static_assert(! LvalueReferenceQualified<FO_1>);
static_assert(! LvalueReferenceQualified<FO_2>);
static_assert(! LvalueReferenceQualified<FO_3>);
static_assert(! LvalueReferenceQualified<FO_4>);
static_assert(! LvalueReferenceQualified<FO_5>);
static_assert(! LvalueReferenceQualified<FO_6>);
static_assert(LvalueReferenceQualified<FO_7>);
static_assert(! LvalueReferenceQualified<FO_8>);
static_assert(! LvalueReferenceQualified<decltype(Lambda_0)>);
static_assert(! LvalueReferenceQualified<decltype(Lambda_1)>);
static_assert(! LvalueReferenceQualified<decltype(Lambda_2)>);
static_assert(! LvalueReferenceQualified<decltype(Lambda_3)>);
static_assert(! LvalueReferenceQualified<decltype(Lambda_4)>);
/******************************************************************************************************/




}}}}

#endif