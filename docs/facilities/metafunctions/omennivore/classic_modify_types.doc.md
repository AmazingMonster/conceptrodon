<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ClassicModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-classic-modify-types">To Index</a></p>

## Description

`Omennivore::ClassicModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ClassicModifyTypes
 :: typename...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ClassicModifyTypes
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_container&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ClassicModifyTypes`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct UnaryMinus
{
    using type = Vay<-Vay::value>;
};

template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = ClassicModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ClassicModifyTypes` is similar to that of `Omennivore::InsertValues`.
We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct ClassicModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ClassicModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<Target>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ClassicModifyTypes<OtherSequences...>
            ::template Road<Operation>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBL%2BAOykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teZ0TA2FD5SNViQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxeZn2DEOXhOZzcBBuKUwAH0CMQmIQFADnoCAPQAKhxWOO2FUBFcADFiLJjrisRjAUSWCkDETIdDYcw2AA6Dlop7jYheBz4wkksmCU6JKyJAAiZys6OetPpTEZ53lDMwTJhjFYmA5bPux0OTAUCmOHkEyPCZGOzM17I52HobEEqP8D2ePL5BAFRIY6FJskhpqa82IkPtmEdBAUOoBLsBJjFgOOSat4YVSqhGtZ2o5EUwAHcwxHna6nsnjl4MkZjgBZTzoT4Sk2yc1xSG5gsOxiRnWkfGdp3R2P%2BGUvSXSuPPbG447KYiYGiqCm46ly1Oq9UsrW9jIAL3hBC5aFBmBSntn87wi7OjcRXjVw4nTynOJNTBSCi89CXOJXTxVivvDNN1tXVYzdW9%2BTcN8P3ocdZSfSkTQMI08GQWt8CoG4ABUNWNSlf3/dNrSzQcS3dSDkIyNCMDwTCcNhY143FKUH3g588QsQ0PigpRvypGk1wAyEmEuVAdQASS5cjPTcSjUPQ2jsNwyEfhAEAwiwVQ4SUABHO9j0hcTSK5JjE2TQjAIsjcbWzUDsH1SjjgAeVhJF6gYLky2kmcySIAAlVAmHQMyk1M54yzLKzwoi0LzhCmLkwxDFjgAdQ%2BCsPhMAA2DRzwXQz7mjHKrVQY5GB8OIANOHK/UELDmmATBI2yjRdWihLkzyy8CpdHVaoIeriEayNSHijqktSj48zoWgrSRBgFH4YgWCtBAPnCQljgairBDa0sOvMzMtWOQbhtG9qDuIrUdU45AAGtTqa1ELrLTyEvGRVUP1ARxkwAA3MQttE448HQG5aAgFYxuTABaPUoPfT81Re5NIWhmL%2Bse7sOXO/aDqtI62Gc1zPoESEsfuNTrVx/Gk1uh6Gqe6MUdih5WJeFmUzpddlUJ2ynmAOdwy7Yt0fLStgBrOsG2OLBDmtCBQfByEBaFotSMhqH2desd2fiqzlUEoi%2BdIhzDSjDlVcwYWnTepMKzCSWAqCmXZ1QfzAuC84rZt7G7Lg0cWJHATuaE84RKICTewjsSOQAKSkiCZLk6iMKUhiVIIdA1I0zAtN0/TtkM0jtyznOfTz7TMD0xgi/OOPjLA0cR0io3LLb6ySM5F0zaNYnKvcu3jm8t2PaC%2BKwrxiKoqn164s5ssJrS8XMpyrrVB67Aio0EqyoYCq3NXjRMcZ5qcr22mfIvDfzkk3qORPoanpp2ml6mma5sMRaSBWgg1uODanptoRgvrTK6RNiR4GIOMLGL98ZvxXtVXKc58r10KpyYqRBjjAFKkwZAZI%2B5/w%2BPgD6BkF6JWSrEAgeZrYMCtHmUqExhpRjFmWdekIE73zZNWUG6B6BYwUHAg6CDpq0FmoiL%2BS1f7/0AVtIaO0CCgPxuAj4QhugCHQLA1hh1gK2XpgIsWQ8vJNEcMgb6C0iQA1mjHEGYMIZQ05nDHuCMYLI1nqjee7iMbCgGqfC2bIhEdRUf3NyWRISQOgb4p%2BB4XRUw1IEhKPDfj8L8T2bRSZgkuQHmE84aijyaNPpTEA1N0nHH0akzknMYzB05gbICNkdQ%2ByLEY5MDsqy1loPWa8stui0AVkrWgKtBbW3Vt3bAmsA46yDo%2BVuociId15ro02BojSNOGb7UWF02lO09q7XyqBnZezcE0kWjdg66xqQhacfluibAyH9biXE%2BIEQWVBUSUcgaR3jr2FROonJEOIGomux5NnciTkhc28kaJ0WUucVS6kK752roXQCRkxml2zgizSVdgV1zcA3dFzkAVApRf4kyCYLp1KpSbMZvdjRZNCWTJuxjeT8lHgcz2E8KVeK5mmNxHU0bkKTAgjKSD2G33QbqTBpVypsEPkgx%2BzCWpKIOuKtwd8t4Px8QIhJMUREfwkQtKRq11p5yAfIkBpTgkRJgafXVEURW8RamqzhmqpU7ywTgra%2BD0jGiIbLPApCi5CuOBNKhNDGD0MYak0pLrJVJL4ZgHVpT9ViM/kan%2BJqAFmrkcABRKqgl82OHkjRWiQ2/I5OU6Jz0eUtKTB9Ux5jfpWM%2BaVAZkMxZOPsgSb0vofGGM8ZfYJslIWp0UvRTAzo3D/LWoC5FtdJ3GRDVTNuxxDmQgZaTDyzLaYrrmR8DpRyq3MKXbWndMU918qlp0gdbhSmKqZjjK1RbN2D3ODaqJw0iklJDQmlJ1a0nlpfSTN9bgS0%2BgprE4pGoB1s0uUE15Fa2QnNtueiK2zr1dP8I2OWfSNSKzsUMtWpyxkTO1qjC5MzzKIcQzSuydK1nEdQyWMsGHDl7Pdhy8e3t1mjP9nrSjbFKTCZE7%2BdiJ1J2RmeZiETsmfyPleKCd4nwLhXFuCZVc%2B7hLAw1YCbytYGCcYYHcdEYph4mK%2BkeX6qgUjEFbccKxd5RQWEkhc0U0z4LUt0ccAAamIROrLPRyGYMQG4PD941snqxiWBNYQywM0Zu45wYZ%2BdoGpRz944NxkExzP8tGlljL0%2BClxSMA4hz5Z3a6lshqgow9WJqTAqBeFBO5GWI6UJjphRndEg7kzwpYEwO68Jc5ItxYBLg9whH9cG8NxFOKUWQn8DDLgy3JvxWm0NuEI35sLshAAVhhktibTcuRqXXecYLzQwthArKdkAh6VY1bOY%2BDDQgvApDSEodANyYKem6SV2C5wEtEGM5CDQk2paGZB0ltwq2XS9mBwIGHZgIeI9B8l/wqOBCJchJILHUOkeQhhntmMWX4JscnZ%2BP72GawNaay1nJbg0cw/B/DyHOPzjHewAj7H0PIQo7Z8zxb%2BOOduDx4L3nhPzgk6HGT3LDbUJwnNnEAgEB4UKC1ErqdP2qe9jex99ImBvuU76fcLWFgOBrDSxwPbvA/AcC0KQVAnA72WGsMPDYWxMrAh4KQAgmhLdrDuiAPbZg2SJDMJIAAHFHvbGgACcoeNBZSj4Ea3kheAsAkBoDQpB7eO%2BdxwXgCgQC5/9w7y3pA4CwBgIgEAGwCApEuOQSgaA6R0DiBELUnBVBR6yjDLKkhsHIDMVINkZheBG8ICQUGeh%2BCCBEGIdgUgZCCEUCodQFfSC6C4KQPMSIUicB4Fbzgtu88B6d5wJylwm%2BelQFQY4vf%2B%2BD%2BH6PyQ4/jgQA8O3%2Bgdm9hcBWF4HLy0DWAgCQDbxSA7zIAoAgAgKgJAGACkDMD4DoCJGgUoGiAv2iDCCuyP14GwJCxuCcmiG0G6HL19zbwjCcgYFoBuAvywGiC8GACgjERL24F4CwAGyMHEC33wDnB6AeTYMdzzluSJDwPIEEFqAv2uGiCRFCw8CwAv0RDwCz3YNIAeWIGiENwlHDEMGAGuCMADzWCoAMGAAUB8zwHzCyXt193n2EFEHEBXzsPXzUAvx330D0JQGsGsH0DwGiBL0gDWFQFPCyDYJhh%2BGvFMDd0sDMALw0OIFBknXgDWC6B6GcAgFcCmD8F3xCHmDKAqD0E%2ByKGyE8HaEKMKHckGHyKWBqDqF6FmCyL0FSPcj6BaCqOGEqFsAaNKLyF3w%2BjaLyI6IkBSM922GGP0FPztwv0L0fz7wHyH2ABH2ODHzME/1wGnz/x90AL9yMLWDWiChGEhlIGD0kH8DZHjySEkA0EkEjxyg0D2yynjwmI4Az1ICz38C4DZCyi4BT3jyjx%2BL20kC4D2wuKynPy30L2L1Lx2Ir1ANrzAPrxv2bxgLgN/y7zYE4GaBYD%2BkSBhiYDNirC4HjzZE%2BOEPwCIASOzl3zsMX0cOkGcKUFcK310GQP3zfDwJPxtymIhKvyRLvwfyxJxLxIJMliJJJLZB3i/1QB/ziFOGBDMG2OAMrwRNRLiBb1gOlMgN/xAEFNxINCMCJK4FzxoD6TiBLwgEwK3wINwLUOtNC2INIIcHEMoK7GoNoPoMwEYOYLEFoDYN904L0J4Mdz4LILwEEIvxEOQEuB2F9zCCJGt0dxkLkJuAUJ2Ed2UNUN9w0K0KUB0K4P0MdiML4FMPMMsLzGsPEJpIcOX3pNkBcM30dxZI8MMKiKsEsF8P8OSKdxCJ%2Bk4HCKzkiO8JiLiLiEpKSMCNqNDPSMyJ6OyKCB9HaMWE6KKPckaN3xXKyEXIKL6NqCnIYFaNaFnKaN3LSP3NmC3JqP6MPNyDnKvIvMqBGM2DGIAOeLP3z14BmN1OFP1NFOJNJLWPJJIDlI%2BMVN2NIH2KwHiCOPT0zwCGJOuMSBBMSESH8BuMkEH133fMvyL1sGhKVLhPgARIb1v3VNVOIHRJ2CxJfxYAUD%2BjMT%2BjFNVHGEn0AspLn1kFpJrNX3kEZIbJ0HyDZMP3YM5LfOmN5Mb0uGOHvzkRYGotovosYoAnGE/2/y1NlL2H8FAthKr3AM1KgNIr0u1Loo%2BzhAYvjzhCYoICV2WkHxQNNPQItKwJwNC3ELtKIJILIOdOlKoJoLoN4M9KYJYN9PEIDO4LTI4KgVDPDK30jOjPELjKkK3yTKu1TKUISMzN4GzO0N0O4MLO0pMKYDMIsKsJZErI4urIkFrLX14rcPyAMBbKHJsBkICKOOCPcjYIxFUlbOsFiI/PiMSJapSJPPchcB9DXPnPQHvPKIyFXKPPXIqM3MGKXOPLqIaG6JvJWr3IPKmr6PWrKN2v6B2sfK93GOt1Ep5I4Bkrkrooc0UqJGUogHWIpOAoAKALAogsOM5NeKzzMGJP8H8D2zjyBJz3%2BsSBT3BIL04ChLLzApOMSHH0Qq4CkHjwQouK4GSGt38G5Mhpwvws5Inwho/KhphJALWA0IyGcEkCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/classic_modify_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/classic_modify_types.test.hpp)
