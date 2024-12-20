<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-slice">To Index</a></p>

## Description

`Pagelivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> Operation&lt;V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I, J
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>J-1</sub>, ..., V<sub>n</sub>
-> Operation&lt;V<sub>I</sub>, ..., V<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice ::   template<auto...> class...
               -> auto...
               -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};


template<template<auto...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2>;

using Result = CognateSlice<Operation>
::Page<2>
::Page<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<1, 2>;

using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Page<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `CognateSlice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateSlice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the variables
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxBIaAMykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BZho1dVmNzQQlkTFxCV0KTS1teZ22EwNhQ%2BUjVRoAlLaoXsTI7BzmiWHI3lgA1CaJbl6OtIQAnufYJhoAgvuHx5hnF8jj6FhUDyerzMBwYRy8p3ObgItxSmAA%2BgRiExCApAS8gQB6ABUuOxJ2UxEwNFUJzx2MxQIImBYKQM1KhMLhzDYpBOTCuqHRzzQYMwKQIBKJJK%2BABETkivJhzlYMS8cXiTgBZASoIgMW5kvGUl7U2n06UXDlEE4ANWaeCY0Xo3PGxC8DmVqvV9wxAHYLCdxkxHMgTrzxphVCliOzOScAG5iKVnD3m4iW63St2imWx1OJWWveXkk5CBCYZpa3E6556uk%2Bw3Q2GMViGx4vO0OwX5wuhkwejsZrNUmkVhkXDIALwRBAAdBOAJK2yWO1vNKG/EAgMJYVTwpQARylfKhk4nY8BiQbr07LxOF4lfYNQMvXzct7vl/LN6NnIPD39BgUChOAHk4WReoGFIR8nxOTFMROAB1T4vCUM4ADYNEJYk8FUPcHg/ZCJVQE5GB8OJKwlAswKfSCTi8BgAHdDGpdB2WIYBCMEBRD3PcChTQjCLmnY8DzkGi6MwdBQI48CmVrNgDwAFWaYBMAINFxK%2BE8729X1/QEQMo1oMMTTwdBbloCBVjIiiIjVT4CAQH0kI0ACiOAkwcLwX8wgjVAAGsRJOaJNV0qVlOeO8KKDJEmAcXyqGIVAWBI6zr2IlJmjraliDY8yoJkhA3JOPLYlEeDPmokq6D0lLkC8/CIziTVCBpLKTlQKh7PjRN6DYicXI0fLBDwnqVQYNUBHuZD2JCy8AFpP0coCsihOSmMUhRl0CzAP2PGUgS7ba5WeBVcROScwTcz5yVLF9K0ZGsWUwNlJLumd7UdE7kDO2MrBTPbszLJKBzcYdRwPSc2SBxEDwAKWe5tjtOpRFwIdBl1XIMN0wbdGB2PdNuwMGkZRhg13RzHdwuSHce5DsszvK6GRUqEyNp/6q2NVBca/Jgf3/QCfSyMTJvAijYMohCetQklMP47qcJNIlIoQBKvTmZrWp6paFKUnqJs4rjJd4rCJwF3XhbgsXkIl9CoWh6XD1lvCCLYIDrILSMLStTqmcvCjSpOWjBFwrTaDqHXOMtni3Bt7BZPklbjc4x66w/BmtpUjS8D9ANqV0/S8MM4zTKayzqRIuyermvmBB6/L3IYTyfIY/y3e8TBgtCqDwuRKKGJiuKlbpz4UuRNh0sylSKJyvKCswIqEN96jypOSrqswWriHqvUmpatr3aTLq7d6sITUG51Ru1siZuPHmnIWi4NZWtbow27qtszHbvrf/bDvxDxgGYakhA3B2MWCkvZ9TXQuAPKEbMOZHC5r%2BCuzlU7PCbI6X%2B/9MCAIztKd0NNnws0XHgEcEMX5qUvKgwUhIRrKCYApT6u1P6/WZuAgG4NBTPBYJsQQ3J1KzkobFIgNCFJQg4VwggPDLzUy9heKBb4iAHnah7VuEjwLwTCMAAktDPjnHFFgI4klpEnAgIYu885iCI2RiAFgTAfLwlRuuLcO5sYXFEVRcRr8yG6wvMuAe%2BUjK0ChIg/mTphouihIovehtDzHkLipO8ZlGF3gYT2FSsjAZENHHmOYYMMmIhONgImKiThEm3HgIkv4IB9BaPeHR%2BSiZmTTnwoU1CtFQiqQQNkBT0BFKkXE/BLDWbvgnBEz2yDdZqKMJouhtS9G0AMX0i8xiFlPjemdCxy5rG2PsSTJxVZ2kPHxpYzZCJtmOKxlWLpU19keJMZeHxLM/HGUCbzYCbIhojQ1OE3eozo6kNiYLJ8CS8EXmSTtVJBC5HswnM8YARIaSMC1mMy8EyNFCO0YkcUVDBGtJcbCzA8LWKU0YaCr%2B5IyXktLN/E4MlW5KRAZS8ljKSxguBKCcEkJvgCB2AKNEyCwH9kGfI0hQIKHX3mlXYlOZFQADEynjHyaoVgdJzrahZSivMXgUhpCUOgAASq3LwcyxRisrgwKEZg2RmCPCk546r9UKENYKWp6DKxYOcW4IJEqTzLjRea7kPqcVuC6CcLglrLXWpZenZA8J4FxAIBAJcIAFB1hjbytwQhNXapEvax1bIc1zIeECllVKhAzwEAxbAir9QquZftdVGatXpGzQauZ8IuDGs9Wai4oaThWtfjau1LaCBtuNS6gBQCqydv9SAX13a2SJGnbOoNbIe0Wt7RG/aUbU1KBaAmgmSaU1czaZmpteqh1trzeerghaZQcHWLQTgABWXgfgOBaFIKgTgD5LDWC9JsbY2iQQ8FIAQTQd71heRAI%2B/wY5EKJEkGYN0khJDQcSBoR9ABOQID6OCSF4CwUYpBX3vs/RwXgq0uigbfXe0gcBYAwEQCATYBAUhXHIJQNAtI6BxAiHWTgqh/CISmohSQJxgDID9FIMcZheAiUICQQyeh%2BCCBEGIdgUgZCCEUCodQ1HSC6FDdRZEKROA8HvU%2Bl9YGP2cD/FcVjgpt4CaEyJsTEmQ2SGk0YjwXH6DtiA6sXgVGtDrAgEgTjKRuNkAoBAcLkWQDACkBamgcy4irQgNEKz0QwjNFuKZ3gWXmDrz/NEbQM8qPAc42wQQf4GC0Fy3prA0QvDADcGIWgq1uC8CwNYow4gGtlLK3gWqHX31BhnlcXYwGj61CszcaIyJ14eCwFZpEeACOddIGvaITbRQ0kMMAG4RgwPrCoAYYAChTR4EwNRRyr7gPKeEKIcQGmHvabUFZgz%2Bh9soGsNYfQeBoirUgOsVAAosgdamr8HRpgf2WE6LwVAa8ExYCB6Zbog3nAQFcFMPwoaQgLDKBUPQ2qijZE8O0YnhRgKDEJ8sdHDhehzBx3oOwGOGDtJp8MSosx%2BjM9Dd6FonOliVHWAof9OwJDmY4M%2BojVnSMnCc8J0T4nJMebMEY3A8m/OJC4AFkDx31gFiYFgeIaPIOSESGODDiQkMaAQ5IZC6HEIYf0JwPDpACM69g1wRC/gsM%2B8fZILgmHEiIVl3p0j5GQCUeO7RhjoWmN2bY9F2LvneNsE4M0FgEY3RTSYJzSZXAMNji4GOUb%2BAiDI6U7IVTz3pCvaUO9vTugLVGaYCZzrUuZfEYRzZpPDnWpZ5z3ngvGii8l7L15uKEXfNnBBGYPXQWaMJ9T3EdjMXp9xaH7nuBRgi9VD4HQUelAMt6YKzlvLpBz9FZK2Vy/lWEU1bq1ZxrzXWvBw68B7r%2B2%2BvvvwESBnYbKzMbZACbS/abHDd9ObBbW4JbXYd9VbdbYDLbHbPbXrdRWPU7WhC7K7G7ZkS/B7WvdTevWQN7XTd9FvL7I7GHKwSwf7QHeAEHMHbSTgSHJGaHX7OHEjJHQyVuRg%2BnYCFwImPnIIImIXInUNEnYCEQqQrIcQunVnBnBoJncnPIfnWoNnDnAnLnFnFQ3IXHHnQXbQ4XSXDYLYCXXXV3aXSzCPTgRibPXPfPXfMfYvUvXqCATXSvOfHXRfA3UgI3E3SgKXd3T3YvO3N0TDN0N0eDMwB3IPcPEjTgKPGPajELePJAZjezdfVfYgdPXYLPFzFgBQCMP0CMcfA0cYWTCvBTZGUNQgp7YgzTeQRvcgnQEAZINvDvMzKw7vOXPvFjK4VWewwo4o0o8oyseVCAbzGfOIbwxIXw1I2jMLTfXzbIlYkYEorVeEMojDeECo4dAo%2BvI/VLE/TLbLdeS/a/W4YrUrBwe/OKKrAgJ/erP/TAJrFrNrT/LrNAg7eArrAbQAvgvTEAsAjbCA2bAHGAuAlbBMJA3gFApQXbHrA7DAxYrA87S7a7W7AgmvBoiQEgrTFoj7doqg4wTgmwObVHJg4CDrTEJcGg6weHD9HglHfgxQwQrHYQ1Qgw/HUoHQyQqnLIGQwU4oYwiQgQxnXnbklnDQpQ9nOYeQ7nAXVoaU/nBUsU5YUXcXdTLvGwxIjgYY0TIokoyMcY6kSYzwkgbw3XQLPwgIkYNHHDEIkAMwYvRIRIR9R9O3FYd0t0X3BI3vMjWwaPfXVIiDEAIPMcUPR9N0MwT0oPZ3SQDQC1HDRIPUwM20sMqwmTAM6zIMpfVYdYNeDIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_slice.test.hpp)
