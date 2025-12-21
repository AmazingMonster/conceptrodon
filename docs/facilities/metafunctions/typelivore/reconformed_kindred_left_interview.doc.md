<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ReconformedKindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-reconformed-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::ReconformedKindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

This function internally is the flattened version of `Typelivore::LeftInterview`.

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
ReconformedKindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct ReconformedKindredLeftInterview
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
using Metafunction = ReconformedKindredLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
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

`Typelivore::ReconformedKindredLeftInterview` is implemented upon `Typella::UnconformedLeftInterview`.
The latter is a flattened version of `Typelivore::LeftInterview`.

Here's a simplified version of it:

```C++
template<
    template<typename...> class,
    typename,
    typename...
>
struct UnconformedLeftInterview
{ static constexpr std::make_signed_t<size_t> value {-1}; };

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First
>
struct UnconformedLeftInterview<Predicate, Interviewer, First>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else
            { return -1; }
        }()
    };
};

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First, typename Second, typename...Others
>
struct UnconformedLeftInterview<
    Predicate,
    Interviewer,
    First, Second, Others...
>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else if constexpr 
            (Predicate<Interviewer, Second>::value)
            { return 1; }

            else if constexpr
            (
                UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value != -1
            )
            { 
                return 2 + UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value; 
            }

            else
            { return -1; }
        }()
    };
};

template<typename...Elements>
struct ReconformedKindredLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = UnconformedLeftInterview
        <Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {
            UnconformedLeftInterview
            <Operation, Interviewer, Elements...>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/reconformed_kindred_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/reconformed_kindred_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/reconformed_kindred_left_interview.test.hpp)
