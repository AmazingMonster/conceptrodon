// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_SAME_TYPE_SIGNATURE_AS_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_SAME_TYPE_SIGNATURE_AS_H

#include "conceptrodon/metafunctions/functivore/concepts/same_type_signature_as.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestSameTypeSignatureAs {




/******************************************************************************************************/
/**** functions ****/
inline int fun_0(int, double){ return 0; }
inline int fun_1(int, double...){ return 0; }
inline int fun_2(int const, double...){ return 0; }
inline int fun_3(int const, double&...){ return 0; }

/**** function pointers ****/
inline constexpr auto FunP_0 { fun_0 };
inline constexpr auto FunP_1 { fun_1 };
inline constexpr auto FunP_2 { fun_2 };
inline constexpr auto FunP_3 { fun_3 };

inline constexpr auto FunAddr_0 { &fun_0 };
inline constexpr auto FunAddr_1 { &fun_1 };
inline constexpr auto FunAddr_2 { &fun_2 };
inline constexpr auto FunAddr_3 { &fun_3 };

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
inline constexpr auto Lambda_0
{
    [](int, double)
    { return 0; }
};

inline constexpr auto Lambda_1
{
    [](int, double...)
    { return 0; }
};

inline constexpr auto Lambda_2
{
    [](int const, double...)
    { return 0; }
};

inline constexpr auto Lambda_3
{
    [](int const, double&...)
    { return 0; }
};

inline constexpr auto Lambda_4
{
    [](int const, double&...) noexcept
    { return 0; }
};
/******************************************************************************************************/




/******************************************************************************************************/
consteval bool pun(auto arg) {return false;}
consteval bool pun(SameTypeSignatureAs<decltype(fun_1)> auto arg) {return true;}

consteval bool bun(auto arg) {return false;};
consteval bool bun(SameTypeSignatureAs<decltype(fun_3)> auto arg) {return true;}
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(pun(fun_1));
static_assert(pun(fun_2));
static_assert(pun(FunP_0));
static_assert(pun(FunP_1));
static_assert(pun(FunP_2));
static_assert(pun(FunAddr_0));
static_assert(pun(FunAddr_1));
static_assert(pun(FunAddr_2));
static_assert(pun(&Tester::fun_0));
static_assert(pun(&Tester::fun_1));
static_assert(pun(&Tester::fun_2));
static_assert(pun(FO_0{}));
static_assert(pun(FO_1{}));
static_assert(pun(FO_2{}));
static_assert(pun(Lambda_0));
static_assert(pun(Lambda_1));
static_assert(pun(Lambda_2));

static_assert(! pun(fun_3));
static_assert(! pun(FunP_3));
static_assert(! pun(FunAddr_3));
static_assert(! pun(&Tester::fun_3));
static_assert(! pun(FO_3{}));
static_assert(! pun(FO_4{}));
static_assert(! pun(FO_5{}));
static_assert(! pun(FO_6{}));
static_assert(! pun(FO_7{}));
static_assert(! pun(FO_8{}));
static_assert(! pun(Lambda_3));
static_assert(! pun(Lambda_4));

static_assert(bun(fun_3));
static_assert(bun(FunP_3));
static_assert(bun(FunAddr_3));
static_assert(bun(&Tester::fun_3));
static_assert(bun(FO_3{}));
static_assert(bun(FO_4{}));
static_assert(bun(FO_5{}));
static_assert(bun(FO_6{}));
static_assert(bun(FO_7{}));
static_assert(bun(FO_8{}));
static_assert(bun(Lambda_3));
static_assert(bun(Lambda_4));

static_assert(! bun(fun_1));
static_assert(! bun(fun_2));
static_assert(! bun(FunP_0));
static_assert(! bun(FunP_1));
static_assert(! bun(FunP_2));
static_assert(! bun(FunAddr_0));
static_assert(! bun(FunAddr_1));
static_assert(! bun(FunAddr_2));
static_assert(! bun(&Tester::fun_0));
static_assert(! bun(&Tester::fun_1));
static_assert(! bun(&Tester::fun_2));
static_assert(! bun(FO_0{}));
static_assert(! bun(FO_1{}));
static_assert(! bun(FO_2{}));
static_assert(! bun(Lambda_0));
static_assert(! bun(Lambda_1));
static_assert(! bun(Lambda_2));
/******************************************************************************************************/




}}}}

#endif