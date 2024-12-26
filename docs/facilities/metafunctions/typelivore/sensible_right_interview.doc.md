<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-right-interview">To Index</a></p>

## Description

`Typelivore::SensibleRightInterview` accepts a list of elements.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the end of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;E<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleRightInterview
 :: typename...
 -> template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct SensibleRightInterview
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/**** Metafuntion ****/
template<typename...Args>
using Metafunction = SensibleRightInterview<int, int*, int**, int**>
::Road<std::is_same>::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::value == 2);
static_assert
(Metafunction<void>::value == -1);
```

## Implementation

We will implement `SensibleRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct SensibleRightInterview
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...>
        struct ProtoMold
        { static constexpr auto value {-1}; };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
};

template<typename First>
struct SensibleRightInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
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

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
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
                        SensibleRightInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEmb%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwOSEWQ3iwtxM/jcBAAns8APoEYhMQgKGHYEHmfzgyGYaGw5ATdBYKhYnG/AE0wEgv57W4ASRYqXobEETEaX0OQIZtIBQJBBEwrIMIphcMRjFYmAAdArKVcJsQvA5bkJGJlYvQAEp4YAIAhMwQJABu7wA7jiAOxWK63R23EVirmYSUutluj3S5hsBVyrG3CFMBQKAPKYiYfCiEWY/zYh1OlVqgi3SOoIi61BMdAgp3Qu35gtOz3i92whHPP3yxUJ4sl24p9UZogAWU8eaTjZMdqbLUcyGDAgmmFUqWItyYXiItzNYi8hN7FgAtFxe/cYRZC5v/Pbgd2S2XvZXfbKA5dgFHRYwCPHE5dG46vJkjLcO7R0ET7uniJnUB%2Beawpe14cneAaUnuDY7luVKPqWopehKlaIeWPrVuedbYMGBhhhGUYxm697QS%2BETALc2a5t%2Bv7/pRQFuJG0Z4LGHwQfWUFXBusGcVcx7IVKGFsLcABieDEBMSqXM2aaagw2p6gaRomiKxAWpg1qwqJ4kEJJy7QXxFZwqhJ4CTK/pYThobhgqjGEXGkkFtJNFZjmXbwY6emHgWBnoWZtZyvqhrCHgWDEV5yaoqmzkAZ20EFsuTpxU%2BcyDsOckiuOk7TrO87eEu4U9kWBVPh5gRWIE9wQMstwrkGpIgCALBMAA1pgSKZMAkToCikqZAAXm1On1sVJWee5JUTXgVBpaOmXQiNE2OlAEFmAAbOYq22cxRGSlpEykBRinBaFbHYA1uWLssyxJYt8V9lGBAbAwtwaFuME8eNt0lvUSg3V9hbbg9T01eue7vZ9t0blVf13bu%2B6jTacNwSVPmnoJ/kgZgN6CGFEPPq%2B5GAdRrYxZ%2BkqY9j4FYdx41cRxB7jajRmuvxVZ%2Badll4QqFNgbjBakW%2BdHE3%2BLm5uTV5Y7zp003T%2B7CsZrNnkJe0EAdbM1hqmBoAw6Bq0r/kAPIEAgCS405snyZggVKaaqlWrtYn7Zr2u67cRsm%2BJ0ucUVjMK4ZTPq5hgYJpz1lyltLF8xFqotiLqB0dBY0o37vk1gG1vHR8DnJZFsf/oBf0JR5C2OilzEzRlE5TjOqBzgu%2BV4yWSf/aV5WVdVtUh/VjUtW1HVdT1sL9YN2ct83LcFlNFdjlXMO3ctiprRtEc7Zpjuq4dQVCCFrFYed9dXXPi0JUDxDPa9YNcR9E/fbQSi3FP2uzbPJcTQvgZL2tK/2bCmouwdGdt4nT3iAC6mBD6vwRoDTAj0z63FBtuK%2BDMb4Fh%2BoSR%2BI5K7ECPm/HBX0LZ4B1FbI6ylzT21hO7U2XtG43wagZCirlJTf13sHB8KCnx0L9u%2BWKsJAE7zDqPdhTp955VuGAMAMIfxrjwU%2Ba6kCnwJRkYtU%2Bz0zDQksJrOShCFJBVIXbdSkpKGe2pvIxanCWaEgTrCZhAjho0InuYpChIC68KOkAlhgihG3BEYuN6Sim6I2RkItB/i7rQNgc9aRl9AmmJ3NDV%2BstC6BPpn9AO%2BsLwS0plHRsAtCadmFvnHhbgea3lsdiemsMZaHgDinNG7MLIhi5nKEpONBG5IYVRSR0UrHFMyVLamKTkly2pAKb49Iji3GwKoVgbJCRjJGaMg4QoFmMjbDApgVAvCCGyDyJZ8sLGpyDpcYgwBcbtLWS0TZDAHA7K6QQohGc9FqQ0m4CIG83l7AOh8z5D9BAHEkg1Hp3c8AKHarKLEDUXHFJOWUqp1wJkABUPh3l2WcEEZdkBIisgkHSVwIAXI2Vsm5AhJTfIhaA%2Bu34ulmGuvTDFWKww4pBPi9ZVziUMElGaVAIVyVgKpf4KRXBaUWA4KsWgnBAi8D8BwLQpBUCcDcNYawTZ1ibCXMkHgpACCaFFasZqIBAiSDlBoAAHGYMwABOC1XBAimpNVwG0NppDio4JIXgLAJAaA0KQaVsr5UcF4AoEA3rtUytFaQOAsAYCIBAOsAgqQZzkEoGgVkdAEhRFlJwVQJrVorlWpIW4wBkBDikHKMwvAmJEGICFPQ/BBAiDEOwKQMhBCKBUOoMNpBdBcFIJaNEqROA8DFRKqVOq5WcANjOBNaZUDTWzbm/Nhbi3wKNWoiAHhU30EnLiIVvBQ1aFWBAJAKbUhprIBQCAJ6z0gGAFIMwfA6AqSDRAWIY7YgRFaPCQdvB33MGIPCA2sRtBa1DZqlNYEDYMFoF%2BztWBYheGAG4MQd9v2kCwE1Iw4hYNiRA3gM0Hwx1ji1jObYmq3n1DHbQQhaJ/0eCwGO1EeAPXcF4Ph4gsQMiYEeBh4AVGjA6tWFQAwpyABqVoDbVlQ3W4QohxDNuk22tQY7u36EMMYJVlh9CEKDZAVYqBUiNCDRwFcpJJGmEsNYMwfq2PVtCvAVYdhcPOAgK4aYfge1hAiMMSoowe1FCyAINzeh/ONAWCMaoPQnNNEmO0TwnQ9COfZf0NoYWfMRbmFMOL%2BQe0ZcGF5xYvmHOqq2BIYdHBJU%2BrHf6248680FqLSW1dtwIC4EICQdR/hd1aoE6sE2uZRhVVIPqyQ/g5QWv8E6jQkgzCSFWl6wIq0LX6E4G60gHrOtylWlwVaJqLX2tWoam143VqVc7f6wNwbuthsPdGo9sap2JovVerdGa2CcFaCwM0NoVxMEsm%2BLgFq5RcGNRW/AVaa09ukw2uT0gFNKCU523Q96%2B1MAHSxsrFXfW8H9ZO%2BNM5bizpqzmurf3yIA6B8a5rG7T1bo6zSvdAmI3HtQJuhISbL0s5p6MEMRgAdcG9TQWgT7KCvs7b%2Bz9qHxf/sA8BhwqHwO3kg9BsdcGENIdoChljaHRRqaw7K/AUYbn4aM7KojyASOofIy62VVHYg0fhHR7YsrGPMc1WxjjShuO67IozoTTBRPick1rqHsmm2w9kIpjtsqkeqf4%2BZqwmnbc6cG/pwznATMECAvcePlnrMJFswR3TkX2UuB1kFjzOtUtLD8xkALOQsvubSLX0L%2BXwsJfqFF5LsW8iN8S40LvVffO2Bi%2BX4f8xW9pdK2sDYJWhXLfK6Os7nAicLoLTzsngPgcaGa61qtHWuv7t1aQPrWBEiDZdat9bgOps2kCBax1/hpuzckD2rH46A22Eu4fm78A7txunezs9umpmhwB9ouiwAoGaEOGaOTuWBMKDm1rZrWrINDmHi2vIPDlHjoAEL2v2t%2Bhjovn6hOg9jOnOuAZAdAbAURGmOupzmeh1v4MsAztdkzigHQVuoAewaMFAakKkEiDARakiHAQQEiKoPmg%2BkLqbCLm%2Bh%2Bv%2BpLrIQBkBiBvLizhBlBjBvrpgPBohshkZpquhrrk7rwAbrhsboRqoMRiKJbqaNbrwLbvbo7gxtWq7qxgkB7lxjrphj7iwX7gHupBJowFJigaHhIOHq2pgcpjgQYHHhpjYEnvZnKgZtkEZjsPVDnpYFZtjjZvwgkX3tkKXu4A3noJ5uUG3jXsUNkKPiFtkIPulh3kliPkUTlvUf3jFrUQlo0T3h0ePqUZPnPgoMVk2gQadkQRwDVuQVAXOFQXGDQbvu1jukwVdger1pgP1mfmVpfiAJanKP4EELai/l6rsTaDtiMdjpwBdiGj1kNiAJIIEGNg6jaF6iapINalwGamtPPv4IQWcR/t/mVuWqce/swcsaQGxpkM4JIEAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/sensible_right_interview.test.hpp)
