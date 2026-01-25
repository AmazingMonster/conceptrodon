<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Passed`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-passed">To Index</a></p>

## Description

`Mouldivore::Passed` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred&lt;Es...&gt;::value</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept Passed = REQUIREMENT;
```

## Examples

`Passed` turns a class template predicate into a concept so that it can be used for subsumption.

Since `Pred_0<***>::value` and `Pred_0<***>::value && Pred_1<***>::value` are both atomic.
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
requires Pred_0<Args...>::value
constexpr bool fun(){return false;}

template<typename...Args>
requires Pred_0<Args...>::value && Pred_1<Args...>::value
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

By turning `Pred_0<***>::value` and `Pred_1<***>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires Passed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires Passed<Pred_0, Args...> && Passed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept Passed = Predicate<Elements...>::value;
```

## Links

- [Example](../../../code/facilities/concepts/mouldivore/passed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/mouldivore/passed.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/passed.test.hpp)
