<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-situational">To Index</a></p>

## Description

`Mouldivore::Situational` accepts a list of predicates and returns a function.

When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational
 :: template<typename...> class...
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class...>
struct Situational
{
    template<typename, typename, typename...>
    alias Mold = RESULT;
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<typename Initiator, typename...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator::value+...+Args::value) < 10};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Situational<SumLessThanTen>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 1>
>);

static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 10>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 2>
>);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<typename...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<typename IfTrue, typename IfFalse, typename...Others>
    struct ProtoMold
    { using type = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<typename IfTrue, typename IfFalse, typename...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoMold<IfTrue, IfFalse, Others...> 
    { using type = IfTrue; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/situational/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/situational.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/situational.test.hpp)
