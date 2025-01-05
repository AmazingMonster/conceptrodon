<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-rotate">To Index</a></p>

## Description

`Varybivore::Rotate` accepts a list of variables.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function relocates variables of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper
   &lt;
       V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>,
       V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 0, 1, 2>;

/**** Result ****/
using Result = Rotate<0, 1, 2, 2>
::Page<3>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

`Swivel` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static constexpr auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        BackArgs::value...,
        decltype(front_args)::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcwQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpiprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbi8jlohAAntDsEDzKCGOCvJDoW5kGN0FgqCi0d8DtdlMRMDRVB99gCCJgWKkDIzcQREY9mGxSNcmHDUCSLmhMQ8CBSqTSoYFbtcCMQvJhoVYLkCfjtrgA1JiIul7BlMllMNkw/lELXNPBMWL0IXnMYKhwW5GqgDsFmuM0cyGuIrGmFUqWIfIF1wAbmJFVD3driFabUrXbdldHk4EVYCyX9s581eSAJLM%2BhsQTG7J6k55nPVgFVvbXIQAdzwYdqFYNReNSphHK5rG7qIuDq8TqbLbbJndk7TGaBjM7JrcmQAXpgAPoEAB02/zduHo%2BbrdouIJIBAESwqjXSgAjorRbj89vNyTAoPAVOLtdv3LDaylV%2BP64kCP6gb%2BC7dm4ZqoM%2BKK%2BgYCjvAA8o8xBlgIpAgWB369ow/bPhYTDIAA1ucxDAAoWHfnaoFengPp%2BoygbBtB1x4OgiLHoB34QFRYFbFs1zYIGhjoFCABsGiUtSeCqI%2BJKSXKqC%2BqsghyggmB8uRPiMAQ7xUMQqAsOpmkGbIL7cWB0k0vJb4hkQz5mYIa7NBRmGWaBAnXLkdQmdcVJjBZ5zYd%2BhEkWRFGwZZix8QAtHBKEJOhDB8cBHk/mFpHkQoZ4Rt4mDPu5wUhVg4K4dQhnOa5CiLLlkYFduqVvsqaJJi1qpZvWABKqBNIy7Zzn%2BXa4tBz6xvG9CUc1Q7yiO4o9X1AEfhmoHzkai4ruu4rnCwqkEDRP77uKlK9agyhMMAS2gZOK0hWt/7skNi6jY1dngkwiHPucwBUkyulTe%2BIXXF4mRGNcXVMHQ0qyqVtC4XxoG8el2FjkeJ4EOgZ4sEwxHrheAbXpgd7PJBO17a%2BgNAz%2BZ73V2bEcceMLfb9JZ6bBb4QNqyIwuN1qTSSU5Js%2BMXI9cMXpqlbUSx1xU4U9kEvZuzOYH9ggA3xIMRMAFIXZp0KyidRDnZduLK6rbOvai0sfjOpKXNW/x1hqwmsCymm5p1DuVjL6rXIlaH1AwA0XLTz0Cuz75HX7qHJe1mb2zcQheKk6RKOgXVvF4cPB%2Bcmtg0nKcZJg6eZ9n%2BvR0lge4mYvIaLyXC8mYr6zp74Ol%2BKHu56D2sZwoWfiuXC3DTCdfXA31w1xPdpnsbkGBNPIAQ3QuL%2B7HzXW071wACpvB39JAnRyAuYhCQEBAp4gAo/bH7ivf97yBep8Xd9wyi4sWBwyy0Jw/i8H4HBaFIKgTgbhrDWE9KsdYesQQ8FIAQTQn9ljEQCJITcGgkhmDMAATiwVwfw6CkhcFdK6aQ38OCSF4CwCQGg67/0AcAjgvAcp13gQAz%2BpA4CwBgIgEAqwCCpDhOQSgaBmR0ASFEfsnBVBJHErFcSkhrjAGQD6KQm4zC8GLoQEg7E9D8EECIMQ7ApAyEEIoFQ6g2GkF0A3RsaFUicB4F/H%2Bf8EFAM4EhOEAjxSoCoNcaRsj5GKOUWPVBZhrgQA8KI%2BgwZ0RcEWLwVhWhlgQCQCI1IYiyAUAgGkjJIBgBSBrjQOGCQcoQFiK42IERmiIgcbwSpzBiCIiQrEbQmAHC1NICI1mSEGC0BqZYrAsQvDACgrQWgOVuC8CwNjIw4gBl4CpA4ccEzAEBjaXCTYsCIiMjIYAhEsQ0KNI8FgVx8o8BUMmaQVsxBYhF3uDM4ACIjAIOWFQAwFFNSvEbIlf%2BsC9HCFEOIYx/yzFqFcdY/QhhjBgMsPoPAsQcqQGWKgVIgcJmxQJPrUwlhrBmHodcuMWBEUQGWHYNpgcXAMHcJ4doegwgREGBUYYDdU7FByDS/ILKiiBzmEMRIDcyVLIaOMVoHK/ACtqOSnoIreVMv5bYEVkxxUKtmAy%2BYzLSWQI2BIJxHBf6kDobwBhfiZFyIUUolRoTwm4C0TEmB8S4EvOWBpJgWBEgktIMgyQgRNxYMCCQjQkgzCSEkhofw4ksH6E4BQ0gVDAhcE3OJLg4kkhYMIeJfwkg8F%2BvEga1xDCmEgBYS8jh3CUm8M8YIrJOTokSLYJwZoLAwyulikweCUKx5YM3Am1Z%2BAiCEt0bIAxQLpAgqUGCyxuga62KYPYyZur9WGrcRwDx/C4TXB8SagJCj3pgy4F2nt4TInpOiVCEEZgHWJPYeWmtCQhHZKMie4Yu78m4LrkUxkxBSnlMsfU6pHS/2NOaa09plyum6R6X01xgzhmjPGR06ZUK5mAPwIsxwrYVkaNUOsxkHTtm1Fcfsw5iJjmbEAWci5sDrm3KUPcpDWsS1vIugoT5mBvlcg6f84dRjR2yFBRYwBU7IXPOxVYWF%2BziXItRdkdFmKZSidxfihIhK3jwFJZKoVfgICuCVXSqlsqFhcsyIHXTRm2UGeZV0KVwq%2Bimas5p3oLQLPypmBMMVehXP9DVXynVKw1jariVGvVLjLHGv8Wa9te6D1oOtX2kgZ742XqdaQF1brKC6pjXGrtgbXT%2BCwcQwIQaQ1ZrzaFzghbi1sOSWWpAfCvH3tvcQOtmxG2BJYAoMMPowz7s3P%2BMYGi4sDoblxwFPGTHyHHQJnQIBggzrnY4oLi783uMrd43xqg2sda6z1vr4oImPoyQlwISWqscNSQd6JDWLvDE6ynNc3WsFrl22uDbo66Cfu/RUqpjSAPfaaS08lHTwOCEg/0lDmAhkjLEPBy5iHZlkamQsqVGHXFrOQBsvDggCOWKI9U0jpy4yUd4NRu5TJ6PPNO0xj5XyfmcaHaNiQvHTGTfBTN4T0KcXifhZJoB0mBATK2KeBTlg8VGoJexVTSL7MUu01Suz9Kyg%2BbMyZ9zyvsjOY8xpwOjnRV5GVYK7XMrvNyo84q1XKqnPG8M5q/zRiF0hfoZwPxm3Ovhh212MYsXbUJbiQk5LqXhgerIZlkA2DNyBECP4fBWaaER9dCm0rjvGG2CLY6qrSCQCSH8L6ohroaFJEkLgrgGCzC5rIYEB3Rrytp6Sbq9Rieq/J6vYsZY1zMjOEkEAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/rotate.test.hpp)
