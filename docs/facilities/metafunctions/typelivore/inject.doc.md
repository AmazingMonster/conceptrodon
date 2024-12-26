<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-inject">To Index</a></p>

## Description

`Typelivore::Inject` accepts a list of elements.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new elements and returns a function.
When invoked by an operation, the function injects new elements into the location and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, Args..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: typename...
 -> auto...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<template<typename...> class>
            alias Road = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `double, double*` into one of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            // Note that we use a parameter pack in the template head
            // even though the function only allows one operation.
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements..., Elements...>()
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCx0gYWQSCCiXsw2KQ7tkAF6YAD6BHJ1zQOOeBGptPpsMCDzuBGIXkwcKs11B/0B%2BsOwL1dwAkmz6GxBEwmozDbqDQ7zhSblTsAxiHhkAhbU7rizzdbNfDubzWEGMddJuqHHc3R6vbCAOxWRMPLXO/3swME4ViggAOkLJslVyjXhjcc9CBzBHQIBAESwqlFSgAjhqZQSTYX8%2BTAhGQcnQXcR6rWVnOcGeYwwz2opgAO7YC2MAgKEujwVq8tymmoIgAWU86GHo5Mydh103m8zHM1V%2BvI4Jp8fN/Hd65075mB76LuUKYBQvgAeReYhrVyUgX1fEddl2O4AHVMDuLwlFhAA2DQaTpPBVC7dFf0w1VUDuRgfASQMMI0AAxYhZAAFTaYBMDXExMN7B8YJHbD6Xw/se1ohimJYhQoM4riQxnNgewsJhkAAa0Y4hmNY8TNw3V95kcZB/wESZMAANzEO4mEREi8HQFFaAgFY7gAWg0x84Ko%2BcFwANTaPAmFiegFEIjQTNpO4Im0TAHEwdBgoYVUEGQ2kCE2aLJI4q4YNAiimgJQTBCUlS/MLAVXOXVlV3y/MBVkhTcpE39%2B3TcTzzTQJtRBcTb2zKdQ2kwsipXQR1zq8TUIiYA7iPWhIrhFU90PY8CV6kr%2BtqjFmsxVN6tal17hNBhQpjH5QXayc3Ek78e2Ky1WMG0ttxjHa9olHUhza98OrcXNxVNBgm0crdo13OiiGUJhmOg88LDPNTRyOoMTq/WcesXC7St%2BzcyxjGbUHGk8oafZ7Uq42D4KifdkIIBBrTuBdkNQ5CmDudI2jDFliAZuT5KimKydelk7lipgcYJwnnMMxgYo2YBvXJ5CqC8HEbQEWgURM2haFQBcvgEZDUDAiCBBSwmRxhrkedh06Ed7ft/wMICeyuYBaUWq6B0NlDsiMO4ACVUAFpUVSwKFJOgmCIGDw3Ky9Gs6xAFgmHksVG0wZs2w7bYu2%2BpO%2Bxd13R3rGH5X3LG5vhBbLrK1HDbz03gss2gCXtx2y57AVkaWwt0RssPHxWDaYMajau7HANjvN7r81LlHrpg4aPexv2C9mib5qRvq12W3uz3W1adRe4fYdMog7YdzAnYG7ORxn0bgeY%2BfMev2GG5Ppv27q7fByalr7UdJkv8OWNVFYOyZCB1KTfztDvLaf90rgRtCAq4xtOpSR/C/Ac6M5TQL1gwAeoC/5CC8OkEoEVPafC8LQOUcDL53DwQQrIRCSFkPnhgzK8IIgEAFOgDYPlMDsM4fQfYApWH8KigQQ4fZP44P2F7eh5Cf7XEocQhQpC5RTS%2Bg9AkrCBGCCEYI/YJZ6z3wJFwPRIBsYEg4V4LhPCLF8OMd7AWBImG5DEc6Y09FPgyPATdCCyBRSASUO0CAxJ6wKDDL4gabgFFKIFNQwh6BIlkPRD3ZqHA1i0E4P4XgfgOBaFIKgTgbhrDWEFBsLYyEsQ8FIAQTQKS1jyQCJIfMGgkhmDMCkFIXB/BNKSFwRMiZpBpI4JIXgLAJAaA0KQLJOS8kcF4AoEA4yqnZJSaQOAsAYCIBABsAg6RETkEoGgNkdAEhRDDJwVQSR0J2XQpIO4wBkA6SkPmMwvAIqEBIBZPQ/BBAiDEOwKQMhBCKBUOoJZpBdBcFIAucC6ROA8FSekzJ1TcmcGAoiHZcpUBUDuOcy51zbn3LuI8swdwIAeEOfQVm5SVi8EWVoNYEAkAHPSEcsgFAIBMpZSAYAUgzB8DoCzOZEBYhItiBENoKJYW8FFcwYgKJgKxAepK0gBzLrAQYErJFWBYheGAG4MQtA5ncF4FgWORhxCgvwLSBweADKfCRUnMKiIdgVNYQ0JFyJYjgVlR4LASK1R4BGUa0gtriCxFoU8U1wBkRGGqWsKgBhgAKDch8Bc6UskVK%2BcIUQ4h/mZqBWoJF4L9CGGMIUyw%2Bg8CxDmZANYOsmiGrssSKaphLDWDMFMkNHosDVpsr0MKTQXDfRmH4CFYQIgjGqGMCFJQcgCGHXoGdTRFijESBCuw/b%2BhTA6J4Loeh13WoEAMdoy7J2rtsFu%2Bda6t0nuWFwNYCgSnbAkPCjgGSJlIumdii5Vybl3IeQ04lEBcBvMpeCO9NLY1rH5lgRIva6mSECPmFIgQ%2BkaEkGYSQmEND%2BHQmkAZQzSAjMCFwfM6EuDoVSN09C/hJAdOQ%2Bhd9oLpmzPmZU2NKz1kMs2Wi3ZbKOUUpOWwTgbQWAGUTHZemAEPZcBSPmEjOTXlEC7Z82QPyc3SDzUoAtoLdC8qhUwGFRqX1vsmbwaZqLtmIjuJir9uKblSdGjJuTjSSVkuZRS2E4IzDUrY0s%2BljLUDkoSHs9lgX3NjAczJrg4yaBkISIK4VoLpXiqVcl2V8rFVBpVauNVGqLWYG1bq/VhqKkmpLeanJlqN22sNQp1QjqWRKtdQMnJHqvUoh9TsHJ/rA0VJDWGpQEbysjXY/GkGSaU1pqVZmtTfyNOyHzSCnJuni0xpbVYctHqe21vSPWzgjbazNrLRYdtZnO0WTtTWvtB6/AQFcJekI30b1ToyFkWdeQd2FGnW9pd46lgvf3U0I926Cgjuu0D69f2V17ovZ9sH8xj1Q9Pc%2B9Ymwn13v0AixjUzOC2Z/dbEthLZPyZJcBpTnniM%2BdpTU0g0Gxi9vw8MkAgRZNocTP4FIvTAjocw7R7HZnOAsYWex1ZGytnopC/x45pyOAibxSwBQBkdIGSc3eSYLz8BKY%2BRCmb2a5sAvkFppbOhmeQuhZK4ziKmMop4xirFqh5eK%2BV6rwMkxXNhZZRTwIVORcBaC6y/ZHuKUgCVwQ0UKuUiijVwQUUDuNP8vi5QRLOS0sSqDanjL/alXZcELltPlWCs6r1arErxrWTla68avAVrHA1ftfV5ATqmuCDdaCtr4rOt%2Bo9L13g/Xw3l7NSNvzfAE0TcXFNoNuvfkSHm4Co3hbTcGDW8ditVb4A7b23sIJ6220doSF2y7vbAe5EHe4OHegx2VGh990ouQHuLtyM9s9x/D2w9B3uhoG7X8LCR7e89gwHsEchhf8p171H0/lLd%2BdkUOBsVHclc7gI98xo9SdNcSAKdwNfM6UoNMABZ6cX0CMRlWl8xAhAh/BOlaMxkSDEwKMoDmNbBWNqcVhakQBJB/AkMelEwxkkhJB2kuBmkzAGMBlAgrcccZlMCacBlnlaDBdxCmDg14sT9JAgA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/inject.test.hpp)
