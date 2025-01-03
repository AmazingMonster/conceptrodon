<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-front">To Index</a></p>

## Description

`Mouldivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = CognateFront<Operation>
::Page<3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<template<typename...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJiNBk6jXa61ncnXSkAMRImAttquzKNZpVcK5PNY3vRVwmSoctydNJhSSsSXuqrtHrZXvxWQAXpgAPoEAB0Of1Isuwa8ofD3rcRJAIAiWFU6aUAEdleL8fqc1myYFA8CoyDbr2FSzExyfQP2aXfYx/a20bdIUwFJ8APLPYhmnL5vu3OaOZAzgQTTAANzEAqFtzw6GRtB7fYg143vZ2O1u2FUaUM6BhADYNNTaXhVM2ZLfgqqC7l4ggKggLqtMAPiMAQnxUMQqAsJBLpIbIbZXPefa/nSgEdieRCtpMwCYAhpB3veU7YX2yxUQAtNOS4JKuAictyE5sLcWCQuOECkeRCjLBW45Th2cbqjGknAhSdweMAzDMg6yEQd8IIJqOnIjkmPqcbymDidgM4GPOtwsSujT5oWoYKUpmAqbIGLdrRvaabpZZ4Gmma3JcLDrII659jZkrUqgRDKEwZFUSYLmXDhbk6UObjjgZrbYMa8EKEFOFeFkRi3AAsp4H6wvKvG0OOVEbrerkJb2JbJgQ6AViwTAANYZlWmA1vWjZbPifkBQQ7advVG6iUlLrnpe%2BIWWxDBohA5YgOO6bnvBKL4hlLJZWS3Yxq29F1Ru9GBGq8V9rFsbnXaG7uclgrETmlzADSu2CNlEl1XlETAFSUUumVUrhagkXRXCr3vSaCFGTJ13w3JNqWkjezPqorBsi66mozaQIYmCEJQkDcJilsaQIfmVp3PN5o45cD1jvpk45tZipFpKtNrrd6qo7cQheGkxSYOgABKHxeJVrpAr9BUC0LmQi%2BLCiS5KwNc%2BxcIRAQ/La3suuCAc7YXdTBy3MrqvSyCsv/RbUvA3ZXqOYFcIa4t32XBW4OloE%2BYVsVtDoPi2sGwQ%2Btnob4d63sxt2nqAAqHySvTW54Mg6ZzkobTLc1FYKP6GdfW48vC2LEuVfydsjR2Z0WBwqy0Jw/i8H4HBaKQqCcG41jWJu6ybEDYI8KQBCaPXqztQEkhZhoAAcZhmAAnIvXD%2BHPs9cEkSTSI3HCSLwLASBoGikK37edxwvAKCAJ%2Bj239ekHAsAwIgIDrAQaQIuQlBoKydAJFEf0nBVCz0/AxT8khbjAGQDuKQWYzC8BFoQEg549D8EECIMQ7ApAyEEIoFQ6h76kF0KkAA7iuNInAeANybi3MeHdOALgRJ/SUqAqC3BAWAiBUCYG3DgWYW4EAPB/3oMQGEQ9li8DvloVYEAkC/zSP/MgFAIAKKUSAYAUgzB8DoMyYg18ICxHobECIrRkRUN4CY5gxBkQLliNoTADgLGkF/jDBcDBaDmKIVgWIXhgBuDELQa%2B3BeBYDakYcQ3i8A0gcHgA8Hx6E9UcQibYw9tb1HoUiWIK4bEeCwPQxUeBD4hNIPE4gsRFaPHCcAJERgx6rCoAYYACgABq7xSEsVbsPdBwhRDiBwT0/Bah6EkP0IYYwPdLD6DwLEa%2BkBVioApjkYJDEiRlVMJYawZhz5lOIBtOZEBVh2EcY0FwDB3CeE6HoMIERhhVFGKkYo2QBDTD8I8zIzyGALBGIkcY9QTl9EmO0S5BQ/m9AEP0No3z7m/NsEC15eg5hQtuYsB5Rz%2B5bAkDQjgzdT70Ivhw0B4DIHQNgdPAREBcDILEZiLgkiR71NWFBJgWBEiHNIJPSQgQsyL0CNvDQkgzCSG/Bofwn5F76E4PvUgh9AhcCzJ%2BLgn5Z6Lw3p%2BfwkhV68s/HiohF8r43wZffWRL85Fv2YV/FRajRGALYJwVoLADxJAYkwEy4y%2BGLyzPK9uSCiB7JaqkHpmD%2BnSEGUoYZRDdDaPIUwShITsW4rPrwC%2BTCP4IluGwwlXDIGzgKlwT13rBHCMUaI8RgQzD0ukQ/M11qEjf1UShEtoxc2aJXifGglUEgGKMUQqxZjnF9psXYhxTiSmuPgu4zx9CfF%2BICbQIJziwnjMie3fAMTHDxOCT61QyTmTOPSbvduWScnIjydsduhTinDzKRUpQVTl1/XqXwJprT2mdOcUGvp2DQ2yCGYQ9uUaxl1I2VYKZWSDkLKWXuTgqzmrrMmRYbZybdn7PgEc/5sTnAQFcAi1INyKg/L0E8xouH0gfMaNCpYYKAUQvhSCt5PQaNNCBZRh5cKBikaRYMFFhG6VrA2Jivju9E34s4Fm4lbq80FpnoIqlfqy10qkYy0gzLWWUGxdK2VnqBVJH8IvLegRBXCs1bq8%2BnADW3yfU/V%2B78WH1trcQW12wHXcJYAoA8O4Dz5qzKOCYiD8B%2BtQYG2Qwbv24PkOG/9OgQDBBjXG6hkqcV0L1Ywi1rD2GqFc%2B5zz3nfOSiEY2pRZbAiVqs/Iwroj7MVdGB5oW6YvOL3THl9MmXQ26K7ZQHt7dB1eOHj14dJznHjsEJOrxq7MC%2BP8YE4Jw8l0RPPaE6JALN2JJ3cgFJ%2B7BAZKIcesxZ6Cl7KvbwG9lSWQPrqca59UVX2YA6TyD9IWv0SB/XgyLIyYtAYmZssDMyIMdygwwYJOxywga2TshI/qEnzMY5hvw2Hzmkfw3cqjZGSg5FI8RnIrHYXHNh5C4F%2BQGO48aPj7HiK6OE/J/MHjMKsX8YHnT4TyWzMcA4VljztwGs%2Ba9BMWTAWSAKdK8aplmAWWjHZbvTTIAl5ZkCIEfwa9NXHzl0kZVpnk3mdsIaqtywJ4gEkP4Hlm8kjH1npIFeXB55mB1bvQIzONeXyNTI7FCD1cMMdzr1YZSsjOEkEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/cognate_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_front.test.hpp)
