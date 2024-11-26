<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredRightInterview`

## Description

`Varybivore::KindredRightInterview` accepts a list of variables.
Its first layer accepts another list of variables and returns a function.
When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   Arguments...
-> RightSides...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
KindredRightInterview ::   auto...
                 -> auto...
                 -> template<auto...> class...
                 -> auto
```

## Structure

```C++
template<auto...>
struct KindredRightInterview
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;

        template<template<auto...> class...>
        static constexpr std::make_signed_t<size_t>
        Rail_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = KindredRightInterview<0, 1, 2, 2>
::Page<Args...>;

static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);
```

## Implementation

We will implement `KindredRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct KindredRightInterview
{
    template<auto...>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        { static constexpr auto value {-1}; };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First>
struct KindredRightInterview<First>
{
    template<auto...RightSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First, auto Second, auto...Others>
struct KindredRightInterview<First, Second, Others...>
{
    template<auto...RightSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredRightInterview<Others...>
                        ::template Page<RightSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredRightInterview<Others...>
                        ::template Page<RightSides...>
                        ::template Rail<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxBIa0gAOqAqETgwe3r4BpClpjgKh4VEssfFcibaY9oUMQgRMxARZPn5cgXaYDhkNTQTFkTFxCdIKjc2tOR22EwNhQ2UjlZIAlLaoXsTI7BzmAMxhyN5YANQm%2B25ejrSEAJ4X2CYaAIIHRyeY55fI4%2BhYVEezzerwImBYSQMYIubiY11QADokUDXuNiF4HKcANJhdDETDoABKeGACAIAElBHEAG54TAAd2BJn8Vlep3ZpzBEKhmBhcKISIRKJeHNOaIxBFOymIqCIyiYwF5bI5zNZItFHK5kKY0MuWp5fPhgsep2OTAUCkF0oJeFEYIUwo1HPFmOlstQhKYdGBTvZqrFjUcyFNAnGmFUSWIp35qFO1LEXi%2BqoAtFxmQARC4Wc7%2BTP7NU%2B336nW8vXg7W62FG5H7bCmgwWwUvYD48GMAgO2uFp1eNJGU6eujfdNSmVEQe0GHN1tsQSWmtPfPdnN5gvK9nFysxpvEYCdp7r069sLAKUKpP7EduuXnqe7%2BdCrtL14ZrNM0Hlg2XGOnABieGIcZhRdSUcQYPECWJUkKSpYhaQZGF/0AghhVVZdN1LKsBSRKCySEPAsH3ZcQNHd15UVZc0MPUUMJhWjv2rR86zNRskWtfA7UwIjqOdAh0VdMcPS9SceL9FkVVEjVxh1W0QwYMMIyjH9428JNJNFKj1V9X0TAAVisXT0wgVZTmTE0/hAEAWCYABrTAAH00mAcJ0HslDLjSAAvBz3IPLTtI1TSAuC048CoOSFMjc51JCqBjTMAA2cwEvY20S07NwkPGUgBxJPCCK441a0slTE1WVZlxCwLxPxAgtgYU4NCzFd338qrRRqJRKvasTs1q%2BrTLTfMWpip0M2M7qxtzN9JNfZ8QTazVPxLOjlq3RiTRYh9p0wNs50dX1j37Cdh1I8dhKnFtdtnDsisXNUNOm%2Bb0LWzDtyRF57wO9kjtPciLyvQT/rvPc7pmt4nrXF56Kw2MsoIHKfyEboBHQRHGIAeQIBA4m4l4SLAiCiTymCwTgulGUueGcuRtBwJyrGccAsGXxZF7uRWhjsIRXDhAKvHRRI69UGBw8gqLV7Vo59buc2hsH1SziBd9IXBInSac2zP1RoDGTgzpyKlPhOMEzUxapoenrzn0vSjJMszawDdBLOsuzHJJFy3JhLyfO%2B9rxatjkwoisFFOi832ri5FEuSxX0sQgDsty6D8MIu6StN8qNaq/1%2BuIBqmuG18Xx17TOq%2BYODdDqLs9iiB4qSxK4/tGFadRnLedTwqFwz1Ss9LnSaswOr89OIbs2LhbA462glFC8Kq/DSNa%2BCiAV/awn8WJ6DKTJ%2BDKbcRncZZiPA8sjCzwoy5O/5k/p99c/XoHC7Lmb7umPXqre8TU4wDAC4Rypk/r6CqA8Lbh3vk6PODUzDnEsNiXEW9ea7xpBTGER9mYLmAcFR%2B0svjA2viTLuD4/aQNOLgisXx1avy3mle0d8yEcm/qWCeYDqqZhLqfEK5dsHVT6sPAaQCi7TTYeNUBXCxKrg1nNKG2kYYw3ekxes5ptpXT2h2UhHJfrPyHAAs6QlvSXB2uokhT5LaSPBuzShhpuafT3H7bR/1TrCwIW4Oxpj7pMkhq1AA9AAKgCYEoJwSfHAn8YE04AAVLiHZThBNCa8cJwTkkBISQtd4DBjheDODCa4dB7ioQ/HgmxsZyToyIKcAAUsBPiEpTjYAAI5eDEF48xusgwhyXlGaIqBPAm1UpRFk5Jhx6Oqd41mUjOEKMYu44U2iACyw8mBUC8Jkuop1N6QRJig8mCFLgaBylwHKZhjnCksq49xYNnqokDLaeyKi4goVeBARZjQVlrIyDCMwjxLLULcI05pk5iogFKgDPRZgKrzWkkGe5FpHnAheUs95PQBAwiEdgX5L9/lNJacC0FIzLyDUhRYDg6xaCcF0rwPwHAtCkFQJwNw1hrBik2NsJMZh9g8FIAQTQpL1g2RALpfwCJ9gAA4Er%2BH2BKjQYrJUAE59j6E4JIXgLAEgHOpbS%2BlHBeAKBAAcnlNLSWkDgLAGAiAQCbAIEka45BKBoAhHQOIERWC7FUOK5MCVJCnGAMgYMUgERmF4DaIgxACJ6H4IIEQYh2BSBkIIRQKh1BGtILoI59JiBMCSJwHgZKKVUt5XSzgGNrg2slKgcK7qEqeu9b6/1khA2nAgB4R19AowHC4KsXghqtDrAgEgB1SQnVkAoBAQdw6QDACkCcmgtAyZ6ogNEQt0QwhNDuDm3gK7mDEDuBjaI2huiGq5Q6m6GMGC0HXSmrA0QvDAFhLQWeG7SBYGskYcQV6AKHrwNSLihbwzdGuLsLlYQwTkpTbcaImad0eCwIWvieA1XcF4D%2B4gPSlDpnBIYYAtwjC8vWFQAwe4ABqFMMZJEYE%2ByNwhRDiDjVRxNahC1pv0FhlATLLD6DwNEPVkB1ioCSHUPVHBkx/AAaYSw1gzBapQ2Gwi8B1hdBRX4CArgpjtCCOBQYpRyh6HyOkAQandOpH0wwLTwwKjVFqL0OYhmjmKbqH0ZoZmlgWekpMTwbQ9BufmCUczEgFOsp2P5pVHBKWkE1bwbVpwq01p9X6seDbYEQFwIQEgcDOVdu5Xh9YOMmBYHiMZUgArJD7ARAq/wkhEhmEkAlDQGhdIJTlSFlVpA1WcoRAlLgCVRVytFV13SkguC6QVQlcLhbtW6v1Vlo1fbzX9staW21o7x1tpdWwTgTQWDUn8MmJgyj%2BxcDlQiLgCJaUhpIOGo5VHo20ekPRpQjGU26BORmrNG682hYLSm7VJbrXXFOBW6MxAts7b22aA7R2TsaCbS2odbb0sQu7Xhk1A7UCtriHasdaO4cjE29t5M4Op1ysqHwOg87KBLpTVutdT7qc7r3QehwT6T3tjPRewt17b33sfUh59mG327FpfgfEPQf1CbO6oADYIn0gZqIWiDUG7gwcF92sNiGuUobQ5gDDr7sMnmRwRhUCgSMMjIxR3n12aOxru7IBjybaXPZY7h8TVgOMQZ44V/jgnOAiYIOgMT7GLBScizJ/m8nLNfucCp8CtmNPoGczpo5em6ix%2BTxkBPywI9Kccy0Dz0ws8ObmBn1zNm8/qe88X4LChAuxo%2B2FiLRaOBA5B7t/bp5DvHdO02lLob0udqRzNnLmA8sjEK2BlrbWjuJH8MN/wkrJDVa9UchvE3bBTZ7ca01FqrVlsxyt51rqNvA69acFgChqTBmpB3nk4xg34FDZd%2BN1GY0SBtwmh79udAgEVa97NSG69fZarFqLblrhSbYn5n4X5xjX7pSSjNrY7Drpb7CZYb59qo7o4jr2oIFtogrIBJBJD2RX5yr2Q34ED3LH53Zk64wU7Lqro7q050G7r7qHrM5o6nrnqXpC6YA3p3piA85covpYbvpC6fqi6/opr/rICAYy5Uhga0oK5rrK5wZq5Pqa6pDa785664YzZ8CEbG6kbkbUpcqW4v50a24f5Mbf5O7GCB6cbcbh5e4ZBCY%2BIWQu6SbSZxCya/q8YF4ZAuAx5l56AhALDaaZ5p4GaBFJ7GZ1CV52Y1CR71Cl7ZDl7xHZ5F4hF%2BZ2ZJGeZZH9CxEBZbBBadohb17jacDN4QHn6X4wH2hwE95pYdooHZakC5b5aUAfYT4gBmBHb7D7C6S6SJCVAyr7D%2BDdZjbfacCTYGrNHFZmAdZcD7CJSLFyqdaJQaCBBgb7CAGRaTHTa9ofZBrjFAE6p7F8qkAoZpDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_right_interview.test.hpp)
