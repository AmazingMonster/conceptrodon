// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_GET_PARAMETER_TYPES_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_GET_PARAMETER_TYPES_H

#include "conceptrodon/metafunctions/functivore/get_parameter_types.hpp"
#include <concepts>

namespace Conceptrodon {

/******************************************************************************************************/
template<typename...>
struct Capsule;
/******************************************************************************************************/

namespace Functivore {
namespace UnitTests {
namespace TestGetParameterTypes {




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
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(fun_0)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(fun_1)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(fun_2)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(fun_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunP_0)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunP_1)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunP_2)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunP_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunAddr_0)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunAddr_1)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunAddr_2)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(FunAddr_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::fun_0)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::fun_1)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::fun_2)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::fun_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::gun_0)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::gun_1)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::gun_2)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::gun_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(&Tester::gun_4)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_0>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_1>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_2>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_3>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_4>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_5>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_6>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_7>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<FO_8>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(Lambda_0)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(Lambda_1)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(Lambda_2)>, Capsule<int, double>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(Lambda_3)>, Capsule<int, double&>>);
static_assert(std::same_as<GetParameterTypes<Capsule>::Mold<decltype(Lambda_4)>, Capsule<int, double&>>);
/******************************************************************************************************/




}}}}

#endif