<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-left-interview">To Index</a></p>

## Description

`Varybivore::SensibleLeftInterview` accepts a list of variables.
Its first layer accepts a list of predicates and returns a function.

When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;Interviewers..., V<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., V<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., V<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview
 :: auto...
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct SensibleLeftInterview
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

- We will find the indices of `2` and `-1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = SensibleLeftInterview<0, 0, 1, 2, 2>
::Rail<Equal>::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::value == 3);
static_assert
(Metafunction<-1>::value == -1);
```

- We will find the first index of the value which is greater than `1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Less ****/
template<auto I, auto J>
struct Less
{
    static constexpr bool value
    {I < J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = SensibleLeftInterview<0, 0, 1, 2, 2>
::Rail<Less>::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction_1<1>::value == 3);
```

## Implementation

We will implement `SensibleLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct SensibleLeftInterview
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...>
        struct ProtoPage
        { static constexpr auto value {-1}; };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

template<auto First>
struct SensibleLeftInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
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

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
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
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/sensible_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_left_interview.test.hpp)
