<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldLeft`

## Description

`Varybivore::KindredFoldLeft` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>, ..., V<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;
   Operation&lt;
        &vellip;
   Operation&lt;
   Operation&lt;
       Initiator, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
        &vellip;
   &gt;::value, V<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldLeft ::   auto...
           -> auto...
           -> template<auto...> class...
           -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldLeft
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
= KindredFoldLeft<3, 4, 3>::Page<Args...>;

static_assert(Metafunction<1>::Rail<Subtract>::value == -9);
```

## Implementation

We will implement `KindredFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldLeft {};

// Base Case:

// Fold once.
template<auto Variable>
struct KindredFoldLeft<Variable>
{
    template<auto Initiator>
    struct ProtoPage
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

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct KindredFoldLeft<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
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
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<auto First, auto Second, auto...Others>
struct KindredFoldLeft<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            {
                KindredFoldLeft<Others...>
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
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSGgAcpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcBJgsqQa7JgDMbkxeRAB01wBqrXhMMfQKJ9gmGgCCE8ReDgDUAGlwuhiJh0AAxTzoEKYKgEP4mADsVkRABETlZPu8PgB6HF/CxMJR/M5KEDY7F4v6Q2joP4CLaXbG7faHTAnM4XVB/O7EB5PdnHN6fb6/eFAhggsE06Gwggc3n8%2BivCnI7F/DV/FkHJhHU7nIh/ACSDCyupIKs%2Bmr%2Bov%2BymIqCIyiYwHZVs1SMxH2t1u1bI5ft1gs5V2urz%2ByAMCgUfwA8ql4rrspbvT6Nbb4fbHagAEpMOjqtMItXuouauaOZARgQTTCqVLEP4G7kANzEXjdqbLGs9cYTxCTAg5JrNRDIPPuj2VQpAIDb3kwxfRxy9ZaRy69hbTgb1bh3web1yZQojUYUR4%2BwFBe0YBBeQq3Pq8mSMfzzdARx1RfyzRHftA5S9rzYQRzzDB8V0fdcMQpUstT2HVd0Pa4gMwG9QJTa1n3CYAfxdRcTm/X9UGdV1AKvNCQLvI8VUgrE0RgrFPipGUtQAdzwRlmQQ/19S5ak8GICZSCbfihEwNBJRTDNAWBUEIShGE4Q5cFBOEv5xMk9AU09R99w5ZtjVNRxzWITDywIH47QdJ18Kgksux9fTTmckNUBok9IyJGN40TRpzLTGTiP/R9rV0uCywrTjqwYWt60bQz5w7BEIqLXtQu7DVfIHfzTgyzLssHBgOXyzLNRHEyxxE1ShPlVLMteWckswETNIEbT6u7Rq53bTsyqXRjHLChi6I%2BUrXNc5Dj2wU9vIvCj0LvAKnxfXD/0/IibNzfMANOVDFrA6bBuGjdYMcyauXm4Db3vYVHOw19SIIr8fy2p7yOu0CPLeUboN%2B5j8RzCSNkyFtF1JdgzpYqF2M4lq/gQQx0HoLUEEXGhavY7lUlaVhMF2ITSEpfEkb%2BUFkBBxcHtwgg0bJzAJiZT4LsNGr1MMtrJREqbY1p%2BJbuxGSJSlBTaSU%2BVTjZghWok9qRN5tGhO%2B1VV01FnuQqh4x2WoK3rsuDwqGtWeKDAMTaQy7wJmrzoz7PzkwfTrdezELOsN/qoqrSS4obUTDWa0rhtV/qNWF%2BSZXFjkFf55XOrLWd9zwsi8rjsrCtytxA7T/sipK1OQ6M0cSGqtS6qNgvuuamWtKzhqZx6hda59brE5C0504du6C41Jreqbv7g%2BbkbN06ibzYPS3ptm6Mrsom7lqw1a3x2jbXpdnaPrnr6reOj1h7O31x4Myf9qogW4OppPns27N3r2haz%2BV3796Y3EACoP8/r/v5xSkv7%2BAAKgzO8fwv6/2Yt/SBYCzrmGOOESMXgsCfjcJJLYqQlqOzGszI%2BfFDQfG5vxKwmCZJCC8DESyTAHAq0fJ7GKPsEr8QDgbZEfwPgAFoLADWfqdV%2B6sLzEGAOfD4l8ACy%2BMmBUC8AwBw2QUpjRemHaUik5QcmOCJaQfxjjdTvm4D4AjDq0RHl8FolYAD63l4gEAgGIlokjpEZy4N1NubhSHkIHFQ%2BuzUNqET%2BGwgAnMsDEHBVi0E4AAVl4H4DgWhSCoE4JnSw1gbTrE2ARMwxweCkAIJoYJqwADWIAwmSEuBoSQXBETHA0GEjQZh/D%2BDMEkFIoSOCSF4CwRIGhSBRJiXEjgvAFAgE6dk6JwTSBwFgDARAIB1gEFSBccglA0D7DoPESIeNOCqCSP4Nh/hJB/GAMgKsUhLhmF4GCQgJA8DoD0PwQQIgxDsCkDIQQigVDqBGaQXQQQ2IDlSJwHgITwmRJybEzgsYLhzPhKgKgfxNnbN2fsw5fxjlmD%2BBADwyz6CNlgVwZYvBhlaFWBAJASzUgrLIBQCApLyUgGAFIMwfA6AEwGRAGIIKYjhFaAAT3%2BbwDlzBiBctjDEbQElhmZKWVRWMDBaA8o%2BVgGIXhgBnFoLQAZ3BeBYBYIYYA4h5WCTFXgMG6qYl1mBrsXl5BBD1BBbQPAMQByCo8FgEFlk8DtI1aQMGxAYgZEwKiPYOq7VGByasKgBhBE3DwJgNivkomZNucIUQ4gnmJteWoEFXz9A6pQNYaw%2Bh7UDMgKsVA6DsjqrYRMbSX5TCJMsGYHp3q%2BRYCLRAVYdhDXOAgK4aYfggihHCMMSooxCgZCyAIXtegijjoYAsEY1QeidqaJMdonhOh6A7TIgQ/Q2hzuHQuuYUw135CCIewYg7FgjvbSkrYEhAUcAiV0kFvTYVbJ2Xsg5RzimoogLgC52L0m4vxaG1YaMmBYASG20gBTJDHEuH444iJJClLMJIfwGgqn%2BD8foTgrTSDtIyZcQI/gkh%2BKSFwfwRSuBhIQ/4J9Hzen9MGVk0NYzJnEumRC%2BZlLqVYrWWwTgrQWAtkRGwpgs1XxcD8ZcLgJSzn4DHFcm5sh7kpukGmpQGaPm6AZT8pgfyNX3sfd03gvTwWzIuPSGFQmRNiYk7hKTMmSlooxWSrFCJ0lmDxSxkZRKSWoExfEBZVKAtudGDZ0TXkjBSZqIy2gzLKBso%2Bfy7llqUuCuFaKhwlrJW3mlbKkFCqlUqrVZarVQbtgxPwOTRwxqQVmophaz14RdjNJiXah13LnWVfxXyD1mTvW%2BqUAG7VRhg2gF83wCNCgo0xrjZaxNqnHnqdkOm95MSdPZpDbWqwlgC0xFbSWstNZOCVoINW1EO3rANtM02q5DN4DtvqEulwkpJ39slHupYo7ijZHe2kMdjQvsjsXVu5dAx/ubsaDu895R50bpXZDldwPqjXo2Le3FOGH3AoY5wJsxBhOifE1Fhz0nZMaDRX%2BscHmMneYJbk0gYGIOUHvXhgj0nSmIho4iCpkhUO7KCCZ0FfTbDMfp0S9jSAZmQuC7x1Z6yOBCYRSwBQLYqwtkc2yCY8n/1KaCIt5Ny3nnyE0%2BtnQIA1F6YMwCrHxnn1gq41C6zBPleq/V5roMEwXOhfJTT44dPWMcblxSxZPusVzmQKkVIpiNd%2BNMVrgg5iXfqaZfzRL7LOWCrS5noVIqxU5YC1KmVcqquYEVcqsQpXPXlbGz10g1XDV1Y%2BQ1i42xMktZtR8jrjquXdddX1y1g2/UjaDThVj4aXQzejbGhM8beAG4eRIFbLzTeZot1t4wea9sdcO7E47sVOA4irbmutFgbuxLuy2x7oPGivfcMevtwRPsXvhz9md/3p1A5f/ujdz2wcw8hz/2h2R2/2%2B1sERwfwR3mFAKvTWHR0eSMxxx6TxyVz2RVzVz%2BFj0uAT0pwUxIBpyAx80JVA0wHA1GCg2aTZxADMGk2OGODCWqTKQwzoMRBI3o2QJFwGSGRA2gxAEkDCXgzCSSFqT8UkD8QqUQy4DUWaWOCQNM04GA183vVOXYPkJF3F1WG9UyGcEkCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_left.test.hpp)
