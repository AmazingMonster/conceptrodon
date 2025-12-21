<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Deceive`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-deceive">To Index</a></p>

## Description

`Varybivore::Deceive` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Pred, Es...
-> not Pred(Es::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0(***))` and `(not Pred_0(***)) && (not Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (not Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0(Args::value...)) && (not Pred_1(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(not Pred_0(***))` and `(not Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Deceive = not Predicate(Elements::value...);
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/deceive.test.hpp)
