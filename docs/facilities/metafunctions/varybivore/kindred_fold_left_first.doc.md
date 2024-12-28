<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-fold-left-first">To Index</a></p>

## Description

`Varybivore::KindredFoldLeftFirst` accepts a list of variables and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first variable as the initiator.

<pre><code>   Init, V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
      &vellip;
   &gt;::value, V<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldLeftFirst
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldLeftFirst
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<template<auto...> class>
    static constexpr auto Rail_v 
    {RESULT};
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction */
template<template<auto...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

/**** Test ****/
static_assert(Metafunction<Subtract>::value == -9);
```

## Implementation

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct KindredFoldLeftFirst<Initiator, Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            KindredFoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgABwAnKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3EwvEQAHRIgBqrTwTBi9AU0OwwImxC8DluAGlwuhiJh0AAxTzoEKYKgEKl4YgTW4mADsVg5ABFoVYrsCdjtbhYmEpbrClCBgUKRTTaOhbgItgjgaDwe9MNDYfDUA8GNl3iRSLc4URbqjiOjMdqobirvjCQQSWSKdTafTGczWQQdfdDY5jWRLWiMfQcbKucDbrHbhrnlqdQmIXbdYikTjbsgDAoFLcAPJpeLvHKRq5x25OonKYioIgAJSYdBjcc5Asulcrc0cyGzAgmmFUaWIZr1twAbmIvJh2RWu7H24Xi8RSwJ/YH0UQQ1abRH7SAQFPvLPOXyoR3K2f%2BbL57GU0mYQ/ITDzagkWr7dncwoP5dgBSYKMAQ2L2q2sZeFkRi3E2dDslCPK3LW9aoLBtA6v%2BgGvCBH6RheUbnh2cq3AqSoEAA7ngqrqmCiYvum%2BoBka26mm%2BJEshMrHjkImBoAw6Dlpc1YuqS/HuqRXpMhxfowkxQYsexvqmjxfECWBgrRne8a0amyY6Y%2BDG4V%2BObivmRYlo0gndgQBI1nWjbNuhWntuBXY9lR/YMIOw6jmxx4zuymmdguXbmaulkwq5IXLhZZaRVp0WVnJW4mopExRSFOKHv5mDKbxAgCQlmUHke07akVi68jezlVfhgpac%2BaaNTqb5Gdg36mX%2BAGYEBgigQ6wUQVBwAwY58GIchDktjCmE9dhv6ZmBdVArVRE/CKDa8RsWQTrOUrsLe1zyrS8aUVspoIIY6D0PGCCzjQvq3YBtxpK0rCYKCrKkMRV23BSyDbbOkHhCNBB3X9mATGqVzNa%2B47JcGXEWj6nFjhaKkFUj75IgWYPxP1eI2c6rpiZSEkMlJvobsxqUowQeWqaauN3aybVRpecaw24XOtYt7UmXmMXhXFA3WbZLqTahjmuS5FVVi0vaed5I5o/qOWBRziUk%2BSZOehTdM6hlWthWuDCG3L0UmxFbhG1rcYIwpBsW8V2DZWVDMFbb0VZaVJ5M3jrOZs7i4lY1o3TW4Vsi17cZuyetvXstV6rYdlZczzeptR1eZdVhwEE1pwPQWh41IfZUsR7NvU4Xz1UrYRh2/P8xyAk3tzYKorDPLOXxCs3AKN0ctxCF4MQ2UwRK9zD%2Bn0WxlxY6KgnCcPo/jw47Oue5fZ8crvnjjlMtcrclwALQWIFDcaZfQI/EPACyH1MFQXgMA4OSfIC6cz2mvOfvzP5/mIMAAulwi4jQfi0Z%2Br8PiygQtrcSetvTSR1FwU0UJTTSFuFCH2aEMJAIWn/Oufc7gABVIYuinkJBWVEAD6pl4gEAgBAp%2BL837rhhCPMeq514lXVtCc8iET7JGWPyDgqxaCcH8LwPwHAtCkFQJwG2lhrBVnWJsU8ZgoQ8FIAQTQYjVgAGsAiSARBoRIZgzDJGSFwfwZjEhcA5ByaQEiOCSF4CwCQGgNCkBkXIhRHBeAKBAN43RsixGkDgLAGAiAQDrAIGkeE5BKBoCeHQeIkR3qcFUIkAAbCfHJkhbjAGQH2KQCIzC8EpIQEgeB0B6H4IIEQYh2BSBkIIRQKh1BhNILoVB5FVxpE4DwcRkjpF6PkZwAs8IEkulQFQW42S8kFKKSU24ZSzC3AgB4VJ9BRzmC0csXgoStCrAgEgFJaQ0lkAoBAC5VyQDACkEEGgtBPpBIgDEcZMRwitAAJ5DN4N85gxBfkFhiNoXioTtEpOwgWBgtB/ndKwDELwwBYS0FoEE7gvAsAsEMMAcQSKWSQrwLtLFcihxbVBAC8ggh6jjNoHgGIq4QUeCwOMmyeAPHYtILtYgMRMiYB5GCfFjKjB6NWFQAwwDkR4EwORcyMjtENOEKIcQrSVUdLUOM3p%2Bh8UoGsNYfQTKgmQFWKgNIjQsUnwmGpHkphlGWDMH4vl1osCmogKsOwJLnAQFcNMPwqDQjhGGFUUYqDijZAEAGvQkbGgLBGAkVB3q2FNEmO0TwnQ9ApsaP0NoCaw1JtsOmmNyb00FqWFwL1aitgSBGRwKRPjxn%2BIWbk/JhTimlJMRsiAuBql7M0VWo5ErVh3SYFgBInrSBGMkFCBEyQoROI0JIMwkgcleP8Dk1ILi3GkA8VohEOSuA5JSPYnJ/hJA2IXTkpt3T/GBOCToiVETolnNidMxJNy7m7IyWwTgrQWATg5CfJgHVoJcGSAiLgpjKn4G3LU%2BpsgmnqukJqpQ2rum6CCP0pggzsX1sbb43g/ipnxPhMqeZiz21gZGhBqDpjNnbMubs9kmizCHKfWE055zUA7PiEk25vHmOjBMkYCDXBvEvLeZQT53SgV/JpfJkFYKIUOBpTC4CcKEXjORai9FmKaW4tFdsOR%2BB/qODJeMylANqU8vCKCFxcjGXMr%2BWykzRzrTcu0XygVShhV4qMGK0AXG%2BDSoULK%2BViqaUquQy01DsgtVdLkVhvV4qHVWEsMamIHrzWWpyNa21/D0vWGdcR11tTIbwC9fUH1fg/X8VLcEfiFbw3pEyFG3ImaCgRva/GkNixWs5r6CWrrgaei1bzYMfribs0jfyGNuY%2BbpuFrrWsDYtaq36FGbevxnBW1LMKaJ2jkHoMaE2X27crGDnDq46OzA47RhTp3e4kAUJIPLo5P4ZIjioQrrXZenbxHOAPpCc%2ByJMS4kzIE9%2B9JmSOAAeWSwBQE4%2BwTjo6mCYsH%2B0IdQTFtVcW2nyHQ0lnQr3SA4bw8MrbDaxl3smR%2B2ZlHEfI9R%2BjrUbItlCauVdqEHHjnhLfTD65ySue7KPMgNIaQaFo%2BSDQjHBAaGqAKXwOg0mPlfJ%2BSCxTmvQXgshep3jsL4WItM5gFFaKxAGZ5UZwL7nSBmZJZZ7p1n4TbG0fZ%2Bl3TnMst%2BW5jlnmaU%2BcFf50VINn1SqYDKuVCrixKt4Hj5pEh4vtOJzqsnBg0uGsy85nL8i8sDk4DsW1BrHUWFK/I8r7qqvjdTS4Bro29DBoqDNnrJQciNbjTkFrRahsCEm413vab5jLcrcWgYA/y0j/DdW9bLSCO092xwBZzOUeTjZ6CDnF2SBXaHZxk5d2HuTvrbujxliERQihP4Wxl6vEX45CewHEyAm2Effz5YhiQCSH8POhxHIvGJEkGsS4HMTMBvRcShAXyB2fzf3rQqUf3vT330V5XxhyE/yAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/kindred_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/kindred_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_left_first.test.hpp)
