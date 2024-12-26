<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left">To Index</a></p>

## Description

`Typelivore::KindredFoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
KindredFoldLeft
 :: typename...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeft
{
    template<typename>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will left-fold 2, 3, 4 and 3 using subtraction.
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
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= KindredFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              Operation<
                Initiator, First
              >, Second
              >;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct KindredFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredFoldLeft<Others...>
            ::template Mold<
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJkCbgIAE80oxWJgAHRo7CvRgEBTQ7AgybELwOO4AaQi6GImHQADFPOhQpgqAQ7iYAOxWVkAEWhVmuIN2uzuFiYSjubhF7BB/MFtNo6DuAm2KJBYIhH0w0NhCKRbDuGPBWNx%2BIIhOJZIYFKpsvpjIImv1bztgTxfPZILuHruqpe6s18MRzF1DwY2Q%2BJCN109dwJROZymIqCIAFk6e7PWzeVco1HvZCNTDc76C9rA6i0bi7sgDAoFHcAPKI4gfHIRrPZj0x4mczCtOhp9sZ/vtz1eLJGL3almR4dR6Gc%2BuN5sCTXB0NEMh6zGCI2BTMztnc3dS6ftwtQgvgn3nrUB5Fo5XOyvVhT3q7ASkGwQ451DqOjiLAHcABKqBMPKc53N2va0Jqb4fo6L7ls6IAgP6%2BZ7umXI8sebYeme%2BY3jqZYonBmCftirZ/mOgEpnKLKBPO8aJqgtHoLB75kQh947pmB7YXyvwynSXoAO54EqKqXnmfolsidzUngxCTKQE63rqQiYGgFqtp2zLmpaNJ0gyTKagpSkECpGlaWxP6uhheFSUWhGlo8IaOGGxCUZ6ul3ExyapieLJuoFOaOde%2BEyWpxEVlWIq1g2CRLgwXntj5UFMH2IWYfZM53P%2B45oVOuG5RBCVNk0mq/rlZVJZVWW5a5a4kCpZmTFV%2B7OpZmkCGx9XDjx7VBYevF9RFF5quFslsNxj6xTWr4ceR34usVVEAcBoHgQxkE9hlMEwqRS0zdgKFofxxV8UeAnFWNzl3mih0ISleXUXcrH0YxCb%2BXK7HwViiEPniV3AlhwPSsBmmbFkABumBihKIA4QK8nCQQYnbCpCCGOg9BeggcM0OZomoHcaRtMiYJKaQ4PY3clLIFDcP5YBBD43TmCTMq1y3WhLmtRZqlEXcVk9SpvP3Sidaswky3GqaenkpShlysZTpuPzXXWSpUv40px1SsFN1hQR4tBm5eAec9Pl%2BSxAUXYbM488bkVEcdT5xQuiUVbZq3eSasY7dBg2Dn1a0FZOg2ztt%2BlK9aquajrMv66Hnqncbb2pjCkfDjV3tuNn7a5y2Wcpw1q7ueuLWKW1pfZrims9QXdc%2Bw1Hq4mnE1wyBYEJ4u3tAzls6gyNvsOZ3frO8WUVu3NAOPf9z1h4B3dbfO6V9gdi1cUhJ2odq51D8NOGhePU%2Buw9W8Ly3I6ve9EE26xv2cf9%2Btg8PSMAv8QJ/PseqqKwLw4bfH5J/QEOFzCBAiFWLwWB6KEQAPomgyhRH2ECoHeFgZqLS2w0goJWiA%2B4QgvCxCQcSYB3NJ53V1FcMWU04ZWB9j5IhJCmwOAABINEbAbHKzNBZDggpMdAKEIhgnfGIeBWl5jbhhCIlSVwULQzEF4TAABaCwCilH5gHgbI%2B10eZ0NfMQYAstri8OYaQ5kEFzGsIIBw2gXCDpGIBu3PeiJzoEMOG9XaVAvAMAcDkL45xJKnyocRK4TjWy8KTN43x/iBBFQgjHK0RlbR1WKoI4RghMBiNoBIgQUi1ayLuIEeuQ4MkgBEdkpsuTJGtGkW4IpkhSmBXKZUnJeSGAFM1EUkp18XGP0ccY1%2BI8f7Cy8GkYoVIgIcy8LQZk5CrhmPGZM9A0yFCzLtHybarSsntNqYYQpggVIqIAJwDWuqMtZGzAmHCBLwq5cyPpeNaD4vxecdmiOqR0rpMijl3C4DuFaKEV6amsUwBw5zgS/GOHcAAKhzeZQTrjzEcMgeBcUEgEAgOUhQyJ0XfjcA8gWRCJmZCmTMuZuIVg8g4GsWgnB/C8D8BwLQpBUCcHzpYaw0YNhbDhhAngpACCaFpWsAA1gESQKINAAA4zBmBOScrg/hZUyq4KyVk0h6UcEkLwFgEgNAaFIMy1l7KOC8AUCAI1wqWW0tIHAWAMBEAgA2AQNIXgLIUAgGgZ4dAEhRGRJwVQMrkgqOSJIO4wBkDIH%2BVKswvAqSEBIHgIRXAZCCBEGIdgUh03yCUGoEVpBdBppEk2NInAeB0oZUywtZq6wevdcyVAVA7jBtDeGyN0bY0ojMHcCAHhfX0GICyMwgQuArF4DarQawIBIB9WkP1ZAvXzsXSAYAUgzB8DoJTS1EBYiFtiBENocIK28EPcwYgcI6yxG0JpG1gqfWOjrAwWgJ7bWkCwLELwwBxS0FoJa7gvAsAsEMMAcQ778D00cLDADrLMCqEhmCU95AsnatZbQPAsQmyXo8FgQtJo8D6sA6QWGxBYhku7CBowGGjAirWFQAwxiABqeBMAiQSsywV/AM2iHEDm7jeaVDqHfcW/QoGUDWGsPoTDlrIBrFQLgnIAGVGCLnKYLllgzCmtI8QFNHN4BrDsHenILgLQzD8GmsIEQRhVDGGm4o2QBDmb0A5poixRg1F6MZgQAxpieC6HoIzcTmhTCGNZpYdnbChec2m%2BY7R3O2ZqIZ3l2wJBVo4Iy41tbOCtpDWGiNUaY1SB7X23ASbh0ConUKujax8ZgTGBAcVIBJCBBRCcwImqNCSDMJIZIhr/DJBOfoTgurSD6rHSiZIXBkgypOWq5I/hJDKva6kE1vAzUWqtdV21M6nWzpdQ2j15BKArqHQGtgnA2gsGhqyFRTB3bji4CclEXBpUJvwOuFNegBOZr49IATighOFt0Ju0tTBy2AfS5ltbbLOD1rdR6hULa235Ye4BJ7L3pV9oHQuodI7AhmCq1Ou1%2B3TsJGO961Ag6xixSME9rgRqaBzJlpQfd77z3HuQxzy917b0OGQ4%2BrEz7X2Fs/d%2B39/7kPAdA%2BB1lkHjMwcLfBxDOxBWVLQ7wDDWHj24Z2KygjRHBWkfI0oSjMuAJ0b4IxhQLG2MceQz93j2b/uyEBwWkTIBN0GFo%2BpqwlhpOxFk41tlin8mcBUwQGynJffWC0%2BtnTemg%2BGYaN5vwEBXAxZCBaBLyx7OZEc7kfzBQ88lByDnyLQWmi%2BY6EXizXngvV/L55uLNf8h15b03tL6xNipfHcNjLNb31mty%2B2iNtP0fPdexoUrH2SD4/HZOmrpA6tYESMH7Vo3xvPa66yfwJyNWBG671pbWWh%2BcE29ay3DrnWusbRTsnxBzs7Cux2lgChoYxuhhjvMkx3vla%2B2mo7lmhIC7oIG7sJqyroMEGDhDpWv3tDtlhwPDo2kjq2q/u/p/t/uqJMNjlTrjgkPjoEETlfnOngYuvfmQUOiAB/hMvAl/icvAj/gQPAqoOGluszkpKzgekepelzjwVejenegLlTk%2Bi%2Bm%2BnLpgF%2Bj%2BmIJLsRtLtRnrkBopArvpu%2BsrgzEhsRuroWlrthnCLrvhrpobrwMbhRuCObrRjtlbkwMxqxuxgGA7rIL9s7rmuAcDiAMEN7sYJJv7lrkniHk0ABrsBkjHpptpgkLplgP4ZXiZunmZrXnoFZhUB5i5vnk0Jnq5mXuFikbFing3tFgkbkX0D5qFp3rFgUW3oFqUdkYll3goCltmlDoPqajlqwRGm/h/ncPQSiEwTPuVvPsQTtrVpgPVmvulpvp7s9oEIEP4CqktoatMayDNqfi0earYFtsTisE1pIP4G1uqqyIajKpIEqlwHKnUNqoEM0etuftttOulvGisdcWsZsWsKRlkM4JIEAA)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left.test.hpp)
