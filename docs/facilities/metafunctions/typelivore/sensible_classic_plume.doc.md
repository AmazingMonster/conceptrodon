<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-classic-plume">To Index</a></p>

## Description

`Typelivore::ClassicPlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by a list of transformations, the function instantiates the transformations using the elements via a process similar to pack expansion;
then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;::type, Transf<sub>1</sub>&lt;E&gt;::type, ..., Transf<sub>n</sub>&lt;E&gt;::type&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;::type, Transf&lt;E<sub>1</sub>&gt;::type, ..., Transf&lt;E<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
SensibleClassicPlume
 :: typename... 
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
/**** Transformations ****/
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = SensibleClassicPlume<int>
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
using Result_1 = SensibleClassicPlume<int, float, double>
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
using Result_2 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwAzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJmSbgIAE80oxWJgAHRo7CvRgEBTQ7B3EGTYheBx3ISMLKxehuAwKLLIZT5TAgkyBKzXO4cu5giEfJkw7kvXnQ2EIpFsNEo3F3ZA0hR3ADyiOIHxyuJBnLuhOJBDuymIqCIACVUEx0OrOSy2VcNRrdrs7gBZLy0RwvTB3DHgrE49k2jl2x3O130O4ed4RBI%2B61%2BrngwVQ/lxyF8kWI5jitFSmVMWkSjwKNiOZA45LYc1%2BrUkgAimFadHLNstDZjdy8WSMXNF%2BOSVYVSpVAmbMeF8LTyNDmULeGLws9b2xuJAIFHqMzpehVpbLKrG%2BZvr9AadLrwbo9mMEUZbAflkQn4cixCHHIFyZHSaF/NF6dXktL0tlE4FrW05qvuNqVjqNZ1rQwr5lOpjrmBGpNkhMZthEwCdoi3a9oqCQDgwT6Np%2BY5sIB8GzueC6lkuK4SmqySbsOgQ7oxe7Rn6L4frC74JqmYo/lmsp5pOwEzohHE2uhHbGqaOF3FBTD1jCcFiQo9E0cuoq7mB246cCYFcXxRkpiu34aXi2a5miVzAMQmBeheoGSdJmGyeg8l6gaqDucKtn2Y52IWfpelsdc7EmSOX7jnOWLORBpLknglKYNSOZ0gyPgprFgjOShkmRYmPLGdFGa/pZAF4cqTTORqCVeUaJpmrprJEdet45QQbX2kewbumGdYPpeMaFTxxWmaVgl/lZ6loqpRYlmWqEcq5dzufJVUEVFpH9aJC2UYFi5aYiwVhZJoVWg2o3XZNFn/ulEr%2BQ586LQ2q3rdCvYNT5TV%2BXZz3eqdl0sSFvwAuD3wgn8%2Bx3AAYngxCTB6qisKekNgxDENAsyZjJBEMpeFg3ZuGgDDbGk1FLQZNzHHcAAqyoMAo/DECwBFyujoK8RNO1nodEkJQAWgkqADMQ%2BKsq27aYSu8mdRuEusZd1w3bz8sCwQRIkjemBixLFhSxhWHup9fPzvsCsXRF3PbQJZtxRrWs6nTADuotTHKlqGx2sum51hyWyDZ1Q7Tm2fJzqsCcF1wJWHqrBxjhykl4aTFJg6CGpgChBl85wgqtQgp2nGdZznptx4OMIRAQpB3NX%2By1/XFvrgnNP3Jn2curnhxAu9pdd6bZJM8lVKytOmVsMK1fOUuvkwhXhESbPv0wsL%2Bpi7XOsb/Tbti69rfQ/TWc6pz8xFgA%2BulCQEBAkzoEuCjIpfJZuB3Qa14XqeZOnb8uriKygzbpjcGQJD5klJh5bAKMITuk5tDYBgJ2JgKLt/EuncT552uAXFBSg0FBnPlwDa/YapV0EA3O4VBaAmgIOQ9AGwUrNzLAfWmv8ME93ztLNa/cCAEPkkPCko90rj0ZFPQQtdKHUNrnQrwKUZ4gDnm4BeciFFbymAxZWQCYZ02Pt3fYQIz7Tmfkodot8CD3xAI/Ngz9hSsIIR/HBP9uEEP/oA%2BBCC4G0zpggBGkDoFo0wZo9xnMQ73E/sXVhuje6cLCag2xZgiH4RIW4au4iqEfFofQ%2BgAcW4aMPhEzmfd0Hn3iYPJKKU0q0mEVlURNcKFpNqdI2RS95Er0UcQ%2BOVNl6mmFGvd2bRN6RG3q7PpiN1FIM8To0%2BrQL5XxMXfB%2BT8cw2KcWYexX9cFxJcYxDgaxaCcH8LwPwHAtCkFQJwNw1hrCag2FsE2uMeCkAIJoHZawADWARJAog0AADjMGYAAnP8rg/gfnfK4IEQI0g9kcEkLwFgEgNAaFIEck5ZyOC8AUCAJFTzjk7NIHAWAMBEAgA2AQNIXga4UAgGgZ4dAEhRGRJwVQ3yABsABaFlkg7jAGQMgO4UgURmF4OnQgJA8D3y4DIQQIgxDsCkFK%2BQSg1DPNILoSVLtlRpE4DwXZ%2BzDkqrRfKCl5KdSoCoHcZl7LOXct5fyz58SIAeFpfQcW5hkhcBWLwHFWg1gQCQDStIdKyBUoDUGkAwApCrJoC6SMlBYgqtiBENocJtW8ETcwYgcJ5SxG0JgBwqbSA0vnDeWgKbcWkCwLELwwA3BiFoJi7gvAsBsyMOIct%2BB7IODwAANyziqzAqg80Up2A86uDQVW0GSsqTNHgsAqs1ngeFjbSC9uILEb%2BNYW3AEnUYZ5axKFMGAAoAAangTALs8JHIefwaVohxDypvYqlQ6hy1qv0IYYwlzLD6GSpiyAaxUAUxyA2tld9PqmEsNYMwqLV3EHFX2/9vQ81NBcAwdwnguh6DCBGJYYxJXFGyAIGYfh8OZEIwwRYowahIa7QIMWHQMMFElXYZD/QphDBw1RvQ8xpiMZI7YdjlGqh4bWAoG52wJC6o4Ac5FBrOAWtZRyrlPK%2BUCodbgUVrr7meseXutYCBMCmjGBAN5IBJDJBRP85IkKNCSDMJIFliL/Asv%2BfoTgsLSDwvdSiFlXAWXfP%2BWCll/hJDAqsyy2T5a0UYqxbp3FvqiV%2BpJcail5BKChpdQytgnA2gsG7YENlTB7odi4P8lEXAvnCvwEQODEqFUyvvdIR9ihn0qt0KsjVTAtWNqkzJlFvBDUpdNeay1SniuYVK%2BVr5dxHWoGdQkfEuMzA6e9XipLGWEhpepXNwNLqUAGCMKVrgSLo1gkRnGhNSbM0FvTcm7Nub83LqLViEtZaTmVurbW2g9aC3No/W297CNWO9obScgdQ6wQFrHdCk5k7YjTrhLOnYJyF1Loeau9dShN3/YwnuvgBgj2nvPZegtj6Gtyqa7IFryrX0gFWQdz9kHv1w7/SZ05QGBAgbAz2CDVhLDQYG7B%2BDrPRMNFY84CArhiNYbQ0J5YpGSg5Glwr8jcu8M0aaPR5XGu2MLE48J6jPGGP5H40btXNRRPiblb1/VUX5OjetdmErZWKsaBmxpmri33Urb06QAzRnEhs%2BhR5rzZXbOBH8P8iFyQ7MOdC5F1FnAYvYrxwS4lpKTVbY28QLLOxcvWpYAobtfLu2TeTJMKrmnxV6DJ3einCrqcvpOboVInXus6rc9J23ieOBGrJRSu4ZqLUF6LyXsvvIkazfm1p5IyQffxfxf6nbQas/L728X1O59S//PPuXnhqhOV8DoGdzFEB43ltu9d5dl%2Bs05uQwW57ghXsqo%2BzWutDaHl/dbcjptQOu0g/7UHWQGHSh0EHHXLThwRyR3nTgzR14Axw3XBBx13QXwPUJzPQvTTFJ1kHJwkEp0EEbzaxAFSAZxQC/RsBZ3gAAw5yZk4F2HmV5ygxgwSFqwQzZxY1oz8ElzQ212wwqC4xVyaG1wIyaHN24zF04K1z43EL6Do0E313lwE0GG1zNwUJE3WE2Akw9U7z6zkw4GHy5UL2LzuG3xRD33d2qxIC9w9S9V939ywEDykxDzpzK1n38BBVC0RVn0CH8wTwGyT1sFi1WxWFM0kH8Es3BUCERW%2BUkCBS4F%2BTMAi2hWSG738PRTix9SkyFT8NOQCOCLWFXSyGcEkCAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/sensible_classic_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/sensible_classic_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/sensible_classic_plume.test.hpp)
