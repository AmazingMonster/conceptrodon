<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::KindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.

When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

- We will find the indices of `Vay<2>` and `Vay<-1>` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

```C++
/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value{Variable}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = KindredLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Road<std::is_same>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Road<std::is_same>::value == -1);
```

- We will find the first index of the type whose member `value` is greater than `1` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

```C++
/**** Less ****/
template<typename I, typename J>
struct Less
{
    static constexpr bool value
    {I::value < J::value};
};

/**** Tests ****/
static_assert
(Metafunction<Vay<1>>::Road<Less>::value == 3);
```

## Implementation

We will implement `KindredLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredLeftInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredLeftInterview<First>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First, typename Second, typename...Others>
struct KindredLeftInterview<First, Second, Others...>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_left_interview.test.hpp)
