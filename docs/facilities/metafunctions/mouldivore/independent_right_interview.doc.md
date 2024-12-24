<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-independent-right-interview">To Index</a></p>

## Description

`Mouldivore::IndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Es...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Es...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Es...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentRightInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentRightInterview
{
    template<typename...>
    alias Mold
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
/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentRightInterview<std::is_same>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

We will implement `IndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentRightInterview
{
    template<typename...RightSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
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

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
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
                            ProtoMold<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoMold<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgAJzSAA6oCoRODB7evgFBaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMAGZwshvFhriYQW5kGN0FgqDDsEDzGCGBCvFCYW4CABPR4AfQIxCYhAUKLR3z%2BtP%2BQJ%2BO2uAEkWCl6GxBEx6h99gDGXS/gCgQRMGyDKLcaLxdzMFLCYxWJgAHSqlHXCFMBQKVXK5TETD4USiykg1EXMbELwOFkMLCPO2MAgAJTwwAQBGZgniADdXgB3NEAdisF2u4eu0vZsvlDqVutd7uEeCwpvN5wj10t1oI131qCIAFlPOggZmTCGy5mI9mbUIDAoEFXq9DK2GW9WoxK5bCCXG2Lqqe2OzXSTm88QC6hi7RS8OR62LFmmo5kBqBGNMKoUsRrkwvERrj6xF5MIuALRcCu3GFL6%2B36kZhfhrsx3sK5hsa4AMTwxDGQ5Ps%2Bta5vmRYlriv7/gQgHPuGFZLvB85wcu3J4GuaAMJu267vuh7Ht4Z7Nihi7ESREYmAArFYlG3BAizXOe6oIiAIAsEwADWmBEhkwAROgJK4hkABe3EwWaZHkaRyFSZmeBUOuWGijh0IybJ4ZQIOZj%2BOY/j6oa6GyqabhQWMpDXImHpCCmbyDmarEEaeiyLJJ6mLtcBoEGsDDXBot6tjeFyueptRKMFskIR5mBecQPmXv595qSR170eFHb3iCoZAQuGVZWlL5itGkrvv2Z6mQQ5l9oqX5CJgmHoJVH7xqqADyBAIPEab5cuVo2mB04QbC5XmbV9XmW1HX/nZ6YoZFSHZShMyrop2E7nuB6oEeJ5EUlI4Id1e3UVRdEMUxZrLugrHsVxPFuvxgmwiJYmwW50kLa98krcpa0HXBmlqtpun6UaRmQX%2BZkWW6Vk2Tqar2SAjmYM5v3PpFnneb5CVBoFgK7VJoVnp9mGrbuKMLv9yq6UDBogyauKjQIDWQ0m1mptNDnbcjePkWj0UY1emUBY%2Br3VgT1xExu33EGTI4QDLcH9TOpawhNnXTfLz4c4R1xgGAMK3IxV7cyRLnG7NIaqe9IvhujsXXGY0KWBOU5K7iqtTXDM3Wy2WunglZtwYluNWyFtBhQHqMW7bcUC3e2MawFqUR0LmXdblwXp0FSWvsVeJNQOqrnMABpik6XVJV4GRGNcSvQiCBv1lqSAgDnZ6K4NbhFyXnIELDlMSan86Z8Hmat7G1UqoXxDAOX2WV%2BEwA1yWdcG%2B3s64uc0991Sg%2BAvHu8MoK9I0jc2CqKw7Jnp8h9H3yj6MjX0VMFQXiYjy18XGPJUT7qm8z4B89q6Fifi/N%2BWQV62ntE8QQllPTemIH6TAgZHoEEuiAPACgeJKkAqxV2sI/7bwHnlE%2BexrgABU3i915HsAES10JEi1EoFoQIIDAKaKAhwWRcThAIHsFEuCO48PMjwnYwjBB7DEbwnY/CEbbRXvre2Lld50OQAw7U8QYIXFYSA1%2BnCBC4h9KgFMMi8FuCEeLcRkiJEWKkTIxG8j66GyURYDgyxaCcEorwPwHAtCkFQJwNw1hrBZlWOsIioIeCkAIJoVxywOIgEopIZUGgAAcZgzCJESFwSiqSUlcCDEGaQ7iOCSF4CwCQGgNCkG8b4/xHBeAKBAFU6JPjXGkDgLAGAiAQCrAICkA85BKBoDZHQeIkQlScFUCk/w55/CSGuMAZAa4pDKjMLwAyRBiApj0PwQQIgxDsCkDIQQigVDqFaaQXQXBSD%2BjJCkTgPA3EeK8TEvxnAWoHn6bmVACkpkzLmQspZ1wVkOwgB4EZ9BSYRMWLwFpWhlgQCQMMlIoyyAUAgMi1FIBgBSDMHwOgop/yUBiK8mI4Rmj4gebwMlzBiD4hajEbQdUWmROGT3FqDBaCUouVgGIXhgBuDEGHKlpAsDsSMOIHlf5mV4B9G8V5W46oHk2JEnhtRXm0DwDEMkdKPBYFeaSPA5TuC8DlcQGI6RMD3HFcATVRgYnLCoAYGeAA1AMLUHQit2cIUQ4gjnetOWoV5Vz9CGGMEEyw%2BgtWNMgMsVAKR6iNI4OeBE%2BtTCWGsGYWpZqtmpngMsOwMrnAQFcJMPw1zQjhEGBUYY1zCiZAEGWvQ9b6hzCGAka5ha9ENHGK0Tw7Q9BdvqL0Fobaa0dtsL2ptnbe1joWFwAtoSNgSCeRwTx1TXl1OuH82Z8zFnLKSaC3AhASCOxBAu2FDrlgdSYFgBI9FSDxMkCCZUiQQSFI0JIMwkh/CVMov4RI%2BhOClNIOU89yp/BcH8CkxIeT/CJOyW%2BoINTeB1IaU0qJDr2ldMRT0z5Az0WYsheMtgnBmgsB9EGc8TANQGGrlwRIyouDJPWfgTZ2zrnev2X66QAalBBouboPFtymD3JNau9dKG3kcA%2BX0g81wfnbumbu2jYbgWMeYxoa4YLUAQviGeswMLMOtIRUi3TKLIWDIxeZrFmojAMa4FUmgtBCWNIgCSi5NKKUiq83ShlTKHAirZU6DlXLXm8v5YK2gwqTWirFGGyVvj8AGk4XKpNvjFXIGVSKtVxTfGau1RSvVmxfGGuNZEs1FqlDWoSwvLDTqmCuvdZ62LXHfWHN47IQN5zfFCdDfa9NVhI0FZjQ%2B%2BNibOAptQWmiNFgs2oZzTDfNXQi1%2BBLXaadwQ7RztraQFtWRNv7ZKFW%2BYu2h09Cnf2vInbairZHf0E77bB2XdyOWydsxHvjpXSsNYy6F1AbXS8i5W6d0Ars4vBjTHknaePZss9F7jPwuvZgW9wwH3FJA2Bxjn6gyUUSAUkEX6f2SGuVJtDtgMNwraR07pvSvlWaI2MiZHByMApYAoH0a4fSQ%2B7GMVjJ7c07NkNxjrxz5D8Z6zoEAIIbl3KpRJoHtT3n4e%2Bb8tnHOuc86MrmHTemoUghBEZqnpmUA2cs4Rs3wxOcpBSESbniQiS84IESVQcz8Uuc6sS0l5K6U%2BZ9/SxlzKgu6fZZy7lSXMB8oFUKpNkSxUJZK7wZLMq0sKtUEq0UOXvR5d4AVnV%2BJisGq2eV018QqtWvixKurJm%2BDOoUG6pBHrGBeuF%2B1iQnWTkS%2BDdL/r4aM3Dejct8bWQk1bBYoNzN2b4i5vlbGlb3aXAbau29ytZQnt1vSA27Iy/m2b9bZ9%2Bd8/h0vYHTd7oAh7s7YnTMCYO%2BZ0fbX19/7Cgl2HIVxu4HnBt3q850eLXJoddYdT10QEdjdkdUd71V1McQAMllQDdKIckSdKkDcgxoMP8ld6kKdmkr1H0QBJBKJX18kgxKkUlJAskuA0ltIAcQRFdUNOBL0TNV01l0C6DMCwDSAzUMhnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/independent_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/independent_right_interview.test.hpp)
