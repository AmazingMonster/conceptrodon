<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensiblePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-plume">To Index</a></p>

## Description

`Typelivore::SensiblePlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by a list of transformations, the function instantiates the transformations using its arguments via a process similar to pack expansion and invokes the operation by the instantiated transformations.

Check out **Example** for more information.

<pre><code>   E
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;, Transf<sub>1</sub>&lt;E&gt;, ..., Transf<sub>n</sub>&lt;E&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;, Transf&lt;E<sub>1</sub>&gt;, ..., Transf&lt;E<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume
 :: typename... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensiblePlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
/**** Transformations ****/
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = SensiblePlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename Element>
struct SensiblePlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<Cosmetics<Element>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3AQAJ6pRisTAAOjR2BejAICmh2GBE2IXgctyEjEysXoyjymGBJkCViutyZt1B4PeNJhrOe7OhsIRSLYaJRuNuyAMCgUtwA8ojiO9srjgczbgSiQRbspiKgiAAlVBMdC3JXMukMy7K5U7Ha3ACyXlojmemFuGLBWJxjItTKttvtjvotw8bwiCQ95q9LLB3MhnKjEI5fMRzEFaJFYqYEqFHgUbEcyBxULxnq9quJABFMC06MavaaaxGmV5MkYWfyjVCy9LZfKBLzs7m8Pnea7XtjcULFVCzQ26WXoWb65brXaHXgnS7MYIww2fVLIoHZEwQ8RF8yufHeeeeZz%2BcnUanC6LxZL%2B5XB4rixbS%2BqK1XaH2MgHUxC1PJk60/BsmwiYBW0RdtOxlBIewYACczfYC3BHd1xwfPEp1Ao1AjnfCrgIq8Y1hONr0TAV72FR900zNFXzzAsi3DL0oJbPUDXg25fyPf8YRYwcFAnQsQBAeFEXnetZ1k0jP3IhNlMvW9kXE7AnwzMS0UuYBiEwN0tw/Djbi4mCeMNaFO01bVUCs3l9MM4zsU0hSgSIjzgVUm8k2RDdXNM78STJPAKRUalh03AhTPAszfMotkKOk2jNO0iUuyQxpTOVEK7N1fVrM/eKd2tPdnSwwQCJ9Fd/WdIMq0iYhtwjRL2vUlN6K0xjdJREShxAiDmQs24rL4xC5Ry4TAPQgtMJinDuo85V5JIoElKolKtpUzq6LTZ8hWcozRzY%2BtRvGmyNS1QqDScgyTvddz1rWhcfn%2BD6vmBX49luAAxPAWvVbBVFYdcvvez7PsBWkzChCIxS8LB2zcNAGC2VIxyGjbriOW4ABU5QYBR%2BGIFhkMlCGQR2tT/LYQLR1M0aAC0ElQfpiDAjsGaxbyrg6unKsW7HRoqjm%2BKqgg9j56nkt2wWeeqkXmxg/GAHd2cmSUrslg4ZZ%2BrKpuyT4zh8mm/LS3D8QIQliUm5D9bxoQvFSIpMHQHVMAUP0TYOQFRud12Mndz3vYdCbu2mtwIgIUhbhjvY44T6WQJeyGDjGr2fapi6s/Dq7SWJ8LKSimEY9MyTHJhe3pvYyuit5VmtQ5uOxcmOP1c11ozrT3G7nxr31SpuY8wAfR0hICAgCZ0EkhRkXH%2BbQ79OPA7dj289iwtlkdqHoe%2Bp3MDRw0QbBgMqZ%2BveAVpdPfrX4ON7DofTauAOXfX5eHVHrgI%2ByhUy8EInW4VBaD6ilnHdA6wIopzwm9PuGdP7Pz9sCXOT9v58ULuSEuPgEwxzjiAsBECoH0AriAKubga7/zrmQhu1dIgc0nHAg2A8Ji%2Bz2ICEeg5F5KDaNPAgs8QDzzYIvXkiDv6r3fg/MRXBcQ717pfK%2BF88b4wQIDE%2BoNwTOiUYo6%2Bil4F30kUoR%2B2cX6XDfkHIxYizC/yNr2ABsdgGgPeEAyBXhoEwN3ggzebD/Yq0zmg6xBcwoRSpDg3keDHGENuK4iKpDyGULsdQ8hTcu5kGlPQ9uBMNYcx7kw5Rg8fHW3lMgbhk8%2BECKEZgERMIrESIsSHTeo8zCyPnBwVYtBOD%2BF4H4DgWhSCoE4G4aw1gVTrE2M6cwUIeCkAIJoNpqwADWARJAog0AADjMGYAAnFsrg/h1lrK4IEQI0gOkcEkLwFgEgNApB6X0gZHBeAKBACkWZvS2mkDgLAGAiAQDrAIKkLwscKAQDQE8OgCQojIk4KoNZAA2AAtHCyQtxgDIGQLcKQKIzC8HdoQEgeBZ5cBkIIEQYh2BSBJfIJQag5mkF0MStWcpUicB4O0zp3S6UPKlECwF6pUBUFuLCxFyLUXosxSs6xEAPDgvoJzSZXBli8DeVoVYEAkBgtSBCsgILNXapAMAKQZg%2BB0FBC1SgsQ6WxAiK0OErLeDWuYMQOEUpYjaCPm86ZYLRx7loHa95pAsCxC8MANwYhaDPO4LwLA5MjDiADfgQyDg8AADcvZ0swKoI%2BQLtjTJjvUOltBwpymdR4LAdKbZ4CuVG0gabiCxGDhWWNwAi1GDmasEBTBgAKAAGp4EwGrRCPTpn8FJaIcQlLR3UpUOoANDL9CGGMMMyw%2BhwrPMgKsVAmNsiRoRTPGyphLDWDMPcutxBCXpo3T0D12QXAMHcJ4ToegwghkWKMYlRQsgCGmH4D9GQv0MAWCMao17k0CA5u0R9%2BRiV2BveByYgxX3Ab0HMKYUHf22AQ0Byo77VgKDGVsCQ7KOBdNIHc3gDyhXwqRSitFGKsVStwPi%2BVcNFXKvbasBAmADSjAgIskAkgoQoi2VCE5GhJBmEkHCm5/g4VbP0JwC5pArlTJRHCrgcK1lbMOXC/wkg9kibhWRrlnAnkvJme2z5Pz1V/N5UC8glA9VyqhWwTgrQWApsCAipg2kWxcC2SiLgqzcX4CIOeolVKyUTukFOxQM66W6GNUypgLKo3EdI%2BR/pnAeUAqBbcAVVGRUovTH5gLQWNC3GlagWVCQjRwzMEqiz7y1Uauq1quVDnQVtf1SVw1uyUg0AdKGC1VqbXOvtaQR1trXXuocBN71WJfX%2Br6UGkNYbaARomzGxd8aVuAxvWmyNfTM3ZtBBN/NZy%2BlFtiCWuEZbth9MrdW6ZdaG1KCbTt6ClnO3dr7QOodE2p1RYpTF2QcXaVzpAMagwbbD1WBXdd9dfH%2BnboELu/dHY4fHtPQkcLl7kewbA34CArgf3PvvdhpYf7ijZDJ9TgDlP32gcaBBunzO%2BhYaQzhkDqHIN5Aw7zxn1Q8MEYpelzlAbKPCpo75mC/nAurMq0xsLdWpmNZVfM0gXGeOJGR2cpTKmAvicCP4LZxyoQSak/p4zkvTO2HMxrtV1mkD/L5Z1pzkLoUcHc6KlgCgU0YpTfL%2BMEwQvMcJXoIH46QdUvB7OvpugoSkGS6ltlCmSMS/udluz/LBWqF9/7wPwf2SsKqzVljUIoTq8szZj3OrHPdblSAAPrtR5B62aPEPBBR755i6a4bEBLUBqm%2BNmtI%2BXVuo9fN6rPqGB%2Brpat0N4bI3TO23Gh70b9vJsOxmrNyAc3ncEAWgN13bv3Yree57vBXuNrBJ9ttzW%2BAGF%2B/2wdSZAeyGBxIUHgg48JZAEnjDkukegjmuvAJuqjsTJwDsDPCgMuhYCehRmehekjnhvUHBsTqTuhuTugELnoJ%2Bo0GzgQdkHgTBugUTqztgWQb0PBvMFzlTphgMGzoLvQbhmsBsIRoqunhliZhwEKgXgHrcO3iiF3krqFiQKrmxk1qqpxtxlgLrsRgblDgFpXv4PsvpjcpXoEJpjblno8vbq8hxqQEspIP4MJkcoEDcmspILslwBsmYEZmclCJnhRnbo7sRjiroa4foe4bWqGLepIEAA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/sensible_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/sensible_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/sensible_plume.test.hpp)
