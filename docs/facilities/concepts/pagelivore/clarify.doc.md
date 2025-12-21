<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Clarify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-clarify">To Index</a></p>

## Description

`Pagelivore::Clarify` accepts a class template predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Pred, Vs...
-> Pred&lt;Vs...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept Clarify = REQUIREMENT;
```

## Examples

`Clarify` turns a class template predicate into a concept so that it can be used for subsumption.

Since `Pred_0<***>::value` and `Pred_0<***>::value && Pred_1<***>::value` are both atomic.
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

/**** fun ****/
template<auto...Args>
requires Pred_0<Args...>::value
constexpr bool fun(){return false;}

template<auto...Args>
requires Pred_0<Args...>::value && Pred_1<Args...>::value
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `Pred_0<***>::value` and `Pred_1<***>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept Clarify = Predicate<Variables...>::value;
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/pagelivore/clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/clarify.test.hpp)
