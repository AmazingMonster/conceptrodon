<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllFailed`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-failed">To Index</a></p>

## Description

`Typelivore::AllFailed` accepts a callable type predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise

<pre><code>   Pred, Vs...
-> (...&&(not Pred{}(Vs)))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AllFailed = REQUIREMENT;
```

## Examples

`AllFailed` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_0{}(***))) && (...&&(not Pred_1{}(***)))` are both atomic.
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
template<auto...Args>
requires (...&&(not Pred_0{}(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0{}(Args))) && (...&&(not Pred_1{}(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

By turning `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_1{}(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** pun ****/
template<auto...Args>
requires AllFailed<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AllFailed<Pred_0, Args...> && AllFailed<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AllFailed = (...&&(not Predicate{}(Variables)));
```

## Links

- [Example](../../../code/facilities/concepts/typelivore/all_failed/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/typelivore/all_failed.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_failed.test.hpp)
