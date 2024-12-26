<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-left-interview">To Index</a></p>

## Description

`Typelivore::SensibleLeftInterview` accepts a list of elements.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview
 :: typename...
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
/**** Metafunction ****/
template<typename...Args>
using Metafunction = SensibleLeftInterview<int, int*, int**, int**>
::Road<std::is_same>::Mold<Args...>;

/**** Tests ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEmb%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwOSEWQ3iwtxM/jcBAAns8APoEYhMQgKGHYEHmfzgyGYaGw5ATdBYKhYnG/AE0wEgv57W4ASRYqXobEETEaX0OQIZtIBQJBBEwrIMIphcMRjFYmAAdArKVcJsQvA5bkJGJlYvRQpgqAQmYIEgA3d4AdxxAHYrFdbvbbiKxVzMJKnWyXW7pcw2Aq5VjbhCmAoFH7lMRMPhRCLMf5sXaHSq1QRbuHUEQAEqoJjoEEO6E2vP5h3u8Wu2EI54%2B%2BWKuNF4u3JPqtNEACynlzCYbJhtjZajmQgYEE0wqlSxD76BAIBYTAA1pgkZlgJF0CjJZkAF6LggBk1iLyEnsWAC0XB79xhFgLl/8tuBXeLpc9Fe9sr9l2AEdFjAIsfjlwNvaXiZEYtztrQ6BEvcqbEOmqAQbmsKft%2BHJ/n6lJ3vWN5XlSgElqKHoShWhFll6VbvrW2CBgYIZhhGUYuv%2B2EgREwC3FmObQbB8GcUhbjhpGeDRh8GF1lhVwXrhklXM%2BxFShRbC3AAYngxATEqlxNimmoMNqur6oaxrEGamCWrCqnqbudaSYWj5yeWcKkS%2BCkyr6VE0cGoYKoJjExpp%2BbaTxmbZp2%2BH2se2H5g55FuTWcp6gaQh4FgzGPoFqLJsFCEdlFDrHvl6VAXMA5DnpIpjhOTBeEQtz7t4R5Fd2dnhUB3aBFYgT3BAyy3CeAaktOs4LkueArpG66wluO4BW1QGRU1c35ngVBlSOlXQotS32lAGFmAAbOY%2B2%2BcJTGSolwgpaJCqkCpakaXG071YeyzLHl235b2EYEBsDC3BoV44TJrUffm9RKO9oMFd9v19eed5AyD20Xj1kP5lJElIxFVq3vekMxa%2BinxShmA/oIaVY7crFgYh3EtjlkGSiTZPoVR0mtRjeP2c58kE651ZidRQZ0QqzNoRT%2BbU%2BxfF03BIU5kzX6k%2BLgvs5zeF85WcV3VZt1a9WGqYGgDDoHrb7uXKADyBAIAkFNBbp%2BmYBdRoiiZFqSpZEy3Zqxum7c1u2%2Bpqu2fe0U845mvm/FAbC95conSJEuJplzZy6gfHYQtlNR0TfoXclqWzQ2QX04hkMFRFW0p1ywlrRV463NVtXPY1lPoy1oP5R1JhdT1fUDQQU4zvOi7Lquk1uNNk0AV32Nh3Py2rcb62N2j227YqB1HYnZ2wgXV3x7dXvWdgT0Hpgr3r0t0OYD9xB/QDCNScDi9g7QSi3Ct9ejmv1dLZvf028Dq738vvQyhdrpyh9kbAQSEz4gFblff%2Bc1b73z%2BvDa8L8Hzt22uDQk38V4N2INfOaEBSEfUdngHUztDKu1NB7WEgc7Yh1wV3acDkOKhUlKAqBxc375g4RHcCuVwFJUPqwgRDZz4NVuGAMAMIYJngoUBN6KC2oFRUUtGGD9bhmGhJYQ2elqEGQNPQ92ZlJTMODmzdR20hHOhFFwhWsJeHx34VI24DiiKEnLmIy6qVJGeIdDIw8gMtHFmwRE9%2BEM7HNWvDov6yjn44wiSjNRbCcKYw0akzG%2BMI6xQFqLJWLNk4NiliIyCst4J%2BLcGLX87jxIL2xrjPC4dHGRwKYTOKgtPIizlPU8m/CKky0UdlTOyESkqzZnk3JXNrgCjpNSO42BVCsDZISb49JFlbOBgycCd8mBUC8AwBw2QeQHCBLnHpotiDAAphU1shzjmnO5GMqhNCXbGVMuZNwEQCC3X%2BXsQFggDggoIAcTS04JlTyHtOPACglyyixNOWplw7mNOxHk5ZBxbgABUPh/guWcEEJVhJIi8gkXcVwIBPJaC8s5AhJRAr2CixBF9oJjLMG9TGZLkAUpDFSkEtLnknMZQwSUJpUApTZa3Tl/glFcB5RYDgqxaCcECLwPwHAtCkFQJwNw1hrCNnWJsI8yQeCkAIJoVVqw5wgECJIOUGgAAcZgzAAE4PVcECK6l1XArRWmkOqjgkheAsAkBoDQpBtW6v1RwXgCgQDRutTq1VpA4CwBgIgEA6wCCpBquQSgaBWR0ASFEWUnBVAuv2iefakhbjAGQIOKQcozC8CEkQYgKU9D8EECIMQ7ApAyEEIoFQ6g02kF0FwUg5o0SpE4DwNVGqtU2r1ZwS2NUC0plQKtattb62NubbcVt%2BiIAeFLfQCcuIlW8FTVoVYEAkAltSGWsgFAIAvrfSAYAUgzB8DoG7JNEBYhrtiBEVo8JF28HA8wYg8JLaxG0EbVNlqS1oUtgwWgUHJ1YFiF4YAbgxAf2g6QLAs4jDiFw2pFDeATQfDXaOI2NVtiWv%2BfUNdtBqFongx4LAa7UR4AjdwXg9HiCxAyJgR4FHgBcaMDa1YVADD3IAGoWktlWUjfbhCiHEMO7TY61BrunfoQwxgjWWH0NQpNkBVioFSI0JNHATykkUaYSw1gzBxrE921K8BVh2Fo84CArhph%2BBnWECIwxKijBnUULIAgwt6Hi40BYIxqg9CC00SY7RPCdD0IF8V/Q2hpZixluYUw8v5BnRVwYUXFixYC6arYEhl0cE1TGtd8bbj7rrQ2ptLanVntwIQEgBj/C3qtQp1YtscyjB6qQe1kh/Byg9f4INGhJBmEkPtKNgR9oev0JwMNpAI0TblPtLg%2B0XUev9ftR1Pq1v7U65O%2BNibk1TbTY%2B7NT7c1bsLR%2Br9V6K1sE4K0FgJorQniYJ5MCXAPVyi4M6jt%2BAu09pndpgdenpAGaUEZyduh/1zqYAukTbWOuxt4PGzd%2Baaq3F3T1mtfXYfsXh4j51txz2oEvQkcb3K70KYzc%2B7nr6r1Fs/SL79QYjDw64NGmgtAgOUFA5O2DkHSNq/g4h5DDhSPod/Jh7Da68MEaI7QEjImyOijM1R3V%2BAIxnPo053VTHkAsdI%2BxkNuquOxB4/CPj2xdWCeE5asTEmlDSZt2xQXSmmCqfU5py3mPdNDpx7IQzE7dWE9M/J9zVhLM%2B5swt%2BzjnOAuaHm5izFgvNU584ffzmXxUuBNkliLJtStLDixkBLOQqvhbSN31L9X0sFfqFl4ruW8j98K40CfHfYu2By63xf8xh9lda2sDYLWlVHfa6u17nBGcHobdL1nCOkcaE5yNrt43Jv3ttaQWbWBEgLZDSds7CPNtWkCB6wN/gts7aSAzqU7roJq2Afb37fbwC/Z5rbri5A7lqVocDg6HosAKAmiDgmhs5lgTAo6ja%2Ba9qyBY6p4jryB46Z46ABCzrzrQbk775xobr/Y7p7qoHoGYHYFMQphc487XrJD%2BDLAC5fZC4oCS5i6A6iGjAYGpCpBIhYEepIg4EEBIiqD1oAaK52zK5gYQbwYa7aEIZIYoZ67c4YZYY4Z26YD4aEbEZOaWrkY26B68D260ZO6MaqDMYige7Ghe68A%2B5%2B4B4Cbdoh6iYJDh5SbW6UbR5CGx7x5mQaaMBaZEEp4SBp6jrkHGZUEGC55V5WaxBF52YObZBOY7CDR56ebeYJC%2BYMa2aN6NDN7uB956CRblAj5d7FDZDL4pbZDz7lZj5FZL4NE1a9Gz45bdEFb9FT5jGr7NHr474KDNZDp0EvYMEcA9asEYF1QcExhcHX5jY3oCGfYPozaYBzYv5tbv4gCepyj%2BBBC%2BpAFRrXFWjXZLFU6cDvYprTaLYgCSCBCrYBpWhRouqSDepcBuoHS77%2BD0EvFgGQFtbtrPGgGCGHGkBiaZDOCSBAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/sensible_left_interview.test.hpp)
