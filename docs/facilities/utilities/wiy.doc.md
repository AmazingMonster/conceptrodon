<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Wiy`

<p style='text-align: right;'><a href="../utilities.md#wiy">To Index</a></p>

## Description

`Wiy` accepts a `Will` operation and returns the operation via member `Will`.

<pre><code>   Oper
-> struct { using Will = Oper; }</code></pre>

## Type Signature

```Haskell
Wiy
 :: template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
struct Wiy
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT;
};
```

## Examples

This function injectively maps a `Will` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Wiy<Op_0>) { return false; }

constexpr bool fun(Wiy<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Wiy<Op_0>{}));
static_assert(fun(Wiy<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Wiy<Op_0>) -> std::false_type;

constexpr auto gun(Wiy<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Wiy<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Wiy<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
struct Wiy
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    using Will = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsai8SioUwvEQAHQUyHYa7IAwKBQUslUml0hmUiHU2lMemM5lcnnszms3kclnchTXADyKTiryyVMBY2IXgc1wA6ngAJ6AkwAdisF2uRuuWKJiNhGPN6JxVvxuItNtNlpJ5MFYoFTNF/LZnqF4pFfo9fOFFPOxGACgVhuNXgyRnVdFo10hABEpTLiHKBAiwxGA5CDQDdSmCzqvr8Kx9Ad8dtcAGJ4Yhja7YVSsR6Yd4nauV3v/Hs3aWy%2BoSqsXJ2OwmWicEh2z63zu1uF2oAPun3B/1u71rnfbkO%2BxUEZWq6UAfQ0yf1epLEMLgJn9oXT6Xj9tZrfK93B83Qa9P//LdfXXfMLiVFUCHTM8uCvKxi1LC4Bz2a4qC8Bguz2f40AYMZMFUFJiGuaJUE8FC0IgDVtShc8NCpRZYOuYhMAINZ0KoMQlALK8S0Qi5sNw/DCOI0jUIYCitQRc8uDohimJY4h0OPLwcQsbiy0uA5rgAFUwMZR27MCmkcZAz3FOICAgBhUEg0TxKotwaIVa9i0WRYEPOGZjNM%2BlzOocjKMklJoKcuCU1c9ykN7X5/hra4hEwbD0BbNtQU7McNKiit%2B0QswITCWkvCwZNMU1GUz2PJhCEjDl1Ni4A0IwnYsIEASCOuFdrnqsSAuooLaI5eiAFpmTGdAQBAdjaCUcrSpU9T%2BOBQT2tJVBOv8iTeuCgbrmG0VRvGpTMBmmUIvLG4dL0xr/k8vATLMlpLOs64sFpAhZugcj9pAF7aAANzEBEeocvqFQ5CBXMWcb/u8TA3LvI85TunyHp%2Bt6ZQ%2BsSvp%2B6HAY24GtuwKlwdcqGxGUuGLA4ZZaE4RJeD8DgtFIVBODcaxrGuBRVnWTtzAhHhSAITQqeWABrEBEkkMkNAADjMMwAE4Fa4RJZZlrhdV1aQaY4SReBYCQNA0UgGaZlmOF4BQQGNoXGap0g4FgGBEBAVYCBSUlyEoNAHjoOIIlYTZVBl/xBsCTrkGQa4pDJMxeEwfAiGIPAxq4GRBBEMR2CkdP5CUNRhdIXQ04Ad0zFJOB4anafpwvzclUkPcg1AqGuYPQ/D4BI%2BjqWzGuCAPF9%2BhCL5rhFl4W2tGWCAkB9lI/bICgIDnheQGAKQzD4OhgSbShokL6IwmaTVK94Q/mGITVJWibQEttgWfeeAhJQYWgT7t0gsGiLxgGXWgptPp/EEhhgDiA/vgJiDg8C/V0oXPCCVSSbAFmEYEOsma0DwNETMl8PBYELsePABtuC8BgcQYiSgUzAKMBgowwtlhUAMBGAAangTAJchwMwFvwDOohxA524XnFQ6gP7F30CAlA7NLD6EwVbSAyxUApBHJwQao1UymEsNYMwZtSHJywLI8GXQ75ZBcAwdwnh2h6BCGEQYFRhhp0KJkAQkw/D2PSI4hgcwhjxDTnYIxAhegTHMXkHxtQ/ENHGP0ax8w7G2Aic4vQMwWieNsd45YXM1gbAkNXDgdMTZ104G3EOYdJARyjjHPuEBcCEBIMmXKY8J50OWAgTATAsDxAMeLSQEIyQKwhFrDQkgzCSH8EbRI/gFb6E4HrUgBt%2BZkn8FwfwMsFbq38JLFWvT/B5I/ubS21tBZ0Ids7GertG6eyXivYeAc2CcGaCwX6upBpMDFPGLgCsyRcGlvHROJAU56AEZnPh0gBGKCEYXXQm8y5MArsQ7JuTTa8Hrmc5urd27FJecAaO7zPmXgHqgIecRakQjMOPA5dtp6z3xfPYeXtl5UtXlyIwbyuDGxoLQHeVsID7w/ufY%2BgDeWX2vrfBwgDH6MGfq/d%2BTMv4/z/gA4hQCWAgLAdKxsRiYFWw/vA5AiDAEoNqIXDBWDj64M2EzAhRCBakPIZgShSrqFhFAOSvgjCFAsLYRwwBALeHZ2BbIUFBcREgE3gYWh6irBSKNfo%2BRiisiapUQQdAajJEWC0YinRKdYFyMMVA5wEBXDxLTlYsoXi9AOPqIW1Ibj6jJIWCE7o/i4lBJcTm%2BoATIklpSQkptuQW2JI7TYutaTuaZLHpMnJtcdkFLReHRlmK3kfOlv3KpSciX1LJVPJpLS2mUGydM2Z7yBm6kSArTWEJBnDMkGnBFzNOB7Jtocx2Ls3ZN1pZc/2gdbnEBYOHFgChfpR1%2Bgu7EYxvnVN0f82QgLfW5wDcIpmugISkChTCqu474X5I4A3d2pJrgtzbr%2B/9gHgNwmbHiglI9coQlJZPe2Jz32L29vS4eIAAMpCCkBhWZ4QMEDPKoTobKOV7wPkfS%2B/LRNXxvnfUV%2BKn4vzfoXGVv8xDyoFlge1oCzW8Ageq2BWrVAIOBHqwQBqP5GuwZqU1%2BDk6WpIXEG1drlWOsOQwpgzDWHsJlJw3g3qs4SD9YIOD4KQBIdDcYFN0jojRuZrGlqnAtj7XDZo7RcRdFZoMb43Nfh82mMrcWwdMTy1ZErUVkoUTS31rCe2ytmW20RNrTE/tNX6vla7WO9JPMsnocnWbadhGAPXE42SHjy6fmUf5jRxppBmmtOGAYnW%2B7g3vIhBCRIqsr1GxW7qJZ2zesW1sPs2jrlSCdMSD0jWuojYy0kMrLgcszBbJ1hCHriK70bpFuOuOu3Xv7aO8sUhGRnCSCAA)$Done$

## Links

- [Example](../../code/facilities/utilities/wiy/implementation.hpp)
- [Source code](../../../conceptrodon/wiy.hpp)
