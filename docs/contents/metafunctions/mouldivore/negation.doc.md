<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Negation`

## Description

`Mouldivore::Negation` accepts a predicate and returns a function. When invoked, the function returns true if the predicate instantiated by the arguments evaluates to false and returns false if otherwise.

<pre><code>   Predicate
-> Arguments...
-> not Predicate&lt;Arguments...&gt;::value</code></pre>

## Type Signature

```Haskell
Negation ::   template<auto...> class...
           -> auto...
           -> auto
```

## Structure

```C++
template<template<auto...> class>
struct Negation
{
    template<auto...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Mold_v 
    {RESULT};
};
```

## Examples

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
template<typename First, typename Second>
struct IsLess
{
    static constexpr bool value
    {First::value < Second::value};
};

template<typename...Args>
using IsNoLess = Negation<IsLess>::Mold<Args...>;

static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 1>>::value);
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 0>>::value);
static_assert(! IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 2>>::value);
```

## Implementation

```C++
template<template<typename...>  class Predicate>
struct Negation
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {not Predicate<Elements...>::value};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxAGkAA6oCoRODB7evgnJqY4CoeFRLLHxXIF2mA7pQgRMxASZPn7ltpj2%2BQy19QSFkTFxCQp1DU3ZrcM9fcWlAQCUtqhexMjsHASYLIkGGyYAzG4bWzuY%2B4cAnomMrJgAdPf72ADUT8gGCgpPysSY%2BKK7e2wJg0AEFhsQvA4nhFMMAmJ1gSCTAB2Kygl4vI7beGnA4ES7XNj3W7YehsQQKR6IjFPcGQghfYioIgAWU86GpGJRaJBNJpk0cyFeAmGmFUiWIT2iqE8TwAbmIvJgnpy%2BSrUQxmYzfnh/ri3KTNowCApiY8QCAFd5TsiACL7Hk0lH2vY81VPLEnM74q7MIn3Q3kk1U9EYrypIxPNm0dAqva2xnM1DRjkHQPG00PQEOxHOnOgxEAegAVKWy%2BWK4Wi%2BWngAVTDDT7lqugksV9tlltIgtmPZhN5eLBxtxeRy0QjnEPdkGenHegl%2B5UAMTwxGGpA9C5uTyEVQEqaBoLpUIAkgpgg3KQXUe6BbrhQxReLJdLZVale7uSu1wQLe/lWcO57gw6B/oqNoum6dr5tOs4Ahcvo3MSILEMAlLZqC4ZhMATxnhEqAXh8cYJjCcIIgcZ6Eeh2AWimZwoWhZrZq6uZHnUgoAPpMB8cQEBAeEEZeZzDKBIBhBswDEGIHFoI%2BdSCGc4kblwjwbiJFribCUm0DJIryQQimCMpVKAmB1pzDBd7IFxPENPxCj4VRwkEKJmmSdJsmTApBxKU8KmAmpLkaYIWkeXphgGT5RlPBoJk0Za4EWSxbHwrqNlKHZYBgLhDmCR8zmuSF7k6Z5%2BmGQQxkBbSQViUV2m6XJEXlRuZhxWZSpJRYHALLQnAAKy8H4HBaKQqCcG41jWLSSwrABvY8KQv7Dd1CwANYgH1yK3HsAAcABsyJ7AdGi7Yd/h7PonCSLwLASBoGikENI1jRwvAKCAD1LVoCxwLAMCICASwEIko7kJQaBbHQcQRDcnCqPtAC0e2SE8wDIEKUi3GYvA6kQxB4KBXAyIIIhiOwUjE/IShqJoOh6AA7lJiScDwPX9YNtOjZwADyo4gwyqBUE88N7UjKNoxjkhY08EAeJD9CSuYexcHMvBfd1pAQEgEOJFDZAUBAOt6yAwBSGYfB0Bsa6UNEnPRGE9TnCzvD28wxDnNz0TaFUS0LRDQbcwwtBO8tpBYNEXjAG4Yi0O93C8FgLCGMA4ih/gPzVHKDac2KVSjmsC2ab1ofjtEUnux4WCcwQ%2BO3fHpBZ8Q0pKLamzJ%2BORi0wsVAGGhABqeCYPT3O%2Bs7lOk%2BIFP8IIigqOooe6ETBid6YljWPoeDRO9kALKgiSdHHCMifstqr1YlhmM9jf41g28QAslTVM4ECuGMLRBCB0wDGUSQpGkAhvz0Lkf%2BDAv4lEGETR%2BnRuijE8M0PQUCagjF6GEfo4Cf6TFgVkd%2BmCUFFG/hIB%2BM1ViEMuhwAaj1OYvWFojZGqN0Z%2BSlmYGWuBCAkBVPNVWi0u4LAQJgJgWB4j31IOtSQexbjnWRJIDQkgzCSD2vdPqe1AjF2uqQW6ytbh7S4HtHa/gdo6L6pILgfVzp7UoaHF6b0PrcOWj9f6WtAZ81BgbI2CsYZsE4PUFgcpkQIyYK8ZeOFyi3C4LcEauMSAEz0NPYQohJ7SFibPGmC8QDm0ZkwZm8c2bkI5pYnmziBZC28b4/xgTk5%2BX8KE8JMs5a6wVhwvYZguHqx%2BtrVA8s4hg0Nh0%2BpgwSl%2BLeMncoXAHo0FoFbd6EBbah1do7Mecz3ae29g4Me/tjSB2DpzcOkdo60FjmPRO7c1gjXTj7PAWc44RNUHnDYY8i6c1LuXc4lcTlq1rmPRuzdMCtyTkYDuoA7F8F7goAeQ8R6MDHrEie5NEmyGSfPEauhzZBJQJNSwG8t7wF3vvdIh9j7xjPtYS%2BvBUDXwJtnHebQOjpBcCBQBRMQioJmBA3%2BeR0gMrZSAsBsxIHtHOQIGBjQ4HjGpQKroyCeWstwZy3BUqyhEOWCQlWZCKFPVJZwJ4AyylDMjCEsJGgWH4Dxo0lWaseGkD4QIwYwjVE3RAHsKpMjkSmORIdWR8jjEWOepwaxn0u6awcUgIG/NuluOhrDDg3i6EsAUHKIUcoQknGGDjY1UTCbj3ibCymCLOa6AuhkrJrNVV5J9RwXmwNRxPEFlq4gLAY1xoTUmnEwxam9L1o0vYLSA2OPDfrcG7aFaWmQIkRIHFE3%2BA4smggXE63IwthMuIUyZkjUWSHBaa7lk%2BzWR0gOQcQ6nMwBHKOMc44LSOf8t5YdVznMuTnG5yB873JCsXEaTzHavOrh8%2BuXyUg/Lbv87CAae5MH7oPYeo967QqzRIOFM9qaIrphdVFRKMWlzvjig%2BnBCzqVQxYElo1yW32xWKp%2BfgX70pFe/Jl%2BD0FAL/p0TlwDOjyoQfysjQrZXsegZK5lBDIHINlbx2jvLFWzVIcXNVVDNXRpRrG%2BN8pm0bFbRAVhJqlZmtsd9Xh/DBGUByWo26Zgql7D2H1PqMjRknT2MiXR3qNWvVsDY1pa0QCyK0VwJpe0mn%2BG0WYBRyIyF7FLQ581dicnY3s1zRzLmG5LtpZIIAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/negation.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/negation.test.hpp)
