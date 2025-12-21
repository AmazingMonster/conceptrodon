<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typical_get_return_type">To Index</a></p>

## Description

`Functivore::TypicalGetReturnType` accepts a function-like type and returns its return type via the alias member `type`.

## Type Signature

```Haskell
TypicalGetReturnType
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
using TypicalGetReturnType
{
    using type = RESULT;
};
```

## Examples

We will extract the return types from several function-like types.

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

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<TypicalGetReturnType<decltype(fun)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<AbominableFun>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<decltype(FunAddr)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<decltype(&Tester::fun)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<FO>::type, SupposedReturnType>);
```

## Implementation

The implementation of `TypicalGetReturnType` relies on dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename Fn>
struct TypicalGetReturnType
{ using type = Analyzer<Fn>::result_type;};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/typical_get_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_return_type.test.hpp)
