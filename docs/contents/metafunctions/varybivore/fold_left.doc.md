<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldLeft`

## Description

`Varybivore::FoldLeft` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.
<pre><code>   V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeft ::   auto...
           -> auto...
           -> template<auto...> class...
           -> auto
```

## Structure

```C++
template<auto...>
struct FoldLeft
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<template<auto...> class...>
        static constexpr auto Rail_v
        {RESULT};
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<auto...Args>
using Metafunction 
= FoldLeft<3, 4, 3>::Page<Args...>;

static_assert(Metafunction<1>::Rail<Subtract>::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldLeft {};

// Base Case:

// Fold once.
template<auto Variable>
struct FoldLeft<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            { Operation<Initiator, Variable>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct FoldLeft<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value 
            { 
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<auto First, auto Second, auto...Others>
struct FoldLeft<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            {
                FoldLeft<Others...>
                ::template Page<
                    Operation<
                    Operation<
                        Initiator, First
                    >::value, Second
                    >::value
                >::template Rail<Operation>
                ::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSGgAcpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcBJgsqQa7JgDMbkxeRAB01wBqrXhMMfQKJ9gmGgCCE8ReDgDUADFPOgQpgqAQ/iYAOxWKEAEROVk%2B7w%2BAHpUX8LEwlH8zkoQCiUejAcC/gItpcUbt9odMCczhdUH87sQHk86cc3p9vr8IUDaCCwQR6Sy2fRXoSYSi/jK/tSDkwjqdzkQ/gBJBhZRUkCWfWV/Hn/ZTEVBEZRMYB0vWy6FIj76/Xy2n0p2KjkMq7XV5/ZAGBQKP4AeVS8UV2V19odMsNELhmBadGlUchUutydlc0cyB9AgmmFUqWIfxVTIAbmIvFbI%2BmZbagyHiGGBPSNVqiGRmfdHuLOSAQOXvJgUwjjnb09CR3ak1HXUq3LP3SXrpTOT6/Qplx9gMRMHtGAQXpzpw6vJkjH8AEpMOiQ45wv5xhO0elbnd7wQbr1H0fHieIwlpnKewKnOS7XK%2Bu5sB%2BEb6qe4TAH85qWre97GqaqBIe6EHvgey4Sj%2ByLwv%2ByKfMS/LoHKADueAUlSwHOsqjKAngxATKQxZMUImBoAw6ARjGJICqC4L0gCLFsX8XE8XxR6EWOsoLvSJbqpqjjasQMEZgQPxGiaZoWlW%2Bq2sejr0W6LpmaBjJ4auvrYgGwaho0mlRgJj7Xs%2BgFGam1Y1pmNE5gweYFkWykDpWkJecmdYmTWMqOY2zmnLFcUJU2DD0ilcWyq2antuxYmscKUVxa8fbhZg7FSQIfElTWZX9hWhnZX%2BBG%2Bd5k4Ae1CmWe6imMZ6K7YGu9mbtukH7oeXLdTKcHnleN4nPe7mJqc2FQbhX5vG1HXER8x79R6qBjW%2BG1Tcec0IZhKGIXpGEGS%2B404Z%2BQ17a1U6kRiF7cRsmSlkOeLsF1ZGkgQ1FbOxCCGOg9ByggQ40EVVFMqkrSsPG8QKKQRIYtDfw7sgv1DpdcNDjuEyUp8h3KYVEnKdVvHsWBlyBgQ8Osfx2m8oJgoiactMEFV3E1exrPsy9EbGYB1NMblDzti5Bpc7p6GYb%2BPnpodMuDd6dn%2BvWTnhrJM1Kzpsbxh5WVSyb%2Br%2BdmPHBYWHGqhVWXefJ2WyuRwnCqcYuYzZ02e/qfYLohD3JXVntpUlbhu9lMdG3HUfBzKcvqQV4nFTbLW9o1g5C9J8elXnrsp1GDVhwtz5%2Bw26WK575VNcXw57eORFtVlWu9Up1lbSN/onRN0HG%2BmJPVzdK012462TYHbc2h3H2%2Bdrx3gU9Z2KyT11LbdqsRzPG9z1tb1L8DABUl9X9fqJElfAAq2BCPfV%2B36R18f%2Bfb/7ciZjHOEvovBYFvG4HiWxUgHkllTHuA0mQfCZkxKwxsBJCC8DEbSTAHCSg9krMM9tcy7BCs7MszdAJ1g%2BAAWgsK3TuZ8SIfFXpuYgwBzqfBJgAWQtlQLwDAHDZEivtO8PMfb0mOOxaQfxjgNTVmtZhEtvzLztgAfXsvEAgEBOEtG4bw2OXAGrV3pKg9BjYsGlyaihXeFCACcyxEQcFWLQTgABWXgfgOBaFIKgTgcdLDWANOsTYQ5zDHB4KQAgmh7GrAANYgCcZIS4GhJBcChMcDQTiNBmH8P4MwSQUiOI4JIXgLBEgaFIG4jxXiOC8AUCAUp4T3H2NIHAWAMBEAgHWAQVIFxyCUDQPsOg8RIjo04KoJI/gKH%2BEkH8YAyBsxSEuGYXgmB8DtjwOgPQ/BBAiDEOwKQMhBCKBUOoBppBdBBEoo2VInAeAOOca4iJnjOCBguF0iEqAqB/FGeMyZ0zZl/HmWYP4EAPD9PoEWYJXBli8HqVoVYEAkB9NSAMsgFAICIuRSAYAUgzB8DoLsVilAYgPJiOEVoABPa5vASXMGIGSwMMRtDcXqaEvpG1AwMFoBSk5WAYheGAGcWgtAancF4FgFghhgDiG5SxJleB/rCo8fmH6uxKXkEEPUB5tA8AxEbLSjwWAHnaTwMUkVpB/rEBiBkTAcZxVGC1UYCJqwqAGBYTcPAmBKKOTcaEzZwhRDiD2b6w5agHlnP0BKlA1hrD6G1TUyAqxUAQOyMKihEwZJwlML4ywZgKnmtZFgONEBVh2Flc4CArhph%2BCCKEcIwxKijEKBkLIAhK16CKM2hgCwRjVB6KWpokx2ieE6HoEtfCBD9DaF2%2BtPa5hTCHfkIIs7Bi1sWA24tAStgSFuRwFxZSHmVM%2BWMiZUyZlzPiYCiAuBCAkEhH/SF0LHWrHhkwLACQi2kBiZIY4lwrHHChJIRJZhJD%2BA0Gk/wVj9CcEKaQYpITLiBH8EkKxSQuD%2BDiVwJxv7/B7pOZU6ptSwmOqaa0%2BF7SXndNReisFQy2CcFaCwUsUIKFMBGueLgVjLhcASUslZJA1kbNkNsgN0gg1KBDSc3QOKLlMCuSK7du7ym8Eqc8zpFwyQfPo4x5jrGELsc4wkoFIKkVgtvccMwULCMNLhQi1AoL4g9LRbZ4zoxNNMbskYdjNRcW0HxTUiARKTnUvJaqoLtL6WMocKq1l%2B52WcoeTyvlAqhWqrFRKqVHj8AE0cPKh5SrCYqtNeEXY%2BSPFap1eS/V2wPFGpNaE81lqlA2rS/BIjzqLQKDdR6r1qrfVCd2SJ2QwbjkeMk%2BGh1marCWBjTEQtCak25k4Kmgg6aJvWBzUpvNazMCzd7WOvw5beKturbxKdSxG3FGyEdtITbGinYbbtxoE7B15CrQ9voA67szoHVdpdn2t1rA2JuyFkGd33Nw5wYsxAGNMZY%2B53THGuMaCBVe9spn72WdhU%2BzAL7RjvvydB2DHHElQkw1CFJkggOTKCIpx5VTbAEZhY05pbSOmvIc1RwZwyOD0Z%2BSwBQpZsylj07SCYPHr35oE1s/1/X9nyDE8NnQIAxHSdkzckHCn91PPI28jTUPef88F8Lt0ExDNOeRaZ44FnGfWZQGbsF7O7ejAF6kVISihdWKUSLggKi9cibxZjQlxLSW0pC8HulDKmVRds2yjlXKMuYF5fysQyXTWpbtVV0VMq%2BE5ZOXli42xQlFY1ScsruqyWVcNayWrvB6tWqa3alrVm%2BAuo6%2B6z1IZvW8F69LiQA2Dny9DUrsbxgo1TbKztxNjRhWojTZGrNFh1ueM2wW%2BAxb6h9pcId%2Bdr2a3lG7W2m7l3t8H4u6UFd%2B/F3r7209n7V/HsffP9Okd33j%2BLof3vp/wOFAbt2fJsHFSIcecpk%2BcBc/h3dLgvdkdeNwU70rdH1SBn1X1KBt0CcQAzAONjhjgnF0kklQNMCoREMcMAC6cak6l4DP0nEf0nEkhMkrFJArEUk/0uAxF8ljh/8lNOAH0rNt1FkiCOC6drdVhzVMhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_left.hpp)
- [unit test](../../../../tests/unit/varybivore/fold_left.test.hpp)
