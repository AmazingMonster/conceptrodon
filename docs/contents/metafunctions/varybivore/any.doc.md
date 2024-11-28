<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Any`

## Description

`Varybivore::Any` accepts a list of variables.
It returns true if any of the variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> bool(V<sub>0</sub>) || bool(V<sub>1</sub>) || ... || bool(V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
Any :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Any
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Any_v
{RESULT};
```

## Examples

```C++
static_assert(Any<1, 2, 3>::value);
static_assert(Any<0, 2, 3>::value);
static_assert(Any<nullptr, 2, 3>::value);
static_assert(! Any<nullptr, 0, 0>::value);
```

## Implementation

We will implement `Any` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Variables
-> false || ... || Variables
-> (...((false || Variable<sub>0</sub>) || Variable<sub>1</sub>) || ...) || Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Any
{
    static constexpr bool value
    { (...||(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool Any_v
{ (...||(static_cast<bool>(Variables))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXFciXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMUR0bEJtg1NLTntCmP9oYNlw5UAlLaoXsTI7BwEmCxJBjsmAMxuTF5EAHRXAGqNeExR9ArH2CYaAILTxF4OANTvDAAnm93iYAOxWD6/aG/aZMRzIX5oBjTTCqJLEX5RVCeX4ANzEXkwIJhv3BFl%2BECuF3BblpEDhCIA%2BqJpsc3NjPC8ILdiPdHpgFEthWSwQARY6Q0HiyUgkE7PYHYknM6XG53B5PF4g5Go9GYzm0f5Apl4uUQynU2n0xl4ZAsphsk6G7m8/lPYVLUUSo5SkEAegAVMGQ6H/QGQwAVbBCSMh8MfIOh5MJ0EfW32x1KJoQAHAk5cUi/MxFo4vEAgAneTBLWXphrMrOxAi5oHsjRFku/MtHbAVqtE2u%2BkEZplNnN59kMLy0WhJAhkYul8uVwk1uufBt2scKbMtsBgY35tzT2fzxcd34aFcD9e%2BjgrWicACsvD8HC0pFQnDplmssLWDZMDJMwjh4UgCE0B8VgAaxAZ8zAuMEzEkAAOVDnw0eIEI0AA2VCjn0ThJF4FgJA0Dt30/b8OF4BQQA7SCPwfUg4FgGBEBANYCCSc5yEoNA9joWJwlYLZVFQ3CAFpcMkX5gGQREpAuMxeEwfAiD5dA9H4QQRDEdgpBkQRFBUdRmNIXRCwAd2IJgkk4HhHxfN8oK/TgAHlzl4ghflQKhfgk6TZPkxTfmUsxKQ8IT6ExcwwKWXgmK0FYICQQSkmEsgKAgDKspAYApBLGhaB2Yh6IgKI3KiUJGkBRzeBq5hiEBDyom0GomPAwS2EEDyGFoeqLKwKIvGAU5Z3o7heCwFhDGAcRhrwYhOrwPFBTctEanOLZwNCHYnws2g8CiOyWo8LA3IXPAyOm0h1uIbElDFXZ5uOowoJWKgDGABRrjwTBrI8pJGAa4zhFEcQjN0%2BQlDUNyrP0eaUGsax9BO%2BjIBWVB5wyKapOmdBjjFUw/0sMxqIerSNqxjougyFwGHcTxWj0YI5lKco9HydIBAmPxCx57oBk5xY6dWgRenGFmckLapaklmYRaGCpRj6fm9DhJplYWCoVgUQDNgkZyOFfUgqN4GjAskmS5IUpTJBUylcEIEgQISpLPpWBBMCYLA4ggWD/COC54iOMFJA0SQUNwijn1wxJDpI0gyLAi5cK4fD4lQzPn0kLhnzD3Dzbcmi6IYiDPtYji0q47y%2BJyvLYtEthOEaFg8TBKSmCRAwjHC%2BILi4C5P3U12tJ02R9Kh6QYdM%2BGLN0EtbPshqTbNi33I4LyePOPyAvbzvu97%2BaB6HkeotQGLYndsxEsr5jUvSq/Mti/jcpf/LD675A%2B8K%2BIuAdhKmVCqVULJNTqmDCBLU2odQcGDHqjACD9UGm5EaY0Jq0CmuBWab0tifnwCtWo60pqj1UNtHYYN9qdDcsdU6dULr4KSnyW64EHpPUwC9OaRh3qgEfnwH6f0AZAxBu%2BcCMNp6GVnrIee5lPxLyRh9UmVhLDoyiJjQOX5cYCHxoTYmyjrAU0tlTPAWANH606BLPwEBXAa0LOzEoKtuapF5pkGWAtkguOFhzJxctLEKx6DMOx4sAlS1mI43WmsgnuKiX0HWXMuD60NoZderkLJW2/sfX%2Bp9Kjnw0M7DSbt4qJM9o/b2vt/aUBNsnVOg8o5gkLmCMERxo6SFkoWTeZdbAV2SixNinFuI%2BXfk3ESYk27EBYCFFgCg8SIjxLkpU0w1KFInoWCRkMpHg1kQjEAhEV4OWmqkku6TPL118v5X47cpkzLmQs%2BEgpfIQGiq/G%2B8Ujj316U/FAn836Nx%2BcMWZSQkimkqEyRZBAxwTNknwOgIDKBgM/NAoa4EkWwM6ggq%2BvVkEDSGgQzAo1xpiCwWDXBPCmGkEIatEhm1yHIB2lQwQNCjonTOoCRhV0WFg3YakThr0eGhD4SlARTBfr/UBsDUGd11kGQkNIkycM5E6F2Yo4wqNVF0PMVo7oU1/SExRmTCwRivwmLMfACx9NnA2KZsEhx8wEmeIKBkYJQsMjxLFvLboYTgkerqErHxkS5bROyB4rW4S7WLCSesI2iSiKmzSdRTglyoVyWmbM/EdydjTAKePd2JSH4pXKX7YYmik6kRAGYQeRwjjPkwvnCiVawT4WOQm2i3TGJe1IHBSQYIVINK4FIeI9Sw5cDBLGo48bLacFKQW2Nqlm2TtbZ8lYD00jOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/any.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/any.test.hpp)
