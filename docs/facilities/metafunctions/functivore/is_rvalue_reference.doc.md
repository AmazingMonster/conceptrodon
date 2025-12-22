<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsRvalueReference`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-is-rvalue-reference">To Index</a></p>

## Description

`Functivore::IsRvalueReference` accepts a function-like type. It returns true if the type is rvalue reference qualified and returns false if otherwise.

## Type Signature

```Haskell
IsRvalueReference
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRvalueReference
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) &&;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) && { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) && { return 0; }
};

/**** Tests ****/
static_assert(! IsRvalueReference<decltype(fun)>::value);
static_assert(IsRvalueReference<AbominableFun>::value);
static_assert(! IsRvalueReference<decltype(FunAddr)>::value);
static_assert(IsRvalueReference<decltype(&Tester::fun)>::value);
static_assert(IsRvalueReference<FO>::value);
static_assert(IsRvalueReference_v<FO>);
```

## Implementation

The implementation of `IsRvalueReference` relies on extracting the qualifiers and specifiers of the function-like types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename F>
struct IsRvalueReference
{
    static constexpr bool value
    { static_cast<bool>((1 << 9) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsRvalueReference_v
{ IsRvalueReference<F>::value };
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_rvalue_reference/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/is_rvalue_reference.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_rvalue_reference.test.hpp)
