<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetParameterTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-get-parameter-types">To Index</a></p>

## Description

`Functivore::GetParameterTypes` accepts a container such as the `std::tuple` and returns a metafunction.

When invoked by a function-like type, the metafunction returns its parameters collected by the previously provided container.

## Type Signature

```Haskell
GetParameterTypes
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct GetParameterTypes
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will extract the parameters from several function-like types. The parameters will be collected by `DummyContainer`.

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

/**** SupposedParameterTypes ****/
using SupposedParameterTypes = DummyContainer<int, int*>;

/**** Tests ****/
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<AbominableFun>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(FunAddr)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(&Tester::fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<FO>, SupposedParameterTypes>);
```

## Implementation

The implementation of `GetParameterTypes` relies on dissecting the structure of the function-like types into return types and parameter types using the metafunction [`Analyzer`](./analyzer.doc.md).


```C++
template<template<typename...> class Container>
struct GetParameterTypes
{ 
    template<typename...Args>
    using Mold = Analyzer<Args...>::template parameter_types<Container>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_parameter_types/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/get_parameter_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_parameter_types.test.hpp)
