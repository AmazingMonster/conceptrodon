<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyConditional`

## Description

Different inputs can lead to different metafunctions returned by `Typelivore::AnyConditional`.
Overall, `Typelivore::AnyConditional` yields a result according to the boolean evaluation of a condition. Check out **Example** for more details.
<pre><code>IfTrue, IfFalse -> true -> IfTrue</code></pre>
<pre><code>IfTrue, IfFalse -> false -> IfFalse</code></pre>
<pre><code>   IfTrue, IfFalse
-> Predicates
-> Arguments...
-> (...||Predicates&lt;Arguments...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
AnyConditional :: typename... -> template<auto...>
```

```Haskell
AnyConditional :: typename... -> template<typename...>
```

```Haskell
AnyConditional ::   typename... 
                 -> template<typename...> class...
                 -> template<typename...>
```

```Haskell
AnyConditional ::   typename... 
                 -> template<auto...> class...
                 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct AnyConditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see four examples that present different use cases of `Typelivore::AnyConditional`:

```C++
struct IfTrue;

struct IfFalse;

using Select = AnyConditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if any argument can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 0>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >, 
    IfFalse
>);
```

- We can pass predicates to `Select::Road`. It returns a function such that when invoked, the function becomes `IfTrue` if the arguments satisfy all predicates;
otherwise, the function becomes `IfFalse`.

```C++
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(std::same_as<Metafunction<int>, IfTrue>);
static_assert(std::same_as<Metafunction<void>, IfTrue>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Metafunction<double>, IfFalse>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfFalse>);
```

- We can pass predicates to `Select::Rail`. It returns a function such that when invoked, the function becomes `IfTrue` if the arguments satisfy all predicates;
otherwise, the function becomes `IfFalse`.

```C++
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<-1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Metafunction_1<nullptr>, IfFalse>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfFalse>);
```

## Implementation

The implementation is straightforward. [Check out this test to see how it works.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxmpK4AMngMmAByPgBGmMQS/tIADqgKhE4MHt6%2BeqnpjgJhEdEscQlSXLaY9oUMQgRMxATZPn6B1bWZDU0ExVGx8YnSCo3NrblVo739peUSklwAlLaoXsTI7BwEmCzJBjsmAMxuBACeyYysmADUAJJUACrEXpikN%2BeXzGz3VABiYiUx2wJg0AEFRi8HDcwQwzh4GPg6mJQWCTAB2Kzgm44j67fZMQ4nJheIjA1G4m6QrzQgAimEadBuGKs6NpxyxaOxuJ2ewOmGObhJRHu5O5OOImAAjl48JKFKLxVSCFCCDd6YzaIK7mKwZSWTcvOkjB8LrdjrTfs9XhzmWyOaiKTz8fzBcLUKKjiClZKZXLMAqIGAwHclk6cdS6QymHRtbr9ZjDcbgKbLsyjpaHgDaECjhY7ey847wcWuXrnXzCQLiaTUAA6Btg4CS3aMAgKeO4o3hFPKJjAc0Z9XR2MnCANusYtxT6aOZAAfVEo0FMVQnmBECbLbYggUSzDXpAIE%2B1c5pdLlN5BKJpzN30wE%2Bw9B37c7OO7JoAsp50OnLRqYy1McJynGdGjnRcmGXE5V3XL0ICfVtdyPAA3MRXn3YEjxPB0SzwstwzxSsbyvV0ThPe8QK9G5kAMBQFAnZRJXwUQdg7L1CMjNUmNQIgACVUCYdBCJZQjLxdKtBQo65H2fNt2O9ctKXfZMbm/WhfwtYdNUFccG1A9E3FnPAFyXAgVzXIDsAgJjMBYqt2LcRCXwY/TDxANDvEwTD3JwoslQxQszyVUjJPIiSSLvGS3OwGi6NcutbPsti3yTHsbgEoS/xuHj%2BME4STiSkyHKokF/KU5l8IvCtr2rU4Irq91SriqCEqK1iA1SricuIXjUD4wCRMxMSarIoVawnAA1Jo8CYGJ6AUkaVPSvsB2ygDRzcPTJ0MsDCRMyDoLcWCrJs5jipSk5puIWb5oDUrUPQ7yD2wbCzVwirAo%2B/UQoaqS/prIhmto1rGPOjrFqVD8UwGpktNy/rBsK8GSpij6vvK1EAHoACo8fxgmsex/HHmwIRHnxonwVxgnaapgizCOcJaK8LB0zcNAGE2ZJXw4/Duoea1T1LAX/kBYX8Ohm4hBqTBoS02F4QEJFMhRE5BZeN5fmzXMyuCsEsaxm5HgDNUNBF8CDta%2BICAgUZ0CPBRrnnKDBRl2oj1WuqqhuMxgXeDWbS9A9OWMhdreaO2CAdkAnbYF3HPduWCE9/s6o0d4/a9AOnk14EQ9RMOE6USP7cd53XZOJOHFTgdBQzm5zez7Xxfz9HqaNk3RhuLgLf28P6JtqOY7jzAE8dE5COrlOQHU4SAsnpVKTLkBwh2ZsxEXARpkEQU1/eXvm6W5UY7XzAN9oLeGB38yTn333Uv9yqKsDgUS2D9uIUtgeS9tlfR/Hu/acSpp5HjniJReFVl7RyPGfC%2BV8b570EO8Ju2B3jHxXnA4gm9OaILvsgh%2BfNPpHyVK/Ce2AC782/sXIe/8K4diAVPWWNdZ4/ggcAqBuJMGCHPtgy%2BuDGi73wQQFBT8MEwNXjw%2BBAjDC3zcPfVBEC0HP0pFmVu78KGf0NsbU2D8qGqhuJNVAeB0B3CEfrUKkUvjRUnEQ7qRiTFdx2AkG4yQvDzRMifI8VBxbzhPHaVkQVSyWLqrqexxj0BOPiIKFCESsKuPcbQTxK8VSvD8WaAJGMLEA2nHY1J0IHGRNNtEq6ESzG31egkjxyAvHHk1uktMol7SY3BCEqSUU2ClULvktU5SokuLcdU2pPicxj38U0oJ%2BE2mTzyQYvpxTiBIIqSAKpSSakpPqeM4azTsnEVCbMmkvTBD9MFIU8p8TBlrNqaksZGSJmf2mbeaxnTGzEGAJDMEUtPzRioF4LmdRsrT1REeTKBU3CFP6QHY5CzdRgLYScMEbyErkhaV/fuNDS4SIAZXNw3zGi/P%2BZkJZT8yEf3KkXCOf8sX0MFHipgBKHBEpOLEkxJLc5B00eS6hlLh7l3jjiulDK6inLKUI5RpLOWh25YPTFI8aUnEFX8xlAhBToDWHdNlOtqySu6einldD%2BWJ2YTPUFgosKsI0ma5uajRlt1RdopxNwjjBJyU1NG4JuqRAEPkDIKFMD9JWZc5JEiRlKAaeabZkyyyPPdJ6RSvpZTyhuBAO47MtIaBuGGD1PSbheoYD6xwfqTnqwuYk4NMcbnhsyTsl1ey3QTXdV/AxeaIjAH2kWhZgay3rJDb4rZgSHmutrHG1ECb/SBgzVazMWam2HNzQIVt7b/UwpLYeVZ5bsKbLuZGwddbAb1lee83UXyflKrqPOLggLjXApALDICbg80FrwB20Y8R3gtvPku4tila51URe8rpqKKUyqpXKw1tLT2EoEBewUh9xXsu1ZQtFEF9XUvAwqyDyqGAwZOAAWjgznIWdqpV6pA7y2O8rcWYfPYfNwqDCN5zJSRlDZGDVjwFdRzIOG3AMC8LQWgPNFnWrFrapjuqWO/3I9io1Htb1I1ya9EAXsrXwa1cRjgKxaCcAAKy8D8NwXgqBODTksNYKkawNjmkZjwUgKcOBaH3KQAA1iAbTkg6waEWOiI4GhtMaDMP4QIAAOIL%2BhOCSF4CwCQGgM76a0KQIzHBeAKBABnOzDnSBwFgDARAIA1gEDcSIigEA0B7DoPESI1xOCqCC/4XDSQbjAGQDUqQdYzC8DsoQEgJi9D8EECIMQ7ApAyEEIoFQ6h7M6D0AAd2wckTgPBNM6b05oQznAADypJCs3FQFQG4NW6sNaay19zZhk0eDK/QYgzJrNLF4OljTmWkCleSOVsgxWXtvZAMAKQQQaC0GcSliAMRVukBiOEJoZwFu8HB8wYgZx1sxG0MnaHpBSsvnWwwWgUPJukCwDELwwAhT8ZSwZvHuxDDAHELj/AkpGV%2BtJ/FzAqg5aki2DZs%2BWncdJJiNg%2BHHgsCg5VHgKLZO/XEFXEoekLBKdJKMKtlYVADDvMmngTA031tfFR314QohxDDZ12NtQoPdBVAMPL0wpnLD6DwDEFLkAVioB5pkUnuH7YWkt1YSwZh4uoHFzdLA9uIArDsMnTILhEQTD8FUUI4QBhlCGFUJ9Ago95DSBkIoce5iJ86GHgQPRxieDaHoUPWGC99Cz4MCotgxgtCL5MGvMxK8J4qCHizmwJBLY4Lp0gcW1scH27V%2BrkhGvNZ7qd5NuAuvXfMEcZY92FcrAQJgISQxg/OZAJII4dYACcRx0SSE82YSQ/gYvaf8DvsLHAIukCi3Pus/guD%2BCCzvoLT%2B3NcG03v/wvfQeJeS6lrZgrpljlhAEgPloVuQJQJ9ldpVmwJwE0CwChOiLhkwC1CaFwDvnWFwB5h1kiN1g7FUDrgNvrtIIbkoMbrjroEELNkwPNgZl3j3n3glhtltqSDtntogcgagegSmJgdgR5udqgJdvEDdkcGYHdkAZNisGASgMIa9ldlASVvIV9lwSgSDEYJgVwBnP9oDpQCDrjrDpDqjkYfDojsjjXGTujm2JjtjqDvjoTsTjmKjlgDLkYNTvFrTmHgzqDszqzjsKjpzqDjznzkrILrjsLqLjZuLpLpgNLrLj2MAUrv2AoKrurprowNrrICQUNmQbIEbhNvFtQfoJTigNYNYDbnbvAI7s7tvJwG7tHB7uUd7r7v7iYgGNUbnlhhHu4PXtHsEIiLMFXmngUJkKnknunnUEMS3iXsat0LXuMV0XUOXtMfMFMAsX0SXrXqsYnm3usB3ssFfkwX/pwDcGoTwRoXwVgTgRmghPgTPrdgvtIUvivlgAkOvlzjfnflgZ5uiF/uiN5pIMfkkFUMwf/rYIAQ9jIaAeAWwUVtASobAVVhwIgQ1iwAoChDUihPwfyKMHgdPj1kQdkXrrkSNvIBQYUVNkcKQLQfQYtkcStrjolptgVuwbtmccQCwGiRiViTiQ5GqBABdgoaIbPkcJIVCU9nISIe9gidKR5MgMkMkPONiTvvOLiQQC7JyUkHwHQHocDqDqYTjjZoaeYSjlYcIRjljjjp4ZgATkTmIM4WTq4bLlsJ4f6PTh0bjn4cgGzoETwlzvFiEZDgLq6fdjdFEbwDEWkHERTu4YkdIXwMrqkWrhrlrmTsQSSQsGSQUSbiANSebsYM0TYDzkHjUXUKTljGXJ7tYD7oZm0YHp0aXnUD0YsbHiUMMRMaMSnpsZ2RngwDsdXk2fMb0IsUOfntsc3msY3oXjkP0dMM0AOZ3qsPsUNowYyb7qcaiSPuiZiTcCqXWOqZPvcWIfPlIQ5i8avu8V3l8SAGYFgUcEcNpn5osDFg%2BeiM/r/kyZwAAWlovhvpINprvtpkFgFjvpIDvt5vvlwPmZwEcOuf3k8eeVfu1p%2BRuUlmeRpisOLukM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/any_conditional.hpp)
- [unit test](../../../../tests/unit/typelivore/any_conditional.test.hpp)
