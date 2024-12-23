<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateClassicTransform`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-classic-transform">To Index</a></p>

## Description

`Mouldivore::CognateClassicTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.
When invoked, the function transforms its arguments that satisfy all the predicates with the transformation and instantiates the first operation with the result.

<pre><code>   Oper
-> Preds...
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf&lt;Arg<sub>0</sub>&gt;::type : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf&lt;Arg<sub>1</sub>&gt;::type : Arg<sub>1</sub>,
                                    &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf&lt;Arg<sub>n</sub>&gt;::type : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateClassicTransform
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateClassicTransform
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

We will apply `UnaryMinus` to elements whose value results are divisible by two and three in the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Vay::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Vay::value % 3 == 0};
};

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateClassicTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<1>, Vay<-12>, Vay<2>, Vay<-6>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
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
    using type = Hormone<Element>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateClassicTransform
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
                    using type = Hormone<Element>::type;
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkizp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJkCbjBEI%2BmGhsIAnulGKxMAA6bHQ7B3ZAGBQKO4AeTRxA%2BuVxIMmxC8DjuHmAzDBbkJ2WQABUKQwFPxiCwQSYUlZrndxXc4S8EUipZDETCCKj0WxsZjcfj2WrlF4akrqWKJbT6QQ7spiKgiAAlVBMdAgiV3YWiq6Ox3GhlCQkIB1u8XO31%2Bx1ymWK8HSqGK5XMVU4wJ4glMIl3AASJBYAgV2EDQfFHtN5stqBtdpzuYDhtzfpDkZRaJjmDu2FejAIBtdVb9%2BdTeHQWAYTsrnYlFY7w6DXmyRklyqdgQAIk2W4JoS7x47hfPV0Kh%2BOawq6yrG83wa32%2BuJcRMABHLx4K/EiBq8wANlfOr1yKRJ7ebfjIBAAA3MQvEwFYy2HbsU17ftv2XP9s13YdRwvP1dl2J0Xw0NMBUzEwsLuPBiQIBBGwIHk%2BXTSkBHVJCL0nCJgBnNE50XHCM0iODTxXf8QCVNFtzoqtN0E4EhNzfdZWjDE1R/VsFHPVCGOnABZTx0FY0lyWohgpPrDEez7RguN/BTeP4rE42zQI12QlItxsiD/Xs0SnMlcN5VlDzQ0PBtn3jTUkwUNUrmAK9uIIMzELHN1lKYksNOhRcvSTJA%2BO8sEzQta1bXtGFQvC0z/Os2znIcl0c0ksN4VrCy/KswKiRCsLMAiqKcziu4Es0wsctLfKWra4rXJcxzrhBP4AROIFJqbVRWBeRtvgmqbAR3YEzECCICS8LA5zcNAGG2dJIvbFb7gANSYZEvnOEEqrcJgvCIR5227K6v3GkU7nmRxkHxARJkwVR0mIO4npe4DvEbZ0HhEmynVGirfmOO55zwQCiLwWJ6AsZFOQAd1QW7DiBB66oMj63vIk00YxrGccwPHCdQIURRzX68H%2Bw6gZBsHYlQTw7ih0Cc2dD6AJFmGzH8O4zFYpK7g0eGKqR9bZvRzHskZ5mEHCkn9jJjKDwptg7ip%2BMaRphlNYZ3H8b11q2dKn7Wj%2BgHeTBPm7gFoWpbFkUJaAkDpdlwIFYXJWVbZ8r1dRuRmGIZEVIiScDaNmqTeks2rtoam6QZBO2mT1OFK%2Bl3OoszSLbcABaXPJZD6kxuBNXxpR%2B4yQSHT0/u429KPYbrm7LuKSaVyO8OO4VMwVoqC8I7PmW65yezyzMSuYhgHa65OpnueF4cXJNKZFlMDZIKue5QxKIFJFR509sAISpFbe1%2B2WdIOmtexj/HazEEz9cpIiLknFODBJxPxAGpWgeU3Cb23sNFu50p5CC8OkEomB0BWkwAoLwtBTTLyuJ1NBGCshYJwXgghmkH7j3GjCGuXBcRfxrrXLgZhmHm2ukiDh8YWHcJhLXN8fCuFfhhFwfwzcSpx3uJQ/BhC7q7ynPFXB8jNL7yYPPReVJ6FuEYZwxhvDsD8LEW4IxJikTCOMaIpEEipETxuKjTkuCFGkytpSZAAB9IKCQCAQEmOgACCgMTeLMm4ORBCv6kMwdg1RBDcTgRshwNYtBOD%2BF4H4DgWhSCoE4G4aw1gfobC2NLQIPBSAEE0MktYABrAIkhMQaAABxmDMEkJIEjmlNK4CkFI0hUkcEkLwFgEgNAaFIJk7JuSOC8AUCAcZlSsnJNIHAWAMBEAgA2AQdIz1yCUDQM8OgCQogYk4KoJpL4hGSDuMAZA/0pCYjMLwLBhASC9j0PwQQIgxDsCkDIQQigVDqCWaQXQXBSAEwpOkTgPAUlpIyVUnJnASTPR2aaVAVA7jnMuS%2Ba5tz7kNPlhADwhz6Bg3MGUlYvBFlaDWBAJABz0hHLIBQCAjLmUgGAFIMwfA6BgmIHMiAsREWxAiMXGFvBRWJ2RCSWI2hMAOAlaQA5v4SQMFoMiRFWBYheGAI9WgtA5ncF4FgFghhgDiBBfgK8R9AK4MRcDBVz0djlIiGCAZ2TaDYwpEnDwWBEXkTwCM41pA7XEAFkoec4JzVeqMFUtYVADDbwungTABMu6ZPKZ84QohxB/OzYCtQiKwX6HNSgAplh9DYzmZANYqATq5CNbXAJSVTCWGsGYKZYbiC9ntbW3oCqmguAYO4TwXQ9BhAiCMaoYxwUlByAIGYfg51ZAXQwRYoxEjgrsIO/oUwOhjsKNuhou6BADHaBumdW7bD7qXXoeYF6p1LFnWsBQxTtgSDhRwdJEzEXTKxRcq5Ny7l3AeUS3ArzyWbS4FSip8a1ikTtGMCAtSQCSECJiJIgQ%2BkaEkGYSQWEND%2BBfEkfQnAhmkBGWUzEL4uAviaUkbpL5/CSAkVhl8v6QXTNmfMuDSy6XrPpZs1FuzWXsrJSctgnA2gsEAikWuTBArTi4EkTEXBGnPPwEQHtgTwXZu%2BXm6QBalBFpBboHlkKmDQuNV%2Bn9kzeDTJRds56dwMUAZxdcxMynVPqY0HcYlqBSUJCdJtMwsGaXLKE%2BJhIey2WBaZWSlABgjAqa4OMmgBCEiCuFSCqV4qQ15aTrK%2BViqQ0qtbGqjVWrMA6r1WIQ1SrTUxp2Nk61u67VGuyY65AzqlVuoaIir1sQfXIj9S16lPbg3lLDRGzAUazVGFjaAfjfAk0KBTWmjNSr9O5t%2BUZ2QhbgXZPM6WuNbarCVqGzWlDOSG2A04M2ggeV5znY7V2hIOm%2B03Z3UfZwEBXB3vBZOyom69DzqaIDjIq6miXuWMevoZ7b2HuXQO37zR92w9nTewYkOH1DCfaDmD6xNgfqJwMuzf7ODuaA15piKm1ONP8xB7TIXKXUvg6QRDWBEg3YGRRqjqncMpH8KkFIgQ8MEdY5xqZnAeMLPjSswTSAtloti9F4gkmdgydxXcFgChAL/UAvT%2BUkxNOQfeXp2QBm9v/PkCZo7OgQDBEs9Z2FZHv0Iq48ikT6LMWqB13rg3wtjcIkmP5klCXgsUsCOFhXUX4vMrVwnxLBuMGeKN0kTxJuCCeP90ZvlWXKA5eyYVzVBWxVFblYOpV5XBCVbL61mrur9UNZDU1xb43SBtdtfakF3Xeshv6x63gQ2RtjYDZNpVM3yHzZjYxBXiamDJtTem%2Bs22re7YkPtgF9vi1O9O8YCtNgrvwDrXd3knBdgBPLe2ywnaHPdt7dd19J60fDtHQUFHwPp1w6h6UXIkO4OuQmO16P2TQ56B6n%2B96r%2B4BGOBOV696SOUB26cBIOCBROb6JOvytmnuMuHAWKAe%2BuhuIeYIYeEAzOJArOMG7O/GCGmASGPOX6/OIAbSmIgQgQ/g/guGaWGg7BKQ9G0uDmsutgvGEWKwqGkg/gmGPSKQYyTSkgHSXALSZgHGAygQuBQhMyfGtKX6TyghSKWhYhawYa2QzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_classic_transform.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_transform.test.hpp)
