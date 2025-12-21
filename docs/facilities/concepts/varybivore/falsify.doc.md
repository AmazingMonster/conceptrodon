<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Falsify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-falsify">To Index</a></p>

## Description

`Varybivore::Falsify` accepts a callable predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred(Vs...)</code></pre>

## Structure

```C++
template<auto, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0(***))` and `(not Pred_0(***)) && (not Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (not Pred_0(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0(Args...)) && (not Pred_1(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(not Pred_0(***))` and `(not Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

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
template<auto Predicate, auto...Variables>
concept Falsify = not Predicate(Variables...);
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/falsify.test.hpp)
