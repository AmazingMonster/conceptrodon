<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsLvalueReference`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_lvalue_reference">To Index</a></p>

## Description

`Functivore::IsLvalueReference` accepts a function-like type. It returns true if the type is lvalue reference qualified and returns false if otherwise.

## Type Signature

```Haskell
IsLvalueReference
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsLvalueReference
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) &;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) & { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) & { return 0; }
};

/**** Tests ****/
static_assert(! IsLvalueReference<decltype(fun)>::value);
static_assert(IsLvalueReference<AbominableFun>::value);
static_assert(! IsLvalueReference<decltype(FunAddr)>::value);
static_assert(IsLvalueReference<decltype(&Tester::fun)>::value);
static_assert(IsLvalueReference<FO>::value);
```

## Implementation

The implementation of `IsLvalueReference` relies on extracting the qualifiers and specifiers of the function-like types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename F>
struct IsLvalueReference
{
    static constexpr bool value
    { static_cast<bool>((1 << 8) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsLvalueReference_v
{ IsLvalueReference<F>::value };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_lvalue_reference/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_lvalue_reference.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_lvalue_reference.test.hpp)
