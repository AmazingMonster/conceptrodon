<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRemove`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-remove">To Index</a></p>

## Description

`Pagelivore::CognateRemove` accepts an operation.
Its first layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function removes its arguments at positions indicated by the index list and instantiates the operation with the arguments left.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
             &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
             &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
             &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove variables of indices `1, 3, 5` from `0, -1, 2, -3, 4, -5` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 4>;

/**** Result ****/
using Result = Metafunction<0, -1, 2, -3, 4, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateRemove` by combining `Pagelivore::CognateSegment` and `Omennivore::RemoveValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Send
            <
                typename CognateSegment<Detail_t>
                ::template Page<I...>
            >::template Road<RemoveValues>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYA7BqkAA6oCoRODB7evgHBmdmOAuGRMSzxiSlpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnthVARXAAxYiyf5ncFMljpAxMkkEDEfZhsAB04up90WxC8DnpjJZbMEiOSVmSLyRVnukO5vKY/ORur5mBJTFRqHFouxTzhTAUfyEmAAjl4vphSE8zURLQA1Np4JixegKSV3aWygjypkMdCs2Qkx0ut0kv3EANB36W6mBHHa1WQp6Fp5G/Um5Fei3iqKYADuqfTwdDRaeXmyRieyiYwEwiMCLyeiddBLLbmrdf9geDlo99cnmYlOc1uPVS%2B1tOeftoHNOXMwPONpvNT1nGdD4blm%2BXFiei31eGQNoEi0wqnSxE9R4AbmJXSqLCf6BMFdAmvICNRAmkHjpZRiEwGhVG3a4dT3PUDTcQVhVYd0bzwAAvTAAH0CFDNBh3SSMYLgvAEKRfsCBlMstQhddTgHBBUQIehEN3fdS0Pb0F1zMN6IjNiOMAiC1yg54ACU91QT9ME3V0/gBZDeLQjDGCwrNFylES5TklgFKUn9fj/MDV2Y6TWIsO0ezcezuPU1CRwrS0AEkzwMyMjJM5TfhJckQBACIsFUAilCTYcSQ83ScT0iF83uZsS35FKixJAtmyLQ5DieAB1HtWx7EwADYNEo%2BDYuxLMKuLVAnkYHwElLREKrjQQABU2m7AgQwqq0MpyjtYOq5EvJzS1OoIHriD6hRSGyka8sKnt0DZdJiwQHtIkZT15pawQhruEbCy0kV3WWnKLp08U7OQABrOaFuupsi1vRwH1I59vy3CsnjwdAMVoCANmu1aolQJltv1dqNCEdiCE4k16rwP4IlvQQAyZdAnliDEnj%2BlSIfyl96KYBxMDxqg2RYbaezSnt0jaLCmWIBQTubVauoQdHAb%2BeJRBKp4ax7Gs6C3FmnqaxTiEJ780znUnAcERryo0S9BuugBaa1EfEk1ht7NxrubGaXswfqQuJzBpzNosHue3qrYUG2zKzY3syY66mf4ytRTuYBYL3Rh%2BvewtWwiYAOy7Uq%2ByeLA4S0iAgZBlMxBJIOQ7YQQQymwSwfBySkvAn37j98tzU8j13PFAApbyZUM%2BTFIC/O3GC0KYxfSLnSHfZYvij0u7C3uooHkd6/i0MgKY1KUIPL3kQdwtVqKlslHhqrqJqgurXqogmoYFriDajWLZd8PteN5sd9UPfsGmpVZqvxbV6edf1s2hmnj2yNepHQIFzM6t02BLVvrlfKG8RYa3viSRu%2B8NYNSeMARqlM2T2l/vgLGg9IFr3yvEAgYtGDFhrI1GYC0QEjXgciRBT9xQAFkgboHoJbfqEDTpnS/onH%2BBAdp/3JgdYAQDqE3SFNpcBH8wF23upTZ281XZvUSs2T695HwMF%2BmID8R806g3BsbPWOYxLI0AsvU2%2BCniX0UdbEAtt7aWOYRSNhb93beFkaKThZ0nhO3YW7OxHsJTLwSuXLh51F58SrgJQOwdMChzzhHTe0dY7dl7P2JOtAU56IzrQLOsT4nhyQTmIuVlLIl0hMCY4Tw5LIF2NkRSTxHJbzUhXCJaE66ig8rXauDcPQyMtAAeX4QkQcbp85CXPL5Vupl3Ed1Hj3CKE9kwTWHjeAg6AQpj0Wf3ZZbhp6CQ9EMnaxBRnDk5oJK8vs2lGzCSbD%2BPDYEVVoW4SaDCD4aBQc1NgZ8YYXxfn4jWYi75jV3hNWq4prELS8dw6B39UBbWGYI/agDc7AOkRIy60KVqws3qVJ5IKH50PBe8lBaDPTIEwX8RFODWgxUsatIhJCGBkIoW/IFRZnn0MtE41hmA/FYpyjwja8Lf7/2EaI9FmEpGWP6XIp6ALgnXTUd9J8TI/o6ManosGutrQMmjLGF%2ByiLG3NShirC1TpntxJEckZOyzkz0sSFJmKSRy%2BNcQE9xDrbmJKddcl1RqP6Qtdm410DiTVFh5S4mx/j7FBO9YucpxtK6OR6TEnOYdxnXSju2TsqTaKJ0aJkiRqdga5ORJeZE2c4movGfFEp5TgKhMqY0pg6QFBeC4i0u4ybZVWkSpMltbaO2MUgs2x0MZnKtI0iOXtTdRLjrxnPMpoSe3XP9vFG0BgsGnP2N06JAFAr9p8gOVwCY7WD3LRODM5y%2B0JSEkupNa7DRPpTdE60tosEDI%2BD83IiSB1vFaHQN6yVw2RzbDHLSaSnhftagMDOStr0zxLs2ZdkEF7ToFC%2Bjp76t03qrQUzNxts0xxkkwOgUGANkbLW4fDNb4pOokaUxtkFV0YcNGasUglN12j%2BB4QQZHIhkGLBxjx2B6A1rnXKBdJI%2BOAcEySMTBGkP3pA%2Bh1ymG2PoRExuj9fwYM/oEH%2B49lGgNe1U2dYjwmPhQf03eQzyJFN0YuchzKzGpJqYPM%2BzTs7jG6ctLRjNiTLMyVQEwRdCcTPUYC3nejIAtJMbLqOukXUhT3jEMoEVXbk3YaPc3SMKX0hpdoBlraS63PWWy0eZkeAObEVy6JArRWSskmq7V2e5mwPJMg/mg2piRze2XIlqSlWj6tcWHuxqjpSLoEk/l1LohivwpazV8bJ7pvtfnkWSz3WE69ZRsttrCafblZcp519jUxsEAm2tgQ6AJuDOGRzWbTxGsLea8iS7Hopu3cOY9m9G2s3gaszclDCc9WKnjOxqVPZXvpaW8iG1HNYvxZUUWX107/UfZW1dm7MYBt5iG9ZZtHhgDMCZI6YAqLJ3dpfSNgOOGePQe/XZhgz2Sdk8wBT1FlzH2aeyPhIiTwuk4QF8AhuRm8uvCtlR4Dm2RrJv54RMXooADSiTmywRdDV8yEAsxmDKuYMqEAVcmyePXDYBjQNJPbAACRYYwQX%2BbbNwYmh6euOsVdIblyqQnVzNMdOi4UoSzZLO5vjv2aTUPJEw/m3D9IeT00xcEgxj4Pq4t%2BtI0B5EkWE/Vozcjv1duKQO7qyE0d%2BUPIxnvOZUQzKxAKEavEJ4LN7TU2tzHDW8zwp92ioPG%2Btye0iYl6JIvWBmVld97z9TyJFeC%2BF7P5X9ClXHtH4wIK6zNkLJ75PWKbvlOy%2BkS%2Bhflo1eo5Gprrw2u/i64lPrw3xvTfm8t94yzkXHcJ2d7%2B13ZuPde7QxZoHHbCPU9KPS6F7WPRbePb/fZW9FPMsYPM6dHVyapGXbPaXOgIifHb1E7KfM7XtQPQjW5SzRhTwcLfsVfVnStfJJzWAuLRjBtSfGyUEZgncCpOkDyfcApFnanSpFg0EcEU7SJdCLDVNBnT9ZnF3CZY9dnUsPyRSHnAfI/PCJXIXEeZQoiS0JfIjIHN/SMfNRyIdCSTuDfEAFgJgR6QiLZbfXZV5EeEwswiwgiKwpZGKOhHWLgYlLAv3afTudQ5XV5ZfSXGCaGVAMPA/GVEQ/dK9RsM/HKUPOOKDaTSxLKSxU1aHE9PHVIzKFeLI%2BXETRpVAUnUsLnMOEkXQ9XbxNHdPDHMIlZC5XI3sbAJA40apULGbZEOQmZEmWI7xZotqWotwA9f7Ho7IhAkaPomGTPajT/ezMvMzRgjzIQgPagwLWI%2BIvNBOYIogAYggv/AnUpFiPg1gw4%2BUVgXkHsLtXgvggQ7UaEWEeEeOUkAQfYciQgtg54GY5lLLSI%2BnerOUT4g4pgp4RhaXKgLwAkAYanOnfzeaQg4g0E8EpoAQKDGQpkTo61CQr/ISEKAYrgD0YIJ4fwUMHEuOLOWEvYonOkIQLwdIEoamOSdtTJanSzak2krIek34DtPQj/TE%2BzNwNIJ4MwD0SQLwk4hkrk5koHcUpk/NEE1oMEiEr/fkj0dwj0IUp4HWAk6QDUoko7JLZ4LqX4SMLtZVAiHjBIAgCALuBQLCM0juVkuk9AaUnHZ07EYuCwDgLYWgTgfwXgPwDgLQUgVATgU2SwawG8HYPYUqaEHgUgAgTQT0rYR6AISQUUDQAADjMDMAAE5syuB/AMz0yuBkhkhpBvSOBJBeAWAJANA0h/TAzgyOBeA3Y0h4yAzPTSA4BYAYBEAQAdgCB0hURyBKA0AeQ6AEgogsJOBVB0yyodYypJBUFkAHwpBRQzBeBqZCASAgY9B%2BBBARAxB2ApAZBBBFAVB1B2zSBdA8Sawz50hOAeAvSfS/SEygzOABlURBzIxUAqAngZy5yFylyVzUyzAngIAPAxz6B3w8QuANheA2ytAtgIAkBRzCsoLhyIBULxzEhgApAhSaBMkEg3YIBYhXzYgIg2gMQHzeByLmB5YBlYhtBGg2zYzRzUUBkGBaAqLLysBYgvBgBHJaBaA3ZuBeAsAzCjBxAeLtcmhFIRLAyXxGhUQDhYyIgmRyzAz0RYgz55YPAsBXz6I8BqzRLSA5ZYh2S3gJLgB0QjAEytgqADBgAFAfQfgawYN/TYy9zhAFsjzpAvKzy1BXzrz9BDBjBrBrB9A8BYg3ZIAth4UBgRKdZyRaJTAwzLAzAGy5Y0wsAYqwZeh%2BhcgXAYw5g/A8SwgVgqgag9ASgcgBASrqqshaqGBRhKqJg8SGgkTBglh6r2q%2BhmLmglgWrxhEh2rurPAug9Bbx2ghq1gRqtgG9dh9gJAnyOBfTSB6zeBGy/zZz5zFzgBlynhVzQKIBcAtzoKYy4K4y7KtgdowsJg8rkzJBAhRRszAhSyNBJAzBJAKoNB/Aypsz9BOBKzSBqzAguBRQyouAyp0zsyiyyp/BJB8zXqyp1rXzGzmyQBWy7LOyezkK%2BzPyhyKBMLUBIKJypyOA2gWBPxkgdYmBuN2wuBszRRwaFL8AiBsrdzZADzxBjz/KlBArLzdAhTbzW1qKVq1qNq3yOAPyBzUQngfztqALFzbQGamaWawKIK0KEhERoQzBLqEKOy8asL0KibjaJgVbcK8y0gCL2ZiLSLLzaLKLqLSBHb6LGLmLna2Kw4OKuLXzeL%2BLBLhLnbxLQqpLAz8BYJZLfhXzFLakmRna1K%2BhXytKdKMQ9KDhAzDLjLYyzKLK9xQ7o5saHKuxnLXL3LnavLubfKTz5B%2BaLzAyhaQrbLUqrBLBIror4A4ryJchErkq%2BwW7rAMrNqsqgZo7Yr8r%2BrnAIBXAeqQgYwZqqq8SaqBhZ7l7cgF62qJ7OqhhZhxrCheqCqBAd7lhKhhrJqxqChSrphhgN65rthFqjzxaXzLytr/zdr6aY5Gbma0ywLTr2adawb9brrSBbqsBEg8ryzgbQamaPrkh/BsySzAhPrvrEbUaX7OAMasb2ykLcakB%2ByvyMKzbiBJy2BOBKbAKWAFBPwHxPwv7jRFgNy2btyNk8TK6fKJA/LZAAr66dAQBggRb7zRKn60GGz3yCbvzfzVAKGqGaG6HSxFgNaSatbzrAhAggHsHOyUKlHsLCHtGoK7FkBaSCJaHsyCJ6GCACIpG/K6BbbKB7bAzXbuLYzHGGKmKHBPaSb2LOLuLw7MA%2BKBKxAg6TKQ7JKM6xKZLHA5KY7VAlL46TLE6NLeAU7KL06DK0xs7eBc6lBLKC7bKNHi6nKXLaxy6TK2HDyOGa7uGgq%2BGm6wq0qbAtLcqu6ErOBDhgoB70rMqEhsqx68qOqBgir3A96r7yrT7ZqGrShchV7GqBhb7Jq%2Brt6L6JqD7J6uqb6Kqz7RrhhZ6pqT7VhF75rIylrYLAbVrn7RGOA/zpHqGiY5GmQFGTqmGVHYL4LgHQH7qVqoGkgmbVH/ACzEbazVHkhoaRHNqMHbBMarrsGkyQBJB/AXrizUgMzJA8yuBMz9dTnAhzmwWmyoXEKVr1zQWpbXnoXTKiLCrJAgA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_remove/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_remove.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_remove.test.hpp)
