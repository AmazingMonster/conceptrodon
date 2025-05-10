// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_GET_INVOKE_RETURN_TYPE_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_GET_INVOKE_RETURN_TYPE_H

#include "conceptrodon/functivore/get_invoke_return_type.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestGetInvokeReturnType {




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
    double operator()(int const, double&, double...) const volatile && noexcept { return 0; }
};

struct FO_10
{
    int operator()(int const, double&...) volatile & { return 0; }
    double operator()(int const, double&, double...) const volatile && noexcept { return 0; }
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
using SupposedType = int;

static_assert(std::same_as<GetInvokeReturnType<decltype(fun_0)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(fun_1)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(fun_2)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(fun_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunP_0)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunP_1)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunP_2)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunP_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr_0)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr_1)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr_2)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun_0)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun_1)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun_2)>::Mold<int, double>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::gun_0)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::gun_1)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::gun_2)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::gun_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::gun_4)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_0>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_1>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_2>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_3>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_4>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_5>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_6>::Mold<int, double&>, SupposedType>);
// static_assert(std::same_as<GetInvokeReturnType<FO_7>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_8>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_9>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<FO_9>::Mold<int, double&, double>, double>);
static_assert(std::same_as<GetInvokeReturnType<decltype(Lambda_0)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(Lambda_1)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(Lambda_2)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(Lambda_3)>::Mold<int, double&>, SupposedType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(Lambda_4)>::Mold<int, double&>, SupposedType>);
/******************************************************************************************************/



// `std::invoke_result` does not work with volatile lvalue reference qualified member functions.
/******************************************************************************************************/
// static_assert(std::same_as<std::invoke_result_t<FO_10, int, double&>, SupposedType>);
/******************************************************************************************************/




}}}}

#endif