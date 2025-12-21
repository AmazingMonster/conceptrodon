<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-confess">To Index</a></p>

## Description

`Varybivore::AllConfess` accepts a callable predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred(Es::value))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0(***))` and `(...&&Pred_0(***)) && (...&&Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0(Args::value)) && (...&&Pred_1(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(...&&Pred_0(***))` and `(...&&Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AllConfess = (...&&Predicate(Elements::value));
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/all_confess/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_confess.test.hpp)
