<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Nice`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-nice">To Index</a></p>

## Description

`Typelivore::Nice` accepts types and yields `true`.

<pre><code>   Es...
-> true</code></pre>

## Structure

```C++
template<typename...>
concept Nice = REQUIREMENT;
```

## Examples

`Nice` is the `concept` counterpart of `std::void_t`. It makes the validity check of an expression subsumable.

```C++
/**** Tester ****/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I, typename J>
requires Nice<typename I::type>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<typename I, typename J>
requires Nice<typename I::type> && Nice<typename J::type>
struct Tester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(Tester<int, std::type_identity<int>>::value == 0);
static_assert(Tester<std::type_identity<int>, int>::value == 1);
static_assert(Tester<std::type_identity<int>, std::type_identity<int>>::value == 2);
```

## Implementation

We will use `Yes` as the internal requirement of the `Typelivore::Nice`. Assuming we implemented `Good` as follows, and test it with our Example:

```C++
template<typename...>
concept Good = true;
```

```C++
template<typename...>
struct AnotherTester
{ static constexpr int value {0}; };

template<typename I, typename J>
requires Good<typename I::type>
struct AnotherTester<I, J>
{ static constexpr int value {1}; };

template<typename I, typename J>
requires Good<typename I::type> && Good<typename J::type>
struct AnotherTester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(AnotherTester<int, std::type_identity<int>>::value == 0);
static_assert(AnotherTester<std::type_identity<int>, int>::value == 1);
static_assert(AnotherTester<std::type_identity<int>, std::type_identity<int>>::value == 2);
```

The compiler will fail with an 'ambiguous template instantiation' error because of the following constrained entity.

```C++
template<typename I, typename J>
requires Good<typename I::type> && Good<typename J::type>
```

Note that an atomic constraint consists of an expression and a parameter mapping. In this constrained entity, the expression is `true`. Since it is not a template, the parameter mapping is nullary. Thus, `Good<typename I::type>` is the same as `Good<typename J::type>`, resulting in both specializations being the same, causing the error.

To avoid ambiguity, we introduce `Yes`, ensuring that the parameter mapping is not nullary.

```C++
template<typename...>
struct Yes
{
    static constexpr bool value {true};
};
```

Finally, we can finish implementing our `Nice`.

```C++
template<typename...Args>
concept Nice = Yes<Args...>::value;
```

## Links

- [Example](../../../code/facilities/concepts/typelivore/nice/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/typelivore/nice.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/nice.test.hpp)
