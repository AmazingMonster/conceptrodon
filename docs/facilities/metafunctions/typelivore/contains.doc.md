<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Contains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-contains">To Index</a></p>

## Description

`Typelivore::Contains` accepts a list of elements and returns a predicate.
When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Es...
-> Arg
-> Arg &in; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct Contains
{
    template<typename>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = Contains<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

`Typelivore::Contains` uses `std::is_same_v` to compare elements and a fold expression to combine results.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEIADMAGykAA6oCoRODB7evv7SaRmOAiFhkSwxcUm2mPbFDEIETMQEOT5%2BATV1WY3NBKUR0bEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLM8VCyG8WGuJnibgIAE9HgB9AjEJiEBTQ7BAoE/P54vYA3HXACSLBS9DYgiY9Q%2B%2B0J%2BIZJ2xFwImDJBlZ0NhCMYrEwADpBdgKYwCBj4liLmNiF4HNcPFTQhiLiYAOxWC7XLXXVns6mYLnwx7MNgkhgKR4OULATFA7XXaWygjXZTEVBEACynnQdu1aosfs19u1M0cyGuaHNrNUKWI1yiqE81wAbmIvJgoUHg1D1RBBfy1W5CxAxugQCA8ApEQo%2BYjk1zhWzRQpSGaLZgrUZMYtFmrbtCNed7X2B8yh9rdeT9YaeSaBYLzsBiJgm4JxZLx1qvBkjNcvbR0FD4rcXW7Pd6uYvl6uxfnbfFByOH2PcYz6TdsKpWOSM58cYy/xVb4Dj3TAmioLwGCtARaQJIFJw5A0YSNXk2Hzc5iGAdcgW3a1QPAyDoIYI8TwVJolS5UICFbKidhowQ9nogg9ltC5y33H0YQwrC7wlUcgMuECABU3jFWCmSlJow0RJgFCUFoIA9MCmAgqD6kohjMXLVNvEwXtn0k6k8GQGS5NiAgIDAMB8JUwj1JhZNUDwTjsG0tM9IHDhlloTgAFZeD8DgtFIVBOCLSxrAdVZ1gzcx4h4UgCE0LzlgAaxAXzJH5DQAA4zDMABOAquF83Kcq4VVVWkHyOEkXgWAkDQNFIQLgtCjheAUEBmqSoKvNIOBYBgRAQFWAgUi8aiKAgNAyToWJwj5ThVByxIAFpEkka5gGQcMpH5MxeEwfAiGIZy9H4QQRDEdgpBkQRFBUdQ%2BtIXQuFIAB3VEUk4HhvL8gLkpCzgAHlJom51UCoa4VvWzbtt2659rMa4IA8Ob6DjOKuEWXheq0ZYICQWaUnmshppJsmQGAKQzD4OhWWILqICiIGolCZo4V%2B3h2eYYg4RBqJtA7XqEtmykCBBhhaC5l6sCiLxgDcMRaC67heCwFhDGAcQ5bwZcrWTN4gcwVQO0mzYEqo2ogdoPAolRfmPCwIGUTwBr1dII3iATJR7i1ow7aMZLlioAwsIANVeD6QeNbn7uEURxDuy75CUNQgbe/RtZQaxrH0e2usgZZUBSeo1bW0toVuUwIssMw2u9s6sCLiBljsEWshcBh3E8do9GCUJBgqYZ3sKTIBEmPwx/SCeGDmIY4nejuiN6CY%2B7yZfak7gQ1/6If5lH2xxlaDfp%2BP2YD8XiR2%2BijYb/0AGWqB9qYdWjatp2vaspRiBcEIEgUIQQ4zxiHZYCBMBMCwHENupB0qSHiPyAq8QqoaEkGYSQiQmq%2BUSAVR%2BtV6oJC4PyRIXBEg5QKuVRImUSrIOSK1Xg7VOrdUSiHAaw0iajXBpNcglBKaY0WmwTgzQWDJlVGtJgEYDC7i4AVfkxDgrHQAc3C6shrrJ2kKnR6GcXq6Dpl9JgP11b/Q4P5Z%2BL12pg3GpNa4UM35wy2uCbWSM5EKNRujUmmMgHxDMLjVhfVCbE1QBjWIvCZrBM8cMJxRhZFcGajQWgjNmasxerzTm8c0n80FsLBw8dxaiiljLIG8tFbK1oKreOmtta62CvgA2jgjZq0UWbZAFt47WxqsFO2DtObO02MFN2HsEre19pgf21TrRsLDkwSO0dY6MHjqndRt1NGyG0c9YKejs7B1rlYSwBcoitxLmXLIFcq7Hl2dYBujCm7OWNsXLoO8/AQFcFPAePcF4jyXqkWe9Q3kzyKFkT5Cwt7dF3iff5jzV4n2BUfGY69cjn3hfvMo18cYrDWPfdFNUzEMOBhwexH8pHONkfI7KqN/6nW8SA/xBNwGQOgZQExdVSANXiHItBqpfIFUqvEdBmDJDvTxUw2wLD8b9UGiNMaEMwn8IWktDgIj4YsAUMmcMyZSWITGEdE6JBzrvSWUnFZCd1mZwSJ9b63MTG4pfqDbhkNoaqGVaq9Vmr9RjHcREsm3j4h%2BPFYElAXrMayqDcMNVKQUh1lkYiLVBBEROs0QzWIyS2Yc35hktNAshYizycEiWhTZa1MwArJWKs1YJSqYHfpGt9ad0aSbFpbTPYdNtvbR2cI%2BmuzOkM3gIz0hjLZBM4OAS%2BDhwUFHTAMc46e0NTdCQqyHrpw2Toc10jjB532d0o5IUTkCDVlsUsuc64WGuSFW5Ld4Dt23kRbuvdEXvPQLC7548/lnz0C%2BoFV8vl6BXvUPekLf09BhV%2BkFF8EX92XsB1F370UKDvrda1gMLGcBhs6tVKY3Wsg9X/XVWNgF%2BrAaQCBUDhiwJqiyhqhV%2BTxHiL5Uqgqmo0dVOQ8xbVODMJ6oR%2BBvkkEVVVE1HKkhipcDymYZINV4hIbYx1WlKV8GHVY4w9jsmexe2TV3SQQA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/contains/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/contains.test.hpp)
