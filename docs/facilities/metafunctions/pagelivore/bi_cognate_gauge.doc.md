<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BiCognateGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bi-cognate-gauge">To Index</a></p>

## Description

`Pagelivore::BiCognateGauge` accepts an operation.
Its first layer accepts a list of transformations and returns a function.
When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion;
then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;::value, Transfs<sub>1</sub>&lt;Arg&gt;::value, ..., Transfs<sub>n</sub>&lt;Arg&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;::value, Transf&lt;Arg<sub>1</sub>&gt;::value, ..., Transf&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
BiCognateGauge
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognateGauge
 :: template<auto...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
// Gauge `Rail`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Gauge `Road`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see six examples that present different use cases of `Pagelivore::BiCognateGauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** AddZero ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

/**** AddOne ****/
template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

/**** AddTwo ****/
template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = BiCognateGauge<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** SupposedResult ****/
using SupposedResult_3 = Operation<0, 1, 2>;

/**** Result ****/
using Result_3 
= BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_4 = Operation<1, 2, 3>;

/**** Result ****/
using Result_4 = BiCognateGauge<Operation>
::Road<TypeAddOne>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_5 = Operation<0, 2, 4>;

/**** Result ****/
using Result_5 = BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Pagelivore::BiCognateGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BiCognateGauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>::value...>;
        };

        // Multiple Sequences
        // One Variable
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        // One Sequence
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        // Multiple Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>::value...>;
        };

        // Multiple Containers
        // One Element
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        // One Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Device<Elements>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGaSAMykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5dnhyYaAIInZwDUAJIs6fRsgkwDT%2Bc390eV2BVwBd1udwImHeBihJhSbihMJ%2BmHhbiYXiIADocfDsE9kAYFAongB5dIJH65PEQxbELwOJ4WPAeYDMKEAcQxwFR9xMgSs9yewqeSI%2BKLRYthqIRGOxuJS%2BMJTGJOKxABFMAA3PD7BQ0oUiukMghPZTEVBEABKTDoEJFT35gruDodh0OTwAsl5aI4PpgnkJMABHLyMPX213C91en1%2B%2BhPABqbTwTFi9H1hqjUolssxqDVyeIqfTmH1isjUeNjM1rTtWddTsrUZFXmyRlFAE8KY6UuqyRTiFSBGjNTqIwiiyWM3iQCAtWIw2qaSlnS3HYF1fDnc23R7vb68P7AyGwwwIw292TIkmU2n6LuRTm4XmiLfi/eZdhH8Lq6ba7atBolOn4Gi6LZNpeLZthEwBdj28L9uSlIDKO2q6mWwF3qWs7zoumDLhWq4/huW7EXyUHCs%2BMrovmap3MAxCYNCjAEOW36UU8MEdsoTA8r2/YAXaCIMUxLGCAohHYHOBDdjKa4ivyZE7g21GStC4ovrR8pYniBJEiSY4YWBDp/maFrWoBaHjl%2BzaQeBUYxqSN5BqG4a8g5roxge8YBiBpaZp5Dpqa%2BBY4v5M4VpxZlCUBnH2euDrcXBskIX2A4odSCJGfsWEfgFuELt4BEKt%2B5FBYpm7bhCJEhdpYVYqJzFfGxJnQe2cG8fxiFPLFaJNeJbFSTJcnVQ2SljeCqkadK6nIlpcoNXpyqqjiA0texzbJU8Np0AJ5mWqgu1ASJjHNaxkmlZNzZ1bdcnMGwUn6Sql0auhE4cZ5ZnmodVqoEw6B2QKJHeXGR4Jh43wrMQgXrqDh7HtgnwXbVM25oi92sCVWJI4Nm3RQQ9I1pgdZxRVwoJYlwrbalAY9chQ6odl72YQiuMbYV%2BFSZN64TeVIP7mDx6Q3WkQwwL14BuzrGo/NNG0w9UvI4IbVVoTJq9STVls8rBCq42wOcUlHXwXT6UM8ODDWRh5ZuNLKuKnORVLld5W81V/OcXdFKK/RZ14/rxuwV6njoPtfWnWJG3DSAtM85Vyk1dNctzZp8uY49pXPcSms2fr30WUd/2A8zedRZ5lOOR6zkBiLtpi7DLbw75Tz261Xto1pCtY2qbf4%2BTTwxVr9YD5XiU03J%2B0W0zbg5TRfec8V3NuxBHsqQP3uMD3a3%2Bxz5frttnqh%2BHw8nW460XTHccrxTa9J55t2d%2BnPvb7pirZ69F8Sfr21/QD%2B0/WtMXfqu9L6ux3HfCiDwQQwP%2BBCIExwngADE8Aw1NNgVQrBjxwMBLAvBYIapmBSBEQkXgsC9jcGgc8mB0itXLvA84Tw7joHQAALQSKgP41wIR1UWq8MCZlmFsI4Y6PkApRFfVaI4ZABIBCLEwKodIxAnh8Odh5B0ToXh8wsBI7R98EFMJYTXLhpwwS8PzPw8ugijGRBquI5siwqQyKofIxRyjVH4SBhYF4jpLBPC4No3RkCprQOeEIgAKgAd04TgyET80R8K0VY9WjIInRLsTohxUjdSyIYK4pRKiLFqK8T46wTwzCBLsYnKBBjp65BMccMx8TQrc3uGZOpI5PahNOIGLw6QSiYHQFaMscYGlgm2kIPpAyhkjN9FPQcls0QaFIP4lZFSiLrwMcMhQozYm/1maaGq6VmSsnZJgLkXgeRog6Vbcuc5jr9RYewi0KyhE11eSwqJqAwJzi6jRDQK5NmMPCWWU0sTHHSIAPovQSAQCAix0BzgUFjaFtttlxhWZM/pWRBnot9HiDY11cF4NgWCAxQYqFhwwVghMsSEEktBPoxhWLpl4rBdw%2B4Eypk4pmTs30kKuDzMyp0twXA1krJSICplzw2VjIhPsvlBABX7ROagNkKILlXIRDcn5IAHkiRsbZe4vy%2BL/JWWK8pUqanAtBXKtp2TkCoqUO0eFBBEUgGRWwVFaI2UCsxdypQvK4wCoJUS7pDLLhkuBQgVBVLMEwgDHSiNwICHEp6Synlsq9kmwzYG31ZghWMyym4ZZ5SVmSCtSErZBy7V3AVcGgtPVVXqs5NyGiOq7l6u1ufJ5HCPnoHeYY9AXzdV/KWeatZlaGHPBBYsWtELdROtha691nrMDeoRPm/12K80HMhes7AhKun0uTRy8NyCdjtAQK3eN2Cz0ntPY06VPTwlySEc8mJZ7N6K1brrARKTTSvopO%2BkRGSJGmQdbk/J7iimePGgKNuTtPFryCdUqtwK32Gtrd%2BrGv7Br/qJoBzDA7bFiMyQ2Bdzi5FQjcYUt8xT4MWEQ3hYqvidEBJQ1UsNBigOYDSZ%2B0xPDmkYxfmwPDLUCMa14/xsDWSnFQZowUjxxUvHMbUWxy1nGxFoenemgNuKa3ZuDrmgzirIUpELYshEpaLUHu44wrNZ7638os0c/szazmavbQspmn17nAIRNJ3tLynhBZI5gFZYWR2dqPrQEubgEVzgiFCRiYhIUuNaA7NwyWVkAqImVIFM7bXgodUul1iWPUopVD6vdaRek7tM8GyVioj2FcffexhKCqAEGvdShNtaH3JtTeekzQa5lGY7KN31khLMz1sxKqdabEGOcE5yk202VUsjVZ5tt1yfNZT83qgLbgws111bF%2BLWT3XJcwKl2g6XqOGD1giHLTw8vYFIFdpLghbtDnuxlp7aJXsBMVJ9ijbrvspb%2Bw9vJmXnvZcEJO%2BhGzn2INney1bdxKNlbhRVtdG63DTe3ayvdFaWv2fax154Qg8CqB6zemliaqeU6fda6n%2BmxsY9Z3WnNHPfX%2BFm8W0tZhy2LfPSt7nzmlUC6bVtlt5zdvav250w7f94thY/ZF4jg6ovpJi6HNEX2QA3buzDxxWXXvvbB5I67P3TcA4t4j/xeJrcQdt1DtLDv4evbs3yFHbOX3FbPdjmF5WIeVa9dVzde7/DE8zTH0Nq4OBbFoJwfwvA/AcC0KQVAnA3DWDKQoS9%2BxfEpB4KQAgmhk9bAANYBEkFiDQAAOMwZgACcbeuD%2BGb03rggRAjSFTxwSQvAWASA0MszP2fc8cF4AoEAyzK9Z%2BT6QOAsAYCIBADsAg6RMTkEoGgd4dAEhRCxpwVQTeABsABaS/M3gDIBkVILEZheCDMICQPAiKxX8EECIMQ7AUgMgggigKg6gy%2BpAugYqkSQ46QnAPAKeaeGeVeOenApImIu%2BpoqAVATwF%2BN%2Bd%2BTwD%2BT%2BDeBaEAHgR%2B9Ayi5gZeGwvAS%2BWgWwEASAh%2B6Qx%2BZAFAEALBbBIAwAUgIuNAvoCQ8%2BEAsQKBsQEQbQnY8BvA4hzAxAnYpIsQ2gjQS%2B5eh%2BLUzktAUhEBWAsQly6ItAtA8%2B3AvAWALAhgwA4gOhqCKheAWoZYKBCijQmIBw5eN2Q%2B2etAeAsQQ48hHgWAKBhMeAY%2BJhpA9hxAsQOKmo5hRgXhRgVeWwVABgwACgiYeAmAkSyEme5ev%2Bwgog4gQBuRoBagKBUB%2BgFhKABelg%2Bg3h8%2BkAWwqAtCuQxh1%2BCKiEpglg1gZg0%2B4RxYWAdREAWwDQTQzgEArgcwfgYqYQKwVQNQegJQOQAgEx8xWQixDAowsxEwYqwxAwQwswngXQegOxzQSwGx4wiQ2xSwyxlxwwZxawFxQxxegBiBHA6epAU%2BvAM%2BuBV%2Bt%2B9%2Bj%2B/iJBTwEAuAH%2BVBRCXAtBFeCRWwCAmAAMEwgxpAdeqQWIbeKQA%2BGgkgyQl%2BE%2B/gl%2Bbe%2BgnAI%2BpAY%2BZeWIl%2BXAl%2BTebevel%2B/gkgXeaJl%2B7xKBM%2Bc%2BC%2BUJy%2BjBG%2BTBW%2BGBe%2BHBXBlBp%2BbAnAbQLAWogQ1%2BTAz0HYXAbeWIXAjeb%2B%2BARAfReguR/%2BBR0gRRSgJREBugIuMBTAcBJhLxbxHxqBHA6BO%2BmITw2B3x%2BBM2yocpCpSpGgQJ5BrBlBpeZgkJ9BK%2BvJQpCQ%2B%2BnBqAFBEwLpvBneyyAhUIMMlAohEBshkh0hpAKZ8hihyhDgaZ6hrEmh2h2euh%2BhYgRhaZZhFhVhRZNhTQ9hxh2eThyALhaZ7hKBXhPhkh/hBw2eQRIR5e4RkRSg0RlZsECRfAyRqR6RmRPsaZmp%2BRgBOpsgxR4B2ehp5R8RHRVg1R7ZAxDRTRcinArRbq7RVRFg3RnxvRX%2BDh9RvQ/QuQLgDA7gBxhQUxj5dxcxYqCxAw1xGQqxAw75Wxt5thAgexHQz5kxQFIxgwpxMx5xRxVx4F8FtxsF9xEgjxuw%2BwaFhJrxyBEBXxeBvxspcE8pipjeQJIJappeEJdB0JpAsJ8JiQiJQ%2BxJpJCpmJgQ/gbe/eKQWJkgd%2BYqlpbJtgHJAZ3J8AvJ2%2BmBoZwZxAIpBw4pBBLACgWoMiWoJF0oiwKpoJX%2BGpsgWpC5wB8gepK5OgIAaQxpppCB2FFprJaB/JWBOBqgilylql6lKIc6ZB4Z3pCQpeKQ/pY5QZXlbB0lQVlB84yA/SkKalbekKGlSqTlOpdA8ZwhSZ2eGZ2h5e6VWZKhuZ4ZGhDAWhKBxZwABhZZoRFZsR3ZphNZjgdZjhqgzhUILZP2HhvA7ZvhnYXZgRxYfZvAA5UR0II58RXJ45fEk5GRWRs5el85Egi5IBxlpRZl65xgp5NRsQu5Oe%2B5eSnAhwiWm5XRPRCQfR15iJxxox4xiFr56AAFFxv5pQuQP5X5uQN1RxfQwF0FwwP5Z1H17QL1Nx%2BxBQEFjiv1KFH56Fewzx1luF0%2BnAuBzlKlTw0VWIcV5FqpJAVF/lXJMJcJWAjFLxLFSQCpKQKQ/g3eDJE%2BxNgQVJLJeFnA7Ji%2BtFyJ/gqJfegQE%2BTekgneXALeZgzJQ%2BKQ0NnxdNnJDBLxr%2BNNMNs%2BIt1eYRQh95kgQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bi_cognate_gauge/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/bi_cognate_gauge.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bi_cognate_gauge.test.hpp)
