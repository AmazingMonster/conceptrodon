<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Upend`

## Description

`Typelivore::Upend` accepts a list of elements and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided elements but in reversed order.
<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n</sub>
-> Operation
-> Operation&lt;Element<sub>n</sub>, Element<sub>n-1</sub>, ..., Element<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend ::   typename...
        -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Upend
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

We will flip `int, int*, int**, int**` and invoke `Operation` with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int**, int*, int>;

using Result = Upend<int, int*, int**, int**>
::Road<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amid`.
We want to label each element to record its index and instruct compilers to pull the element from a set by the index on its label.

First, we need to create a label class:

```C++
template<typename Element, size_t I>
struct Label
{ 
    static constexpr auto idyl
    (std::integral_constant<size_t, I>) -> Element;
};
```

We can pull out the element of a given index by asking `decltype` the return type of `idyl` if invoked by `std::integral_constant<size_t, I>`.
Here, `std::integral_constant` helps us create a type with an index for argument-dependent lookup.

Now, we will assemble an overload set and instruct compilers to pull the elements out in reversed order. Here's the entire implementation:

```C++
template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, I>...
    {
        using Label<Elements, I>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            )...
        >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQBspAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnufYJhoAgvuHx5hnF8hz6FhUDyerxeBEwLFSBlB5zcBFuqUYrE%2B2HobEEpBOmQAXpgAPoEE4ASUBLzmxC8DhOoSY8VoQJMAHYLGcXidWRjmo5kCc0Aw5phVKliCcmFdUCc8OhbrSWWyIL8QCAIqDgMQxDieXNDARoVjcQR0UTAthVicALQPE7IsGMbWBKwvBkAEXO9uBz1B4MhmGhsPhzDYADog1bUQQFMTnqTyfi5H70HTGUC2ScPRCmFCLqmvT64QjA0GLUcmAoFOjfXnvUak2yoxTHZhmnQzon6c67XSZays%2BnKzCwWmMzDc/7MEGA4WDCWTgB5eGqvro3V4seGx6d9lkusNph0aGzhLp7KLgjoBURLCqHFKACOXkYO2hBLHgKr64A9G%2BTgB1T7IYiYHthQYE5UAANwSWhUCYdAMQbECqDOJINAlKUTCQlMEGITZgAQcUGAQBJCEMHZx3XEATlSLxYhuLkqRpaEQxtUtCQeZ91wZV1k2TLxMiMSlqR6BiUSYg0HjPSVaGfdt1243jgBTXMvkdGc50PARoWrLiuI/E4olQUEMPTRCNF1VAqDHCACVWNCNHFBQMM%2BIhmloE4GFGIUzMJMdSE0rS2R0gB3BA8GQXC8HsphuQETVBFI54/O0z8f2Ff8TnQVAInk1ImGQABrE5%2BWy3lshA8ChQIAjYJ5GCn18hKdIAFUq/8FC8Wh8XC4UThuOZ4JOfhiBYEA6r8nTTPMoNLJNU0Ti4Rc8GxMyLKss0TjMdFvJODQA2ZeKErZLAjnLCARv28UJJOmSzq4%2BVFUETAVTVDVmkEU7rtZHUFr1ebFomgMptWglVq4QEW2dK6zusiGuNWNi9q0l9OLZJ0XQ7eGU37bNM0xnscz9REpOwblJwUMdnhVTBrUEcNX3RnjMpOAAlKCYPOZT60bWkLnJ/8qbDTbbpYJhctxc9%2BSvTBb3vXtxosxjqesqsjQVctUYdVs1bdN8ACpdb1/W3yBHXdYa7AhAavXDZeY39YNtG3gYI4vFOaEeR2VIwwjIFu0HcsR0JoFa3xfd52yTWgXpvihC8VIikwdBGcwVr2qUlSDz6aElV19Es%2B1nPBDzvDbUeaS3Uj%2BTE%2BT/E2ZOWNXEztEi8L3P84IXWIwVZnoL3VSM6V11A45EKcWLJRWjlE8FQURER5ptxo9jjJ48rtr9SZpPV4eRXXQ4dZaE4fxeD8DgtFIVBODcaxrAxTZtk%2BfYeFIAhNF39ZcoCSQAw0SQuHpQINH8BoMwSQkhmAABxgP0JwSQvAhpcA0BoUgx9T7nw4LwBQIBEHPxPrvUgcBYAwEQCATYBBKL6goBANA4I6AJCiIiTgqgwFJFNEkSQJxgDIC5FIAMZheDx0ICQCUeh%2BCCBEGIdgUgZCCEUCodQODSC6DmgFVUqROA8D3gfI%2BL8z6cGnFcMhfVGHMNYewzhs1P5mBOBADw1D6BCgfqsXg2CtDrAgEgKhqQaFkAoR4rxIBgBSHWjQdqCQMEQFiNo2IEQWi3DUbwKJzBiC3GnLEbQ9RsGPyoaGacDBaCxPkVgWIXhgBuDELQDB3BeBYCFkYcQBS8D/gaOBCpp9%2BT1CuLsR%2BSoejaJuLEVUSSPBYG0QQYgeAhqVNIGVWIS96w1OADcIwL91hUAMMABQAA1PAmAAr7mPo/ERwhRDiEkYcmRahtGKP0IYYwV9LD6DwLEDBkB1ioA9tkCpppfhs1MJYawZgUFlTGVgZ5EB1h1AaM4CArhph%2BDmmERYFQqh6CKFkAQsKUUZDRQwYYSKxhzQhX0AYUxPAdD0ISxo8xcXuXJfMDFBKqWIppVwcFt8dgSA0RwQ%2BSDtGoJOEYlhbCOFcIsVY3AAj7FmECCypxyz1gEWgmMMFpB36SECAGAAnIEekkhv5mEkEhABSQNVQI4DA0gQ1pUBiSFwJIYCNVgNtf4H%2B/gtUpGQbwVB6DMFP2WXgwhbjiH6KuOQSgvi7F0LYJwFoLBQL0lNJFIsfEuAaoDFwL%2BfD8BEGBcI2QYiTnSDOUoC58jdDrWUUwVRlTOXco9TojgejSFXD6jGuNCbiY3Nmqm9NtlrGoFsQkM4UqzCON9Tg1x7j%2B2eLsaGyhU6/GtvjUmgJGr4F8DoKCYgYSInyISTEuJpA91JJSWkhwB6sk2hyXk7RhTimlNoOUg91Sbl1NPvgRpjhmnaLacgDpB7un73kX0gZtwhm7FPqM8ZB7pmzLBC%2BzKfrVlMHWVsnZeyD2HPzRIwtshzlyNPmW65SzflWHuX00Frz3nRU4F8k8Py7kWABZ6oFEok7wHBT0dJ2QXAMHcKS/I8LePUuWIkOaqK%2Bj0rSFivownkUEs45C/odL%2BNwu6L0SlgxZP4omIMSTmpWhadE6yrY7KWWmtrbyzgKVY3xsTQYZN3av5iqzSQId0rR3ONfqQBVWBEjKsA%2Bay1qbv70ldfSP%2Bkh9WsLmnWr1tgfWedcQGpAJCyGzvDbQ%2BhHAY0mJYAoUCXJQIpoDF6OYmaJVCLmph452GpHyGLfhnQIBggVqreo8zWj5GoMbQYzyOW2F5YKycIrqbSv4j7QOyVgRAgeb9YGjL3iw3zrsSAArsccQjZxGNkeg1WHrpCVuygO7T5HvyY/U7J70nnv7dk3J%2BS32YCKSUspFTH7PtqeBqpDSuNfvkT%2Bv9kyAO9MeSBsDIyxkTMfjBpQcz4NLPHXwNZmztm7L9BhvNNWJA4ekQ1y5zWiO3L%2BWRx5FGz5Ud5JwN88oSP/MBQkYFbGXlqa41CmFKm9AIvKMyqTxRsiSfE9kQz5KFNEuU3kVTFKBDEoWFzkTtLdPs4ZZpplcuzMKDZRImtnWUFWf6ycQbhXitjecxKtzMqx0uPlQBXzlBOWBZAGYVN03/CAJ/gg6b9I7U8q65wb1WC5UqpAJIfwmr/BgOARqyQGq/7aq4MEQDgRteet9xbrzgHeHe512g1Pqx1hlUyM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/upend.hpp)
- [unit test](../../../../tests/unit/typelivore/upend.test.hpp)
