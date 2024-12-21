<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AddTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-add-to">To Index</a></p>

## Description

`Varybivore::AddTo` accepts a variable and returns a function. When invoked, the function sums up the variable and the arguments.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub> + Target</code></pre>

## Type Signature

```Haskell
AddTo
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AddTo
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will add `1, 2` to `3`.

```C++
template<auto...Variables>
using Metafunction = AddTo<3>::Page<Variables...>;

static_assert(Metafunction<1, 2>::value == 6);
```

## Implementation

We will implement `AddTo` using a fold expression.

We will place the initiator on the right side of the expression to conform to other similar functions in the library.
This means we are doing a right-fold.

<pre><code>   Variables + ... + Init
-> Variable<sub>0</sub> + (... + (Variable<sub>Last-1</sub> + (Variable<sub>Last</sub> + Init))...)
</code></pre>

In our case, left-fold and right-fold produce the same result since `+` is commutative.

Here's the entire implementation:

```C++
template<auto Init>
struct AddTo
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Variables+...+Init)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v 
    {(Variables+...+Init)}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwEmCwJBpsmAMxuTF5EANQAkgyEB9gmGgCCE8ReDqf36OgAKqh39yYA7FYHqcQadNttdpgDkcTqgAHQIgBqdTwTAi9AUN1%2BoNOTxeBFOymIqCIyiYwChwNBAIsp2xONBEyYjmQpzQDAmmFUCWIp2OZwAbmIvJg6VSGXTARBkcRUejMJjLAi4dZLoR5gCACIHWn0kFanW/PVgrY7ZlQw78%2BEI%2B7AYiYLaMAiY/a3cWnLwpIyE8mig6awnE0m%2B6G2%2B2OwQKZVY/ZAv7u8FmvaW2HKmVyjFY91MllsgSc7m8q0%2BikAfQFYvuOJp0pRaMzSoRqquBA1/21scrBtjRoeAHoAFRD4cjvu/QdDz7YISfYdj/sjxcD%2Bfx%2B6JyHQq1puvyl1u%2B6e4LAU4AWUwtSoXgYVQEdP2AfeXx%2Bh32NxAIDJFOh6frCujrsNB5fhzPBkFLJgFCUeoIDPC8rxvBhoRaU4zDfEAhW8P1739U4ADYNVjDhFloTgAFZeD8DgtFIVBODcaxrFxZZVj9Mx9h4UgCE0IjFgAaxAUizDhf4zEkWJYlIjQAE5BI0XDYn2fROEkXgWAkDQNFISjqNojheAUEBNK4qiiNIOBYBgRAQGWAgEhOchKDQbY6GiUJWHWVRYlwgBaXDJFOYBkFZKQ4TMXhMHwIhZXQPR%2BEEEQxHYKQZEERQVHUEzSF0FoAHdiCYBJOB4YiyIo7iaM4AB5E47IJVAqFOTyfL8gKgtOEKzFOCAPGc%2BheXMdj5l4YytEWCAkCchIXLICgIEm6aQGAKQzD4OhNmIAyIAicqImCOoAE8it4XbmGIfbKoibRKmMjinLYQRKoYWhDsyrAIi8YAjloWgDO4XgsBYQxgHEV68HtKoBQVcquUqE51g44JNhIzLaDwCJ8rOjwsHKghZTUv7SEh4gImSTBNS2IHUaMbjFioAxgAURE8EwHLKoSRgjpS4RRHEZK4vkJQ1HK7L9CBlAGMsfQ0YMyBFlQBIOl%2B7yJnQf1TEsawzB0onoqh2XWnaNIXAYdxPCafwTd6IoSmyZJUgEUZmkSO2Oit/pSgN67qkmR29AqBCunqN3Zg9pkRjNsYhm6YOba4RYFGYtYJBKjhyK08rdMarzfP8wLgskUKutwQgSDpNi4%2BGmnFgQTAmCwGIID4kBJH2OEpP2f5JA0SRRNwjTSNwqSlI4FTSDU9i4Vwrh5Kk2Jp9IyQuFI9vcPTzLdP0wzOJpszLPG6yavs2b5r6ty2E4OoWAFf5vKYNkDG9LgpLhLg4WoiKS%2Bi2LZAS3npH5tKQtMq6BWnlAqR0U5p20rwXS1VbInFOPVPkxAr43zvsgB%2Bx4n4vzfl1HqU0%2Bpl32GYIa28TJjQmqgXq0QHJzSoQQgYl9r7eQwUDJ%2BXBNI0FoOtTa21MonQOpzARZ0LpXQcJzO6TpHrPXKm9D6X0fqcwBpTdY1F8Dg0cJDX679VCw02JzRGbRyqo3RgdLGqjhp405kTEmShyaAyMFTUA5C%2BD00ZszVm7NKIcX5r/JK/9ZCAIytREBotqbqysJLExMtG40QVmkJWKs1YSwsFrGBOs8BYBifHNoXtnAQFcL7FogRpjWzmM7XIaQikVPtgwGO5T/YdEDg0COTtGne2jqU92fsfatJ6Z0wo3S45LBWEnYZyMoEZ04Mg1Bt975A3as/V%2BGgi6RVLgNCuZDRrV1rvXSgKdR7j2ft3f4y9/j/H2D3SQfkWjQIqnpWwW8RqmXMlZGytVaEn1cu5C%2BKCWosAUAKVkApsGQgmOFNZX8Wi%2BJ5v4rmQThYgEUmAwqf1IFlXXlVQ%2BdUGqX3%2BYC4FoLzQTDwfQ6aRD9ikOeRQlAZK%2BqfLpQMIFCQEjlifqWMFBBwJ/P/mtaIvCdp7TOkIoV51LrXQkVQ%2B6BBpEvTUZgd6n0xCKIJsoxxFjSDqK9lo6GujkBwwMYIIxKM0YY32uYnGViCY2NJvYymR4d503JO4lmbMOYExhYlCQATUqC2CToJFYTjApKlhEbJcTFacD7CrcWGtLBpJohkrJ8AcmG3yYUvpxTLZdJDrbSpDtM01Ndjm2OnsA69MyG03J5aBkzFLWHFplb%2BlBxLXMeOickrorXjpaZeL/IAqBacEFz9OWrM/kQzZ1Kdl1wGLE5GhyQBmGfvsfYpFJKLw0iu/48lu0wM4JvIyVdSD8UkP8UKpyuBSCkic9uXB/jD32BintDyp3DzCru%2B5ldyGLCJikZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/add_to.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/add_to.test.hpp)
