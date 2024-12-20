<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllDeceive`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-deceive">To Index</a></p>

## Description

`Varybivore::AllDeceive` accepts a callable predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&(not Pred(Es::value)))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0(***)))` and `(...&&(not Pred_0(***))) && (...&&(not Pred_1(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&(not Pred_0(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&(not Pred_0(Args::value))) && (...&&(not Pred_1(Args::value)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOVDESiBVmRwPx9weJL2Bz%2BZ3OXGuBzuj2er3en1hqEpFxpQNB4Mh0NZCLhSNR6Mx2NxmGJhOJjzJN0OADUmABPWn7ekPAiYFipAyaoFuVmHACSQOwJPGxC8DgVypJKKsj0OTsOs0cyEOjM1zK%2BPzZADcxF5MGDUSapf4HaTw5HZRSqF4sTd1ZrtbqJf43AQlalGKxMAKHsRgApTSTTgBHLx4U4KQ4QAXmABsTYgDFQBHZlwgheLIBAAe8mCWw5JnreH0OMVQnmxCYgQrRmAxxCxONoeIjKKJMseKZ1TD1GazOeYbALRZL/jNjwrVZr9YRTZbbY7JypGm7F77A6Dw6WYLMZtALrBtAOfdtOy4T9e37QMhxHBkBCZCcpxneMGHne0RRXQ4CEtdMCW3UlHnJfZDgAFUwcZVVuMltkObBiGIEhzWaN1ziYBQlFaagE31RUlX1LhSyveckQjDgVloTgkl4PwOC0UhUE4NxrGsF01g2YNzH8HhSAITRJJWABrEAkkbOEAA5GykJJkUbSQAE5/Hssx/H0ThJF4FgJA0IJ5MU5SOF4BQQCCAyFMk0g4FgGBEBANYCFSH5yEoNBtToeJIjzThVGsgBaBzDmAZB3SkOEzF4M5CBIPB0D0fhBBEMR2CkGRBEUFR1Ei0hdC4UgAHdiCYVJOB4KSZLkwylM4AB5H5ko7VAqEOPLG0KyRitKw5yrMOsPAy%2BhPh0rgll4CKtBWCAkHS1JMrICgIFu%2B6QGAKQzD4OhNWIUKIBiaaYnCFolTG3hAeYYglVmmJtEwBxQdIdK2EEWaGFoEGeqwGIvGAA1aHXBGsBYQxgHETHqzhxw/So6a3jhn4tj08JNWknraDwGJhshjwsGmvC8B87heGp4gpyUYEtRJ9mjEMlYqAMYt5TwTABtmk8Eca4RRHENrNc6tRpr6/QSZQNTLH0DnQsgFZUFSBpQo4fLxnQLlTEsawzECkXiDqmnre6SnshcBh3E8Do9FCcIhkqEZ%2BqKLIBCmPw44yBOGHmYYEn6uxA4EPpJjD/Js7qXPGgmAYo4WWPbHLpO9FmVoM5jrOVgUTTNgkCaOFk0gAt4ILVoKoqSrKyQKrrXAauOtzTvO2WVgQTAmCwBJ51IUzJH8OFnORSQNEkMxJEbPzzMcjyOC80gfP8Mw4X8RtkUs/xLKSJIuBcxzLN76agpCsL9NltFOK10EoLRSo9Z6R1spsFykPTayADBGB2o5OEXA4SKWqkQH29V%2Bqa2ajraQeslAGx6roD6Q0Rqgy7j3PuM0ODzSSj8Q4y1B7rSKggkmyDUHoP2qgQ68QAI3zOgAyKV0bp8LukdVKT0JEvQ4UYLgjkuBBBoLQb6v1/o9XBsDBG2jIbQ1hvDIWiM%2BHIwIKjdG00sY4zxgTYxRMpZbEUvgU4Dg8DUwdhg1Q9NNQI2ZnUaa7NObAx5k486PtBZ6RFmLTAEtiZGGlqAURfAFYKCVirNWjANayHwa1Qhsh9bdUUmQ42Ms3ZWHNkEq2a9bb204E7AgLsQTlI9l7eI2C/Zrxzm45wEBXB136pHcomc9DxwaAMtIqcGhN0WMXHoeda6F2TgHHpZc5iVxGdnRZeRlkNwrsM5undVjrA7qdc%2BNCf6cFYRtD0iDgBcLQVcCAk8sGCNniIy6C8l4r0oCZXyQRWaX2vkkOETkkiOTMBCwCll34OW/j1X%2Bth/4XSijFeKiVFrSMgVlHKHAWgsCKiwBQfp3R%2BkUXCNM4wqr4CwXVBqOTtZ5PavIYhRSdABEGsNUaQtqFTQRXNMBS0VqqEJcS0l5LKUdggAdSRAidL%2BGESisRKBZFSIgaqkYJLUipHOGSxy5xJXnBFYQr68QNEAyBpDXRlqoYw0pgjJGjBzFowxs4zA2NcZiDsXpBxCSwmkBcYHDxtNvHIAZn4wQAS2Ycy5kqUJfMIkI2iRkWJksEnhCSZdFJTBFbK1VurYxeDGUSHyR1VlhsOV3NNu7Splt4A2zttkB22xnbVoqRYT2/dva%2B2qa3Euqzg6hx2RHEOMzq5jOyBMidpQNmHLmaXfObQln137Q0RdY6s4136BMvZG6jltxOa1Xl8LApXONYcIlJLDh6opQeKiUqXkkDeYq%2BepBF7LxGGvQF3kAi31hW5MwgGuCWQ0I2cFJ7%2B6cD/uFV9G8t7vxfgffwSRQNuXsuffwfLT3BQ%2BUZc%2BlUIN0LnqIlYItMjOEkEAA%3D%3D%3D)

By turning `(...&&(not Pred_0(***)))` and `(...&&(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3K60WgAETqmDwADdMHdoSy7hAiQTzAA2UUQBioBlIlF4NGYCAk8FkhQgECcsReTArHXQqzXEF/AHnQ3HO4AFUwswUXxNv2NJyBpvuMvQAH0NLbDkCabNMKoUsQ7nCEa6Pbz/PyTIkrIkWRAQ6ghSsTAB2CzIgibBh3KhiJR6tMswsG%2B0u5Hurhe/Y%2BgR%2BgNBxOIituqt83kx6PxxPJtMZzBZ4g5vO0Av%2BKyp4vjkHOw53ABqTCx1aBYIhH0w0Nh8NQj0pINmxC8DgXS5n6ZBdyvd1mHzld19YIbwZ3dw13h5fYeRZLwMnv9nfZcy8HNvhBNcXg3LdsVxZg2CFK5iGACl/Cpa5kQARy8PBkRtJlWXZLlNxhMMgkZJCFCFfdrkff1AzuGJUE8YCGAgFN00zbNc3zYiJ2LUtQXBSCoRhGC8XgolEOQ6jEMwLCcKtRlmTZbYiK3UiMSkyiiUpXkzDFfSlII1TuXUlsuE0iiqNQ6k6yfejGOYqgQLYvtOKHTEj14n8BKNC0rQZMDrlvRxkDdJgFCUFpqBArdFyxLcuH3VC2JTccODWWhOESXg/A4LRSFQTg3Gsawbw2LZPzMfweFIAhNAytYAGsQESEUCQADhFKRElTEVJAATn8Prqv0ThJF4FgJA0II8oKoqOF4VUgnq/KMtIOBYBgRAQA2AgUnhchKDQZ46HiSJ8U4VQuoAWn6u5gGQZA7ikAkzF4WUiGIPB0D0fhBBEMR2CkGRBEUFR1DW0hdAsgB3YgmBSTgeEy7LcoawrOAAeXhA6GVQKg7mukU7skB6npeyQ3oFDxTvoINzBqlZeFWrQ1ggJATpSM6yAoCAuZ5kBgCkMw%2BDoMFiFVCAYgxmJwmaLFkd4OXmGILEsZibQ6lW2qTreAgsYYWhFahrAYi8YBYWZVVuF4LAWEMYBxFNhT6m5G2Cv9Op4R2WrwjBLKodoPAYgRtWPCwDGCG%2BqbbdIbliEYpQ2Qdoxg6MBq1ioAxkPnPBMFhrHYKV0HhFEcQQf%2B%2BQlDUDGYf0R2UFKyx9BD1VIDWVB6SyG2btmdA%2BVMSxrDMeaE%2B%2BrB27YroeiyFwGHcTx2j0UIFnKSo9EKTIBCmPwLK33ohnX0YLNqeoBH6SYl7yU/um1ho5iPkYElPuZd70W8WifpYX7WBQKu2BIVGHAcqkDmrwBaRNbr3Ues9V6ZgBS4EICQPSTMWaZzWAgTATAsAJGni1SQ/gCRDVTJIDQkgzCSBFDNNqA0xocAmqQKa/gzAEn8CKVMHV/AdUSIkLgw0BodTARjBaS0QArUzhtbaHNdq40OnzAW9MLpsCutAsmyADBGBegNAkXACSe3wF9H6f1ZCAwrtIKu4Na5Q10KLeGiMlbANAeAzGHAcb7XhHcAmUCSb3Q0Y7bRuj9E01QHTeIqCzDMzqpImRij4hHX5qE7m9MUCaOFgNLgQQaC0AllLGWUMVYKxLoUtWGstYOBLnrMkhtjYYzNhbK2o4S720ds7Aq%2BBkRuytBjL2yAfYl39t0DGwdQ4KwjjsAq0c8Cx1qgnJOmAU6tPCKANaWcc4KDzgXIujAS5VzMcDCxsgrGQwKrYhuGch5WBbiMqendu51k4H3AgA9IyXJHmPeIE9ukdxnvfZwEBXDvwsqvMoz9N7pG3tka%2Be9UgQsPmvMFt9Z4XzftCj%2Bd9z59Efgin%2BH9UW5BhZ/eYoLcVcD/gA4GTj0ZQ0gcTUmD40mBL0Z6RUhiUGMzJeg1ZmDsG4MoM1aaQRA6MOYYkAkg1EgDTMFK/SHV%2BH9WETSzgYiJGrKkfAGRe08YJLicQZROxmgsHuiwBQnJnqci4DoyEAUPpsoniYgG5cDml2OXXAIpB7FI1tlSxV81sZyPxoTVQxrTXmstQSa1swQlhIZtVfwUTWbrViUknmOqU0pLNSkFIboLUDTdJGggbpg0WPFvEPJst5Zq2KZW9WmttaVNCfrGpJt2mYHNpbMQTS44tLThMu2rtHDux6aob2YIBmCCGUHEOYcsTjKjjHEucz0gLPBEsjOars5MFzvnQuxc457KdRIQ5YMa4nJ0O6tJTdh7XLbvAO5vQba7H7leq5FhR4QPHj9b508z69HnovAlK8F7fw3vvOFWQgWwqKFkEDJ9fmYsvq0NFSK/lYoGLBl%2B4wBiQaJRhoB6xNiALJfQ5xIjOBExDWat84aC2ILtagzl0TuWkCwTg0Y09hWTQCKw%2BV1UzD8a4B1DQIpJW%2Bogcq2w4imNswFYQ3R3DEgUOqMJ6qfV6H%2BGpX6xa0nGr0PemJ1xXKZPxzLXPSQQA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/all_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/all_deceive/implementation.hpp)
