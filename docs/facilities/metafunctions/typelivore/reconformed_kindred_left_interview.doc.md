<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ReconformedKindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-reconformed-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::ReconformedKindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

This function internally is the flattened version of `Typelivore::LeftInterview`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
ReconformedKindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct ReconformedKindredLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = ReconformedKindredLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

`Typelivore::ReconformedKindredLeftInterview` is implemented upon `Typella::UnconformedLeftInterview`.
The latter is a flattened version of `Typelivore::LeftInterview`.

Here's a simplified version of it:

```C++
template<
    template<typename...> class,
    typename,
    typename...
>
struct UnconformedLeftInterview
{ static constexpr auto value {-1}; };

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First
>
struct UnconformedLeftInterview<Predicate, Interviewer, First>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else
            { return -1; }
        }()
    };
};


template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First, typename Second, typename...Others
>
struct UnconformedLeftInterview<
    Predicate,
    Interviewer,
    First, Second, Others...
>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else if constexpr 
            (Predicate<Interviewer, Second>::value)
            { return 1; }

            else if constexpr
            (
                UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value != -1
            )
            { 
                return 2 + UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value; 
            }

            else
            { return -1; }
        }()
    };
};

template<typename...Elements>
struct ReconformedKindredLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = UnconformedLeftInterview
        <Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {
            UnconformedLeftInterview
            <Operation, Interviewer, Elements...>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSZlykAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSTgTdZTcxRKeZgSYinsw2AA6LXYm6QpgKBSkGVy1WMViYI2XOXypFmzXay7Uy7jYheBw3OQEgT8YhsdAhTBUAgswTxABubwA7riAOwWG6zRzIXUCcaYVQpYgJgjoEAgFhMADWmGRGWAEXQqJJGQAXiWCDqw2IvJgYXGALRcEwxu6w%2BPd3ugqyOy4KjlK6VWk3i8dSuGm9WYLUanV6g03ZTETD4URiy0Xa0L82s0PECOYSPxfeH22Lm4AMTwxHGuNBOOdaLdBA9XoYPr9AZBiGYpnlGJKbtueC7haJ4geel5kA%2BT4vm%2BsbDgecqJlBKYMGmGZZkwXhEDcTbeK2xqyt26HWtaJj%2BFY/h3BASw3O2OrknmBbFqWeDltuVZwrW9ZOhhNFttRYk0XgVA4XhmYwlOklyhAEE7hOcLAeGUZXkhz4Nm%2BeakS2SwUUp4k3FuBDrAwNwaH2ba9iOolmXUSimUpVEWZgVnEDZnb2QO7lygOzGmYFQ6xoO6GijOkrKnCpljnFKq3uay6rgY66qVBSrXiaqVsLBWkXleiUFa2j56aQNpqseQiYGgDDoNVR72hqADyBAIPEWKOqhH6uu6nqNf%2B26AcGp7wZOznZdBeWyppoElWQpmVeM1X1Y1zU3J13XPulfXvkCcamVhyaNXJBFEagJHNuRiniUFlH0XRTEsWxb7Zrm%2BZFiWZYVgJbhCQJR0eSdD1KdJslivhCnOUpKlbmpc5uIt8E6Wt%2BnYIZd0mRDkmeZZ1m2QFPY0vDkmua2UMXTD8lPTRiOQdBJJo9piGbQI6DYjjZF4xTYmE95xNdkODnk2ZcpUzcNOpnTxAM9aECK5Jw3eiQAGBhNcFgQl%2BOS9as25XDBtmWzy3VSrku7T1B0C2ZPMgEZrZgGAsJ3KxXb6zR/Om55Vs0UTvk3GYMKWD%2BI0a2NWvm9Gev26bRt7ibpuSbHOkB0pNv7Q6CcEwZTt3QF3u0WTTmm1TAdCz5fmi/2Zf2yFvvBWTEWOq30WjrF6nwuVy7YJyjAEFi/UXC6X43AASg16u%2BtuADS4ToEj42x2hiXdyjrWtunCuj9a4/upuqBEAAsp46Ap5R4P20lPd31vffap9a4fO1Tzog0IlKV4GRGFPqAmCX3dhHWemsgKTTAt7Ek794g8iyNVXe1UB7iiHgodKqE25Am9g/eK8JN54O3hg7AupMpvw/vAgQ39JJnWhumeShFiKT0AZWMMV8aJUQDmrP8Ud/Qx0gReKucJYGfwQUVJaCFkGD0EOg5%2B2NC5kQZuFCS18ooS2nIqR%2BtU2oXGAFuVBMjqGyl/uEYANxz60GAaCD2x8z4XxJLo/RXJh7EL7JFNxTlBRCgFIcG42BVCsA5K2L4jIhQMk8b40%2B3kmBUC8IILIfJ9iAlwSlbRS4tQXGIMAEeR0TH/yic0WJBJeQgOnpHOe6BF5NRXvwnWgi4ThAINVRpuxmmCH2G0gg%2BwRJ5gsdzOEmTsmuKwaE24AAVd434QkfngcgZE%2BolCtGBBAApMS4kOCyCSFpuxHbMKAdWHMeY8AKFLOaR2zsYTWJAWYEyWCzrzINPEBslwVnRKKRsqhcIwyoDwP0%2BRez%2BlA0OSAY5py2DnLupcwcHtOy3IsBwFYtBOD%2BF4H4DgWhSCoE4G4aw1gExrA2ORMEPBSAEE0AilYhYAiSA1BoAAHGYMwABOJlXB/D0rpVwGMMZpBIo4JIXgLAJAaA0KQNFGKsUcF4AoEAoqyXooRaQOAsAYCIBAGsAgKQiLkEoGgdkdB4iRHNJwVQdKABs7YzWSBuMAZAyYpAajMLwSCRBiC/L0PwQQIgxDsCkDIQQigVDqAVaQXQyRIzohSJwHgiLkWovJZizg7UiJau/KgGSpqLVWptXam4DrQ4QA8Pq%2BgWY8RcCWLweVWgVgQCQHqlIBqyAUAgPWxtIBgBSDMHwOgIEZUQBiAmmI4QWgImjbwIdzBiAInajEbQDV5Ukr1c49qDBaCjpDVgGIXhgBuDELQGV3BeBYALEYcQG6nzzrwGGd4Cb0wNSIlsEljS6gJtoHgGI6Ip0eCwAmtEeAhWHtINe4gMR0iYAeCe4Ab6jDkpWFQAw2SABqUZYFopJZ64QohxB%2Bow4GtQCaw36EMMYXFlh9DvplZAFYqAUgNAPe2ck7tTCWGsGYCVwG3VYEo8xbol7nAQFcFMPwyRQjhCGBUEYyRCiZAEEJvQ0mGjzGGFUXjHzGgTDaJ4Doeg7B8fU3MMTCxJO2A03JsYGmlMSaqCsBQBLNgSFjRwFFYqE2SpuJmy11rbX2ppQW3AhASBh1BOWytsGVjdSASMHjVLJCgg1Ey0EPKNCSDMJIM1Ir/BmqZfoTgArSBCuCxqM1XAzV0qZZys1/hJBsoS2alzIbJXStlaS2DSrVW1vVSm7VzbW0lqNWwTgLQWBhhjO2JgpDiN5qZRqLgtLnX4Fde65IGHvXYekLhpQ%2BGQ26C7RGpgUbD2Oec%2BK3gkrk2aqIjcdN7nzWeYm//Lg03ZsaBuIW1Axb4hBZuaFhVNa63vYbSWnVLaAdtr1EYR7XBRU0FoL2ygA6Q0TpHWO0gSOp0zrnQ4FHS6h4rrXQmzd27d20H3Sj49xGz0YvwFuDZ16D0YrvcgB9KPn18oxW%2Bj9I7v1bAxX%2BgDJLgOgaUBBinpjWvwaYEhlDaoUcraw769bsg8PBoxTtojMHmNWDIxz7j1HaNZHo4x6xmvWPsfiJxm9VHVMNBcE1MzwQmqWcWFJ9IMnshabyC7ooWQnfGd02pvokwPfCet70CzhnlM6dM8HqPBmyiR/LasdY9nE98uO65zgN2s3WvB2Yx7M3aWvf866oLIWWu/fC5gSLCQeN8rywV6byWYz%2BCZdy0EKW0vVfqxKzgTW5WteVWqjVqbge9cNcajgQ3s0sAUGGZMYZ89xXGPNgLnGPWyFWwr/18hNsq50CAUEpA9sHZjTlpz8aGtJq62mjN0/Z/z8X0qcYr2i2A8%2B3iUEFby/VqVf9j7TbdVQcS0nZkAUgUhkQF8mVkQl8CBkRVArVu1Ycep4dB1h0p0Uc0dp1Z151sd3tl1V110qdMAt0d090D0SVydT0ecj0L1acb0Q1GdmdANWdX131P0ERudf03V%2BdeBBcwMRdT0xdfs%2BAEMFBkMLxUNZcN95cJBFcA1d8CMD91cSMWNtcKN4A9c6NOBtgOITdLA2NTsONflLceN/cbcBM7cY8RNHcI8rN5NXcGh7cFMfdbDndQ8BBA9NNcgQ8zCw849xM3DZgg9vDY9WhfdrMk9CUHMz909L8OB3M7858SJH8xRn8IBi9Asy0v8q0KVSAIssAa9HN68QBmUNRQRQRAhksocNByiYxStu9Tte9bBmscilhKUQBJB/B4suUYwRU6VJBWUuAGUzA6s%2BVQQL8e8pVv9ci%2BUnUGjE0pjWiVhgMMhnBJAgA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/reconformed_kindred_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/reconformed_kindred_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/reconformed_kindred_left_interview.test.hpp)
