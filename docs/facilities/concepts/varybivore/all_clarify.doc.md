<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllClarify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-clarify">To Index</a></p>

## Description

`Varybivore::AllClarify` accepts a callable predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&Pred(Vs))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0(***))` and `(...&&Pred_0(***)) && (...&&Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0(Args)) && (...&&Pred_1(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(...&&Pred_0(***))` and `(...&&Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

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
template<auto Predicate, auto...Variables>
concept AllClarify = (...&&Predicate(Variables));
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/all_clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/all_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_clarify.test.hpp)
