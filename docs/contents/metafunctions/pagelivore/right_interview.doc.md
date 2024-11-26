<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightInterview`

## Description

`Pagelivore::RightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> RightSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
RightInterview ::   template<auto...> class...
                        -> auto...
                        -> auto...
                        -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct RightInterview
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
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = RightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::RightInterview` is implemented based on `Varybivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct RightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSkhqkAA6oCoRODB7evgFBaRmOAmER0SxxCVLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Yk1TS1teZ0KE4PhwxWj1QCUtqhexMjsHOYAzOHI3lgA1CZ7bl6OtIQAnufYJhoAgvuHx5hnF8iz6FhUDyerxeAHoAFQQsEnABqzVuMTwADcSOwQEJGBkYvQAEp4YAIAgASUE8UReEwAHcTpCwSCgQRMCwUgYGec3EwrqgAHQ8wEvWbELwOE7ohiYnF4gnEhnEMmUoEmADsVheJzVJwZTJZmDZmuZTFZFw5RB5XIeJyOTAUClNymImHwogZCj5z3VJwFQoIJztqCI2KYdCB7qVKrd7vVeu1bON3N5e0eqojas9wt9RGUTGAOqTydDHqajmQFoEs0wqhSxBOsZOiLEXk%2BoYAtFwlQARc4WM6Kjt7MPB5Maxn6w3szmm57Ae2MxgEF0JgfJrwZIw%2BrONvZtn3EP2oTPZtmT6dsQQ2%2BOPPuL7u9/u5odag06i5Rx8x8fni0Ga22%2B2Ox/zxNwzVZdwmAE4AzoL4t3TVAINoNk7QdPAnUwM8zQXS8XnbTsFReF9RxrAAxPBiFmV1U29UVxUwXF8SJElZXJCk2WI0iCFdUMr3wp83G4t8TQ/S1vx5RC/2dV13Qo7ddzgq9OLvd0%2BKNd8uVogkhDwLAAKvSSCEFNMdwzdcdPVfM1RM5NZgNZCSzFBkKyrGs628RsFMHeSgMHPN/Csfw2wgFYTibc1fhAEAWCYABrTAAH0MmACJ0Bi9iLgyAAvWKUsAryvI8nL8pOPAqFsssHLONyCvVKBTXMAA2OrROQ/8WJI2ZSHAyVhE01CaoTMLnIbFYVgsyruy7e0CE2BgTg0Ttr1wzzRvVbolBGyr8wmqagtbPt5oqnL2wCtbTJ7HD9uwzDgUWyNh2jZSBK5I9MBnU8JMHEDV33DdoMMvdjIuJ6XrnXqLzDENTsurjbtfZ9oYIlTzSEtDAZPOc3uAlcwLgqDpP9QN4IBqdntRtDAUhiHb2eJSxyIE5WLa6tORFOoBHQdrY1NAB5AgEHibT%2BT0r1mbFPAsRozrpVJJiWrY9r0TQBg2ZObnedIkGFWVKGH1HamOcEr80MalD%2Bc8qSYNku88sHXWVLUrqtPRiMzd%2Br6RrM8rrsswsbIV0rK0Z2mBtcz2IytpaTB8iP/MC4KEwLdAwoi6K4rxRLkrZdLMsd9bNf2yqipK%2Bz/eO/Lqt5Mx6oro3mouemCHau2NK0kH%2BvrTAhpLg7lROTbiGm2bduwrC84KlbPgL32i6rTuvLLs0K4a38mvEi55dZhvOqbnrz1blyO5H/KNswSa%2B5OHauyHq6luTMfCuKyfy0rGfBwgZ/8qo0WJToyXGPlC4Vb5urA%2Bo0wrcXAvjBCS9jZAJDtfE4oC4afFdhcRu3VSYLmAZVXeDYThgDAOcLcLY34RmGpg9y3diFeV7tNMwZxLDC2onbH%2BcpmL/x5oA88lDBwIO1p8WSFxq7OhgXAryPCRxIP%2Bm4VBzdOFkPytgp8F85Gh1OsPWBo9aCrWUeDcax8tpEMHqo9ReYexHWARdMG5CbwLS8jbB6KNZwmy8h9MCX0cYwWQW4Bxp51aXXBtYtRilEG6mCfdOM6FsCfitMjImQMnHqhceAyCBDcawQgYTY8jjfH9gpgtcEkI1zZhuMie0YUmEMRYdSSEdI8KhN4nUvWESonCS5II1C5FBbCnKTKFhGtLFqjseE5hTE%2BaO2druV2ltc4h0GaaWExA8BMDFvEpcmNCnfQYZ/cW38KnSwuPMxZyzhHcJAGA826S3BtPQdlE5ZyXaSOGZSDhESzqeQsTYm6vD%2BLhIOUs%2BgKyTiJLcSkjxkjflHM4eTAJV18k0jhTSGpzxYVQgACqoTnFUiEiLkXwrhYihUZgDgMCOF4U4bIrh0DuBxWpXywknEJOzJmAApDp%2BlvTYAAI5eDEH0q8VkiyF0flWGIqBPC1jbnJZUhIoIpJZbkrC8qrqzJ5M8YgwATaJIALLHyYFQLwxLeg426VLP%2BbhOXcoJoBMKnjVXquyQtflyEYrRPiOxF4EBtVND1QarIbIzAPGtZI5IZ92pmFDQGkAQcZWbhOGYYal1HXIGddaV1QIPU6u9fUAQbIDHYEDQeC4wagixvDX1SNbdo2EK4PGiwHA1i0E4P4XgfgOBaFIKgTgbhrDWA9BsLYjZCU8FIAQTQda1iRQCIqLkewAActVFR7HnRoWdC6ACcex9CcEkLwFgEgNDJBbW2jtHBeAKBAMkEdra62kDgLAGAiAQAbAICkK45BKBoCZHQeIkRWA7FUHOpstVJAnGAMgYsUguRmF4EhIgCyE5BH4IIEQYh2BSBkIIRQKh1BXtILoIIFJiBMBSJwHg9bG3NtHe2zgnMrgvu9KgYq/7aqAeA6B8DkhIMnAgB4T99Bp6DpWLwS9Wg1gQCQB%2BlIX6yAUAgBJqTIBgBSDDTQWgMoz0QBiJRhEzBiC3BI7wbTcJOYxG0HUS9Q6P2o05gwWgemcNYBiF4YA7JaCaP06QLAEUjDiHsyRMzSJUKUfLHUK4Owh3hAZA2nDNwYiEd0x4LAlG9J4F3dwXgiJ4giqUG2RkhhgA3CMKOtYVADDquhExTmKRGDucQ8IUQ4g0O1cw2oSjeH9B5ZQN2yw%2BhRZnsgGsVAKRehno4E2X4BDTCWGsGYI9GXiBwcC/1roPQsguEVlMPwQRQgLHKJUPQhRMgCA2/t9Ih2GBDF28sZb/mBD9EmJ4doehahZr6HMC7Iwqi2DmMdoIVkWjvaWFUNYCg%2B3bAkGRjgTbSCHt4Mek4TGWMgbA2fDjtCIC4EICQOhexq1CaK2sXmTAsAJACqQCdkg9hcnXYqJIkgzCSFqvu/wtVV2bo4Nu0gu6cdclqlwWqM7V0zr5/4SQXB/DrtqtDyjx7T3nuHUVm996xOPto6%2BmTcm%2BM/rYJwZoLBESKibEwKJq4uCrq5FwLkbaYMkE0noWryGGvSCa0oFrOHdBhoI0R/TEOocw6oxwGjz6rgnAY9WYgeuDdG8tCbs3FuNBcZ45Jvj2O4146vaJ8TqBePxDfbJrPSfRi6/102aPinV1cGSCptTlBNM4cM7p9z9fbjGdMw4dzlnZzWds5RhzTmXNubSx53L3mdhtvwPaeoGWRtW9UCFhk7mIvdEozFuLtwEuj6Ews1LQ65tZcwDlrz%2BXQIK5K1mBQ5XKSVeq4P%2B39XUNO9kM17Dbb3ftcK5Nqw3WYt9dJ4N4bnAxsCB0AJsusLAZtYc5sFsf9gdugbs/AIBXAftghFYAc9sChTtegkCDtehUCrtnteg7tWgHs8hftYCXtCDcDPs/siDchNsvsBhKDwd1hNgwdq02dfdpdOAw8I9DdjcwJTdzdLcuMMdYNsdcd5d08CdMAidRhScosOcuczcNBJBFRxdFQF06cGdRcpccMZdbA5dhNr1b0H0n06Nc8Ndv1f0ddw8gMTgWAFBERixEQBDtRZhoN8BYNbcENZAHd790N5AXdn8dAQAN1PdiM0sfcKNdDqNVd6NipddbD7DHDawXD/xvRuN88pNsc9hBMJCRMb1M9s9pN31Mi%2BNI1kAUgUgYpnDV0YpXCCBnUbCnc6Bq8NMtNwg4RG8OjdMW8zN28s8rMbM7Mx9MBHNnMxAB8h1PM8sfMx8/NJ9AscNgtkBQsF8SQos20V84R18kst93Nd90h99h8j9Ct08%2BBStz8KsqsW0h1b8UNEh/Cn9WsQi39jBQCesYhoD20hssgRsQRQoP9ptZt4goD4AYCVtnAED1tiC6DtsygPsTsigsgsCMCshGDSCITXsBgkD8CGg3sdsETftvsYSnt8T4TAcmCQcWDUNIidCj0uCEjgMkinDUjnR0iRCsd9hxDDChpSBCdidKAIcFCQAzAzc9g9h/B/BlCK9l09hFR%2Bc6TYdOBZcL18cycQA6cecuA9gK4dTV1ecK4NBFQ2c9goj6ST08ix02coNFT/c08RM1g5sMhnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/right_interview.test.hpp)
