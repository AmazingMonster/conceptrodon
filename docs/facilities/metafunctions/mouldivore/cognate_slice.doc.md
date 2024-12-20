<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-slice">To Index</a></p>

## Description

`Mouldivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> Operation&lt;E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I, J
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>J-1</sub>, ..., E<sub>n</sub>
-> Operation&lt;E<sub>I</sub>, ..., E<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice ::   template<typename...> class...
               -> auto...
               -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};


template<template<typename...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all elements from `int, int*, int**, int**` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int**>;

using Result = CognateSlice<Operation>
::Page<2>
::Mold<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect elements between indices one and three from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<int*, int**>;

using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Mold<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

- In the case where the second layer of `CognateSlice` only accepts an amount, we want to remove the elements of the given amount from the front of the list.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateSlice` accepts two indices, we want to collect the elements between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the elements
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5gDMEcjeWADUJrtuXo60hACeZ9gmGgCCewdHmKfnyBPoWFT3jxeZn2DEOXhOZzcBBuqUwAH0CMQmIQFADnoCAPQAKhxWOOymImBoqmOuKxGMBBEwLFSBipkOhsOYbFIx0yAC94QQ0U80KDMKkCPjCcTPgARY6IryYM5WdHPbG445CBCYVqk3EU55Uml0mXnRmMVj6h7PCbELwOZWq9UmQJWQJi2WAynU2lMennDlcgB0foAkjzzZahSq1cRIT8QCAIlhVHClABHaX8yH%2Bv0%2BgG7U0ve2A44FyVuvX5wuQ0uFws692eqEwo1sDP3Y6HJgKBTHADysKRjVIFcrxwxGOOAHUPl4lKcAGwaAlEvCqNP3JuzyWoY6MHwJD0fAiqgeV4fHLwMADuhip6GOrWA28ECkzz0HhfnxOX2YzcnPl8w6H7z4vpK9bMpgGYACq3pgBCooBBY8pWcyOMgLYCBMmAAG5iDelwbng6A3LQEDLAOAC0zbdjujSQpBxDANBj5%2Blmcq5k6uwsZiZLHP6oJ4FOZJak81YlgaIHGqyhqgUGUpWjxyB8R8doOmxHHasWu6RngnIIhm/qst6Ol%2BgAUtJFqybxSiRgQ6DRrGmDxkmKZbGmTbZvp1m2QwcYJpgyaMM55xGa5DzZi6eZwUWuoaRF5YRZWwkaaJTLGsFLYGO2XY9h62QAU8QFDiO44nlOJizm%2Bi4ftgq4aOuxyEkwyAIJKqpspMQqoFQM4aLR9EwaVGhPnlQHlUu5yBp%2Bfq5flx5FZOillSKFWBSuTFrkQm4MNuvZ7i19TUowfVxYWx5nh8F6CLVaC0A0g35SNkImRNPo9QxU1AZJKVMTFoURUheAoXy6FYbQOHrfhhHEWRFFZdR5wvTBwXOuijpIy8CpcR4wDMFSQjXFsGo4oJCW1sT%2Bp1sljZMdmaVth2lG9tkpkhscmPY5guP/TKyMsfF6m1gZBCI79MlCgSqBEMoTD0aceYo%2BxLoRaTmnaUKTwsOsggIYWwZWmLEtS2Tasa9yP1DfB4Vm4OStJQ2YF%2Btg9BsA%2BWsvpOETAMcACynjXmcEpYIchqHoWEDBy%2BYatFZNkgCwTAANbwnZDm%2BU5hvq6eJshTm%2BWVtGpPHODtCQvT2UCKyDv7Q%2BwWQ0dBYkfLMVy6plvW24AvKm1%2BlaVyxzYF5Lt1SneCEh2ED9G0nxuH7vdeSRwtmaLxDi6gkv0ZC48EOX/em5WSlh5FNZkx9lM%2BhXTt9TvQFu0YXs%2B%2BKxwB7QQe18cocv5WckKVH0axwncJJz5PyqZzgb3uO5aOv9E5eXsoA1OkI%2B7oFIqA0Kl8c7HDznzD4hdi4wxyr3R2B1GKZmzDXS2lZ648zLE3BWLdMGQiYLhDMTxgCEkrhfbOhZr4e1XopXYEo9YrwNpCZhrDz5EOYmFFSNDFRklkQJTiSpwKYAmB2eR6M5EaPJDQ14oJ3iTz5FsQUqJTauiiiTMSJ8mZWhLrDZuMi8QADFh4TF7qoVgtIPhqLRk8LhyovCpCKH%2BAASsorwT9742MZucCIBAcSshiTiCR8ofGZBviEhQYShTT1ZruDmAU3CRIEDyaMPDIRmGKSAb2tB0CQhifEwQWJ6mxMaQXBpWIkneL%2BsgOEtMEgEAgFGEAChjQ9OMW4IQ/jAnoHSZk1kMyn73AodIriQhMB8mvNgNxupPGahob4iZASMjBNCU/OEXAIm4KKdEhpTTEkoObr4%2BZBAzn3xyTjPGZNCkMAqaU84XBWS7AqVUmp1zN6tNibclpCT2n3JoV00ZSg2gDI8kMkZbZ16TKOdMk5zz/nHCeWcxZsoOCrFoJwfwvA/AcC0KQVAnAp6WGsGydYmxFLAh4KQAgmgSWrDjgEAAHD6acuxJBmECJISQ/h%2BW7A0P4AAnPy/QnBJC8BYBIDQKQqU0rpRwXgCgQApC5dSklpA4CwBgIgEA6wCCpEuOQSgaAaR0ASFEY0nBVD8unKRackhjjAGQChKQPozC8D/IQEg%2BE9D8EECIMQ7ApAyEEIoFQ6hjWkF0P8s8SJUicB4KS8llLuW0s4J2S4tr2qdQ9V6n1fqA3HCDWYV%2BHgnX0GIKcdlyxeBGq0KsCASBHWpGdWQCgEAB1DpAMAKQZg%2BB0CpMQfVEBYhFtiBEVoNxc28BXcwYgNxOyxG0Gso1HLHXn07AwWg6601YFiF4YAbgxC0H1dwXgWBY5GHEFe4eh68AYWUUW%2ByazLjbA5TE%2BoRbrixCRDujwWAi2IjwGq59pBf3EFiEcsU1JDDAGuEYblqwqAGGAAoAAangTAZ5KJUo5dG4QohxAJpo8mtQRaM36Cwygaw1h9B4FiPqyAqxUCCmyE%2B0iPw/amEZZYMw2qUPEHwn%2B/jPRv3OAgK4aYfh/lhAiMMSoox/lFCyAIdTegDONAWCMaoSmHB9DasZ/5dhlNNDauZ3Tlm5hTE8J0PQ7nBjacWHp1YCgWVbAkPmjgFLSBat4Dq44VbvW%2Bv9YGyQwbX64HDW2vYXBO2crw6sG0WBEjEVIHyyQuwfRyt2OKjQorJCzlldOOVSqOAqtIGq3YXAhVcGnPyhVXX/CSC4PK3Y05ItFp1Xqg1OXjW9otX2q1Za7UjrHa211bBOCtBYBhQIpEmA0xvlwOVPoOs0rDUQOTNl/k0djfR6QjGlDMbTboadWamA5ufWFiLUXi0cFLTay4xwOo3mIJt7bu3Wz7cO8dptqAW0JHbbsMw2Xu0mrm8thI9rR0w8Ha2kAG2tukXB5OuVtQaBPwSAupdaat1ro3aQanO690HocLTk9B0z0XqLde2997rpPo5a%2BrDH6aX4EJNZ39T6TuqEA1SWnoGyVpog1Bm4MHtg0vg4hjlKG0NKAw2%2B7D7s8N8EIyRsjFGmS06u3R%2BNt3ZBMdTTSp7bHcMSasJYbjvH4ACaE2hTgonrLic41JmTCRzsKaKw56zKm1OefyJpryLmlj6YyIZnIMeNNpGT2ZvzFnvN7Uj05gYdmrONA3gnvTthbNp%2B8857PrnQtrA2CFrLTXPtjc4EDkHO29sewO0dn0NUIBpbO/DrLXbcukHy6MIr8uWttcO9VwI8rAiBBFWYWrA3RtpvG7YSbyOZvwDm9a8tGO0fEFW9sDbNaWAKAwihDCve9QTFDfgM7kbLuyGu9bxN8h7v250CAXYUgF7N7PNFvQtLfEtBbCtDvK/G/O/B/XcFxCAZtbHOHPYXYJHQ3VHLHIdE/HAnHW/AJOEe/OVOER/Z5S/W7WdcnSgSnGlenS9DlBgxnQ9FnGHU9c9S9YXTAG9O9B9PnF9TDd9VXF9L9MXP9NNADZAIDWXQQMDBXHjJXFXODOTDXXgLXdDIQ/XXDabI3KWE3cjSjC3D/K3CQG3JNX/FjAAp3YwQPGwCDPjIrQTRoJ9DEKMF3awaTaLWTeTRwwLPPRoFwLyIvLTcoHPJPYobIIvUzbIMvNzAImzQvKvezBIgQUvWvRPCvJIvIdPHzOI%2BvILRveND7cA7VdvSg44a/W/Y4Egn0cg1LF/EgEfTA6bPLNUArSgMLWfEAMwQ7XYXYfwfwarZIDQfowIbrTfMo3VHfQ1cfErDrYbIIMwQYgbBrSQDQadeXXYUo6LTgMfVoprENSY3Y6YvfVYFDTIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_slice.test.hpp)
