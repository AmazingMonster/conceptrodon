<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-erase">To Index</a></p>

## Description

`Varybivore::Erase` accepts a list of variables.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the variable at the index from the list and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the variables of indices within the interval from the list and invokes the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>J-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

```C++
template<auto...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 2>;

/**** Result ****/
using Result = Erase<0, 1, 2, 2>::Page<1>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Result ****/
using Result_1 = Erase<0, 1, 2, 2>::Page<1, 3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

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

- In the case where the second layer of `Erase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_targets)::value...,
        BackArgs::value...
    >;
};
```

- In the case where the second layer of `Erase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_args)::value...,
        BackArgs::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEpIAzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJUql2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSXUtbR0F3QpTwxGjVeO1AJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimGmujMh4mAoPp1e39wuQLO/xu1zBZmSEWQ3iwDxMyTcXkctEIAE8EdhweYoQwYV44Qi3Mh5ugsFRMdiAacHspiJgaKpfidQQRMCw0gY2USCGi3sw2KQHkxkahKbc0HjXgRafTGfDkk8HgRiF5MAirLdwYDDg8AGpMNHM46s9mcpjcxEioj61p4Jixejim7zVUOW0YrWBCwPeYWvDIB6S%2BaYVRpYjC0UPABuYjV8O9BuI9sd6sCTw1CYzyU1YOpwILf21NIAkhz6GxBP6BMbLsXCw3QfXjs9CMgELXTeWLerEbz%2Baxe1jbq6vO6nm2OyZvdPs7nwWzu5a3FkAF6YAD6BAAdLuS87R%2BPJ0TSSAQBEsKoN0oAI5qqVEku77eU5LDsEz24Pb/Ks1c9Vfj%2BRLgj%2BoG/kuvZuNaqDPpiQYGAoPwAPJvMQ1YMKQIFgd%2B/aMIOz4WEwyAANY3MQwAKFh37OqBfqOIGwZsrGtCRjaeDoGitBUQ8EDcaB%2Bz7A82BhoY6DwgAbBodIMngqiPpSknKqgQZbIIyoIJgwrkT4jAED8VDEKgLDqZpBmyC%2BgHYdJjLyW%2BrEwbuZmCFurTAJgemYZZYECQ8ABK7KoNGmkEBpDyRKoO58T%2B0GeTc2Hfj5eR9CZDz0vMFlxfFhEkWRFGwV5azcQAtHBKEJOh3HAV5oFYDCuHUIZzlTG5elrGezFqs%2BsXxQ82WkeRCjtXGmD5Zl1Fvhq2LppNWr5i2wlpF4RiaUWtyLuay64QKmBCltg4HiqY4ygtS1uQmVjTTmVI3Ot/4nng65bs%2BJZCmum47ruABSB1usdYanZBp7ngwl7Xpgd4fJBT67pir0EOgZ4XqGYMQw%2BiKfbBE0TV6uagbdPaVYiUU4X%2BBNWqKmPYPBTCIQ8ZVof03XxXtbAEUR/UUYT760S09EqQwIbMfZDzsZx3G8dVP4%2BQtokSVJcqybZWKKTaaBLTKIWaa5OmCPphnGZrDxOZFkvftZiuIvudnQc%2Bxsbq5ChM9h0siSDcvm3J6MKRoSkqerKVLQA7oYbJidrlZ6RlPUe0S33WxTu5O95glJQ0GuhWlJtjWBfW5Qoo2gYVXklXZ9MVV5VXZzVDS0PVdsO21IAdSNifE717N50N3gt1HQFY/Ol3znNurYGhSidgupPLjbu5Jim9CUdjLqHe6o80wBH64z%2B%2BPTwnL5Lzzv2yqgRDKEwZ3Thdc7XXjU%2BAw970PCWIOhjRP6HjKdIn6gZ9uY%2BL%2Be25kBT8Vdt53x5OA8mRBKbU0Qs%2BG4wB6Tsl0ovIB2EvBZCMH5JgdAFRKlqrXPkG8eoS1AdhCcBB2wnnhmeFgTBiKbiRleW895dj/0vK%2BNBPUHhnh3ppUWXFEQIKQRHfOMM3wQANBiREc8HQL0pDOdMz4i5kIeIVK6FdB43zARBe6j0ZSDDaK9B%2BW4hIgzft%2Bekd48BpR4oYmUwFFRmPQCow%2BR1j6n3PpBexQpsDmIPsAre2E%2BEQN0VAhy%2B8qYwhpmI7cwjMDIN1hYsCGCIjAGwbghE%2BCa64TbqQ7hP4TrLTbqBSuBTsJAzoQwjcTCUasO8QsWGJT4qVPoYwgBdTIZEj8egIq9jkk9QGfFXhd8RYcUEW4eJiTI7iOwJIw0RJZGplQZfWcyi27qKCVmGaeZs4hPCfAxBCTRHJNSVg3%2BmkskeJ/l4okUzRGUx2bOJ5w8GwXFBDqB4AAxGx8whKqFYJyFaLJmxvPeddT5Zd%2BgTzWpAqCe8fruKhTkF5dwaRCC8GkYomB0D%2BQUF4WuMKbhnPSRirFmQcV4oJQ4pxyKBBEg0EKMwTLXxDzRY8KlhLVrEswekzlNKlRryUAyoUXAmUsrfGeC5RIuCYjPL5HBEy6UMFZRCmkAAVb4MpuV0QDPbRCCQCAQCBgoQc%2BqiRkuxbi741KhT8sxJstVYLgQfPRQ0AQYlhKAvoESnUzqQROpbJail1r8VcpBbcElDxg1KFDdSjcXA8F01QhVREjKHhmFVbNdlLZ%2BVEqjfyhNSahWQXTWKjNErsBStuYictyQ5UgAVXQIkyqs27M%2BZqv5OreZ6piYa41NCQCmrYOaxEMbKU2trgmu1k6CAJodRqDgGxaCcH8LwPwHAtCkFQJwNw1hrC%2Bi2DsS5kIeCkAIJoJdGxiIBEkNuDQAAOMwZgACcL6uD%2BEfQ%2BrggRAjSBXRwSQvAWASA0IyjdW6d0cF4INRlF7N1LtIHAWAMBEAgC2AQRaBByCUDQByOgCQoiDk4KoB94kiriUkA8YAyBAxSG3GYXgOLCAkHYnofgggRBiHYFIGQghFAqHUAh0gugxWBzQmkTgPBl2rvXZe7dnAkLIiww8VAVAHikfI5R6jtGHj0bMDxDw%2BH6ARhxFwNYvB4NaA2BAJAeG0gEbIBQCA9nHMgGAFIZlNBa4JEGhAWI8nYgRFaGiKTvAgvMGIGiJCsRtBpzC6QPDEckIMFoKF4TWBYheGAFBWgtBBrcF4FgOhRhxAZZsWnPAQUCtbtDA0ZEewz0RDZABrdqJYhoSix4LA8mVR4BA4V0gQViCxApS8ErwBURGEvRsKgBgKJ6i%2BIHMqG6z0ceEKIcQvH1sCbUPJ0T%2BhDDGH3ZYfQeBYiDUgBsVAaR%2BgFaKqSLJphLDWDMJB4byYsCXYgBseojRnAQFcDMPwYqwhLEqNUPQxRsgCGB1DzIMOGAjAh6sHofQmgLDh2Kv7/R7HI7GDUWwmPPCdD0H6No%2BOVg1F%2B0e3YEgZMcDXaQCDvAoMabIxRqjNG6N3oMxAXALHTOnos%2BembGwNJMCwIkH7pAb0pG3C%2B5If6NCSDMJISSGh/DiRffoTgQHSAgeSFwbc4kuDiQfS%2B794l/CSA/Yr8SzP5NQZgyAODM2kOods%2Bh5TyIcMuaMg5kzRG2CcFaCwaMgQipMGplgrgL7tzG9q/gIgn32OyC41t6QO2lB7eE7oZl4mmCScKwzpnLOFMcCU5h5Eqn1Oac5zH9JceE/3sMwHxz8JIRmBF1ZxDXvXMmb9wP8Y0SjBx64Iy7zbJiB%2BYC8JiLIWEsL6izFuLDgEtJd0iltL8nMvZdy/lhLxWjtla3fgekjRqvybq8gBrCXmu9Hk%2B1zraJut7C3X1gbZ7hujaUONk/aS7uc258Cgi2mAy2/ICW62GePGWesgu2QmW6%2Beh202z2Vgp27W3212t2OQ92j2ioaBr272CQn23w8Av2vQlWAOQOJOBQoOIMlOkOYq0O/QWO6QCO/QjBqOOOGOQwbBPBAgeO4OBOZOxO%2BQIOROQwXB1Omw2wdO5muujOcmwmbO9e2mo%2BTe8eiePEAuKeneRuPeYupAEuUulADO%2Buhu8eKugQ/gL6v6yQqu6utujuKhnALubuCGNmnuSAGGWGQ%2B7eQexGHAYe2mLACg0YgY0Yze/48wTGyerGCMYq0Bm2sBfG8gOeiBOgIAqQhexe0mihZeTuimPuMoamGmoR4RkR0RPYfyEARmgeCQ%2BhyQhhnhSGdmARCQ/hxm4wERWKG4URL6G4MRc6qglGfAdA0%2Bs%2BgWwWUWS%2BMx0WsW8Wg2m%2Bgg2%2B6WZ%2BmAWWOWYgh%2Bg2x%2BpW7%2BRWFWl%2BZBwmN%2Bd%2Bg2D%2BrWvAz%2BIWb%2BvWyYX%2BvAP%2BY27IAB02rRwBC2S2K2UB6eKRSQaRCB%2B22RKBx2L2GB52WB26OBAgBW%2Bwp4hBlgb2rOH27EZBV2aOVBfggOIMbBYOFQIhzBHBOQbBLBOQ0hZOlB/2AwYhpO2O1JuOCwlJ2OdJdBkhFOwhVO9Oshx6PJAGhRrhHA5RVGYRERMY1RbItRuhJA%2Bh5mlmRhJh4wMuAGFhIAr624yQyQ/gn6tuYGWpgQ5uLhkGbhtgruounh16IAkg/gCuP6gQYGD6kg76XAT6ZgDuAGyQyhJp0GFp1mDOjGxprOppveawGww2WQzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/erase.test.hpp)
