<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByClosedInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bound-by-closed-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByClosedInterval` accepts two variables, indicating a closed interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &le; Max) && (Min &le; V<sub>1</sub> &le; Max) && ... && (Min &le; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByClosedInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByClosedInterval
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
// Create a closed interval [1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByClosedInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper]</code> is expressed as:

```C++
(not (Variable < Lower)) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcTC8RFuoVQAHcEqRbrD4XI0mkElDsMCJsQvA5bpdiJgLOsGFh0BYAJ5uWiZTDoe6CBIANzEwJMAHYrFdbkLbqDwe9MFCYXDUAA6OUANVaeCYsXoCjxwOFt0JxIIt2UxFQRGUTGAEsFwr5AsuWq1c0cyFuaAYE0wqjSxFusVQnluXO85pttqFVtuEDlMvMySjEAYRrDiuIytVmAUt0lCORCWW6bM0bztzjeogWJxnozieTauWNfTvIAIlDrVq%2BY3AtbNcLRc9xZKMbK5ZdgOSwYwCOrAviLUKvFkjPrTZh04F6/rDcbF5KhyPXuOIxr2zzpyKwT3IdD%2BxHKyq1Rrj/a8I7na73Z7vb6TWaAPoc9PH0PhnKUYxkWCZKjeqbLm4mYosQObAQWoEltiCRQbc14pgoNbwQ2TY8rhh5XMCvz/McgIkbc2CqKwzxLl8xGkQCR7XEctwALKYC0VBeAwDg5J8ZzETstxuOS4rok6TJKOgtwRKCxD%2Bum/gWFwaKSCY/j1pGVzdhCEoXtKEZksAE5Tpcs4RMA7GcUw3G8Y0PIrqS5KUjxNL0oyzKsuyCnctCqm3Opk7AiAICfvpbjGQo%2B7BYRQI/KxAAqqbjgJByAg%2ByBfkwChKG0EAcVxPF8QIkoBWYaLBIFeKhf6XiYMseFXJl2W5QkBAQGAYDWUV9k5GVaIVbcVXSLc/g1SAdUNU2HCrLQnD%2BLwfgcFopCoJwbjWNY2rrJsS7mIEPCkAQmizasADWASSDKGgABxmGYACcj1cP4d23VwvK8tI80cJIvAsBIGgaKQy2retHC8AoIAgydK2zaQcCwDAiAgOsBBpHC5CUGgTx0AkUSsNsqi3ckAC0ySSLcwDII6UgymYvAsoQJB4Ogej8IIIhiOwUgyIIigqOo8OkLoqlIsQTBpJwPBzQtS2nWtnAAPJwpjeqoFQtwk%2BTlPU7Ttz02YYYeHj9DlmYh3LLwcNaKsEBILjaT42QFAQE7LsgMAUgVTQtDydDECxIrsQRK0dIy7wofMMQdLK7E2iYA4kekLju7KwwtARyLWCxF4wAwrQtDQ9wvBYCwhjAOIOd4OSfEcqmitukncLbEdcn1IrtB4LEkuxx4WCKwQSaA6XpAN8Q3pKPWYKV93RinasVAGCZ8p4JgSLKziy1HZzwiiOIfN74LaiK2L%2BiVygW2WPoPfQ5AqyoGkjQl2TEzoFC9amJY1hmODE9JiwPfCAqw7BJ0aC4ak0w/CqTCBEYYVRRiqWKNkAQ0C9AoMaAsEYiRVJgJKk0SY7RPCdD0Pgxo/Q2jYMQbg2wRD0F4KIdQpYXBQG7S2BIOWHBFqg0VhDbWpMKZUxpnTa6xsIC4BZhbK2NtF6rAQJgJgWBEggNIJdSQgQZSPUCN9DQkgzCSGSMDfwyRHr6E4P9UggNDoymSFwZIt1HofWSP4SQr1tGpDBrwCGUMYbHUXojFGDs0Zqyxm7D25tCZsE4K0FgHJeRkyYJJSuhtHoyi4DdJm%2BAiCAI5rIbmh9pDHyUKfEWugKoSylpHLhPCvFKw4KrDGcJbiawEbrKmyADDzi4GkjJGgTaoDNqhA6Zhrb%2BPhvbR2gznbm2xu7aZntOmVx6VwEGfsA6UGDiLaO4cU47NjvHROycx5pzHBnLOitc750LsXFO5c57bFWvgOujgG4l1Ws3ZArcU4d1%2Bqtbuvdw4D0eTbEeKcJ5T0wDPCuRh56gAmXwFeCg14by3owFOe8Cm8yKbIE%2BwtVrlIvgvb%2BVgb4AuAY/Z%2BORX7v0/iS3%2B/8EiAMbg/Ho4CciQPcCQgosDqTMKQekTIqDcjcpgYKkoOR%2BW0PIX0ehoqyH1HZQIShgx4GLAFXMKY8rGHzDVTgzhawNgcNYeY7hCsRb8J1kI5J3Tek3TDJInJuYZHjLtvIxRyjKBcMsdYtJejeT%2BEel9QI%2BjDFuN4RazgvjYYBKRqjdG6s5kRIJkTGJxAWB6xYAoDkjoOQ9JlHpCYWSpFszyVzA%2B2L%2BbyBKfinQSRSCVOlqXGp5rwYq1CRrLWqhM3ZtzfmwtxZTYzOGZbQIYzbYI2Ccm12OMFnm0msgbEP4elfgHV%2BbtRS6AbKDiHMOsc9l7rjgncBKdTmCHOdnJ5mA84FzELcse9zYUgtIM89lbym6qBbqCH57I/m8ABX3BkGBn3DzwKPI6ELmTQrnpZAJy9TTIvXpvbeGL8kVokDigWNaz71q6cYa%2BNhyXwEpS/TgOx35Xx/pYP%2B3iAFsxZaomVzgICuAYSEPleqaEYKFY0NjmDJWcZYWyghKq2NMcIbqio%2BqdVavyGKzVqqpNcZNQodhvMW0RrbRwbWPac1%2Bn7eKCYDrskkGdaw2REz3VKNGKo36PqQBPRlIEQI/g3puOBs53kDjNPeKjbYPxE6axqJAJIfwWjPq8mBrdSQL0uD3TzKawIrbfOQ1dWdU1jMfP1Is268eCQsjOEkEAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_closed_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_closed_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_closed_interval.test.hpp)
