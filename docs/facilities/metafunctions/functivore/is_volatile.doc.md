<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsVolatile`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-is-volatile">To Index</a></p>

## Description

`Functivore::IsVolatile` accepts a function-like type. It returns true if the type is `volatile` qualified and returns false if otherwise.

## Type Signature

```Haskell
IsVolatile
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsVolatile
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) volatile;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) volatile { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) volatile { return 0; }
};

/**** Tests ****/
static_assert(! IsVolatile<decltype(fun)>::value);
static_assert(IsVolatile<AbominableFun>::value);
static_assert(! IsVolatile<decltype(FunAddr)>::value);
static_assert(IsVolatile<decltype(&Tester::fun)>::value);
static_assert(IsVolatile<FO>::value);
static_assert(IsVolatile_v<FO>);
```

## Implementation

The implementation of `IsVolatile` relies on extracting the qualifiers and specifiers of the function-like types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename F>
struct IsVolatile
{
    static constexpr bool value
    { static_cast<bool>((1 << 7) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVolatile_v
{ IsVolatile<F>::value };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_volatile/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/is_volatile.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_volatile.test.hpp)
