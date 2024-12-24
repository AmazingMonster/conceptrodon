<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-situational">To Index</a></p>

## Description

`Mouldivore::Situational` accepts a list of predicates and returns a function.
When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational
 :: template<typename...> class...
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class...>
struct Situational
{
    template<typename, typename, typename...>
    alias Mold = RESULT;
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<typename Initiator, typename...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator::value+...+Args::value) < 10};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Situational<SumLessThanTen>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 1>
>);

static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 10>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 2>
>);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<typename...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<typename IfTrue, typename IfFalse, typename...Others>
    struct ProtoMold
    { using type = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<typename IfTrue, typename IfFalse, typename...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoMold<IfTrue, IfFalse, Others...> 
    { using type = IfTrue; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgAGwArKQADqgKhE4MHt6%2B/ilpGQLBoREs0bGJtpj2jgJCBEzEBNk%2BftJ2mA6Z9Y0ExeFRMfFJCg1NLbntY30hA2VDiQCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkizJ9GyCTLUM1wenF1fHv8df5zO5wImAeBhBJgAzG4QWDXpgoTCAJ7JRisTAAOixUOw12QBgUCixGOUxEw%2BFEIIUOKBo2IXgc1yEhC8r0yYiBJgA7FYLtd%2BdctltrqS8CxGkjrrDHvDrgB3Oi0a4CWiS6LXDoOclAgWC4VyhCMa4MVAa1HIPBiPAALzZAmueAU1yYADcmHQmJF6BidQKhXd3qtiHimEpSA6CA6nQbGL7%2Bf6IMTzHFk6TyXhKZhqdDblQACr0zDh3MAMTEYeuAHkCIbiETsZDsCAQG7vJhFtdMK3WVSpaaqOXMXGpaCZRDoQQUWi2Hd84Xw5PUcwZ6XBwup8vMVjq7Xs9hh3SGZHSagiABZTzoYfcizXLzpIxSqfXKEAEVnZdoSiht%2B5r5/nJ8n6wp5ggjrXMkvSWkqCjmtBNp2u8Cq0Eq6qaiCV5AfGwp4FQ1yJtiZgpkRaYUvC2ZuLmBZeEWH5rlWNYxPWPqNs23btlGUqFj6WEjnC47Iku6KztRtGLtOmB0V%2BYkbuixI7kxNK8WSACOXh4GSToET6RGpmSZFUoiVHzlJFYKXWSasS2Yg0YsB4EPSjInuel5GXONHFlQn5mYxFkNri148neD7AE%2BqIvpC77GTRP4vly/6QrygK8dK4IIhOslsMS5zAGSoKMAQe7DveIShRetDoBF77Oag5VXtCOV5c8hWWfuiWcvFAEXECPx/IcAK9dc2CqKwjySZ8PV9f8gGAmYkIhPiXhYBFbhoAwGzJIVSnJZcBxMj4gRZgooGGHmRoTd8womHEGhCAdR0nQwZ0MNdGicYxEH6Rm8I9cKNavPKknIUqkGEn2L43cyBA9uytCvTxwKjmliLiZuAYZK8JDrkJWVYucxDAEVFyHoyd0sIdhKPc9HVJbqoxssgeICKMmCqMkwaRKgnjXOxgUWBAtwMBjRCxNZbbWEmlj44TbE2RxiLXFwGh/l1gKde13XfHtZ6YA0VBeOtbwfCcQKpT9GU41uGLS0T5wlY%2BOt6wbXT2m%2BTIsohHLQmTFPHQgp2xo2QLNnViI261quTTcZ2jE6F3nPTjjIAA%2BqGShNBAozoM2CjoqnFHDo7TD64bmTXtCw50wQ2cgCEIK5WIydrfTgiInX4ZcDipCVwKWfNnXmAN7QTfMw0rfQu31xmNtuo4s24nd7xfe14Ig/EI3zdjwQbeCB3204nZGs7YnGb5%2BnBCZ9XOd56GiKF7rxfO285duD3/LLwPQ8jwwLfbxPu%2BK2Vo2Re5xdRVxrp/dew9N6GD/m4Se08g68TniABe9kIGry/jA8e8CAGIP3N1Rsh8LAcGWLQTgCReB%2BA4FoUgqBOCv0sNYDUQYNgvjmjwUgBBNCkOWAAaxAAkSQGINAAA4zBmAAJySK4AkMRoiuBci5NIchHBJC8BYBIDQGhSDUNofQjgvAFAgB0dwmhpDSBwFgDARAIBVgEGSF4Ag5BKBoAeHQGIYR0ScFUKIuIABaOIkhrjAGQIzKQGIzC8HTCLPA2cuAyEECIMQ7ApCJPkEoNQPDSC6ASXKdeyROA8DIRQqh2SDGVicY4yMqA8K%2BICUEkJYTFbCLMPhDw7j6DBnMJCLgixeBmK0MsCASA3HJA8WQCgEAxkTJAMAKQZg%2BB0BBHWSgkRsmRBCBKIpvBNnMGIEiSskRtCdDMZwtxzVKwMFVNkrAkQvDADcGIL8OzSBYHFEYcQ5i3kaVOXgF0WZsms06E4zYnCB6qNobQPAkR14HI8FgbJDkxSvIBcQTmShXygkMMAaFRgeHLCoAYQmAA1PAmA5SViXK8/gSTRDiDSbSjJKh1DfNyfoHFKBrDWH0DC4xkBlioE2pkYxHB/FZzfKYJhlgzD6LRcQOJgKBVVBqJkFwDB3CeFaHoIIsxSjlD0KkdIbwJh%2BASUawoDB%2Bj6qGAk9C3Rpimr0Pauo0xrWDFiHax1Wrchet6O6%2BYnrlgKFYakkpHBKG6PKZwa49TAnBNCeE1p%2BFcCEBIOw3p/SuEEuWIaJgWBYgQH4f4SEGJJGQmURoSQZhJA3Q0AkOIkj9CcHUaQTRvSMRxC4HEURkiFGJEkLI8tcQo3fIMUYkx2bzHDJsSMuxVSnEuOmagTpnjvEcEaCwF0XJ/FMDxAYR8XBJEYi4CI6J%2BBYnxPSckhl0gmWKBZdk3Qiz8lMEKdwCxqjI16N4BUhdNS6l%2BPjfunFitj2nrehADp4yukZrMFmwZFi50zK6UulDQx8Q4qPUrJZtAVnGIgOs75eztkftICRg5RyTkOFeRcgqVybnfLuQ8p5KFRWcPeTir5tD8Bki6AC0VtDgXIFBa8iF2ToWwolAizYtDkWaLI2ijFmAsUfNxaVAlfBiUKDJRSqljAaWyBvaku9sgH1ZLZSARZB7jDcssLyyI/Ki10OFczTg4rq6SrsxYWVv75WKqc8G6ofznAQFcE6hJuqSgesNQUE1PqzX5GNZkANBq7XBZdgwHo4wEvOoy28bLMxouBudd6nIiX6ZNFS7a4NoaJDhu/dGjgsagONMw4e8DIiU0XvTT0vpAyc2kDzQWyg4bW3tuPVWrkCRJFKMhNW2tg7R36M4BO0xmmrG2PsdUtDK6YNrrYJwTdjSWAKBdIzF0R6MRpVGOetNCqr1MuMxIUzghzOstoboSEpBX3vuKc2iNZSx2cEqQ4pxyo6knbOxdq7N3IxQb2xMjNkIEMbdGYj1DUz0OxHO8kZIydLuSOTnD5Oqggm4fw2sjZWyDmvIo4c45pzaMrsudcpEtzMD3Mec89jvBOOfNk3z35/HAXfOE6Jsj4nvmSbhUiGTSKFUKc4UptIKnsWfI09OrTTBSXkspdSsjT36UmfSe9p9IBvs2a5dKmwknAsubeKKrYfcpVWBlXKmID2lXOZdX4MLGqIukCi3MNLSXLWB4tW8arnqVUhay2V7V6XVWuv9XqmLfqcvldK6n4raXatrA2PVgHjXgfNbJ8E0752eaw/IvD1NIsM39anUM3NmB81DGc6o8bVnj2QkhAkORg7tF965D25bv7Vu2EnYhxYxbJAJDLYork2jRGSBkVwcRREAeQiBytwxzfeEA6iePuhk%2BZ/LDRekZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/situational.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/situational.test.hpp)
