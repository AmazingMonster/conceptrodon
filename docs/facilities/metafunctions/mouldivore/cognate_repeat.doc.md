<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-repeat">To Index</a></p>

## Description

`Mouldivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.
When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Oper
-> N
-> Args...
-> Oper&lt;Args...<sub>1</sub>, Args...<sub>2</sub>, ..., Args...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `Vay<0>, Vay<1>`:

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SuppoesedResult ****/
using SupposedResult = Operation<
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Mold<Vay<0>, Vay<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `Typelivore::TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the iteration completes, we transfer the elements from the final `Capsule` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `Typelivore::TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

We will use `Typelivore::TypicalReiterate` to reiterate the elements.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** TypicalReiterate ****/
template<typename...Elements>
struct TypicalReiterate
{
    template<size_t...>
    struct ProtoPage {};

// Base Case:
    template<size_t I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<size_t I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<size_t I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

We will use `Send` to transfer elements from the final `Capsule`.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename Typelivore::TypicalReiterate<Elements...>
            ::template ProtoPage<Amount>::type
        >
        ::template Road<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEoFmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbmQE3QWCosOwIJBfz2t2wqgIrgsTGQAGsvocgXiWKkDHjYW4CABPZ7MNgAOjZqJBE2IXgc2Nx%2BMJJJMAHYrML7rCrFcQRSqUwaXCQbdlbdZdTMLSGUzWJg2SzUbdIUwFJ8PIImBEEqQlSqtYwdXrsPQ2IIFOjAmirlyeQQ%2BXiGOgCcTaWaWpbiLSnZgXQQFHqOR70aKbcq1fKNXC7czdWzLsBiJho4xYxyrirbl5MkZbgBZTzoGGBe63UMWyIRuFRmNxtmkW55gtF13xxOBKXA8WS9G/I4tpipBReeikg7k6NyhV0xn21nsxNegjc3lueeL%2BhT6VXbMKVKEzC3AAq29oeAAbiR7yLxzL1%2BrNdvs0dZ1izdfdLm9Xkn1SPBRFoAAlTBCASdMk3Hcs003JgvCIEdPUucsIN9ZRiFQIhlCYYBP2TScx2na4dluAklDnJQQBTVVfxQuEsKIW4AElS3wlUCwARy8PAC0%2BCA%2BMbCUm1uDRlnYwjbmI0jUHIyjaQEsDyy/djy0rCJgFVbdZLnBclwzNwEzQlURTk78y1tTjMOw1B%2BME8tRPEyTbmk2TYWbLglOc5UVLUsiKOsnS8L05MwvLCsqxMu1zJPSzz07YDhz3NFaMShyL2BX4GIQ5ANkyV97xPVj2Iw6yeI82L2J8iSPn8sxGxs%2BS%2BNCoTwsPH1VJIqKtLhFrCoSgakqM6s0qCv0BWDTMAJ1Eb1M0mLbgAWluMxURAEA7S8pLlSOhra3rSMctjPU%2By7EDcOK%2BLHLo9DXMa9y9QHQtu1O5U5pMrbzMijTotpX6hzuvLiqKgqSonCVL2uWchFcFczh/Sk/1W7Vd31MCVPRgMYWot6UYazVPv/fGc0J7BDQME0W1kNsrVMumgOh0C8OJ1wQzZ8Mbp556wP0xKqczGm8Z3emDSNFmAHlnmIeVsgB24VMeMNaHYiWZsMlLOc/eSVeQxoRe7MW7OVeGnJmqW6RlrcubypnjR7Fkof%2B3SVSB244NQJgG0WnWLT1uEfaevKLu3OGaIdzEARTrGZzuPiceh9WBExoFk9T/4gWxjdrKdrMHXdxXPnNtXLaJobj1QYBmDxBDnnlVD6pdzIAC9MAAfV9S4WHWQRNYi0bwa0qbbaS8u1oJx7XU1o3jKu2hQ/kkn0AM%2BzFUSs7U0X%2B8oPqN8PyOqCYLEBCkLr6zl5hhm97Oi7Po2sbrJHseCEO4746H33nFI%2B78cbpkDsHXecJa45wYLZfWid3ouXAZuPug8CA/XzH9ECmsA4g0WmDLakNsGi1hgje2dEC6p3zrOHErAqT3m%2BBiQugI6LmHBAwSEXhoS0jQFwp4JZxbpwOLcAAakwekecS64xPO5TyDcjy%2BgkfSVCWsWiOGQIaAQExMCqFSMQW4TVbivjEF4KiFgBKJzJhTRGmJbiwMaNIq4C83YvwPEohxqs4FwxEViIQXhUjpA%2BJgdACEzy%2BmYVcAOASgkZFCeEpcvpFqOI1gfGaKjaQaFRH2TJcIuA5PYnktw2SPS5MkbSApZSikVLhKU7A5TVH5MKYlYp9TGmVMEgglG9jEm0EiWSEEAc%2BnJPkh4Fu6Z26YE7jA7x9c8JHWIXCSQgkjp1k3rSNpOTxG1LcFU/K%2BUk6zgfB8AZq5OQaJggPT2CQCAQEREdBQOprmgTcCMvssSigJI%2BEk1ESkxwcFWLQTg/heB%2BA4FoUgqBOA2UsNYLW6xNifjBDwUgBBNCAtWESAIkgWQaAABxmDMAATmJVwfwBL8VcGFMKaQwKOCSF4CwCQGgNCkHBZC6FHBeAKBAGy9FELAWkDgLAGAiAQDrAIKkbC5BKBoEpHQBIUQdScFUPigAbDtdVkhbjAGQFoqQLIzC8FCYQEgeB0B6H4IIEQYh2BSBkIIRQKh1CCtILoLgpAADuatUicB4ECkFYKMVQs4ErbC0rfSoCoLcNVmrtW6v1bcQ1XUIAeAVfQQxHCQq8AFVoVYEAkDyugpm2VEBi2KsSMAKQKQaD9ISLyiAsQQ2xAiK0ek/reCtuYMQekStYjaEwA4TtpB5UxiVgwWgHa3VYFiF4YAJ5aC0F5dwXgWAWCGGAOIGd7UHBvg%2BCGvRQ7sLbFRREPE9LIUvliGrXtHgsAhsPHgZlq7SDVWILEeJjwN1GBfEYDFqwqAGGAAoMR7wvXm3Bai61whYL2ukDB51agQ0ev0JulA1hrD6DwLEXlkBVioFSI0FdO1ERBVMHCywZhOXvuIBag9%2BGehDsaC4AM0w/CerCJaRYoxPVFCyAIdjeh%2BONAWCMaoTG90CH6FMTwnQ9B2GY30SYgxuPiYUypoTnq5htDE5UXjqwFCIq2BIQNHBQXspDVy2NGqtU6r1Qa3FqbcBmqzSi5YuaAOrAQNMrAiQIBYpAJIQILJiWBFpRoSQZhJDqtZf4dVxL9CcEZaQZlgQuAsnVVwdV%2BLiVUvVf4SQ5Kwvqss26rlPK%2BVooA8KsVhaJURplRQctqAM1KpVRwVoLBXzCh2kwD21YuDEpZBlyFpqiB0ctZ6mDtrxAOsQ0oZDbrdApB9fOTtZmLMct4Fy8NUrsK3GjTZ%2BNOqjSDeG6N/y6aS0JBhGCMwHnquCoLUW1rN2yDNYrZmlABgjBDa4GyuteJiCNubW67t7aR0Q97f2wdw7X1juLBOqdIbZ3zsXcukd67N3bshfgAse7qorrG6oY9eIR3nvqCG69t76T3u2JCp9L7UXvs/Uob9OPjI1aAxRUD4HIMjpm3BiQCHZBIddZClbaH/0UasJYbDuH4AEaI9kEjZGmyy%2BsNRnbtH6N4YC5JljEBXBaZCAGPTSw%2BMZAEzkOT%2BQrfFGyBb3jhvlMDFN4pqTTQVPO4kzp9oduOO2B92p/T1RDPGftZt4N5XODHbswNkyQ2Rt4v8i5ibd30uPbzZi0gPmQ6jAN/SlLaXhuReFP4YlNLAhRZi0VsrnLOCVf5TVkV4rJWRrLV99rbBOBdYTSwBQr4tGvmT%2BqCYJr8ATYtVa2Qs34OOvkItiXOgQDBDW361d0eG87bDY1qNMbVAD6HyPsf6YJhXbe5WzPgRs%2Bt9e21j7cqr/feH0Egeo/iUD3HwQAeR%2BEN0DA6g4tptq9pQ6gF9oDrMYjqI6CDI7Tp46YBzoLpiCY6vrY6/oM5rq7qOBE6Hqk4VTk6vqU6Xq8A07tr06Pp0bM68Cs5frRic7/rPZ8DAZ86YAQZMiC5z7C7zZi7L4oZr7S7GCYby7Xr67K7EacA7APKa5UY0YJCTYMYG6e5G4m6B56BcblDqYO426m4iZO6h6W6u7SaabqHab1BKYmHzCGEu7%2B4e4h5aFh6mZrAbAmYhRJbmYx6N4cCxrH7D4mJn54gX4QDp4kCZ45pPb5rea%2BaF5mYl4gAkosiBCBD%2BAUpFasrJHCg5Y76hrcq2BVY57LCBaSD%2BChbUrCisr4qSBkpcCEpmClb0qBBeG755GFFmbGo5EVaRG57vqZDOCSBAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_repeat/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_repeat.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_repeat.test.hpp)
