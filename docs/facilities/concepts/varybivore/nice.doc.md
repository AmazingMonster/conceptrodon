<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Nice`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-nice">To Index</a></p>

## Description

`Varybivore::Nice` accepts values and yields `true`.

<pre><code>   Vs...
-> true</code></pre>

## Structure

```C++
template<auto...>
concept Nice = REQUIREMENT;
```

## Examples

`Nice` is the `concept` counterpart of `std::void_t`. It makes the validity check of an expression subsumable.

```C++
/**** Tester ****/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires Nice<I.value>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires Nice<I.value> && Nice<J.value>
struct Tester<I, J>
{ static constexpr int value {2}; };

/**** Tests ****/
static_assert(Tester<0>::value == 0);
static_assert(Tester<std::integral_constant<int, 0>{}, 0>::value == 1);
static_assert(Tester<std::integral_constant<int, 0>{}, std::integral_constant<int, 0>{}>::value == 2);
```

## Implementation

We will use `Yes` as the internal requirement of the `Varybivore::Nice`. Assuming we implemented `Good` as follows, and test it with our Example:

```C++
template<auto...>
concept Good = true;
```

```C++
template<auto...>
struct AnotherTester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires Good<I.value>
struct AnotherTester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires Good<I.value> && Good<J.value>
struct AnotherTester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(AnotherTester<0>::value == 0);
static_assert(AnotherTester<std::integral_constant<int, 0>{}, 0>::value == 1);
static_assert(AnotherTester<std::integral_constant<int, 0>{}, std::integral_constant<int, 0>{}>::value == 2);
```

The compiler will fail with an 'ambiguous template instantiation' error because of the following constrained entity.

```C++
template<auto I, auto J>
requires Good<I.value> && Good<J.value>
```

Note that an atomic constraint consists of an expression and a parameter mapping. In this constrained entity, the expression is `true`. Since it is not a template, the parameter mapping is nullary. Thus, `Good<I.value>` is the same as `Good<J.value>`, resulting in both specializations being the same, causing the error.

To avoid ambiguity, we introduce `Yes`, ensuring that the parameter mapping is not nullary.

```C++
template<auto...>
struct Yes
{
    static constexpr bool value {true};
};
```

Finally, we can finish implementing our `Nice`.

```C++
template<auto...Args>
concept Nice = Yes<Args...>::value;
```

## Links

- [Example](../../../code/facilities/concepts/varybivore/nice/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/varybivore/nice.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/nice.test.hpp)
