<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-find">To Index</a></p>

## Description

`Varybivore::KindredFind` accepts a list of variables and returns a function.
When invoked by predicates, the function returns the index of the first variable that satisfies all predicates, or `-1` if it cannot find the variable.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> (...&&Preds&lt;V<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;V<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;V<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredFind
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredFind
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class...>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 3`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** IsMinusOne ****/
template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = KindredFind<0, 1, 2, 3>
::Rail<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

We will implement `KindredFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct KindredFind
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    { static constexpr auto value {-1}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First>
struct KindredFind<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxBIaAOykAA6oCoRODB7evgHSaRmOAqHhUSyx8VxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlkTFxCckKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzGFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSmF4iAA6BXUy7jYheBw3ADSYXQxEw6AAYtrcYkrJcbuabmKJTzMCSrRybdLZagFXLsTdIUwFApXcpdfhRGKsaCcWaLSq1QQbn7UEQAEoY2jAi0wk03WaOZAegTjTCqFLEdMEdAgEAsJgAa0wyIywHC6FRJIyAC9qwR3QA3MReTCpiwAWi4JkSd1hFlTo9BpqBYfN9sltrh88dcJl8sVIY9Bm9rouwF14sYBGDoYuKa8GSMNwTdBhoLu0eIsdQN6TcL3B65x9d1Knxsn06iuKDpSquzo3IaxDjEqFwRuqWoMDqeqGohJKQdBIbGtOKbLqB8LAQuTrrm6m6ejuCp%2BnqeCBu8MEpnBUYxvGibJhaw7juarEpuaGbUdmDC5vmhZrqgNxdt4vZcdx7FSdxbH%2BFY/h3BASw3P27rkqW5ZVjWeB1nqjZwi2bZ0XJ0kmrJZkpngVD8YJBY3FAP5mAAbOYLmUQGNrBm46HtiGpbiT2SxLJZVmcWmuoEOsDA3BoY4TjSZ7hXJdRKGF4XsTcUUxWpQ5Tols6ZSOKkZcOAFSeVY5JThBErvh1p4SJP6kduPoKh%2BmCHoIJ5SReYTANeiZ3g%2BTEvix777l1X7tSROJ/pcVULTOFy4YubgiRBeBQQQpA3JtQiYGgiF7c1CoAPIEAgcS9cqaKRpq2r%2Bih6Bodt4x7Ydx3oHtl3XVBLWnjJRVrXadVNc6gNbl6s2edR3mmTx93qmNr6VWmnFFfRzSZnZYpCft4FBZJWNsRZpNySYClU8pqnqZumllpW1a1vWhluMZhmnilEXYTz1m2cd9nEBlVlOYqrnuXDNE%2BX52KBd2mAhaLZlZTlxCxfFBVVYtFPhWlvY2XjeYFircni26kuudLCNwl9AivQFIDE8retWWrmDRRrNz5eOOsrfzKYGzcRtC/jptu2ZEBm%2BFCFIQaRpwn9N2AzHVmlmtj7PmjcI20GqeRylCsSTcYBgLCD6DmnFqhYX5l%2B3XVnq7FZgwpYj2Ic9iduMnAMbtzgdyRn4O9qjE1uHn7wF8lg8psXPYJdXEWjrrM%2BBwbS99tlnu5VX2sjjH5WlXrS188v1Wr7VjXraDYHEe6ZGzZ13XHojNz9Ver4jVnzF0CSz8zVTstU%2BSVBRCgFIcG42BVCsA5L2L4jIhQMlXkyVkCgAAqAB3USCDLi3w2uBFkMEGJoKwagYEIAbgpC8NEWgfFGbRFQJ4ZEYdDD%2BTcCyEaFcbhmHdDJA%2BwDaS3BZAoAAsmEC851wh8n2ICfBm0iGYTuqqdUIjxEMEkeEChVCaF0KzAwphtAWE5maIIEkijJx3D3tgPsICUGQNEZ7JgVAvAEl5Lg1aI8wbXyIi6fu0NyJyguMQYAt0Lgf0Go45oLi3FZG/nHLuqE4QaD2lwPaZg9qghgqWHObhgmhKAYBIR%2BwbjoPeMeGRpxgS8WQMiGGcQCAQCic41xDgsjmIwdg%2BWztFZcPvDw0Ky0al1O9A0ppTiYltIEB09RmjFzYHnpJe83DByDIsBwFYtBOD%2BF4H4DgWhSCoE4G4aw1h0xrA2JJMEPBSAEE0BslYFZ8hyg0AADjMGYAAnJ8rg/g3mvK4IkRI0gtkcEkLwFgCQUl7IOUcjgvAFAgBSXc/ZGzSBwFgDARAIA1gEGobtCgEA0DsjoHECIrAtiqFeS5fsLlJA3GAMgLMUg5RmF4FRIgxA8AljSfwQQIgxDsCkDIQQigVDqFRaQXQaTMHohSJwHgmztm7PuYczg51ZT4puKgWyVKaV0oZUyn2khWWOQ8CS%2BghY8RcCWLwFFWgVgQCQMSlIpKyCEpdW6kAwApAZJoLQMUUFKDRFVdEMILQEQKt4GG5gxAETnWiNoI6KKbnEq/FI2gkbJVYGiF4YAG1aC0ERdwXgWByxGHENm7aya8AdneKqvMR1ZRbBuWEMUoKDl0OiOiONHgsCqrRHgSFJbSB1uIIwpQDxy3ADoUYe5KwqAGFCQANTeJg86Tw9k3L5cIUQ4hhU7rFWoVV0r9CGGMKcyw%2Bg8DRERZAFYqAUgNGLf2ckFdTCWGsGYWFY6uVYDvSpboNbnAQFcFMPwaSQhhCGBUEYaTCiZAEOBvQCGGjzGGFUIDUzGgTDaJ4Doeg7DAZw3MaDCw4O2Fw8htJsxWjodg1UFYCgLmbAkEqjgOzSAwt4HCm4eraX0sZcyk1rcIC4EICQNuoIbV2vnSsa6TAsDxEA08yQoI5SfNBMCjQkgzCSBchoDQ/gXKfP0JwcFpBIXSblC5LgLlXmfIBS5QIvzNMuS46quFCKkW3PneirFTqcWatlOQSgnrLXkrYJwFoLAOyJH7EwaGV4uCfLlFwF57L8Ccu5XoHdAr93SEPUoY9krdAZNlUweVJb2Oce42qjgGq8Wym1bq6lAmkuDRS2ll5ZrUAWriFJswtrfOosdc6vrrrLWhaJRNr1nojApeqHwOggbEUQBDZKmNEao2kC23GhNSaHA7bTUeDNWaDk5rzQWotO2y3nsrRd6tbS63FoOY25AzadttrqKqrtPaER9q2Acwdw6bljonZgKd92Bp%2BcXUwFda6N2MB23lvdQrCuyCPRKg5ZWz1zo/VYK9XaAMPqfVkF9b77wE6/T%2BuIf7633qww0FwiFqOkCg2UDDKH0iIeyPhvI8GedobI1zmjdRiN9EmPziDTPei4fo4sGjVHpeEflyLhjbHVjrFYzaszHGVWSt4/xg183OupfSxoRy4nOVSZkyNh18nMCKZGIB0FFmrOpZ04kfwnygWgl0/pyQaS6tedsD5%2B1aKMXYtxfi6b4WyUUui8QFgBqWAKA7FmDsXWFzjEyxJv9uXZD5fRyK%2BQxXsc6BAKCUgFWquKr17Vzz6rgtRh1Xx1P6fM/Z%2B8lGCA5rJsDbxKCYbEexsoFm1Nj1E%2BRgZ5SCkZEWfPnIhzwQZEqg6XLYDTdYNobw1xp23t%2BNibk3Hb6%2BmhgmbVWXfzWIG7I67sVqB6Wp7jgXsNtUE2sUX3BA/clX9iNgOA6XKoOvA4O6QkO4o0Oc6o2fAS6Cgq6mA66m6KOReaOEgGOoq5eJ6VeeOF6n6RON6JOhyZOOYnA2wmk1Olg36PGv63KDOgGRG2GLO7gKukGiECuFGqGWQbOXBJQ6uiusuAgkueGuQMujBDQwhHBmGtGIhBGSupGnOGuuuzG2uQqNWBusKnA7e9KaeGeYk3eQYve1ukm1qI%2BcmpACmSmlA7G7uIAXycooIoI/gfyQehmjhiQ9mHmhunA3myK5hqm/gGmgKiQhmrykgPyXA7yrkeuoIGhPGPh9uDyeubKXhmh8KiRIUo6N0WQIAkgQAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/kindred_find/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/kindred_find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/kindred_find.test.hpp)
