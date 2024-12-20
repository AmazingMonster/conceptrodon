<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-look-for">To Index</a></p>

## Description

`Typelivore::KindredLookFor` accepts a list of elements and returns a function.
When invoked by a predicate, the function returns the index of the first element that satisfies the predicate, or `-1` if it cannot find the element.
This function is created to exhibit the power of fold expression and to compare with `Typelivore::Find`.

<pre><code>   Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Predicate
-> Exist Predicate&lt;Arg<sub>I</sub>&gt;::value ?
   I : -1</code></pre>

## Type Signature

```Haskell
KindredLookFor ::   typename...
                 -> template<typename...> class...
                 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLookFor
{
    template<template<typename...> class...>
    alias Road
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will look for the indices of `int**` and `void` in list `int, int*, int**, int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

template<template<typename...> class...Args>
using Metafunction = KindredLookFor<int, int*, int**, int**>
::Road<Args...>;

static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Elements>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies all the predicates, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<typename...Elements>
struct KindredLookFor
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Elements>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOYAzOHI3lgA1Cbbbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYKQMQJObgIVxSjFYmAAdIjsPQ2IIFH9HmNiF4HIcANLhdDETDoEKoVAAawAYiR/iYAOxWR6HFmHIEgsGYCHs0FMcGnKEw5hsRHw26HfZMBQKQ7KYn4UT8u7M1lYnEEWXEVBEABKqCY6H%2BrOOjKNxtVTUcyAlAjGmFUKWIhyY51QhwAbmIvFyVeaTUyHn6/SZ/FZ/AARCCLQ4AWnFXxAIBYTApmAA%2BhlgBF0GmCBCMgAvdN57bKwNB40MgMVisJpMp9OZ7O5/N4Ist0s2ryCeL%2BmNcBnhk7Vmt%2B4kENYMM2j40QUUMtwLiDWaxobtAsiakl4RVc07I4GMAjo0uJz3eTCLaMnKnHX0zllrntOkCxgfbEejwdR6fmwfD39/w/Ol7x5TluWBXl%2BUhaFYRFRFxUlaVRQeYBiUPNEMXLFkvAyIxDj1A13nDTVtVQQjDVOVD0NRY951LADHiAgN/gAegAKk4rjuJ41i2O4w4ABVMDGGVuL4x4OJ46SuIkgEnjMXYGH2Lwjghc46GuLD/jAvk9xgoU4UOA9aKwtVcQASQUCzBHDVYYnoXpiH%2BV8Ui8Byd0OOs8AUDM4QhEyj1IQ5wgITjxSrZiQIeXToMFOC3kCwQzIIbFLIUAA1VA8ENR5XPcy5rW83yFH8/cUSCj1sso7B/SipjAUg8CBSavTuVg4UEQQzskIUFDiGAE8y1w8JgEOABZTAmiobsHCyYj8UJeUyUpGlnNOULgtC9itsETjdrC9isMTCiIQeAa%2Bu6u5gIah4ZitNMpSUFoIEm6bZvqCErJsgg7IKzAnNuM8vTeE4h22EizEWRi7stHdHuleICFeqamBm5TPtOKyspyoGQHPb1iLBt9oY/DhlloTh/F4PwOC0UhUE4RdLGsLzVnWUHFJ4UgCE0cnlgpAJ6XhbYAA4ADZ6W2SWNDFqWAE5tn0ThJF4FgJA0IJafpxmOF4BQQCCXm6fJ0g4FgGBEBAVYCDcghyEoNAQToeJIjhThVAlmNxckQ5gGQa0pHhMxeG3IhiByvR%2BEEEQxHYKQZEERQVHUE3SF0LhSAAd2IJgUk4HgKapmm%2BYZzgAHlzjtw5UCoQ5PfF73ff9wPJGDw4IA8Z36CdHYuEWXhja0ZYICQJ2UhdsgKAgcfJ5AYApDMPg6A3A2IBiUuYnCZorgL3gt%2BYYgrnLmJtEwBw99IJ3aPLhhaF3tOsBiLxgDcMRaAN7heCwZMjHER%2B8DEjmu6ESpd7Tn3OJsbmoVail0uDEXOR8PBYFLqlPA6sv6kBAcQGI6RMDhmBIYYAlwjB82WFQAwg0Mp4EwFncuQpL7R2EKIcQCcmHJzUKXDO%2BgiEoBXJYfQeAYgG0gMsVAKR6ifxjF8MGpgWaWDMDrbBEcsAiKjF0c%2B9QXAMHcJ4doehQjhEGBUYYmdCiZAEJMPwZj0gWIYHMIYCRM52E0T0cYrQ9F5GcbUVxAgnL9CMfMUxth3FWL0DMFoDiTFOOWAodmGwJBFw4NTUg2teC63rl7H2fsA6HCDmYDuuBCAkGOFzAePMyHLAQJgA0wx1GC0kNseEit6SSA0JIMwkhxaa38OLeWysOCq1IOrbYXB4Tiy4OLUW8tRaTP8JILg/hFbi1SaXXW%2BtDYVJNiPS2o9rZV3OA7GeqBu6u3dhwZoLB3T0hjEwCUBh8JcHlvCMZ9Mw4kEjpnJhsdWHSHYUoThaddBLxznnPeSSUlpLLhwSuttzg1zrpc65tz7lELyc815Hcu4Tx7qU7YUNB5kLNmPE5OL4hHNnj3EASKbmSiME8rgQQaC0FXpQDeacD470vpyo%2BJ8z4X0wdfI8t976lyfi/N%2BtAP6Xx/kQ/%2B9N8BAMcCAz%2BbzVAQKBJfGBlM07wMQVcZBmx6ZoIwdzbBuClAEN/sQ0aRKKFMCoTQuhDDMHfJYfHP5sgOGp3psCnhpC5FWAEfAtRYiJFZCkTIiGgbrCKPSconKoDREaLms4CArgwmZ0MWURxehzH1EzakWx9QokLG8d0PxoTPHWJTfUfxpbgkRI8bkGtTaG0xJWGsBJ/cBmQrWZwZ0xArk3LuXSsaTyXnwg0IU/A4c8X90JdsqpNSsAJHUTqoZIznntPpEs%2BkUsOldIWastO6zbCbKHqbc2VsbZ2wpaSyebs2CcEudklgCh3TWndBOzkYxQ6zo%2BegKOsgfkesTvIAFPqdAgCVqC/OX8IUl1PRXA5Gpa6DpYG%2Bj9X6f16TGFih9uKdjbHKZekeJLTlT0doR4Yn6UgpDTN%2B%2BWaZf0EEekOn2y8WXxDXuy%2BmPKH7cwE3yzRl8hWCBFQ/BVmBn6v3fp/bmsq/5Gu/oA1xKqwHquQJArVPYdX0z1TvQ1qCI6mt4OavBVq5W2u2XwShmUnX0MYIwkD7qJCeqTpBrhMH/XGH4TYEN8Aw2SM4KxBMMaFFKPiCopN6iXGpr8OmnRhbs3GLLUWooWRC35qyO28JPiEv%2BMLfFut7i8vOKrS28JZXAm5p7XErt8dEMnp1gO19vt32fo9LhoE%2BGIBFLnX3UjlTSDVNqWupJm6QBmGedsbY/hAgLM1nN%2BkUyWvpM4Bso2I2GlmHGVwfF4t8XywmWYbp9IBnbCQ61vWWzh5JJDut6Fi77tYJ41kRIQA)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_look_for.test.hpp)
