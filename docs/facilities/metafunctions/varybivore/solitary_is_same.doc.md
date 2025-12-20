<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-solitary-is-same">To Index</a></p>

## Description

`Varybivore::SolitaryIsSame` accepts two variables.
It returns true if they are the same and returns false otherwise.

<pre><code>   Left, Right
-> Left `same as` Right ?
   true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsSame
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsSame_v
{RESULT};
```

## Examples

```C++
static_assert(! SolitaryIsSame<1, 1.0>::value);
static_assert(SolitaryIsSame<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/solitary_is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/solitary_is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_same.test.hpp)
