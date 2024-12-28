<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-left">To Index</a></p>

## Description

`Mouldivore::FoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;, Arg<sub>1</sub>
   &gt;, Arg<sub>2</sub>
      &vellip;
   &gt;, Arg<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
FoldLeft
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldLeft<Subtract>
::Mold<std::integral_constant<int, 1>>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldLeft
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements>
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Initiator, Element>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<
                Operation<
                    Initiator, First
                >, Second
                >;
        };

        // Recursive Case:

        // Fold twice, handle the first two parameters,
        // and recurse using the rest.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            = ProtoMold
            <
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Detail<Others...>::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIACc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJn8bhBYLemEh0IAnqlGKxMAA6TGQ7A3ZAGBQKG4AeRRxDe2WxQPGxC8DhuADFPOhQpgqAQgSYAOxWS43Pk3GFPOEIgjI1Fse4MLJvEiU3n86m0gg3ZTEVBEACyTKB/JuXJ5F11usF4PhUNFKOYbEx6Owz0YBAUcsNRr5irpABFMM06HruVyPZCDTrXTdttsbhYmEobm5o%2BwOfLXeGGUybgJNuiQ66TcLzWKrZgbnbQQ7naGbu7lV6fbQESWXuz/Nhs0b9a2K15MkYBWK9f4PcTSeSBAi7lLHDKyMX7YJKf4DRWA0HEy7kxHGbR0AKAO54TMd/m5iH5y1ohl4YjjUi9s8SoSYNAMdDl0NVm41ph0BH0y/Xm4Pk%2BL7NoefLtkmFY3F2ETALe8IQUuA78iSCQjgwCKgZBKFkg0GEIZBrrjtKRDTr%2BV7svhBHYjegECC%2BlGQfOi6hsuC6rhWKYAEqPusmQAG5FnGSggOxoYppu24EHumw3gghjoPQAoIEWNDkbuqA3KkLRoiCV6kJhKbyTcxA8VeRbQT2BDKcZmDjFmDHHmaSJ3kWZH/ha4pFrRz43h5hY2kSVkJE6IEMe%2Bn7flCbkEDRj50TegXKVeNqvq64FrpBFmwR5mG6pCg6quqqBaluuX8nhGUEXy2FoRVVVGjVuFQmVBFEZOJE3tFLVts2sVAd1eWhZVLHNiAICOR%2B3pfnWUKJcFKWjeNYorgxrHBg5oJCiezmeTaFzACZpaCCFLYMVlNwldu%2BWTbWCL7YdjYKAt2BjTlbEQWtol8o5IoFmie0HZgR2OqlUHdrBl39gVaqatqUL3UDj3PStgKcoG72At8fy/ACPy7MWqisE8RafECePY6cq7mP4ER4l4WD9jtAD6BBkoQJ2rnjAFeLErNMHSpOXD9p6eTcFy%2BX9EpWEN75CDzfMOAAEnUpIcv6EHnR5UOVgQ6BjREIIHWITNPrMc4fVCBs3hcY18WIXhFgAtJGtv22aLYY59lxAsLO3%2BZiFzEMAHOXOdcu82SdLXeHCsEMrtCq/DQdPVii1vetVyHBdU1UF4DAONkHyU0Lm2mr9Ll7cnzrnRqOd5wXAh6t7SESSybIIjHkdNqdNsgJdCLjHrIAG5gRu0CbAhm02bhWzcXDzj3Y390nwfI57WO3NxCheLQyqCxc51bzvyrXbXzS5/nuHN24raD/rgij2S4%2Bm80c6W4IN7%2BNRt%2B6/fhtPxPBgU8ESz0kN/CCd9h4PzHoA4B78Yo3C/kNJinMs4ABVbJ72LhcWYjhkBM2jEoVoEAj671dt4Is%2BVrqOySEsIMHAVi0E4AAVl4H4DgWhSCoE4DfSw1hKxrA2JQsw/geCkAIJoBhKwADWIBmGSHRBoAAHGYMwSQkhcGYcopRXBOScmkEwjgkheAsAkBoDQpB2GcO4RwXgCgQAWIkRwhhpA4CwBgIgEAawCCpC8DFCgEA0CPDoAkKIaJOCqCUYER2gRJA3GAMgZAc8FFmF4JgfAJE8B6y4DIQQIgxDsCkLk%2BQSg1CSNILoHJO4ySpE4DwRhLC2HlJsUSPxvjlSoCoDcSJ0TYnxMSck9EZgbgQA8ME%2BgxA9QiK4EsXgTitArAgEgIJqQQlkACSstZIBgBSDMHwOgul7EQFiOU2IEQWiIjqbwM5zBiCIiJLEbQj4nFiKCY2IkDBaCXOcaQLAsQvDADjLQWg9juC8CwCwQwwBxA/PwCZAuAlQWcMwKoHiIIrnkAfoYzhtA8CxDJHcjwWBymszwKYsFpABLEFiBkTAXpIVGFxUYSRKwqAGGDgANTwJgHcKF2FiP4Hk0Q4gimCpKSodQPzKn6ChSgaw1h9B4vsZAFYqBUgNFBY7Qe%2BVTB8MsGYaxVLiBZNsvAFYdhnnZBcM%2BKYfgclhAiEMSoIwclFCyAIW1eg3UNHmMMRIOSLUN0aBMNongOh6EDQ0PorRfXOv9bYENnqA0htjYsGZqx1ibAkA0jgrDLHNM4N0qJMS4kJKSVIIZIzcCEBIFM0RszxEspWMpJgWBEgQBkSASQ/h0RJH8PojQkgzCSECOY5hgQkj6E4MY0gpjRHokCFwQISikg6MCPIzRfbghWN4DYuxDjG3OMWR4pZXi2l%2BPIJQTZEywlsE4C0FgfFOSOyYLiAwPYuBJHRFwRRaSMkkCyXoMV%2BSRXSDFYoCV5TdB7OqUwWpYKc15p3VwzgrSfF%2BPTF0npJa31Qrnl%2Bn9GgRljNWRMutZgG3zJcae69CRL2BNQOMkYeIoWfq4BYmgu9gqUBOT8m5FyMX8buQ8p5DgMVvIdB8r55S/kAqBSCjFEKoUws4XCy1iLykorRVsMRI9sW8Fxfii5RKticNJeSsRVKaVKHpcpmCLK%2BDsoUFynlfKMXAeFYUsDsgINlKlSAPZ77jDyssIq2IyqO1cPVdkTV2qBy6qsPqw1CRjVYAi%2BauolrnAQFcEmkIz5U0utIN67IeWSulEdQsIrkbeiJrDfkANmWg3RoGJVv1Ea6t5DtQmuYbW43ZozUIgbhikMFo4EW3pcSWMfoI4oqt/7JnUxmXMptpAW1tsoDmmdc6v2Ds5MwpIej/BDpHZIHJyG922APVR498BT3ePafR2jxBb1bAfX0lgCg%2BJJL4p%2B9Eppxh/praloDsgQNeeKb5yVnDdD%2BFILB%2BD9Sp25qaT8lp56OlYY%2B19n7f2AfKlGYx0jCQ63%2BEow5mjRO1lPapxMkA33UipCZr9pITN8dM1ULE/ZXGrw8dOecu5gmBf3Mec88TjH3mfO%2BapzA/zAViAUxSpTjLTPgsvOp01PytPID8Tp3genymGYJYiEzJLjUWd4FZ2ltnGX2aPY5pgnLuW8stO5sHnmJDecEFDqDAQZXMoSwqwz6Wosas4NsO%2Bgeku7qNSakPNXsu5fq91h15R2uuoyO6nIyevWZ59X1tN3QsvBv6HlhPJeY0F%2Bq518Nybetp/6%2BmhQgis3ppG6j6xhbOdxM%2B99m4LP/twnGPN4HdbluHoWc2zAraRiRcMdtgLX7/D%2BGYVos75jl%2BcmXfmtHnB92ONW7IyQzDe26M5OYpRkgNFcBUWYYIhj/Ad93XvifUjkepJ3532xr%2BlgrCpZkZwSQIAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/fold_left.test.hpp)
