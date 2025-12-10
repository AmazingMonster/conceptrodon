<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Sieve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-sieve">To Index</a></p>

## Description

`Pagelivore::Sieve` accepts a list of predicates and returns a function.

When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Shuttle`.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Shuttle
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Sieve
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15`.

```C++
/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, 2, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each variable in a shuttle separately;
2. taking the variable out of its shuttle if it satisfies all the predicates;
3. concatenating all shuttles.

We can merge 1. and 2. by:

```C++
template<auto Variable>
struct Detail 
{ using type = Shuttle<>; };

template<auto Variable>
requires (not (...&&Predicates<Variable>::value))
struct Detail<Variable>
{ using type = Shuttle<Variable>; };
```

We will use `Sequnivore::TypicalPaste` to concatenate the shuttles. Here is the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Sieve
{
    template<auto Variable>
    struct Detail 
    { using type = Shuttle<>; };

    template<auto Variable>
    requires (not (...&&Predicates<Variable>::value))
    struct Detail<Variable>
    { using type = Shuttle<Variable>; };

    template<auto...Variables>
    using Page = Sequnivore::TypicalPaste
    <typename Detail<Variables>::type...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/sieve/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/sieve.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/sieve.test.hpp)
