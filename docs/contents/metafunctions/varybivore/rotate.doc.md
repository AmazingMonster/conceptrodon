<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rotate`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::Rotate` accepts a list of variables.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function relocates variables of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>, Variable<sub>I</sub>, ..., Variable<sub>n</sub>
-> I
-> Operation
-> Operation&lt;
       Variable<sub>I</sub>, Variable<sub>I+1</sub>, ..., Variable<sub>n</sub>,
       Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate ::   auto...
         -> auto...
         -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 0, 1, 2>;

using Result = Rotate<0, 1, 2, 2>
::Page<3>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<auto...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    // Note that `Operation` is invoked by values extracted from
    // the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<BackTargets::value..., FrontTargets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM2akrgAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwc5gDMYcjeWADUJrtuXo60hACeZ9gmGgCCewdHmKfnyDPoWFT3jxezwImBYyQMILObiYl1QxwAak08ExovQAc8ZsQvA5jgBZASoIgMO7PEwAdgsxxmTEcyGOaAYM0wqmSxGOMKIxwAbmIvB9yRZEcRkajMOSACJnSkSqWAwEgsEQsXnAg3ZKMViYUjs2Hop4MrbJAjHZTETA0VSfcXHAhY5VWUnA0HgmnKtyq9XMNh6zHY41CADueC5XVOFJluwdQKeCpdkPO6QAXpgAPoEAB0mYAUj7bX7joHg10oT8QCAwlhVCmlABHPkMLZQrOZ9MA3YPUnh57HHs251KqGA3vDvuK11QjmoFv3ekGBQKY4AeXVxBpmVIQ5HPdN5rwqib9xbADFiLIACpNYCYAgKDfdrc2tUatgtixMZAAawvxCvN83Pb1YdqVpekBCZFk2UnY48HQG5aAgZZ/2OAB6ZDjgiQkPgIBAPgKDIBHpBBDCvY5UCoU4ADYNBPc9L2vBRpyo9kGHQSiNDfT9v1/BiTCopDUPQzCbSI41eI0Zc4jXAQxOghcwi5VAP0wVjohubleUwBdmVtd8QVYqhTxYfi0OwrD%2B1dY5kiaTUQWIHj7x7ABaGcJNXHooQ4r86JvMseW8TAW21GjBC4%2BjfI06d21lTtJUjOUnTHeNoVhFshRFegFFzLEcQAJUJcdOyjYdYwHBM8GTNNjieFh1kEQDe19HFTUJVBlCYK8kIFJDivMpKSvHc5J0i7BZyYecWyeYAzVBRg/yihyRy8dIjGOHKmDoK1jiwQ4PTFBbhwgbqH0LENaBLAh0DLFgmCUlMK2ZatMDrRhG3OaraoINsOyeB8RzLfqQWg2CzreqbMBmwQGMzbV8QYFriShNKUQyw9M3uBCjp7RC4oWiMoyQgG3SGzNJumthIfqnslrCYATXa/ldmtZqiDajrQbJ2aodbKKcZeMlYvx55kIAKlFsXxeQwERdFs9sCEM8xcloXxZV4WlejV4G3eT4LiuW49XlXqiZStH5qeRrjVcqSGGi6NqZWoQvGSAplJyzSvFoUTGaXFdrahQJjg0bUuG1Mw20Fp57dpt2FA9r3rTyxokqD44Q%2BOAOw7NstWbdXY9TLNa6ChK33J5iPgLwZAUzGpRmggUsQAUTVq8y84Y7j7VHedtJXfdz37mxiwOFWWhOAAVl4PwOC0UhUE4NxrGsKl1k2fkzF2HhSAITRh9WD8QDHsx0zJMxJASBIx40ABOQ%2BNAohJdn0ThJF4FgJA0IOp5nueOF4BQQCDtvaew9SBwFgDARAIB1gEGSJccglA0BgjoHECImpOCqASBRRyFFJDHGAMgOkUh0xmF4MpQgJAYJ6H4IIEQYh2BSBkIIRQKh1DANILoEOAZVzJE4DwEe49J471npwRclxYHGjIscDBWCcF4IIanSQxDjgQA8Eg%2BgbI9hcGWLwIBWhVgQCQIg5IyCyAUAgEYkxIBgBSECDQT2cR/4QGiEI6IYQmg3F4bwVxzBiA3EXNEbQtQgGb0QeTAgi4GC0A8WwrA0QvDAGhLQWg/9uC8CwNdIw4gYl4DNHUEMKSZ7MlqJcbYm8wgglHmw640RVy%2BI8FgIRto8Bv1SaQEMxBog93FKCYi1wjA71WFQAwwAFDwjwJgAMEkp6b2ocIUQ4gGGzOYWoIRHD9DERQIvSw%2Bg8DRH/pAVYqAjSZBSY5H4ZxxSmEsNYMw392nCiwPshCnRuiZBcCxSYfgQ4hHmGUCoeg8I9E%2BQCtI%2BEGCDD%2BUsF5QT6izGBSHGodQBB9GaBC4YlQxj9HhZi1Fvz0USFWAoFeWwCVPw4BPUgX9eA/ykZg7BuD8GEMUWYZRuByEaPXlonRAzVg4SYFgeIzz96SF2OmK%2BuwySSA0JIU%2BVENBjwolfMlL9SBvw3umCiXB75XwSFqsekguBj3FRRSlQif5/wAVvAZoCIEGKgWIuBZiLHqNQWwTgTQWBcjJI5Jgo0VpcCvumLg6ZCn4CIA8qhshaELOkEspQKy2G6ECFwpgPDUn8PJYIthP9REwMuKRciHqvU%2Br9bTANQaQ3KNUcY9Rpx15mG0Va4B%2BjDGoDUXEeB5i201pGEW71hxiIBq4EHOxtlHHOLYd49xnjSBTt8f4wJDgZ2hNmhEqJQjYnxMSckmd6TenbBnvgXJjh8lCKKcgEpM7yldCEdU2pNx6kHp0cKFpm92mdKUN0jJwA%2BmgGbXwYZozxmTM9DO2Z0b6GxtkMs1hM8k3rP6Vcqw2zqlPMOccsCnAzkXQuUhm5dy4gPM0vAQlXQYXOAgK4bFPzSj4pDoCzI2KGPFDxYsDFiKegopaJ4NoegOOwv6GitjfG4U8dyAi2YQn/laLWBsElMnKkUqpcIjg7JiCeu9b6gd/rA3Bo0KysNJA60b0bbo3epA%2BUCsoBmlVarA3SrJEaskZJdgyskDgkOynzW2EtWZ/RtqkDQPEZ251KC0EcA9bIlgCguR0i5OWpUMxSGGYjSHcD8zIOMPkPG2DOgQCPxTWmvhZKlNmpEQ6iRhb1NRZi3FhLroZhVu7SY4zuxTPWrtaF0xCDmvqJALF52KZ4tXxTIlgg1dquxroGOygE6Z5zuiZvBbC6gnLrbWEtd0TD2YDiQksQO7Wl7syU%2B0gR6YWnrYeey9rTr2VJnne9xj7Gkvpne%2BrpPTMk02tUM9qQGJlTLA1GjLEgoNMJy6s/LCHjBbJsKhkjs8MOMk4MhUseHLC3OpfcmCxGDnQqRX4SjHyxNfKCCxKTULmNZGJyCwomRyfsbI/jrj2L%2BPIsk6x6TOLuM5BJ9SXFtHhMyaJXJ%2BhGbSvZs4GplgNXYvcnqyCRrEA2XhuM1yptejeWYH5SMZ5lTbP%2BEDbsXYY9L4Go/kbsk99TUS9/j5wBPLSDCrJMQxzXApBXwc%2BKrgZIyW7Czd/Tg3Lm0ZpIdbgPtu/OrHaekZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/rotate.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/rotate.test.hpp)
