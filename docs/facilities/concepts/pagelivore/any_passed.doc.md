<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyPassed`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-passed">To Index</a></p>

## Description

`Pagelivore::AnyPassed` accepts a class template predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||Pred&lt;Vs&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AnyPassed = REQUIREMENT;
```

## Examples

`AnyPassed` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

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

/**** fun ****/
template<auto...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires AnyPassed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AnyPassed<Pred_0, Args...> && AnyPassed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AnyPassed = (...||Predicate<Variables>::value);
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/any_passed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/pagelivore/any_passed.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_passed.test.hpp)
