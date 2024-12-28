<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-front">To Index</a></p>

## Description

`Varybivore::Front` accepts a list of variables.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects variables of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three variables from `0, 1, 2, 2`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    static consteval auto idyl() -> Operation<Targets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCx0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf99ncAGpMFGMw7M1nspic%2BFCoi6tp4Jixeiiq6TZUOa1ojVJCx3eaOZB3cWTTCqdLEQXCu4ANzEKthnr1xFt9tVSQeatjqcC6pBlMBuZ%2BmqpAEk2fQ2IIzblDecC3na8Ca4c7gAxEiYKvGktm1Xw7m81jdjHXZ1eV0t2mxqwptUUq4szvmtzZABemAA%2BgQAHRbwuO4ej1sE4kgEARLCqVdKACOKolBMLW435MCg5BntBdw/ipNHNV10/crcd9/0/OdTQXS1UAfdF/QMBQvgAeReYgKwEUggOAu5dl2O4AHU2y8JRYRSDQaTpPBVDvdEoOIxVUDuRgfASLsiI0AAVNpgEwAgFBMYjHz/DDpTIij4R3Z8H3Y4hOO4tCBIw3tGH7KC5LlF9/ywu4olQFlFQQM0WMQpiml4jQ7jwL4IgjVAAGtMHQO5YgNKNvE%2BdDMOwoMlSYBw7LuKhiFQFhdLbUCfzudI2n7FliAUfirnU7DWIQcyzK%2BeJRAItsAHdsroWhwu86z6IjBIDUIVk3I01AqBY%2BNE3oWKtxMszBDoky9TRPi3J9PA/QDFlnLDK08HQFFaAgFY7gAWmgwzkOM%2BFJOkhRj2clUoOfacPQzLMG21JsAsEdtQVCrsCQgh86rtBrdyVEcpQO2RMTfFTToXZc1ylK4WA2QRHX/PcpRpbTUGUJhOLckwXviwS3u7Nw4fO4UNuwGCmDgh8rmAWlWUYbj/sEgiImAO4ACUmDoOUFSwKEFLc/8IHpwSx3ho8QBYJhbNXU8gwvTBrzeeHvt%2BggnzUwT/2POGzNG2gCSxnGy24h8BQ6gkrqTHjxKa58JqZj8Vi2mGPyhnaZ3/RGLWRrcFcwXHBC18WPyJoxqXBts4QVYGiDBiH4Vt%2B3lZ1jFM2es2NRzWsmT2u5sFUVh2TbfNI6j6sI5uKk5pQhhjuuS23Au4PQUBu4s4W3aU7uIQvHSEo7NJz4vFoKVk6uF2Ser2usnrxvm6p0ukOzgkNAFLgBTMJ8K4z%2B4G4UJuW%2Bj6527J3upU95tDtF%2BER7uMe7jMcf0WPX34cCI%2BQHJugCTL3JJ5nLU7lYz4F6NYvWl9Vd0aUdoIDZhR%2B0/lrNwnc67oFnvPAU4Dm7okNpmDgaxaCcH8LwPwHAtCkFQJwQClhrDeg2FsD24IeCkAIJoeBaxrIBEkBuDQAAOMwZgACcjCuD%2BDobQrgSQkjSEQRwSQvAWASA0CPVB6DMEcF4CtEepC0HwNIHAWAMBEAgA2AQdIiJyCUDQGyOgCQoj9k4KoWhKQpopEkHcYAyA/RSA3GYXgdlCAkBGnofgggRBiHYFIGQghFAqHULI0gugx5ZWQukTgPAEFIJQWQjBnB4KInUVKaqdwjEmLMRYqxu9qFmDuBADwOj6ChixFwFYvAZFaDWBAJA2j0i6LIBQCANS6kgGAFIA%2BNBm4JBWhAWIMTYgRDaCicJvB%2BnMGICieCsRtCYAcMM0g2ilbwQYLQIZASsCxC8MAAutBaArW4LwLAHMjDiDWXgWkDg8AlT2egoMMzEQ7GIREFkvD0HIliMhcZHgsAxKVHgQR%2BzSAlWILEbuTwjnAGREYMhawqAGGAAoHUHwsqGVQcQ1xwhRDiC8ei3xagYlBP0IYYw1hrD6DwLEFakA1ioHSE0PZU1iSe1MDgywZgxFAoTFgSlE1egzKaC4Bg7hPBdD0GECIIxqhjDHiUHIAgZh%2BGlVkWVDBFijESGPOwfL%2BhTA6MKwoGqGhaoEAMdoqrJXqtsDq%2BVeh5imvFUsKVawFD4O2BISJHBkGkFEbwcRKTjGmPMZY6x2Tcm4EcUUohpSSHQrWAgTATAsCJB5ZQyQgQNyMMCNwjQkgzCSGIhofwKRGH6E4Pw0ggjAhcA3CkLgKRaGMI4SkfwkhWEZrSN62JEjbAgGkdC%2BRSiqkqISRohpTTCn6LYJwNoLAIxJCmkwNGrsuCMI3FWm5%2BAiCcpcbIdxWLpA4qUHigJugD4hKYGE/Z7rPUdvEfEtRiI7jJNSQGxdJNl2rpobk/JtTCmwnBGYKN5S5GDrHQkTRjTAo/rGFCIly6uAjw6dFbpvSAmjMGXMtD4zJnTNmQChZeMlkrJieszZ2zdlzMOUSk56D8DnMcFcmJtzkD3LmU8hoMS3kfJRF8nY6Dfn/OIUCkFSgwVUeJn22F4MEVIpRXM9Fu7PH7tkLi/x6CT2EqhcyqwlgyUUvgNS2luR6WMvlFp6wbKfUcpGp8fTvKLnOAgK4a1Y8xWVDVXoGVTRnMZCVU0M1ywDV9GNVavVCq7NNBNUMe17mNUhYKGF21UW3PmrdesTYrqSklo9dEgJvrn3pJg0ulda7Q0bpIH%2BytgGY2kDjQmsYPLeFlorSu7NSR/CMK4YEHNeaW1epieIyRPbo2yMqQOpAqjEngdA8QCdOxp3pJYAoCMfoIzvp/JMexZWt1j3k5ixT3j5CHtUzoEAwQz0XoiVl69/W4nDqSTVVQC2lsrbW12SYX7IN1Iq4EKrI35HVM%2B4UqbgOxjLdrquVbjDVzrYIKuR7%2B66BIcoCh9BmHVnELR9hvlcz8OCEI6smjmANlbLEORgFlHjm8YOWcrVDGAlMZYwCtjLzeCccGTxn5CYBO8CE6C1kYmoV/ck/CxFmBkW8jkzuvbEglM%2BKO/i07GniUspsG87lBm6WcF2EeMzrL2UJE5TZql4XcgCqFfF0Vgr/NSp86UXI3nPO5GtxazV9nmhxZFYFo17uFjRZS7FwY3nEvO9S869Lnir05bEZwFJT3luRleyyd7EAw2boqyUsp1XauJsoO6prIAmEbkCIEfwbCW3COL6kWhfXcucEG72kbFCQCSH8OmzhSRhG0MkCwrg9CzBpF4YEKPPq6/DYqe6uxNfo9dqAysNYQLsjOEkEAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/front.test.hpp)
