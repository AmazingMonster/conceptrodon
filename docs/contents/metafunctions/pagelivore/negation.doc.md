<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Negation`

## Description

`Pagelivore::Negation` accepts a predicate and returns a function. When invoked, the function returns true if the predicate instantiated by the arguments evaluates to false and returns false if otherwise.

<pre><code>   Predicate
-> Arguments...
-> not Predicate&lt;Arguments...&gt;::value</code></pre>

## Type Signature

```Haskell
Negation ::   template<auto...> class...
           -> auto...
           -> auto
```

## Structure

```C++
template<template<auto...> class>
struct Negation
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
template<auto First, auto Second>
struct IsLess
{
    static constexpr bool value
    {First < Second};
};

template<auto...Args>
using IsNoLess = Negation<IsLess>::Page<Args...>;

static_assert(IsNoLess<1, 1>::value);
static_assert(IsNoLess<1, 0>::value);
static_assert(! IsNoLess<1, 2>::value);
```

## Implementation

```C++
template<template<auto...>  class Predicate>
struct Negation
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {not Predicate<Variables...>::value};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQgZgDspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuO3sHmMduTF5EAHQPx9gA1M/IBgoKz8rEmPiihyO2BMGgAguNiF4HM9IphgEwGiDQSYklYwa9Xmd9gjLicbvcHgA1Fp4JgxegKJ5IjHPCFQgjfYioIjKJjAS7ojEotGgmk02aOZBvATjTCqVLEZ4xVCeZ4ANzEXkwz2pfNe3IYzMZfzwANxbmJxFJ5MwCgedyeIBACu8lySABFjjyaSjHUcearMbtsYDrrdUObDcaKVTOa8vJkjN82crjvbGczUKz2Vcg2SKeaqe6ka6nTmwQB6ABUJdLZfLBaRxdLzwAKqaCF8y5XC%2BW28386CsRcrvjUM8AGJ4YjjUjPPvPISYNAMdCh8EESHQgCSChCpspYO5ntpzUFwoYovFkulsptSp33KHI4ZV0n04Ec4dea3z%2BzW7B3Zxvf95tBxGASkgSRCNwmAZ5V0iVB10%2BFUjnjWF4URE5VxgoDsCtZN9X/QDM2A99kTBAVdQAfSYT54gICBIOgjcri4McuEta1FUwJYXwXBFSPIpRWmohQoLQ%2Bixw0ZjzzYjjiOQMiKL4sAwAggTaM%2BYTnjMMTWPY90OBWWhOH8Xg/A4LRSFQTg3GsaxaTWDZYzMI4eFIAhNB0lYAGsAiSO4jgADgANiSI4Ao0XzAoATiOfROEkXgWAkDQgiMkyzI4XgFBAIJnOMnTSDgWAYEQEA1gIVJbnISg0D2Oh4kiVgtlUfyAFo/MkZ5gGQIUpDuMxeB1IgjXQPR%2BEEEQxHYKQZEERQVHUbLSF0BiAHdiCYVJOB4XT9MMlzTM4AB5W5SoZVAqGeBq/Oa1r2s6yRuueCAPCq%2BhJXMByll4LKtBWCAkEq1JqrICgID%2BgGQGAKQzD4OgdhHSgYh2mJwhaABPdbeER5hiGRvaYm0acsscyq2EEPaGFoVG5qwGIvGAa5aFodLuF4LAWEMYBxEp4d8bwOVTR2sVp1uLZHPCHY9Lm2g8BiFasY8LAdsXPA4qZ0heeIaUlHtXY2clowXJWKgDEAwk8EwRa9tSRg0cm4RRHECbhvkJQ1B2hb9DZlBLMsfQpfSyAVlQVIGkZxrxjneDTEsawzGStWBr5/3um55wIFcKY/AY0JwiGSoRgYoosgEdO9ALhp5mGBIGLsZPGgmNpPA6PRq4cXo6/L3PK9sOvi6rtvs4WPOVgUGzNgkTaOAM0gkt4FKzqalq2o654urMe7cEIEgVXsrh3qc/WVgQTAmCwBIIHckBJCOO4IqSSQNEkMxJD8hL/D8sKoo4GLSDihy7j8rg/I%2BTCj5AB/hJBcH8BFPyU8dopTShlPe2VvoFR%2BkVQ6ZUgYg2erVNgnAWgsDlEkRqTA3gGCjFwMKdwuB3BMn1EgeBBoMUdqNe20hHbTRdnNXQkNlqrTRuPSe09docAOiVW4zwTrjmIAQohJD3hs2XpQ6hGh7qPX%2Bs9LeRwzC70%2BjlVBWD4jlWBqgJ6Ix8GEMavIowFCuBBBoLQGG6UIDwzmhjFG1s3FYxxnjBw1siaMAIKTcmO0qY0zpgza2LMdZbBMvgX4LdeaM1oaoQWOxraizqDtSW0sUZyxiR9I0ytHJqw1pgLWrMjC61AEgvgRsFAmzNhbK2KtmF23Gmw2QHDZomW4e7PWkcrDe2yX7M%2Bpkg7ZBDmHOMAzo6x3iPHEZQ86g1xcLOHuwRZzt0WPnDIhccgN3yDs4o2Qtl5yTi3AQfRJgHIzuchoVyBj9wrk3buNyXlzCeR3Meqx1ijx3h/QRsDOBSJkcQ0hCiKFUJoWvfA/VNE7w%2BvvUgh9j4jFGeLL%2BP9KH3ySJApIgUH5P3ATAuacDbAIN0cg%2BAqDipHSMQY4gOCtj4IXiwBQcohRykhRccYvVYX0MYTbFh7SbZdNdiASKvC1pMwEdtUl%2B10HHVOiy1qbKOXym5TicYqiTHqPiJoo4Oj9a5V%2BrqgG9KzXPWtMgVIqQSJcrCiRHlBAyLSJalDBx8QnEuJMp4imjk/XePxn4kxxNAlkwprEzA1NaZiAiSrKJlT8mkDidzRJ/MUnICFukwQmSJZSxlsjPJCtCnWxKRkMp2tKlgWNYbNk9TTbm0tkZRyrSxoSA6VNZ23SdASr6cYL2NhhnwADuMkUnACxh09lHSwMcZ5xwYQnUZzcGirPcG8zOmzPnbLSLsho6zS4nO3Wcldrd%2BjrNPZcvu5Rnm93PRuruHyb1fP%2BcPX541ZUkuSsClVzw1Wcs1TsbVEB15wtegixBX0D5HxPpQcemLEiUKOEcfwgRwEJWQ0kQBX6Z6cHgZlJFHkH5/y4FovyWiwr/zMM/FI4sjhyu/alSDrkP49Rw8IxFSCVhq0yM4SQQA)

## Links

- [source code](../../../../conceptrodon/pagelivore/negation.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/negation.test.hpp)
