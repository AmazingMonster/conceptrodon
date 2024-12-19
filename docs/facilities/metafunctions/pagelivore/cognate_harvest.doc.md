<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-3">To Index</a></p>

## Description

`Pagelivore::CognateHarvest` accepts an operation and returns a function.
When invoked, the function collects the value result from its arguments and instantiates the operation with the collection.

<pre><code>   Operation
-> Elements
-> Operation&lt;Elements::value...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest ::   template<auto...> class...
                 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the value results from `std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>`.

```C++
template<auto...>
struct Operation;

template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

using SupposedResult = Operation<0, 1, 2, 2>;

using Result = Metafunction<
    std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<auto...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxBJmpAAOqAqETgwe3r4ByanpAqHhUSyx8VyJdpgOGUIETMQEWT5%2BXIFVNQJ1DQRFkTFxCbb1jc05bcM9fSVlCQCUtqhexMjsHASYLEkGGyYAzG4bWzuY%2B25MXkQAdDf72ADUyAYKCvcA8klxTI4CdyYaAEEFARiF4HPcPMBmBsABINABumGB/wBJgA7BZ7ij7jj7kdtt9TgcCABPT7MNg3K5uYioJIKP6A3H3LxpIz3ACynnQWL2ABF3p9iN8MmcaXSFCAQPCxF5MFS/ntMSj0Xz9lZASiAPQAKj1%2BoNhq12oN9wAKkiCK8DcbAbrDQ79bbUZqzHswk8vFheW5LnRCCTGai3R7vN6zmgGKsklagyj8Sczhdrrc9tgUcDQeCPl8fgx1SrAQnCWdSeTWPKbgDiMAGWmUaywsBOZh6lQvFG87yBZDoZg4cREciDjnhXmg1KubR0Gdq7WFfWlYWAY32UIvEkUkp0AAlJFeWgEbuC3Oig4aUj3LiXxL3MyKjUulds5t7hQHo/7AUc1tMduds83GxXFgXQKUwg2YBhVoAB9SNgUMAgzggy8NDuS9QPAwRMCgsQ4IEBDBGQwRLy4dD7kwkAIJw6D8IYQikIOFC73IyjqNw2D4PqIimJIlj601RdHwzepHGQGCmBeOICAgSiFArCS6zcN8P0vddN1STBd33Q87jmdUOAWWhOAAVl4PwOC0UhUE4IDLGsCilhWTAsTdHhSAITRDIWABrEATIANiuAAOAKpBMtEAskfw9kit19E4SReBYCQNAvCyrJsjheElC9PMswzSDgWAYEQEAlgIJJLnISg0C2Og4giCtOFUUKAFoovuYBkGQK9JCuMxeC0wgSDwMDr34QQRDEdgpBkQRFBUdQCtIXRrwAd2FJJOB4IzTPMrzrM4N5Liqo9UCoe5WoCjrJC6nq%2BoG%2B4IA8er6GIVy9i4OZeHyrQFggJA6qSBqyAoCBgdBkBgCkRIaEPOJJQgaJDuiMIGhJHbeDR5hiBJN5om0ap8vcuq2EEN4GFoTGVqwaIvGAc5aFoSVuF4LAWEMYBxFpvBiGJvAh0OzBVGqS41nc6jjJW2g8GiYU8Y8LBDpBPAUrZ0hEWIaJNL5TYudlowvIWKgDFrAA1PBMHWnMLPcybhFEcQ5odxa1EOtb9C5lBrGsfQ5clSAFjpPNWba0Cv1MezLDMTKteIMakXgBYOjzFwGHcTwWj0EIwn6UpBmvLcCkyLPxjyNI82mAZylsTB7DzbpRjL1o64b2oRl6POZkLyZm%2ByVuEMaauC/KFOnNWCQ9o4MzSAy3gsqu9rOu63qpCeiBcBGj7zC%2Bn6PONhYEEwJgsHiCBfJASQ9iuGK0UkDRJDMSQArSwLAmlpLSBSr6rjCgLgr%2BGClwAKJlJBcBMjFAKc9DpZRyiAPKxsiqlUBuVU61VwaQ3ek1NgnAGgsHhGiNqTBHgGHZG0K4XArhWWGkQBO415qOxmhIaQrslDuxWroRIm0mDbTZtPWe88jocBOpVS49wLr3HwYQ4hpCuZXn8JQ6hz1Xog3ep9Mw%2B8/qFVQVguINUIaoDeoMaRRCnhczaFwC88MNjECRijFaOMMZY1IE4vGBMiYOBcWTRgBBKbU0OnTBmTMWYuI5gbNYVl8D8xqELFaIsxYbBcVLQ6st5YYyVpE36Cd1buS1jrJQetOZGENqAAqJszYKEttbW2LiHbTWdqw2QbtlpWS4V7I2UcrCWH9tEQOF9rIxgyGHCO/IunWFjgveOid%2Bkp3rgLZwEBXBjFbrnYoNc9DFzzCszZ%2BQq7dw2deVOHceg7KOfMzoDAm5d3WaPPQQ8mgt3uZ3EesxvqLGWJPd50tBGwM4FI4gBCiEkPMeQxRVCNDPS3nQz631fqH1IMfU%2BgwBmf2SiAPYijH5okgWiNEewn4v3ATAlacDbAIIPuU5B8BUEVTOgYvRxAcFrHwZ1FgCh4S9XhBQk4wIhr4DoWNPQ9SnazSaQtdhrSdAYtIDwvhu0EozwOqS466DzqXVZXddlnL7jcsUbyo8L0jFqLiJ9PYWikG6ONaDBl1r3rSmQJuGCeqYIGokoCqKfA6C2PsajdGeMXFuPxoTYm3ijHkz8VTGmUTMD00ZmIUJGtwklKyaQaJAs4k0NFsgcWyTsLSysmkhWJJMkqxyS4/Jut9YlKbEg02TALZWxtuSOpsgGlisYS0j2MqyHGF9j0tJszBmh04FqTC4yY5xziPQpOQc24LL8EsjOZyggZ1eb3LZGQV2bsKAcu55z25dE7iu45R6ph7reX3R5A9nnntuW88enzZoCOVZlf5mr7jaq5TywkwIoUCpILCi15Sj4nzPpQaeX8UpmEUXsPYJkTKPysRoODkVgokrfdlcliCQOkD8tfShexgpgLdIhgKbpIqKr2K%2BhenB4W4eloNDDtGsPaLmAsLWaRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_harvest.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_harvest.test.hpp)
