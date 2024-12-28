<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Upend`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-upend">To Index</a></p>

## Description

`Varybivore::Upend` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided variables but in reversed order.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Upend
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

We will flip `0, 1, 2, 2` and invoke `Operation` with the result.

```C++
/**** Shuttle ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Result ****/
using Result = Upend<0, 1, 2, 2>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amid`.
We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

Note that `Label::idyl` maps its parameter type `Key` to its return type `Treasure`. We will pack each variable into a `Vay` so that we can use it as a return type:

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Vay&lt;V<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variables out in reversed order. Here's the entire implementation:

```C++
template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
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
            // We pull the value result out of `Vay`.
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7qEmPFaN8jsCCJgWOkDMyCQQUS9mGw7gAVYiYJgKTaYUh3Lk81iYO4AaUwaMCGOuk2IXgc1NpDUxSQssOudyNd3mjmQdzQDEmmFU6WIdyYiNQdzw6BRtAgCpRKzuAFp0QKhSKxXCrNcTEkHqGKTcqQA1JgohmHJkstlMDnwx1EO4J4h4Wn0cmqgjqzUJtHhvWg40m1pmi0Ca22%2B3Z50ANzEXllEYseYLsSLkejVajgTDIMpgOnP1B/32dwAkqz6GxBBncsnznOZ7vt%2BHrsyVxnMAS2wA6S/9wufYtXNUagh3OQ89C6ie1o/pzNuL/s09Zk6l7ngGUIigoEpSowMp3rWD6ak8rR0LC1bDuOMafmm/6clhJ5nkBl6gQYChfAA8i8xAbgIErZAAXpgAD6BDAYusHGvBT6IUwdAEuRCRUQwNEEOgIAgBEWCqAxSgAI7djiAFuIuwHksqNbGrsux3AA6rKyBBsyDoMHcqDtgktCoEw6AmpgT6oFQsIpBorruiYjmSggxAbMACAugwCAJIQhjbCBhrGiAdzpF4g54OaNJ0gSFYJW0A70Ao6JCSJYmCJgwCUbQDGWvMggEnRjEEBKrGqcqymhUavZqbWRpeNkRhavF8KJR1yU3mlyoZaJETMrlYgFU2rTFfCpVMRVKnYANbq0Mp6G1Y1zURMAkrcj2gQPHcfGUU0BINY1tYaXcUSoAZBAIBmDkaKVdnARAi4rK5Ggul812ykQrT0gwoz2nZS7AaQx0nUaZ0AO4IDFPl4F8TCNla43MWD4NnTpDpCnc6CoOtEVMMgADWdw2ukhjZAIxmmfaX3WZaVlKWjJ1nfy/l3EKoq0E%2B8MOncyKTMZ9n8MQLAgMzjVnQ9VBPS9fp3FwNF4PRj2Xs9Pq%2BncZgSiDdwaOeBpXODjVYFCUEQBLxvOR6lvG%2BxwkDdlw35YVKO23bsKTcrZVKyrMtq3LmuLvLXDkqhUYrR7RqvZH6OaZjkW0PSdOdt4sqc143PGYiQt3YljkhUbUcrKJqfdjVRcnSpH7GhGY4Tsdf54fCTc/hehHKhaxEKMBVy5ZgLKMAQvUqpXdxra1ABK3H0nCu1cTx8J90Kg%2BCD3l79SALBMETjHiTaUmYLJbwKdLT3XoOnyvVVc0gFBI4gmhDdTnuKY7vc2CqKwbKyrOL%2Bv8CTE4JITQm2oSAQ2x0jDzvO/Q4dwhAIERAQegW5UzHjbgRECqkSxlifPtASD9YELiEF4dIJRMDoEnp8TOT4/5XAnhtEhZCsgUKoVzJ8c89oUQIfCbWWsJSKz1tXGM847hsJoag0EDCxHUKzpwl8rgCQaAERKPhZg7yiWnovNw%2BDDpVWfrGe4/JPi0MZKCU0MUGLgQSAQCAxJRIKBlFY3qbgmHkMobI8qMj2HomvhYDgaxaCcH8LwPwHAtCkFQJwNw1hrAmg2FsHs4IeCkAIJoAJawiYBEkOeDQAAOMwZgACcRSuD%2BHyXkrgSQkjSCCRwSQvAxZcA0MosJESokcF4AoEAyi0nhICaQOAsAYCIBABsAgkVyoUAgGgVkdAEhRBlJwVQeSUi%2BhSJIO4wBkDmikOeMwvAKGEBIK6PQ/BBAiDEOwKQMhBCKBUOofppBdCK0hpRdInAeCBOCaE9JkTOCkURJM3OKy1kbK2TshWOSzB3AgB4OZ9B7RYi4CsXgfStBrAgEgWZ6R5lkGmTivFIBgBSG1jQbmCRukQFiH82IEQ2gok%2BbwOlzBiAolIrEbQmAHBMtILMtcBBSIMFoIyp5WBYheGAG4MQtBuncF4FgbeRhxBirwEKBweBTJyoiTabliIdgpMGg0P5yJYiUTZR4LAfzSx4DFvK0gNNYgsKeEq4AyIjDpLWFQAwwAFBxg%2BJDPiYSUnnOEKIcQNzQ33LUH8l5%2BhDDGFiZYfQeBYjdMgGsVAUDchyt9MSOephLDWDMO0mm%2BYsDpogGsOw3KmguAYO4TwXQ9BhAiCMaoYxFYlByAIGYfgu1ZB7QwRYAM9A1o1QIAY0wm2FEVuOpoU6hhtqWJ22wUwOgzv7WuhYy7R0ovWJsbYEhvkcBCaQNpvAOl3FBeszZ2zdnQthbgY5SLkmotSZ6tY/lLJjCraQLJkhAjniKYEGpGhJBmEkI5DQ/gUhFP0JwBppAxaBC4OeFIXAUh5KKZUlI/hJBlJA2kC9/zOm2B6R%2B/pmKRlYrGUCxE5BKCEsRYstgnA2gsHbEkX0iMwKtS4EU88aGdX4CIOWs5shLkRukFGpQManm6G1m8pgHz5UnrPSRjpgKJk5yBje8FfGNoCaE7k2F8LcWIthOCMw770UDNo8xhIjGZmoARWMQzAnml8DoMyYgVKaVPJZQy3lQW2Ucq5Ty%2B1/Kh5CpFX88VkrpVJzlSkxVCaVURPwOqxwWq/m6uQPq3lRq6kRNNealElqdgRJtXalJjrnUsnS%2BtT1fAfV%2BoDUG3loapPXJk7IaNjyImKfjR6wtVhk2msrZm7NTZOB5uEgWpNFgS2XrLa6T48Bq0NFrbketjaChbtbZUPdGRB1ND7XobtTQR0dsSHO7bE7mjrou/dvok7103eWHO57m6x0fd3bd49B7ElA7qRpv5V79ObMMwrQTwmn2iZIFZ1DtnP2kG/VgRIf66lIZQ4J8DSR/BFOqYECDUGCPnoh5wLpFG7PUfgLR8ZkznOOeIKxnYHHwUsAUO2c07ZjP/kmIcxH4nFbdfDb1258g5ODZ0CAYIynVNfIQ6e35TytP0dsvZVQXOed84FyeQWcLXMWYSMjwIqOqODOxSbvFLPbeIpALzshDF%2BdFIYoLggDEdcyZ85SygAWImhdFSk4P4Xa28ui4IWLorMuYAlVKmVKWFWNeVVVhVaqdu5aeflwr9rismtTeVyr1r8y1d4PVpQLqmseqt96pgvr/WYEDTyLrkmJcSD63cmXsb5cjcTUWibqapuRJm1aTgux7FjeLaWhI5aNsZt6Dt5wEBXAvZCA2z7q6ru5HXzv8oAOvtL8e4u9f87%2Bj/eO4D77gwz%2BX/bV96tCSj37rB2r9pnBr26953cN355PcI4vrI4opopo4Y6/onq44gDFLniBCBD%2BDlIEYtJwGpB5KU7q7U7ka9Jo4Ab%2BDAZVJJAtJ5KSClJcAFJmBpB1KBDv6XqYF04noHLoEf5kb0EOqUq7aSBAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/upend/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/upend.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/upend.test.hpp)
