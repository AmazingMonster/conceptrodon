<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldRight`

## Description

`Varybivore::FoldRight` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function right-folds the list using the operation and the initiator.
<pre><code>   V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;V<sub>0</sub>, ...
   Operation&lt;V<sub>n-1</sub>,
   Operation&lt;V<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
   ...&gt;::value</code></pre>

## Type Signature

```Haskell
FoldRight ::   auto...
            -> auto...
            -> template<auto...> class...
            -> auto
```

## Structure

```C++
template<auto...>
struct FoldRight
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

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

template<auto...Args>
using Metafunction 
= FoldRight<1, 3, 4>::Page<Args...>;

static_assert(Metafunction<3>::Rail<Subtract>::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldRight {};

// Base Case:

// Fold once.
template<auto Variable>
struct FoldRight<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            { Operation<Variable, Initiator>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct FoldRight<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value 
            { 
                Operation<First,
                Operation<Second,
                    Initiator
                >::value
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

// Write out the last two folds, handle the first two parameters,
// and recurse using the rest to obtain the initiator.
template<auto First, auto Second, auto...Others>
struct FoldRight<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            {
                Operation<First,
                Operation<Second,
                    FoldRight<Others...>
                    ::template Page<Initiator>
                    ::template Rail<Operation>
                    ::value
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCAAnGakAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxickKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHASYLCkGeyYAzG5MXkQAdDcAak14TNH0CqfYJhoAguPEXg4A1AAxTzoABKeGACAI/xM/is/gAIqcrF8Pp8APTo/4WJhKf7nJQgNFozFAkH/ATbK5ovYHI6YU7nS6of73YiPZ4Mk7vL4/P7Q4G0MEQqGMtkc%2BhvYlwtH/OX/WmHJjHM4XIj/ACSDEyypIUq%2B8v%2BfIBymIqCIyiYwAZBvlsJRn0NhsV9MZLuVXKZ1xub3%2ByAMCgU/wA8ik4sqsvrHU65cboabzahQUw6LKYzCZbb0/LxhHkH6BONMKoUsR/mqWQA3MReG3R7Ny%2B0hsPECMCMUPJ70Uia7WOXXEN4gEDV7yYDNIk4O7OwycOtMx90qtxLz0Vm7U7l%2BgMKDefYDETD7RgEV7chdOrwZIz/ZN0GEnBH/BNEO%2B0Rn7w/HwS7n3nqcXrOyLElmCr7Eqy7rjcn5HmwP5RoaV5hMAz5WuOpxPi%2BqCWtaH4HrBJ6/pu7wAaiiLAaiXykoK6AKgA7ngVI0uBrqqsyQJ4MQ4w9hW/xCN0AjoFGcZkkK4KQgQjKApx3F8QJDBCeeZHTvKq6MrxWo6kQg5KfWRoEL8JpmhaaGAZmenOixHpulZkHMhuvr%2BriQahuGdQMAh6YiVhb4Xoa9p%2BV5jSOPmaAMEWJZlrxo61jCoEznCcUWQ2cqua27lSTJBCkIFKVpW2HlnPxYXoDl8UpU6mn9tpuUNkOI41nWFVOvVMVNRVQGkcljbkV1tVqWcA1eqgDlbk5gZ7vh36np5MZITeb4PphxlJim75nDB01EVKXX%2Bb186gUNUFXJtcEzbpiHXihOHoY%2Bz4rTdeFfmd23/vO%2B0gRiWKgt0mwZJW44Euwn2kgA6uyewUpcCoIOOAbQgQdEsvwQoKD2CCGOg9Aw%2BONBcQjSP/CkTSsJgexcWVX3lgp/yHsgf3jvNKEELDtOYOMCosqg0SNGEOP/GEWkkNSXxHex0n4zx7HFYJUvelcwYs3EZ48t8Bn8qJwoSZlktySVPaK7DXGjarAWHbZa7sVVjw1RdObq0ZiaPaBZvdWBdLWYNFvqfZf7YNuznNm5kZ2zG3krb55U9SpKW5iFBbhXskXluxbW1XtMfNUH6Uh24Evcen6b5RlRXyaVhcpTR4mimchvKybFcNsOq6obhZzWwOs1Z4azcW7ea2MsXIeq93MbDmnUd1dy4%2BNY3/nTw1Y6N51md7XOn3ZkNYvy45O6Tc9hFd5dyH9/eGH3YmvkbVNL0N7tdofZRenbyN0E34fof/Ezre3ctTumdfA%2BP477vXXk/dEAAqKB0CYGwPRCSGB/wAAq7NTz/BgfAqisDsEYM%2BuYE4YR/ReCwA%2BNwYVtgpHOqbUW3s2Lqk%2BHLFkVhdIiSEF4HmrYHDSkznHRiCcIqlhTuqCeekmyOgALTYgnBRT4K9Povz3MQYAKs0TfwALJkyYFQLwDAegCCSufKuIpJJnC4D2E4PZJD1UehtJRr0SIHTVnmAA%2Bs5OIBAIAaMaNo3RJc3AnHqlfNwbCOFMC4QvNqS1z7iK4CsZEHA1i0E4AAVl4H4DgWhSCoE4G4aw1gjQbC2OhMwJweCkAIJoBJawADWIBkmSCuBoSQHQTgaGSRoMwAA2TpZgAAcvT9CcEkLwFgEgNAaFIOkzJ2SOC8AUCACZFSMkJNIHAWAMBEAgA2AQFIlxyCUDQAcOgcQIik04KoXpnTxGdMkP8YAyB8xSCuGYXgmB8DaTwOgPQ/BBAiDEOwKQMhBCKBUOoZZpBdBmLoq2FInAeCJJSWkypWTODBkuLs6EqAqD/AuVcm5dyHn/CeWYf4EAPBHPoGWfBsTeBLK0GsCASBDkpGOWQCgEBmWspAMAKQyQaC0HJvMiA0RkXRDCE0AAnnC3gYrmDEAlcGaI2huhLLKYcs6wYGC0CleCrA0QvDAHOLQWg8zuC8CwCwQwwBxC6s4iqvAANTWZOLL9PY0ryCCBqMi2geBoitnlR4LAyKDJ4FGWa0gANiDRHSJgBE%2BwrU%2BqMJUtYVADDKNuHgTAdFXLpLKT84QohxCAvzSCtQyLIX6CtSgPJlh9C%2BvmZANYqBKFZFNeI8YikESmEsNYMw0zI3siwA2iAawuh6L8BAVwUx2hBAUoMMoFQ9BpAyO5adS7CjuXncMeIZix3uT6JMTwbQ9B7t6HMLdSwd2zH6Gu3d56FgLpGLE9YmxtgSARRwVJkzkUzJxZc65tz7mPIaSSiAuBCAkBhCUml5Tk1rFhkwLA8QR2kFqZIE4VwEgnH8JIJpZhJCdPGckzpCRBkcGGaQUZpSridK4J03pCRel0fqVwZJWHOnfvBTMuZCzYPLIZRsxlWz0V7PZZyylpy2CcCaCwSs/hxFMADjeLgCQrhcEaa895JBPnfNkH8ot0gS1KDLeC3QyRoVMFhWaj9X6pm8BmWinZ0MsXlmILJ%2BTimnLKdU%2BpjQpLyUsspVBk4ZgVi0uTasplqAKVxH2Ry6LgWRgybk%2BIrzPKEhcAmfywVlARXgtlZK91BX5WKuVQ4d16qTyau1civVBqjUmvdRahNOxMn4Dpo4R1yKXX0zdeGsIewkngp9X6yVgbWu0vZGGspkbo1KDjZaowibQD8b4GmhQGas05vdfm/TALDOyFLWCzJZnK1Ju7VYWtI3h1NpbYWTg7aCCdou72/tcRB3s3gKOmo9rnCToUre2d6AL2LrMcuoo2Qj3TAKCurIIOn3VFqGem9UOZ2nvqPe0o26T1zEB7mZo8Od2jsKW%2B59Q3bM/s4K59zCmlMoRU2pxppLwPaWCzBulVTSAIaQ5QD9FGqOqaaf4Nj/h/AnEkPhm5Zi7MotmbYXjHOBPwCE9sjFcXxMnLORwGT%2BKWAKErPmSsDP6TjE0xBwdunfmFv20C%2BQxnjs6BABYizVn4VkYp1x1FInMXYp17cvXBv/hG9Uyb6EZKEusuCycMLfH6WRZQBHyl6vE8jANykFIzjg/OND64tzNy%2BB0By8K0V4r5VFdLwqpVKqKvRY1VqnVbXMD6sNWIRr4bmtLYm6Qdr9quvgp65cHYZSBteuG76/1ErxvBqm%2B62bMaFsJuQhF1NVoNuZuzWGXNvBdvW4kAd4F9vy1O7O8YGtNhrtfayXd8KnB0QdurT2ywfb7MDs%2BZ9xtiPfsTqnajvQIQH3Y5g4bpZCA7g6boAGXono/bjoHotC/67rQH7qY6LCg7XqHq5Bo7IGPpE4vpFLvru5Iqe4cDU66766G7G4egcxgZaZUrQYx6K7waYCIYjAoZDb84gBmCqYnAnDJLtLNLjLcH%2BD0acbTKcA8aLJwaoYgCSDJKYbJK9JdIJCSAJBi7YZcAWJDYnCEGiFy4MFkYvIiH2ZiGx6c6RoZDOCSBAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_right.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/fold_right.test.hpp)
