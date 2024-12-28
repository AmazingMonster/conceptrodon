<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-left">To Index</a></p>

## Description

`Mouldivore::ClassicFoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::type, Arg<sub>1</sub>
   &gt;::type, Arg<sub>2</sub>
      &vellip;
   &gt;::type, Arg<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeft
 :: template<typename...> class...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
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
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction
= ClassicFoldLeft<Subtract>
::Mold<std::integral_constant<int, 1>>
::Mold<Args...>::type;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `ClassicFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldLeft
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements>
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Initiator, Element>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type;
        };

        // Recursive Case:

        // Fold twice, handle the first two parameters,
        // and recurse using the rest.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            = ProtoMold
            <
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Detail<Others...>::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIACcXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJM/jcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctzcBKyyAAYp50KFMFQCMCTAB2KxXW7C26w57wxEEFFotgPBjZd4kKlCkU0ukEW7KYioIgAWXZwJFt35gsuRqNYohCOhUtRzDYWIx2BejAICmVZvNwrV9IAIpgWnRjQL%2Bb6oabDV7bjsdrcLEwlAyE%2BxeSqvTHbmzaOhbgIthjI17LRKbdL7Zhbs6wa6PVHbj6Nf7A7REVXXjz/NhC%2BaTd2614skZRdLjf5fSSyRSBIj7vLHIqyJWXYIcSAQLbraa66Hw6nPenY1mcwQAO54fN9kXFyGlu3ozN4YgTUjDu%2ByoSYNAMdC1qMN25NkwdCIiyj7PrcH5fj%2BnaXsKvZpnWtwDhEwCvgiCHbmOIqkgkU4MIisGIRu5YTrhjQERhiFerOCpEIuoFPjylFUau67Si%2BkECD%2BzGIaxG67jxO7%2BBGPEZgASp%2BGxZAAbhWbjJiAe51hmR6imeWwvgghjoPQooIBWNCMWpqC3GkrToqCT6kIRGbabcxCSU%2BFbIUOBD6fZmATAWPHXtayJvhWDHgcR96cd%2BL4hQ6WLEm5CTujBPH/oBwHQkFBAcZ%2BXEvjF%2BlPo6v5evB%2B6IS5qH8TxRpQuOWo6qg%2BrZoRlXQo1UaRRWOHkuRzUVa1Zb3h1eEUcVVHUXOeALi%2BaUtYVnZrhuGVQdNPazWxqJLXxYLiqCAEBkBLbQjlcX5St/HCYRQkicNV6bVakp9VFGKXMADnVoI8VdjxpW3PVOZVTtzaIk9L3tgox3YHN0oCcVF1KddcI3v5MqYliQOYK9boFUhg6oT9o7VdqeoGtCqPo6D2IwWdVww1TPz/H8gK/HslaqKwzwVl8wKM3TZx7uY/gRPiXhYKOiMAPoEOShDvXujMQV4sQS0w9Ic1cvl3QFtyXBF90VlYCWXP%2BQjy4rDi8iGCFfRueP1gQ6BrhEoLPWIotfnMK4IYiDsvpca7SWIXgVgAtHGvv%2B9aXaU0CfJhpHnNHN9u1UF4DAODknw86rN0loj5aOpcxDANLVxfbqifJ6n05U1hjIJsyR6ctyiJGwr5Km/ra4/YiEx2yADuYE7tAuwIbsdm4Xu3FwVLtyAnfEwXZMFidkOx7TdwSQoXi0BqKuXF96%2Bbxqf2ly0Scp%2BRVduN23f24I/fkoPrstCu0Lj/4OLWQh1%2B97fA9DwwI%2Be0EC%2BSQ78r62xvo7e%2Bf8AEvyAbcN%2B%2Bsp6XVlgAFU8tvDOBsWiOGQKLWuCQCAQH3lvUO3gKxVT%2BoHJIyxwwcFWLQTgABWXgfgOBaFIKgTgl9LDWHrOsTY5CzD%2BB4KQAgmg6GrAANYgEYZIDEGgAAcZgzBJBSIwxRCiuB8j5NIBhHBJC8BYBIDQGhSCsPYZwjgvAFAgFMWIthdDSBwFgDARAIB1gEDSF4dKFAIBoCeHQBIUR0ScFUAowIgdAiSFuMAZAyAJ5yLMLwTA%2BA6J4DtqkfgggRBiHYFIGQghFAqHUA40guhUgnnJGkTgPB6FMJYeIjhnBiTeK8RqVAVBbhhIiVEmJcSEkYjMLcCAHgAn0GIMaIRXBli8HsVoVYEAkD%2BLSIEsgvjlmrJAMAKQZg%2BB0EsjYiAsRGmxAiK0JENTeCnOYMQJExJYjaE/PYkR/j2zEgYLQC5pSsCxC8MAeStBaA2O4LwLALBDDAHEN8x8Ty8CyWBewzAqhJKgkueQW%2Bej2G0DwLEcktyPBYEaRLPARiQWkFksQWImRMD%2BnBUYbFRhxGrCoAYQuAA1PAmATw4VYSIrJwhRDiHyfyopahGnlP0BClA1hrD6BxTYyAqxUBpEaMCwO3cqqmB4ZYMwFiKXEHSZ5eAqw7CwucBAVw0w/CpDCBEYYVRRipGKNkAQVq9DOsaAsEYiRxj1DNU0SY7RPCdD0KaiuAb5h2sWI62wga3XjEDV6h1PqTX8K2BIOpHBmFmMaZYrp4TInRNifEqQgzhm4EICQSZwiZmiKZasfSTAsCJAgFIkAkh/AYiSP4HRGhJBmEkIEExjDAhJH0JwAxpAjHCIxIELggQFFJE0YEWRXBGHduCOY3gljrG2LrQ4hZrjFnuNad48glANnjOCWwTgrQWDST5IHJgeIDBDi4EkDEXB5HJNSSQdJeh%2BU5KFdIEVSgxWlN0LsypTBqkgszdmrdTSOAtM8d43MnTumFpfRCieH6v0aGGaMlZ4zq1mFrXMxxx7L0JHPX41AYzRj4ghe%2BrgpiaBbzipQY5pTrnnLRbx259zHkODRa8107zPmNJ%2BX8gFQK0VgohVC9h%2BAHKp3hY0pFKLtgiL7pi3g2LcXnIJdsdhxLSUiIpVSpQtLFMoSZXwVlCgOVcp5WiwDgq8kgdkKKkp7DIOSsZVqqwlg5WxAVa2jhKqchqo1WOIL1hdXbv1Ya8LJq/XhpcN%2BeNIRvxJqWE6zILrcjBoKAVkoOQ8sxrDY0foUwSvWp6P62rgwo3etDXG%2Br7XI0VDa9MtYGx019b0Qh3NnB809OiUxt9eH5Hlt/RMvm0zZn1tII25tlBM2TunR%2BvtfJ13aP8P2wdkhUiIZ3bYPdFHD3wGPR4tptHqPEGvdsO9vSWAKGkvE6S76MRWgmD%2BytBqMkFIFbkiQXnClgd8zoAIpBoOwdqeOrNDTSmWJQ209DXS3sfa%2Bz9v7GoRn0eIwkat/hyP2ao0T1ZD2qfjJAJ9tIaRRbfaSKLfHotVBRL2Rxp8XGTlnNufxgXdyHlPNE/Rt5HyvnKcwL8/5Yg5NkoU/SkzoKYVqaNaUzTyBvHad4LpxpBm8VImM0Sg15neCWepTZ%2BldmD0OaYOyzl3K7RudkEBzzIOfPith6%2B4wMqQsGdS5F1VnAdjX3izqvVCQgdGsVY1jLFqsudZtbl1ryb3WFcaNlj1FX0/5YTzVjr%2BQGvVb6Im/PVXi8hoTd1%2B1%2BXU0DbyfBlHFixuc%2Bie9z7twWe/fhBMObgPq1Lf3fMhtmAm2jAi3orbIAVEYn8P4Rh6iTsmMX3yBdObUecF3XYlb0jJCMK7VovkJiFGSBSFwJRZhgh6P8K37dO/R8SKR0krfberHP%2BWKsClWRnCSCAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_left.test.hpp)
