<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Shuttle`

<p style='text-align: right;'><a href="../utilities.md#shuttle">To Index</a></p>

## Description

`Shuttle` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the variables.

<pre><code>   Variables...
-> Operation
-> Operation&lt;Variables...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the variables.

<pre><code>size() -> sizeof...(Variables)</code></pre>

Check out **Examples** for all the abilities of `Shuttle`.

## Type Signature

```Haskell
Shuttle
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

If `Shuttle` is instantiated by one variable:

```C++
template<auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();
};
```

If `Shuttle` is instantiated by two variables:

```C++
template<auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();
};
```

If `Shuttle` is instantiated by three variables:

```C++
template<auto, auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();
};
```

If `Shuttle` is instantiated by more than four variables:

```C++
template<auto, auto, auto, auto, auto...>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();

    constexpr auto fourth();
};
```

## Examples

- We will create a `Shuttle` with variables `0, 1, 2, 2`.
Then, we will transport the variables to `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Packed Vessel ****/
using PackedShuttle = Shuttle<nullptr, 1, 2, 2>;

/**** SupposedResult ****/
using SupposedResult = Operation<nullptr, 1, 2, 2>;
using Result = PackedShuttle::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Shuttle`.

```C++
static_assert(PackedShuttle::size() == 4);
```

- We can retrieve the first four variables of a packed `Shuttle` via regular member functions `first`, `second`, `third`, and `fourth`.

```C++
static_assert(PackedShuttle::first() == nullptr);
static_assert(PackedShuttle::second() == 1);
static_assert(PackedShuttle::third() == 2);
static_assert(PackedShuttle::fourth() == 2);
```

- If a packed `Shuttle` contains only `size_t`variables, then it inherits the corresponding `std::index_sequence`.

```C++
/**** Packed Vessel ****/
using PackedIndexShuttle = Shuttle
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2),
    static_cast<size_t>(2)
>;

/**** fun ****/
template<size_t...I>
constexpr bool fun(std::index_sequence<I...>)
{return true;}

/**** Test ****/
static_assert(fun(PackedIndexShuttle{}));
```

## Implementation

First, we will create a helper function that is responsible for the regular transportation functionalities.

```C++
template<auto...Variables>
struct Payload
{
    static constexpr size_t size() { return sizeof...(Variables); }

    template<template<auto...> class Sequence>
    struct Detail { using type = Sequence<Variables...>; };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;
};
```

Second, we will create a helper function to retrieve the first four arguments.

```C++
template<auto...>
struct Payroll {};

template<auto First, auto...Others>
struct Payroll<First, Others...>
{
    static constexpr auto first() { return First; }
};

template<auto First, auto Second, auto...Others>
struct Payroll<First, Second, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};

template<auto First, auto Second, auto Third, auto...Others>
struct Payroll<First, Second, Third, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
};

template<auto First, auto Second, auto Third, auto Fourth, auto...Others>
struct Payroll<First, Second, Third, Fourth, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
    static constexpr auto fourth() { return Fourth; }
};
```

Then, we create an interface inheriting the two helpers.

```C++
template<auto...Variables>
struct Shuttle
: public Payload<Variables...>
, public Payroll<Variables...> {};
```

If the variables are all of type `size_t`, we also inherit the corresponding `std::index_sequence`.

```C++
template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
, public Payload<Indices...>
, public Payroll<Indices...> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxBJmAKykAA6oCoRODB7evv6BaRmOAqHhUSyx8VxJtpj2xQxCBEzEBDk%2BfgG19VlNLQSlkTFxCckKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzGFkN4sDcTKC3MhxugsFRYdhgeZwQxIV5obC3F5HLRCABPVHon7/SkA4G/XY3ACSLBS9DYgiYDU%2BB0BtKp/0BNMON2UTGJtFQTHQnP2gIImCZBlleKYBNQADp1QA1Fp4JjRegKMmXcbELwOIUisUS9EAdislxuDpus0cyBuaAY40wqhSxCdeAAXpgAPoEP2BiBLGG2m7ETAEdYMMOYVBUdWqiBa4g6vXvJawixRu7ki6Om6y%2BXszB48vMytKlVp1FugwKD5CTAARy8LyroLR9sdxtNoYezToUYLXgyRjLxKeMNBdxu7a7Pbxmez%2BsbffzhfzxdLNYVvbcR7rcOVRG32GbTFbaZX3ax70NJcdU7CwBuACUmOPYUuo5/rQeKPj2CjXiAIAEHOvZ2kC1pFqC8ECrcwrEsQni0FKpzAmeioXg26qvkOZroZhtDYSYtrUUhKGXPhJ6XqgNwAGJ4MQ4ykDczFpgA8gQCBxAaO5GgQJpkSKFEgXC7GcQQ3ECUJnHXja8Gls6eCuu6nrer6zE3DQ8kRhOMZxgmbEceMu60TadHFox9ZEJZ8ncQZ7buugblEaqSnCSR4nDuaGFYXiclccumCeYpgnCaplzUepg7NC6boCLpPo8SqhlWQQJmJWZ8bEIm4UEDZiHAhpKVaWlHqynpWXOUonn5dGsZFYmHkCOg5VFglFXIQ5cq1gRbgGaV3nOV1DBeY1LEACoIBxs28eqfmcQFEmhuRoWybl3HTbNi3LTFykQcRokIUlDqadp6X1ZlBlGeMrUFu1Fmlb1lXJeyNU6Q9%2BnZc13WvYVFmHV9A43dVd11V6j3ZYJy2g%2B9xU3MdxA9che79fZCUMcNx5OSxE1zZF0VkxjK3ZaxaytAgk1qmtsUbZdpHbVJu1uKTh3cVT3G0%2BsgmnXFF39ld33Q79sMZYDznPXlkYFajJW5ZDb5S6l/3w3LLHAzNKPmWjEPY7ZUNOjDtWy2TSOY4bHXo0tmPq1V0tWwDZP8ELCD2x9dOCertmDfjVyCkICAEgQ9A4TKhPnmNPkbrq%2BqbUF4eR/QwIgDcKReHqNXoZaWNuEnObnaqr7cbn%2BeujtlHrtqyfvNeE5B/RFyOXCGSBiGab0jNWkvmzgVmunBBRye/f4Js5evtn1dEq6iJQWEWCqEGSirs%2BeJT4Ps%2BXVXeeL8FRc7wPM/xRch818F0ln9Pzdi63A3tzyvLHNygqlTc2CqKwzKYBjqhd%2Bfx%2BQJTBBCKEgC8Tuk2CkAgIlxbALpHxJ4xBfoCCAQTCso1VoV2HltG4qC4gYIYPuEOtJzTIAANaYElBqd4dgsEXA/DOYUNC6FjwnguJcXDM5wgYF4Si8CyA3C4NxQINwzBkmDkCCktwhBeBSIUOh353hCNDF8YErCvyKOUekVR6jaChgAkQtBpC8SCOEeJbi4ipESJkfBHRP4jEmMXFQ2h6A%2BHsBAL%2BOgeJiHoIaI44slD5rvE0VyYEt0gx3iUK0CAy8QAKFYMGO8eI1EKA0QdJRKj0CZI0aiPMsjkEgI/sg8m3Uf5/3lIArR8iyknDARcGJcS4h5XYZ47xUFu6YHyouUxkhimv0aU0ipVNqn/2jvU0OozqQh1aa2dpEBOmcIjuPcQIAFb9KQkuKxtARHDOiTDWJSyEmrK8esiePSoogyVgM9xXAjliWlqc%2BJHSmAcMuRnHxtt0A7NMWYZ5LSTltPOZ8rpVzNle3pgC9xQLyFyNmXMmZlDBb00mbU5hb85nNMoRcm4DClnYRmc4i5U8vTeJ4cuKFVYEpwklhbV5ohrJdwDMGMqfYIAaBWIymJLLOVuF6SGVEEAnmkD5ScgVeJhWcuwBAIFErzb8rvIK2VoqEX0rRCUhpdIqBeETDMzuQr2W93VPSV82sGrRFQJ4QyBrEkEHQCvGaXoN6difJsHe148z9QsCrMsJo4JmyRWEiJzDFnvOoA68lrrVDeMSrRJYwyOArFoJwRIvA/AcC0KQVAnA3DWGsE6OmmwYRgh4KQAgmhU0rGoSARIkhVQaAABxmDMAATg7VwRIraW1cGtNaaQ6aOCSF4CwCQGgNCkGzbm/NHBeAKBANO6tObU2kDgLAGAiAQBrAILnBSFAIBoCZHQOIERUmcFUC2gAbAAWhvZIG4wBkCuikKqMwvA6GEBIHgZ14j%2BCCBEGIdgUgZCCEUCodQa7SC6HEQAd3QSkTgPA00ZqzTWvNnA%2BIEgPTcFMNxr33sfc%2B19Yim1mBuBADwp76C%2BgxE83gq6tArAgEgE9KQz1kCPRxrjIBgBSECDQYxwlKDREw9EMILRiQod4JJ5gxBiR8WiNoKKq7K0ntZAQPiDBaAyZg1gaIXhgBjUoku7gvAsAsEMMAcQBmOJqbwAAN3eJhr0UUCRbErWEWUI7c1EmiOgxTHgsCYfEngCdFnSAueIDapQDxrNGCJEYGtKwqAGGAAoDUbx4PEOzZWwDwhRDiDA4VyDahMNwf0DZlARbLD6DwNEJdkAVioHgVkczd7EQAVMJYawZg50xazFgZrEZuiOecBAVwUw/DiJCGEIYFQRjiMKJkAQM29CrYaPMYYVRxsOF6BMNongOh6DsBNxoR2dtLb27MSYJ28jiLuwMBbCxlsrAUKW0DaGOCZpnZh%2BdhHb0PqfS%2Bt9FGqO4B/fRitSwmOpZWEJCUIwxv1skKCVUHbQRDo0AESQN6p2JBvR2/QnAx2kAnaCLgqob1cBvS2jt/ab2Np7Vjm9/2YPzsXcuqtqWN3brY7u3DBJyCUF43Ri9bBOAtBYE560d6mC3hnFwDtqpqe5u/UQYbehCvAZK9IMrSgKswd0IERDTBkMWZ%2B392dvB504f3QSfDVAgfEafZCGzYjVfq6ozRzjdHy2giBfDtdrH2OoFo3EUXx6I/%2B5GB7owKuuDTuE7KTiYmJNScU7J0g8npPKdUw4HPmnGDad0/p3NhnjOmdoOZytVmbN2crw5g7LnzMa9UB52UOefN1EwwFoLxIQtbFzeFyLlaYtxcwAlxvn4%2BfpaYJl7LmBctPHy7wXXxXQMG9kOV6DubTfVZS71qw9WAujda%2B19KnAutOp63ViwA27dDb/a5lr%2B2GguBmhtubM1ruLBW3SDW2yAe1m1SCAO21e12zOzqAuz6Hu1yDAPOwOwEHgJezKGgKeyOx/1sCuygJuwkA%2By%2B0INJ1%2Bww0504FdxByVy/BVzV2bUh3wC10D0Y151D0R0wGR3iDGxHXJ0p1V1x2tESA7UHVBDx0fXEVtywwXVsB52Y3XU3R3T3QPWj3F3PUvQ4BlxIxYAUCc1dCczoOPHGC/SYN/X/XAyKxAwkB3wgyN33x0BAFBFIHN0t1Q1IJtwB2w2F1DAI1UG0N0P0MMMrHGF91jy40D1BDhzYJYw3XD0j24zFzCLoxAD0OUSDAMI7SDCMIICDD8INzoDTyXQgHExgzz2zyizKKUxUzU2Lwjy0x0z00wyrxMzEFrxzwbySxH0sxb0cDbzc072QE8x70ED7xgwH2k2HzCyzHH14EnwMRnySzn1Dz4Ayyyxyzyxz03ysNK13zsMq0cKP2MAfwaya3gEvwaHM22GXhP360GziGGzfzG2QM/ym2/1AL0HmwwIIMAKKCyBwK2yyH/2Ww/0O36BwOeNBNaCBNu2wPeKwLmHwIAKIPWE2BIJHQ8IoI4EI38L0JuAyNVGyMYOhxYKiPkOTVICRywG4J%2Bz4JAE7VVFBFBESF7UkGTw0EZOtHpw5znU4G5xXQR1IDR0SExwHWtCnRbUkG7S4DbTMHZxHVBHIJ5JkLJJ%2B0/W5Lt15OiNrWi2EiyH8CAA)$Done$

## Links

- [Example](../../code/facilities/utilities/shuttle/implementation.hpp)
- [Source code](../../../conceptrodon/shuttle.hpp)
- [Unit test](../../../tests/unit/utilities/shuttle.test.hpp)
