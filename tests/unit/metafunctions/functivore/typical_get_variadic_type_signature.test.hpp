// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_TYPICAL_GET_VARIADIC_TYPE_SIGNATURE_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_TYPICAL_GET_VARIADIC_TYPE_SIGNATURE_H

#include "conceptrodon/functivore/get_variadic_type_signature.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestTypicalGetVariadicTypeSignature {




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
using SupposedType_0 = int(int, double);

static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun_0)>::type, SupposedType_0>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunP_0)>::type, SupposedType_0>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr_0)>::type, SupposedType_0>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun_0)>::type, SupposedType_0>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_0>::type, SupposedType_0>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(Lambda_0)>::type, SupposedType_0>);

using SupposedType_1 = int(int, double...);

static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun_1)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun_2)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunP_1)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunP_2)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr_1)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr_2)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun_1)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun_2)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_1>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_2>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(Lambda_1)>::type, SupposedType_1>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(Lambda_2)>::type, SupposedType_1>);

using SupposedType_2 = int(int, double&...);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunP_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::gun_0)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::gun_1)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::gun_2)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::gun_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::gun_4)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_3>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_4>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_5>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_6>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_7>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO_8>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(Lambda_3)>::type, SupposedType_2>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(Lambda_4)>::type, SupposedType_2>);
/******************************************************************************************************/




}}}}

#endif