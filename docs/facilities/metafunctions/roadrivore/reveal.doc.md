<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-reveal">To Index</a></p>

## Description

`Roadrivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<template<typename...> class...> class... 
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Reveal
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Operation ****/
template<template<typename...> class...Args>
struct Operation
{ using type = Vehicle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Vehicle<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Reveal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Reveal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Reveal
{
    template<template<typename...> class...Containers>
    using Road = Operation<Containers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArNIADqgKhE4MHt6%2BekkpjgJBIeEsUTHxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRcdIKtfWNWS2Dnd1FJf0AlLaoXsTI7BwA9ABUm1vbO7tbqyYaAIIbWwDUAJIsCfRsgkxVZ9sHx6d773svR4dHBJjXBj%2BJgAzG4/gCHpgQWD/jdIdCCABPBKMViYAB0mJB2DOyAMCgUmPR2Nx%2BIUZwA8ijiA80tifoNiF4HGcAEqYABumDEPxMAHYrMczsKzuC4UDQWLAVDJcjUWwiSS8UwCUSPPdgtEFPShSKvCkjGzUEx0GcQQARSnU2kCaHq2qa4iErHA7AgEBIlEgwXfPnm72814fd5fN7rM7YVSsG6YJ77H5h4Px468szA4J4rxYM2gtAMZYJAja12Bk7bM7mnwsRFnI7EYA%2BRhFuObL5S%2BGylHMBUu7AMghMlnqgD6GgDKeO7YlYLl3Yxvf7g4IZxHXHH30nsOlCNnaMVJeOjOZy5HZnXPynMpnXb3C8PA%2BPK4Ew%2BB56D5wAapgEHg8bHnheW4djCELTp68rzsSrqkiqzpQX295LmcX4/n%2Bb5lucVLRDaDAtusbZAWBhFXuBc77jiyqqpidbAMWCFHEeLJYTSVS8gKZz6sEwCinKOaWihv70NCNFwfSwIWGafroWGZxCF4CQ5Jg6DsgoXi0MuAHHJxhpyQpyRKSpanLhayHfoJV6nqQT4MC%2BVkjhodnPmuJbiaWMkALKYLUVBePmjyab8xEIkFnYQeRMFUeiIk6kc2ncZ53m%2BQ4aR8WynLcrQ0LMThMXuqyxroMJ9aiS5PoJuWhnqXhXxxWlqlVSZCVMD5fl0qClnWbZnUOZ1zl9q5E4YZsZwACqYIM1X9rSyDDrB0QEBAgzoO6ChorNxZuJVBBWbpinKeNRnYjM6EcHMtCcLEvB%2BBwWikKgnBuNY1hnAoCxLLG5jAjwpAEJop1zAA1v06IaAAHGYZgAJyQ1wsRg6DXB8ny0jnRwki8CwEgaA5123fdHC8AoIAOb9N2naQcCwDAiAgAsBAJF420UBAaDXHQ0ShGinCqKDABsAC0vOSGcwDIMgZxSOiZi8EphAkHgy0tPwggiGI7BSDIgiKCo6hk6QugtAA7jSCScDwZ0XVdf13ZwFKMwzy6oFQZw8wLQsi2LEuSFLZwQB4bP0MQZpplwMy8KTWhzBASCswk7NkMzsfxyAwBSGYfB0H8TqUBE1sRMEdSImbvD58wxCIhSETaJgDjF6QrN3AQFIMLQRd61gEReMAbhiLQRPcLwWAsIYwDiO3eDEDXjhcv3t2YKoNeMys33BH8qO3bQeARDS5ceFg1sDngmMD6QXLEBE%2Bnmv8I%2Bb0Yf1zFQBi0R%2BeCYIbWHXd9yvCKI4ga9/2s1DWwNvoEeKAnqWH0FvImkA5ioELGkfu/MloWlMJYawZg8Zn2IArca8A5h2CnmkFwDB3CeCaP4UhkxegxBaDkVIAgRjNFIPQqo1Dih9DGBUIhAgOjDHIaMVoPDqhDC6JqKYnDbCiKYXocY9R2HTFDvMRYywJAWw4JdUguNeD4xdnzQWwtRbi0lmYX2uA5ZB0%2BqHcO985gIG5FgGIEBAYgEkMCdEkNgTIw0JIMwkhebY1iLzSG%2BhODo1IJjL66JeZcF5qDSGCNebxFhp43mWjrb40JsTH698KbU2jrTe2jNyCUCToHTmbBOB1BYByPk/MmAwUNFwSG6IuAgxlvgIgODFaax/mrCQ0gAFKCAXrXQ6djZMFNgPdRmjtE2w4HbemjMzhOz0W7YWyomktLaRoX2/s46B2DsCMwYcclkyjjHVAAdoglJZlcg5fRNmpxhg5Gg6ktQ5zzgXcuddS6F0rtXWuJ8G5Nmbq3a2Hcu491oH3OuQ8b4rFuvgSeyUZ7W3novP4ddV4VGtpvbehc96IvDjg4%2B30z4XyUFfYeRhb6gHOXwJ%2BCgX5vw/nXb%2Bqs/6DNkIA3Wt0xmgLvmgqwkD8UwOcXdBBAgkEoOBOaYVGCsHRG6Xg2BQjkrOAgK4GRLRAjiJodkZIDD0gCOYawtICjJGEI1SIzoOr1VVD4WIwoBqxjSNNbI0RlraEELeqopRqNZkZM4GsgxjTuLNNaSDMxnSSBHOsWcyOdiHF9AlajcJkSWk%2BL5LESGSNgS%2BP8ZIFoczMm2GyRHcmlMaZ0wdrcspHMuYcGqe7FgCgOTiw5JG6UgwOkWIVnoDlv91bcq1sMvlOgQDAlIBMqZ5tQkaKtnrfGiyHYrOdqoVt7bO3dshBNP29z45HOBKcytFyUCHsDvWy9fQO0KWHF2yGw4e0EGHJuwZmcPkQFznrP5PyT5/orlXKedcQWCDBW3JFmBO7d17v3b68LaXEtIMiohaK9YYuQEvbFghcV63xTvRERKD6krrhSy%2B19aVcVyY/Jgz9X7vy7Oy2QnKR29N5cAqdgrjAQJsGK/Bkqqj91WEtcB6DLCYJ0dg3B4qCHcJtSQshmRmF6pdRw2hLCjVVHtea/I%2Br1OyPk4691ynDNtF4V6/TiipF2o9W6iYVnOG%2BpUerGZS68YhvfWcNtHaziPvRC%2BmNFj42ntsaQexJpU3qIzSAKG6JgTAliHDYt2MEt8jiek5dnAskkzC0DSQsQPGIz5NjUGkgYZcHBmYNJqNgTuZ0dlxN/0F3S0yx5gmTWZhzDPikZwkggA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/reveal.test.hpp)
