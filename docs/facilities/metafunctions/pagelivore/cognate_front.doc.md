<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-front">To Index</a></p>

## Description

`Pagelivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
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
using Result = CognateFront<Operation>
::Page<3>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

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
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    static consteval auto idyl() -> Operation<Targets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrcAGpMZFfQ5AgiYFhpAxM/FMBGoamtPBMWL0MlXCbELwOHmoq4mADsFluc0cyFuaAYE0wqjSxFunKItwAbmIvJgYbKacQ%2BQLMDL7rC5dbbeTrpTlMRMDRVPSDozmaymOy4QRkc9mGxSNquULLiqtmkCLcXW68B7YfdbgRRVbAlYpRSAXnviC/ntbgBJFn0NiCP05T1nQv5ht1nNOu4AMRIxoLVyZ5b9mbcgeDrEz6OF6bFcfbrpNVmlNqzjp7vv9biyAC9MAB9AgAOj3JcjIontyn/aJIBAESwqk3SgAjkbsf2S3ud2TAqPgbKQbdf2mfWyVpXH%2BMJwj%2BIF/kugEclyr5osqBgKJ8ADyzzENWAikOBEG3DsOy3AA6saXhKDCABsGgJu6%2BIHh%2BcEUWm3KMD4CR9uRGgACqtMAmAEAoJgUW%2BwE4fGrrUXCtHYK%2BXHEDxfFYcJOGDoww5wYpoGfiBeG3FEqBMmmCB%2BuxqGsY0AkaLceCfBEeqoAA1pg6C3LEdIGt4HzYbh%2BHqumTAOI5txUMQqAsAZxpQWxaStMOTLEAoQmXFp%2BEcQgVmWZ88SiCRxoAO65XQtC3FFyB2bcmB6gkdKEMynnaagVDsWaFr0PFe7mZZgjcuZNKooJnkKngSoqmqbnhrqeDoMitAQMstwALTwSZ6FmXCMlyQoF5uUacEfg6UpzntwK5gctweMAzBMq2wWCLW3q9iuEUrjqqA7dgCFMEhtxLRhDCHuO4pnRdmBXbIGLfupj1nngG7brclwsOsgiRiBR7ii6emoMoTA8Z5MrZolImQzBRCvk1/ItcjIkkREwDxtjxoprcWCQspnkgRAbMiae%2BLniALBMA5m5Xuqt6YA%2Brz9vDiMEO%2BmkiSBF6Q5Zk20Pi32NGGPX4mTlr8XRbUfjNnO/ssh0gfaC7NiBRNws9r6XMArrMowfGU7%2B1NGHTPGgam6NEFjONwg7TuVnxr2HRb%2BP1o2DLRyd2CqKwrKdrHx0x0CGJghCUIM3C0ZPK7u3NkWX1oT9t0gjbbh2wbn6o3G6s5BHae3EIXhpMUjkAEofF4tBxl2lwe7Tbcd5k3e9/3Pul6ZTdwqktxcGGZjvlHLc9wofcD6nQ9ZJ7G9b9PgN9iDSNwo3AiRheAf9oEV8gDf%2BIL0vtxmMvq%2BOiXHEfNvXoggNyBNwfSUG0CAvMFDDiAXrNwo9O7oAPv3MMCCZYflNlmDgqxaCcH8LwPwHAtCkFQJwNw1hrDynWJsBmYIeCkAIJoDBqw7IBEkDuDQSQzBmAAJycK4P4NhSQuDSmlNILBHBJC8BYBIDQqQ8EEKIRwXgG1Uh0PwRg0gcBYAwEQCAdYBA0gInIJQNALI6AJCiMOTgqgkhkTmmRSQtxgDICVFIHcZheCOUICQCaeh%2BCCBEGIdgUgZCCEUCodQqjSC6CXjldCaROA8Ewdg3B9DCGcGQgifRcZ6q3CsTYuxDinGLxYWYW4EAPAmPoFqTEXBli8BUVoVYEAkDGLSKYsgFAIAtLaSAYAUg340H7gkDaEBYgpNiBEVoyJ4m8HGcwYgyJkKxG0JgBw0zSDGNDshBgtApkRKwLELwwBq60FoBtbgvAsD8yMOIPZeBXQODwBVM5BD1QrIRNsGhEQmSiIIUiWI6F5keCwCk9MeBJHnNIBVYgsRx6PCucAJERh6GrCoAYYACgqTvByiZPBNDfHCFEOIIJ%2BLQlqBSVE/QhhjCkMsPoPAsQNqQFWKgWMOQzlzSJCmUwlhrBmDkVC80WBGUzR6CsxoLgGDuE8J0PQYQIjDCqKMJexRsgCGmH4ZVmRVUMAWCMRIS87Bir6JMdo0qCgGvqEagQ/Q2i6sVfq2wJr1V6DmLa%2BViwlWrAUBQrYEhEkcBwaQWRvB5E5OsbY%2BxjjnHFNKbgTxVTqG1Noci1YCBMBMCwIkEVTDJCBB3JwwIwiNCSDMJICiGh/BkU4foTg4jSCSMCFwHcZEuBkSSJwgRZF/CSF4QWsiQaUnyMUSAZRyL1FaKaTojJBiOldMqeYtgnBWgsD1NKOaTB3qey4JwncTaXn4CIIKnxsh/FEukCSpQZKIm6DfjEpgcTzn%2BsDcG1JHB0l6IRLcbJuSI2btptu3drDSnlNaZUmEYIzBJvqWoydc6EiGM6SFUDoxIRUu3VwVIAzYrDNGRE2Zky1n4fmYs5ZqyIUbJdlsnZKT9mHOOactZlyqU3IIfge5jgnkpNecgd5ayvn1BSX8gFyIgXbAIaC8FNCoUwqUHC5jNMx2ouxhirFOK1n4tPYE89shSXhIITeylSLuVWFpX84VzLWUCHZZywI9xjO8v5QkQVHx4BestQ85wEBXDOqXnKioeq9AqsaD59IWrGh2qWBa3o1qnVmo1aKjzTQTURaVY6gYIXXWDHdQFmpawNi%2Bty6I59g7OBhryfY1DW6d17tjQekg4HG1QZTaQNNGbRgitEXWhtO7i3Sn8JwoRgQS1lp7QOiJQ7bAjuTaoxpE6kC6MyQhuDxAF3bGXfklgCg9RKj1ABwCEx3F1aPUvDThKtPBPkJevTOgQDBDvQ%2BhJNaA3JPG2k6dWSGqqA21tnbe2%2BwTGA0htpDXAhNZm%2Bo5pQPKlLah6MbbHdNy7c4ZufbBBNxffPXQbDlBcMEKI7smh%2BOSNirWRRwQVHdmscwAco5YgGMQqY9csTFy7lGs4xE7jvGIX8Z%2BbwITkzRMgvNJJ3g0nYXMnk0i8HSn0WYswNi4M6mT1nYkNpkJV3yW3cM9Snlpn6XmcIZZ1UnAdjnns5YPlIaBUTRc0yhL4qvOSpC35hVkXQslByCFoLOQUsOsNYlm1pr8jxf940QPvuXWxeD5H%2BY2X7V%2Bry5QhPRWXtyNKxj24m3tv6j%2B0yAHEA42HoazUupzXWuZsoP6rrIAuE7kCIEfwfCe3SPr9KNtY208KMm6OmbjCQCSH8PmwR0ppFJEkDwrg7CzD9tEYEVPIbOCl9709txHeF9d%2Bg8sVYUKsjOEkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_front.test.hpp)
