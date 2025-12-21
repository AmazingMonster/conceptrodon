<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsVariadic`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_variadic">To Index</a></p>

## Description

`Functivore::IsVariadic` accepts a function-like type. It returns true if the type has a variadic parameter list and returns false if otherwise.

## Type Signature

```Haskell
IsVariadic
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsVariadic
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*...);

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*...) { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*...) { return 0; }
};

/**** Tests ****/
static_assert(! IsVariadic<decltype(fun)>::value);
static_assert(IsVariadic<AbominableFun>::value);
static_assert(! IsVariadic<decltype(FunAddr)>::value);
static_assert(IsVariadic<decltype(&Tester::fun)>::value);
static_assert(IsVariadic<FO>::value);
static_assert(IsVariadic_v<FO>);
```

## Implementation

The implementation of `IsVariadic` relies on studying the parameters of the function-like types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename F>
struct IsVariadic
{
    static constexpr bool value
    { static_cast<bool>((1 << 4) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVariadic_v
{ IsVariadic<F>::value };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_variadic/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/is_variadic.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_variadic.test.hpp)
