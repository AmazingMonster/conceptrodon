<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Slice`

## Description

`Varybivore::Slice` accepts a list of variables.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked by an operation, the function collects all variables with indices greater than the given index from the list and instantiates the operation with the collection.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>, Variable<sub>I</sub>, ..., Variable<sub>n</sub>
-> I
-> Operation
-> Operation&lt;Variable<sub>I</sub>, Variable<sub>I+1</sub>, ..., Variable<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the variables of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I</sub>, ..., Variable<sub>J-1</sub>, ..., Variable<sub>n</sub>
-> I, J
-> Operation
-> Operation&lt;Variable<sub>I</sub>, ..., Variable<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice ::   auto...
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
        template<template<auto...> class...>
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
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2>;

using Result = Slice<0, 1, 2, 2>
::Page<2>
::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<1, 2>;

using Result_1 = Slice<0, 1, 2, 2>
::Page<1, 3>
::Rail<Operation>;

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
struct Monotony
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
    // of `Variables...` into `Monotony`.
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
    // of `Variables...` into `Monotony`.
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
            ::template idyl<Agreements..., Variables...>()
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
            ::template idyl<Agreements..., Variables...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIACcAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHOYAzBHI3lgA1CZ7bl6OtIQAnufYJhoAgvuHx5hnF8iT6FhUDyerzMBwYRy8p3ObgIt3SmAA%2BgRiExCApAS8gQRMCx0gYsVCYXDmGxSCcmFdUOjnmgwZh0gQTspiJgaKovgARE5IryYc5WDEvLE4vG8i6ExisUWPF6TYheBwnIQITBtM6BKyBdl8oGY7G4pj4i7ZABeCIIADpLQBJKmy%2BUMpUq4hQ34gEARLCqeFKACOPNpUKtlvNgL20te6qBJ2jXL1IqjMahCZjMaF%2BsN0NhErYwYeJyOTAUChOAHk4cimqRkymTgB6WsnADqny8SjOKQ0TJZeFUgYeuY7XNQJ0YPgSBs%2BBGV1ZT9ZOXgYAHdDFj0GTiMAx4IFCGXjWY13WX2w8G5EuV5h0FW9/uuVniZhgwAVNrATAENE36NUlPzRzIfMBEmTAADcxDJCkTjwdBbloCAVhOABaPMy3HJooRfDd3x3S1Q35CMtT2fDdWFCcCXvSVSXFB9bW5BUrTBPA2xMSNNW1AVnjTeMjTwU1EWDK1SRNM1gwAKVouV6MYpQXQIdA3Q9TAvV9f1tkDXMwyEuSFIYT1vUwP1GDUi5RI0x4wx1SMv1jUj8WspNrJTLiyLFCic1wsN8wMItS3LA1cmvZ5bzrBtm3nZiO0PHtj2wAcNCHE5mSYZAEC5ZUTnmdoTlQKh2w0TC3w/EwO13ILbyi3sLhtE9LUC4K5zC1tPmKztmSPEz%2B1wwciBHBgxwrSd0oabFGCKxyYznRdPmXQQErQWhGlK4KKqhcSavNArsLq29qMlXN7Is6y/zwACaWAsDaAgnroNg%2BCkJQvz0IuTaPzM9iCPekj01FTMiT2y1sHoNhtwk%2B1FRuNSMSssro2cjNySIN6jrohkmVQIhlCYN81Q1QjiOsuGfuExETmeFgNkEH8YztBU0YxrGfrJimCCp79oeCwmCTjFzfuzR8POwLzCxw81nmAZkRpBw6YZrVsImAE4ACVUCYNdzk5LAjnFGcYwgHX90dNpZPkkAWCYABrBFFOUgzVMZ8mFxZizpeClM3UJqCYNoKExYl4HXtqk5AclgOQzDeD9ZOFZ3pTFi8Z1AnuYzYmHSmAghN4s0g901nEttvBmWLCABiypM9k5bBdOj5HJNR4h0dQTG3yhEv0%2Bz9Bc5YixE3G2Gk5%2BznXL%2B9yw8Fgsi2DX3MBDtEXdvOWjCVlW1fLk5NdobXe5OPWt5TBjkCYontNNi2rd0pT9MMgMLlbh4tJNs3Lfha3L7tqFK/QRDb%2Bd8NXZjd3%2B6e1gj7cW09/Yi1JMHcBZkI5b2jkRascdPqJ1sj9BGqBJ6gJnrnBeCsm7NVXnTRuDMQF%2B1GiLPCll44cVrAAKnoQwxhtYgR0PoU%2BbAQgnwMOYS8VhjCmEJ2BKCcEkJvgCG2PSWe4YvrcV5g%2BJGzwaYMlQhWXIyDni4MVF4dIJRLyK0wAoLwG8OS%2BTQmoi4EQCD0NJJY%2BhlCOKaP0YY4x6twYnR%2BpYmxghaFeKsT4qC3jaEPDdPgqEZhgkgGVqrKEKj/ICHsa8GUrR/zwmFgkAgEBXQgAUJKVJs83BCG0bo9ATijFt1KRvB48D8YaOyIvQpOish6IMWU%2BEXATGxKem4Wxvi7HOxqY4lpG82kmKEBDDxghem9P8bYoJYYQkkIuFwUkewIlRI7hcTp5jzI1OOsgPJSh2iZOPjktgeSW5FKaSUoZBA2mkgqbcrgVS%2BQcDWLQTg/heB%2BA4FoUgqBOBuGsNYDKGwtjNRBDwUgBBNCvLWObAIAAOc0KQ9iSDMIESQkh/AIr2BofwSQEX6E4JIXgLAJAaA0KQb5vz/kcF4AoEAlLoU/NeaQOAsAYCIBABsAg6QrjkEoGgHEdAEhRElJwVQCKUiIRSJIE4wBkAASkOaMwvBLyEBINBPQ/BBAiDEOwKQMhBCKBUOoFlpBdDLMXMidInAeBvI%2BV8mFfzOAliuHyhkOUTiSulbK%2BViqTjKrMNvDwwr6DEDOBClYvBmVaDWBAJAQr0girIBQCASaU0gGAFIMwfA6BYmIAyiAsRnWxAiG0W4dreBluYMQW4JZYjaEwA4KtpAhX%2BxLAwWglbzVYFiF4YAbgxC0AZdwXgWAzZGHEL2guzbHAgQMc6pSzarg7EhZYhozqbixGRHWjwWBnVIjwGSsdpAF3EFiE09k2JDDABuEYGFawqAGGAAoAAangTAi5ULfMhTq4QohxCGv/SatQzrLX6FvSgIFlh9B4FiAyyAaxUD0lyKOxCvx1amEsNYMwNLz3EGgoupDvQ525BcLpGYfhllhAiCMaoYxlklByAIKjehmNNEWKMRIyy7BkYEK3NjvHhoOH6GnLjDGeO2DTkJ6TCw6NLEY2sBQoLtgSAdRwT5VLnW0u9VKmVcqFVKskCq7euANURv2FwaNULH1rGVKrMY8FSDwskHsc0SQ9gYo0GiyQHY8UpCSESjgJLSBkr2FwZFXAUgIoJdF/wkguD4r2GkalvBaX0sZbZll8bOUJu5e6/laaM3hrFWwTgbQWAgUCIhJgQtF5cCSOaSLvz1VEEI/JZZ/69VAekCBpQYHzW6Fzdapgtqx0aa02ll1HA3W8quNlXKlXqu1fqwrRrzXzTxQgKG5N4bI17DMDZ2NrL8slYSAK9NqAw1jGWzVgsRhGtcEpTQDeCQi0lvNTWitrbvt1obU2ltp722jU7d251faB1DoWqOyFE7b3Tt%2BfgZkomF2jta6oFdWJW0bveea7du7bj7p2L8o9J7IXnsvUoa9k673y0fXwF977P3fqJK27rgGDV9dkKBs1vzhuQYfdhqwsHt2Iecyhpo6HMPl2F7h/DCQOvEec3x0TzgICuFk7Ryo3H2NZBY3kTwXQ9elFyBJ5Ywm%2BgCZk0bwolv%2BPNHEwp3XvGbcFGo3J9o5ulPrE2Gp6zwWps6c4OuKrNW6sPfW01lrZn8DtYO9ZmNdnSAOawIkZzePQvhaaz5wI%2BLAiBFRWYPziXtPmoy7YLLJ3cvwHyzyj1l3zvEDKzsSrfqWAKBAgBECG2RSTDVXHzVnWjUAf1RIbnxqBt850CAPYpBRvjftYHp15fXWFc9Ut4gLB2%2Bd%2B773ickwQ3Xb2wkA7exjsM7O8flNjfr/hpAF3nR8Ie9JHhH325be%2Bv5ve5QT7vy/s9qQoAEA5zqtog6CBg49pI6YD9qDrDqw7jo3pTok7jqzqo6LrmrLrICro46CCbr47waE7E6HqEbk68CU5XpIF04Po5aM5YzM5fo/rs6yA9Zc4j687gaz6C7GAwY2Bi7wDIaoZAScC1iuhy6WB4bpYEZEbi7KYiZNAUbuC24e7a70YW4ZD65NCyYcZm7O6SZ6Cq5NCCbKEGHyFibyY676Gu6DCyaZRDB6EW7KaqYGqTYr40oh6f4nAd5d4nAv7mjv6x4WYJ4X45b2Yqhp6UAaZZ4gBmBNZ7B7D%2BD%2BA%2BbPYaDxGBAxZl7uF0qV5MrJ6uaRYpZBBmCJGJaBaSAaC5p457BuHpacBJ6hHBaqqZG1HZHV5rDnrZDOCSBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/slice.hpp)
- [unit test](../../../../tests/unit/varybivore/slice.test.hpp)
