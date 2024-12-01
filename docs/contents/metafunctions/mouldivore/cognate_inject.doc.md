<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInject`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new elements and returns a function.
When invoked, the function injects new elements into the location of its argument list and instantiates the operation with the result.

<pre><code>   Operation
-> I
-> NewElements...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Operation&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, NewElements..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject ::   template<typename...> class...
                -> auto...
                -> typename...
                -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        { 
            template<typename...>
            alias Mold = RESULT;
        };
    };
}；
```

## Examples

We will inject `double, double*` into one of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, double, double*, int*, int**>;

using Result = CognateInject<Operation>
::Page<1>
::Mold<double, double*>
::Mold<int, int*, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

```C++
/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Enrich ****/
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewElements...` are injected in the return type.
        Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<typename...NewElements>
            struct ProtoMold
            {
                template<typename...Elements>
                using Mold = decltype
                (
                    // Note that we use a parameter pack in the template head
                    // even though the function only allows one operation.
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoMold<NewElements...>
                    ::template idyl<Operation, Elements...>()
                );
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxBIapAAOqAqETgwe3r4ByanpAqHhUSyx8VyJdpgOGUIETMQEWT5%2BXIFVNQJ1DQRFkTFxCbb1jc05bcM9fSVlCQCUtqhexMjsHOYAzGHI3lgA1CYbbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc392ZbDB2Xn2hzcBHOSUwAH0CMQmIQFD87r8APQAKgxaL2ymImBoqj2mLRKN%2BBEwLCSBjJoPBkOYbFIezSAC9oQQkbc0IDMEkCNjcfiXgARPawryYQ5WZF3dGYvbYBjEPDIBCEzEku5kilUiVHWmMVi6653d7ELwOeWK5WqkwAdistqFkt%2BpPJlKY1KOLLZADo/QBJDmm818hVKlWg97oEAgMJYVRQpQAR3F3NB/r9Pp%2BG2N93tvz2hdFbp1NIhBrYmYimAA7th6GxBIicwWi8GLTjUEQALKedCtwt2iwHO5FsfF7UeiWj8eDo4D2dFrXuz1g8v0zCZq57HZMBQKPYAeUhcMcAlIC8XexRKL2AHVnl4lAcAGwaHF4vCqdNXLdv0WoHsjA%2BHEU6vhoABixCyAAKg0wCYAQiJvlmM5XoWH74j%2BOaZlBsHwYhCgXmh6H6humYWEwyAANZwcQCFIZeRYcle7wesqO4CO8mAAG5iHsTAnIBeDoOctAQHMewALQsYuN7gdWdYNowSF/hoAm4nsYTaNUZLoFpDCiggzy4gQyyGfqqG3Fex6gWeDCgnhgh0QxCiZoyin1uSKluX6jKUTRLmEVuLYbFK1nMY6zrShFhbLqWerroaVa1l5jaMS2JFPmEwB7L2tD6YcIqdj2fagp5ylNiF1xhS6UW1TFsoYnsHjAMwZL%2BgwOkWkSGq3PFU40iWg2JXSyV%2Btuu77keJ7sQIQZiharXtZgnXdeyyL5iRA2rt6MJ7J18ayYW7Z8iVqDKEwCELkOTEnYtfJCAYCgIHdBxbbFpHDauZHjT6FXeU2x3oad/Jdqg%2BX9iRV63dD6Fxd9uprmNlZ%2BmlPnA/DhbZUYeV9sKexYDs%2BpvVeECk1j8kRF2zwEAgHp7DWj7PkwexJA0hpksQbNUdRBlGbTiN7MZTBQ59WPjvJvGMEZSzAKqdPPFQXiAvZewCLQ5wCbQtCoDWB4CM8qCzfZVkS1eYbWpGHwxiwTDUdCcaYAmyapqs6YMEdoW5ubi4xjtzznZD5WpZVqkTZl4u%2B3s/tCyJYmgrZp4ZIy6NVRH2ASRTs5zNFUeznaToNfn71F%2BFb0B2WKObn6tzALigMZT7i447lkME09e5ICAAdg6VBWgnXDfpb5WaheFY6F3nC6V0cglEJmQ%2BYI3zbN9jaS45dCEE%2BdW9I0vK/VdP9XlzKRLnxffVNViMGYO8B69aiF/PxifUuv8jzAs8oJcqsvKry6TUiMq4VhrmPXMoMk5zQcsXX4rc9hCC8EkFISh0AACU75eFoHyIqM07IZFBGEAgjJ0BLGiPQEhZD6BokZEQmhBkCAYmzKfW48CMEKCwTgjYIplpTjWrpROJsCGRxjHvUEXAOQxmDkcUhXhyGYEoXI6hkiQDSLcEQ2hgh6F0LRMwwBtw2KOGQFCPcShGgQCjDGBQhoTHNjcOwzhjJEHINSJgdBmDsFXFzmFDgCxaCcAAKy8D8BwLQpBUCcDcNYawTIlgrG/v8HgpACCaF8QsaiIAAkAA4fQvg2JIMwtpJCSGyRsDQAT/BZP0JwSQvAWAJESCEsJESOC8AUCARIKTQm%2BNIHAWAMBEAgCWAQJIJxyCUDQBSOgcQIiGk4KoLJL4pIvkkHsYAyBkB7CkD6MwvA3GEBICJPQ/BBAiDEOwKQMhBCKBUOobppBdBcFIDWOESROA8D8YE4JqTwmcEPCcUZfJUBUD2AspZKy1kbK2ZIHZewIAeCmfQbmmwuBzF4F0rQCwIBIEmUkaZZAKAQFxfikAwApBmD4HQLm7SIDRB%2BdEMIDRzjvN4Ay5gxBziHmiOtFlpBJnpUPAwTWPysDRC8MANwYhaDtO4LwLAdsjDiHufgXENQeJ3x%2Bc7aoJw1hJKIZgfx9yzjRDhByjwWAfmwjwPU2VpB1XEGiK4oU5JDDADOEYVJCwqAGGAAoAAangWstkQlJJOcIUQ4hLlhpuWoH5jz9CupQNEyw%2Bg8DRHaZABYxt7IyqklGIqphLDWDMM0%2B1SosAZokrYA1ukMguE9mMVoQRPbTAGOUPIaR7KNr0CggoDBW2lEGE8jo9luijE8C0PQI7agjF6GEfog721sXHdkJty653FDbRIBYCg4mrG3dUjgQTSBNN4C00FizlmrPWZs7ZZg4W4AOcixJaLkmeoWCLLA8Qq0ZMkBsH0/gNhFI0AUyQb5ykvkCIa2ppB6kbC4LkrgL4smVKQwEyQXAKkbBfCen5LS2kdLfd0rFAzsVDIBWMwlxKkWzLYJwBoLAeK2ikqzXcuM2g%2BgQ2E/ZRBy3HNkGcyN0ho1KFjfc3QFKXlMDebKz5R7vn3Jaf8kZJx1YgoY0xljO4DDsf8Jxn06l4WoERXEA4/wzCvoxT0sj1G4jjKJcZvFSKQAaeY2xsl/gKiUuwXEGldL7lsqZbywLHKuU8ttfylSgrhXKswGKiVUqZVJPla6pVYSVW1vVTK7jqhtVkl5fqw1YTjWmvOOatYYSrU2qSfax1ShnUKrdTlT1fAfX%2BsDTWYNvKw2CYucJ2QMa7lhIkwmj1harApuNZWrNvIMi5vzdw8bxbS1xHLRqzN1b7D2Xre4Cd4xm3oAHbMJ5vau17abadjIR2h2bdrV0Wd3bh01s6AwMdG6F3HcmCuydw7Z3XfKDuvdFy5PHtPb8jgGlGPMdYzp3KHGuMPvwLxsz8HLPvtIJ%2BwYVboN1JABsPTIHbQVNtLafJZgwMYdw4pzgBHOktb6YM4ZgL7O2eILRtYDGIUsAUDxTZPEOM6neHspHhzoxPJ6xGvrVz5CiaGzoPHzzXkspBwp5pfyKNAvU8QFgXOed84F1Od4cKEVOdM5sDYaPiO9JxY5/FLPbfOd58gqE/P/BQkFwQEx2uVneepZQfzYSQvMttUHsLuleWRcENF4P6W4vislTrJLcqXWKoq3KvAqrHBZc1bl5AOqCuCANT8krTLyuWqVNV3gtWnUp6ax6q33qrrtaDXSbrAnJcSH69c2XcaFew6TUWybabpvhNm1xTgKJLFLcsCWs9ZaRLrardO5wEBXCPYO/9nt%2BQzurq352q786Zg3eX69h752p3PdHX9w/W7fs9HX%2BuzfqLFjLH3c/w1oO8OcEh7r3nexXc%2Bge6I5Poo6ororo6Y7fpyYwb1JmB6YbAbABIBIgYVAaAIG2jIZU5q6tK2CEZWZzDpIgAYY%2BjYYBK2hmBIEYaQaSAaAUqGobCq5no05EaYpya7JYFME4H4ELD2ppDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_inject.test.hpp)
