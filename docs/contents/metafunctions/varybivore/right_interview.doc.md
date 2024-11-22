<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::RightInterview`

## Description

`Varybivore::RightInterview` accepts a list of variables.
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
RightInterview ::   auto...
                 -> auto...
                 -> template<auto...> class...
                 -> auto
```

## Structure

```C++
template<auto...>
struct RightInterview
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
using Metafunction = RightInterview<0, 1, 2, 2>
::Page<Args...>;

static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);
```

## Implementation

We will implement `RightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct RightInterview
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
struct RightInterview<First>
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
struct RightInterview<First, Second, Others...>
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
                        RightInterview<Others...>
                        ::template Page<RightSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + RightInterview<Others...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIaGqQADqgKhE4MHt6%2BeqnpjgKh4VEssfHSdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXEJSQr1jc25XLYjPWF9ZQOSAJS2qF7EyOwc5v5hyN5YANQm/m5ejrSEAJ5H2CYaAIJbO3uYh8fIw%2BhYVNe3D/cEmBYyQMAKObiYp1QADoYT97sNiF4HPsAEp4YAIAgASUEcQAbnhMAB3X4mADsVnu%2B2p%2BwBQJBmDBEKIMKhcLuNP2CKRBH2ymIqCIyiYwEZVJp5MpHM5NLpwKYoOOcoZTMhrOu%2B12TAUClZ/Mw%2BFEAIU7JlNO5yP5gtQKKYdF%2BZupkq59UcyE1AmGmFUyWI%2B2ZqH2eLEXhekoAtFxyQARI4WQ5k2P%2BKUOx3KhWMpWA%2BWK8Fq2H%2BbCagw61l3YDETCAxgEE2F1NmrzpIyou20V7RvkCoi2%2B3HcuV6uCXUFm7JhsJpMp8XU9O5gNl4jAOs3Gf7JthYB8kVh/ydq1Cndgu5Lkds%2Bvj%2B4xuOk/7ZlXHAP7ABieGIw3ZFt5aIx2NxxAJYkwVfd8CHZSUJznTM8xZGEf0xIQ8CwFcJy/LtrWFUUJwgtdOSgsF8MffNzyLLVSxhfVDQzFDcPNAhEUtbsbTbCdOWdJ1aLNYYFTwd00AYL0fT9J9g28MNOJlHDpUdR0TAAVisOTowgBZ9nDDUPhAEAWCYABrTAAH10mAcJ0AMsDjnSAAvQyLNXaSZMkilWMcs08CoD0BIBITDgk1zqSgdUzAANnMYLKN46jgLfYZSFRdEEKQzAz2uLTRNDBYFhc/yJQpfZKwIVYGH2DQ40nW8HJyzlMFoJRsqq50CqKtSo2Tcq/NkxMVPqtjExvCTr0vP5Ktle8MwIsb52IjUyLPAcqzYYdTUdDcW17dsjn3Jj1uPCsFprFKLylXqpwqvDJughcYRPZdlupVat0w3ctowo9%2B1PdUjtJPqht%2BQiYMDEDYv9SF9iEaoBHQOKrqhAB5AgEDiGi7jQ%2BC/wBADCRJY4gYIOLwf4qH9nhxH30%2B%2BypPO%2BlxqI2CoTRxDkLul0GN5A9UCe7DnIk/7/phmaSzPCKjWS5nOTQ9mdoGvKOJGrjXV4zzBN9EGiCDENxLlpzjqqp0FPk5TVPUwsXXQLSdP0oz0VM8ywWs2yxf8yndZldyle8lWev8wLYRCsLhainGYrx%2BLf0Z5LybSjXMq91zGswQriGK0q2uvK8OtcmqlH2N3%2BOVv1Y8cn22T9kKA%2BNMECchuKGaSw7sCjsSY4zxz48T4rWvjNPhpdmUs5eXPPQ94hC5kiBR/8tGcQxwDsbcEmkfJifXK0qDtyw45a%2BQpeW5y1eLtbPs3HLiPR2XxzG9DfYwDATaWvPzkst3zqu%2Bf1ymqT/YzEOSxQ8xaf8RYzBAvMmZ834XxAGvTmm8ErCDrjvLWvd97UwBIfWgYIT71wfo6S%2BmZX6IKdn1dOBDM61TFCQ1ueUP7FUjGVbuvcYzdRboNHWZoWFnTTBdCaKDLrTRNrNMse0hy1kdvdZsW51odnQj2Fi/YhGLVrEvIaJ1%2Bo91Gjw1UdMbrI05A9dez1pEczem4bRSiUw/WnHcAA9AAKjsfYhxVjfi2LsQAFWwEIVx9inH3BcQ4xxFVHgMF2F4A4YJTh0EuOBO8GjaaBixNDUGAApT89EeT7GwAARy8GIb6rCXQ8T4kPb0KtoioE8OrMSXMLBYg7HfFJFjvqnWIXzYi2j2R6IALIJyYFQLwwTCjFTvlPf8s8wRJH2BML%2BcUzDsi0tAkxH0z6/XhArZABltRKEaL8CA3T6h9IGZkMEszCxaR2scLJOT0GnJAOlZ6d8zBZSGtxN0GydRxDAvcXZPSDkdAYGCWhNzzluEubkm5dy6l7hak8iwHAli0E4HJXgfgOBaFIKgTgbhrDWC5CsNYYYzD%2BB4KQAgmg4VLF0iAOSZIoT%2BAABzBTJP4RlGh6VMoAJyBARRwSQvAWCDFICitFGKOC8AUCAJIpLUVwtIHAWAMBEAgBWAQZIpxyCUDQECOgcQIisA2KoBl4ZgqSH2MAZA7opBQjMLwA0hASBIT0PwQQIgxDsCkDIQQigVDqGlaQXQEwiTECYMkTgPB4WIuRWS9FnBYanFVbyVAHkDXBSNSas1FrJBWv2BADwWr6AF0JVwBYvApVaCWBAJAmrkjarIBQCAVaa0gGAFIMwfA6AY3FRAaIUbohhAaBcUNvBe3MGIBcWG0RtDVClcSzVCjYYMFoAO31WBoheGAOCWgtVB2kCwDpIw4hl1vinXgPEyUo3emqKcDYxKwgAm5Wi840Qg2jo8FgKN9E8D8u4LwU9xAylKGjICQwwBzhGDJUsKgBhlwADUsaw2SIwbdTrhCiHEO65DXq1BRv9foYDKBsWWH0HgaI4rIBLFQMkQZ4qODhg%2BJtUwlhrBmGFb%2B4gdd4BLHaIMlwDB3CeBaHoEIMxSjlDyGkDIAgxh%2BAmPkCTDBegiYGBMLjtQphSb0CpzoUwFP9HiMptT/HxiTG6DpuYenON4vWBIcNHAkWCqjSK/YybU2mvNZMzN38IC4DtQWolxaSXgaWIjJgWB4gqVIJSyQ/goScrJJIDQkgzCSGCokOSwV2X6E4Ly0g/KiVQmClwYKdL2V0sK3JSQXA5KcuCvZ31IqxUSoC9K8tCqK1KrjWqutDb826rYJwBoLA8RknDEwYswHJnsqhFwKEaLbVEDY2bCYyGXVoekBhpQWHfW6FbYG4Ng6bN2aFbwEVsaVWnH2Im/0xBBvDdG1qFsXBJvTY0Nm3N1b80/38I8kt4HZWVtQHmuI6r60A/ewMAbQ3wz3ebeyrgSQaC0A7ZQbtvrh39u3Wj0d47J0OG3bOms87F1RpXWujdW7v07qA/ujYaL8CVhqKe6js3VCXoBNu29NUo2PufRcV9NOS1sa/cS39/7MCAb3SBzcv3IMigULB4k8HEMU%2BW6ht1a3ZCYZ9Wi7buGwMMasIRx9pHwsUao5wWjBB0D0YIxYZjx3WPsbI7YGqx7nAQFcOpiYQmSi6bEwUTInuUjicGaZ0TymXd/K6KMQz0nnf2EGVH6YPuzMaYMzkWP3FGih6UxZ1YVmi2Zds5GurnArs3ZG2Nh7T2ZvZu8/Nz7RafvNaC5gELAxwvcuy7lybCWyRVbJEyxLyWKu1eFZwBrkrftysVcq%2BNwPus6r1f167xr9gsAUHid0eJHtQgZMMG1%2BB5sOqW7IFbauPXyA21rnQARSC7ZDd%2Bg7xex8cFO/Gi7HkBur/X5voMO%2B9%2B8g5qg41qfb%2BD%2BaloyptYL61oarAH5q3LIDJDJAGTb7soGQAEbIr5rbtpIzI49p9qjoY4EFjoTpTp44A5zoLpLq06YCrrrpiDk7Eq7rAYHq05HoM5nq%2BoXrIBXrs64j3q8Dc79p87vqC7boi5pBi5U6S5gbNZ8BQZy5wYIYorEoq6uoSDq6epX7Ya34GB6425EYkYcboqUaZDUZWKaT65MYsZxALZnpO6aZ%2BDu68aB7e6zBh5B7%2B6SYx5%2B5ybZ56Zx6u4MCJ6B6OGJ7%2BGp7dChHabCa%2B4F4KCWZupP6j7Hal5f4mo/5b7/7USAF14kAN7gGBakDBahaUA2Zd4gBmCTb%2BD%2BByRyQJZw6sr%2BBkhFYpHRqiq2CNYQGZQRYgCJb5ZcBfbBRfbsoFYhQaBkiF7%2BDP6pEdHdE2bWptH1ZNZlpLC/rpDOCSBAA)

## Links

- [source code](../../../../conceptrodon/varybivore/right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/right_interview.test.hpp)
