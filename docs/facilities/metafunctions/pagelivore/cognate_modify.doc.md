<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-modify">To Index</a></p>

## Description

`Pagelivore::CognateModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<auto...> class...
 -> template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to variables of indices `1, 3, 5` from `0, 1, 2, 3, 4, 5` and invoke `Operation` with the result.

```C++
/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateModify<Operation>
::Rail<UnaryMinus>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyValues`.

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
struct CognateModify
{
    template<template<auto...> class Hormone>
    struct ProtoRail
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
                >::template Road<Omennivore::ModifyValues>
                ::template ProtoRail<Hormone>
                ::template Page<Variables...>
            >
            ::template Rail<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFmZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9sKoCK4AGLEWR/U5gxksNIGRnEgjo97MNgAOjFVLuC2IXgcdIZzNZggRAHYrMrnoirHcIVyeUw%2BUjdbzMMSmCjUGKRVjHrCmApfkJMABHLyfTCkR5moiWgBqrTwTFi9AUEtuUplBDljIY6BZsmJjpdbuJfuIAaDP0tVMC2O1qohj0LjyN%2BpNSK9FrFUUwAHdU%2Bng6Gi48vFkjI9lExgJgEYFno9E678WW3NW6/7A8HLR765PM%2BKc5qceql9qaU8/ej2SdOZhucbTebHrOM6Hw7LN8uLI8Fvq8MgbQIFphVGliJ6jwA3MSulUWE/0CYK6BNeQEaiB1L3LSyjEJgNCqNuVw6nueoGm4ApCqw7ofkQoZoMOaSRjBcF4AhiL9gQ0pllq4LricA4ICiBD0Ihu77qWh7eguuZhpREYMUxgEQWuUFPAA8mwDAMHgn4kOwIAALIYHgVDon63g/KxELCj8aRMHsjwSYw0mybBf6QSWaEYYwWFZoukp8bKSn4Kp6mur8QFquBNEQkCRyPBYdo9m4QVaXclkjhWloAJJno5kbOSpak/j8xJkiAIARFgqgAPpKEmw7EtFdnYvZ4L5nczYRfyKEHuW5olTaBj2oZ7zEHeAhNkW55EayRAAEpMHQBZFp5I3NoW1WVRNhbEuNM1FgcByPAA6j2rY9iYABsGjEfBRVYlmO3FqgjyMD4CSlgiO1xoIAAqrTdgQIY7Va00LUWe2kQdOaWrdBAPcQT0KKQ80fUtq09jWdC0MW7UMAo/DECwxYID2kQMp6QMXYIb23B9VWCjZbCPIDT2g%2B9BPWTplqBcgADWZOYM9YOjWVH23o4D74c%2B36wxWjx4Og6K0BA6ys4WENRKgjKo/q10aEIjEEMxJrHXgvwRLeggBoy6CPLEW58%2B5EuPBDL6UfpeuPFQrIowQaPFrVV16e1bCMsQCh4%2BDy13QgGuC788SiBtjw1lDMOPHpDNnZ%2BCRGxOp6U82EMREQCuXq9psALTWkrgkmsnbNuKbzb/Uzz0ZcbmDTqXRZiW1HUMMSFdVylWJtxpFP4wThZ04zj3MwoneulmRezYuwm0T3M3VfVXEircwCwXujAs%2BzC2thEwAdl2m19o8WCwtZEBCyLKZMJiSJLyvknr9gJVi%2BLU/NmBq7T1VztWV/kUNdxTV2i9mKG%2BmBV6CBDBvQsW92yDToL2fsMEZaoFgbQYkICwHPRKu/N%2BU9kLsTQlFMU0UPSEJFAAKTitKJyylXIpQgW4dKmUYwvjys6IcewiolQ9IwrKLD8rsJHGQrBZUxqUznuhH%2BnFKxWhzAAlqDdLr9C6oWHqHY%2BrIKGqgymoiZ4TSmro1%2BSI66S2WmtFsSgFZfVUD9B%2B4pjrp3OmwdqsttoaHLoPFmWdx4TSsTYv6ioAYeJBsYs2piI60FhpbBGSN7aOwxpGR6OMCDe17sWImOlHhMjwJ7QJQNmbd1SaEyG5jNo7V8UiChv07EaBOo8YAp19Kshag7Hs%2BBtYcO8SnZa8QCDh0YMWGsp1pjAxSb3cpbhKm2JFApIW6B6AV2CZ0xaYSw6RyiYjEgsT0YWyxsAJJoyqbpKwgOBoAh0AVwKak6mtkxT9wWabZRE1Ob3kfAjRkfMcKnTPqLcW3jc6yPzirQC3i5pLMLO4vJlcQDV1rmC1qiicjEiyTk1u0L245hHu6EJMzyTzKCZi2FBiFoKOcYipEjp8LnI8ZijuaKu4hLufiulo9xQgsnj5bx4jSHoLvhAniH1oE707N2eBh8Gi0BPt8i%2BV83A8rXnyx%2B6xn40VfsBDlujxFcr/jI7AcigGL2XqA3ljzBWPBQaKxBA1NFoMNRg/V2YfJqsgn5M1DQdhZDjo8EKFj/h4NQr/BexDPmWjIR6a5ooxRiRacQQcbo%2BUQlUYlWhGl6E8OYblfhyYkTFW4twgg6AMq8IzWwrNEyuGGWjbG4c9qREVQ1ZIw0DaQrautLaeRjclGQJvPFNRSCUHzR0R9fRH1QVEpmhDMxodXHjNilUq09jTqOMUaUtxAT7leLHT42C%2B1s2HTFBC4Glze4TvCZE%2BGGzkao22ZjRJd8DlDqOSTZFCwLkhJPSUyx27voVL3fOmp6d6memQE034LTD4axaIVOFEMel9IYAMoZQT70LXGZMy0OK5mYAWUegm77oYRLhoYC9WzHjxN2fskJ4aewUrOa%2BuFVHab6QHpCkMbL%2BULWedzJ87yxCfMFsLH5OdrT0mjLGAJDyjH0cfT2JNyUU3EijWjGNJbq1YLhRlCKZrrVIhJU3R5H0NM/13t2YkjKWMEu4hJ9jM1DP4J7MKwum7R2FIPUPCzIocMfV052twz7clPRpRi5lWK4UYbxeZ4LhLCnebJW4GjMZUXV1pUltj2DOVNu5ba41Xbmymoc6Ko%2BEqianwE9Km1t95W/qxE/d%2BqrvKQU/nZmqTX57SNbc1fVcrwEmrbDvc15Fe1WuGtfLL8rhGOvqyJN%2BIkXUhTSAoLwLFfXhSbQxyzDkqGRjmwtoS6qXWOhjGFW4mrpNqd4ptk5h2xpOpEpqjLLbZFtodCpvYJDtUAVSmVVRB30AJheyOD7NbSo8UHUWO7LXm0L3a4A%2BFpLOpdtUa8Fow1tF1oFb1tJ7xRUxfh24QH42B03Y/mD1b92oePY65aLr995qmv6wfJH2nZWjfASVDTRNsFE79XVCREO1s6r1V62QQ1IhkEx8TGuYpsD0Gyzxb7rhiQeEECLhIxJpd2uESDtHJO%2BerdO//J7sO9MI57YzlHujQczVNdZbHHbYvq95QT1Hk3ieTVJ3z/XAuntU5ZzTymdPUBMH1gNs3qCRsVdZ9xdn7xOcu98rSO6gp7xiGUKgNIR2dIKGjj2VM6JYgyTkuZW7ZO2tfZ7YntIyfaCp/T9duPK2IcCz85Q/iFeq816RdkhYoZLfmO3uL0VgLVZzXZcuevx2S%2BZK7wQN76d4u/bLxdtvohq9p87zkj08%2Be/a6gRjm3A2h9CV89Ph1Y%2B0sT8b0ePzs/Trz5v5aRTCR40bdb0nlfHekTX5OZSj0j/PZnd72tw520QPhEwVHjENGk1JjfxTzXx02jSB2jzLGs0eFs39WMxHC/y31HzzHH2m2nlm1QGAGYEZEdGADviO3B39SkUakNxx2bkX34g8GINLDILvivHmnESyAAC9MAcpIwg0eC%2BDkkxRJl5pEdmZrVUcVUFouC8BeD%2BDLQABpfTIsWCF0bJTSCALMMwLacwLaCAJQ3sNwR4MhJVU2U1AACVmUYH4NtwRVxyDTIWziUKdwty5zERLx9wjz910Tyz3kHwV0gMwhJlz3z1MnkmX1gLSHKyNTGyjxAGskeTQONC02GzcFD1iI1wSM02sPJFsIIFPxm2WmihjHvE0lEHgzEAUFOniCjkAUwH1lNVcTTWylYQKg4Q3Ua2oOCIl0eVUTyKwHgzr3P26J5yELsMEPkOEJDX6J7UGMYDSnzULXTXaIESKg9CEUsy7V7zGI4iRAmJEJFBUJyzULYU0N%2BG0PFF0P0MMOMNMPMO8VNVDzsIG3oI2NMJcLcIsL3yJkCJjH5CgLCIL1ggyiiNXxiOzU2LZ0SI51OMLBSKun7SRBeMKJwPcPHz2Ksk92p2fz8IxyUloGDwPgWIYOZx8MQNhJj1wQ8NEhBHpI5HjyeGin3AwSbiOz8gZJBDBG532N5x6Mh1L11ToLt3hzlx7WYJIMwFkw4M8N10v3J2FI60eEsM2QEGQPEJ7UtQ0XN1VRkNnibUOMeCmIUKOLEKeIx1RNFW20WxHEYRYCYHpj4KLTWNLVnWwDzQLRAAdKdJyhdMzUKgqWzi4Cq3RNNjkNNJilUJUS1PUQcweR3ypi8LFEB2jImn8JFQPwVzhWc0KTBygJ%2BxCUMRLjhQfRCOCiIKlLYLXmJFRLTMKURNlnjOzTOzzLZmwEbJ7H6kDwXzcCMikhBPklkzck%2BxQIbMSKM21ORLcFVORnVPrIWk7IwIvjTDnCBxCQXIRInLszSLDz7NFIYNKn1ImhwXVSHWTINQpLTIzP3gQTjL3iyMd22OPNPIax1wFK1UVL1W8LiO6y7Tp00QtXUWnNxO%2BNpM5K5LBBdXpFYB5B7GWzpK5J3EglxBhDhH3hJAED2EIjxKZPojkGYGIHRBmQYFbEoMn3dITR7QItaGIoiFbFlN0U41eWfFfHfAFhS3cIsGzlii53AtpHoPIoVKFKoou3eNwTon8gUkkKoC8HxH6CEoFO5SBjxNNWkpaFkvkpyGtMrNLBlJ0wPNDAymnJoqIpIoYrKgymbLcC4A9GCEeH8CMpAGstuBUu%2BMkoHC8DSGKEaP6h%2BEW0jAQtNSEC8p8vQD8p20jDeMMqRA0A9GDI9FSEeGznsukGSscrDI8oioCqOzp38olVFXUqYE0saFxziseFsseCStSo9AyqPOdQTx%2BECsZIcjvGQBygaLaAgEYQUCwg6voWyolU31CsyF8vyrROwGVQ4E2FoE4H8F4D8A4C0FIFQE4BLksGsBvG2F2E2ihB4FIAIE0Gms2HpgCEkBFA0AAA4UgABOG6rgfwK6y6rgZUZUaQWajgSQXgFgCQDQOKxa5a1ajgXgYeOKw6pa6a0gOAWAGARAEAbYAgNIFEcgSgNAbkOgBIKILCTgVQS6rabOLaSQOpZAB8KQEUMwXgRowgEgIWPQfgQQEQMQdgKQGQQQRQFQdQCG0gXQWymsdqNITgHgGauahao6lazgMSFEJGyMVAKgR4XG/Gwm4m0m86swR4CADwdG%2Bgd8XELgdYXgcGrQTYCAJANGyvbWlGiAM2jGxIYAKQVIGgCVJ/SgWIMW/PQi9EQW3gd22isSWIbQBocG/atGu%2BMSBgWgT2rmrAWILwYAEKCJYebgXgLAB0owcQKOzQxoOORO5al8N1RkL28gQQXoMWtEWIdqIijwLAMWyiPAH6pO0gOOYgWIUa14VO4ANEIwI6zYKgAwYABQH0b4GsBRRa/a%2Bm4QFfZm6Qce9mtQMWnm/QQwYwawawfQPAWIYeSATYNPfoRO7OMkciUwDaywMwQGputMLATesWHoPoHIFwGMWYPwWysIZYSoaoPQYobIAQR%2Bj%2BzIL%2BhgEYN%2B8YWy%2BoUqgYRYH%2BkB3oQOpoRYQBsYRIEBiBzwToPQW8NoeB1YRBzYGonYPYCQYWjgea0gAG3gIG%2BWvGgmom4AEmiq1W9W3AamnWva/Wg67uzYNGIPcYa%2B06yQQIEUG6wIN6jQSQMwSQHaDQfwLaG6/QTgL60gH6wILgEULaLgLaS6m656rafwSQB6wRraEhsWoGkGkAMG7uqG2Gk2%2BGqW5GigK21ALWzG7GjgVoFgT8ZUbOJgABdsLgG6kUZR3O/AIgC%2Bum2QRm8QFmmepQOerm3QVIPmpgAWpOwh4h0h8WjgSWxGlER4WWihxWom20HxvxgJ9WzW82hIBEKEMwVhw2yGqx62i2uxhp8YQpu2%2B6uKx2j2YeCAV2rmn2oiwu/p9EP2gOhwQukOteMOiOsW6O2O%2BO2gRO/alOpe9O5a/AWCLOn4MWvO5AFEfYfatOEurmsuiu9EKu/YZa2u%2Bu/apulupQNulZ7ecx3ursAeoekewu8e8Jqe1m%2BQaJzm5auJxeruo%2BqwSwNeje%2BAbewiHIPeg%2BvsUF6wU%2Bsh8%2BoWLZrem%2BmB5wCAVwSBkIGMTB9%2B2yz%2B/oPFklnIQl4BzFsBwYGYFBgoKB2%2BgQWlpYCoBBtB5B/IJ%2BqYIYSl7BrYPB5mlJ0Wrm8hhWqh7xneXx/xi6hhoJkgSppRmp9h0gThrARIa%2Bj6%2BRxRvxkR5UfwG616wIUR8R3Rwx0VzgExsxiG42yxpABG6Wy25p4gLGtgTgVxpWlgBQT8B8T8aV40BYSm%2BVkJ2yr5yeiQae2QWegFnQJIUgBJpJoW2RohkVwGiWmxmWuW1QT17131/10sBYUphx8p5hwIQIZVm1qG024tm2p1mt7W6FZAbynKP1m6nKANggHKbN6eugLpl2t2iIWiwZwdoikZwO8Zhx0O8OyOtZzAGOuOsQBZwu5ZtOi55OzOxwbO7Z1QfO/Z3gQ5j65ak52i85mutMa53gW51uvcR5ruytl5/uwe2sD5husNpmiN356N%2BeuNgwEFle8Fsuq%2B6F3ezgA4dKRFk%2Bs%2BhIC%2B9F6%2B0B/oe%2B9wel7ll%2BtlrB3%2BkoHIMlv%2B/oPltB6Bmlzl1BxlrF8B3l1%2B9lpBoYPF9B1llYIlnB7a/BvW5N1JoxzgeWnNn1x4VtkUDtuVphxVvWg2lVtV7hwh7VkAMwPxst/wR63Rv6st5UdR81tN4G2wUxthm1k6kASQfwARl65UP6y6yQe6rga63Q5NwIVNshy1rTo2whim1T2z9T2ppVRup/O%2ByQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_modify.test.hpp)
