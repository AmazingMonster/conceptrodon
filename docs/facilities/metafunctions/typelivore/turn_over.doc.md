<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-turn-over">To Index</a></p>

## Description

`Typelivore::TurnOver` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Capsule&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TurnOver
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias TurnOver = RESULT;
```

## Examples

We will turn over `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int**, int**, int*, int>;

/**** Result ****/
using Result = TurnOver<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

`TurnOver` is implemented as a shortcut to `TypicalTurnOver<*>::type`:

```C++
template<typename...Elements>
using TurnOver = TypicalTurnOver<Elements...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOt2wqgIrgsTGQAGsvocgVCWGkDFCTIE3AQAJ7PZhsAB0xMx2BBE2IXgc4Mh0NhCJMSSsSXumKsVxBKLRTAxWJBtwFty56MwmOxeMYrEwxMJpNuyAMCk%2BHkETAiCVI/MFuPxUpl2HobEEChBpPJBEp1IhUIY6Bh8LFKpa6uIYoNmCNBAUMrNgTJHKZWoFwp5oqxOslROJl2AxEwHsYXrNV0Fty8WSMtwAsp50LdMfdbk61ZFXVj3Z7vcTSLcY3GE8afX62aaWS2Ob8wW4mGkFF56IiDsiPdzeeLdVHZc2rhSqQQiz2%2B/R28DO3cACp4vCiWjrjYMADyADcEoOzpyRyKxRGCdKSdPLrPqZu0tuxHviIeT8R84G24F2VXS4QzHG8pVuAAxPBiAmZNHwtOdbhfN9d33Y8EjFKCYIIODGUA1N0wiYAhQlfNAkLbte37MM3Cw2DmwA1tWUYjtgMvUNrwlW9IOgiYazAthbiETA0FtOCn3nZCdw/L8MKxOiCBrYTRPQXDAxTQVCMzCMyIoxdqLFZSBHQGsFN9QDGWYiyrhAmiBMwHjsP4rjwKM21nInO9CQPAgEASE0HwkpCt2ktDv0w3jFKEkTjJrHy/Jgpt/WBdTLgIjNiJ0oNdJpG07XpTjPOC19Qs/dCyzceL/KSkAQAjODU1q2zs1zQyYvcxz6LJFiUqs001wBQakRBP49luABJVFDUTHkcjPIFRqGgEgQvKaOPDFzJwrRMAuSrTiJk8qcqk98wrktxtsbe9sCaiUVxGpbAQeu4IVYNEHO%2BZ7HqHfrgTMQIIgVLwsDItxRK2NIkwfL6xsopcPuGmz2NAzavPEhDqThgyephoSvDSYpMHQAAlD5%2B3nT6rn2vGCcyInSaXecCwXKjlyxCICAOGsOa524ee5wRzN%2B0bbgZ8n5pBamxdoJnyKQs6Ko5gXOeV3meb2IXWJF9cPgpxH4Nm5AAH0mCVBICAgCZ0FqhQpRNgK3CEfHCZJsmZZraWcL9ZY2Q4VZaE4fxeD8DgtFIVBODcaxrFuBR1k2BzzECHhSAITQ/dWOEAkkQkNAADjMMwAE4i64fx87zrgkiSaQA44SReBYCQNA0UgQ7DiOOF4BQQFbtPQ790g4FgGBEBAdYCDSLxFIoCA0FROgEiiKVOFUPOADYAFp18kW5gGQZBbikQkzF4InCBIPBrdSfhBBEMR2CkGRBEUFR1AH0hdFSAB3Yge04Hg/tA7B3TuHTgB5p5T3nKgKgtw15bx3nvA%2BR8c5mFuBADwC96A/iTlwZYvB%2B5aFWBAJA89XzYPIJQMhi9EjACkGYPgdAoQwUoLEUBsQIitBxAA3gHDmDEBxAeWI2gRL9xTvPT0B4GC0G4R/LAsQvDAG7LQWgPduC8CwCwQwwBxByOgqIvAJ41Fh0wKoES09tgpw5vUUBtA8CxD/gIjwWBQEWjwE3dRpBvyxDpo8LRRg7FGHTqsKgBhgAKAAGrvG/gefEPDn7CB3I/aQt95BKDUKAr%2B%2BhtEoGjpYfQ9ie6QFWKgSGOQ1GbytgWUwlhrBmA7t%2BYgV8PjwFWHYAxzgICuGmH4VIYR1SLFGKkYo2QBA9L0CMxoCwRiJHGPUDpTRJjtE8J0PQ7SHB9CWdMqoQzbBLPGeMLZAyZkSDafHLYpz9DALbqAzucCN7b13vvQ%2Bx80EQFwBfHB/08EEOCasPyTAsCJAgJnEAkhAiEiLoEGuGhJBmEkOvFu/h15FyufXRuIBk6EnXlwdeeci6V3Xv4SQZcoXrxuR/Tu3de6p2CUPUeJDx6QOnpQueqAsFLxXhwVoLAjxJE3kweUBhMxcCLoSLgucz74CIE06%2BCT77iCfqk1%2BGSP66AYb/f%2B6igEcCDhSju4DmXQNgfAx5QrtFHzFRKjQ6DMHkNPEnMw%2BDaUD2IaQ9l9qyCz2odglAwq6Gl1bjQGW/lWHsM4QI%2BJfCuFCJEQ4eJEjExSJkaA%2BRijlGqPiZo7Ruiw74DjBsoxoDTHmKhPE6xdcw52IcVw5x2ww5uI8SnbxviPQ5qInS0JTBwlRMwDEuJnjUkKuSQklV78w7quyUEmpVh8nVqKSC8OZSBAVKqeRGddSGkJFlS04pPQFkuFtAckItptlLGGZkUZuQVkFAvSUHIZ7dnrMaP0KYN7en7o2QIV9gxjk7NmXsgYx65htEfbMs5GwLl4LRXq9uvA7mmsQQqC1orxW53QR8mV%2BZvnOsIRnUgAKgWUB1Q3UgTdAhithUkfwRdq6BDhQikl%2Br4OcGpX3Olw8x4Tygayn1nK2CcB5YglgCgjyHyPKhkUEwpWfKvnoIdSSJApNkGOzJmLSCarSDwnVsHbmGsntPW4MC4HCdE%2BJyToYJi2o9TQ7DgRAi4Y4%2B6jlXqqE2d9WJgmRsJNFyNlJggRtVA70YSGlhEA2Ef2jZGzxUXBHCNEQm9lkjpGyLzZgBRSixCZs8dmgJ9aNH6MLS0j%2BJbkAWPLYIGxH9q2OJxHW1xTSm28BbUoPx7agmur4GEyJ0TYmMHiQph%2BSnR3pPHTodT/rcm1LnYU1pS7GhqJ2FbKbs6LD1Pg405pC62nzK/X4LpR7316H6RUE5d6r3HsmQ%2Bv957P0vv2UduZvRv1HNO/%2BtZD38gfpA7%2Bt756IMJ0uXXXTlLOAmd3iJsTtwfOEn8xh6VJA7M/JdUQ/5mBAWjEXXXUjTdi6Ens/4cuJKW72aSHi5jYCu62BpXh5YoLJD%2BEhVXJILc86SFLlwAuZhyV10CCA0HVPac6tPhTqlKP8PfiyM4SQQA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/turn_over.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/turn_over.test.hpp)
