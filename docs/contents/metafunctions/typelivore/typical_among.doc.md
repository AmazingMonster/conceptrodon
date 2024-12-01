<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-2">To Index</a></p>

## Description

`Typelivore::TypicalAmong` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>...Element<sub><i>i</i></sub>... -> I -> Element<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
TypicalAmong :: typename... -> auto... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalAmong
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = TypicalAmong<int, int*, int**, int***>::Page<3>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalAmong` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the element at the index is returned. Otherwise:
  1. Drop several elements from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `TypicalAmong` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<typename...Elements>
struct TypicalAmong {};

template<typename First>
struct TypicalAmong<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct TypicalAmong<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { using type = TypicalAmong<Others...>::template ProtoPage<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAWakAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHOaBEcjeWADUJoFuyLPoWFRn2CYaAIIPjwSYLCkGb2duBACeKUYrEwADowdh6GxBAo7i9ZsQvA5jgAVAF4US0R4sATAU4AdiseIAImcrE8Xm8Pl9MD9/oDmGxjgAxPDEWawp7wxEEFFojFYnE/Flsggc54El7HKXHSmfJjfc4ZABemAA%2BjyAJJi6XHLlI5TEVBEZRMYCYfGEkmBMnPJ462XUn7KtWa7XS4iYACOXlZmAUxwgWsCVqJGhWkulep5BqNqBNZp%2BQfudulJgJxy8GSMMoB5rOROZrPZ1vxVptEalDvlNPOTC8RDBIMewA970YBBhgWTjx1mYiuPjeeDxxjxtNNbczdbUI7jbuIBAdJr5eJpJeFPecoVv1zDPNwtmpBz9OBxyEdQE6CPS73jYA8gQEAlO92o7yUuixAKjEKiwQj%2BeaAMFexwPk%2BbJzl264Simlabo6ip4Cq6rHEmFa6gQCL6oaY5mqcsEWhmWa4kupzDqiH78tiP7nGBz6QdgC5Vm8I44XG46JscAC0xxmPOi65qSpZruSBHMROzooWhBEet6vr%2BoG%2Bb5mG6FvqO7EJuc0k9qm6Z9tmpH5oWIpCWmZbrmJ8HVk6SEuqhbpSrJPoegpQYhlw4YEWpbGDomDmEfpJG5mRBaAZepmrtaFk6XBVLWbW9aoI2U6YG20L%2BYFI7jiFrGxr55wpWls5grCUXkpF5ZPAA9AAVHV9UNVVLy1XVyLYEIyL1U11UNb1NXdbazxmPsDCHF4Jw/EB2wpB2YovJlQheCkhSYOgABKfpeLQPJGREBD1SJg2ZRtChbTt5F8l%2B1HAD8e1HntNX3YIdVPftdX8flbiBPxS6HXCTSOMgqpMAoSgtBAVwLgowLA52bgnWdAFLSt62bdtdzhmVjwcGstCcP4vB%2BBwWikKgnBuNY1i6hsWx5sNPCkAQmg42sADWASSCCGiSFweKBBo/gaGYABswtmAAHOL%2BicJIvAsBIGgaKQRMk2THC8AoIBK0zxM46QcCwDAiAgBsBApPW5CUGgHx0AkUTApwqji8LXHC5IxzAMgyDHFIIJmLwq2ECQeDoHo/CCCIYjsFIMiCIoKjqLrpC6FwpAAO7EEwKScDwuP44TzOk5wd71ubPKoFQxxOy7bse17Puc2YAYeDb9DEKc9MrLwOtaGsEBINbH5t5bECD7biTAFIyQ0Ntz6ULEhexBEzR/DnvBL8wxB/HesTaHUOsM9bM53gwtCr0nWCxF4wBuGItCa9wvBYCwhjAOIF%2B%2BvUABufqF5gqh1HrDsBme1uiF1oHgWImct4eCwIXTCeB5aP1ID/YgsR0iYCJO8V%2BECjDMzWFQAwwAFAADU8CYDTneeka9Y7CAxNHaQ4d5BKDUIXFO%2BhX4oEppYfQkDNaQDWKgGaWQH5cSuPmUwlhrBmFVqg4gIdf4CK6D0LILhgJTD8KnMICxyiVD0IUTIAgNH6PSIYhgQxdGjFTrUeoAh%2BiTE8O0PQNjej2PmGUEYiRrFzGMd4gYFjPESDWAoGm2wgnSw4ATZWhc1ZV2dq7d2ntva%2BybhAXAQd257A8t3fBawnxMCwIkCAbMQCSECCCAAnIEPEkhuZmEkMLRW/hhYVIibLUg8tAhcBBMLLgwtxYVPFn0/wPN/BVOFtEpOasNZa0Zvg/WRt%2B4m1LhbCgo9UCtztg7DgzQWBfzxFxJgxxDivx9hUkE3SSaByIPI0OqcmGR3EDHJh8dWFJ10MkDOWc1550iQXKZxcVnl0rrs/ZhzjkGGzFwc5lzm4bKHgkDugQzBdzmbrPuA94XjxHmPNuIBQUHJOUYaFXAlYzzeGyeei9l5bxoRvFeO894OBoUfdsJ8z6F0vtfW%2BtB740OfjgnYJN8Aem/r/JO/9AFvBoaAvGScIFQJXrAoV3d5FIIZqg9BSgsEvyMLg0A6K%2BBENIeQyh1DkEPPoRIRhshXmJxJh8jheDJFWB4Qq/hxTSbCIEKI8RwYXXSNkQkW5ijPUuNURAVwviQjAQCUsLxqRTG9GjQY3oca9HWO6PvBoPjHF5EzSouxcx01WPGAMaNsx/E6MCR5dYmwwm1rlVElWvBYkEvBUS3E0KLlcwDOkm5SLslot7nkzABTRierle0zp5zuZ4jGXiPmkh6lu1Ti2ou6tbCzJ7nrA2xtTZlxxVitu9s2CcF2bXFgCgv7ey/t26kswA74BuSHMOshHkMNoXathIBghfOzo/X5zaYmArNvWY4FdjgXvdlem9xw73nIfTyCALcEWZOGoEVFO6MUoGPQkI9mzEg3uWqqBDqokPA2ICwN2fA6AUs1hABeSd6W0uQSx7eu994so2cfU%2B59hWYCvjfO%2BD8GYCr1Sq0gIrs0/wflcgByAgEysEGA%2BVkDoF/GVfAtVNDNUYJ1Tg/s8zCGmhNRQqhjAaGWqjtar9LD7U6F/U64w3CbDuvgII71DAH5VUhgGywMjW1yIUR64JWbbF%2BEjeovNmiY3oBLQm1NWQU1JqyAl5x4XXG5tyLF8NRaq0ePjc47LTi/EtHS7WkJ9bo5Af%2BarTgUGqOXuvbe%2B91ZZh9ufSQQdWHcmkHyYUygvzp0gDMOcwIgR/CCx5orCbeJ%2BmTPq5uzW2s%2Bvs0kP4Sp/hxYiwqZICpfNqlcGCHKwIdXW2cByei35/tFsXc3dhtYqCMjOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_among.test.hpp)
