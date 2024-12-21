<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-rotate">To Index</a></p>

## Description

`Mouldivore::CognateRotate` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function relocates arguments of the given amount from the front to the end of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper
   &lt;
       Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>,
       Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
CognateRotate
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int, int*, int**>;

template<typename...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Mold<Args...>;

using Result = Metafunction<int, int*, int**, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`.
    -> Operation<BackTargets..., FrontTargets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABswQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHOaBEcjeWADUJoFuXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PAHoAFQgoEHZTETA0VQHUFAgF/AiYFipAxI45uAiXVKMViYUgHTIAL0wAH0CL8HmgGBtUgRwZDoW8ACIHAjELyYY5WB5/YGgg5CADueAAbrVYaCEQ8kSi0VyTliccw2JT7mMOQ5BSLxbQjgB2Kz65ncv6I5Gopjok7EskEAB0joAUmqNV4tcKxbUMZ8QCAIlhVKSlABHTk0hVuJ2O%2B2/QK3XmGv4HFNsi3y5OpjGZ1Op2WW62Y7G4tgxm4HPZMBQKA4AeRxxCt2VIOdzDKheFUGJd8ZjADFiLIACrNYCYAgKFsPNt54sqzAxixMZAAaxHxDHE9batzM0cyArAjGmFUqWIByYZ1QBzw6EutAgi1bAIBByiqCRbIQr3SmXqDArBBDDHA5UCoI4kg0Adh1HccFDLSCLwYdAII0JdV3XTd4JMSDY2nVMAFpy3rBImwEDF0LXWCJxjAloMETC4LLeNTUTE1Ah5f57n5EEDg8YBmCRAAlD8rVeOFpXufMM0VdMxIxJUSwXR1y0ras6wbMiGFddl3XpfjBMwESmnRRNONzaT5JtPASXJA57hYVZBB3VM3S1CEP1QZQmDHbck3wmdLMLRT5xjbB6DYQQFBcmcvEyIwDgAWU8FDjlZLA9kU1tcwgbKZ21L1aB9Ah0D9FgmBXMkAxPYNMDDRgNgxBynIpFiWIC/KUz9ILXlve8MRIxt/wJcLkUYGiVPjR88pTJ8OL89jONbHqMUvIgY3uYBITGqKYoOOKImAcEfNeNKGU87zfJOTbtsiibYzapbjVYrieLhd6pT5OEDiHTAxhrCSvo%2B4H4TNXkzB2GkXjeU5ziuNVzTlKyi2VPFmITdVdK1QatJev4DoSoQvFSX9MHQIS/q8Wh6TOnH/wxCICBBAlGZZwQgTZpmgTjJaZTk4K5zRx17g3aL2vuAmjsS8cmCoLwaX/Fk%2BNQASxOM5G6eyNU/UuyNAm1kBktodAmtF9G8YeSWDgphQqZpwJWWlpo5YVrWTlZm92c55nPa5nmwcxptkFJKslBaCBfRABQ8RDsW3Btu2CSJkmMjJhPqZuOaLA4ZZaE4fxeD8DgtFIVBODcaxrEJVZ1lOiGeFIAhNBz5YVwCMx7X1MxJAADh7/wNAATn8MwNCSHvgjzjhJF4FgJA0DRSCLkuy44XgFBARem%2BLnPSDgWAYEQEBVgIVIznISg0BROgEiiPFOFUHukgIpJJAOYBkAPKR7TMXgycIEgt49D8EECIMQ7ApAyEEIoFQ6gd6kF0FwUgQpGypE4DwXO%2BdC7N1LpwWsZwz70jAgcR%2Bz9X7v0/gcb%2BZgDgQA8Nfeg55thcEWLwbeWhlgQCQFfVIN8yAUAgDwvhIBgBSDMHwOgSJiAbwgLEHBsQIjNEuOg3gCjmDEEuLWWI2hMAOBUaQK%2Bd1awMFoMo%2BBWBYheGAG4MQtAN7cF4FgcqRhxDmLwJCBwXp7ElxPLos4mwG6M1qDgi4sRGwaI8FgHB7I8BzwcaQcUxBYip2ZMiYCFwjDN2WFQAwwAFAADU8CYCFCRIuDcQHCFEOISBFSYFqBwYg/QwEUCV0sPoPAsQN6QGWKgOk2R7EEU%2BGlUwlhrCj14KgRJxBbx/XgMsOwuj/wuGQpMPwSCwgREGBUYYSDfzFByJ4doeg9n/jmEMRISCFmeIaOMVohz8iXNqIsnotyznbIubYW5qy9AzBaG8hYLCVhrA2BITBHAC5LxwavEhT8X5vw/l/SQP9aG4AAUw%2BurDG5ZOWN%2BJgWBEiPlIG3SQgR7SD0CPqSQGhJDd0ghofwSRB76E4DPUgc9AhcHtEkLg49B49x5f4SQXB/DkqSJC%2BBq916byxTvThh8uHHwIefARQjGF3zYJwZoLBRT6gIkwCsBgEpcEHvaTlPj8BEGmaVJBFSwHVOkLUpQ9T4G6HESgpgaCHFgohcvCZeClVEPAlqnVeqDXASoSas1tD6G8MYUcCGZhMXsN3gq1VCQL6CNQAw4YwbdWViMMargi8aDUwSDIuR8C1FKP0VWjRWidF6PiYY8axjTE4IsVYmxtA7H6KcekzYJd8AeMcOKbxf9VB%2BKRPooJU8S6hPCZcSJA62HTLiQ3RJySlCpOccADJoBZV8FyQUopJTlT6NtVUiBDrZB1LgSXV1TTMkjKsG00JXTCW9P/AMoZDtn1jJXlMmZ775lPOuX4CArhvnrOQv8nZpATnZCg/BoopzNnzDg1c/8vQJj3LWV0Z5NzZhofOT8r5uHSNEbKCRwFCga4gsBVPH1ULOAXmINq3V%2Br81HWNaa%2B0GgUUWpIPGjlSbsWkFxfiygYLWXspNdS/UIr9T6kCDSyQr8kG%2BtwWvWw0rk1yvgAqk%2BhCM1puIOqzYWryEsAUKKA8ooePyjGH/QTVrgGyDtVeqB8gnV3p0CAYI7rPUYOZeC7BEr/WnzOKBINbGrM2bsw5sSYxo1ZtjQkYTgRRMHtTalvhJncuMJALZkmpJ7OD1JI5ggIdYsOskWWygFaS61rMQ3Zr9bFn6ObYIVtZjB2YEsdY2x9iG59pccu0gQ7nmjpwb45A/jp2CGCfA%2BdSil3RNXfojdKS0kuMOlkw9Plj3FNKee9zl6JDXugT5hp/nH3GFaTYN9czS59KPJwAEvo/2WHGaXQDWBgP4bA8s9w5HoPoFgx8hDAgkNQ4YBDn5oGsNkbyHhzDLzKNbIBZ8voSHfn9GI%2B80FQLa5E8Y2FleLHLNv2s7Zg4ZX7SVYE2i4TLC2FiYk8MQlU8ZMgDMCawIgR/ADyFQvAX%2Bpx7iop9pjeW8xPEv1D/BTXApCD3k%2BSrg%2BoQuBHJ367TemwW/0l7rtnsrliJMyM4SQQA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_rotate.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_rotate.test.hpp)
