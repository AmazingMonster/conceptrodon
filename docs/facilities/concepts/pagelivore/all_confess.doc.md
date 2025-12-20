<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-confess">To Index</a></p>

## Description

`Pagelivore::AllConfess` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred&lt;Es::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0<***>::value)` and `(...&&Pred_0<***>::value) && (...&&Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&Pred_0<Args::value>::value) && (...&&Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements::value>::value);
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/all_confess/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_confess.test.hpp)
