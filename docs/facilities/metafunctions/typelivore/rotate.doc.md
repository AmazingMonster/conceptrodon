<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Rotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-rotate">To Index</a></p>

## Description

`Typelivore::Rotate` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function relocates elements of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper
   &lt;
       E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>,
       E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Result ****/
using Result = Rotate<int, int*, int**, int**>
::Page<3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<typename...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    -> Operation<BackTargets..., FrontTargets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJiNBk6jXa61ncnXSlCADueAAbvULbarsyjWaVXCuTzWH70VcJkqHLcna73SYklYkvdVXbvWzffisgAvTAAfQIADoCwApEWXMNeCNRt20dMEdAgEARLCqbNKACOyvF%2BMLBbzZMCIeBcZBtxHCpZqY5cOHo5nKfZfrcAcYQZ7aNukKYCk%2BAHlnsQzTlSNOZyPqbS8Kou2iewAxYiyAAqrWAmAICiPVxPo6XvMwPYsTDIAA1k%2BxAvm%2Bx6ygOM5zI4yDrgIEyYKoaTEAKQq3Hg6DIrQEDLJBOw7LcUSoMyCoIJgtzFNkAjrgghgvrcqBUDCABsGh3o%2Bz6vgoq7sQKDDoGxGgAcBoHgbxJjsZBAC0a67gkB4CPiokgdxb49vynGCOJPGrv2SbqgmhnAhSdwAEqkb6HpMuO86ctyy5sD22DGowEEGaGirlpKlktByRlqpcs52WmcKZjmkqXCw6yCCWMHeRG1KkagyhMC%2BkGxkFX4jnOYWLqFk6Lo5v76dg64GFuPaXMANIsu5CjxTlXhZEYtyWUwQmwvKWCQkukEzhAA05ZW9Q1nWIAsEwQE5o2yEtpg7avAu0WxQQfbQTlM71nlZFYTh%2BI1XVJoaQW/KufVgi8QWaJ4cNI74YE2WjrGiZPXaIU%2BkVgpENVtWYJdHmbSOLURMAVLpZR3VSilaUZXCR0Ayd129gZ71GW9QVWjajLYwctzYKorBspR3x4zjQIYmCEJQlDcJilsaRA3aeoKfu5pk16hULj%2BK43Z5paJZKbNKQwJnk5GXhpMUmDoOZHxeLQkqc5coNtUIUsy3LCtK7K8oi40%2BIRAQBz8sbZuCHsFsm3sfZY2Z%2BPywoivK7jVxq%2BDTsu3r7VWUV5uYZb1um4HNslvWcMLoE4cgB16D4gbOR2yzlIPh8ruWl5B7INmm5KG0EBEvWChBrnjVwl7Sv8hr0uZLLlfrf2j0WBwqy0Jw/i8H4HBaKQqCcG41jWLcCjrJsUNgjwpAEJorerEBASSHmGgABxmGYACcG9cP4q8r1wSRJNI7ccJIvAsBIGgaKQ3e9/3HC8AoIDXzPPet6QcCwDAiAgOsBBpAicglA0CsjoAkKIQZOCqBXqxGSrFJC3GAMgeCUg8xmF4LLQgJAsJ6H4IIEQYh2BSBkIIRQKh1Bv1ILoVIjp9xpE4DwNuHcu6zz7pwbcCIAGSmYrcaBsD4GIOQbcVBZhbgQA8KA%2BgaFMRcGWLwV%2BWhVgQCQCAtIYCyAUAgKo9RIBgBSDMHwOgzJiBPwgLEVhsQIitGRAw3gljmDEGRNuWI2hMAOFsaQEBJ1twMFoDYyhWBYheGAG4MQtAn7cF4FgKaRhxABLwDSBw0YIm92Qm4hE2wp7G3qKwpEsR9yOI8FgVhio8AX0iaQN0xBYh10eDE4ASIjCz1WFQAwwAFAADV3iOgUt3KeeDhCiHEMQgZZC1CsOofoBiKAh6WH0HgWIT9ICrFQEzHIESZJEm6qYSw1gzB3yqcQLCHx4CrDsG4xoLhBLTD8KkMIERhhVFGKkaijQbl6FeTkBYIxEjjHqBcvokx2ieE6Hoc5SSBD9DaN8p5vzbBAveeMIFMKliyLWBsLYEgmEcE7jfVh99eEwLgQgpBKCl6iIgLgLB0jJ5yOns01YFFOqjDwqQBekhAh5g3oEI%2BGhJBmEkOxDQ/hWIb30JwM%2BpAL6BC4HmViXBWIrw3vvVi/hJA725axPFlD76P2fvSt%2BSjv7KN/pwwBmjtFSIgWwTgrQWAuiSDJJgFUGLCI3nmWVqT8BECOXWVIAyCHDOkKMpQ4zKG6AMbQpg9DInYtxbfXg98OH/wRExFifDiUuralwd1nqxESLUVImEYIzB0oUe/E1lqEhAK0agSRowNxGBzVwa%2BNAlYJFMeYyh9jrEeJ7Y45xrj3EVK8e5HxfjWGBOCaE2g4SPHRIYnE3u%2BBEmODdCkjBqh0nMg8dkk%2Bvc8kFOREU7YvdSnlKnlUmpSg6mLrBs0vgbTOndN6R4gNQyiHBtkGMihvcI1TKaTsqwcy8lLNZasxoGytlyiA3sg5CRfUnOWT0AFzgICuERSEQSKLnnpEyDRXIIKCgvPw40HDcLwWNChcC/ItyUMQqaMih5ixcNzCmERujbHBjMZ%2BVi9F48%2BMn3jfizghL%2BEIMbeDHNHrl5iKpT64tMqy0MtIEyrAiRWUn0ldK91fKkj%2BA3ofQI/LBXqu1XfTgeqX4Ps/j/P%2BXCa1VuINa7YdqBEsAUC6eCLppPzgmBg712C/UkMGYQiQX7SGht/ToEAwQo0xsYeKnFLCdXsLNdw9N7nPPed876CY%2Ba62FoSIpwIynDUfxUYV9RjmqtSJAF56W2YfMb2zH5gg2ZVDwMMe2kxlAu2937f4qeg3B0XI8aOwQ47/HLswEEkJYSIlTwXbE09USEkAvXawtJyAMm7sEDkyhh7rEnpKUci9vAr21JZHepp5XWnpWfZgHpPI32yEDZ%2BkLP6JmxYA8YWZNhQOnL7msxCnAdhF1g5YfZibDnHLA2c/5DGrnuA43oe5FReMkZKDkTDnyyg8dhWCxHVGEWo7%2Bb0SFTGMeE6RQMTDXHyN8dHhiohcaUsWY4LwrLXnbjNbzG1uTgWaVKfkSptTLLsXaZAJvPMgRAj%2BF3uqq%2BcukiKvM4myzth9XluWPPEAkh/BcoPkkK%2BK9JDby4GvMwWqT6BHZxrh%2BBrFHYvQerthjuderCqVkZwkggA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/rotate.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/rotate.test.hpp)
