<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Sieve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-sieve">To Index</a></p>

## Description

`Mouldivore::Sieve` accepts a list of predicates and returns a function.

When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Capsule`.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Capsule
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Sieve
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will remove every element whose value result is divisible by two and three in the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule
<Vay<1>, Vay<2>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each element in a capsule separately;
2. taking the element out of its capsule if it satisfies all the predicates;
3. concatenating all capsules.

We can merge 1. and 2. by:

```C++
template<typename Element>
struct Detail 
{ using type = Capsule<>; };

template<typename Element>
requires (not (...&&Predicates<Element>::value))
struct Detail<Element>
{ using type = Capsule<Element>; };
```

We will use `Cotanivore::TypicalPaste` to concatenate the capsules. Here is the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not (...&&Predicates<Element>::value))
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    using Mold = Contanivore::TypicalPaste
    <typename Detail<Elements>::type...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/sieve/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/sieve.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/sieve.test.hpp)
