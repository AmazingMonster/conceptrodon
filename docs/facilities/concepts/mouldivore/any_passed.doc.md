<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AnyPassed`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-any-passed">To Index</a></p>

## Description

`Mouldivore::AnyPassed` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred&lt;Es&gt;::value)</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyPassed = REQUIREMENT;
```

## Examples

`AnyPassed` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0<***>::value)` and `(...||Pred_0<***>::value) && (...||Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<typename...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AnyPassed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AnyPassed<Pred_0, Args...> && AnyPassed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyPassed = (...||Predicate<Elements>::value);
```

## Links

- [Example](../../../code/facilities/concepts/mouldivore/any_passed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/mouldivore/any_passed.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/any_passed.test.hpp)
