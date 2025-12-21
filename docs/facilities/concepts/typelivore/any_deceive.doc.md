<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-deceive">To Index</a></p>

## Description

`Typelivore::AnyDeceive` accepts a callable type predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred{}(Es::value)))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0{}(***)))` and `(...||(not Pred_0{}(***))) && (...||(not Pred_1{}(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return false;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return false;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...||(not Pred_0{}(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||(not Pred_0{}(Args::value))) && (...||(not Pred_1{}(Args::value)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

By turning `(...||(not Pred_0(***)))` and `(...||(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate{}(Elements::value)));
```

## Links

- [Example](../../../code/facilities/concepts/typelivore/any_deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/concepts/any_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_deceive.test.hpp)