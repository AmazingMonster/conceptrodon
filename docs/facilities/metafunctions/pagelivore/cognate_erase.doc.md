<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-erase">To Index</a></p>

## Description

`Pagelivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateErase<Operation>::Page<1>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = CognateErase<Operation>::Page<1, 3>::Page<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

- In the case where the first layer of `CognateErase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_targets)::value...,
        BackArgs::value...
    >;
};
```

- In the case where the first layer of `CognateErase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_args)::value...,
        BackArgs::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEpIAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJUql2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSXUtbR0F3QpTwxGjVeO1AJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimGmujMh4mAoPp1e39wuQLO/xu1zBZgAzBFkN4sA8TJC3F5HLRCABPRHYcHmaEMWFeeGItzIeboLBULE4gGnB4ANSY6N%2BJ1BBEwLDSBjZxKYKNQ9NaeCYsXoVNu82IXgcAsxtxMgQsD3mTEcyAeaAY80wqjSxAevKIDwAbmIvJgEQqGcQhSLMPKnojFfbHdS7rTlMRMDRVMzjqz2ZyVXakQR0W9mGxSPq%2BWKbhrdmkCA8PV68D7EU8HgRJcGrHKacDC39wYDDg8AJIc%2BhsQQqnK%2By4lovNxv5t2PJ6EZAIBv%2BqtB4mh8OsYPY8XZqVJzsEbsWqyBB2QvNg25s/vcpFZABemAA%2BgQAHRH8uxiWT55dhDEskgEARLCqXdKACOZvxwbc5aPB6pkLHYIVcEHmArMAy5O1bhAhEkSAqCQLXQMNzcA1UG/LF1QMBQfgAeTeYg6wEUhYLgrMw0YEdvwsJhkAAaxuYhgAUYjoP/KDlVVdUBC1E1aGjQ08HQdFaGYiBmKg/Z9gebAdUMdAEQANg0FNvWJE8/xMRSs35NAvEELMEHNVpgB8RgCB%2BKhiFQFh9PNCzZB/SCSOTT0VKRNTsD41CjzswR9yMzAzKIxySIkh4ACV2VQI1zQIAyHkiVRDzEkCUKCm4nIeUK8j6GyHk9eYHPSpyqNo%2BjGLQ4KHjWZiAFp0NwhICIYZjiWS4CsFhIdMGoSzfKmYAAoUNZbx4s1vzSjKSrohiFBG01MAqorgN/ZdnSXV1SyknVdIG3twQQ8DBzIiNMCjLqTtPCdpWktIdvNeV50XVbVzAgdNzwHd92/cso23PdDyPAApS7JWu7ajA/G87wYB8n0wV8Pg/L8jyxX6CHQW9721OGEffYlAbQ9T1LlQDKoOgdKtayqoPJpCUMJjzYSYLCHga/D%2Bgmpzzooo8prKpjKeJpalRaDiNW4sRPIeAShJEtrMskm7ZIUpSXLTVSqU0w0dL02LDIYkzBHMyzrL1h4fKS6mQOU9W3PQ%2BnvN6ghdyMhROZCxWZJhlWbdUfHNY0LTON0pMzd0gB3Qw2TkozDbMwqMt9/2/088b5ayzwcrN/LLeFqC%2BZmxaoOqyq6pTtmmpamCrfahpaC6nrZBdmbhpAUaFqPd24ILxi5u8DuE5AlacQXF0202jxgGYNlsHwpQ9pe9cP1pj8HZ/FOmZZiv%2BhB89J%2BnnA54ggDlxp16kL%2Br6UaFtirqTD1UCIZQmF2h61ue4WV%2BvD7/orGHtVjLfUG99LJPxfkjf%2Bfsb5D1JnneC59V58m/FaG09AmLQJIl4LIRhkzgOgpmDq9cyLy1EjXOC05uzXnRreFgTAaJ7ixo%2BF8b5diqUgb%2BViGUQK3hXtLQSwkkTbxyFiCADJMRIhQcKNBVJAILm/CXOBwFqrrUpqPFRK5P4IO/p9JMgw2i/R/vuKSMNAEgU9K%2BPA%2BUHgQD0UmVqkJMzYBhgooB54H5gIGsSWxUYnHoFMctWBGUv5IjXpI206DOGYOwcAXBr8HEPEIV1Eh8soI3TulQjGIBaH0N3IwnGLCPy2NRiLTJ2SGGQPyYjYkviapFKJpErhPCEF8NloIvClc/yiMZMSMJ0j1KyKePI%2BWyjT4wKeq6M%2BS8eRIKPDcYAnp2SmQicxLBEQYnPziZmdxqANkfjmQsms8dr7YnUe/DaLZCygk2gAMUsfMLarBOTmmLAWC5FxQQ4ihDCOE90kTxleGZWMTZHhCIEAvG4wTkIzPXv%2BM80pQXNVOa8ssQgvBpGKJgdAEUFBeHruC1ZODUXosyJi7FuK7HxIRcSDQUYzC0uHuPWkABZAKTAqC6UaGCl5EKtEhOhfzWMBKYkspaOy/E/R8EPH3kGWezMPxUr/LeXZxIuBYiVeA4k/MGZjw0ZtMleLuVCvCt8clkqRVso5TvJENKHhcFpfSomH9NoABVvhJm5exPAyAXZYQSAQCAUMFAjh9V4tFGKsUmvrlGfVBAsQjPOW8oEVzaRCAaAIOS0lHn0HBaWRN3LgXHAeES8NMb8XRKLWGklEacX113FwSVCq3A2rMAy3VzLWVis5QwcFkK14CqFka81nb%2Bh1sldKmeR9iQKuwOqzxSI7UPEhGqkAyqkRauOTqgtZZS2GvLTG0dGYHhDstTkOt1KowLrpQ8FtjqE2Ftdfcj1osvU%2BqUG0AN1CQBBrYCGpExaq37oXYBuNjoOAbFoJwfwvA/AcC0KQVAnA3DWGsEqLYOx7pQh4KQAgmgwMbBogESQB4NAAA4zBmGSMkLg/hSMka4IEQI0gIMcEkLwFgEgNA0pg3BhDHBeCzRpTh2DYHSBwFgDARAIAtgEFugQcglA0AcjoAkKII5OCqBI/JGq8lJAPGAMgNUUgDxmF4JiwgJABJ6H4IIEQYh2BSBkIIRQKh1DCdILoO14d8JpE4DwcDkHoO4fg5wbCKJZMPFQFQB4GmtM6b0wZ21RGzDWI8Ep%2BgepcRcDWLwITWgNgQCQIptIymyAUAgEVkrIBgBSDpTQeuCRZoQFiEF2IERWjol87wVrzBiDomwrEbQDQhNYcU4c7CDBaAdbc1gWIXhgDIVoLQWa3BeBYFoUYcQ03LFDbwNFZbcHtQNBRHsLDEQ2TMbg2iWI%2BFeseCwEF7MeB2MrdINFYgsQSUvHW8ANERhcMbCoAYRidIvjhwajBrD1nhCiHEA5qHzm1BBY8/oQwxhkOWH0HgWIs1IAbFQImHIy2apkgzKYSw1gzA8be9aLAOOIAbHqF2lwMMZh%2BDtWEJYlRqh6GKNkAQrOeeZD5wwEYXPVg9D6E0BYAu7WM/6LY0XYwai2Gl54ToehlRtEVysGoDO0O7AkP5jgUHSDcd4Lx6LmntO6f04ZpL1jcDmYy5h7L2H/sbAMkwLAiR6ekAI5ISEB5kiQkYxoSQZhJCKQ0P4eSqRmOsdIOxyEXADzyS4PJEjyQ6PyX8JIajwf5Km6C7x/jIBBP/dExJgrUmwsonk%2BVqyxX0uqbYJwVoLAjSBBqkwDCqPbXJAPCng7%2BAiA06s7IWzsPpDw6UIjtzug6VeaYD5lbRuTdm%2BCxwULMmUQRaizF63vecFcAH0PlLjeSsIihGYV3uWRPV4q%2Bl%2Bvj/xhMyMCfrgNK6tsmII15rbnut2tOtSBADet%2BtBsHBgDRtTJxtJsgsZs5sFsltgC1tUdNs4N8BPRGg9sgtDtkBjtgCzteggsrsbt0Q7s9g4NHtnssM3sPslAvs0C1kK9AcX4FAQdMAwdwxgCodJ97Np9ZAEdXM4MF8Uc/sycrAMcrs6c8cCcuJOBid0ZSd0cLBKdzdqcBJvh4AGdegdtnAIBXAZcQgYZtduc7Ved%2BgjCLCchTDxc5cpchgjD7CBAFdOclcNdVd8g2cVchhbDddNhtgDcst9AAsi83MLcD84s38YkT9B9iMHcR8SAr9k9b93dSBPdvdKAjcE8k8B8w9Ah/BkgGNIRw9I888wieNOBS9y9hN8sq8kBpNZNn8L9m81MOB284sWAFAjQ1QjRYjwJ5hTNEix87VeCYd%2BDHN5BZ9hCdAQBIRSAl8V8/MQjjdAtwiQta8kxItotOjujej%2Bigx7kIBUsm8EhkjIRUjajRNCsWiEhmi0txgej0Vdw%2BjkhdwBjnZVAdM%2BA6Af8/8Ws2tetgDQC%2BsBshsoCrIxsJspsMDMBZt5sxBkCXtUCNtKDVtttsCtC3M8CCCXsiCLteBSD2sKCHtrQaDeA6DPt2QmC/srjWDgdQdwceCJ9xikhJihCkc5ixC0dycpCscZD4M5DNROB9gbwJCKcqcEgactDccJc9C/ADCWc1cCh2cTC3CddBcSgcgrChd%2Bg/CNddCu1bEnDDT5cFh9TZdPD1dLTfD1SzC9dAj7M181jKiOAdjdMuiejjQDi2QjjHdR9kisscs0iMjxhfd482MQAKMDxIRIR/AaM89ONYzAgM8KjzcqjbAy83daj8MQBJB/Ag96NAhOMSMUguAuAyMzBC9mNIQXT0y%2BNsy8sjcTM0zN9gyczXsGscg8ygA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_erase.test.hpp)
