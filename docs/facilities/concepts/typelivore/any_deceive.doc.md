<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-deceive">To Index</a></p>

## Description

`Typelivore::AnyDeceive` accepts a callable type predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred{}(Es::value)))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0{}(***)))` and `(...||(not Pred_0{}(***))) && (...||(not Pred_1{}(***)))` are both atomic.
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
template<typename...Args>
requires (...||(not Pred_0{}(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||(not Pred_0{}(Args::value))) && (...||(not Pred_1{}(Args::value)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOVDESi%2BVlR3xR/isj3uDz2BzeZ3OXGuBzuj2e4WAtIuDK%2Bv3%2BgJBYIhUJhcMRyLRGMwWOIOLxtAJZLRJMJlMp1P2hwAakwgYz9syHgRMCxUgZDV83CLUIcAJJfbCU8bELwOTXalXoymHL2HWaOZCHNAMcaYVSpYiHS2HABuYi8mEO4ttxOVFOTCopjzVRyoXhxN31huNpsw5uBoOYbCRCIexGACjtlNOAEcvHhTgpDhAq2i3D2IAxUAQOZdxYqIDW6yAQDHvJglvPKYHg6HwzFUJ5cbmICj0Zjsbj8SWFcmMwajSamGb/G4y4xWJgqxP6/57Y9m63212kT2%2BwOhyc6Q0UdiXHWsFCnGc43nJYEzMAA2cw4M7btUV7VD%2B0HYcuGAmEnwg2M5wXR4l0NFdDjXDccwYbdxT3aVDgIJ0jyJb4VUzG5DgAFUwcZdVuVVtkObBiGIEgHWaP1ziYBQlFaahc3NLUgXNbCXztbdSQsDgVloTgkl4PwOC0UhUE4XtLGsH01g2eNzH8HhSAITRtJWABrEAkjghEAA44KkJJUTgyQAE5/ECsx/H0ThJF4FgJA0IJDOM0yOF4cCgicoztNIOBYBgRAQDWAhUnhchKDQY06HiSJ704VRfIAWiCw5gGQf0pARMxeDOQgSDwdA9H4QQRDEdgpBkQRFBUdQstIXQuFIAB3YgmFSTgeB0vSDOckzOAAeXhEqh1QKhDnquCmskFq2sODqzE7DxKvocM7K4JZeEyrQVggJAKtSKqyAoCA/oBkBgCkMw%2BDoQ1iHAiAYh2mJwhaIF1t4JHmGIIE9pibRMAcNHSAqthBD2hhaFR2asBiLxgAtWg5UJrAWEMYBxCptt8ccKMeJ2kN8fhLYHPCQ1dNm2g8BiFasY8LAdsYvA4u4XgeeINclG%2BI1WYloxnJWKgDDrDU8EwRa9vLQmhuEURxHGq2prUHb5v0VmUGsax9El8DIBWVBUgacCOAa8Z0G5UwLMsMxktV4h%2Bt5n3ui57IXAYdxPA6PRQnCIZKhGBaiiyAQpj8fOMkLhh5mGBIFrsJOBD6SZ0/yGu6jrxoJgGbOFjz2wO%2BLvRZlaSvc%2BrlYFGszYJE2jh9NIJLeBSs7Gua1r2skTrO1wXqXoit6Pr1lYEEwJgsASbdSHcyR/ARULUUkDRJDMSQ4ISzzgqijgYtIOL/DMBF/Dgqiby/hvJJCSFwMKwVvJzx2ilNKIAMp6xyvlH6hVDqlSBiDZ6NU2B1WXldAErNbrBQRFwBExkepEFjgNBaVsRq22kPbJQjtZq6EhstVaaNp6z3nrtDgB1irwkOCdJeF1mqENeFwEhZCrgQEev9Z6sFf7vUckg1BWD4hlWBqgJ6IwJHg2ClwIINBATxDhgjWaGMUaEysVjHGeMCbKyJjokmBAyYUx2tTWm9NGZOOZtrLYxl8CnAcHgHmgcKGqAFoaQmIs6g7QllLFGstAkfVjkrByqt1aYE1izIwOtQBZX1obBQxtTbm0YJbWQ9CxqMNkA7Gaxk2Eu11uHKwlhPYxG9ufP2AdODBwIKHH4bTrBRwXjHOO3Sx6t1Cc4CArh%2B4LSzuUKuegC4NEWWkMuDRh6LBbj0eufcm4l0TrM9ucwu6rJrkcvIJzB6dxWSPKeqx1iTzeh/HhsDOCiMugGAwkjpHkM3vgKhSi96qKKYfY%2Bp9KBuXikEMWX8f5JARCFJIwUzAYvgt5CBQUYGzTgbYBBEKvrIPgKgoqR0tEaOIDgrYLQWDNRYAoKM/ooxSIRMWcY3UQV9RoRNa2o0JB1MmswxpOgAhLRWmtZW3DtoEv2ug46p1VBMpZWyjlXKhxyJ0Qo%2BISj/AqM%2BtldRuqAbUrNc9acyBUipHOOy4K5wtXnFVYw6GZjKAWOMrYymDkfX2K5oTYmjA3Hk0pkEzANM6ZiF8Q5fx%2BTUmkGCUncJfMonIEFrEwQ8TxaS2lkCFJ8t0mEyyRkHJWt8lsiQQbJgRsTZmwtk4uhNtakCoaU7SV/zjDuw6YkqZJl/bZEDtsEObsI4WDGSZCZWB%2B21zOSnNOtzM6p12T3dZ2RNnrtKJcp5%2By24NzaMcgeMyGgHtXdXXu/RNn3PPc88eryxpyvxclb5rrDjMtZdGTVl4eLaq3qC16RqD6kCPifEY59EWxQCH/XFEUzDwa4N5DQcF0XPoXpweBiDIUXxAFfUhICkiP38EkZDEVAof38PKl9qUSUuQ/l1NDfD97YdVpkZwkggA)

By turning `(...||(not Pred_0(***)))` and `(...||(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate{}(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO5XBhwgAidUweAAbijoay7hBiYSTAB2NyitwQBioRlojF4LGYUVWEWsiCk8HkhQgEBcsReTArI3QqzXEF/AHnc3HO4AFUwswUXytv0tJyB1vucvQAH0NM7DkCvBkjKj0b7/Xy7lhkLQ8ZgICZElZEmqmF4iEKVsr0QRNgw7lQxEoTaLWdn/Kbga6veGfVwA/sgyHgGGMfW7lGY3GEQmkym0xnUFmc5g88QC0XaCXK2WK1XPYc7gA1JhwxtAsEQj5KmHpoiPKkg2bELwOFdrkHKkF3W93WYfBV3WmzTCqFLEO771B3PXeXkihYDxlqWZqqqB1Y3DaVBeAW3wgluLw7tCsK9gSmBClcxDAJS/jUtc6IAI5eHg6JOsybIctyu5uN6fo4lhOFCke1wvmC76fjEqCeIWsEQNmgG5vmhbFruKqsle1yIZCNHxuhmHYbh%2BFYZgxGkQ6TIsuy2zUShdFBEyinMXhnZmAAbOYZmaZROk8npdZcAxRnEixVxsW%2BH53FxPEwQw/GjuOBYEKeYkgWaNZLvaswbseTSOMgPpMAoSgtNQsEoaucIoVwR54fx84cGstCcIkvB%2BBwWikKgnDipY1j3hsWy8mY/g8KQBCaIVawANYgIkZmEgAHGZUiJCKZmSAAnP440tfonCSLwLASBoQTlZV1UcLw2pBB1FWFaQcCwDAiAgBsBApBm5CUGgzx0PEkTIpwqjDQAtBNdzAMgyB3FIhJmLw8pEMQeDoHo/CCCIYjsFIMiCIoKjqPtpC6I5ADuxBMCknA8EVJVlZ1VWcAA8hml2MqgVB3C9ZnvZIn3fb9kj/QKHh3fQn7mK1Ky8HtWhrBASC3Sk91kBQEDC6LIDAFIZh8HQYLENqEAxITMThM0cI47w6vMMQcLEzE2h1HtbW3W8BDEwwtBa8jWAxF4wBuGI07a6QWAsIYwDiHb6n1Dy2rI2%2BdQZjsbXhGCxXI7QeAxJj%2BseFghPBXgy3cLwPLEFxSjsp7Rgx0YnVrFQBg4cueCYGjxP4m7EPCKI4iw3XCNqITqP6F7KDWNY%2Bix9qkBrKgDJZIHr2zOgfKmHVlhmBtmcg1g/f8V0PRZC4DDuJ47R6KECzlJUeiFJkAhTH4jlH70Qz76Mjm1PUAj9JMW95Lf3Qmw0cxXyMCS33Mp96A%2BFoX8lg/zWAoRq2wJB4w4KVUg61eCbWpm9D6X0fp/TMAKXAhASCmW5rzIuawECYCYFgBIy9eqSH8ISaaIpJAaEkGYSQZlVr9UmvNDgi1SDLX8GYQk/gzIikGv4QaiREhcBmpNQacDCabW2iAXaRdDonUFmdMmV1xaSw5o9Ngz1kH01jF7X6k1CRcEJJVIGJBQbg1kFDRu0hm5KFbsjXQcsMZY21tA2B8CiYcFJhdDMdxKZINph9AxoYuDGNMf6CAbMRYc1wWYHm7VFEqM0fEa6EtUDs1GGEmWk0uBBBoHGeIytVbI11prN2FT9aG2Ng4N25tyRWxtoTe2jtna0Fdund24IvY%2B0qvgdE/sHSE2DsgUObsI7dEJjHOOmtE47EqinNObVM7Z0wLnPp4RQD7WLqXBQ5dK7V0YLXGxDcYb2NkC3JGlUXEd0LlPKwlhe4xCXoPYeAhR7j0nt3Gec94gLxGQPFe79nAQFcP/Ryu8yjf0PukY%2B2Rn5n1SPCy%2Be9YWv1Xg/P%2BSKAFv3vn0T%2B6KQEAJxbkZFgD5gwpJVwMBECYaeIJsjRBNM6bPgMOEyJZjMH4GBrg2l%2BDdmEOIaQygPUVpBCjpw7hiRCRTUSJNMwirzKDXERNaRzLOByIUbspR8AVHnXJhktJxBtE7GaCwD6LAFBch%2BlyCJhIZKzEBryyxYNHJ11sRcuG8hHE3J0AEUgbjsbp0ZRqjaJM1EUypqoK1Nq7UOqdYyGJWS4nxFwf4JJfMDqpNTaLY1eaOa6mQCkFIPp7WTR9Emn0sb7EKxKZQMplVqm2zai22pJsGlZIts022AzMAOydi7QObUPZ9MWbwQZ78A6jNUCHMEkzBDTOjrHeOcIFnJxBisjO8R1mbPztsxRJcmBlwrlXGu3TPXnIkJc%2BGfq26Bo5cYX5NhZlvKqh8hggddjjy7tPCws8EHz1BkC5ed9ejr03uSneG9gEH3PqirIkKUVFCyHBm%2BIKCWP1aLizFoLCUDHQz/cYAxkOUqI1A9YmxIG0vYV4mRnBqZxttb%2BRNO5orqldZzFqArklCtIEQkhoxl5SqWgEXhaqWpmGk1wQaGgzIKvDQgrVth5F8f5uKyhJjhGJAYdUeTLVxrsP8EyiNW11NdXYQDJTPjBUadIJnDIzhJBAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/any_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/any_deceive/implementation.hpp)
