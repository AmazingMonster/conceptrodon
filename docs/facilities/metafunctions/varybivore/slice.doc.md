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
We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Slice` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

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

- In the case where the second layer of `Slice` accepts two indices, we want to collect the variables between them.

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
            ::template idyl<Agreements..., Vay<Variables>...>()
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
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDM/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZiSEWQ3iwdxMSTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bCkg87gRiF5MHCrNdQf99ncAGpMFGMw7M1nspic%2BFCoi6tp4Jixeiiq6TZUOa1ojWBCx3eaOZB3cWTTCqNLEQXCu4ANzEKthnr1xFt9tVgQeatjqaS6pBlMBuZ%2BmqpAEk2fQ2IIzTlDecC3na8Ca4dHoRkAgq8aS2bVfDubzWF2MddnV5XUIEJg2rGrCm1RSriyO%2Ba3FkAF6YAD6BAAdNvC46hyOx20CcSQCAIlhVGulABHFUSgmF7eb8lJAcgz2gu5fxUmjmq67fnKbifoB37zqai6WqgT7ov6BgKF8ADyLzEBWAikCBoF3Lsux3AA6pgdxeEosIAGwaDSdJ4KoD7ojB5GKqgdyMD4CSdoqY6YaBOFEQwADuhgsuggrEMArGCAoz4AVh0pUTR8K7q%2BT5yPxgmYOgGHSVhPaMH2T4ACptMAmAEAoXGOoBPp4H6AYslGtBhlaeDoCitAQCsXE8VEqAshxZpkRoyFsU0JgMXgXwRBGqAANbqXcsQGvZKpmVp2G4UGSpMA4cVUMQqAsBxhHgX%2BdxpG0fYssQkmebh%2BkIOFdwNfEojEYRfFtXQDllcg0XMRGCQGoQrI1XcqBUAF8aJvQknbqFGiNYITFzXqaLkVJVyAQAtLBQWoSF8KGaJJkKKeSWYDBr4zh6GZZg22rYMGXhGIR%2BbXMVnZcjyun8oqX18v2oL7lKhY4uFhEmB%2B06ZrO72Liu65bjuArwxuT4AFJ7kqw7A6DSjHgQ6CnueQZXpgt5vF2biPrNr7IwTRMMBepPk/e8JoxdGKXR6WaAbD/4bd%2BBJcbzv4fRawoc3BTAIXcu1oQwmkC1hPEEURJFzZR9K0Ups0MVatJZa2BBjt6UxSmNAWHcZplzetMmyVrCl0duiv2yrhGtQFmvUQSGM68%2BetMSxbB7UVJtRgmdrTcL348e1dwCYIjH%2Bp4jR2zJ3vyW4fvYAZRnHa7Mk6f9MGpRZ35WTZAiBvZjlMc5rnuSN3m%2Bcb/lzXLIVhRFDBRbFwkJZG0afCNGWodlwm5flhU/guhFlahbCVdVqU8XVDVNZgLUkfHfGdaVWW9Zg/XEIN84jRby02lHnz0fNERWlfq0aOnX7ba%2BssofLBJW8dp3DxzK674bqzi1HcIQyJthtlBHzAkUEnyTRvmZLmTosYjkgfzCGPMwKi0ghLGmb5LJoKlDSHyqBlBMGMpOCGICNSpVgfCFGUorgsA2IIcuX4gbSjIRQ4yBIWFsIIBw6hqURZzy5Lgym8CCFSwQk%2BK4wBaSskYDbFB9tiIRGAHcAASkwOgcoFRYChDpGOX4ICmNAqOccxB8aExACwJgsU1zE0vDeO82x%2BGsKekIy6aj7bflPHzRqLlaD8MUZgZREknwChWgSRBSZkG5wIU3UR34PLQzLlDW69DJHHjwKuDc4CzbI3yQjO42BGbCNpLePAtIvgQAGO0ICcIFQVPQB5VKXDSFEF4ZTRpBABRtOEVgwWqSvwMLcBM6Rz4P5QmljNTcCilFllUYQmSGijA6L0Q5FpdwjG0BMWMu45ijmARBu8PGjD6b2MceuFxzN3F9LNuiOmdiHFOPuW4imBI2mbX6S%2BNZ/i7iBMkcE1yYTlkqIWTE/UcTr4JOdjM7AKSlagXSdgr8NCgFcSmfgxZ4TImrK4hsrRvSDHcJ6ZQymSyIkrIWS%2BW6WTQG1jzMCMBAAxWpkxymqFYOyF6TI7ostOPWHMjZO6VlenOXJ4siCAMHMQz%2BwUcjYrFdqIQXg0jFHUtoz4XgDnQOuCS8BmrtXoF1QofVUpdkSoEASMwAozAMuZfcC1VrDVXGNW6g1uyIHWUphoAUXBHWOsdKeXp9qw0gF0XQAktqGDOroTcKk%2BlPhSilZXNc8yEgEAgCeEACg%2BxZuQW4DVWrMg6r1QcgU3qfHYHRS64VAI2VUiEFvAQwkHp8voB6rUTagSNvVaait5qq3psFUarImyy1mtrWuLg5L40EmDXcJ1vjsnJtdWOj1Xqx3zvJX6jx8JA13BXQ61dUaI3whXUkKNMbQnwiXeuwddxU3coza0X0xalDtDzdcwtbBi0EhnSOudK6wPonRRwNYtBOD%2BF4H4DgWhSCoE4MBSw1hvQbC2ODcEPBSAEE0NBtY0UAiSE3BoAAHGYMwABOWjXB/BUco1wQIgRpCwY4JIXgLAJAaEDYh5DqGOC8BOoGwjSHoOkDgLAGAiAQAbAIGkRE5BKBoDZHQBIUQ%2BycFUJR0im1SKSDuMAZAfopCbjMLwdShASDOT0PwQQIgxDsCkDIQQigVDqEk6QXQwa%2BKoTSJwHgMG4MIaIyhzgiFETKfNuNPTBmjMmbM6e8jZhjkeA0/QUMWIuArF4BJrQawIBIHU2kTTZAKAQDKxVkAwApAOpoAchIJ0ICxAi7ECIbQUTBd4J15gp9EKxG0FvCT%2BH1MrMQgwWgPWfNYFiF4YAbgxC0BOtwXgWAHFGHEHN2po28D9TW8hoMW9EQ7Hww/BoEXkSxFQqfDwWAItKjwLx9bpAT6xArU8LbwBkRGCI2sKgBhgAKB1B8PiQVEP4cc8IUQ4g3Mw882oCLfn9CGGMNYaw%2Bg8CxBOpANYqA0hNDW5tYkLTTAYcsGYITJ8ExYDx%2B5Xo%2B3nAQFcDMPwwawgRBGFUMYwbijZAEOzvQAumiLFGDUJnDh%2Bhm2F8GuwzPmhm3F7zyX8xpieC6HodXQxudLD52sBQ2HtgSFCxweDpBBO8GE3cBLhnjOmfM2l45uBbM5bw/lgjAO1iHiwIkRnpHJBJE3LRpI7GNCSDMJIciGh/CkVo/oTg3HSC8aSFwTcpEuCkUo7RljpF/CSEY6H0iluIvCdEyAcTAPpNyZKwpmLKmqs1ey9ptgnA2gsAjIETaTApabK4LRzc6fjv4CIHThzshnPw%2BkIjpQyOfO6AdQFpgQX1tm4t1byLHBotKcRKNeL%2Bn7d960QPofFGMv5XK9l2E4IzCe8K1JuvzeEiqeq5f2rcyjAD64IGpry9KDtY%2Bb9bda9akDAGDbDajagETYqJTYzYRbzaLbLa0CragGbbo47bIb4C0jS6HYRYnbIBnagGXacbIY3Z3YogPY7DIbPavb4YfZfasgYGaLV5A6UKg7g6Q6gEw5T6uYz6yBI7ebIaL5o7/YU5WCWDY647wAE5E45Ak5k7yjiHWDU7W607OSfAyFS5NAuCMxy4hCMwq7LD86ZCC65Ca4FAmElA5BGF87aEy6DD6EK7S4CD9K2Fq6y4WEc62DK564S6m7rCbAm55aJ7m7hY%2BY2525Jaf4n6D7D4u6j4kA35p737e6kC%2B5jCM6cbJ6p6D4R6BD%2BC0ZsZJCR7R6F6l4RGcAV5V6SbFa15ICKaxav7P7ECt47Ad5JYsAKARh%2BgRin5/iTDWaJHj7Bo8Fw58HubyBz5CE6AgBJCkDL6r4hahEb5l5RYN5xa26dHdG9H9GdjcoQCZZX4JDJFJCpG1HSalbv7ZbNHXFjA9Faprh9G0ZrgDEEBriqBGZ8B0D/5tYdZdanygHgEohDYjYODQH5STbTazZYGYALZLYrZrb4boHbbUEbZ7a4GaE%2BYEFEFvYkHXY44UFUFPYJh0G8AMFKDfbMH/YXFsEg5g6YAQ68jcGT7jESD8EebTEo5zGiEY6U42A3YM6yHE6cC7AnjKFU404JB06aH472Es5s5eF6Bc4VD%2BFWFmH6Gi42F%2BGq7a4NCK79JOH6kuFK4LA6nGE%2BGOFKny6%2BGqm6khFG5BGubr7hFCacBbHGZdE9GRh7EsgHGu5j7JF5YFZpEZH%2B5m45EgB0abhJApBMaF78axmBDZ4VFukia2CV5e61EkYgCSD%2BAh6saBD8aUaSAMZcDUZmAl6cZJCunW5VFZlFZm5Wapl1npkP4rBrAnxZDOCSBAA)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/slice/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/slice.test.hpp)
