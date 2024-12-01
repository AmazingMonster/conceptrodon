<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFind`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-3">To Index</a></p>

## Description

`Varybivore::KindredFind` accepts a list of variables and returns a function.
When invoked by predicates, the function returns the index of the first variable that satisfies all predicates, or `-1` if it cannot find the variable.

<pre><code>   Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Predicates...
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
KindredFind ::   auto...
              -> template<auto...> class...
              -> auto
```

## Structure

```C++
template<auto...>
struct KindredFind
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class...>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

template<template<auto...> class...Args>
using Metafunction = KindredFind<0, 1, 2, 3>
::Rail<Args...>;

static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

We will implement `KindredFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct KindredFind
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    { static constexpr auto value {-1}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First>
struct KindredFind<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHOaxwcjeWADUJrFuBACeCZgA%2BgTETIQKB9gmGgCCG1s7mPuHyOPoWFT3jxezwImBYCQMIIObiYXiIADoEQDnuNiF4HLsANLBdDETDoABi2MBJgA7FZnrtKbsQWCIZgoTTwUxIYcYfDEbFsLttkwFAoEXDlLj8KIQXdOYCqbsUWiCLshagiAAlG60SVU0kWaU1RzIbkCcaYVQJYi7NmoXYANzEXg%2BmoAtFxSQARA5al1u4kUqmMukM0FMlnQ2GoAX3bkGPkCp7AXGgxgEcUPb2UrwpIy7FV0T7O%2BXERWoLNqw4xuNsQT8jkPWLkl4k101r1PX3M%2BmskO7QnEcZIp4y9FYhg4vGEodQrs9iXPTXqyktoPztvB9lw8M8qMIoV4vCizBJ2fa1HohXK1UHzUalNS7XMnf6hiG42m81Wm12q9Smcf6%2BUkwAVisP9nQgOZdntcMfhAEAWCYABrC4UmAEJ0EuKEUgALwuAhex/H8vyeXDCN2PAqHvR8TV2KAwzMAA2cwaK3EVW3FNwJ2wzkoOtbxMDmOYDyIjUyV2XECGWBhdg0N19nrJsBJ/VolH4uSLxEsSwKdGtpNdb88PrEClN/GTGyvD1jKBAifQDP1DkXKFzTDTkI15Ss4VLTB4wrHCqTTYJgEzVUczzAsiyhNyPMTBzq1rUzouBKzWzsjs2NIM0OyECoBHQFL7IRAB5AgEGifdkSuWVMWxYVR3Qcc8G7AgUvStAhxS/LCu7SLiTJA9bJs%2BKgxy1dHPXFzGJ3ZivMpfs5RPQszxMoTfx0m9dTIkEn1SohX24/YlvwuT9gA/9gNA8DHMg6C4IQvAkLxVDDgwrCJqIvb9qpEjVqNE0DKIqjEVo%2BjRt3Fi2PuTi31477CJUzBROIcTJM0j1pyWwiFI%2Bd6mvI4hIdw37V3%2B2jAfGw5Gsy0GQC420IZR3Dodh8SNPdGTkYs17djR4jSMxtavppn8IBxgTB2HAkiUOVqio6vmiKgxcgtPOgoSJsUpdZtmqTB7awDAA5c0dQXrz46XPyEg3CNUuHdjMfZLHKodKrFtwJfaqszdw2W%2Bo%2BGaQsOZW91V9Xr0120pLdwztPMwO0bD6StQt8T9cR5m1ahvSjZTwSG1rE2s9kyzaQS3qC/6kNIqcjdXNjdzy0TJ6fIzItAu9s8Syr8KXIBMyYqbAB6AAqAfB6H4ee8BfvB92AAVPdE12IfR%2Becfh%2BXgeF/M14GG2Lw9ihJrVgSWup3MnrlwtABJXspt2M%2BFEngB3VBARAXYEi8CJaDvc6IlQTxzm5wx2JuDPjmXWVtwwziMrFZsntEqbQvkfK%2BN8ACywQ0y5RCE/F%2Bb8P56i/j/Wgf8DQ1EEFCeBDZnSJy5BA3OLMT4nwGmuSMLknjEGAMVJ49c/JIJhkwKgXhN7tECsLB2Y5DgaBSs0K2KVYi9igj7NwLC2EdS7iVW8yBzjOWiAQCA3Cah8IEWkUht8H7k0pnaWI5CrZ8TMuMNRGi%2BRaJ0Tw/RlQBBGJQQwNBGCOIUzfCAix6lrG1g4AsWgnA/y8D8BwLQpBUCcDcNYaw0olgrDtGYWIPBSAEE0CEhYsEQB/kkHCDQkguAkliBoP8GhaI0TMAADjqfoTgkheAsAkBocRUSYlxI4LwBQIBxHZOiSE0gcBYAwEQCAJYBBX71QoBANAYI6DRFCKwNYqg6k0XtDRSQuxgDID1FIOEZheDbiIMQPA6A9D8EECIMQ7ApAyEEIoFQ6hhmkF0M0O%2B1wEicB4KE8JkScmxM4LlWEszdioFIhsrZOy9kHN2Ec62EAPBLPoKaDYXA5i8CGVoBYEAkCLISMssg8yiUkpAMAKQZg%2BB0BBN2SgERgURGCLUY4fzeAsuYMQY4uUIjaAqEMzJiya7oNoOy95WAIheGANCWgtB%2BncF4FgGCRhxCStqoKvAlo9zAqNBUWEaxMnBBBGE95H8IjXB5R4LAwKrh4DaUq0gOriDfyUM6UEhhgAfyMDkhYVADBsIAGp4EwHfXKZwomZJucIUQ4hHkxpeWoYFnz9BepQIkyw%2Bg8ARH6ZABYqAD5pEVfaH4utTCWGsGYbpLqLlYDzSBFobQ0guCHCMJopBAhTCKCUbIyRUgCHbX23IaQeg9v6GMVoWqBCdGGJ4RoehyiuI6BMMdfQYhjAmEOzdXQ10zA3QsBQKTVgSABRwCJpAum8B6bsGF2zdn7MOUU5FuBCAkBthk7FWS/ULEKkwLAMRG35MkLEOEABOWIJJJAlLMJIGiHS/w0TA00jgLTSBtIyXCGiXAaJ1LA3UnDhSuB/ggzRS9wKel9IGd%2B4Z%2BKJkEqmeC2E5BKDkvRastgnBagsEtCSe0TAnIZi4GBuEXBimnPwOcy51zZB3PjdIRNShk3vN0DS75TBflKrPReq9IKOBgpmbCSFpFuO8f44JvywnRPFMoqi4l6KP1mC/bikZDG2PRBYws1AaL%2Bimb4zyIwwmuDiJoLQel/SIBMveVytlHLSAxZ5XygVDg4sioTGKiVMSpUyrlQquLKqvXqqy5qyoOrFUxP1cgQ1cWTWtGBRaq1xwbVrBifax1mSXVuswB61V3rfJ%2Br4IGhQIaw0RsYHFmNcmHkKdkEmt5MTVNpt9RWqwWaLUNoLUWg0nBS0EGqhYlbVaa3RDrbq/NTbp1%2BAgK4bdnahx7t7c0HIA70jztGIkft7QHsTou8u2d9Q3sdqXe0f732N2DC6Ld2xdQwensWMsE9WKUM6Yo5wM0xAeN8YEwFyzImxMaEoq%2B85H6sU4p/aQP9AHKBnrQxhkTJSSQkZJOUyQsGdnNF05R2w1GXN0fgAx6ZszPPueIBxtY3G4UsAUJaPUlorN0nGBJt9daZO3LjdNp58glPzZ0AMdTmn/nI6Be8npBmIVQvRywSX0vZfy%2BYnKFF3n7PRA/fMMntHRmEqdyS4X3v0UU2QAkBI5w5dgfOArggGiMc7NpWFoqjLmWsp5XFhLvL%2BWCtS950VDBxXAuy7KsQeWnUFbVS15VJXHBlb1aoA1IIauCDq%2BanNjXmt2oue13gnXkjdc9Wq/rHuA1MGDaG8NkaJuyfVxIGbzztcpoGAYZbmabDrfgJt9oiqe6QUO5Yat17a2XLO424HLbrttsB/4e73b13Dpe7d57X2r/7sXVOv7W7z%2BTubTO1dj/HsQ7nZkIHb/Qoa/JHI9BHB5bTY3bpNHCXXZKXGXK0O3MUB3Ind9TFZzcnSnfoRtM1WnEAMwETWIWIP8KpUpDpIgkkXDcjE3TgKjQZcnYDP8cDP8OpWiMDSQMDcpSDLgeIM1WIKA69WgmjPFM9E5ag6A3pYQ3JZ1IqFtSQIAA)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_find.test.hpp)
