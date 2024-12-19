<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-2">To Index</a></p>

## Description

`Typelivore::SensibleLeftInterview` accepts a list of elements.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Predicates...
-> LeftSides...
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview ::   typename...
                        -> template<typename...> class...
                        -> typename...
                        -> auto
```

## Structure

```C++
template<typename...>
struct SensibleLeftInterview
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
template<typename...Args>
using Metafunction = SensibleLeftInterview<int, int*, int**, int**>
::Road<std::is_same>::Mold<Args...>;

static_assert
(Metafunction<int**>::value == 2);
static_assert
(Metafunction<void>::value == -1);
```

## Implementation

We will implement `SensibleLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct SensibleLeftInterview
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
struct SensibleLeftInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
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
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEElzBAA6oCoRODB7evgGp6ZkC4ZExLPGJXMm2mPaOAkIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW15nWN9A2UVIwCUtqhexMjsHOb%2BEcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PBEwLBSBkBxzcBEuKUYrEwADoEb8HmNiF4HAchIwMrF6KFMFQCABJQQJABueEwAHc/iYAOxWB4HJkHQHA0GYcGskFMMEnSHQ5hsBFwm4HPZMBQKYXKYiYfCiQEKJH3ZkHFFoggHGWoIgAJVQTHQf1VdIZKtVzK57M5UJhQsR/lujItTPV6O1RAAsp4jc6Xaa1U1HMgxQIxphVCliAcmGdUAdSWIvK9TQBaLh0gAixwsR1p2f8ZuNLpZQO5vIhtsF8IR92AsqBjAISsdxZdXgyRgO3to6Dema1xB1qB7RpOdYbbEEUodt0LbbzBaLftLbJ5HL5ZetfKrsOFovFkulsvl65bTvNTI7EWAB31hv7g%2BH97HbhlcrwCswM5FrfnDyzHMaQBLd1xtAVYQOAAxPBiDGZU3U1TEGGxXF8SJEliHJKlwRguCCGVU0FytMDNzXCt%2BTtGtf2wMUDCPBF31PRVlVVRCnz1A1fUvPMzRLVdyw3SsIPtOE8QJIQ8Cwc8FzYghUXdIcvR9WTmQDJlVJdGZg1DFDAUjaNYyIBMkxTFd%2BKI8z%2BLUwIrECTMIEWA5U1FT4QBAFgmAAa0wAB9DJgEidBfIIk4MgALz80KL2sktLJ42KXTwKhdPDAyjisxLmSgfczAANnMPKmM/M9wXE4QpO/YVSGg2D4MddzE28TBFkWTSst4g5ZQINYGAODQc0XYCEo6plaiUdqsoDbreucjNCyGzLrKzRzJrU/MgKWwD/3%2BEamRIijd1EidMEbadWJLa8u1HR8PRHFTx3rU6p2bfc/z49al2G1UDqE37wKot7aMPH8TrO5sLqvTtbxfW6lNQF9wTBl6f1%2BHbtuXe5/p3ETXjwsYaso6sMUwNAGHQQmjuogB5AgEASGTkXkjUSZQvAcUwcriUBLCKWpE58YIGrMTJimDlp%2Bm4KBml6WI0CKPlv6qaBuiJR/Yqv0Znj2LuxGV3i/jseEwGEXKyTpMhi0dfh0d2vUjK9qtoNP1S/SoxjOMTOah2ptlpaLNskx7Mc5zXIIdB3M8nz/LwQK5RC8EIqiy3fY%2B0bVWS12I3dtbYpyxF8sKjXSpOM3Kp/GrBZuRrTNa3PlvpLrMB64g%2BoGhbAIA/3EvG15M7JtKc%2B7vOIFygr8uLljS/Q82qoRYXSYEMdsBr5q6%2BHhvcxm1uDnm3NO929OLV7g5%2B7DN3iHr/iICvxLkNQzn0O5sk%2BfBCWGeljesvc367y48FJ5zxorfWKP9Fbdgem4Mu0lP6OyPqvZMBwwBgGOAOdMICLRtS/nFRuGD%2BLbz6mYI4lhWYPy5phbC/M3DvylrOPBJYwHkVeIjE4gDUatmwaAkAv9bbTwkuXWBR9%2BIII3PvThFoD70LGrQCa4iTSNwIXNQaB8j4rSwXAz6m1HYY2%2BiWI2RM9y1ieuDLW/Erq3huqgji91exI2MSjaWO15FfS7jxfRisAbVhViDYUyMmymOZOYv%2BD4rG63/o9Sc/jHFFg2ujB4AB6AAVMklJqT4l/CSckgAKtgIQWSUnpISak4piTCm7SeAwPYXhDjgjOHQK4hEQJMM8YYuE9xiDAC1kEz0zcmBUC8JU%2BofUrH33ZmhAkz9eY4ROBEIWp9BCJJqrM5JSyFmJOVO5Fhbg3IgDwAofysJq4gF4W4dpnTonDW0p%2BXyasEgEQeBAHpTR%2BmDKyOCZZ6yGogCaog1BVizBtR2lc5ANzJR3L%2BI83pLyHBvJOKSVAUkjk/JTP4AsaCuCAosBwZYtBOCBF4H4bgvBUCcDcNYawapVjrBTGYfwPBSAEE0Ni5YXkQCBFpHCfwAAOPKtJ/C8o0NyvlABOfw%2BhOCSF4CwCQGgNCkEJVoUgJKOC8AUCAOVjKOBaGWHAWAMBEAgFWAQFIZxyCUDQMCOgCQoiwk4KoHlqY8qSAOMAZAIYpBwjMLwD8RBiBST0PwQQIgxDsCkDIQQigVDqC1ToPQlJiBMBSJwHgOK8UEqZUqzg1Mzgms1KgFK9q8qOuda691khPUHAgB4S19BozbAxbwTV2rSAQCQBalIVqyAUAgO2ztIBgBSDMHwOgPM1UQFiBm2IERmiXGTbwKdzBiCXGprEbQpNNX0otS9amDBaCzpjaQLAsQvDADcGIGRc7D1AkMMAcQB78CyhhaSb8GaIykzOJselszagZouLEBNS6PBYAzfJPA0qiWkGfcQWI6RMCZmvUYC4RgmXLCoAYTpAA1Pm1MBSXsDcIUQ4gw34cjWoDNuguD6BvSgcllh9DszVZAZYqAUhDLVRwVMnxUGmEsNYMwirUBQb9dJeAyw7DrqyC4cmkw/CUbCBEQY5RhiUbSBkIZMm9CqaKAwOYQxKhdAkw0cYrRPDtD0OJmFRnZgKfmMp2wxmNOUZmC0XTSnKhiapRsCQqaOD4vlRm5VBxC3FpdW63e5aiEQFwIQEgxC6WLEbSh5Y9NDTDEcqQVlkh/BwlFbSSQGhJBmEkHlWVgQ8rCvFRwSVpBpV0rhHlLgeUuXCq5Y1wIkhkiiryv5g9yrVXqoZShlt%2BrW2Gpzaa7tvba02rYJwZoLBSS0lTEwVWXYuDCrhFwOEiqfUkH9ZR/DwaiPSBI0oMjB7dBDvjYmudPm/MKuJVm8beaUrzcW8t1bt51ube25W6tHba1xYBYlmNOq22oBrQkM1PaIcA%2BGG9pb4ojDra4HKmgtBR2UAnQehdM7L246XSutdDhL1bqbDuvdGaj0nrPbQC9EGsCeUQ5sRVD6JPPvYzt1Q77ASXu/big9f6AOXCAyzxtfrwP0qgzBpQ8Gme3pvENtDTBMPYdwxBw7hHQ0ndkKR6NirLtUeQzxqwdG/2MfSyxtjnBOPh247Riw/HiVCfLqJgzlm/AQFcI5kI5NXMLBU4UdTpm8iB7U1kf3dmLNDN6BMEPsn3cx%2BM5H/TzmTO5AT2nlP3mVhrC8xiyr92AucBjMQBbS2VtI6%2BxtrbGhK3Rd9XFhtg3QfJcwKlxI6WBfVdqxtgrtJAjCtpHywrxWOs9YE5wfrGqhu6oNUa3N0OpvWttRwebTqDgsAUKSEMpJvvsjGN6/Avr9vhoIyGiQOuI1nf17GsV12k1Eru%2Bm3rT3jVnAOPm0vLAN9b53wmffM8TUKtWHTtOLfwBLFvZtUbZfLtc1UA2tb5ZAFIFIXyPfYVXyA/AgG5MvJ1YdDHBmLHSdadJdfHEg5dVdddUnCHbdXdfdVnTAY9U9c9djelRnG9O9VnWCdnF9A9N9ZAD9PnEkAXRVIXGdUXEDCXS9aXWDOXDgxXUHPgdDBQLDKkHDRgPDWQI7bXM/PXcjAII3YwB3ejWIC3ZjVjLIdjeJNyE3PjATF3ETJjRPSTL3aTePPQeTUoPTTTIPLIH3LTIZbPJzWoQzBgWPdPMzYI7oKzFzGzbwpzBzdwhI6zLwtzHPBQTzUNZ/CfR7Dgb/X/bfXfQAxUYAhvWLetSAptZlUgFLLATvHzHvEAMwDbfwIIQIArVHQVfwWkJrHIzNFVWwAbKo1qDLEAQrerLgfwfKKY4VBrfKDQWkSrfwF/SfAY4YnzL1PovrKA6oqDDIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/sensible_left_interview.test.hpp)
