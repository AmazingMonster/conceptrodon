<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-agent">To Index</a></p>

## Description

`Roadrivore::Agent` accepts an operation and returns a function.
When invoked by a packed warehouse, the function extracts the list of containers from the packed warehouse and instantiates the operation with the list.

<pre><code>   Oper
-> Ware&lt;Cons...&gt;
-> Oper&lt;Cons...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<typename...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Vehicle<Con_0, Con_1, Con_2>`.

```C++
/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_0, Con_1, Con_2>;

/**** Result ****/
using Result = Metafunction<Vehicle<Con_0, Con_1, Con_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Roadrivore::Agent` uses partial template specialization to extract containers from a packed warehouse. Here is the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
    struct Detail<Warehouse<Containers...>>
    { using type = Operation<Containers...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArABspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCCABPJKMViYAB02LB2AuyAMCgU2MxuPxhIUFwA8mjiE8Mri/sNiF4HBcTsBGAQ/iYAOxWU4XIUXSEIkHglFo5hsRmC4XM1kEC4AEUw9ToFz5Vl5yrBAt%2BcqFouBMIl8JNSPNiIlqPRbBJZIJTCJDtBeKdRIuAHUGpgEEslKQRVbxRDbdKsTi3eTncTsR5HsFogpZSdhRcFWzVeraLCfcQ/QHTW4E%2BqQsQ46S3an01qLl40kYRbbNaDldTafSBLDS0wkxXXdg9ZqdXq/rXDcGoaHJXbI5iOQXAVyU9XJw3gsALgBZTzoVvt7N93PgxeYZeCSu4kAgWdj0583Wg/V/D5fPY/N8XbCqVh3TAvIcr7vt8PIPmYoLBASXhYK2bhoAwqxJAQq5Dg%2B7y7BcABqfp4ASAGvH8xrWnC07FrOEaDjGLpRmhJyZkqOEIHh9D3gaZyYScxDAD4K6AdsPzETO4YYoOTIECybIJgA%2BhobFESG5EifatHiZJSoyVw8mnEJSlSqJqmnAxFwyWY2kcZcNLRF2DD8ZsgmKZaZFIsp86OhSYlGRJiodtZNTmV%2B25qkwVBeIhzyETpjk2vpKkLtxqF/BuTZBfUoXhRkB7spygiwlZdL%2BW6N67rQ6CwlxwBXtWz5gRZ2wXEIXhJHkmDoAASpgCheLQSqRScyVbo1zWpK1HVdT1WX5TZPYCLJQaafNs1mdVL4YZcY3db1QGnANFwbRNYLtqlIVhQ4DLgkxLHFjJGiLQw0ltCZS2MittVfgAKp1W0CeJ9LINJsbRAQEDDOgN4KBiAOrm4%2B0EEGQ0te1nWbbiczmRwCy0JwsS8H4HBaKQqCcG41jWBmSwrAB5igjwpAEJoGMLAA1nEkiYhoAAcZhmAAnDzXCxJzHNcLyvLSFjHCSLwLASBot14wTRMcLwCggLd9P4xjpBwLAMCICASwEEkXhwxQEBoLcdDRKEGKcKoHPxAAtPEkgXMAyDIBcUiYmYvCtYQJB4GDbT8IIIhiOwUgyIIigqOomukLobQAO50kknA8Jj2O4wzhOcFSJvG0qqBUBc9tOy7bse17bNmBcEAeJb9DEJqEFcHMvAa1oCwQEgFtJFbZBm/3g8gMAUhmHwdAAhWlARLnETBA0yIZ7wi/MMQyJUhE2iYA4q%2BkBbDwEFSDC0CvCdYBEXjAG4Yi0Kr3C8FgLCGMA4iX3gBZnQAbp1ueYFUHvE2axabBABBLAmtA8ARDpJvDwWBc4STwDLJ%2BpA/7EAiCNVUr8jDQKMAzBYVADCVSwngTAycrJ41pqHYQohxBR1obHNQuck76DfigUmlh9AwNVpABYqBkIZEfo7UGh1TCWGsGYRWGDiBB3/vw9oe8aguAYO4TwLR/BqOmP0GIbQ8jpAEGMVoyRUiGIYDo0oAwJhVGUZ0EYTQNHjCUWdAQXRGiWNmBMBxxi9CTA8UmGY1iFgKApqsCQWcOA41IArXgSsy4O2dq7d2ntvZ1wgLgAOLdqbt07oQhYCBMBMCwDECAzMQCSFBJiHmoIxYaEkGYSQ8Q5YJB5voTgUtSAyxppieIXB4gcx5sLeIsRJACxqYkWJedla2DVnTQh2s9a9wNoXE25BKAj2bjbNgnAGgsB/ryR2TAYxNi4DzTEXB2Z%2B3wEQORwdo50IjhIaQTClAsITroSeqcmDpyfpE6JUylYFyNibC4JcEkV1dk6U55zLkaHro3AezdW6gjMB3eZmse591QE3aI6zzY4qRQMaF49%2Ba3RoD1ZMc8F5L03gfdey9t6733mgo%2BXJT7n1zlfG%2Bd9aAPwPi/N%2BH8Cb4G/o4P%2Bj8CaAOAQCA%2B4Cqi52gbA5eCC1gE2Qag2mGCsFKBwUKzcCziFMFIeQyhUoD60PDgwl5shmHxwJp89hBCJFWG4UqvhZTCZCIECIsRbYXVSJkdEO5CjPV2Dsc4CArhfFtECIE3RuQzE1BjaY/IGRPHWJcTUdxjjsgmPDa42oDiM16NsD4px%2Bbi3xqsXokJYTI7/JzgneJ5ckknK3Gci57N66ZNuSi3JGLu4FKKSUygkTOndPOfU3ksQeai1BA0ppYyYm5yVirOZXctY631obIu%2BLNnW1thwPZlcWAKB/p7H%2BnaTTDGuVkoOehLX0MjjamObz7U6BAKCUg3zfmZ3aVEptit86rOLqXVQp7z2XuvdCYYCLCWDxRaCdFm6sUoAQ83fdGGBgXuatJK9PNpI3oINJCDLzp5UogPPBODK6VoNo1vHeyiD5ssEByi%2BIrMDX1vvfR%2BtNBV4LVc/L%2BdiJUAKAcgEBcrBAKoTkquByJVVILkZq3g2rsGAn1QQzFfASEKDIRQqhFrZBWpfQ8u1rCv1OuMFwmw7r4ACO9QwR%2B6xQacMkZYaRcTZHyI9SE2xhbVHqLzVo9AJbE1pqMRWiL5jws2I6G48tIX4sRqLVMatXiy3dBTf4noGXgmLGWOE9uAGAWrs4GXSDF6LgEcxMRntNySD9pQ/k0ghTikDE9RLCdIBeaYlBKCWIgsxlywG7yAZK7m2cHXerVrLNJCxGqSLXkcsOaSH5lwLmZhEgS1BEBuJ03B2MwA77SbwGZmoYWBgtIzhJBAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/roadrivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/agent.test.hpp)
