<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-conditional">To Index</a></p>

## Description

`Varybivore::Conditional` accepts two variables and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two variables according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...&&Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Conditional :: auto... -> auto... -> auto
```

```Haskell
Conditional :: auto... -> typename... -> auto
```

```Haskell
Conditional ::   auto... 
              -> template<typename...> class...
              -> typename...
              -> auto
```

```Haskell
Conditional ::   auto... 
              -> template<auto...> class...
              -> auto...
              -> auto
```

## Structure

```C++
template<auto, auto>
struct Conditional
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<typename...>
    alias Mold
    {
        static constexpr auto value
        {RESULT};
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold
        {
            static constexpr auto value
            {RESULT};
        };
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    };
};
```

## Examples

We will see four examples that present different use cases of `Varybivore::Conditional`:

```C++
using Select = Conditional<1, 0>;
```

- The template member `Page` of `Select` is a function that returns `1` if all arguments can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 0);
```

- The template member `Mold` of `Select` is a function that returns `1` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >::value == 0
);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(Metafunction<int>::value == 0);
static_assert(Metafunction<void>::value == 0);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Select::Road<>::Mold<>::value == 1);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0)
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(Metafunction_1<-1>::value == 0);
static_assert(Metafunction_1<1>::value == 0);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Select::Rail<>::Page<>::value == 1);
```

## Implementation

The implementation is straightforward. [Check out this test to see how it works.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEgCsABykAA6oCoRODB7evv7SaRmOAiFhkSwxcVxJtpj2xQxCBEzEBDk%2BfgG19VlNLQSlEdGxCckKza3teV3j/YPllaMAlLaoXsTI7BwEmCwpBjsmAMxuTF5EANQAklQAKsRemKQXZ5c3AGJiSsfYJhoAguMHg4Lh4GPgGmI/v8TAB2KwAi5Ii47PYHTDHU7nVA/aHIi5ArwggAimGadAucKssOJxwRMMRyNR%2ByYhxOr1Q11xjKRxEwAEcvHg%2BQouTyCQRgQQLqTybRKScrtz/viqRLWXhkBc0AxxphVCliC9sRcAG5iR6U%2BE3e6POG0o4WK0O%2Bl4pm7FlsrFvZX4vmC4WYUUQMBgK5LN1IwkkslMCmYpVHX7itWzRxanV6g1Gjlmi2YK0WD5fDE0unOunQqsA6sq91o1kY9nYgB0bf%2BwD5u0YBAUvuRXgyRguyiYwALx2JMtjdExEDbLfMADZl2nNQB9UTjTFRVCeH4QDtdtiCBRLCNJys18XM9GYjkL/7EYB9y/itcZgRZw3Gy6j8frqahaynGtBzguy6rs06abkw24nLu%2B5Joez5nhe2AgCA5reKWLq1vhN4eneJwEAAnikjCsJgC7YPQJ69v2SKDqEwAXAAsp46AKlOIGzic85tpBZhLh%2BsHwW4iFgchtHdqemHYY8564o6tb4rejaYmRFHMGwNF0T2r7JnWUbQZq2pfjs2a/pyHG0OggGFtOcrgYJwlQRqyBiQQO57lJ2AQDJ9EKPJ%2BZKUmIU4RWKnXgysWRiiREaSRiVelplG6YJSbagYCgKAuyh8vgog7IZ8XRtKBWoEQABKqBMOg8VUvFqrimpKVNm4aU6dRbaBQZjH4hczHDrZXGTk5oEuYubnCaJW7eQhvkHgVmBFY2r5uH1p4QeFWGhehV6xYN9aeh1XVUXpskMW%2BxmDR%2B5m6pZP65qNDnNciaq8VJbgCdNK6zaZnnzT5SH%2BSta0lZiW29jtGF7ThYVwwpE5ltFt32od8Xqal7WaeR6U9YuWXIDleVtuDmrrQNw2sbV9XcSOxBVagdMNScFPFUGsOHS1cUxW1DY44LHUPpl2DZXBZMthzVM3fi5WM8z1WTSm8LvUi2Mi62bYAGotHgTBRPQpWtQOQ6sf%2BE5HDxM7fb9QkiYDXkg35EAy5DJx68QBtG1zYsRYpB1o8dx3qwlwv3trLZez7xsDfLgMPd%2BOYmpbb2m0in221NDtzXBC0SUtyHu0GmIx4bxuwwHmCI9XUX0qqqMNx9hER8lbfeqgsMS7l%2BWFZTHtGfiNMXMr8bW4rNWTez/ec1Lymuk3tYAPQAFTrxvm/L9Ca/r7c2BCLcG/bwCu%2Bb1v%2BFmEcoQk14WAKm4OqbCk11GdCI9CHUmAguNYIQlkUIThcGeBoBeK9l4XFuEGaUoCYqiUlrEAgEBP71EwpbTEwCLhmB%2BHXSc40uAXnpPA3KiDkFfwcGgscHUNDPGwbtZG3FxoaEIeAyB0CLhcFrMQpQrQIDxRQd/AgmFRqNROGHcY6BMKhB2J2MQm4LKGALtI54nCkzPHEQQSRIBpGYFkbQeRj1FGYmUVggaOD4aWjwRPThAIWFwKdgg3h/DyFCJACIlMYiM4Si0TovRBjZiCGMYIEBPx1FeIkVIwQujiByMzM0QJJwTF0KHh9eh%2BZGET1gf8OxsVl4QKgeMUx9ipQXB1qgPA6ArgJNdACTWeNtIXTFtCBWZSKkFJ2HEC4KQvBGzMhEkAVASzrjSoWDGaNoR1LETdFp5T0DtNiJiU0sycFdJ6bQPpmjMKSkeMM/Goyl4xUmW4ZUMy2nQIWZ7WZVSFoYVWb0rU/TtmYF2RRfZeFDm4xIvjbq3MAQK2ufMzp3T7neMwoM2gSgXko2pO82KRyTnbJBAC85xAgk3JAHc9ZDzNkgCeVCt5mNamfOOdMxF0pkV6lRZcip1yVnAqxaC3FDxnkjKagcuFxLzoZRbE%2BF8yoR5sVjFQLwDAHBZAZgIhw0JMKszLrMwFzwKUdOVMIzimJeXz0vOMv5DiSG8MFc0YVoqGhovMQwqxU5mGHW4aQg1TAjVioEIs5ZaTIoWouFatGNr9VCpFY6hgcqaUJKRuk91BDrW6p4UgyVrjZVTLhiI%2BNuDrb4JyTvfJ7Cji1iOaLImRkFbhAEIUTIppMCAoxfSjZWjwWQtZWrdlEziW5kTEZf0QoRQXAgFcB%2BTCIw6pKYWhgxbHClsBQmOlayq1bOZfitlsLG0d1zQigdAgwjAA1KOlFFbJ3YurUMutMLCX/BzSaFt0I22BmDBoHtE9wzNLJRcQda6N1lpReO8KmKp1Mp2QesZNTj1Nqjhq/l5t2K%2BuNVkdcXAJUuOlSAMe31B3DrwJuylzwn26JfWOm6lDxzqtQtzbVgJI22vA/6qDmIAC0qiQ1upTZknJ3qkF2odQ0CjQCzWhvo5axjJGfWGr9Wx1RbhQGussdxjhvGPLrkcdGlxMrp4krhugpNFirYOinOGx0HAVi0E4PEXgfgOBaFIKgTgxzLDWAJGsDYE4r48FIEI4zOmVgAGsQDxEkC2DQkguCwiOBoeIGhhJLjMIkZIemOCSF4CwCQGgaFGZM2ZjgvBgo0Kc1oFYcBYAwEQCANYBBukEHIJQNAew6CxHCFRTgqhEhLko0uSQFxgDIC1FIFsZheCrUICQCpeh%2BCCBEGIdgUgZCCEUCodQznSC6GAQAdxiSkTgPBdP6cM5oXgyWADy5wisXFQFQC4tX6uNea61jhXmzCdo8OV%2BgRpzBHAIbwDLOnSAQCQGVlIFWyAUAgJ977IBgBSDMHwOgHTgoQCiBt0gURQgtFIst3gsPmDEFIltqI2hBGI9IGV%2BiW2GC0AR9NrAUQvDAFOLQCF2OsAsEMMAcQxPAxitLcFab%2Bpv7nC2A5nRkWTPrKiDE1HHgsDQ8lHgWL3BeCluILuJQpJadGHWUYDbKwqAGBfDrPAmA5tbe0tjgbwhRDiFGwbibahoezf0HTlA1hrD6DwFEYKkAVioBflkVnlGJGTlMJZywZgkvS%2B9lgJ3EAVh2EEVkFw4Iph%2BGAcEUIQwKgjGAchgQMe9Cp4YPMYYVRugR4EH0SYngOh6HD/6wvAwE8LGT7YCYbRi95GAbMVo2ek9VDDzZzYEhVscAM6QRLm3OBHbqw1prLW2uXc7bgHr937NLGeyrlYCBMD1RGKH0g7nJBHBbAATiOLCSQPmzCSCXPF%2BIS4d/6E4NF0gsXHstiXFwJciQd%2BJCf556oe%2Blz9%2Bh8l1LIB0sVc3tct3t8tdtzgSs/tUBbtKtqsOAWgWBTRYRKMmAJZhwuAd8WwuBvMusIRetJFgEDchtjdpBTclBzdptdAQcFsmAltJce8%2B8B9TNOAdtCtzh9tDsECkCUC0DWIMCsDvNrtoCvs7tKQr4zB59HMgDQD/s7tIDZCRguDkCSY6cMCuAaEaBaBwdKAodptkd4dsd9DUd0dMcKFJccdoC8cCcicTMScycKcqdzCac6cGdbCmcR0gxod2dkBOdscedod%2BdBdSJhctgTMxcJcHNpdZdMB5cXCWIgC1cxwFBNdtdddGB9dZBiCRtSDZAzcpsTMqCrdlcfcrBLB7dHd4AXc3cvxOBPdNFvdbc/cA9Ygg9PDnc89/Uo93AG9Y9SB48ygc8M90hMg08eihiigshW9Fgm8XFeg6908ZiegC868pia9m969chej1jVj29Vh1gu8CEr9e91tptksXhiBEDkDUCVD0DMDsDr0Ao8DZ9HtJCXtzxSBl9V84h19Isb879MCfNYR4gd9YR/NJBj9GtgEmC/9bAACpDnMssQCkACsit5DhDvsqs2BOAEDTsWAFBTQtRTR%2BD0RxhcCZ8%2BtCDMijdsixt5ByD8idAQAjhSAaC6CVsjjGDf8WDwDpQDtziWBcT8TCTiT1ppQIAbsRDYgxCjgjhXjpCPt0S5DfsFC4gCSUgUhAIMD1wSSCAZMLjGtQctDYgIddCTMjCicHNzSTCsdzDccex8dCdoc7DycxBHCHNnDFdQjeB8A%2BRmdPC2dVAOcdg/ColedeBAj4cQjRdvYIipdYhojYjFd4iES%2BB1dkitcdc9dzCiDqSJAcjxt6SLcmSijjBGibB%2BcQ8qiGhWdl4IkSjrB/dNtA8Kk2j18y8GguiFi%2BjwQdjxiRjsgxiU9hiGhezFj89Gh5jByOiGgK9Rza9%2Bguztiq9BjDiFBO8RsGCTiksh8cSms8SCSzQRSSoxTp8iBnint4TMsl8V8sBvie8/iQAzBMCZT4ggtfN4sZTYRn8f9TjOB/9ACES3N/B4hd8khhId9JAQTPyuBmTIsjgtzB8UtLyXMjjOsfztykK3iVhpcMhnBJAgA)

## Links

- [source code](../../../../conceptrodon/varybivore/conditional.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/conditional.test.hpp)
