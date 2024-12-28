<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-distinct">To Index</a></p>

## Description

`Varybivore::AreDistinct` accepts a list of variables. It returns true if no two variables in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreDistinct
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `0, 1, 2, 3` are distinct. Then, we will append `1` and check again.

```C++
static_assert(AreDistinct<0, 1, 2, 3>::value);
static_assert(! AreDistinct<0, 1, 2, 3, 1>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we will create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.

In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
This is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Treasure, size_t I>
struct Label
{ static constexpr void lark(Treasure); };
```

To instantiate `Label` with variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Then, given a `Variable` and an index `I`, we will instantiate `Label` as follows:

```C++
Label<Vay<Variable>, I>
```

Here's the entire implementation:

```C++
template<auto...Variables>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    : public Label<Vay<Variables>, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Vay<Variables>, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<auto, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if a variable
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Vay<Variable>`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<auto Variable>
        struct Hidden<Variable, decltype(lark(std::declval<Vay<Variable>>()))>
        { static constexpr bool value {true}; };

        // We check every variable using a fold expression.
        // It returns true if and only if each variable
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Variables>::value)};
    };

    static constexpr bool value
    {Detail<std::make_index_sequence<sizeof...(Variables)>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgAOxBAA6oCoRODB7evgGp6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimCmujMh4mApX%2Byfnl0c/B59npwBZgAzOFkN4sFcTMC3F5HLRCABPaHYQHmUEMcFeSHQtzIUboLBUFFor77K4hJhxWjvPb/AiYFgpAwM3EEREPZhsK4AFWImCYClWmFIVwyAC9MAB9AhXACSJPOo2IXgcFKpNTRiQsYsajmQVzQDFGmFUKWIVwAbqg8OgrgZiABrCB8gVC/kLaE6kyJG5e0kXckANSYiNpu3pjOZTFZMKYcNQVxDxDwVPoirOytVspDyPOPp1031hoEJrNFvjRCtYi8mCh2uTqZi6d9XvrfuBVnzZN%2BvY%2BgO%2B23lTPobEEMay4eOA77s%2Bn3bODJHMcwuMrqAAdFvG2nXhms2qzvybnhRmCCFqu2crjerkvo7G3OzOaxV8DUedb7qVWq7o06PWVitp2AZfveLJvm4ErSgQW4bgq76Al%2BB6yn%2BTB0LiBIgCA4RYKoUpKAAjrWmKQXKcEkohn63psmxXAA6nWyD8iuVyGFcqCWvEtCoEwdpKLKBAIMQKzAAgVzhAg8SEIY6wbkht4gFcKReM2eAGpS1K4rm2lNE29AKCiooIdgFHUTeBYKV%2BN60QxdYxCmRhXJgXHEGGJgAGwaA6jqeRoVxUCJLASQQbwxIKTEGAohnmdZtlVkJTGrPyghimgDzybFX5eBkTmaZqMI6YVem7oZ77GSi2E%2BRRIELtZNF0YxVwAO50DS6CJkIABicqRGc2AcQwd5SWKmBGnaKRNK%2BDLEJl171Vctk8iNRLxrQspNMAPiMLKfnWrafnOcawoxfN9XxSNaBMnQ8SGlJyCOm8iVig8zxiHg4oTgIVlxXRcT8Pyw11uaeAsE0YbgSuc0LXeUYQWuCais%2BjCvtCNz7egGYwyhVwABK2lgDA/V%2BBa6hOBpGmW5pXDEqCeNW3h1gWVBiEoPodt6wFXsTDW8ggp4BV4mJ1ENyD3Y9ElUGx1YpruPM2XRAvhEDyn8paTg5bQYbmpxtqYHaCKjNDC22U1gqOirV0pDdFpVjQDB2kwUJeT5h1CTG8uLXRWDgk0rzS5NxDTbdqBS8jzsaEVbg7s2b6ol5xvnXRcph5dqDXfQFr2%2BgT0jX5PmkH5nsXQLCivamCKfSLLVtTTdY5frie/VcADyiXEK1ShIyNINg25sPLgyNe0DScRXA36BN2BcMrgjVYx%2BmVFndZOP44SjC6bLseij760cpgEA%2BRAWEgLvlpiLpyLFVvi%2Bou%2BEALI/WMLaTRbqSWxoMuWNN0zS5%2BM4BAgKpVxc3bP6OqJtGpMXFs5VyYZz433rrlYA0t%2BC0DtKac0rwMgCCnrzOUsp%2BQEFWMaO8wDJZsQdoNLWFCBRixlvpVcWVeZMBSA8JobwBA0IEOsCSQ1nqG1gp7N%2BFNSxf2prTem/9ayewLBACiZgPLmA8mvQmm9GFlWwNhaRmBPRcx%2BuzcBAJYoiI/lTC0ki/41iYcvAsaEMIwhPmDR00pcKmgIpgYiTxILQVDnBCAC9XiekQu%2BbR1jDG1QBPohcg45z/EHFcbAqhWDMjrP2Hsc4IwBhEVKQUShmgQCPJgE8Z5ha4g0KKLgooghXGBJVEAOjglXhyXk%2BIBAIBgDAFcIpJTHBlJhBUq4VSrg1OBJU%2BpjSvQcCWLQTg/heB%2BA4FoUgqBOBuGsNYMUKw1hMxBDwUgBBNDTKWI6AIkgNwaAABxmDMAATluVwfwVzLlcESIkaQsyOCSF4CwCQGgKmLOWasjgvAFAgAqYcpZ0zSBwFgDARAIAVgEBUgQcglArY20iK%2BTgqhLkeQALQeUkFcYAyADRSA3GYXg%2BtCAkFtHofgggRBiHYFIGQghFAqHUFC0gugqnNSDikTgPAZlzIWUclZnAW5whRRxKWuKCVEpJWSoZ5yzBXAgB4DOt10RcAWLwSFWglgQCQBizOaKIBmqGMAKQQQaDrXiGCiAMQJUxHCODYVvA3XMDci3GI2gxqQv2VdMcBAW4MC1hKrAMQvDADcGIWgYLuC8CwGDIw4geX4H5A4PAXEk3LNNGNOEGx9nhAZJ85ZCIHLgw8FgCVQDQaetIK5WmSg7hpuAAiIwRylhUAMMABQQYXjNRbpyJtjLhCiHEGyidnK1ASr5foQwxgNmWH0HgGIYLIBLFQCkEWSb8UEjRqYSw1gzBAtcimLAW6H6dEDVkFwDsJh%2BCqaEcIAxyhDCqWkDIItn16B/UUBgsxBgJCqXYe99QxgtE8G0PQEGc1QZmO%2BuYX7bDQf/eB6DIHP1gaWAobZ6wJCio4PM0ggLeDAquAqwlxLSXkrVRq3AtKLS6v1QcntSwpJ8SGLe05khgQblucCd5GhJBmEkF5DQ/gPK3P0Jwb5pBfnAi4BuDyXAPKXNuS8jy/hJCPOEx5cjErgWgvBRxqFxr4UmsRTKuEFqrXECxWwTgTQWCWkSPip2vsnJcFuRuVTBb8BECvQy2QzLp3SFnUoedPLdBBAFawz1JGyMUclRwaVyK4Ryuo3i2jhoDC%2Bf84FjVWrraZyhCCMw7HDXQps45hz6dytDB8zah5FT7UzSdS6nl3qPXJtIH131/rA1NpDTtcNkbM2YBjXGhNSb9mpuXRm5ZWb715olYW5Axam1lpqBKqtQc3K1o2MshtvyBstvSMUxky3wigEs3wftg7h2jsYOO8LU7WVRdkHO7lyz4tLu7Seqwa6q03p3XurIB6j3AhuCDs9F74hXtePAfDNRIN%2BAgK4TDwQHY4fmN%2Bwof7YN5CJ7%2BrIBO0MIZFj0cYpOX13sQwwOnfQUOgfgxhhnnPkOlA53q5YqwiMC8%2BalkznBcuKuJa1oZxWLlMeCyQSrKmaucdINxrACRb2fMU8p/zYnEj%2BFuW84E4nJP6eMzy0zthzO1as/AGzSKUWNe1U57FHA3NKpYAoS0BpLR%2BY3BBUY1LFehaqROiL332XyBi/9nQIAxmJaFcmlL4qrdSrs7KUO1Gvc%2B79wHoPspNVNZtsr4EqvHv1ZL%2Baiglrq9DF92wqU/vblSkL1KVQRK%2BB0C65QHryyhuIibYPv1AaHBjfTqGybQ/puzfjSPBbKbbvptOymvA2bHAbZ5VtnbA29sVt4IdmtGBV8HJTBd/ZV223L87fdntT2mADqHZgEdY6BsR6%2BxIH7HLY8LoT0DldU9MHDdCHFZKHUsTgTYLCBHSwc9SjS9PWUAmnB9bHJ9bnV9fHdnXDADYnLIXHQDEWKnMDJnWnLnXIRnZApDZoIgnnencg2gtnPnbAgXAjIXVlVPS3IFCXTvYlb3X3K0AvFcUYBXFjZXPVA1NXDXXjEjXXEAO5DcYEYEfwJ5fTf5RQxITTTgyjTgMzCFNXfjfwITV5RIf5S5SQB5Lga5RReTDgYENPLgkFCzI1EjKlLQ9LCQyzJYVyHBPwSQIAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_distinct/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/are_distinct.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_distinct.test.hpp)
