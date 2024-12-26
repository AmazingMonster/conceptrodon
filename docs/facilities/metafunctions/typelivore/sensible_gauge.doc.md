<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-gauge">To Index</a></p>

## Description

`Typelivore::SensibleGauge` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by a list of transformations, the function instantiates the transformations using the elements via a process similar to pack expansion.
Then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transfs<sub>0</sub>&lt;E&gt;::value, Transfs<sub>1</sub>&lt;E&gt;::value, ..., Transfs<sub>n</sub>&lt;E&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;::value, Transf&lt;E<sub>1</sub>&gt;::value, ..., Transf&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge
 :: typename... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensibleGauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= SensibleGauge<std::integral_constant<int, 0>>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddOne>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensibleGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Elements>::value...>;
        };
        
        // Multiple Elements
        // One Container
        template<template<typename...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Elements>::value...>;
        };

        template<template<typename...> class...Devices>
        using Road = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename Element>
struct SensibleGauge<Element>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Devices>
        using Road = Operation
        <Devices<Element>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDM0gAOqAqETgwe3r4BwemZjgLhkTEs8YlcKbaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCcnSCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMSTcBAAnqlGKxMAA6VHYF6MAgKKHYYETYheBy3ISMTKxegAcSYXmAmGBJkCViutxZt1B4PedOh7OenKhbmpRFRyJxt2QBgUCluAHkEcR3tkccDWbd8YSCLdlMRUEQAEpMOjK1kMpmXFUqnY7W4AWS8tEcz0wt3RYMx2OZ5pZlptdod9FuHjeEQS7rNnrZYN5kO5kYhXJh8MRbGFovFTElwoAIpgAG54LbYpK4j2etVE7MtQ0l80mo3h1leTJGNmJ25QzMyuUKgR1%2Btt6HZvMF/ku15YnEgEA5sReFGopVJU31hmZqFL8O9i1W232vCO50YwSh%2Bve6WRAOyA2RYib1k8uP8%2B987mJ5jJ%2BdFsUSqWD/Nc4thqWBAEuWmCVrQ/K/lsSrViqtaweGjYRMALYIv2Haygk3YMLenqQbmf4joe45FpO07eHOIpFmuuFtoEq6LvSCEsk%2B0YwrGz4Jgib6Uam35ZgRw7UcxtxIc2uqoEw6DobcFYGhBA6CZgCgpqRIBwgiNHViuWlAtWrHxgZ/KCqgqnYF%2B6YqailzAMQmCukeMGAaJTYofqdAyVqOqoO5CluDZdkOViZm6TpjFXMCRkvtxSIHkFTllhqJIMGSlLUrSRHxcJQKMr2UXsRybEmWZFmSp2WGNE5KqJZq2p6vJvbwc5W4yueo6YrR3o7n6TqBpW17HuG%2BXDa%2BSIlWmGaolBylVYhrm3BJUkyZh8qVSJ%2BFDjN0LtYIE5TjOvHUeFzlhaaeUcWx%2BXFR%2B5kTVZyIBfZY6FgBKpiW58meXVPkNdCj1BfdC5nfRoU/P84NfMCvx7LcABieDEBMzqqKw%2B6Q2DEMQ4C9JmEkETil4WD9m4aAMFsqQkQBUNHLcAAq8opfwxAsNhUroyCF2GaNbBxWOCXAeqtyXOg6AAFoJKgbYRYyUvOXMjjIGKAgTJgqipMQtwmbc5Gzo1jI7QQZEHadsunUxHOFVzMU8wb/MgRqwvoGedLSxYsvVS0CtKyloJqxrWs6y7J368RRsUW2li3FwJv0iDx2RZzj7c06tvZTVju0wA7qgsdu728v5t7Kt%2B5rXhENrxvaSHQVh7OEdu2YMfSwxZ0Ywc5WrdknxnAnlvGWXpk3XiAtEit2Gg9cNNCF4qRFJg6C6spvrdwcgLvcSM9zwvS/2stXaVdCGikFHx%2BN0dreT3ci8KMv7Pr9fy/0kkHbJalmBUjS8YTOgk4RKCtliAAPqkzmLtaEf9j4aAXABScvl%2BRjwPjAkAi10D8kduLbUx9HbOywSLLOOdz7m2hnTZSGp2YF2QIAyyCQCAQG/pOBQSIqGFjcA/e0x9p6zwyPPNhBAcTLAntDTGfxATEJJKTaS2AUbgidOzIRwiTjYzbjDThW9eErz2GveaqjuHbxvvaQBXA94VUVNCLgp9j5JCBkQmm6i77zV4YYmSr88DknfuleM%2BcCA/xAH/TAADaDAOVi0MBbgIG3CgUWUgXifF%2BICUEn2hg%2BHgMEMfaOUSYm/0EP4%2BUgSQEhOSWE1Jtwz5U2yrA36bgEGmKQSgtBItnbWIisokhSNyGe3zMwpQbQ6HeIYUw9M/JHHmI3lwpQejfSGP4YIhR/xRE01pggBGkjpFox7so2Z7NqZ3B0eMux6zLjr12TwneBBAFmGMZ3Hsh8LG3EkE0vSl9277NXsCe%2BpzznONJK4tKn9%2BSZN8dk%2BJ%2BSkn8nCZE7A0Tqz0MBf/XJCTQGFPCekyFAK4nwpBaE8JpSn61MqdU65tTJKoL%2BiLDBqBcFO0iJS/BDztnt1pqQjRgIKFdJob0nxjC2DMKGR8swHDN66McaUgRi4OCrFoJwfwvA/AcC0KQVAnA3DWGsKqdYmwnTmCSDwUghs5XitWAAawCJIZEGgAAcZgzAAE5rVcH8Ba81XBAiBGkJKjgkheAsAkBoI%2Bsr5WKo4LwBQIAj56q0KsOAsAYCIBAOsAgqQy7kEoGgJ4dAEhRCRJwVQ5qABsABaXNkhbjAGQIrKQyIzC8HnoQEgeAf7mP4IIEQYh2BSBkIIRQKh1D6tILocxmd5SpE4DwCVUqZWaF4IG6UZdE0alQFQW4OaC1FpLWWqOpqLkQA8Gm%2BgGstVcGWLwcN4rSAQCQKm1I6ayAUAgJe69IBgBSH5TQe0IZKCxEnaQWIERWiwhHbwH9zBiCwmlLEbQmAHAAdIKmscZ5aD/t7VgWINIBS0FoCG7gvAsAsyMOIJDCNIOOBzMpL9qtINl22Dqvx7r5W0FcfKEDHgsBfuAngb1WHSAkeILEbh2ZcPAHo0YSdqwqAGGAAoAAangTAmdMKyp1U24QohxDtqU12tQX7%2B36EMMYFVlh9CuJDZAVYqAKbZEw/m7%2B7ZTCWGsGYAN3HiD1tIyZnoRHsguAYO4TwnQ9BhGDIsUY5iihZAENMPwIWMhhYYAsEY1R3MOD6JMdovn8jmLsB5gQ/Q2hxcqMF2wKWIt6DmLlwL8WJCrAUOqrYlX9DjtIP6qdnAl15sLcW0t5bN23AgLgWt%2B7caHuPSJ1YCBMBSVGBAI1IBJBJGRNapIrqNCSDMJIXNvr/C5utfVj1XqQDauRLmrgubzXWqdbm/wkh7ULdzY1r9gbg2ht1SJs9Mbz1xtnUm299692ZrYJwVoLAcyBHzUwCyzYuDWuRFwM11b8BEGcw2jtynW0SGkOppQmne26H5YOpgw6sNjo4NKu7vbp2ffnYu5d7XwcoUh9Ds1PWd1Xr3RHJIZgj3Pf1ZGi9qBd0JGTXevnLPRhpiMJDrgR9X2gkRh%2Br9QG/3QYVyBsDEGoOcdg5ieDiH5XIdQ2IDD0GcO6fw7rwjSWSOYfleR5AlHoM0a/fR2IjHYTMe2PKtjHGdXcd40ofjJvkIvbE0wCT0nZPyeg0pltqn0eyA0z2%2BVOOdPCds1YAzTvjNTYVeZ5WnArPeJs/piwDmp1OZc5nqr9Qst%2BAgK4Yr5iAvlAq1F4o2R6%2BkFC40PLSwMtV6S9loraXIuJcaDlwY5X8sJdK6lvIw/p/d%2BC1Vmrbaick6awqlr1PV1i7p1DmHGget9YR2zobXOI2jfG1gRIWf3WetIN6pIUPluBH8Nal1KRVtFvMevh7tgnsnsjTeyQHjTnUFx%2BwzSzQ4EB1XRYAUBzEVhzHpzjAmDh363rT0CjxUzbVj07UxwTx0H21IDxwJ1HR2zX3u04BnQTTLluAXSXRgLgIQKQM5CRm3WF2vTZySE5wALPV535xvRTXYL3SnGQFnkAUQOtUAWQLOVUCLT4DoBlxDQgE/V7WV0Qx1TUNVyI2g010EG1y/T12ADQ0N042Nzw3d2w3N2I1I17Rtzt04wd17Sdxdzd1Y2cy914B9z4zBAD2E25z4HEykxkzk24kj1kGj2wOR3jy00IIMBTyL0M1iAr2z0aEwx2HoVT3s0cwSER1cyz0y37xrzryH3828wXwS07zbxKJbxi3KJKz71H0H1n3qN6AH3mAnx70KwGHb3nw6MXzWA2Fq0PTIInTJ03wYPgO1mYNBFYKPxIBP24JG1IDGwm2vyJzv29RtWRCSCSH8AdSu19R2MCBO1JwDU4EezDSWONUkH8Hm2dUCF9XNUkDtS4EtTMFu3dSSFGLOKDTPwNR2yrVOOa1%2BIANWG40yGcEkCAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/sensible_gauge.test.hpp)
