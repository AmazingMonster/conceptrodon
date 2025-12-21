<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Fake`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-fake">To Index</a></p>

## Description

`Mouldivore::Fake` accepts an element and a class template predicate.
It returns true if the predicate invoked by the element returns true and returns false if otherwise.

<pre><code>   E, Pred
-> not Pred&lt;E&gt;::value</code></pre>

## Structure

```C++
template<typename, template<typename...> class>
concept Fake = REQUIREMENT;
```

## Examples

`Fake` turns a class template predicate into a concept so that it can be used for subsumption.

It accepts the element before the predicate so that the constraint can be applied to the terms inside the parameter list of an ordinary function.

```C++
/**** SameAsInt ****/
template<typename...>
struct SameAsInt
{ static constexpr bool value {false}; };

template<>
struct SameAsInt<int>
{ static constexpr bool value {true}; };

/**** fun ****/
std::true_type fun(Fake<SameAsInt> auto);
std::false_type fun(auto);

/**** Test ****/
static_assert(! decltype(fun(1))::value);
static_assert(decltype(fun(1.1))::value);
```

## Implementation

```C++
template<typename Element, template<typename...> class Predicate>
concept Fake = not Predicate<Element>::value;
```

## Links

- [Example](../../../code/facilities/concepts/mouldivore/fake/implementation.hpp)
- [Source code](../../../../conceptrodon/concepts/mouldivore/fake.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/fake.test.hpp)
