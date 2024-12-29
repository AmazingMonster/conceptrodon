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
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

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
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<auto...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    // Note that `Operation` is invoked by values extracted from
    // the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<BackTargets::value..., FrontTargets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

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
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCx0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf99ncAGpMFGMw7M1nspic%2BFCoi6tp4Jixeiiq6TZUOa1ojVJCx3eaOZB3cWTTCqdLEQXCu4ANzEKthnr1xFt9tVSQeatjqcC6pBlMBuZ%2BmqpAEk2fQ2IIzblDecC3na8Ca4c7kIAO54CMNKvGktm1Xw7m81i9jHXZ1eV0ttsdkye6cZrOglnd81ubIAL0wAH0CAA6XcAKUdo/HrfbtAJxJAIAiWFUG6UAEcVRKCXvd9vyYFhyCZ9c7n/FSaHK9m4oL/mBAFLsBlqoG%2B6L%2BgYChfAA8i8xAVgIpCgeBf40nSeCqC%2B6JvgAYsQsgACptMAmAEAomG/thio8owg5vhYTDIAA1pRxDUbRWF/o6YE%2BngfoBiywahtBdx4OgKK0BAKwCXcuy7HcUSoCyioIJgdwlDkAj%2BgghjUXcqBULCABsGikRRVE0QosHWYKDDoFZGjsVxPF8Y5JjWcpqnqZpukEMZUp%2BRoKEJOhDARTJXwRBGqCcZgbmxAaUbeJ8dxBkqHEsm5VBkSwAVqaFIWAT2eltIOLLEL5DF/oF5EIHgCVfPEoheEodzNrpra0LQ1VcTl7bEAahCsqVZkWRF8aJvQjm7nFERWnN%2BoRe%2BjV3AAtHBUVoU0BKedx9m0ZemUqm%2BAq2YI3kORd0aYLBn5qpiKZvRqOaNgASppVX5tci6msu0FvvNdqLYeSpjlKf2tJyHpZmBwNAeeeDrludxXCwGyCEJ/5HlKNKaagyhMNRynTsjjGoz2XKVaDwovdg8FMIhb5XMAtKsow/GvdtYHdREwB3D9TB0HKCpYFC/aqoL/4QMpjFNieDTngQ6CXiwTApRu15BnemCPm8wE43jBAfl%2BKtgZedNabJ8kElzPNlrR11ugSENJgoRHLZ%2BinK/%2BSmZlTH2h19Vwo4zUHM7uLuYLzgi%2BwLUf/sLRjUhTulwgqJNEOTlPwgnSfu/7GIR9%2Bc4UjctZAg22rYKorDsrpgO13XTI11qdwHTFnYLjHBJg%2BXoJE73qExZ92Yd42QheOkJSpT9nxeLQUrtxnovz4vWTL6v69SxP0VHfCZgChoApcAKZgfvO33aivChrxvXfXFvYsH%2BF8pi/9y6X3ca%2Bdxz7AMdJeQuwFAhgJAOLOgBI%2B6nwrvfWe2pyKfFfkaMeCNRIbnZkodoEALwgAUIOXBKc3BPxfgKHeS90CUPXuiEOFgOBrFoJwfwvA/AcC0KQVAnAQKWGsN6DYWwc7gh4KQAgmgWFrE4gESQ24NApDMGYAAnKorg/glEpC4EkJI0g2EcEkLwFgEgNCXy4TwvhHBeAKBAJfKR3CWGkDgLAGAiAQAbAIOkRE5BKBoDZHQBIURBycFUCkSyO1LKSDuMAZAfopDbjMLwVKhASCyT0PwQQIgxDsCkDIQQigVDqCcaQXQ19mxoXSJwHgrD2GcOkbwzgSFEQ%2BKlOZO44TInRNifEwBCizB3AgB4QJ9BQxYi4CsXgjitBrAgEgAJ6QglkAoBARZyyQDACkOfGg68Eh2IgLERpsQIhtBRDU3gJzmDjSQrEbQmAHAXNIAEt2SEGC0HOaUrAsQvDADcGIWgdjuC8CwDrIw4gvl4FpA4ScQKeFBgeYiHYEjVoNEaciWIaFxoeCwI0pUeBTHAtIGNWIe8nhguAMiIw0i1hUAMMABQOoPjNiilwiRWThCiHEPkjlRS1CNPKfoEyKBrDWH0HgWIdjIBrFQOkJoQKdrElzqYQRlgzBWLGgmLAUrFK9AeU0FwrkZh%2BGvmECIIxqhjGvvpJoxq9A2tyIsUYiRr52H1f0KYHRPBdD0G6mFAgBjtCdZal1thPV2tdZ64NyxJnrE2NsCQdSOAcNIJY3g1jOkRKiTEuJCSBlDNwGk8Z4ipmSJpWsHSTAsCJF1XIyQgRtyqMCPojQkgzCSGshofwllVH6E4MY0gpjAhcG3JZLglkUiqJ0ZZfwkhNFNssqmxp1jbH2LLU4uZ7j5meNab41Z6yxkhLYJwNoLAIxJB2kwNmmcuCqO3CO%2BF%2BAiBasybIHJ3LpC8qUPy0puhz6VKYNU4FSaU1pqaRwFp3jEQzUzd0mJUITKALvQ%2BoZIylljNhOCMwpaZnOO3QehIfi1moFGWMBDRhb1cEvrsuqByjmlKuWcp5jGbl3P1U8l5fM3kfMad835/zBpAokaCkyEKeH4GhY4dscKUmqERSyJ5qLDE8IxVilEOKdg8PxYSiRJKyWslEyLGlfB6WMuZayp5HL315M/bIPlJSeF/qFdSlVVhLDislfAGVcrcgKqVfKVz1h1Xps1bJT4Xm9X%2Br8BAVwEaQiuWjVajIWQDJ5G9YUa1KWmiJdDX6pogavUFBNZF/LUbzVLCS/MaY6XitVaGOV51ia42iKa4Y0Dy7OCwezde0Wt772KILU%2BkgmHh04fLaQSt1bKBJoHUOu9rakj%2BFUXowIbaO1zqXaUldtg124c3fAbdXi2lEYI8QI9OxT09JYAoCMfoIx9aApMFJQ2X3Xys1ymzBT5DfoczoEAwQANAdqX25NDStvNN3e0iyqgrs3buw9nskxUMkfQwkEbgQxsbpcQslHyyTu47GSAW7i8Nz3dURuR7BANww8/XQWjlB6M8JY58iRzPbn3MeUSzjghuOfPE5gH5fyAVCZBQZ8FmmQVQvddJxpCLkBIsU4INFpTVNnI03ihMOneB6aUOSwz1Ksd0opmZzALLeSWbfR9iQtnCk/YFf95zxhRXuYxTq7z8rOC7AvIFtVGqEhavC9KkruRDXuBq3oM1lRGuZdKLkOLDrygNZDb6ho7qA3hvD661PUWCs5d9Rnor%2BeFhJ5jWsBQIiE2xra2DqxnWad3Gu7dyMCOWRI4gIW59I3JnTPG5NsYurDGzZAGo7cgRAj%2BC0XO8xY%2BkgTs27XmxO2HHjbrf4RtuikjmJSJIDRXBlFmEXYYwINf02cB7xupNyT5%2Bn8X3ttYY1sjOEkEAA)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/rotate.test.hpp)
