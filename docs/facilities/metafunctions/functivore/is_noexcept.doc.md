<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsNoexcept`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_noexcept">To Index</a></p>

## Description

`Functivore::IsNoexcept` accepts a function-like type. It returns true if the type is `noexcept` specified and returns false if otherwise.

## Type Signature

```Haskell
IsNoexcept
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsNoexcept
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) noexcept;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) noexcept { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) noexcept { return 0; }
};

/**** Tests ****/
static_assert(! IsNoexcept<decltype(fun)>::value);
static_assert(IsNoexcept<AbominableFun>::value);
static_assert(! IsNoexcept<decltype(FunAddr)>::value);
static_assert(IsNoexcept<decltype(&Tester::fun)>::value);
static_assert(IsNoexcept<FO>::value);
```

## Implementation

The implementation of `IsNoexcept` relies on extracting the qualifiers and specifiers of the function-like types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename F>
struct IsNoexcept
{
    static constexpr bool value
    { static_cast<bool>((1 << 5) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsNoexcept_v
{ static_cast<bool>((1 << 5) & Analyzer<F>::value) };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_noexcept/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_noexcept.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_noexcept.test.hpp)
