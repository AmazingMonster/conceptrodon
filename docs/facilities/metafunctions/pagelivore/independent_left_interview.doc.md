<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-independent-left-interview">To Index</a></p>

## Description

`Pagelivore::IndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Vs..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Vs..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Vs..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentLeftInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentLeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = IndependentLeftInterview<Equal>
::Page<Args...>;

/**** Test ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentLeftInterview
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSGmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSxRKeZgSUwvEQAHSq7E3SFMBQKVXK5TETD4URirGgnGXcbELwOVkMLBPO2MAaYKgEFmCeIANzeAHdcQB2KyXG4hm4yjlyhVK1C6kIu4R4LCm80XUM3S3Wgg3fWoIjKJjAeXB0MmQPAtNpjM2oQGBQIcsVkOloOpxsV8OS%2BVwxUqtVmhtt0NVrM5vMFoutwdNwPp5qOZAagTjTCqFLEG491A3T1iLyYGGBgC0XFLd1hFgPZ9BLYHU47ke70ZuADE8MRxtTi1PZ1abaPUPmhYkq%2B74EJ%2Bk5Ts2JZft%2BQ5zngC5oAwy6ruum7bru%2B63rBB4tjhg4mP4Vj%2BHcEBLDch7quSIAgCwTAANaYMiGTABE6CoiSGQAF5MWB/YwfhJZlgJgkVngVCLshYqoTCImiaGUC6uYABsKn6oaCFyqabhxq6QiJu8uqkC%2Bb4fmaNE7t4mBLEs2HyUJF4GgQ6wMDcGjnpeNIQfZoZ1Eodk%2BVBTkuRRJ7Xp5cn4aeZEBZB/pXnhsGnueXk4feUqPkQJmgcZ6FCJgSHoLl0a6gA8gQCDxMmsWVmimbZsQuYAeOwGmQQxn5YVxnlZV75Kfx3ltlBTaRYOszzpJKFrhuT6WXusmDd%2BzY1UlRGEaR5GUWas7oDRdGMcxeCsYaHFwtxvHgT506JVdobiZN0nTStgmKWqZiqe96lGlpJK6QmSZGdlZnYBZmE2c9UUzsFxCue54XJZcEM4X5%2B73UhU3rkjsGvcqKlqQa30mr98b6QDqodQVAjoNioNWeDo2iUFmDOTDNxhReCNAgzgkozcaNLo9xBY9%2BEDC/h/6AV2bg9VV/Uprdg60/NYBgLCdyhWLg62dzkMczr8nQ65ZgwpYDVNZLJIy31fbywrjZK12euLfZnOa22KNu42TMs65x4eZzt3RdrzsEfFKU68l16xZHN0VrF6VS5uuoXMABrik61WRV4GRGNm44wqC6s1lqSAgAnZtjkBcIp2nXIEDqNvhxBMepaGCdRr2yo15g6eCJnEHZ%2BEwB54WBfqxLLXV6nPd1w3uP9lHiNh4vXNXEKDK0rc2CqKwHL7l8jLrwfiOb/sNzYAAjl4Yh8vsgLt5lW4ssVWUAFLgcO59X2IAax%2BNCEPRXNNGIqBPAYSsreZsLIx5qxuO/ZeN4EFeSZDcAAsszJgVAvAEl5MfC4D83BJ1VBcYgwB%2B6D1zug5oWCcFZDHrae0zxBB/XdGKYg3pMB%2BjhJfa%2BtBwI0QttXUhc9qQr0PrcAAKu8LMeD/7IGRFqJQrRgQQCoZg7BDgsgkjMDTEAgi3AaGMkEG4yQTG6LmlhQusCzC2RXnIhR2p4hgUuKojBNDNECBJH7cyejJ4GKMcZUxOifEWJgYXUKtiLAcBWLQTg/heB%2BA4FoUgqBOBuGsNYdMawNhYTBDwUgBBNDRJWPRAIkhlQaAABxmDMAATlqVwfwVTKlcH9P6aQsSOCSF4CwRIhjEnJNSRwXgCgQCGMKUk6JpA4CwBgIgEAawCApCVOQSgaB2R0HiJEVgWxVCVOUoeZSkgbjAGQAuKQyozC8A0kQYgiY9D8EECIMQ7ApAyEEIoFQ6hJmkF0EEH06IUicB4DEuJCSikpM4KVJUyysyoAknsg5RyTlnLZuU42EAPAbPoJjPJSxeATK0CsCASB1kpE2WQCgEAyUUpAMAKQyQaC0DYaMiAMQIUxHCC0BEwLeCcuYMQBEpUYjaAKhM/J6y66lQYLQHlPysAxC8MAQhtBaCjO4LwLAdEjDiHlW%2BMVeBPTvAhSuAqSotj5PCGKTpyTaB4BiOiQVHgsAQrRHgXpGrSBGuICApQDxtXADtUYIpKwqAGDIQANV9KVB0vL3nCFEOIN5jz5BKDUBCv5%2BhDDGAyZYfQ9rRmQBWKgFIDR1WHnJGrUwlhrBmEGd6u5SZ4ArDsAa5wEBXBTD8EEUI4QhgVBGAUdImQBBdr0IUEdDB5jDCqN0NtjQJhtE8B0PQraPELrmH2hYg7bCLrHUEWYrRp0DqqC27JmwJCgo4PE0gAzeBDJuIiw5xzTnnPRTcCAuBCAkBNqCLg%2BKCkhpWJVJgWAEhkVIKUyQoJlS1NBO0jQkgzCSGUhoDQ/hlK1P0JwbppBel/uVMpLgylKm1JacpfwkhGlweUreiFQyRljMA5M4lcySULJhSsqlNKcXbLYJwFoLBPT%2BkPEwDUBhc5cFqcqLgFTrn4FufcoIKbnlJukCmz56afm6GSACpgQKNVXpvXeyFHBoVLKVDceFj79nPvE9mtm0nZMaA/Vi8lOLf02IJSG6ZpLUDYviKs6l/n3MjE1EYKT1Q%2BB0BZZQdlPz%2BXcrjYlwVwrRUODjZKp00rZUQoVUqlVaq41auzbq5J%2BADSaKNeq5JprkDmrjVauoEK7UOu5c6rYyS3Uevyd631mB/WlaHj5sNBYFBRs4TGxgcaVOJteep2QmnvnJJ01m4N1arB5ta4WiDJay2cArQQamhcNu1vrfERtxqi1zvXS4O0%2B7gh2mPYsIdRQsgPYnQ0Z7O610ND6JMZdeQD11Hnf9gYW6Z2rr3YD7tu7N1lEh/%2B1Y6wL1I86cZ%2BjnAbNIuOeF4eUmZMVI/V%2B25v7/3eZY8BzAoGRgQc6bh/D0nEP%2Bn8LUtpoIkMoao3Rn5DHbBMcJVMmZ8zFmwqCzxrZOyBPEBYMilgChPQLk9ATzs4x5PfsbQ82Qqn5vxqWxmkAoJSB6YMyC7D17wW86hZxuFCK5cK6VyrrSWZMUhYpb%2B0EAHBfEr8wFylay3c4pAIrlIKRkTK9qciVXBBkSqCOdF5lVU4scq5YK5LqehUirFZl/zUqZVyvK5gRVyqxBFc9SVnVnXNX6qq8an5dWGueqaza3grXHUIg666u5PXeB9fSAN8UQ3g0sb4OG8b0bY2etmy8iQC2PlpuWzoQ3a2c01q2wW5tKTS1ZHVdsaip3LB1vvQ2gyO2W0g9ux2%2B7MO9C9oRye8dw6Ggfaf1kb7s7fu9Gh7kWHn%2BBBg/fyh36Ae0PXB3vxezPRR1eSM0t0GSxzj2OXl0V23CdxNBdxJx/TxHJ2YyJSpxp3AyvQZxADqWVFBFBH8CaSozQzIP9BIx5zgOGX53GSA0gxAEkH8Fg1aX9DQ0qUkAaS4GqXenN1BFgPvU4Ap1wPNyuXoLEMYO9xWG9QyGcEkCAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_left_interview.test.hpp)
