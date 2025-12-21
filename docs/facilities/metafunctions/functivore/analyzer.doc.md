<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::Analyzer`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-analyzer">To Index</a></p>

## Description

`Functivore::Analyzer` accepts a function-like type and extracts its return type, parameter types, and qualifiers through various members.

## Type Signature

## Structure

```C++
template<typename>
struct Analyzer
{
    static constexpr bool value {RESULT};
    using return_type = RESULT;
    using parameter_types = RESULT;
    using class_type = RESULT;
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** DummyContainer ****/
template<typename...>
struct DummyContainer;

/**** SupposedResultType ****/
using SupposedResultType = int;

/**** SupposedParameterTypes ****/
using SupposedParameterTypes = DummyContainer<int, int*>;

/**** Tests ****/
static_assert(Analyzer<decltype(fun)>::value == (1 << 3));
static_assert(std::same_as<Analyzer<decltype(fun)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(fun)>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<AbominableFun>::value == (1 << 6 | 1 << 3));
static_assert(std::same_as<Analyzer<AbominableFun>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<AbominableFun>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<decltype(FunAddr)>::value == (1 << 2));
static_assert(std::same_as<Analyzer<decltype(FunAddr)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(FunAddr)>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<decltype(&Tester::fun)>::value == (1 << 1 | 1 << 6));
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::parameter_types<DummyContainer>, SupposedParameterTypes>);
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::class_type, Tester>);

static_assert(Analyzer<FO>::value == (1 | 1 << 6));
static_assert(std::same_as<Analyzer<FO>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<FO>::parameter_types<DummyContainer>, SupposedParameterTypes>);
static_assert(std::same_as<Analyzer<FO>::class_type, FO>);
```

## Implementation

```C++
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    static constexpr std::uint32_t value {1 << 3};
    
    using type_signature = Ret(Args...);
    
    using result_type = Ret;

    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    static constexpr std::uint32_t value {1 << 6 | 1 << 3};

    using type_signature = Ret(Args...);
    
    using result_type = Ret;

    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn>
{
    static constexpr std::uint32_t value
    {
        1 << 2 |
        (
            1 << 3 ^
            AnalyzerPrototype<Fn>::value
        )
    };
};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn>
{
    static constexpr std::uint32_t value
    {
        1 << 1 |
        (
            1 << 3 ^
            AnalyzerPrototype<MemFn>::value
        )
    };

    using class_type = Structure;
};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())>
{
    static constexpr std::uint32_t value
    {
        1 |
        (
            1 << 1 ^
            Analyzer<decltype(&FO::operator())>::value
        )
    };

    using class_type = FO;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/analyzer/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/analyzer.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/analyzer.test.hpp)
