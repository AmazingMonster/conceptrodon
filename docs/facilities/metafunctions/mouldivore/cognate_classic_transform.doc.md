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
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct DivisibleByTwo
{
    static constexpr bool value
    {Vay::value % 2 == 0};
};

template<typename Vay>
struct DivisibleByThree
{
    static constexpr bool value
    {Vay::value % 3 == 0};
};

template<typename Vay>
struct UnaryMinus
{
    using type = Vay<-Vay::value>;
};

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateClassicTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

using SupposedResult = Operation
<Vay<1>, Vay<-12>, Vay<2>, Vay<-6>, Vay<15>>;

using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMQSGqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbrv7h5gnZwCeyYysmAB0LyfYANTIBgoK7wDy92ITB6bxMGgAgjNiF4HO8PMBmLs3N90sgACpAhgKfjEFhg8EmADsVgh7zJ73OB2BV1OlMu1wIdwebBeTzenxRrOUXgqjNBpPJUJhBHeymIqCIACVUEx0Pjye8iSTwQqFULYUJvgh5aqyUqdbqFXTqQy9lSjrSmcwWa9jh8vkwfu8ABIkFgCGnYA2GsnqkViiWoaWy70%2B/UCn2640W273a2Yd7YehsQT8lWR3V%2Bl14dBYBiKiMZ8nh9NFw1edJGClMxXHAAiieTjAIJ2VZYVRLrrfxoaL0ZpseZCaTe2bafb5OImAAjl48FPfhBWeYAGyr7m8m7XEcplt2kAgABuYi8mGWvYzWedObz26bqbtF8jJYnuoA9G/FSuNK7cR6TN%2B7x4L8BAIAmBCYtibrApkbKFq%2B7wVuEwDVvctYNr%2B7oRHeo4PtgB6Mvc3bwUWnbEQSJEZv2DJWo8rI7s2Cjjq%2BSFVgAsp46Dof8gIwQINFxo82a5owOG7kx%2B4gIRzy2l6xxtqRhJdvJT5kSpEJPtRtJmvSlqCTabJ2hyjoKKy4LAFOuEEBJXqUYhlYocGXEnA2mqOkgUk6dSorilKMpyqc5mWeJy6PuppaKkp5HelpZxeTG0nxqF9qci8QWYFZNneqxjn%2BdxAZ%2BSGgUWRlIWydFUXhfib4AFR1fVDWNW%2B1UNe8aKYDMvwNc1EK1Y1/X1T1FEEmYxzhF8XhYLWbheI4tCEFuj4aRCsVMLNqDvAAkmmWYcQwgYMFuGnEu8MwwcgnwCDMmCqMkxDvGtRDvMe3gJkq22VRYkXKcqLX1e8dZ4IewF4DE9AWDcaIAO4bd1%2BKxYlQkAGpiDtEHCgDQMg2DmAQ9DqA9sS3pnY4F1oFiuy3fdMSoJ4z0nlchZKijtAHi9p6KmYACs7xmOhLnvBoam/Z9Pa9a1gPA%2BkON4wglnvHDK3xQOiNsO8LNo9CsKS9j4OQ3LGWEwpvqNKTl0Uzdd3vDTdPs4zEXM2IbMM5zPPHPz9aC8LhM/WL4J9XV7xyMwxA3Gx4QVgrg3w8rAlDurqNLZC6OwsHTRhxHTHHcb9nIahb2e3tB2LW4AC0LPO69oJVaLy3%2B612CqKwBwJor4II7RBmaxjALxHxDDRUrFwmnpQ5mcQwBZRCOXvGxmCNFQXgMHUAjcfCiKYMiJl4OikE4nipy90CIJJweTnXDr0t6/jpCY1LoPXwbnr4mf/nXGnofhwwFZpgeHG0AFNw4IJ6mXKlVaeDl3hCC8MkAomB0CSg6l4WgIoBZH37j2U4RciCHWuFwN4t9sECBLqXLgZgCGzwEMXa45C7SEKoTgkha46GUP2owvBXNq5yV%2BhAvOiCFDINQYXeeTBF7LxBBpLBDDiF4IoUQ3BpwyFyOkQotwtDsD0LYTI04zCNGsOoYozhYVuF%2BxJjvAA%2BiZeIBAIAzHQAeBQjxLESTcPwwRt9oGwLSPAtxKC3jnnkhwVYrMOBc14H4DgWhSCoE4G4aw1hTrrE2G9UaPBSAEE0EE1YABrEAXMzBPEJGYSQAAOEpXMNABHyRoFcJTjj6E4JIXgLBEhJAiVEmJHBeAKBAEkDJkSgmkDgLAGAiAQDrAIMkWa5BKBoH2HQeIkRHicFUCUlcpcVySHeMAZAF0pBPDMLweBhASA5j0PwQQIgxDsCkDIQQigVDqAGaQXQXBSBQyBMkTgPBgmcDCaQdpvBOl/FmlMkUqAqDvFWeszZ2zdnvH2XzCAHh5n0HuuYY4XBli8H6VoVYEAkBzOSAssgFAIBEpJSAYAUgzB8DoLsYgPSIAxEyaQGI4R07fN4OykONw/gxG0LUfpaS5m7j%2BAwWgNxWVYBiF4YAbgxC0B6dwXgWAWCGGAOIZ5%2BApx1EPB1VlN1aizW2Gk8IuwQlRPmjEIEocPBYFZRBPALSVWkH1cQGmSg6x7A1fNIwmTVhUAMJPJGeBMBQ17hEtJFzhCiHELcmNDy1CstefoDVKB4mWH0KDHpkBVioGSD0ZVpc7EuVMJYawZgOnuuIDmA1ebOjdEyC4Bg7hPBtD0KEeYZQKh6AKBkAQkw/BvP7T0QYPaliNqFfUWYQ69A1BXr0WY47hiVDGP0OdbyzrNBXYsSoqwFBJK2BIX5oTwmss6VCtZGytk7L2ZIA57wIC4BOei1J2L0kBtWGBWUIwIA5JAJIY4TwAjHEJJIDQkhinfg0FzFcQQQlNNIC0zFTwVxcFqQEEpGGuaSC4FzUDK4AUXs4N03pn6Bn4tGQS8ZoLplkopWipZbBOBNBYIeQkpcmDGSrFwAITwuBPCiccogtb7FvJjVc%2BN0hE1KGTc83QtKPlMC%2BSq09/zAXRM4CCyZs13gQoeriDjXGeMoT4wJoTT6UXErRZzY4ZgP24sGTRxj8QZnktQKikYbHjMOiMHxqodKUHxCZSy55PLOWuoi6HflgqHBctIKK5s4rJXSswLK%2BVirlVpLVb67YUSdXTv1cq4TqhjW7AS%2BarorLrW2puPa/LOLa0urSe6z1mBvXqqMH60AlG%2BDBoUKG8NkaEuSbjTcmTsgk1PKiYptN/ry1WCzda3N/7omFsyMW0t9ZFuVurfEMT9a1sLp6C2ttORh3BFbbu3tI60gDqyO23Id3CiZBu5Ok7M6N1Pcu59gQfQd3dtXfO2dP2Qf9He/utYGxj1YoaWe4jzzL0%2Bc49xvzZn%2BOCY0E%2Bl9om7NYpxV%2B0gP6sAJDW4h5pIBjj8cg4SAjhJCTHCg5ITZbzNOdLI30gNQzqNIAmWC9zrniDMe2Gx2FLAFCHguoeczlwZhHPwKJs5EnZBSYm3c%2BQcmZs6Cp%2B8z5XL1PnqR9puj4LIVi62RLqXz1ZfUhmFZzzNn4h2eOI57nLnHcksF57tFR5kCwPMTLgI5i5cEEsbiTZQWGWhdZdFqVUWOUxYFUKhLSXBApfjwV9LcqFW0CVQl3L3XGukEK3qg1zyjXIBNZVwQ1Xnm1fTg1x1zWEtte8Z131yFudBqYCGsNEa4yjdV%2BNiQk37la5TbrgwC3M02BW/AfNG2rqcDfHYjNFbLBVqBTWutq2D1dGnc4CArhN1XfQJDvt92ein9HW9oHe750H8XQDloYOt1P56C/i/W7QcXfB4D0oYHOHQ9GHG5Q3RHDpTgQzFgcXSXaXW3XYe3Z9RXEgfHN3Sjb9TAX9MnU9JDFpQIJ4Y4Y4LmCpPDDQDQIgwkWpCAoFUjWwcjJzZYADSQQkA5OnLgKQAIWnUDLgQkeHY4I3SArpCjPFU9Q5GgrTYQxg1Yd1dIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_classic_transform.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_transform.test.hpp)
