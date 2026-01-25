<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Failed`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-failed">To Index</a></p>

## Description

`Varybivore::Failed` accepts a callable predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred(Vs...)</code></pre>

## Structure

```C++
template<auto, auto...>
concept Failed = REQUIREMENT;
```

## Examples

`Failed` turns a callable predicate into a concept so that it can be used for subsumption.

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
requires Failed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires Failed<Pred_0, Args...> && Failed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept Failed = not Predicate(Variables...);
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/failed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/failed.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/failed.test.hpp)
