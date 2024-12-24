<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-repack">To Index</a></p>

## Description

`Mouldivore::Repack` accepts an operation and returns a function.
When invoked by a list of packed containers, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Oper
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Oper&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<int*, int**>` and `std::tuple<int**>`. Then we pack the result into `Container`:

```C++
/**** Container ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

/**** SupposedResult ****/
using SupposedResult = Container<int, int*, int**, int***>;

/**** Result ****/
using Result = Repack<Container>
::Mold
<
    std::tuple<int>,
    std::tuple<int*, int**>,
    std::tuple<int***>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Repack` is implemented similarly to `Typelivore::TypicalPaste`. Intermediate results are kept in `Capsule`.
After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<typename...>
struct Capsule;

template<template<typename...> class Operation>
struct Repack
{
    template<typename...>
    struct Detail {};

// Base Case:

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    {
        using type = Operation<Elements...>;
    };

// Recursive Case:

    template
    <
        template<typename...> class ContainerA,
        template<typename...> class ContainerB,
        typename...ElementAs, 
        typename...ElementBs,
        typename...Others
    >
    struct Detail<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
    {
        using type = Detail
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::type;
    };

    template<typename...PackedContainers>
    using Mold = Detail<PackedContainers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7ACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8cnBEwLCSBkBJgAzG4CABPO7MNgAOiREOw/2GxC8DgubiYSQUXnoEKsp3%2Bn2%2B5O2vzJFwAksD6GxBEwaq8dlSKRzDv9/oD6czMBCoUCQfzBTC4axMEiESiLsgDAoXgB5O7EZkZFFoggYrEAJVuTGQAGtubFiScLpaLryRWDIeLGJLpZrTlaLujMQRrph6nQLiYzQGrkTuR91hcLEwlNio%2BxQxarTbQQL7cLk2LYY7Ecjwdg5QqXh4mcFoqRrZn4VKkdgGYwCAoXQnLR6sTdfbRBUXfSFiIKa0C6wpnbnG26A%2Ba3W6vGkjOW7v7wVcLirouqBH3a4IhznUeCJ1agyGSWGLvrkMs0gA3TAxpQgeNupOi10HyH/SeJtOi%2B0Vp07/NRoWshMCWxAnKQ74ftaX52lCv7ZjKuYAYq2LAaBNiQR%2BDqVtK/aMgQJwKGWmGTthf4InhdYWERJGPvBVYIkqBAINEDYvpao5Wi2XptiBHaQl2IE9n8kKUYIhHDtgZaCehG4DoI1GSWWTEscQ26Iai7H%2BoGWlTjOwBzjeEJLrxdC0a%2BbjmR%2BOJ4gSKZuGJBHqWWjmKTuEG6VBKmsc6nkcbmIAgA6R5NtpwZ7g%2Bn58rBZEIcohpGpg7hoT2DYjlp07BAZACynjoAuJk%2BnxgrxcaSUyalkmBcFEUkrE4XmqSnJvE1lzYKorAgjeLUfM1bLxuY4LBPKXhYAuUJeF1jaDcN3hjYKaAMKsST1tNvWXBV0SspSPIwfZsUMScxDAGlmlHZgACOXh4MQzwXBAaQAF6YKgVDShAR0nXMBXGRckhzFqOpeptva1X863bBcQiTXkSX6vitBej1JyZbO0NJLD6DwwSXq/SDgrBAQZaE5sxOCNsZMEDsmpg61kPY4j21cqcqMGQzuOLqeBrGp2KXRI2gW5bQ6Dcm%2BWnDOg1WTYSkKEyiHmhRLUtTbL5OU9s8skUrQXS/ZJMa%2BlIm7o1EObBcAAqzxI/1pyTI4yAAPqAdEBAPQQksgAokpO2lbjs2W6OY%2BzKIA2DHALLQnDxLwfgcFopCoJwlmWNY7pLCsRlmOCPCkAQmjhwsRogPEkgIhoAAcZhmAAnNXXDxBX5dcLEsTSJHHCSLwLASBoGikLH8eJxwvAKCAfd53H4ekHAsAwIgIBLAQSReETFAQGgwJ0NEoSSpwqjlwAbAAtAfkgXMAyDIBcUgImYvBJYQJB4JLbT8IIIhiOwUgyIIigqOok9SC6DaAAdzVEkTgPAI5RxjvnBOnAlQr2Xl6V6Fx97H1PufS%2B19S5mHuh4Te9BiD%2BizlwOYvAJ5aAWBAJAG8khbzIGvOhDCQDACkGYPgdBARqUoBEOBERggNGhJA3gAjmDEGhEqCI2hMAOBEaQDe%2BElQMFoMIwBWAIheGADiWgtBR7cF4FgFghhgDiHUTdWRjhrz6PjpgVQsiV5rBzoTKocDaB4AiGqCRHgsBwO1HgbuBjSDXmIBEVImAbjGKMO4ow%2BcFhUAMCdAAak8EBK5Y45zfsIUQ4hv5ZL/moOBwD9AmJQNYaw%2BgPGj0gAsVAK0Mj6KPhLYypgU6WDMIPEJxBn7PHgAsOwliMguAYMlbIrRSCBBLDMAYbQ8jpAEGMcZcyajTH6DECYVRBkCC6KMTwLQ9ADIcJ0EYPQplrIOScxZFyphnNKDM/p6dVgSGgRwaO/c4FDzQYfE%2BZ8L5XxvngiAuBH7EMGmQihcSFgsSYFgGIEBC4gEkOCBE1dwStw0JIMwkgD693iAfau%2BhOCd1IN3bOCID5cAPuXauTcD4l3rqig%2B7zAFDxHmPXOcTp5zxoQvJBK9yCUGYUQnebBOANBYJeWIR8mAAVnFwauCIuBl3vvgIg3SX4/2yZ/CQ0h8lKEKYA3QHCwG4hES8t5A9eBD0QUvFeFxUHoJ%2BbKgy8rFVl3wagQhW1BpmHIRyye1DaGevoUQgV69g0sPlCY%2BVXA%2B40ERqxXh/DBESPkWIoRUiZFyKCYousyjVFwI0VonRej5FGJMWY%2BO%2BBbpHOsXAuxDjATyJce3eO7jPFCJ8WseO/jAk5xCWEpQkSK1ZU5QkpgyTUnpPkVkj%2BuTdWyAKQA%2BORqSmxNaVYSwlSIjVPhQnepAhGnNMXBu6wHSrVdJ6bu/pmyjnOAgK4K5bRJnFHObM1I8zMh7PGMkD9KzbmzA2R0bZlzv3jMOTUHZpzX13PWbYUDYzrmNFWbB55ixlhPLIYS15sCWWcC%2BRgs%2BUa5UKqVRoe6wK1UkOzn6yhBdSDQthZQF5xLSUKoxQkauLdwSYuxZINolr4HD1sOyuj1DuVIEXsgsNQrt67w4OKzBLAFCXivpeV1yZhgqpBc/PQs6clfwXb/fVy6dAgHBKQE1ECDHmtw4PBBfKUFUDQUplTamNP8mGB6r1oKs7glo5ynlsnGGCojUQkAqmMYO3U9XB2mmCAO1UKfThCaeEQD4YA9NqaglZckdIyx8jc2CHzWoqtmBNHaLEKWoJ5bondsMRY2tvTAENvPE2oJLa3EeK8dCLtfjul9t4AO8Jw7omjoDXwRJCgUmYDSXCGdsg52Gc1Uuop5m13GHKVu9t17901H0esJWp72mdOiOq3pNT2hbL8A%2BkZT6JkjJQ4B39%2BQMj3eWRkJ7Myrt3tqAh/ZQHrtQa%2B3ByYuzEMTBOSDtDChHlf1s8y%2BzHAXNn2U6pi4MWETxYo6qkg1HwX%2BqoVCzAMKBh7vbqxkANcETgnBPEBu/He609iFSxHVrOBsvHpC0gRdJDxBRc3WIvdy6SDrlwSuZgmXt3BHZ9nwmxMvLvmzoTEKA0LBCWkZwkggA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/repack.test.hpp)
