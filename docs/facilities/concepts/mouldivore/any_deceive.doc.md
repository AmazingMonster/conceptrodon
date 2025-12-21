<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-any-deceive">To Index</a></p>

## Description

`Mouldivore::AnyDeceive` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred&lt;Es&gt;::value))</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0<***>::value))` and `(...||(not Pred_0<***>::value)) && (...||(not Pred_1<***>::value))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** fun ****/
template<typename...Args>
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

By turning `(...||(not Pred_0<***>::value))` and `(...||(not Pred_1<***>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements>::value));
```

## Links

- [Example](../../../code/facilities/concepts/mouldivore/any_deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/concepts/any_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/any_deceive.test.hpp)
