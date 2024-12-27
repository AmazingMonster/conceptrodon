<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-inject">To Index</a></p>

## Description

`Varybivore::Inject` accepts a list of variables.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new variables and returns a function.
When invoked by an operation, the function injects new variables into the location and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, Args..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: auto...
 -> auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<template<auto...> class>
            alias Rail = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 10, 11, 1, 2>;

using Result = Inject<0, 1, 2>
::Page<1>
::Page<10, 11>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        // Note that `Operation` is invoked by values
        // extracted from the template parameters.
        // This is because we will pack every item
        // of `Variables...` into `Vay`.
        Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                // Note that we use a parameter pack in the template head
                // even though the function only allows one operation.
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Agreements..., Vay<Variables>...>()
                );
            };
        };

        template<auto...NewVariables>
        using Page = Slash::template ProtoPage<NewVariables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhpcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbgA1JjIhkHJkstlMDlwwVEHWtPBMWL0EWXCZKhxW1HqgDsFluc0cyFuYommFUqWIAqFtwAbmJlTDPbriDa7Sr3fdVbHU4E1cCKQDc98NZSAJKs%2BhsQSm7IGs4FvO1oE1g63bAMBPIBBVo0l00quFcnmsHvoq5Orwu5ut9smT1TjNZkHMrtmtyZABemAA%2BgQAHQ7wsOkdjlt4Nv4okgEARLCqddKACOyvF%2BMLO63ZMCQ%2BB06utx/CuN7J7NwLVQF8okwAB3eNE3oBQHV/b1FVHSVqVQIhlCYYAVW/X8py9EF4PghcTQ5bCCNlNx8LIgiiIA/FgJfNF/QMBRPgAeWeYgKwEUhKKo38dh2W4AHVMFuLwlBhAA2DRqVpPBVCfNEGOkhVUFuRgfASbspI0AAxYhZAAFVaTCCFg6TX1IvipTkhS4T3d8X30oyTMwMyeKsvi%2B0YAcXwsJhkAAa2M4hTNgzycPfXiCJ9Y9/QEQMo1oMNLTwdBkVoCBlluABaOCqIEnSwMg61bRg5SNAFGlbgibRMAcTB0BqhgFQQUSaQIDYWu8yzLj4wqolQ0SCAQU0dPYrTGhMFS8E%2BCII1QQLGtuWJ9SS5Vwr6grBKDRUAuZJqqAMlhWuG/9tNSVoB2ZYgFF6/rBMMhBZpqz54lEcTRPAr66GSy6gvUiMEn1QgWWi%2BDCtQKgdKgsqPgq5rLWmjRdVRCzwd/CbOKmuFnMEEKwvPdbMBfflithpM7p3fl/KCgm3IUInoxJnc3yzeCZ1Vcktp/GjuzooVQIgimYPyn9xIiYAqQw0TYXlFC0Jl/FydKymGKizMMRTLn1RzRtCwYOqXXzK4%2BaXeidxFj590Ql0DaNggtfZ38zcA1cN0lA2rzFhDnWQgzFcw6LcJwiKfwPSUhGYhAMZ/XDY%2Bo87zcFncVYTOHYKisOYtt/3UNQdCg%2Bzjmvx56yIcEwbmVasbvrEiSmFuS7OLYG6m4CwLmtOv9F1EtqmHQBOHsBxhWvWYB2xG0SqC8bFGluARaH1MRaFQcDPgEUTUA4riGHu8vE97zkk8Ai3X3fJimBYl9LmAGkWUYMyfYP%2BvJduAAlJg6FleUsEhbyh5UQgIA8u45jwxzhGeEALAmBLXXJeIMN5MD3leIBL2QY3wfhfnxc8rspT50LoBNO0F4asyzmXbBv5cEnxqulWg%2BJb73zLGZUmrp8RW0ztgdW2AsogIIssHWFCqKc01tnERc5s6uwFkQIWJV06U2fr%2BCWRhpaYR/rcKOV8kAgDwQrAuSs4TEIztwwRJdZzc0IifaRIEdyMMwA/QQnDorKKloQ9RejCEMLvvY5hVNz7olEZ%2Bcxutri1kBA2LU2BVCsDZKJE2oSwmMm5pqW4WNd4dnnFY80Kd/EggjqkneOMJEJMbEILwqQiiNXfh8LwtBJTxJcRo8plT0DVIULUyUcsCmTWyPiDQ/IagDJSLcYZZg2bJMpG0jpGSriNKmXU9R9t6qOzhP0kZ/IxnkPPJ4uEXAHTbIMW4QZIy9lbJAJ/Og%2BI0k4wCcUlJhkPj1KScOFovp1xXyUG0CAUCFADneZnNw8yCD8jKRUjIVSal1LRAIzMHBVi0E4P4XgfgOBaFIKgTgFFLDWG9OsTYsswQ8FIAQTQcLViBQCJILcGgAAcZgzAAE4GVcH8LSmlXB3TumkAijgkheAsCSP0lFaKMUcF4IzfpJLUVwtIHAWAMBEAgHWAQVICJyCUDQKyOgCQogDk4KoGlkkcqSUkLcYAyA/RSC3GYXgjVCAkDSnofgggRBiHYFIGQghFAqHUNK0gugUjgU4qkTgPB4WIuRaS9FnBWIIlVZKKGtwDVGpNWai1IyqVmFuBADwWr6ChkxFwZYvApVaFWBAJAmrUjarIBQCAVaa0gGAFIMwfA6A3UZhAWIUbYgRFaMiUNvBe3MGIMiVisQHaDtIJq5hrEGBLyjVgWIXhgBAVoLQRm3BeBYBgUYcQfr8A0gcHgIGm60VBnqgibYRKIjMh5WipEsROKjo8FgKNio8ACq3aQIGxBYjgseLu4ASIjCktWFQAwwAFDaneOBCaKKiXOuEKIcQHqkPerUFGgN%2BhDDGGsNYfQeBYiM0gKsbejRN05SJHLUw2LLBmBFb%2BhMWASNZR6Ms7ILgGDuE8J0PQYQIjDEqKMFIRQsgCGmH4UTGRxMMAWCMao7Hj0CH6FMXj%2BRxj1A4ypyYgxBOLBE7YXTkm9BzDaPJ4T1RVgKDxVsCQ4aOBItIMK3goqk2GuNaa81lrM3ZtwPagthLi3ErA6sfuWBEhsYpZIQIW4GWBC5RoSQZhJDSQ0P4SSDL9CcD5aQAVgQuBbkklwSSNKGXsskv4SQLL4uSWc1G0V4qQCSrA7KhVFalVxrVXWht%2BbdVsE4K0FgEZ3Q5UbpCXDIyGVbkK%2Be/ARBmNOtkK61D0h0NKEw363Qrag1MBDVuhzTmXPRo4LGlVCIF7Q2TZ5y%2BKiuDTdm9m3N1b80wjBGYYLpaZUdd6wkdV9bUB5tGBNow93Bk0DqQkTt3a/XDv7VOuHo7x2Tu/TOx%2Bc6F0HswMu1dK9N1Ep3bh/daLD0cdPVGi9yAr1TtvfUKNj7n3IlfdsNFH6v1Et/f%2BpQgGieS1axBjC0HYPwanUhlb7q1uyAw76tF22cOgdo1YSwhHiPwDI6kCjnAqMEEHnKRX1gGOuaY2lD4aulONC4zxvIUmQjcYs0saTxRsgmcd7J%2B3hm7DaaaMZ9TNvPfKe9/MfTCnTM%2B%2Bt6HoP5QQ9FrWBsOzMeeVHYa5wdzKbTUg6lvdmb1K/PzZIG9grn3QukHC6MNjPLcv5em0l90/gGWcsCMl1L1X6t%2Bsa7YZrIXpXlva0gZV8b/u/eIP17YQ3U0sAUBGP0EYs8AQmLavPi2Uhi5QxLz18gNsy50CAYIu39thuy45yNbeY1dYTVd8fk/p%2Bz%2B7BMJ7gOXsJAL4EIv3fZWVofzWwfn/80gCnxU9cGfBldcOfAgdcVQE1NtSHW6SgGHNFRHAdb9BA5HZZKdNHQQDHRAknbHFdNdDdKdQnPdFnbdPAI9RwcnP1Snanb9Wne9XgBnftZnd9BMdnXgTnADFkXnUDN/AXKDGDCCEXb9FfN1CQSXL1TfLDHfeXPDOjGwR9VjdXTXXYM8fXejRjBIZjU3Ujc3TjCAVwF3W3dAd3RTMTRoAw0w7IYw0zLTAPVTdoX3aw3oHTSPITB3IzAYAwszPTKPSzezWPfFPwxPY/EVFPCA01CfKfSMG/ZkO/CAfzBbAvItEtYvUvSLBzSvEARlLcQIQIfwVlarDQDQHI90UrVvEIsVDvFrbvclEASQfwOLDld0QomlSQZlLgOlMwOrHlQIYI1zTgZI6ow/G1Movoior7ZYVYX9TIZwSQIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/varybivore/inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/inject.test.hpp)
