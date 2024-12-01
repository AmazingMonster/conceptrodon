<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateTransform`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.
When invoked, the function transforms its arguments that satisfy all the predicates with the transformation and instantiates the first operation with the result.

<pre><code>   FirstOperation
-> Predicates...
-> Transformation
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>i</sub>, ..., V<sub>n</sub>
-> FirstOperation
   <
       (...&&Predicates&lt;V<sub>0</sub>&gt;) ? Transformation&lt;V<sub>0</sub>&gt; : V<sub>0</sub>,
       (...&&Predicates&lt;V<sub>1</sub>&gt;) ? Transformation&lt;V<sub>1</sub>&gt; : V<sub>1</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>i</sub>&gt;) ? Transformation&lt;V<sub>i</sub>&gt; : V<sub>i</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>n</sub>&gt;) ? Transformation&lt;V<sub>n</sub>&gt; : V<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateTransform ::   template<typename...> class...
                   -> template<typename...> class...
                   -> template<typename...> class...
                   -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateTransform
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to elements whose value results are divisible by two and three in the list `Monotony<1>, Monotony<12>, Monotony<2>, Monotony<6>, Monotony<15>`.

```C++
template<auto I>
struct Monotony
{ static constexpr auto value {I}; };

template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

template<typename Val>
struct UnaryMinusHelper
{
    using type = Monotony<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

using SupposedResult = Operation
<Monotony<1>, Monotony<-12>, Monotony<2>, Monotony<-6>, Monotony<15>>;

using Result = Metafunction
<Monotony<1>, Monotony<12>, Monotony<2>, Monotony<6>, Monotony<15>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For every element in the list, we transform it with the second operation if it satisfies all the predicates.
We will do this using the following helper template.
It decides whether a element shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<typename Element>
struct Hidden 
{
    using type = Element;
};

// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Element>::value) == true`.
template<typename Element>
requires (...&&Puberty<Element>::value)
struct Hidden<Element>
{
    // `Hormone` is the transformation.
    using type = Hormone<Element>;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateTransform
{
    template<template<typename...> class...Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class Hormone>
            struct ProtoRoad
            {
                template<typename Element>
                struct Hidden 
                {
                    using type = Element;
                };

                template<typename Element>
                requires (...&&Puberty<Element>::value)
                struct Hidden<Element>
                {
                    // `Hormone` is the transformation.
                    using type = Hormone<Element>;
                };

                template<typename...Elements>
                using Mold = Operation<typename Hidden<Elements>::type...>;
            };
        };

        template<template<typename...> class...Agreements>
        using Road = Slash::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAEA7KQADqgKhE4MHt6%2BASlpGQKh4VEssfH%2BSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7BwEmCzJBpsm/m6b27uY%2B4cAnsmMrJgAdPf72ADUyAYKCk8A8lfETI4CjxMGgAggoCMQvA4nh5gMxNgAVX4MBT8YgsIHAkwJKwgp54p5HHZ/U4HQknM4ES7XNj3W6PF5vBS05RecqUwG4/FgiFQ5TEVBEABKqCY6Ax%2BKeWJxwIlEu5kIITyEbwQ4tleKlavVErJxIpWyJe1JVOYNIe/meryY7yeAAkSCwBCTsFrtXj5bz%2BUKRWLOW6NdjXf78bqjRcrqbME9sPQ2IIOTLg7KPYrbXh0FgGJK/UmA9Lc26vOkjASqZL/AARaOxxgEfb5gsBiv1jFBpOhknh6lRmNbWsJxt44iYACOXjww4%2BEFp5gAbHOWWzzmde3G6xaQCAAG5iLyYeZt4Mpu3pzMrmvxi2H/2anODp4AegfktnGntaKdJlfTzwHwICCjcFDBRB0/kyOk70HIswmAUsrnLKt30dcJzz7S8XX8BtGyxZtMNbSDgw7CkTRuWlV1rBQByg4tYIAWU8dAEK%2BH4wIBY0IxuE8M0YVC10ojcQEpK4ZyvPCCNlHCW3EySxMxcSiNJA1yXY7sRMtRlaWBYBhzQgh%2BJdcToJLYVRSY5VrSQQSlOJJ4%2BQFVATLFA4tJ0vi1KkxMmw810FMOaywyE1TzXU60mXuFzMF0/TXSM2DHKYuzvVFM4Iqi9zZJk6UMQfAAqPL8oKwqH2ygqnnhTAwQ%2BAripBXLCvq/KarkzEzH8MJXi8LByzcLxHFoQhlyvEEMV8phetQJ4AEkE2PeiGHshhl2G7EnjBMDkBeAQwUwVRkmIJ4xqIJ4d28KMpWmhJcIsSVLu82rSorPAt1/PBonoCxznhAB3CbqpG/zO0CyMngANTEGbwQVJ5Hue9I3swD7vtQVtAxzNbHA2tBkU2Xb9uiVBPGO3dThzKUwdoTcTr3SUzAAVieMwEP2KsNEylGrvw4E6ry6Gnpe%2BHEYQHSnj%2BkFfKBzjyYhnlFRh/n3s%2BoXIpRrDVoaDHNuxna9qefHCapknPJuixycp4mafp/wmcrJ5WdujL7ay%2B78qeORmGIc5aLCIsRca/7jj1FTgalobQUhqE3caT3vYUW1MFoH4VZimi4LOm25oWwa3AAWlN7dicBB2OeGsWAeIjizVuYFiGAaKQVi133ejhgfeZxuo69lvY/jxPnJrsK6QEwK7q50rsFUVgdijUXgXFkjK%2BlqHvjiViGBHueK7ucL%2B4TBvaMwBoqC8BhOizNuYThTBEWA1F0QOZffn%2BNfQ83RyzjluGFaR0hedh16v6Vs6DEr8fRnEjh7TuRYEybnorQJybhq613Sk7YEDchBeGSKkJQ6BBQVS8LQRUbcH6r1bAcDORBFpnC4I8H%2B5CBBZ2zlwMwNCnh0MoQcZhFpaECEzmcbO84uGsJ4RQrOXBaaFwwighuuCFD4MIenA%2BTAj4nyfqQtwbDREsI0VQzh2BuHzREWcXR%2BjeEHAEXooRBj6FUPEaJSRnN0Z4GQAAfVCnEAgEAwToE3AoG4rj%2BJuBkXIn%2B6DMFpEwDgvBBDHgHkwhwRYFMOC014H4DgWhSCoE4G4aw1hVrLFWGdVqPBSAEE0PExYABrEAtMzC3ASGYSQAAORptMNAAE4akaFnI0wIiTJC8BYBIDQGhSCpPSZkjgvAFAgBGaUtJ8TSBwFgDARAIBlgEGSL1cglA0DbDoHECINxOCqEabOfhkgnjAGQBtKQtwzC8AiYQEg6Y9D8EECIMQ7ApAyEEIoFQ6h5mkF0FwUgX1fjJE4DwBJnBkmjLKRkzgnxeqbMVKgKgTwTlnNnBcq5NzJB3KeBADwez6D7XMP4Lg8xeBzK0IsCASBdnJH2WQCgEBGXMpAMAKQZg%2BB0E2MQaZEBojwuiGEKOkLeCiqbp8aI2gahzOKbstcnwGC0HOPCrA0QvDADcGIWg0zuC8CwCwQwwBxCAvwMOWoW4Krwp2jUXq6xilhE2Ik9J/Voi/A9h4LA8LwR4EGYa0gNriD4yUBWLYpr%2BpGDKYsKgBha4gzwJgL6y9UnFLecIUQ4hvmZr%2BWoeFwL9CmpQDkyw%2BhXrTMgIsVAyQn4Guzl45mphLDWDMOMkNxB0y2urbYeO8rMguAYO4TwrQ9AhGmKUcoegsGFCyKO3IILZ1Pz6FOwYIKOhP26KMBdfgN39tPtuqYJQBjxA3ZMMYe7hg9FXaeiQiwFD5LWPe/QMKUnwomRi055zLnXKeLcxmEBcBPLJUUqlJTY2LAAqKQYEBKkgEkP4W4bTKiSA0JIBpr4NC01nG019HB%2BmkEGRS24s4uDdLaY08jtNJBiJQ7OOFgKJlTJmRB%2BZdKVn0rWcirZrL2WksOWwTgjQWBbgSNnJgDJTX/rabcLgtx0mPKIF27xILM0fJzdIPNSgC2At0DysFTAIWGuhUk99THEU8dReikTYmJNSZLFwWT8mNCEuJUy0lNN/BmHAzShZXH%2BNxG2Wy1AJLBi2fE1aIwTmuAjJoAQuIgrhWAqleKoNqWPYyrlQ4CVpAlW1hVWqjVmAtU6r1Qa4pxqo3rHSZagdNqDWKdUA6zYuWXXx3hR6r15wfU1epV2wNxSQ1hswBGk1Rho2gHY3wBNCgk0prTbl9T2avladkPmgF6T9PFpjS2qw5aPVVrgxkutmQG1NsrHtttHa4gqZ7cdzdg6ICuEveO4dt7ZhnvyOkJ%2Br2l0FBXZOu9%2B77BbovbuvQj2uiTA%2B9O89PQ/vXqaLD9dD6n1fNM7CsZvBP0Rfs1F2CTm5MKcJcB5TXnKXUsg6QaDWB4jHb6QMgIsn0MJFpm0hICR/AYckNikF2OEWTNsKxvzHH4BcfWSi4LgXiCCfWCJ7FTwWAKC3BtLcROThggefgZTLy1OyA06tn58gdObZ0HkQzxmoX4axx%2ByzGzepPDRQdNEivleq%2BOhr4kYI3OhY83ELz/hfOxsWQyv3zLpfh9JduZAmDnHq7ac4zXBBXGu603yxLlBkvpIy%2Bq9LYrMuyvlbl/LghCt59qyV7VuraD6ty1VibfXSB1etbawF9rkCOra4IDrgKutR1636gbuXhvhLG1GmCIf41METcm1NEYlsG5WxINbvzTeFryAYXbZabCHfgDW07W1OAPi8aW1tlh20487d2o7D6D1PyHSOnIV6J0ns%2BzOgHmREfLsyCjr7UOGAj1EcACj0/9Idwdn9wCb0gd39KUlgVhn04DElbcLMOAXcWA3cVc1cvdNgfcgMdcSAKdg92MoNMAYN6dTNCNBkzBZN/B/BaZWlaNhk6CEhulGNxlOAWNZlqcqlJAEg7k2cuApA2lWcUMuAkhEl/BzMOChdRdTN7l2CcdOC2NaVFgQ10hnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_transform.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_transform.test.hpp)
