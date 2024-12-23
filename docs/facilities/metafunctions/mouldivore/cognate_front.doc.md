<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-front">To Index</a></p>

## Description

`Mouldivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = CognateFront<Operation>
::Page<3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    static consteval auto idyl() -> Operation<Targets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BASlpGQKh4VEssfEArLaY9o4CQgRMxATZPn5cgXaYDpkNTQTFkTFxibaNza25HWP9g6XlIBUAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYya6MyHiYCjeHZ5fXJ39H3wu5yBZgAzGFkN4sDcTKC3F5HLRCABPWHYYHmcEMSFeaGwtzIBQEdBYKhojGXAiYFjJAxU/EEZFPZhsUg3dIAL0wAH0COTLmhsY8CDdlMRMDRVDDQXcbgRiF5MLCrJdgb9/hr9oD1TcAJI0%2BhsQRMOoMT4HbWaq2nClXQ43ABiJEw5q1wKpBpNSrhjOZrG96MuRIVDkdzphAHYrBG7srbR7aV78ZyeQQAHQZ3X8i7Bryhp3i5PEkAgMJYVTcpQAR0VQvxuozafJoMDQKjwJunbl1MT9MuXelbg7A67Cbp3rcvsY/sbaJukKYCg%2BAHknsQTZlSMORzdttsbgB1F1eJQwhIaMUSvCqeto2fnuWoG6MHxxL1njQAFSawEwBAUJjnk2/Y7qK4qSreLaNt%2BxC/v%2BW4gTuU4spgs6IdKrYDkSG7IPOAhEpgABuYg3EwCJPng6DIrQEBLDcAC0c6rm%2Bpr4jBcEKLOLZxqqMY8UCPz2h4wDMFSDrELIro2pSPbjgyslJj6TLTmwXHYPOBhLjczHrqx3FBvKeYisJomYOJsgYu26FjopbgpryNwXCwayCNmWGGaGYqoEQyhML%2B26RiqFygd2nr0kpfqqRm2CGow/5uaBJ5hMANwALKeOg0qylgkJTgFA4QPloEFhORLoCWLBMAA1jyZaYBW1a1ps%2BJOS5fLcfpwUhV2JY2VSNyUdR%2BI6RuAhsjF1JxZxGZorRRWdks/EDiYfGgkFAV9ROZFEI2FzAOKk2CABnUDklRiin5LqwrKXk%2BZdLX7Zgh3/mp/ErbGa22uq1qWrc2CqKwtIul8arWiDqqqmCEJQldcKCpsyTxZ1oO3CNppSYCm0MspKGvQZIYimjmRvYJtxCF4ySpEo6AAErvF4tAiuDFxnSl5OU2kmC0/TjNZdpa6jQw%2BJhAQbIi7sYuCPszbraT%2Bw3HTCgM0zFrAqzCs8yK103CZXrma5cJEwI2Ylr5/lwqCJsgOltDoMLgiSwQEsDVLzvi7sMtffan7vCrboGTh3KLkozQQGVJYKP6QfHW47NU1zivK2yieM2ii1rRwKy0JwFS8H4HBaKQqCcEOljWOyawbFdYI8KQBCaJnKxVYskhphoAAcZhmP4/hcBUHft1wEYRtI2ccJIvAsBIGgaKQ%2BeF8XHC8AoICz/XBeZ6QcCwDAiAgGsBDJAi5CUGgNJ0HEET%2Bpwqjtwk9EJJINzAMguFSGmZi8FzhAkJRej8IIEQYh2BSBkIIRQKh1Ab1ILoLgpAADu65kicB4FnHOecG5F04MuBER8RSoCoDcW%2B99H7P1fjcd%2BZgbgQA8OfegxAYQ1yWLwdeWgVgQCQGfZIF8yAUAgFwnhIBgBSDMHwOgVJiArwgNETB0QwhNGRCg3gcjmDEGRMuaI2hujr1rmfI0BBlwMFoIo6BWBoheGAG4MQtAV7cF4FgSqRhxCmLwOKHohF3iYPqt0BEWxa4ixqJgpE0R1xqI8FgTB8o8BTzsaQDxxBoicweI44ASIjANxWFQAwwAFAADU3jwOYvnWuADhCiHEKA0pEC1CYNgfoQwxhrDWH0HgaIK9IArFQIjTItj6JlWuqYMulgzAL3icQSiniOnVFqJkFwDB3CeDaHoEIYQhhlBGHAqmhQsiLKmPkdIpo5jDHiHAroPR6jjBaLs9o0ztG9EuUc9ZJyZgTGuXobCzRHkLC4CsBQldNgSDQRwXOc9MGLyIXfB%2BT8X5v1blQiAuAf4MMxD8lhGSVgIEwEwLA8RaKkGbpIUEaZ/CghHhoSQZhJDng0BUBIgQx4T1IFPUEXA0wJC4Akdu/hB4JAqJIPuJKkjz14IvZeq864ZK3rvDh%2B9cHHz4QI%2BhV82CcCaCwQiEZ6JMA0g0ih/g0yssLt/Ig4zypwNKUAip0gqlKBqdA3QojEFMGQXYoFILhVYI4Dgw%2BCIbgEIhSQp%2BC5zodANW3ahtDuH0MYaCMwzCJUb3YZw1AdC4gn34SmqNIxg3CN7rPGgjM4hSJkdAlRCilGkDLWojRWiHAVr0XFQxxjMFmIsVY2gNiK0OIac4wu%2BA3GOA8bYo1qgfFUgrQEsehdgmhOROErYhcokxNrvExJShkk9uSpKrJfk8kFKKRWi15SQHWtkNUqBhcHX1PSYMqwlgWltPgJ07p%2BFOB9OJAMppwzRlxFNZMvFZzTRzIWTkG5KySjHL0Fs00kwbnQcyF8jZtzzkMD6K80D7yah3IubMVZ8wkMfKuRh05Dy8OQZ%2BasdYAKKNj3dWCzgAaoU6pDfqw11DEUmpjaihNbCMVYpxZQIFjLmX6vJRGCo/hh6ggpVS/loLoGitsOK1hm9t57wPng9NirL7Xw4Gq0hLAFCEVwoRUN44iRf3wCav%2B5rZCWpPWA%2BQtqL06BAKCBBSClFuowQp7Bcr8GENUAZozJmzNeiJBGzNPCY2gnjSppNKAov0K00lkYxnKbclM/4bk5mCDciC9a8RRbKAlsLlWkxtdys1u0fWlN%2Bim0mL7ZgcxljrG2Nrt2pxC77GuLuUOrxo7kC%2BInYIQJ0CZ0KPnZE8Zy7eCrqSdSTd6TE18GyXuzAhTmSHrs8eiQp7wHOdqW569jShk2GCe0vFXTTS2O2OHW91gRkirGRMy7vysMoeA7B5Z8zEPPPgwIb7myCiHLI08zDMycPoaWacj7po0MDDB98l5RGYco7%2B4CyjVdMe0Z8wvBjBWbiGeMzcLLaZcvsasyQLjcX0WkExdikYeKGWTxAN3NMoJQQVH7vymenOIycvk/jpeSm1504JRUYlQ8Iwz3bpIXuXBO5mCSGPUEeORWcDRYmoFn8hca5F/FlY8T0jOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_front.test.hpp)
