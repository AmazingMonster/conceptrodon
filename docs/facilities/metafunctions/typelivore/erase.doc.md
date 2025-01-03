<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-erase">To Index</a></p>

## Description

`Typelivore::Erase` accepts a list of elements.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the element at the index from the list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the elements of indices within the interval from the list and invokes the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>J-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the element of index one from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int**, int**>;

/**** Result ****/
using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Result ****/
using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the second layer of `Erase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

- In the case where the second layer of `Erase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke ordinary functions.

```C++
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEpJcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlSKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQlJtc2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2cHeyYaAIKHxwDUACKYqa6MyHiYCvcnlzd350Bpz%2B1yuoLMAGYIshvFh7iYIW4vI5aIQAJ4I7Bg8xQhgwrxwhFuZBzdBYKiY7H/E73ZTETA0VQ/Y4ggiYFipAxsokENGvZhsUj3JjI1CUm5oPEvAi0%2BmM%2BEQx73AjELyYBFWG5ggFA3VHEE6%2B4ASQ59DYgiYfWZ%2Bu1ertFyptxpj0IyAQ1odNzZpst6sRvP5rD9WJuc1VDiervdJkCVkCjw1ju9nN9RMyAC9MAB9AgAOnzRvF1zDXgjLoIbrTBHQIBAESwqizSgAjmqpUSjfnc5SISHQbGwfch8r2SnuTdhwq3IPJ8Pk1y/W4A4wg13MfcYUwFN8APKvYiW7KkGez5V8ldsLsWJjIADWABUWsBMAQFCeFX3J3ND8gNwI5pgABuYjCqK9x4OgaK0O%2BEDvpOex7Pc2CqKkhjoPCABsGh0gyeCqB2lJYcqqB/l4gjKggmDCsQwA%2BIwr73FQxCoCwFFUUxsjdhOp6yrh%2BGIoWvagUQXYcYIOZPi%2BCjHtxp4IfcABK7KoIBVEEJR9yRKoeZwcOIpEDJ1w8fc8m5L0bH3PScxcUZPHXnej40VJa6yfcqzvgAtOue4JIeAjvkSulDsuApUVgMLLtQzHiZMz6vqstbLl2hnGSFQb3PZD6Sa%2BiXni5tlDj2mr9gmELFbaDzIakZHPh6rKjguPLnqFQppWwRYlhGVU1VRMZxqV5Veg1qaIhm2Z5gWQpjTmXYAFIdSqpYyt1RiLqStb1pgjYtm2OwdmuvZTdWG0MA2TaYK27yLrNB1Yr22IDq586pq5gWuZOz3cv6zWrvm66btu9w%2BQefQpTxbWYFeN5ZU5r4Bfdrnfo4v6SgBwG0MJJEQVBMFBSZiFVWhmHYXKeEEfdRFEKR5HqVRT50YI3wcaxtOMdFOnvcOOGMuT2CY6J7MSbD0l4/JhOncT3Nk4i80UxoxHUzKrNkQA7oYbLofT5qvjZxlS/xbiy3z%2BmoMlouIWZ9RKxpVkcwVs6ZY5cUKPlk7ua5XlCcDfkMPD06c8FP1sPc4W0JFYkEELzsJSASX5mDp4Qxl0NO1JuWvK7w5FQ9A2Ooa2AHkodVgp9i4Q122BmvRb4I8Wi1dYX6pao99ul0SJu3e%2BnUynSqBEMoTC1X1Ma51qT3DV9bjTTKRqnVtRZfvXPfMf3g%2BLrPDYL1nLepRPZd701gaXn9QkAy7%2BbXMA9LstXW%2Bnl4mRGIpqBMOhCJKqHy547BAezuWlajWOiAFgTBbzZk2ttC6u115z34ndT8xlhyJT3uBSC0FESX2vtrc%2B3ZewQHWrHc8WYIL0XRESSuN9GaUgHPGLs7t7Zu0TK9eMTDQTjx9JPae9wBitCmngTMOYkKnTvpZKBeArL3AgDwmUgVFRCPQPQxe4Zl591QAPZ8RJpFCmwMI2uk5h6/zbv6A%2B30j6QxPnzM%2BXZMGYEoXDPRPEH4RGAM/V%2BCoP71DDueb%2BeNJwrQ0b/fRiJfE8QISAsBxDYHnUuu2RE0jMQJ0QfBRCJgsI6PQB5eJRE8DfFZgwUYxB7ioCoPcHodjvgqyoirOgGNfJKF1kk2cYTQHgKiTtK65DTqZPmCI4yvSeLII4VRbG6C3A2PKbdfBQDlzEKwIIMhiIKHYOof1OheN3JlQCiwzZY9W4mLcB3C%2BV9bHLIcUOJxT91G9Tkb3VeGiMHHImRY1hI8XnUntECA0NIABi4i5hIVUKwTkVFfgVQ%2BecEE2JITQlhNc4kAgdipHsX2MFBwgb7h9sXIaQzD4XnMbgvs3d0W%2BT6G8p0DwhBeFSEUTA6AlIKC8GHLF1wLkuMpdSjItL6WMpkXI72pLEQRAIEKIVRwRWCCONnXZhpuVMtBTcVlikvg8vcUhRuRIhXioIAcLVYrwISoOJiWsVyiRcCNSABSL90BEn5dkKVbDyVHHuPeL4Mp5V1x/FmLcShWhTJrCABQQYvU1zcOymldLlVhyFLKggmINmDUdeCs4XyKX1AEOhZCQL6DMp1Em91qLuFUvDTG5liqw2cojQysOWYuCqttf5QVghdWGvujsh1MrI1upZGCRVMaa2qoLluRcmr9Xaubc281JrEQpHuBCc1lrX42oxQKu6CbDQuv%2Be6pGeBkDBp9QQP1tZA1sGDZootFa%2B0zsvXGjUHB1i0E4P4XgfgOBaFIKgTg05LDWHuAoTY2xeqQh4KQAgmg73rFvAESQuYNAAA4zBmAAJyIa4P4ODsGuCBECNIB9HBJC8BYBIDQGhSAvrfR%2BjgvAFAgBI6B19d7SBwFgDARAIBNgEGqsKigEA0AcjoAkKIQZOCqFgxhDyGFJD3GAMgX8UhcxmF4LSwgJAIJ6H4IIEQYh2BSBkIIRQKh1D0dILoFIKsDypE4Dwe9j7n1gffZwHcyJONFJKSJsTEmpMyfuHJswkiPB8foIUnEXBVi8Do1odYEAkC8dSPxsg3GYtxZAMAKQZg%2BB0DZMQajEBYh2diBEFoaJLO8Hy8wYgaIdyxG0FbYrpBePax3AwWgRWjNYFiF4YABzaC0Go9wXgWAQFGHEK18RVs8CqV62%2Bra9RkS7GA0KnodnUSxAPOVjwWA7MqjwIRvrpBVLEFiJy54g3gCoiMGB9YVADDAAUAANU%2BCrHyL7gPqeEKIcQOnXv6bUHZkz%2BhDDGGsNYfQeBYjUcgOsVASLsi9Y8qSd%2Bphv2WDMOR/bxASHg4gOsOoDRnAQFcNMPwKQwiLAqFUPQRQsgCEJxTjIVOGDDDJysbovRGjzBp7UMpuP%2BjzEZwUvQ34pieA6AL3npP%2BchY2FsHYEhrMcCfaRuzFH7hufE5J6TsnoO%2BYgLgZTQWgOhZAxd9YlFX5jCx6QSDkgIS5kQxCbDGhJBmEkFhDQ/gMKIf0JwfDpBCMQi4LmDCXAMKwcQxhjC/hkj%2BDtxhRXRmKNUZo0b%2BjkWWNRbY055E5BKCJcC4JtgnAWgsEAoEDyTANwGCflwRDuYA9TfwEQdHNYUivc0x96QX2lA/aM7oNLZmmAWb63LhXZHeAUccxx5ELmVeibVxXgH3ma9178yxWLgX4SQjMIb8LDH0%2B54SNnnjq%2BkubiMNXrgJGaBhwSNl3LRnSuFdqw/8rlXqsOFq/V%2BijXmt2bax1rrPWtWA2AOw2b6%2BA9IDQE2dm02yAs2tWC2uGb6y2q2aI62uwb6W2O2wG%2B2h2Sgx2IBziF2fA12d2D2T2tWre722mHesg32hmb6ve/252iOVglgIOYO8AkO0O/4nAcO1YCOQOyOqOCQTeXwnBLOY2eOBOwu%2BQxOp0fOyw1QaQdOfQHOyhxQ2QCh5OnOrOAg0iahOOfQ0iWhzOgubQMhROtgYu5QEu2O/6MukuuGI%2BSunAM%2B7mkmp%2BLi1eteMGkiuujeG%2B/u2%2BxupApuWAiQFuuGPufuNejugQ0eWGEITuLuyQce5GnAietGRBTGrG7GnGh%2B%2B%2BxA%2BeuwReHmLACggEv4gE3hC4cwimDeKmzeumb2WmSQzRdBv2IAEIpA/eg%2BVmXu8utm8eDmmeMoxSKuZRFRVRNRvo/yEA/ma%2BCQgREIwRKejG0Wx%2BgWBRmxYwlR1KWY1RiGWYtRkcqgEm6W1%2BWWlAd%2Bb6z%2BLWwGdxr%2BNWu2n%2Bgg3%2BLWYBmA7WnWYggBu2wBQ26B/Wo2kBYhRmMBcBu2CBS2oOKBaBm26OWBvAOBR27IBB52axV2g8pBmAj2/IFBsgbe1B7RXe9BOgXRTBgOSONgy2mOXBfQvWew60LB1gKOY%2BaOGO4hhh2QLgp0ahJONhihtOGh1OFhwp9OJhSh3Jeh7OYpOhkhPOgwkpougwBh1hSw2hdh0u2mw%2BQx6RHAExkm5RlR9whxuYJxfhDR%2BuQRYWIRYR5ucu0RIASGuYEIEI/gaGyQxGbpgQIeaRY%2BGRtgSeO%2BqwEGIAkg/gtumGgQxGsGkgKGXA8GZgseuGEIepAZlGyeEWcuCm/p9mmZIZ6w%2B2mQzgkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/erase.test.hpp)
