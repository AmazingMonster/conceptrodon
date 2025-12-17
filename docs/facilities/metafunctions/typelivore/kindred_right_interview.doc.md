<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-right-interview">To Index</a></p>

## Description

`Typelivore::KindredRightInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.

When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;E<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredRightInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredRightInterview
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
using Metafunction = KindredRightInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Road<std::is_same>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Road<std::is_same>::value == -1);
```

- We will find the first index of the type whose member `value` is less than `1` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

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
(Metafunction<Vay<1>>::Road<Less>::value == 0);
```

## Implementation

We will implement `KindredRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredRightInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr auto value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredRightInterview<First>
{
    template<typename...RightSides>
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
                    ((...&&Predicates<First, RightSides...>::value))
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
struct KindredRightInterview<First, Second, Others...>
{
    template<typename...RightSides>
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
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredRightInterview<Others...>
                        ::template Mold<RightSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredRightInterview<Others...>
                        ::template Mold<RightSides...>
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

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_right_interview.test.hpp)
