<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Falsify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-falsify">To Index</a></p>

## Description

`Pagelivore::Falsify` accepts a class template predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred&lt;Vs...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a class template predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0<***>::value)` and `(not Pred_0<***>::value) && (not Pred_1<***>::value)` are both atomic.
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
template<auto...Args>
requires (not Pred_0<Args...>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0<Args...>::value && not Pred_1<Args...>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(not Pred_0<***>::value)` and `(not Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires Falsify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires Falsify<Pred_0, Args...> && Falsify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept Falsify = not Predicate<Variables...>::value;
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/pagelivore/falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/falsify.test.hpp)
