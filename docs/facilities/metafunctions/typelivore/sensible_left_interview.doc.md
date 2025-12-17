<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-left-interview">To Index</a></p>

## Description

`Typelivore::SensibleLeftInterview` accepts a list of elements.
Its first layer accepts a list of predicates and returns a function.

When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview
 :: typename...
 -> template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct SensibleLeftInterview
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
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
using Metafunction = SensibleLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Road<std::is_same>::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::value == 3);
static_assert
(Metafunction<Vay<-1>>::value == -1);
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

/**** Metafunction_1 ****/
template<typename...Args>
using Metafunction_1 = SensibleLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Road<Less>::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_1<Vay<1>>::value == 3);
```

## Implementation

We will implement `SensibleLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct SensibleLeftInterview
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...>
        struct ProtoMold
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
};

template<typename First>
struct SensibleLeftInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
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

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
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
                        SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/sensible_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/sensible_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/sensible_left_interview.test.hpp)
