<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllFalsify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-falsify">To Index</a></p>

## Description

`Typelivore::AllFalsify` accepts a callable type predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise

<pre><code>   Pred, Vs...
-> (...&&(not Pred{}(Vs)))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_0{}(***))) && (...&&(not Pred_1{}(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return false;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return false;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<auto...Args>
requires (...&&(not Pred_0{}(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0{}(Args))) && (...&&(not Pred_1{}(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BQQAOqAqETgwe3r6JpClpjgJhEdEscQmBtpj2hQxCBEzEBFk%2BfpV2mA4Z9Y0ExVGx8bkKDU0tOe2jfeEDZUOBAJS2qF7EyOwcAPQAVLvbANTKxJjoAPoa%2B3vbmyYaAIJeaUaHx2cXJgDMACL7WMi0BAAnklMBATAErAEvhAmF4iAA6RELEwAdgsxwIqwY%2ByoYiUnysKK%2ByI%2BVnutzuOz2LxOpy4lz2N3uj3CwBpZ3pnx%2BfwBwNB4Mh0NhCKRqPRmExxGxuNo%2BNJqOJBIpFKpu32ADUmICGbsmXcCJgWEkDAbPm5hah9gBJT7YCkjYheBwarXKtEU/ae/YjJiOZD7NAMEaYVRJYj7C37ABuYi8mH2YptRKV5OT8vJ91VByoXmxVz1BqNJswZotiPhd2IwAUtopxwAjl48McFPsIOXzAA2LsQBioAjs85ihUQSvVhYTimB4Oh8MxVCeHG5iDItEYrE4vEl%2BXJjP6w3G33b81w1Dlsc1j52%2B4Npsttsdszdp%2B9/uDjTDomjqsKCcLBNPl2D6Il2PZ9gORy0lwn7Qhef5TgIM5hvs86LjmDArmK65SvsBCOtuhJfMqmZXPsAAqmAjDq1wqps%2BzYMQxAkPaDR%2BqcTAKEoTTULmZrQVeK4khYHBLLQnABLwfgcFopCoJwbjWNY3orGs8bmB8PCkAQmgiUsADWIABJ28IABydlIAQop2kgAJwfFZZgfPonCSLwLASBoGikFJMlyRwvAKCAXnadJImkHAsAwIgIArAQSRwuQlBoEadDxJErAbKoZkALTWfswDIP6UjwmYvAnIQJB4Ogej8IIIhiOwUgyIIigqOooWkLoXCkAA7sQTBJJwPCieJkk6bJnAAPJwvFA6oFQ%2BxZZ2uWSPlhX7MVZhth4KX0OG6lcAsvAhVoSwQEgyVJKlZAUBAl3XSAwBSGYfB0AaxCBRAMTjTE4SNICQ28L9zDEICk0xNonQhZpyVsIIk0MLQAMdVgMReMA5q0LKgOkFgLCGMA4go82UN4FGlHjSGnRwhsmnhAaYkdbQeAxP1oMeFg414Xg7ncLw5PEPOShfIaBPM0YOlLFQBjVuqeCYD1k0glJmm1cIojiE1autWo41dfoBMoIplj6CzgWQEsqBJLUgUcNlIzoFypiWNYZi%2BQLxBVRTFtVDUGQuAw7ieK0eihDMpTlHo%2BTpAI4x%2BN10e1P0EdDN1HRdAIPRjMHORp9UpOZ1MyeDAkadTHHeg%2Bk0xdzKXSwKCp6wSCNHASd541%2BYtOV5QVRWSCVba4BV%2B2OYdx2S0sCCYEwWAJCupAGZIHzwnZKKSBokhmJInaeUZNnORwrmkO5HxmPCHydiiJkfCZAQBFw9k2SZ7cdX5AVBVpkvhVF50xTNCW3XuntdKbBOBLRWgGAwzwuA2XhFweEMlypEE9tVbqat6qa2kNrJQusOq6Ben1AagMW5tx8rwPy004pwn2PNLuy08r/AJhtWB8CLgQB2ldPaAFT5HU/qFM6F1UC7XiIlO6QjOFDEYUYGBXAvI0ABPET630OrA3%2BjjVRoNwaQwcDjWGjACAIyRuNVG6NMbYz5rjUWRgiYyXwMcLo5NbaINUNTA0ON6bVHGszVm/0OYbBktzXmmkBZC0wCLfG1jWRf2lkwWW8tFbKxxugjWjUsGyB1u1GS%2BCDYS2dlYE23jzbzytjbTg9sCCO2%2BHk127t4goO9vPdOtQA5B2yPHYIgca6RwTqkGOmQc7tMThkLpqdfYFzqOXAZld84Zwmb0EZpdbCTLaZXIu4cS7N2WKsJuh0D6kI7pwOhECpFshgXAhBg98DIO4WPPhp1J7T1npQfSHkvKMyPifAI8JbIBBsmYP5T4TIP2si/XynB37BS/hFaKsVZqiKAWlDKnBGgsDyiwBQUZ/RRjOcWEYZUrmVVQc1dWDUJBpJajgzJOgQBOUIYNPmJCxqvymv/OaC1VBooxVinFR4qLsPEddbhHxeEnTCr/BFN0koCr2iATFSQkinGxTZU4uKCCnA5Vgt6ijKDKJkho5Gml9VaKhrooRcMDGI2RrYzAaMMZiHMZpPGYt/G8DsaTRxlMXHIBpu4wQnimYszZoCPxXNPZBP5vEUJ4SxZRP4XwGWCg5YKyVowJJsgMGpOJRkvWNKcnGGNjYQp8BLbWwyLbTYDsjYu0sG7chHsvZFPrjM5pEBXAV26mHEoGyekFAyO2vIvSk7rNrtMv2hdej9qad0NZXaR1lwnVM%2Bd1dh3dPro3RqjLQXkMORq/Y6LMXRh5QaPlQ9rkHRFRPUgU8Z5DHnu8tyNKz7AscmYV9XATIaE7L8rdE1/K2A/qKicC8QBLzgTfAIm8PgBE/Y5KyB8PhMrBX%2BwDLdSo/rfnc3SpABZpGcJIIAA%3D)

By turning `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_1{}(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllFalsify<Pred_0, Args...> && AllFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate{}(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMxBAA6oCoRODB7evv6p6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMiTcBAAnilGKxMFdlMRMPhRMDSFcmF4iAA6fEANSaeCYMXoCgh2EBaAY6xSBCuZ1otAAYmIMlRoVcIQARK4QfG48wANhFEAYqAZyNReHRmBMAHYrAqeRAicQSWTMAoFrqIVZzoDvr9jkb9lcACraggKd6mr4mg7/M3XaXoAD6Gjtu3%2BXgyRiRKI9Xt5VywyFoMLhEBMASsAVV2Lx%2BIWiosKIIqzeVHZ8sSyp5qfzgJdu0DqPdXG9219/uA5Y9VdD4cjsMwMbjscTONQgtTSozWauOdoSn1isL48NDuuRK5H0BwNBLzzbiTqFulMBo2IXgcVznJaVgKup6u00cyCuNNGmFUKWIWJ7VwAbmIvIi0zcJ1OASrf6W2zDl4bwLucS4PCuEJrj2gpnMQwAUokVLnCiACOXh4CitpMqy7J4Jy0Fup6mLwYhgpbucN7Avej4xKgnjAQwED9ummCZsQ2a5uO/7TkCIKQeCkLrnBCFISh8GYBhWHaoyzJsqOBHQkRQYkYyYkUch3JmKKOlyXhimEZCxFcKRGn4pRZzUXeD5XPRjFUCBLFpoOnFXAQu55gWJYzmWVqjNW/wXrK7pMAoSjNNQIHQVwlIsUWFgcEstCcAEvB%2BBwWikKgnBuNY1jnisayfmYiQ8KQBCaElSwANYgAEwq4gAHMKUgBAqwqSAAnIkHWlfonCSLwLASBoGikBlWU5RwvAKCA42VZlSWkHAsAwIgIArAQKQ4uQlBoPcdDxJECKcKoLUALSdVcwDIFeUi4mYvAykQGroHo/CCCIYjsFIMiCIoKjqEtpC6KZADuxBMCknA8MlqXpVV2WcAA8jiO0MqgVBXOdwpXZIN13VcD1mPyHiHfQj7mGVCy8ItWhLBASAHSkR1kBQEAs2zIDAFIZh8HQwLEHNEAxEjMThE00Kw7wEvMMQ0IozE2iYA4MukAdTwECjDC0NLINYDEXjAGuzJzdwvBYCwhjAOIBsyQ4eAvtqSN3qrOIbOV4TAilIO0HgMRQwrHhYEjHl4CNFukM7xD0UoPIgjb/tGFVSxUAYiEEngmDgyjcIZeVn3CKI4h/UXgNqEjYP6DbKD5ZY%2BgB3NkBLKg9JZObF2jOgvKmJY1hmFNMdvS7LedKrrwuAw7ieG0eihOEAzlEMplpBkrwTH4q%2BFK8syDAkpl2BP3RjC0s95IfNTH/Up978vB%2B2Kfm96NMzR3/MXBLAoRXrBI8McGlCaSNpo40utdW691JCPX5LgQgJBtI0zpqnJYCBMBMCwAkFipA6qSESLiHqCpJAaEkGYSQwoxoNS6gNDgQ1SAjUSGYXEiRhQKiaokJqAQAhcF6l1JqQCQbTVmvNCqqcVrrSZptdGu0OZc0pidNgZ0wEEwjDbYmXVcRcFxFlF6JA8DvVMkXb6pdpDlyUJXEGuh%2BaQ2hjLf%2BgDJq8GmmjbaOIrhY1AXja6KiAxcHUZor0EByas0pggswtMRFLUZszVAFN4h7U5jE4JQxvG8y6lwcaNBIzxBFmLEGcspbq3yQrJWKs1ZR01owbWut9ZZUNsbU2o51ZWyThsWpDtHDO3Nto1Q7tgTq29jUJG/tA5SxDq0umGpI7lRjnHTACdrZGGTqASJfAM4KCzjnPOjB1aGJLr9ExsgK7AyypYmuKc%2B5WAbsM5uWC26vE7t3Xu9cLCD0ccPPRo8sFH0ds4CArhn6mQXqUfeeg15FGyOfLepAwW70XnMFe48fkMB6OMSFL8r5IpRX0OFILD5PzRXimYOL75/2WKsX%2Bn9qH2OAZwDx%2BNrwGB8X4rRMD8CvQQZ/JBkSUFoIwZQWqo1xq%2B1ofQgIuJuoBC6mYKVOkmrcM6vwqanAhELVEatDaW0MbxNkcdU6HAmgsGuiwBQL4rwvl8biME1pnpst0fo/6xcfoSAOQDMxxydBJFINYmGFs7GIwEajKRmNsaqCNSas1FqrUBUCYktmCDEjhPpstCROr2b7VjZTEApqUgpHdOarq7oo0EHdKGkxgtsmUFyVlIp%2Btyo1pKRPdWFTBA6z1kjOpJsxCNKjs0xZ4zSD4BRI7TprsenIA9v0wQgy/YByDtCMZYdJnqxmekOZidFnhGWQzVZTBM7Z1zvnHZsgjH7IdUcqunrGXGGeY3GINzW7twEObTY3c6790sK87K7ysD3sRZPP508AXBGnu/BFMKshAfA8UYlH8/0n16EB75rwsWgYfq/M%2BuQoXodQ6S7%2B5Lfp%2BsVY42lparjGtNa%2BSNK5o2wPZdTTlESGY8vQUMLBwrhpJEYfK0qZheNcCahoYUkqiPIxmrYYRSbdTYJALgjR7CAgkOSIJ0qHVqGJH9UqsTkn/5PRE4Ixj1Vo7ZKyDJoAA%3D)

## Links

- [Example](../../../code/facilities/concepts/typelivore/all_falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/concepts/all_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_falsify.test.hpp)
