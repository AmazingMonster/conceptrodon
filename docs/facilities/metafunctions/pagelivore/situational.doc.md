<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-situational">To Index</a></p>

## Description

`Pagelivore::Situational` accepts a list of predicates and returns a function.

When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Situational
{
    template<auto, auto, auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto, auto, auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<auto Initiator, auto...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator+...+Args) < 10};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Situational<SumLessThanTen>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2>::value == 1);
static_assert(Metafunction<10, 2>::value == 2);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<auto...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/situational/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/situational.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/situational.test.hpp)
