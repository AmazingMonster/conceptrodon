<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-solitary-is-different">To Index</a></p>

## Description

`Varybivore::SolitaryIsDifferent` accepts two variables.
It returns true if they are different and returns false otherwise.

<pre><code>   Left, Right
-> Left `different from` Right ?
   true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsDifferent
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(SolitaryIsDifferent<1, 1.0>::value);
static_assert(!SolitaryIsDifferent<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/solitary_is_different/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/solitary_is_different.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_different.test.hpp)
