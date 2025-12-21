<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Confess`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-confess">To Index</a></p>

## Description

`Varybivore::Confess` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred(Es::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(Pred_0(***))` and `(Pred_0(***)) && (Pred_1(***))` are both atomic.
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
requires (Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (Pred_0(Args::value...)) && (Pred_1(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(Pred_0(***))` and `(Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Confess = Predicate(Elements::value...);
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/confess/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/confess.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/confess.test.hpp)
