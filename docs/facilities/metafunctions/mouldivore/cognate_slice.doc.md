<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-slice">To Index</a></p>

## Description

`Mouldivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};


template<template<typename...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all elements from `int, int*, int**, int**` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect elements between indices one and three from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult */
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

- In the case where the second layer of `CognateSlice` only accepts an amount, we want to remove the elements of the given amount from the front of the list.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateSlice` accepts two indices, we want to collect the elements between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the elements
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBKQiyG8WDuJmSbi8jlohAAnrDsKDzMkIVDMDC4chJugsFQ0Ri/sc7spiJgaKpvkdgQRMCw0gYmbC3ARkS9mGxSHcsgAvTAAfQIpOuaAY2zSBEp1NpeIedwIxC8mFhVmuoP%2B%2BzuQgA7ngAG4NemHRnM1lMdlwrk81ga5Lo66TNUOfUITBtGGBKyBB6aslXJkstlOtxC0UEAB0cYAkhKrm6vB6hF62hzCSAQBEsKoRUoAI7q6UR%2BNxmOk50Yv2gu4NlVW8P1xsc1uNxuh622zncxiOytou6QpgKL4AeRexBtOVIHc7d12uzuAHVcV4lDCAGwaKk0vCqDmJ51D3cq1B3Rg%2BBI23EEL0LzvLu5eBgGwxM9B3NrAG%2BCBQq2uRdG33WljzRSs5HfT9MHQedgJAlV%2B15TBKwAFV/TACAUBck07eZHGQEcBEmTBjTEH8EUvPB0GRWgIBWBcAFphynW8mg5TDiGAbDALjastRBAMg21cl7njaU8C3H5QW7Fs7RQx1%2BXtAc2CTFMPUk94txMOsROSIS5ObO8szwYUxUreN%2BSjSy4wAKQ01VUzlbTpIjbNcwYfNC0wEs3nLIdnRsgh0BzPNMALYtS22Dl7KC9Ea21OtEIbeTTNSvE3CfLsTN7VTUISkcDHHO52JnJoEKuJClxXddX103cwMPCDTwE88iDuakmGQBAVS9AUpjlVAqB3DRuN4nCTF3IDqqQ5qjzhE9sErKqapferN1xaa9wVFq4Uctqqw6y9rzYCr7wGhpmUYKbMufFcDVxD9BAvEjaEaWaaoWuLILjCa%2BLWpCCsHATMvwxtCLwYipTIijaCozraPoxiWLY6dZwELisJwhLROEwNDODXVAVJ84dQpeMwxuwRMYYc1yfEsmyeBYyw1Mu08ojEG2CK0dSvKumnPdOUPGAZgmSEJFYuSoTO3S3tbNjASkrmhtNLlKlUCIZQmF431/UJozMoVjzzOjO4rhYDZBAh9XnI9LWdb1iMrZt8VVc7PS5eBrmOR5tC42weg2AAu3F03CJgDuABZTxv1hZUsEhVScobCA08XdNvWILNQpzFgmAAa1FCKor8mLXett8PcSl01Zqu4c1Nu5kdoDlBcqu5g5p3GVewVH7sbJiifBgzjYb02zIsuUBnaGzzbFbvvPD6kSzwakvggOe5XbZJlWwbymMyjX5W11Bdd4jkd/5Q/0HD73M6nxSHV5oOQ9u3DPaQyOjFj%2BOlR3GTrQVOQ906Z07G5JQecwogELiXEUZdfL%2BTLNfIaaIQqwPgaXbykVkGVw5HfZiO9qz10bo2ZuXNW50XbnCTuc5u4fwAglQeDdOwjx9g2PSRtgzyz9nCJg1FKxXGANSXuX8yGNl/tHS%2B2195n2dlfOEIixGhz7lWGso8Cb4wpszUmwJdR3AAGIb0mN3VQrBWS4lkkzPRZxWbanBNKHEWUpQyimqrXRhwyoYyaAzS07N8pKTfho%2Bup96FYy0V4vUQgvBpGKHBAASp8LwID/GgmkfqOJCT0DJIUKk3e8iIkMA5BEAghx%2BRlMOIJYmFI8kFPSdcTJ9S0mJzuGLCWmApbQwjMUpMOZZEcjMP0kAcdaD3zhGUypgh9jTPKbM1uMz9g1LEjcCk6FPhyhscmVoRERRjiUO0CAnkFCOn2V/NwsT4mZCSSkkB/IWm1w4bUuxgIDEUiEJgKU35sAWOpo0tZryAQOMBd4q5OTHnfGBJk8FNzcl3IICKLggC%2BmTJmXM6pmiJ6GMhds5pCKkWAI6XebpsU6G%2BJyCMwZcIuD8mSCMsZEy3BTMWeUjFCyqnLKxS87xGyzHbKhsgc5hyCDHPziAU5bBznX2yXCx5SKHkEq4GiDhHA1i0E4P4XgfgOBaFIKgTg2VLDWAFBsLY20Ug8FIAQTQaq1hFwCJIGMGgAAcZgzAAE4PVcH8K6l1XBAiBGkBqjgkheAsAkBoDQpAdV6oNRwXgCgQDRptbqtVpA4CwBgIgEAGwCBpAROQSgaAWR0ASFER0nBVAuu3Mxbckg7jAGQMRKQMYzC8DgoQEgtE9D8EECIMQ7ApAyEEIoFQ6g02kF0LSg0M40icB4OqzV2rbX6s4BOBEBbhqjWrbW%2Btjbm13FbWYO4EAPClvoMQGElqVi8FTVoNYEAkAlrSGWsgFAIAvrfSAYAUgzB8DoEyYgSaICxFXbECIbRkQLt4BB5gxBkQTliNoL5qarUlrUROBgtBoOTqwLELwwA3BiFoEm7gvAsCFyMOIPDG9UMmk%2BKuyKXyEQ7CtWUhoq6kSxBnAhjwWBV2qjwBG8jpBTTEFiDcp4VHgBIiMLatYVADDAAUAANQ%2BAadiOqrV9uEKIcQw7dNjrUKu6d%2BhDDGGsNYfQeBYhJsgGsVAsochkeYoSROphjWWDMHG8TxBaKMYc70ejzgICuBmH4WlYQIgjCqGMWlxRsgCAi3oRLTRFijBqMFhw/QhopdpXYELzQhoZbi1l%2BY0xPBdD0BVoYMWljxbWAoM12wJBLo4FqmNq7413F3XWhtTaW1OpPRAXAXar2Yi4Le61Cm1gZiwIkRipAHWSGSDGD1yQg0aEkGYSQu4ND%2BG3B6/QnAw2kAjckLgMZtxcG3C6j1/rtz%2BEkD6jb24uuTvjYm5NM202PuzU%2B3Nm7C0fq/ZeitbBOBtBYMaQIzEmDFQs0ej1MYrt6s7UQfzYVaW6YHQZ6QRmlAmcnbof9s6mDzvI%2B1zrsbeDxo3fmhEdwRq9Zrf1xHf8uAo7R6e89r7L3XuSGYab9702A7BwkItn7UAXrGKOIwXOuDRpoCAhIIGwOTrg1BmDpAtcIaQyhhwOuMO3Swzh1d%2BHCPEY%2BmRq1lGLM0b1fgakOXTRkfR6oFjTIdccZDXq7jvHkT8Z2HqoTImrXick0oaTDuo4Kb4MptTGmtM69x/podBPZDGYnXq0n5n5OeasJYGzdn4COec6RTgbnQoeas953zCQseBaW4VnLoXwtVYKFF7ypXlgJcyEl3InfIvpAH%2Bl%2BrmWavXTb8VwY%2BXstNB3r3%2BLtg8vD5qyVifZW2vrE2K1qbJ2Osrs%2B5wVne6G3y%2Bjlz1HzrT1jcx4Lqbd7ZukHm2MJbIazsXZR9twI/gPWBrJA7Z7YvYfZxqcDfYprx6Zo5p5pbpS4S7EAQ47DQ77osAKDGjETGjX7hiTAdr4CY49o46yB44Z4jryBE4546AgCpDk6U6LqH407dbrrA7bq9ZoEYFYE4F3hmJnoy784JCC7JAi7QHPr8FvoIHiGXogCYHxIijYEeoii4GIqqD1oAaq7AaUAa56p664ZWq6EG6obG4y6YbYa4ZO6YAEZEYka24UbMgO4h4UZ0au6MaTrMbICsY%2B6CCcaToB5QbB6Cb%2Bbh68CR5Sb2HUZx5/YJ56xJ6YCaY8ip4kHp4SCZ6jqUGmY0H56WZeY2Dcb2ZLZOZNBka7DZiF7WA%2BZ05%2BYBb5FNbT5NAuDeTz7RYVCT794lA5Dz5pY5DL7lZ1G5Zz7r4FZ9ECBL5b596r4DH5Aj61Y9E77NZ75DrU7H7gEcDsENroGYF3AKExjKF34EEkCP4iF/ZzbegLaUDtZf4gCeoxjJDJD%2BC%2BovZRq3GBB3ZgF04QG2A/ai4rD2ogCSD%2BDrYBqBBRouqSDepcBupmDvYhrJDLHvEJq/YPrtbtpvFroInfFrDiZZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_slice.test.hpp)
