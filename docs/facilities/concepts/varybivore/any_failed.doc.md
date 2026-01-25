<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyFailed`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-failed">To Index</a></p>

## Description

`Varybivore::AnyFailed` accepts a callable predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||(not Pred(Vs)))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AnyFailed = REQUIREMENT;
```

## Examples

`AnyFailed` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0(***)))` and `(...||(not Pred_0(***))) && (...||(not Pred_1(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (...||(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0(Args))) && (...||(not Pred_1(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(...||(not Pred_0(***)))` and `(...||(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires AnyFailed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AnyFailed<Pred_0, Args...> && AnyFailed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AnyFailed = (...||(not Predicate(Variables)));
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/any_failed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/any_failed.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_failed.test.hpp)
