<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreEqualTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-equal-to">To Index</a></p>

## Description

`Varybivore::AreEqualTo` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreEqualTo
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreEqualTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 1.0>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreEqualTo` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreEqualTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target) && not (Target < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target) && not (Target < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgAMwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuABVWsBMAQodhgRNiF4HLdLsQcABHLxiBGoYEmAJWK63Wm3UHg96YKEwuGoAB0nIAaq08EwYvQFOjgXTblicQRbspiKgiMomCiRXTKdTLqLRXNHMhbmgGBNMKo0sRbjFUJ5bgA3MReZk09W0lW3CCc9nmABs7ogDFlTp5xD5AswCluLMRyNRyxDZg90du3slECRxBRktDfoDguWWZDAQAIlDVaLKfnEqqlbSGc8mSzYUQXZdgASwYwCELEhi7bSvFkjFKFZgQ4lc1KZXL%2ByyG03Xq2XcLS%2BWQ536WCq5DobWOdzefzBcKl5q8NrdfrDcbTeb5SiAPoWxdq5VUp2z6Oe%2BO%2B7eB4OhpMpyPu91xj6ibhqm0K3OmO5Blmf55gWFKwfOVzAr8/zHICKG3NgqisM8A5fMhqEAhSPxHLcACyqJMFQXgMA4OSfGcwKVhCzLrmy9bJm2HaXN24TAORlHUbRjQUkOeIEtgxKkuS0JcHulwgCAl6sW4%2BLAAos7tnBSEkXcCJBpK%2BFXAeyBXkwChKG0EAUS0Ql0QILJcKQtxcOyGjoopVreJgyzaZcJlmRZ8QEBAYBgAJtk0fZDCOc5ZjOYkHkgF5Nq%2BaWHCrLQnDJLwfgcFopCoJwbjWNYYrrJsA7mIkPCkAQmgZasADWIDJJIbkABxmGYACcPVcMkGgdR1XABAE0hZRwki8CwEgaBopB5QVRUcLwCggAt9X5RlpBwLAMCICA6wEGkcLkJQaBPHQ8SRKw2yqB1boALRupItzAMg2pSOyZi8Jg%2BBEP66B6PwggiGI7BSDIgiKCo6jbaQuhOQA7sQTBpJwPCZdluUNYVnAAPJwqdkqoFQtwPc9r3vZ9LntWYToeFd9DGtVXDLLwW1aKsEBIJdaTXWQFAQPzgsgMAUjxTQtCgsQ60QDEeMxOErQAJ6Y7wyvMMQqsEzE2iYA4GukJd04EwwtDqwjWAxF4wAwrQtDrdwvBYCwhjAOI1t4ASdEWkGeMGobcLbLV4SgpNBW0HgMRozrHhYHjBD%2BrNLukP7xCmkouZgh70dGA1qxUAY6lcngmDIwTaSMMboPCKI4hQ3XsNqHjSP6B7KClZY%2Bgx%2BtkCrKgaSNM7T0TOgUK5qYljWGYy0Z0DAcDz0huNC4DDuJ4nR6KE4TDFUoxOcU2QCNMfhH5kJ8MAsIwJE5dir30kztFvBT3/Uj8CP0bQ3wfd%2B2M/M%2Beg5g/z3osQ%2BqwFAVS2BIbGHAcqLTxitCmj0XpvQ%2Bl9emTpcCEBIFGGqHM6qF1WAgTATAsAJAgM1fwiR2Q9USONDQkgzCSDdPNZIboer6E4NNUgs0arsjdFwN0HUeojTdG1Aa9C3SIIRitNaG0iHbR5gdXmR1iZnWFqLFmt02CcFaCwC0AQnpMB1AYXsXAerslcgVf6uCgYg1kODRu0hm5KFbgjXQ8VUbow1nAhBS1eArSJidOEtwyYoKpm9ZA5j%2BKWOsW5RmqBmbxHwWYQhXMdpqO0fEc6ItkkCxZigWJliuALWlrLeWisEZazVsbWpOs9YGyNmnU2LZzaWzxjbO2DsnbGzdnnbYBV8C%2B0cP7Z2tjVDB1BMbcO9Q8bR1jmrBOQzOYp2NhnLOmAc7uyMPnUAyi%2BAlwUGXCuVca5pzrs4yGrjZAt3hgVLxHcC7TysD3RZ/cqGFWHjkUe49J6vNnvPeIi9PmQI/tFdem98jn2CBvX%2BSwL4lByEApFV8EWHxXtFb%2BL8YXAIhY0HFGL/4gNxdve%2Bz9iWwLWBsGB7NuHwNxnIzgkS0FmI9i5KxNjsEAzwWzDJxDSCkPIaML5k1eH8KsUwgIyQepjUSMw1hkgnKBPxqtWwijMkqPgGo46JM8k5OILo7YBjqYsAUBabUFp4ksQmH9XlDinJXIbjc6G8h3EPJ0EkUgPiMYu38Uy5ahMNGk3JqoM1FqrU2qZBMJJKTWZmESIkAVhzskFMFga9NRTLVpDSDeSxV5bUECvOG1xdBKmUGqQVBpVtao1qaavY2bTBAdKtsMzAtt7ZiD6WnAZezVmkBGY/cZgcpnIBDrMwQ8yEaLLjqrFZSd1lp02ZkbZuc9l8ULkchUJzy6V2rnlWqzqIYSFuTDD1bdvWxK7jPd5fd4CDx%2BQIZ2Oxx43reRYOeQSF54CwGCrFa8ICuFRXC9AVK0WNBA8fRo4GANPwGCBh%2B2LKVgNvsAwBr9YWkvA5A6BkMA2yKDRwCmEbLWWmjaCWNEAcGA3wezTmgrhUUMoHAiVIBersiTckQayr5pJoCCIwjQTOAKM2oKlqkhkh0NGgEeaHVJD9S4F1aMDLEiBuE%2BqrVcDfpCbVQx5RqwM5ZGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_equal_to.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_equal_to.test.hpp)
