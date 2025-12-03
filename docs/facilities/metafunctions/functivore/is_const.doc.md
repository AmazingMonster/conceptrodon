<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsConst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_const">To Index</a></p>

## Description

`Functivore::IsConst` accepts a function-like type. It returns true if the type is `const` qualified and returns false if otherwise.

## Type Signature

```Haskell
IsConst
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsConst
{
    static constexpr bool value {RESULT};
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

/**** Tests ****/
static_assert(! IsConst<decltype(fun)>::value);
static_assert(IsConst<AbominableFun>::value);
static_assert(! IsConst<decltype(FunAddr)>::value);
static_assert(IsConst<decltype(&Tester::fun)>::value);
static_assert(IsConst<FO>::value);
```

## Implementation

The implementation of `IsConst` relies on extracting the qualifiers and specifiers of the function-like types using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsConst
{
    static constexpr bool value
    { static_cast<bool>((1 << 6) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsConst_v
{ IsConst<F>::value };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_const/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_const.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_const.test.hpp)
