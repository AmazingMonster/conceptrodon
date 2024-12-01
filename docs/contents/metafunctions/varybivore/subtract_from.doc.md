<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SubtractFrom`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-modifications">To Index</a></p>

## Description

`Varybivore::SubtractFrom` accepts a variable and returns a function. When invoked, the function subtracts all arguments from the variable.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
SubtractFrom :: auto... -> auto... -> auto
```

## Structure

```C++
template<auto>
struct SubtractFrom
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

We will subtract `1, 2, -2, 2` from `3`.

```C++
template<auto...Variables>
using Metafunction = SubtractFrom<3>::Page<Variables...>;

static_assert(Metafunction<1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `SubtractFrom` using a fold expression.

We will place the initiator on the left side of the expression.
This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub></code></pre>

Here's the entire implementation:

```C++
template<auto Target>
struct SubtractFrom
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Target -...- Variables)}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {(Target -...- Variables)};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCBmAGykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG5MXkQA1AAqzcCYBEfYJhoAgmPEXg7nQl7RBMRMDgAYsRUCwns8TAB2Kwvc5w87bXb7TBHE5nVAAOixADVmngmNF6AoHuD4ec3h8COdlCCiMomLdSfCoRZzkyyXCZo5kOc0AwxphVCliOdThcAG5iLyYNmwjlwlkQa7EW5UgC0WIxavOuOI%2BMJmAUiyhABEjqz2WzIWbDjDnmTLYi9kwDscxZisc9gMRMDtGARiYdHnK4V4MkZqQyZUcTdTaah6Yzjl6fX7BApNSTbeDHTtna60URNbr9USSSHyU1ubyBAKhSL3ZHbgB9cWWxXK1XnDVY7UlglE43W8054fZl7ggD0ACpZ3P55Op3PLtghJc54uXjP5zvNxCXk7kaj3cW8QPDeXnmGwsBzgBZO5MKheBgOLJsw6x76/f5AkFg45DgeEAQETFFjn7A0MyxLM7XBLk8GQZsmAUJQWggB8mmfV96lRLhSHOMwCLVIjCOAkBJW8aNPxjc4NGNW0OGWWhOH8Xg/A4LRSFQTg3GsaxyVWdZozMQ4eFIAhNCY5YAGsAjMDFITMSQAA4VP8DQAE5/DMDREhUw59E4SReBYCQNA0UgOK4niOF4BQQEsyTOKY0g4FgGBEBAVYCBSM5yEoNBdjoOIIlYTZVBUxI1USSRzmAZAeSkDEzF4TB8CIPV0D0fhBBEMR2CkGRBEUFR1Bc0hdHwgB3f4Uk4HhmNY9ipO4zgAHkzj8qlUCoc5Iui2L4sS85krMc4IA8YL6BFcwxMWXhnK0ZYICQIKUhCsgKAgdbNpAYApCImhaG2YgHIgaJWuiMJmgATwa3hruYYhbva6JtEwBwHtIIK2EEdqGFoe6KqwaIvGAE5aFoBzuF4LAWEMYBxBBvAfTfcVDVawVPrOTZxLCbYWIq2g8Gif4Xo8LBWr%2BPAzNh0gMeIaJ0kwE0dkRkmjCk5YqAMYAFGxPBMGq9qUkYb7cuEURxCKyXSrUVqqv0RGUH4yx9FJhzIGWVAUnqGG1TGdAY1MSxrF03hUEZrLMe1rpPvqFwGHcTx2j0EIwkGCphnwwpMgESY/F99J/YYOYhnifC7AdnpxlaV28ij2oY4EXoWnD73I9sOPA70GZ089%2BYfeWBQhI2CQmo4NirNa2z%2BqimK4oSpLJBSibcEIEg2VErgFok7nlgQTAmCweIIFkkBJEODFNMOSFJA0SRlMSCz/ESTSjI4EzSDMsSMUSLh9M0lTD8CLh/Fn5JrMtzh7Mc/uXJWzzVu8rr/O23aZrCthOGaFhxUhGqJgvIDARi4JpDEXAMRcXSp3LKOVZD5RltIOWSgFYVV0ERWqTB6qw0rtXa%2BbUOCdV8mcc4vVRTEH/oA4ByBQG3nAZA6BE0pobRmt3Q4Zg%2B5LVci/T%2BcQAo7VBGw4Yf8AFqjoYjcBXBLLHVOudS6FUnp3W%2Bsol6b0PpfXpr9f0AMgatVBuDSG0Nvrww5psLi%2BA0aOAxjDGBqgcbbG%2BgTWorUSZkzupTCxi09R03EozZmSg2YIyMJzUAj8%2BB8wFkLEWYsOLiUlkgwqKDZDy3KlxTBysuamysOrdxWtx7cT1lkA2RsTZqwsBbbi1s8BYAKSXZOb5nAQFcLnfCHsygRz0H7eobTUgh3qBnBYSduipxzgnIO9smkNDjkMn22c%2Bh9Pzv0QuXTe4rDWOXdZRMCG104JQ6hQCQGI1GhAqBGh24ZS7nNXui0B6kCHiPYYhSibb13hAxekIL6QkhIcJekhYr4UIbZO%2BTluZuWfkgHy3VBH8OIN/TYf8hosAUOKHk4pGHIjGGlK58D8KJOlsk4q8g0HpJ0CAQy2DcGNU3rsiqtkSHdXIX1JFcUUVovOBiiBWKqSTWEZtDhhxuHgr4fymasKxXDDRSkFIrZwHNh5chKhsU%2BB0HkZQRRXE1HA3EtqjRDtvo6P%2BoDYGljMBgwhmIEx9MzGhO8aQKxMdbFYwccgXGzjBCuOJqTcmt0vHU18d9AJLNgkcxvOC3mDJonC1FuLemBKCoSBSSVUlisKVZOMBUjW0R6lFP1pwScRtVZm0sFUq2cQba5ujtMp2LtciTI6V7YZ/SihZD6T0rIcys7VvqGneO9a86NN7bM1Zmc87jIHVHEdnSx3rNLpswq%2BCWr0v2ay847L0WYpdIaXlHdMocNuQ/Zag9h6j0oJXN5CQIGHEOP4DSkgZEaBvZCfSNcV12VsPfHhiwJ6SEhClL5XApCaU%2BbPLgkJN6HGXTZW%2BR7pKb1Sm%2BmDH7v3LEZhkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/subtract_from.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/subtract_from.test.hpp)
