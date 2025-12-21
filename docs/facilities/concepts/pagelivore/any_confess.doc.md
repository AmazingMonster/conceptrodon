<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-confess">To Index</a></p>

## Description

`Pagelivore::AnyConfess` accepts a class template predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred&lt;Es::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0<***>::value)` and `(...||Pred_0<***>::value) && (...||Pred_1<***>::value)` are both atomic.
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
requires (...||Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args::value>::value) && (...||Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements::value>::value);
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/any_confess/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/concepts/any_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_confess.test.hpp)
