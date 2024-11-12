<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Inject`

## Description

`Typelivore::Inject` accepts a list of elements.
Its first layer accepts an index. Its second layer accepts a list of new elements and returns a function.
When invoked by an operation, the function injects new elements into the index of the previously provided list and instantiates the operation with the result.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I</sub>, ..., Element<sub>n</sub>
-> I
-> NewElements...
-> Operation
-> Operation&lt;Element<sub>0</sub>, Element<sub>1</sub>, ..., NewElements..., Element<sub>I</sub>, ..., Element<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject ::   typename...
         -> auto...
         -> typename...
         -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<template<typename...> class>
            alias Road = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `double, double*` into index 1 of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, double, double*, int*, int**>;

using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        template<template<typename...> class Operation, Prefix<I>...FrontTargets, typename...BackTargets>
        // `NewElements` are injected in the return type.
        static consteval auto idyl() -> Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            // Note that we use a parameter pack in the template head
            // even though the function only allows one operation.
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements..., Elements...>()
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsZqQADqgKhE4MHt6%2BehlZjgLhkTEs8YkAbKl2mA45QgRMxAR5Pn5Btpj2JQzNrQRl0XEJyXUtbR0FXLZTwxGjleO1AJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ4X2CYaAIIHRyeY55fICgToWCoj2ebzMhwYxy8ZwubgIdzSmAA%2BgRiExCApga8QQRMCw0gYcTC4QjmGxSKcmNdUJiXmgIZg0gRTspiJgaKpvgARU4oryYC5WLGvHF4gn8y7ExiscVPV5/YheBynbAMYh4ZAIc5JKxJTkCkHY3H4piEy5ZABeSIIADpbQBJGnyxVMlVqjUwv7oEAgCJYVSIpQARz59Jhdtt1uBgVlb21INOCZ5RrFRPhUrYEaimAA7th6GxBBjo/HE06lSzUEQALKedAlhMmbXnV6J1unAD07dOAHUvl4lOdqhoWWy8Kow48IyYhzzUKdGD4EiavtONAAxYiyAAqrWAmAIGKHkZbbYTIuNpthyeXqZJ0qn0dOxyYCgUpwA8gjUf1ySP2RPowjDdt13fcFHJSVSUwCMLCYZAAGsd2IPcDxpU8E07QcNCzXN80YVCZ1aL4Im0BocXQU4Ih5BAvlZAhtgYHk02PF50NOP4TXVJ8BD%2BTAADcxApKlKPQO5aAgNZTgAWkeD8v04gQYWAwQkJQhQI3JHC81xfD1NtclYIQ1SwIfJ5AkFVjE0bPVzINE8z2vS9IPvW0tLwws0MTfsImAU4a1oCiLm5Ctq1rGE3J0wtTP1LFdRit5hUc8VYTTKCI20gtUOLOVeSVO0GFIhwDTjeyk1FG8zTwS1kVOfK/U8hMyyZELUGUJg93rLULCs0rW3PFMJVSlzrQizKixjNimuZTdQoCzrW0bCy2IW3r0MwqJKy%2BAgEBNU5sz7AcmFONJWmlHFiGOuD4Moxjtq2pLThopg61W09MP4xhqK2YBNTu04qC8CF%2BlOARaDuClaFoVBszfAQvlQeT%2BhY5bE36iqr3KpyhozW1ZOfV8IxeYBWUirKJpR05vKMU4ACVUGerlTiwY5JXm9CIDZlHXXVBAPX%2Bb0WCYeCkV9TB/SDENdjDBh6uLbLLIpxNvTRnFpsrVB/LrS5Rt06LXuW5WHrwUTaBhImSbGjTlXcg9TIkzm2zWeK2Os%2BKHZV5LnJxkacwy3SGrbKnfM1xmWs18LfZtvTIzlparLi2yhQVsqL2SykiEJ4nMFJ8bOqD5l2pXQJgpm1rC7NrOc%2BixPYxsiyQXbAAqZuW9b9sG5brdsCELcW/b14m9bof%2B4S0FwUhaEfgEXZGVzpOPdvdNoNx%2BWps/Jd%2Bjd1586ELw0iKTB0BpzAFC8WgmSCuSN5yGEIgIcl0C2WJ6Afp/6Eb8k74/m6CGbqN6%2B3lkamx9T7n0ZvlQqBBb6CE/oIb%2BX9G40m9G1DqlwuBIJAOHS4j8vDP0wK/XB78MF02ejCde34b6xzsi8DijhkCIhfEoNoEBPTegUNKBhRY3AgLPvfU4u996ZEPjw8%2BjwnbmQ4BsWgnB/C8D8BwLQpBUCcDcNYaw7Etg7BXGCHgpACCaEkRseCAQAAc1pqiBEkGYJIkhJD%2BBMYEDQ/gACcJj9CcEkLwFgEgNAaFIPIxRyiOC8AUCAPx%2BiFGSNIHAWAMBEAgC2AQNI1xyCUDQHiOgCQojSk4KoEx1QpLVEkKcYAyBkCnCkNaMwvBD6EBIMbPQ/BBAiDEOwKQMhBCKBUOoSJpBdBzGzKiNInAeBSJkXIgxSjODvmuMkpkqAqCnDyQUopJSykVMkFU04EAPAZPoBdA4XA1i8AiVoDYEAkDpLSJksgFAIBXJuSAYAUhUg0HPgkUJEBYiTNiBEVodwRm8F%2BcwYgdx3yxEgYC0g6TMrvgYGDSZWBYheGAG4MQtBQncF4FgQWRhxC9PwKyRofET6TLFg0a4exdF316JM24sRUSgo8FgSZKI8DeKxaQElxBYhCM5LiQwwBbhGAMRsKgBhgAKAAGp4BzOveRuimnCFEOIdpSqulqEmf0/QgqUBqMsPoPAsRQmQA2AjfomKpKeiCqYSw1gzCBO5WqLAJqJI9D6DkFwMsZh%2BDmGEJYFQqiFEyNkAQPrg3FByCMQN4w5j1EaAIQY0xPCdD0PG/oSbFjlDGIkONCxw15qGNGnNEgNgKE0bsUt7iOCyP8ZMoJSz8mFOKaU8plSzDbNwHUg5Ojjl6NFRsJ6WBEhuuMZIQI1pnGBBsRoKxkghxOOqM46tnjSDeMCFwcxXBqgmNcdu/wkguAuMCNUOtvSgkhLCf2yJ5y4kXISbMlJdyHn7OyWwTgrQWB8SSFJI6z5qZcGcdaTdijalEGdY02QLTVXSHVUoTVvTdCpEGUwYZWKxk1omee6Zj75mLM/d%2B39T4DAAaAyB7Zuzrn7POGCMwfbTlRPvS%2BhIqT7moD2eMAjP7/3POcVwPxbzzqfO%2Bb04F/yoVidBeCyFnKYX4ThQiglmBkWovRZi3ROLBX4sUYSsieASWYtA6oClOIoU0ukb0%2BljK7jMr2IotlHLdHct5UofluKhU%2BVFXwCV0rZXZnlVCpV0G2mwdkBqnpiikM6pFbaqwBr6WurNYyHIlrrXF1i/ax1CRnWktNe6vTzgICuALSEGWxaVi5vSCG/oJWiihoYOVoNcbegFYGPmlNsx8sJra0WgNJbC3JvyL6%2BYvXs0VareW7YlajnVtrQE3gDauNEZ4xUsj1oNCdvwOBmjG76MDtIEO8YbqLOrvXUB2dSQXFJCSJYsw87D1nsCZwS94SvMxPiYkuZrHmPEDfXsT9qyWAKD4uUvigHrRij%2BDUrb9SvRzCCyqkLHT5DwYizoEAwQUNodGbNrDT2OAzKSdcEG%2BHiAsEB8D0H4PIdMh2exqjCQduBD2ze6Jlz6c3O%2Bxz/ZIAQf70RGD5xiIacMLJ0UvgdAhOUBE4oyTALOVy%2Bk2RKFcnBAKflzp5TKK0WQ3U9igVeK7PYrwESxwBmyXGeQJSszghaWWaNdZ2zrK1SOd4M5vlBuPMitZ%2BK9qvm5UkkC1BxHEhQudNR1qjH0XjD6psAl%2BASWLWcHbKwjLlgHULadcbXLbr02eqK96jrw3/Vjaa1VyNYai8Rvq412NXWM3taG2mlr3XM218qxxQbqaBtZuWE1stFa2kYbm/WzgFIxfFKByD04guIfLj%2BJt7tO2jknP24dkdGHTsgDMEBwIgR/D%2BFnfxjQe%2Bkg7sewt57tgr0MbWEYkAh7rQnv8CkA/h6l2SA0KkCzgQ8eX%2BCdemchhtUhflMgAbfhsNylkM4JIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/inject.hpp)
- [unit test](../../../../tests/unit/typelivore/inject.test.hpp)
