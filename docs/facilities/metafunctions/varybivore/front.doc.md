<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-front">To Index</a></p>

## Description

`Varybivore::Front` accepts a list of variables.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects variables of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three variables from `0, 1, 2, 2`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbgA1JjIhkHJkstlMDlwwVEHWtPBMWL0EWXCZKhxW1HqpIWW5zRzIW5iiaYVRpYgCoW3ABuYmVMI9uuINrtKqS91VMZTgTVwIpAJz3w1lIAkqz6GxBKacgazvnczWgdWDrcAGIkTCVo3F00quFcnmsLvoq5Orwu5s0mNWZOq8mXZkds1uLIAL0wAH0CAA6TcFh1Dkct/FEkAgCJYVQrpQAR2V4vxBc367JgQHwI9INu74VxvZXbcs5N84tVB7zRP0DAUT4AHlnmIcsBAdD8vRaH0/QEANI1oUNLTwdBkVoN8PwgfCEPfHYdlubAg0MdAYQANg0alaTwVRbzJOiFVQFCvEEBUEFbVpgB8RgCE%2BKhiFQFgeNbUTZAfK5iI/Bi6RYp9MKAzdJmATBhNIIjiOAuSP2WXSAFoQKghJYIYfEsEhHtMAgDStIUZYj3Q5VgKfKd3XTTN6y1RsxO4vMrj/b98UA%2B84wTegFB3RVh0lALZAxV8DPfULOwPPBlzXW5LhYdZBHgj9d0lalUCIZQmE03STFSy55PSr9Mu7ZqAKFDzsFAphwPvS5gBpFkhNizy0uIrwsiMW4ACUmDoWV5Rs2g7N0hDCLGxqm33OFDxAFgmAAa1XE9A3PTAr1eH98sKghH2fTaEKPDLmVubDcPxfrBtLYTOogXVUThKLbRislX2Te8jI2wyvIaj86p86cEOen8Is3T7MCGwQRvuj8JoiYAqWq1tYXlcrKqJj6Box76FE6mH4fp7Ma0ZPzyNUVg2VbYLrmZ7nWfMmDGjbEFkfCjrNzi51JQFyzGZ5u4hC8NJikwdBpo%2BLxluFq48amxXlcyVX1YUTXJRJ24ZcafENH5Lh%2BTMR9fKZrVjdN7XLl1gnXa182kqKuEbduO3blSEO0SPKqarhQJw5AWa6HxS2ckd6dNVuAAVD5JW5708GQFceqUNoIF2hQ%2BwLka3H1lW1Y15b%2BW926nyMjMOFWWhOH8Xg/A4LRSFQTg3GsawvXWTZibBHhSAITQ29WA6AkkdcNAADjMMwAE4N64fxV5XrgkiSaQO44SReBYCQNBtnu%2B4HjheAUEAbZn3u29IOBYBgRAQHWAg0gRcglA0CsjoAkKIfZOCqBXjRYyNFJC3GAMgX0Uh1xmF4KrQgJBsJ6H4IIEQYh2BSBkIIRQKh1Cv1ILoO2AB3GCaROA8Hbp3bus9%2B6cAggif%2BkpUBUFuFAmBcCEFIKDkvMwtwIAeBAfQEMmIuDLF4C/LQqwIBIGAWkUBZAKAQDURokAwApCpBoMtBIj8ICxFYbECIrRkQMN4JY5gxBkQQViNoTADhbGkGAd9CCDBaA2IoVgWIXhgBuDELQR%2B3BeBYH2kYcQAS8A0gcHgcMHxWGBjcQibYU8IjMhPn3JEsQYKOI8FgVhio8AX0iaQFJxBYiG0eDE4ASIjCz1WFQAwwAFDaneNQ8yPcp64OEKIcQRDBmkLUKwqh%2BhDDGGHpYfQeBYiP0gKsVAaRGgROMkSEmphLDWDMLfGp8YsDLIgKsOwbjGguAYO4TwnQ9BhAiMMKoow7bFGyAIaYfg3mZA%2BQwBYIxEh2wuUkgQ/Qph3IKMC%2Boly%2BiTEGE8xYrzbDwq%2BXoOYbQAUvKBecseWwJBMI4F3UgN9eB3z4dA2B8DEHINEeI3AmCZGT3kdPVpqxeJMCwIkM5pAF6SECOuDegQj4aEkGYSQdEND%2BBohvfQnAz6kAvoELg64aJcBoivDe%2B8aL%2BEkDvIVNESWsLvg/J%2BrLX7KK/ion%2BnCAFaJ0dI8BbBOCtBYOGJIxkmDdSmlwDe64VV9wwUQY5ODZD4JGdIMZSgJkUN0KkWhTB6GRMJcS0lbCOAcL/giW4PCKUCPgZCGZQc/UBvEZI9R0iYRgjMCyxRb9rUOoSIA7R4kK2jELUYX1XAbZGOZMQUx5iKH2OsR44djjnGuPcVUrxQkfF%2BNYYE4JoTaDhI8dEmZcS%2B74ESY4FJETA2qAycyDxOT6isIKUU5EJTth93KZUqeNS6lKAaRu/GrS%2BAdK6T0vpHjBnhsIZG2Q4zyF9zjdMlpuyrDzIKac1Z6ycibO2XKSD%2BzDkJGOaklZPRYXOAgK4NFdtHkVEBXod5jQCPpF%2BY0LFSxoW9DBaiyF3zsOgqaPCmjyKMXtCY%2Bi9jiKSNyLWBsfFgmT6puNZwPNVLvUE19f65e9L8DBqrcq2tbLSAcq5ZQQlCqlV%2BtFUkfwG9D6BDFRKvVRqKEmtsGautlr4DWt/lw5tjbiBOu2K6wRLAFDhl9OGOT34JjoKU1g9Aoa8HDIA8Q%2BQ0aQM6BAMEBNSbGFyqJSwqz7DbXcN4aoLzPm/MBc7BMMtraNEqcCGpi179VGlekS52roxfPKxXP5jeK5AsEBXLlyNdA%2B0DosVYxxo7BtOJcZcjxM7BBzv8VuzAQSQlhIiVPddsSb1RISbCvdaTD3IEySewQZ6KEXusdesp8Z728EffUlkr6WlVfadVL9mBek8l/WGyLEhAMkNi5MhL4HZl7Og4s2D/d4OoU4DsQ8KHLAHLJUc7CmGeUgquXhm5FGiPPNo5RkoOQKNkZyBxoFLHGjgu4/kZjyO4XzH49i3jAwKNccJwSoT49mdifS7fST3Xbjed8xGQrzJisQAZcp2RlWlHsswJy0YPKT66ZAJvdcgRAj%2BF3nqq%2Byukgass5z%2B%2BNnn7qb5f4QVB8khXxXpIbeXA15mENSfQIHOyWcAUepk%2BaCddO713Z1YNSsjOEkEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/front.test.hpp)
