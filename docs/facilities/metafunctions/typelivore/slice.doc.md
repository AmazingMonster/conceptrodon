<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Slice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-slice">To Index</a></p>

## Description

`Typelivore::Slice` accepts a list of elements.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked by an operation, the function collects all elements with indices greater than the given index from the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>I</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the elements of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>J-1</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>I</sub>, ..., E<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Slice
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Slice
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all elements from `int, int*, int**, int**` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = Slice<int, int*, int**, int**>
::Page<2>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = Slice<int, int*, int**, int**>
::Page<1, 3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Slice` using concept expansion.

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the elements of the given amount from the front of the list.

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
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl() -> Operation<Targets...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Slice` accepts two indices, we want to collect the elements between them.

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
    static consteval auto idyl() -> Operation<Targets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {   
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZgAzBFkN4sHcTOC3F5HLRCABPeHYUHmSEMaFeWHwtzISboLBUDFYv6A6lA0H/fZ3ACSLDS9DYgiYTW%2BR2B9JpgOBoIImBZBmFhIIqJezDYpDuTCRqAp1zQuOeBDuymImBoqjh4IedwIxC8mHhVmudOOdyECEwbW5h2BwtFnLNCMl0tY7sx10mJocNrtDpMgSsgQe5spVxdrLdhKyAC9MAB9AgAOkzjOVV39XkDtvtxATBHQIBAESwqhTSgAjqa1YTGZn0xTwb6QWHQXce0aRXHxdde/q3N3h73Y2L3W5PYxvS2MXdoUwFF8APIvYicnKkMfju67XZ3ADqmDuXiUcIAbBotTq8KomxiFzejag7owfAk3Ua7Xvx4e54MAA7oYwroPKxDAF%2BggKK2Q77pq2q6k%2B7YtnIIFgZg6C7gh%2B6zjKmAtgAKm0wCYAQCj/jmw7zI4yBLgIkyYAAbmI8qKnceDoKitAQCsdwALSLhu35NISpFQRRcGZm2FqdpG4LyVa9yMrieCXj8Qr9lOEpSnOspGvphE5nmgZqe8l6huGinKdck7xgiSaphmWZys5aYtgAUqZxr5hqFkadOJLlpWmDVnWDbbE2C7tu5pahQwVY1pg9ZvNOXmxZi7ZYl2eF9q6g5XMOhL/sODnih6xnzrJ7ZLgYq53KJW5NLhxWIYBp7nlZN53ihCLZmhsmvkQdzakwyAIL%2BZ7zO0dyoFQ14aJJ5GUSYN7we1%2B59Q%2BqHYC2bWIQeR5dReZ7rbeyG7QiPlDa2I3vp%2BbAtWeBB2h%2BbKMGt%2BXDoBwFnqBghvoxtCNJtR07Y%2BN3PpmK3SYdiEETV4O9jRvZ0XgDGqsxbG0Bxo3cbx/FCSJm7bgIElkdJWVRpaEa0yCVL3EIKLbI65zaYV05I2wLbYJ9sG%2BQGGos5jZp0/J5U6Y5bgKkQNP5WZGpaqgRDKEw5Fwl29NKdGUtcwmeDJmmdxXCwGyCGjPZK0hquoOr5GEmbFsEFbWuS4j0uVTOXvc9VvO1dg9UrjJ6ZXMA2oil9VE5T9vYXhEwB3AASqgTAQfChpYNCs5lb2EB5/uhZtCWZYgCwTAANapmFEWpVF07O14ls5bHW1HXc5YVWehO0E7EeYFHsEHXc/ND5RWX8YXdwrAzJU63Z7fd4bxsi1MBDuUbLmj0lbvavWeDal8EADHNpUGjv6Cz4rfmBirasa9Op8b5fbvWajcc9svHq%2B3pXoB62Oqy5VwtnDpHdka025HQTkYFOacM4X2zrQXOn87gF1QcOQKShS7lgrtXFMtcUppUbAiZ%2BGJ4plzwTXJK4UiEN0JNgJKgkyGtw7B3XsXdfZcR4n3BEYDB4QNDnKMegjJ7X3bsOWeut8qhlsnrCcv8ERy1QKAge48Y5sPjlkWBDtzoX3vvbR%2B/dwHRxptIhSDMVL8gFFYhkAAxQ%2BkxR6qFYKyM8WkmbWIBIKTxDJmrkwYOzZ0iiZz%2ByIoHUENt/HiXMbYm0Xg0jFGwsnT4XhkFBNBDApOQgElJPQCkhQaSNSZyamTGJbgIgEEOHKSphw5LRnpCnVJ6SPFXCyU0wp6SSmi2igiSpNTBD7AGVUoZXFBn7BzOWXRhIzCTJAKndOhJok5HqZaXxdxiKfA1K0jGyAUwhwSAQCAIUQAKG9PsmObgcmJMyMk5pL8ClFIxFIxefIvG0nWUITAqoILYBcaKdxPJbHvI%2BYzG41prl5MeS0oF1x2mQtufk%2B5KYuD6kNMsimfTBnDLqa3V51poXbNhW07RSdCUorRTaVm05%2BljKqTi0ZtSJltymUYhEXA5TgjmQs9ASyykrLxQ060mynE7NaPRC5Sh2jHISqc85K5CQIqUEizpBAUVynJVwZ55oOBrFoJwfwvA/AcC0KQVAnBRyWGsHcBQGwtjnQhDwUgBBNC6rWJXAIkh0waAABxmDMMkZIXB/C%2Bp9VwQIgRpD6o4JIXgLAJAaA0KQY1przUcF4AoEASaXUmt1aQOAsAYCIBABsAgaQkTkEoGgFkdAEhRG9JwVQPqryCSvJIO4wBkAMSkOmMwvBsKEBINxPQ/BBAiDEOwKQMhBCKBUOoXNpBdAcuAluNInAeB6oNUa11ZrOBriROWjUC07hNpbW2jtXa7g9rMGgjwNb6DEDhI6lYvAc1aDWBAJA1a0i1rIBQCA37f0gGAFIMwfA6DCmIJmiAsQd2xAiG0VE67eDweYMQVEa5YjaG%2BTmp11aIFrgYLQJDC6sCxC8MAWWoNM3cF4FgCuRhxCkcPjhvALFPg7vCt8pEOwnWVIaDulEsQtzoY8FgHdxo8Dxto6QdjxBYi3KeAx4AKIjCurWFQAwwAFAADUPjAVEsap1o7hCiHEFOkzs61A7qXfoQwxhrDWH0HgWImbIBrFQGkJoNHBIkkzqYK1lgzCprk8QbiHH3O9FY84CArgZh%2BA5WECIIwqhjA5cUbIAh4t6Ay00RYowahRYcP0de2WOV2Gi80de%2BXUuFdmh0TwXQ9D1Zq8sLgaxbWbG2BITdHBDXJp3Wmk9zbW3ts7d2r1N6IC4EHY%2B7E7XX3qbWMGLAiR%2BKkA9ZIcE6ZkjgkjRoSQZhJA3g0P4K8qRo2xtIPG8EXB0xXi4FeH1yQw1Xn8JIYNu2rwDYXWmjNWbnXqfzUWz9JaD0Vv/YBh99a2CcDaCwFigRBJMGDrAlI6Y7umoHUQMLZYOUmfHeZ6QlmlDWYXboMDK6mBrto71/rKbeBpv3WWpE81FqntG6jpO6PMe3tQPehIT7wRmBfYD3NH6v385/Q%2BytAGpdAeXEYFIXAk00GQQkaDsGF2ocQ8h0gOv0OYeww4PX%2BGvqEeIzusjFGqO0Bo06%2Bj9mmOmvwNqYr7GaNY9UNx4Uev%2BPRtNUJkTqIxM7FNZJ6TTq5MKaUEpp3icgeaY1rp/Thm9cE7M5O4nsgrPztNRTuzamAtWEsM51z8APNeZyD5vzBpi/WGC4z0L4W3PrYq8VmLcXGsFES0lVraX0iZEy7kbvCXB8lByP3urDRKvPzK0Vpoz8p/NdK6PlfCxktLDSx1u13X2v6C3T91NnBhtnvbYr7nyQMferQTNnHQuFti/fct%2B0q3KC9auzdq/B3Aj%2BGSBG8EQ7Y7D7I/RnTgf7bNIHAtYtUtQ9WXKHOtBtDgeHc9FgBQFiBiFidHKcSYftfAHHYdfHWQQnLPadeQUnPPHQEAcEUgKnGnDdA/PrbdX7PdcHI9dnVA9AzA7At0JxCAO9aXQXbEcEUXN9PNUHBAv9KteXB9EADAxJFMLA5IFMHAtVVQNtcDdXKDSgLXU1A3EjJ1fQo3HDU3fnAjIjEjF3TAcjSjMQO3PXR3RjMPOjFjd3DjBdLjZAHjP3QQATBdIPRDUPCTMLSPXgaPRTEUePNTcXPgLTFPTAAzaUdPYgzPCQbPGdCgmzagwvBzQLGwITVvSvbzTgXYEKevILELBIXHCLNvGfDvPwWLJKefJLCoArHLIfJoefXLSfTfNo8rOoxfVffIMfdvQYjfVo2rdfaYNfcrarXoyY/fTre1HrRg%2BnQbE/dQ9tNAjAu4JQ9MVQ2/fAkgB/UQpbUgFbMYdbS7ONEAANdMcEcEfwEND7RNB4wIJ7UA3ddNWwAHMQlYd1EASQfwHbcNQIRNH1SQINLgP1Mwb7aNcEZg4/b4v43rPtT4v7J/N1WTDXHIQEoAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/slice.test.hpp)
