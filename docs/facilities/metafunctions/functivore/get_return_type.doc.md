<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-get-return-type">To Index</a></p>

## Description

`Functivore::GetReturnType` accepts a function-like type and returns its return type.

## Type Signature

```Haskell
GetReturnType
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetReturnType = RESULT;
```

## Examples

We will extract the return type from several function-like type.

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
static_assert(std::same_as<GetReturnType<decltype(fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<AbominableFun>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(FunAddr)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(&Tester::fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<FO>, SupposedReturnType>);
```

## Implementation

The implementation of `GetReturnType` relies on the metafunction [`TypicalGetReturnType`](./typical_get_return_type.doc.md), which is implemented by dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename...Args>
using GetReturnType = TypicalGetReturnType<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/get_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_return_type.test.hpp)
