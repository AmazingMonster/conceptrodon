<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllDeceive`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-deceive">To Index</a></p>

## Description

`Pagelivore::AllDeceive` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&(not Pred&lt;Es::value&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0<***>::value))` and `(...&&(not Pred_0<***>::value)) && (...&&(not Pred_1<***>::value))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value)) && (...&&(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements::value>::value));
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/all_deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/concepts/all_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_deceive.test.hpp)
