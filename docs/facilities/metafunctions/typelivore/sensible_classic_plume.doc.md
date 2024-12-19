<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleClassicPlume`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::SensibleClassicPlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by containers, the function places the elements into the containers via a process similar to pack expansion;
then, it collects the type result of each packed container and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
SensibleClassicPlume ::   typename... 
                       -> template<typename...> class...
                       -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensibleClassicPlume
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
struct SensibleClassicPlume
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
struct SensibleClassicPlume
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

We will see three examples that present different use cases of `Typelivore::SensibleClassicPlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = SensibleClassicPlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensibleClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Elements>::type...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<typename Element>
struct SensibleClassicPlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<typename Cosmetics<Element>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIACcwQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHASYLKkG2yb%2BbgQAnqmMrJgAdDfY9GyCCofYANQmGgCCY8ReDi9CjEysXobgMCkyyGUeUw7w%2BJgA7FZPi8US9trt9jCjui9kwDtizhc2Dcrs8XsgwQoXgB5c7EPHZZ6w1Evb6/AgvZTEVBEABKqCY6GZqIRSI%2BLJZAHpJS8ALJeWiOPaYF53HaMAhPZESlHSuUKpX0F4eQRMCIJLXinVona4/HHW2Yw7HQnMYk3MkUpjgkkeBRsRzIJ7%2BbDCnVsv4AEUwTToYYlovj1peXkyRjRhLe/kjNLpDIESetztO5zdKr9AbwQedaoemueIBAJeuHpDhzFyYRkfbsMLupl8sVeGVqvuGstyb11MixtkZsixD7NoxeKxDpX9ubZZJnsps/9MarTO14YIPyjMbNtGdFcPpjbJ4TiKXLNTEWAGfOWZztIS%2BYYL4igSpaXPulb3m4tbjg2TaEjubb%2BB2Rbwt2iG9o%2BLI4k62KOquxaupc8GvF6Po3LegbBqGGGom%2B6b8oK34vNGsbXkc5FVgoRGNs2PaPl2vFwo%2BWF4ThG5rluhGtsRlIkh8wDEJg6qPMeVoorRH70egjFcjyqCac6ckKUpmpEQJ/FoZ86EfMJm4EWwo7GSpEYcgCDBAiClJVlCPhrlBggqYmQm4ZuwXiXZLakiG5J7r%2B9L1ABD6qayZ7spy3J8gKQp8c%2B1H9jSM5%2BQQS56oOhrlnO5rEBO1o2eJoX4SB7qRdJ3qcWRGTgZRS7qS8mmMbF/4NUS5UHhRNZjv5IbcXBUkCSy5livGtXFvVwHDUR0WtbJ8mKXWXWPj1fWHDmOkZYKBk7cZbXNWZKFmZ8koAFTPS9r2SrCT3PQAKtgQhfS970Pa9wOPYDglwmY/gRBSXhYFmbhoAwGypPWiWwsta1lg5dZOSlfwAFoJKgvTEG8iIpmmH7NoxhXtmTqGLZ8GMuo1Kq04lzn5ZgJNkxYFPvp%2BKrHdjGqPXTC1WczEn2ezVFfHjHJfQA7sT4xUqK/PptTwuFc94t3RZ4NS%2BFpmfJzA3xfdHx6l9mBjC8GhWT1QheKk6RKOgvJ2wa/V5pbRwRAQpAvIHj3B6HYsIYzHyHd7iqMa57mYKCrVedCzqBypjb6UcFuMol2eZc6hPciTwfTtz4zB8rqvNF1huwjMgYAPqtQkBAQGM6CNgolyt8GbhewoBrBy7bsZJgntx0VIaLFbNt2xyXBO5T/yu%2B7k9DwazdcL7f7%2B24ofB1QtACgQYcvOgqzApgkehg3nyx8Pio7wngJ4DfKfgmnPkZ4Ix%2BnzxMHK%2BXgb5ZxADnNwecCwFwgUXXOkQSZMgfvLBkyB%2B5KBaJ3Ag3cQC9zYP3Z0W8X5cFHuvCeU9n4EB3s8OeKCF72zMCvAWY8N6UO3mYPecV86H3/i8E%2BZ8L4gJvnrKOzC6LT2bpw4WicP4eVTpCdOAc%2BECKAZfa%2B9BwGQOgQlOWhdzpHBLrXMgXMy4vBriTeu0cm5Vgwe3bBuD8GYEIUcYh1CzBkPHh7NxUjaHtg4MsWgnAACsvA/AcC0KQVAnA3DWGsKyVY6whaQx4KQAgmgAnLAANYgGCZIK4GhJBcHhP4DQwSNBmECIEMwAAOGp%2BhOCSF4CwCQGgNCkHCZE6JHBeAKBAO09JESAmkDgLAGAiAQCrAIKkLwQcKAQDQLsOgCQoiXE4KoGpgQAC0gRJAvGAMgZALwpBXDMLwSehASB4G7qQ/gggRBiHYFIGQghFAqHUEM0guhSFK3pKkTgPBAkhLCRkqJnBqSzJmRyVAVAXgbO2bs/Zhzjn5M4RADwSz6Ck3MP4LgixeCDK0MsCASBFmpGWWQeZZKKUgGAFIDxNBFQWkoLEUFsQIjNBOAC3g7LmDEBONSWI2hMAOG5aQRZdZpy0C5Z8rAsQvDADcGIWgfTuC8CwCwQwwBxCyrwApBweAABudtQWYFUCK2ZmxUmB1qKC2gH96T8o8FgUFZ48AtLVaQY1xBYgT2jJqow9qjAZOWCfJgwAFAADU8CYCVr%2BcJqS7nCFEOIZ5Sa3lqFBd8/QWqUBxMsPoD%2BfTIDLFQCjbIqqtld2OqYSw1gzBdO9cQa5JqS1dBFfFFwDB3CeHaHoMI5p5jDFIe7YoORe35BHUUeKcwhiJFIXYDtPRxitAnX4BdtQl0NBXbOiow7bArsmOug9sxB1zokMsBQiSNgXoaRwUJHTQXdLhZsnZeyDlHJOWi3AlzsUpPxWkkNywECYEFMMCA2SQCSH8FcJI/h4SSEKWYSQgQ2nBMCEkO9TTSAtNxVcQIXBAg1KSDUwjeSuDBLg8ETpvBum9P6YBoZxLxkksmZC2Z5BKDUqxastgnBmgsENfCLZTBNrpi4EkK4XACnnPwEQZtNyXnJseRIaQ6alCZs%2BboDxvymD/LVUC%2B9ILPndIhdM2ZLwYUvAE0JkTYmPwSakwUl46LUCYoSG8SGZgAOEuGax7jCROMLLc%2BSrFIAbPCa9EYCTXB2mMu2FVFlbKOX8rFbyzlgrhWis9RKjUUqZWRLlQqpVtAVVio1VqnVhW9VLuNaqyJZqLXbDFTaoJnz7WxEdScZ1mxIluo9ak71vqlD%2Bsq%2B%2BENfADARujbG%2BNYqk0PNTWp2QGaPmRO0zm4NtarAFo68WiDUTy0CErdW7M2362NoSAp1tB3F0GucBAVwR7%2B3dt3QsKdmR4rPY%2B2Ot7%2B67vxRJquvIx6AfLtPWUc9C7D1rr0DMFof352XuvU8wzD6aNgo4NZ4ggnhOiaiw5yT0mNAuZ/fJzzuKfNAdICBsDiQDttew7hyThT4SUfhCUyQyHdmkIx3R2wDHfPMfgKxqZUKgsBeILxzYAnEUsAUIao5hrHOYjGLJ391y9ALZTU85bryNNrZ0AEUgun9OArvejp94L2PQthbLvZ8vFcvGV5J1XHJXPub/f4fwVOmMjNJSFilEvA9hcV27ZuLvm5u9bjj3ZfA6AJb6RAVlnz0upc9WngVQqO1ity4IfLoKiuKuVaq1JFXA29fVTVg1dXTXmuQJalrghbXtYdZynrrrm0Dd4ENv1OwxvBr92G6bMa42lnm7IRbuulOrazcbgwW3802D2/AUtR23KcElF3PNdbLANto02lt%2B3L2bvu34R73bvshFe2evd87SCjq%2B7Dn7M7b/vfbWfoHV%2Bwfboh4MO/cOMOIOgBf%2BQ6SOKwawN6eKFuxmXSnA2OLAcuCuSuKuq49sEAZOJAFOeKBK1OtOWA9OhmTOIAZgkm3uwS5SRSbS3u8IRGj6JmnA9GAy1OOSkgwSsGwSNSlSSQkgSQJS8GXA/gd6/gsBtGjBjGRKhmZy9BcBPSEhmSXqFo2QUGQAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/sensible_classic_plume.test.hpp)
