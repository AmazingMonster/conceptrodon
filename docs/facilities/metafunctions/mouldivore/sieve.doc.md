<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Sieve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-sieve">To Index</a></p>

## Description

`Mouldivore::Sieve` accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Capsule`.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Capsule
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Sieve
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will remove every element whose value result is divisible by two and three in the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>`.

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
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule
<Vay<1>, Vay<2>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each element in a capsule separately;
2. taking the element out of its capsule if it satisfies all the predicates;
3. concatenating all capsules.

We can merge 1. and 2. by:

```C++
template<typename Element>
struct Detail 
{ using type = Capsule<>; };

template<typename Element>
requires (not (...&&Predicates<Element>::value))
struct Detail<Element>
{ using type = Capsule<Element>; };
```

We will use `Cotanivore::TypicalPaste` to concatenate the capsules. Here is the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not (...&&Predicates<Element>::value))
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    using Mold = Contanivore::TypicalPaste
    <typename Detail<Elements>::type...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElwapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOtw8LQYeAAbiR2CAACoAT1SeFEtGUTAmmC%2BhyBzDYClSTC24NkhhhcNuJgA7FYriCCJgWKkDEyTIE3AQUYxWJgAHSCjnYEETYheBy3ZGo9GY7HUum0%2B4c%2BnA347W4WLE4tzakAgxnM1lMdmc7nPAk4zHIADWmHc5IiCWFooI4sl0rRYjlprc1rtDsETCdxBdDMVV1uUduXkyRlu5pxHPut399o8QZDKoNNOVgVVIJ2GoASphkBtMtCdXqDVcmSy2ZgDZyQdGE0bGxyuTzLYL%2BcLbsgDApPhmWiHLqRW9H68bfYne0LAthB8PR47IsQbNOowu%2BX3sPQ2IJLgpSNTIzOe/vBYfmYwCBYzzuE9e2H2APIEBAJBTNkVXGKEoEFKKJehiWK%2BmOwabsCnJ3seBCnn2wrntBIZWPBR4Pk%2BKHLueX4/sQCh4QBwIRpcbaxhEwCvs81KBCmnqypBTaXlGXYvm26GwV2CEPshgrnvxgi4Uu2BTuxba3IRv4oVJwogCAibZuGeYFmptagncuqpAoXj0LiBxArOnZmm%2BAria67ogbp%2Bn0KparaQCLl4oWYIAJINveQaNEZZzua5QVAoaDYmk2ZoduFXZ7u%2B4mrliJGCsoxD2l6TJ/su1nAbcQjvFWOaqm2pnReZFp8rcIkEGGlHRkBkqPOOtAXrVHF0jGca0YmDEpnZBkRW4Lr5gq6lacVUXzhZlXYYINVtqlACOXh4KlnwQAwqAgRAKFmAAbOYu0pWlogZXxM3VcuSnQmIXiYMsywvvVIGNcGtBnT5F1kW2tIWB1NF0UmjHgkwen9e9iFDb9SqOS%2BJWTeVcX8lVmVfdG1HxgAsp46A9WSQZQrCqVKcx3qsS%2BMVTS9dDgw%2BKNKYmpH0zyMO5jDvxBYCgUHJVqisKyOLfFzHMBQyDJmIEERDl4WAMW4aAMFsqQECjWl/HstwAGpMEi/kmRNA1MF4RC3B5NVPZr2uFbccyOMgg4CNiqipMQtyG8b13eEmdKm6zw3Q/mqtgvcMJ4JksT0BYSIIgA7qguuhXOA2xTiWtvVlgFujlwfQqHeDh5gkcx6ghWPS0tv2wwjvO7csSoJ4twe7d5N0qnV03UmZj%2BLcZg9cmtwaP7Ba%2Bxpznq9nuf54XCCpQLbl1vrFMIynYhm5nDUh2HEdR9PmBseRRV1WXaIV1XLu1/Xjd799LdiG3nvUp3tyBL3QMD8POajaLo/A6DhmC/PYV4a8kRqvGyP97IRRHmrW4GNMAtCoF4BWfl/6XDhknCyfZLjEGACrK46NaKwPgYghw2RcZ5UwAVTk49N4FyjrHc81C85bwRDvCKZElJY1oOgLsWCcGkTZt/IQXhUhFHtKWeyIEUH4NysI0R6BxEGRAn3PqDkGSci1kiLsXBUIW00ZyMwOiNFaP8ENEUAcv7QIUbQSRc9LjSKsUooGhCmAIKQdkZsbgjGcm0fhXRWiDG%2BK8W4AJEk/Gcn2oEy23iTFZViVAsECIPg2OMq6E0aIAD6iUEgEAgBMdASkFB8kyZlNwDjzxCJERkMRHxFHCgevmDgqxaCcH8LwPwHAtCkFQJwQalhrDW3WJsDugQeCkAIJoRpqwbQBEkPyDQAAOMwZgACcyyuD%2BAWfMrgNIaTSGaRwSQvAWASA0CkdpnTukcF4AoEAKRxkdMaaQOAsAYCIBAOsAgqQjbkEoGgFkdAEhRD5JwVQ8zdoAFpdqSFuMAZAdspD8jMLwNKRBiB4HyVwGQggRBiHYFILF8glBqAmaQXQmLo7EBBpwHgTSWltJJZcj8RsvkgVQFQW4oKIVQphXC24CKe4QA8P8%2BgLtzAjOWLwe5WhVgQCQH81EIqfkQHlQCxIwApBmD4HQJkxFKCxBJbECIrQkTUt4Ia5gxAkQfliNoMs9zRl/MQh%2BBgtATUPNIFgWIXhgC6loLQG53BeBYBYIYYA4h3X4FSiQqsAbOmYFUGWI22xRkRCZPszptA86UstR4LAJK3R4GOYG0gVZiC1yUI8ENRhM1GAmasKgBgcEa3eNHD8FpTUEpxeIfF/BBCKBUOod1ZL9ChpQNYaw%2Bg843MgKsVAStsgBvBXk5Mpg%2BmWDMBc0taKsDTogKsOwdrsguAYA6PIfhMVhCdIsUYmKihZAENMc9aQMj3oYAsEY1QeiHoEP0KYnhOh6APSQn9kxBhXo/YB0Dj7IPzHA5UG9%2B7BlbAkLSjgrTSDnN4JcjlYLIXQthfC2ZArcCEBIA/cVkq62rB/EwLAiQ92kGmZIQI/JlmBF2RoSQZhJC7VOf4Xayz9CcEOaQY5Iz%2BS7S4LteZyytm7X8JIdZbHdoYYZZwa5tyxl1qea82V7zmXfIoMq1AwrAXAo4K0Fg0IaTgqYAleMXBln8i4HM5F%2BBUXor0L24Q6I8XSG8/24lQ6QCaopVSwNqH0OYa6ZwJlnyja3DZThrl0Khyhr5U5lzGhbiCpMwqhI5GzASq0w8mVcq8uqqVSqkVKADBGEc7UGg1jfx6oNUay1HbzXGutbahwHbHUPmda6klnrvW%2Bv9R24Nobw2dMjYemNJL42JqZB21N9QSWZtiNmpEubtidILUW0Zpby2YErdNmi2mG1MCbS2ttjAO3ea7X5glgXB2dN0Jqurxhx2WEnbEXds750O04Eugg3DGKrqsOuzdCRt0fHgPu%2Bo36/AQFcNBi9J733wc/Xexo6Pn3FGyFjpYmKgONF/e0f9%2BRSdI%2BA00UDxOb22Cg1Tp9cw2iM%2BqIhjYyGuCRfpe67DnK8P2doo55zcycskdReRvnlHSvUcwLR0YDH9kibE05zjNJ/DLJ2YELjPHFOqcF%2Bp2wmmpWPOeW8j5LKqsVZFUCtgnBLPcpYAoaEdtoTi8bBMNzpHt1edkE9iQ/nZCvZJboYIYXUimv58bi5sWDOsvZaoV37vPfe/ChMHLQr8uivFoEYrFuysoHtwkO3pnEge5Eekr3yz0k%2B4IOk1P/ntUtYgPq91XWOvFu71am1dr%2BsmadS6t1s3MBep9WICbxapvVr20Gla834fuqW%2BWFbxa1vpt4Jt7bu381osO7wY7VSzvVou6VvgjaFDNswK29txbHu%2BZDy9olb2dAgGCF9sda6bCbYB10kDpXJwDsHkj/lDhYBulhluuivDjOl%2BnTseqegBhjugJznoLjtkPjpgaUHBiTggeTizmeoBrToQbBuUBBqTkQSgczuQcMNjihmsDzninHtFkLmnh7g3JnhlFtNLmRmKnLiVtKorsrvRqhuriFk5oEIEP4BsopqctITSNJvHlhqbjcnclRoxiAJIP4KxtsjSKcvMpIGslwIsntEJhwIEALgnlckIZMhYUiioTFrYcXqsKWpkM4JIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/sieve/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/sieve.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/sieve.test.hpp)
