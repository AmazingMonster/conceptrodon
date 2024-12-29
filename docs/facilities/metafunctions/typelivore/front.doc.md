<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-front">To Index</a></p>

## Description

`Typelivore::Front` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects elements of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
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
using Result = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

```C++
template<typename, auto>
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
template<typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCx0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf9AdrDsCtXcAJJs%2BhsQRMJqM3WanU284Um5UgBiJEwlrt1xZxvNqvh3N5rB9GOuk2VDjuztpsIA7FYow81fbPezvQTsgAvTAAfQIADo8wbRVcQ14wxGfW5iSAQBEsKpM0oAI4qiUEg15nPkwJBkEx0F3fuK1nJznXAdytx9scDpMc8t%2BxgB9vou5QpgKL4AeRexHNuVIk6nd12uzuAHVXV4lLCkhoaXS8KpW%2BilzfFag7owfAlvdeNAAVNpgEwAgFBMG8O1HQ9pXvR94QLLt2wA4ggJA/dIMPec%2BUwJd0Llbsx3mRxkBXARJkwAA3MRBWFO48HQFFaAgFY7gAWmXLdvyaAkkJQhQly7BMNTjQSQUpe5HWIWQ3WZIdZy5HkFzYdtsBNRgQMLYtS0kwRMV7XCZxTeF0yzKUrhYDYdIE3DNKlGlUCIZQmCAg9o3VK4oMHL1OV9WTDLcTDFzzZdV3XdsrmAWlWTU0CrPcqDLwiYA7gAJVQJh0DlBUsChecXLHCA8qgstUwIdAqxYJgAGssxrTA60bZttgJMyLIITt8I8gcqwMllaPo2hmoizAosEPi8wFFSRpA/jsCYwr%2BxWESxxMYTAjclyevLIUiDCoappijr%2BwSoxqSc104QVOyHLOwbItNaagoEtbdPjZ6NTE20rQ%2B/Y7mwVRWHZV0fmtT6vtEsFsVxfF4XFbZ0nU2KQcOO4OJ3C1gY9XzvP8hSsJm0EbJR7ddwEESkZ%2BoQvHSEpMHQZLPi8WgpQxq5jqSynqayWn6YURmpQuonONyAkIgIAVRf2cXBEOTt1u%2BlKGaZ6TQTZhXeaVgWJNkEXBClghJdo6WDYl/Z0SrRznPhQIzZAVL0oJVGSYYWX7X1P9PmZpkCdaIjMzXJR2ggSsQAUAM/ZitwOZpunFbFtW%2BfRRa1o4NZaE4fxeD8DgtFIVBOAnSxrDuBQNi2c7wR4UgCE0FO1kqgJJBzDQAA4zDMFIUi4fwW%2BbrgoyjaQ044SReBYCQNA0Ugs5zvOOF4BQQEn6vs5T0g4FgGBEBADYCHSRFyEoNA2ToBIogDThVGbpIWKSSQ7mAZBiKkHMzF4WnCBIOi9H4QQRDEdgpAyEEIoFQ6gV6kF0FwUgAB3Hc6ROA8FTunTONdc6cA3IiPeUpUBUDuJfa%2Bt976PzuM/MwdwIAeGPvQYgsIK4rF4MvLQawIBICPukE%2BZAKAQDYRwkAwApBmD4HQFkxAF4QFiKg2IEQ2gogQbwKRzBiAog3LEbQmAHByNIEfe6G4GC0FkeArAsQvDADcGIWgC9uC8CwBVIw4hDF4FpA4PA5FPioLquoxEOxK6iwaKg5EsQdxKI8FgVBSo8BjysaQVxxBYhcyeLY4AyIjA1zWFQAwwAFAADUPjQI4lnSuP9hCiHEIAopIC1CoMgfoQwxhrDWH0HgWIC9IBrFQPDXIliWLEguqYQulgzAzxicQOibjWm9HUU0FwDB3CeC6HoMIEQRjVDGFAkoOQBAzD8GsrIGyGCLFGIkKBdhJn9CmB0OZhRjkNFOQIAY7QDkrKObYc5Wy9DzAeUspYqy1gl02NsCQSCOAZynqg2eeCr43zvg/J%2BjcyEQFwB/GhWIuD0KrqktYCBMDpTGExUg9dJCBBzCkQIA8NCSDMJIG8Gh/B1CHiPUgY9AhcBzEkLgSRm4pF7kkfwkgu4kqSKC8Bs956L3RSvZhm8WHb0wfvLhPDqFnzYJwNoLByJRhYkwFcBgTpcBSDmFlOd35EBGWVKBRS/6lOkOUpQlTwG6EEbApg8CrFApBdPXgs8MG70RHcHBEKCF31XLq/VhryGUPYdQ2hgQzBosYavaVCqEgH24agKhYxg38M7pPGgTMEhiIkeAhRMjNHFqUSotRGionaLUro/RqCjEmLMbQCxmibG1PsTnfATjHCuMsUa1QniWSaN8UPHOASgkohCTsHO4TImVxiXEpQCSO2JVSXwDJ2Tcn5M0RakpADrWyAqWAnODqakpL6VYSwjTmnwDaR00inBumlV6fUgZQyEimrGXik5zjnAQFcG8qBizKiHL0OspoQGMi7KaI85Y1y%2Bh3NeZc7ZEy/3NHOXB1ZLzBhQY%2BUML5YHUXrH%2BQAt1KDhWcADVC7VtSSGhqbuQxFJro2ooYRi0gWKcWJDxfS0eIBAj6vJVGfwKR%2B6BApVSvlQqZ6cFFUvdd68t47ywSmpNxAlU7FVYQlgChyLEXInqnMs5Jhv3wCar%2B5rZCWoPUA%2BQtqT06AEzAuBcjyMyc9eg2V2DcGqB03pgzRmTNSgoWmyNCRo2BDjYp1hYWOFqbi9QkA%2BnqaZkMykTMwXMx%2BetcI/NlBC05zLQYyuxWK2TM0TWwQdaDFdswMY0x5jLGV3bXYmd1jHGnL7e4wdyAvEjsEH48BE6ZHTrCSM%2BdvBF3xNZKulJEqN1OS3ZgPJvJd3Wf3RIQ9wCHNVOczqup/SbABJaXi9pTRLG7ErJe6wgzPXDNGad35Nz0PTNmQUVDIHlnweg6UXIUGIO5Cw8839TR7kXI%2B%2B8l7YPMOEaee85DkPjmw9A/D4jfyy6Av0MgjzaCOB4P8/pu46XjPekmEx8zJBWPRYlZi7FWAeNAoZWPduOZAiBH8N3PlE92dRg5bjkVtgxXxpWHXEAkh/DEr7lGCezdJCdy4K3Mwgqh6BAo7Jue4qmFAtfgLuTWva7RPzbkcXQA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/front.test.hpp)
