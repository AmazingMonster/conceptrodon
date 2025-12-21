// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_ANALYZER_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_ANALYZER_H

#include "conceptrodon/metafunctions/functivore/analyzer.hpp"
#include "conceptrodon/metafunctions/microbiota/functilis/analyzer_prototype.hpp"
#include <concepts>




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG
#error "CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/rvalue_reference.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_LVALUE_REFERENCE_FLAG
#error "CONCEPTRODON_NUCLEOLUS_LVALUE_REFERENCE_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/lvalue_reference.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
#error "CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/volatile.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_CONST_FLAG
#error "CONCEPTRODON_NUCLEOLUS_CONST_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/const.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
#error "CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/noexcept.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
#error "CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/variadic.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function_pointer.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/pointer_to_member_function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function_object.hpp"
/******************************************************************************************************/




namespace Conceptrodon {

/******************************************************************************************************/
template<typename...>
struct Capsule;
/******************************************************************************************************/

namespace Functivore {
namespace UnitTests {
namespace TestAnalyzer {

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



/**** fun_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(fun_0)>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_0)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_0)>::result_type,
    int
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_0)>::parameter_types<>,
    std::tuple<int, double>
>);

static_assert
(
    Analyzer<decltype(fun_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
    )
);
/******************************************************************************************************/



/**** fun_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(fun_1)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_1)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_1)>::result_type,
    int
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_1)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(fun_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** fun_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(fun_2)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_2)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(fun_2)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_2)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(fun_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** fun_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(fun_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(fun_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(fun_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(fun_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** FunP_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunP_0)>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_0)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_0)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunP_0)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_0)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunP_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
    )
);
/******************************************************************************************************/



/**** FunP_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunP_1)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_1)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_1)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunP_1)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_1)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunP_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/




/**** FunP_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunP_2)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_2)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunP_2)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_2)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunP_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** FunP_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunP_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunP_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunP_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(FunP_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** FunAddr_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_0)>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_0)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_0)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunAddr_0)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_0)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunAddr_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
    )
);
/******************************************************************************************************/



/**** FunAddr_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_1)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_1)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_1)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunAddr_1)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_1)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunAddr_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/




/**** FunAddr_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_2)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_2)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunAddr_2)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_2)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(FunAddr_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/




/**** FunAddr_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(FunAddr_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(FunAddr_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(FunAddr_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);
/******************************************************************************************************/



/**** Tester::fun_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(&Tester::fun_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_0)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::fun_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(&Tester::fun_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_1)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::fun_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(&Tester::fun_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_2)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::fun_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::fun_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::fun_3)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::gun_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::gun_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_0)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::gun_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::gun_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_1)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::gun_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::gun_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_2)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::gun_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::gun_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
      | CONCEPTRODON_NUCLEOLUS_LVALUE_REFERENCE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_3)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** Tester::gun_4 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(&Tester::gun_4)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
      | CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(&Tester::gun_4)>::class_type,
    Tester
>);
/******************************************************************************************************/



/**** FO_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_0>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<FO_0>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<FO_0>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_0>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<FO_0>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<FO_0>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_0>::class_type,
    FO_0
>);
/******************************************************************************************************/



/**** FO_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_1>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<FO_1>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<FO_1>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_1>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<FO_1>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<FO_1>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_1>::class_type,
    FO_1
>);
/******************************************************************************************************/



/**** FO_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_2>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<FO_2>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<FO_2>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_2>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<FO_2>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<FO_2>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_2>::class_type,
    FO_2
>);
/******************************************************************************************************/



/**** FO_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_3>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_3>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_3>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_3>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_3>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_3>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_3>::class_type,
    FO_3
>);
/******************************************************************************************************/



/**** FO_4 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_4>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_4>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_4>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_4>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_4>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_4>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_4>::class_type,
    FO_4
>);
/******************************************************************************************************/



/**** FO_5 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_5>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_5>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_5>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_5>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_5>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_5>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_5>::class_type,
    FO_5
>);
/******************************************************************************************************/



/**** FO_6 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_6>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_6>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_6>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_6>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_6>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_6>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_6>::class_type,
    FO_6
>);
/******************************************************************************************************/



/**** FO_7 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_7>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_7>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_7>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_7>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_7>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_7>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
      | CONCEPTRODON_NUCLEOLUS_LVALUE_REFERENCE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_7>::class_type,
    FO_7
>);
/******************************************************************************************************/



/**** FO_8 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<FO_8>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<FO_8>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<FO_8>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<FO_8>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<FO_8>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<FO_8>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
      | CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<FO_8>::class_type,
    FO_8
>);
/******************************************************************************************************/



/**** Lambda_0 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(Lambda_0)>::variadic_type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_0)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_0)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(Lambda_0)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_0)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(Lambda_0)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_0)>::class_type,
    decltype(Lambda_0)
>);
/******************************************************************************************************/



/**** Lambda_1 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(Lambda_1)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_1)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_1)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(Lambda_1)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_1)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(Lambda_1)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_1)>::class_type,
    decltype(Lambda_1)
>);
/******************************************************************************************************/



/**** Lambda_2 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(Lambda_2)>::variadic_type_signature,
    int(int, double...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_2)>::type_signature,
    int(int, double)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_2)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(Lambda_2)>::parameter_types<Capsule>,
    Capsule<int const, double>
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_2)>::parameter_types<Capsule>,
    Capsule<int, double>
>);

static_assert
(
    Analyzer<decltype(Lambda_2)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_2)>::class_type,
    decltype(Lambda_2)
>);
/******************************************************************************************************/



/**** Lambda_3 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(Lambda_3)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_3)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_3)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(Lambda_3)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_3)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(Lambda_3)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_3)>::class_type,
    decltype(Lambda_3)
>);
/******************************************************************************************************/



/**** Lambda_4 ****/
/******************************************************************************************************/
static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::variadic_type_signature,
    int(int, double&...)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::type_signature,
    int(int, double&)
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::result_type,
    int
>);

static_assert
(! std::same_as<
    Analyzer<decltype(Lambda_4)>::parameter_types<Capsule>,
    Capsule<int const, double&>
>);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::parameter_types<Capsule>,
    Capsule<int, double&>
>);

static_assert
(
    Analyzer<decltype(Lambda_4)>::value
    == (
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
      | CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
      | CONCEPTRODON_NUCLEOLUS_CONST_FLAG
      | CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
    )
);

static_assert
(std::same_as<
    Analyzer<decltype(Lambda_4)>::class_type,
    decltype(Lambda_4)
>);
/******************************************************************************************************/




}}}}




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/rvalue_reference.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/lvalue_reference.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/volatile.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/const.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/noexcept.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/variadic.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function_pointer.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/pointer_to_member_function.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function_object.hpp"
/******************************************************************************************************/

#endif
