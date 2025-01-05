<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Slice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-slice">To Index</a></p>

## Description

`Varybivore::Slice` accepts a list of variables.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked by an operation, the function collects all variables with indices greater or equal to the given index from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the variables of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>J-1</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Slice
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
alias Slice
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

- In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2>;

/**** Result ****/
using Result = Slice<0, 1, 2, 2>
::Page<2>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2>;

/**** Result ****/
using Result_1 = Slice<0, 1, 2, 2>
::Page<1, 3>
::Rail<Operation>;

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

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Collect the rest.
        Targets...
    )
    -> Operation<Targets::value...>;
};
```

- In the case where the second layer of `Slice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Expand `Prefix<J>` to collect the proper number of arguments.
        Prefix<J> auto...targets,
        // Remove the rest.
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Shear<std::make_index_sequence<Amount>>
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
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZgAzBFkN4sHcTOC3F5HLRCABPeHYUHmSEMaFeWHwtzISboLBUDFYv7HO7KYiYGiqb5HYEETAsNIGVmEgiol7MNikO5MJGoCnXNC454EGl0hlw8EPO4EYheTDwqzXUH/fZ3ABqTFRTMOLLZHKYXIRwqIeraeCYsXoYqukxVDht6M1gQsd3mjmQdwlk0wqjSxCFIruADcxKq4V79cQ7Q61YEHuq42nwRqQVTAXmflrqQBJdn0NiCc05I3nQv5uvA2uHO5CBCYNrVk2l81qhE8vmsHuY64urxulttsMmL1TzPZ0GsrsWtxZABemAA%2BgQAHQ7otOkdj1ttQkkkAgCJYVTrpQAR1VksJRZ3W4p4KHIOn1zu36Vps5aq/H9CVBH9QN/RcezcK1UGfDEAwMBQvgAeReYhKwEUgQLA78%2B0YAdnwAFTaYBMAIBQsO/J1QN9PB/UDVlo1ocNrTwdBUVoCi7ggTjQN2XY7mwENDHQOEADYNFpek8FUR8KXEpVUADDZBCVVs7i8AB3QxWRE4ifEYMiX0A7DJIZWS32YmCd0w4ywL4u48kaVTMDuOlJiMq5sO/IjiBIwyd04lZOIAWjglCEnQhhCR8vyFDPRjVVgt91SxVMUs1XMmyLXE8CUDt5z/btuV5PCBSVEr%2BUHUED2lbL3jyqcrDSrNKSuBczSXVcN23XdBS6zdnwAKX3ZVR1qnKlBPAh0DPC9g2vTA7zeSCnwCt8%2Bum2aGEvBalofBFBqSzFks9bNQPa/9uUKpdoKO%2BCmEQu5wrQpoqJ/Gi6IEINGMsu5WPYzjuNs3j%2BMEtJhLEiTZWk8zMXk600C8FSCDUzTtMwXTfP0wQFA8ryZSkmSET3Czbusnif3ssGIZMcTTJhg65I0BSlNoJyUZc0NUFQu4GFGMNUCoIUsfLQyKe/emibcYbSZFZ8plimzPK8%2ByACU2VQSMXI51zPm3cW7lg2ygts0KLOeyLCSwaFcIgBXSIUFZ4pjTAjvSj9Z1a7VmxRbZ8uuC6istOWdwTJN6HIk7nVGsdfYAj8zp/QObpDl8o%2BomPpVpVAiGUJgSLjJrPYy5WcOuyD%2BulK4WGUgg3u/GqZRz1A85Iwlq9r%2BvC4N5PIN7wkybT7B7sQ58rmAOk2QMyP33xrwsiMO5VaYOh5UVa3aFwg2gdL/HmyPYgppmkAWCYABrDc5qvW9722dua6RuvkvTvfvzPXu/rYjiEXHyfRdxta2AID6nRAiMO9oI4UmnKmZ8Jtd6gSCi1WyM53acX7giSuzYpgED6ngNcm4BLbS7nSO8eA3JcQGO0eUbh4SKmwNtOBGdXRZ2IM3VukFKE4MIegLujUgLAyTuXK6EEB6pzgtCB6ACty/0wFPHGXdQLzwiMAJeK8mK0LuBvLeAjvw71ft%2BOquUK6bRPufS%2B215o32WoSThGINrH1PhfdcV9dq30gvQ9AwVbHP1nvo9%2B5dP4Ax/hPWR/8jrAINIScByYZ6NRnLAg2iDE6UWanOWy6CoKpxkXIsiXclGL3YWvJuud86QWyWEwBqDUlezrPmYE3sABiZDJgCVUKwDkLkCyZVqWcBs3SnqoUiv7NqQjg5EDdsOTOAyIqvSQTmG41IhBeDSMUDG6sFBeE3sM/JKilkrMyGsz4mzpQaItrMtwZhBRmFfGkhZ9x1nHO2QvFRDytkaKEHHQkGhBRcCuVcp0Z52GEmuVHM8y86CEjOTkG5NT7gET1sMj665JEJAIBAU8IAFADmRZHNwezVnoFeVwolGIkmwp6QCepizMAShEoJdp9BhnagpUCclOp8UHMJUcrZXSrg7ObMsglRL1xcCKVCgQhJfl3BBcdW53siVPOUUvblBARVFI%2BbRSC3y7hSsudKgFIAgUIileCA14Lv5uHFVFZ%2BcrqTwpabypFKL2jopMVitgOKbGCs5cKqVvrSXqg4GsWgnB/C8D8BwLQpBUCcBoZYawPoNhbBctiHgpACCaCDWsM%2BARJBbg0AADjMCkZIXB/CFoLVwQIgRpAho4JIXgLAJAaG%2BRGqNMaOC8Dit8jNkag2kDgLAGAiAQAbAIGkJE5BKBoHZHQBIUQBycFUAW0SwVRKSDuMAZA/opBbjMLwDGhASCsT0PwQQIgxDsCkDIQQigVDqD7aQXQvyNJoTSJwHgwbQ3hszdGzgSEkQTulILO4y7V3rs3dunVeazBcQ8LO%2Bgk4IRcBWLwXtWg1gQCQDOtIc6yAUAgDhvDIBgBSEuTQTeCQ4oQFiL%2B2IEQ2iog/bwejzBiCoiQrEbQNLe1ppnaLJCDBaBMcfVgWIXhgBQTZnFbgvAsCnyMOIUTZCeN4C1jJqNwYaVIh2GmiIrI61RpRLENC7GPBYF/cqPATbZOkC1sQWIByngKeACiIwma1hUAMMABQuoPgaXChGtNZ7hCiHENekLd61C/uffoQwxhrDWH0HgWIcVIBrG5k0GTwUSS0NMPGywZh232cTFgNLEA1h2FU84CArgZh%2BF%2BWECIIwqhjF%2BcUbIAh6t6A600RY/M9BVYcP0bB3XflDaaJw/rrWai2FG54Log3sHTeWCh9YmxtgSC/RwMNpA228A7aBlda6N1bp3TBriuAj1IfBChtDHm1hHiwIkCrpAc2SHBFuZI4Ia0aEkGYSQ4kND%2BFEqkOtDbSBNtu1uUSXBRIFuSJW0S/hJBlu%2B6JPbv6O1dpAD2jzA7h1YdHYBydBGiOIYXWwTgbQWCRkCMFJg91F5cGSFuLg%2BaD34CIKV09sgL3hekJFpQ0XH26Eua%2Bpg77ZPbd2/tv9HAAPjqRHcEDYGTtM5USztn%2Ba4OoAQwkOEEIzCofTfjon5OEhTsI3r3DiGUAGCMCzrg3yKOsmINR2jj7WOMeY6Qb37HOPcYcL7/jBlBPCd/WJiTUnaAybTfJ%2BLSmo34DpMN9Tv6tPIB077/TDRf3GdM6iczOwo1WZs2m%2BzjmlDOcT8o/HXn86%2Bf84F33IX%2BdXsF7IKLD6o1i7i%2B5/LVhLDJdS/ADLaQsucBy9NPLiXCvFYSKVz4Y/ejVb8LV7aY2QjbRW219ImROu5AWwUdrB%2B%2BvNaWHvibI3Bhb%2BvwIKbF%2BBvjfm/kBrc2FhP5m1t9byaf91tlyx04CO3Aw3QkWZ1Z3Z2ZggCu250N1uxN3QyzVICezGFe3B0bRAHBFZz%2B0CH8GSGrXBH%2B0B1R0x0fWx1sFx1Nz7Uw0JyQDHSAytwt2IEpx2BpwgxYAUEjH9EjC13/EmE52uxPV%2BTbzCw7xvXkGFx7x0CwNIAlyl0/X0G/TIPbX/RJ2AyFlUA4K4J4L4O7BaQgHg1twN2xHBEQLN2wxtzwyYKsLt24JWXXF4OSHXH4NVS0MFzoDdw9zowY3Y1939w4y4x4xDz1wEyExE2T0wHE0kzEFj19wT0UxLzkxUzT2X0fUz2z1s1z0M14AL0Y2L0s0THL14EryczZFr3cxoL4G8yb0wACz5Fbz5zEIkE71vSkJi1kIdwSwKxsGM3K3H0nz2FPEH2sCKwOxK1YmX3S1X2Gxqzq2P3fyawqGf33xKByC316xyF31m3v2aFf0W3GwaDX0f2WO/xf1vwWKW0/1ONW0qyTU2zWwAJ/XIOAPcLuE4O4KjD0NZAMNgJIHgLu2oIw0ezbGe0oG2whybRSC3HBHBH8HLVRxbVhMCHhxUIO04BxzxxoOzRAEkH8C%2ByrUCBbQLUkFLS4CLTMAxzrXBGeNUM7SBOQLrX3TRPl3u2xLsyoxyFxKAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/slice/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/slice.test.hpp)
