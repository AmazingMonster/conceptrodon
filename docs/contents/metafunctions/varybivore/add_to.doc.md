<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AddTo`

## Description

`Varybivore::AddTo` accepts a variable and returns a function. When invoked, the function sums up the variable and the arguments.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub></code></pre>

## Type Signature

```Haskell
AddTo :: auto... -> auto... -> auto
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
using Metafunction = AddTo<3>::Page<Variables...>

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIArKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwEmCwJBpsmAMxuTF5EANQAkgyEpKfHRAB0jwBqdXhMEfQKB9gmGgCCE2IXgcpz%2B6HQvz%2BJgA7BZTpDTojThMmI5kKc0AwJphVAliLcTqhTgA3MReTDw/5I%2BGw04QS6EayPe7WF7EN4fTAKeY0gAiBzhkJh/P2Vn%2BkM2212mAOR0JFyuBBud1QzLZHM%2B30hmOxuPxKtB4IA%2BsTKVDafTFUzHqzXu9PjzhQKzZCAPQAKk9Xu9rrdXoAKtghP6vb7/h7vZGw1D/ii0UamAolPUIGCIYcWqczDd9t8QCBSd4KQcRbzTgA2eYCjiLWicWK8PwcLSkVCcNzWazI5arYtmfY8UgETQ1xYAaxAsTM92hZkkAA557ENABOKcacvz/b6TiSXgsCQaDSkJsttscXgKEDH4fNmukOCwGCIEDLAgJE7kShobZ0aKhVh1lUedywAWnLSRTmAZB0Ske4zF4TB8CIdl0D0fhBBEMR2CkGRBEUFR1DvUhdBaAB3YgmASTgeFretGxHVtOAAeROD8CFOVAqFOYCwIgqCYNOOCzDpDxf3ofFzAHeZeFvLRFggJAfwSP8yAoCBlNUkBgCkbMaFoTZiCvCAIkYiJgjqABPGjeHM5hiEs5iIm0Spb0HH82EEZiGFoaziKwCIvGAI5aFoK9uF4LAWEMYBxH8vBiFcvBiS5RicUqE51kHYJNjrYjaDwCJKIcjwsEYgh2QPCLSBS4gImSTBeS2GKCqMEdFioAxgAUJ48EwMjmISRgbLw4RRHEXCMPkJQ1EY0j9BilBO0sfRCqvSBFlQBIOnC0CJnTXlTEsawzDPWrUNSjbWnaNIXAYdxPCafx7t6IoSmyZJUgEUZmkST6Ole/pSmupKBC6EZHrGEGqjByZAdmYGUQhzJfqRqZCiBiRFgUHs1ixncOAbE9GPPHiQPAyDoNgyR4LpXBCBIeF%2By4GSh3axYEEwJgsBiCBxxASR9nuFd9mhSQNEkOdyyPWJyxXAm91IA8B3ucsuE3Fd53V2JJDKEXy2J4jz0va82bvBTn0U182M/dTNIkgC2E4OoWGJaFQKYDEDCMISV3uLh7hbJCGdQ9DZCwibpCmgjZuI3RswoqibLowmGKNlibY4rjbmIV33c95BveAX3/cD0TUHE6Imf2MxWbk%2B8rft6Ivw0iuVIkkAXbd0DC5irgVy4Y99MM4zTOIuyrJGieHKclyHBGjzGAIbzfMYgKgpCsKRqilr1hbfBEqqFLwqD1QMs2EacraRiCqKqzSr32TKpG2r6qUJroqMVrQHNvgup6vqA0hpNkHFNCOOEo6yBjkRFs8cFptSOlYFat91p81bNtNIu19olkQSdM60QLqoOxm0UGfgICuB%2Bs9dA8N3otByF9dIkNfr0IBtMN6cxoYdHBg0JhegKgw06HDNhmNxiTEoaI7oNC5jY1xjhFORNTy8FJl3fOXsYolwDhoOmyFGZSRZrJdmpBObcwGGgvKitlZ%2BwltCWIK5oTQn2JLSQEEWiKKYheWwpt64W3gFbN87EW5N2II7dYLt%2BIsAUMSdExJ%2B73GlBMRCOjQ4tDAeNCBo1oFzRANuRO1EIryLTmeDO74TicW4mEyCESokklifEjiEAxLtyrlJfYdd2oPiUm3VSgSukdyiQkBIJp%2B5GjqQmXOEE%2BB0BHpQMeLZp5%2BUHPM2erkF4V08svHyfl96YECsFMQW9qo7y/o/UgB8krHzSmfZAmVL6CGvvlQqxVLIP3Ks/aqr8GofxasEH%2B8k/5MG6r1fqg1hrVVSdhCQkD8IzRgTobJ8DjDLRsCg%2BAm0MECHCq6faS1jqWFOko86eAsBEM4bdch91xGkECMIhGH1chpEpSwtIUjEYkIEdwyl/CuFCIxrSiRyMnr8vRjMWhMiVh4xZgTBRJNOA5xYOEyJ0Tamoi5PU%2BmKFq76LNvJDmXMeaUBThYkAZg/b7H2LEZcusjxmuhJuQ2RSPFXhvIYickhoTwRsVwKQK5rEiy4NCAm%2BxClKM4AY82KcEL2pDR47xixaopGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/add_to.hpp)
- [unit test](../../../../tests/unit/varybivore/add_to.test.hpp)
