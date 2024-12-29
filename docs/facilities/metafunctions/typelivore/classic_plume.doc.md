<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-classic-plume">To Index</a></p>

## Description

`Typelivore::ClassicPlume` accepts a list of elements.
Its first layer accepts a list of transformations and returns a function.
When invoked by an operation, the function instantiates the transformations using the elements via a process similar to pack expansion;
then, it invokes the operation by the type results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;::type, Transf<sub>1</sub>&lt;E&gt;::type, ..., Transf<sub>n</sub>&lt;E&gt;::type&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;::type, Transf&lt;E<sub>1</sub>&gt;::type, ..., Transf&lt;E<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume
 :: typename... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct ClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct ClassicPlume
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
struct ClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::ClassicPlume`:

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
using Result = ClassicPlume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = ClassicPlume<int, float, double>
::Road<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = ClassicPlume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct ClassicPlume
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Cosmetic>
    struct ProtoRoad<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct ClassicPlume<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Element>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJmSbgIAE80oxWJgAHRo7CvRgEBTQ7AgybELwOO5uAwKLLIZT5TAgkyBKzXO5Mu67XZ3ACyXlojhemDuGPBWJxjOZrI5XJ59BJsiYEQSwquzLuYIhHxpMJVLzV0NhCKRbDRKNxd2QZIUho8CjYjmQOOSeJFTIJRIId2UxFQRAASqgmOg7iClXSLAHHUrleCtVCNZHIerdYjmAa0cbTUxyXcAPKI4gfHK4wPhp0EQnEgAimFadELReDNaLzK8WSMyr1AeSZazObzAh18MTyOlVsreFtOoFb2xuJAIH7qJT9uhDMVDbpZaXtLDSs1cb7se1Gr1SfnRvtJrNhquwGImEFgjtDpXRabEWAdx9fvbnYrVdoOqvN53tihrTrOeobmGa4QcCYZipy3J4Ly/KYve9ZigIfIeO8crEPWO4HrC%2B7Rgm%2BonqmZpDtao4FmGzrEu6nqoB%2B6A6paVGmIukH0qGT7hvhxH8fGc7HiBZ5phm2YJD2DA0bxSp0a6P6yn%2BW7MnWqnPs2b5zl%2BXZSU0fZHoObEjhxbgTkKoFzqJeLJMuDYBoE652ZucnMoJe6qgJRnJqe2Dnum5pogBt6Tg%2B9ZKi%2BLbMbpSnVjCIVAUFfkznO0FBk50F4URQk5YZA6%2BeRgUWpk7HhWGUVvjF0Kdgx3q%2BixMImTayUFi51xQe1MGgnlh4FXyFmCLJCkkmao5Uj48aDQQsnqbxYqZpEyFAWhbLwZKmEyjhCrbr1hFeUJPlkWJF5os1o7lbxI11UxDU8RlIYRe5e0eX1pE2QFEndgZnFucWpaKZWylPUyc0OZFWmtoiumSbmP0kcelGmXa5koTN9qpXqNnpaumVdSDEYHZ5UaHf1H3icliVhbJDmVe%2Bd01XccV/gl16hUKNmY4iOOg3jy7ZUTMaCwjyLk6dKLnWOv0Q6%2B9OfozN3MaxpXI9j%2BN865fwAtr%2BxAlrdwAGJ4MQkz8qorBId8IJazr/xArSKQRKaXhYO2bhoAw2xpFOv3W8cdwACq5gwCj8MQLDSQoXznCCr0i2wy2TsNJYuncABaCSoAMxCOSGdM6Yz01Lo5zn89ccfCYORe/SNi2YNnud3PnbaF2j%2BzF51Zc9cLlcJ9Xj4jQHADuWdTFHwZN5DBcdonWKHB3Gsdb8/uw9J0eHECFdHdj1y199%2Bb48v9xCF4aTFJg6BepgCgSuvusgnTJ9n5kF9Xzf3Iw/vvYwhEBCkHcv99j/0Ae3Rch8bj%2BzfrfK21w6ZQI/ozUkgVxrUh1L/WSM4lYwgzh6bO/8654MDiPbOl1MENR1KvH6tku76wDtfV0MCrjzBtAAfUCgkAgEBJjoBnAoZEbCUbwL/ncJ%2B59L7XwlLiFYWUj6221nrf2QhMAe39Ngc2EI%2BSMJtnI049tZH7BEafMRQi75AkfkYl%2B4j34EBYVwT%2B%2BkD5uEAf/KgtBfQECAXcdAGxYj0FAdQzWkCJEf0YXA4JNi7GILGpSVBP9BAuLcR8f%2B3ivC%2BPVI%2BMhfoKGRGzhgkAWC3CUIPgEpeED7h0NNow5ho4BFKHaFwggPCQB8LYAInUQjbH/1EZYjpXApEyLKTowEftykIGNqo9RlsY76KGYwkZhxDHPyUFY6B0yrjmKWa/cJLCzD2Lho43%2BCT3GeJSWk%2BeYCaFBOsaYh%2BkMOm7KicgmJk00HxLuK49xySfH0DyQUnBo82j4JyVMf%2Bw8AUm1%2BeQmERTv4lO6rQ%2BhNzd6tFYew%2Bp3DeH8PTO07ZZgukWOWfc/pdkOBrFoJwfwvA/AcC0KQVAnA3DWGsHcBQGwth8nMMkHgpACCaFJWsAA1gESQKINAAA4zBmAAJxSq4P4cVYquCBECNIclHBJC8BYBIDQGhSDUtpfSjgvAFAgF1bymlpLSBwFgDARAIANgEDSF4P%2BFAIBoGeHQBIURkScFUGKgAbAAWn9ZIO4wBkDIDuFIFEZheAX0ICQPAPCuAyEECIMQ7ApCpvkEoNQfLSC6BTUPXMaROA8DJRSql%2BbDWZmdU610qAqB3D9UGkNYaI1RpFbsiAHgPX0BzpyrgKxeDmq0GsCASB3VpE9WQV1U6Z0gGAFIPFNBuTykoLEfNsQIhtDhGW3g27mDEDhJmWI2hlHmu5e6yci1aB7otaQLAsQvDADcGIWgJruC8CwBHIw4gH34BvA4PAAA3a%2B%2BbMCqGUc6nY3Lf4NHzbQPAsRczHo8FgfNJY8Baq/aQMDxBYgvwrL%2B4ASGjB8rWK4pgwAFAADU8CYCHpJal3L%2BBptEOILNbGc0qHUA%2Bwt%2BhDDGCZZYfQyGTWQDWKgb2ORP2Bu4TVUwlhrBmANfh4gSbwOSd6BenILgGDuE8F0PQYQ5RLDGCm4o2QBAzD8JZzI1mGCLFGDUHTwGBDZw6EZgoKa7C6Y81MIYZmXN6HmNMbzdnbCBec1UCzaxWWbG2BICtHBKV6urZwZtAbg2hvDZG6N3bcAJoHSkIdI6KNrAQJgP0YwICCpAJIZIKIpXJBVRoSQZhJD%2Bp1f4f1Ur9CcA1aQLVXKUT%2Bq4P6sVUrFX%2Bv8JIOVLX/XpYfYa41pqeUUatbaid9q63OvIJQed/bvVsE4G0FgIHAiBqYAFFsXApUoi4KKuN%2BAiAaeTdm9NnHpDccULx/Nug8XFqYKWr9KW0v6t4DWvbDam0tpy7dt893HuiruD21AfaEgBhSGYYdG2LXjsnRj6d/aDtuuJwutMRh7tcF1ausEJsN1bp3ce/dpBD27tPeehwbPr1Ylvfe2lT6X1vtoB%2BtnP6hP/qF8bXTYHP20sg9BsEbP4NqtpUhlDu70M7FpVhnD3L8OEaUMRqXr5NtUZo/RxjzG2fca%2B5mn7sg/t5v4yAPFBhyNKasKJzXEm6t0pkwIOTCmOze5U2phI72tMB78%2B5vwEBXC2ZMwZmLyx7MlByMnjPjm08Wbc00Tz2eC/9Gi8F2LrmwtefyJFqveeajxbZUlodA3UtVpW5l%2BHbaqdI4e09jQaOitvex1yvHo7%2BWkCqzVxIAe1VDZGw99rgR/BSuVckDrXX5vLYNZwNbZrNvWrtQ6%2BtZOjtep9Rwc7baWAKBA5GkDyO4yTBe8VpNeh7cccd9ml3fHaW6FSMDqDuWq3hDhlhwLWo6s6ncI2s2tfrfvfo/mqKbOjpjiVskMkGPgfkTqgafhTv2iAHfmfCwg/lKiwk/jYqoCGnwHQAziahAJug%2BhzqzrhkwSemeherzhjjegwHevmsLq%2Bu%2Bp%2BtypLn%2Brrt%2BrLsBvLhBlBsgDBqroIAhg%2BprqhnCDrphhpgbrwEbkRuCGbuRgTnwAYFbgxkxomHbrIA7hIE7oID/gDiAKkJ7sJspr7uJvAFJkHiHJwLsBiuHpYKplDupppv7vFg0P5gnknhFinugPXnoFZk0MXnETkDEb5qEfHkXpESkX0AFgsOXunlFoMMXnXrkXFusIlpmuDu3jvhwLAaGjfnfncCQSiOQYPq9iQCPmVvjmOpVtVlgDPilvPu7g9ugf4PKvNjqugYEJNtvlDrvrYOtuPisPVpIP4M1kqoEDqmKpILKlwBKmYEtmqskJUTMUap0RPmqrGtMXSrMQsWsPhlkM4JIEAA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/classic_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/classic_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/classic_plume.test.hpp)
