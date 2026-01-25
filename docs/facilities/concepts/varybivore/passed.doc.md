<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Passed`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-passed">To Index</a></p>

## Description

`Varybivore::Passed` accepts a callable predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Pred, Vs...
-> Pred(Vs...)</code></pre>

## Structure

```C++
template<auto, auto...>
concept Passed = REQUIREMENT;
```

## Examples

`Passed` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(Pred_0(***))` and `(Pred_0(***)) && (Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (Pred_0(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (Pred_0(Args...)) && (Pred_1(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(Pred_0(***))` and `(Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires Passed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires Passed<Pred_0, Args...> && Passed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept Passed = Predicate(Variables...);
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/passed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/passed.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/passed.test.hpp)
