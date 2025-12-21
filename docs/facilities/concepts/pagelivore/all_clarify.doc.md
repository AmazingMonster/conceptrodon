<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllClarify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-clarify">To Index</a></p>

## Description

`Pagelivore::AllClarify` accepts a class template predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&Pred&lt;Vs&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

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

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0<Args>::value) && (...&&Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AllClarify = (...&&Predicate<Variables>::value);
```

## Links

- [Example](../../../code/facilities/concepts/pagelivore/all_clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/pagelivore/all_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_clarify.test.hpp)
