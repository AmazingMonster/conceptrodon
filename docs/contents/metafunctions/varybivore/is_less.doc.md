<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsLess`

## Description

`Varybivore::IsLess` accepts a target and a list of variables.
It returns true if the target is less than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &lt; V<sub>0</sub>) && (Target &lt; V<sub>1</sub>) && ... && (Target &lt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsLess :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct IsLess
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsLess_v
{RESULT};
```

## Examples

```C++
static_assert(IsLess<0, 2, 3, 4>::value);
static_assert(! IsLess<0, -1, 2, 3>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsLess
{
    static constexpr bool value
    { (...&&(Target < Variables)) };
};

template<auto Target, auto...Variables>
constexpr bool IsLess_v
{ (...&&(Target < Variables)) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evnppGY4CYRHRLHEJXABstpj2RQxCBEzEBDk%2BfoG19VlNLQQlUbHxSbbNre15XGP9g2UVElUAlLaoXsTI7BwEmCwpBjsmAMxuTF5EANQAKi3AmASkF2dEAHRvAGoteEwx9ArH2BMGgAggoCMQvA4LgBJBQhTAKf4gkyJKwgi4Yi5gpiOZAXNAMMGYVQpYgXGKoTwXABuYi8mCBwMxFxRFguEDeL3MVW5EBuxDuBBZJwun2I31%2BCKWSxZiQAIsc0cCUQqjkrGTs9gcGSdnqhrrd7o89ZyxRK/gDGQSiSSyRSqbD4YiAPrUxms9mc7m8/mC4VuUVfH5/aWy1XqkEAegAVLG4/HI4yY7GrtghFc44mo/Gc9Gs8qQdjcc6mIj4gQII6Ef8ThpHmZHkdHpIASAQLTvJglorGUW8MgS2XWhAwGAYXDq8c3HWLgBaaYXBsXI6t9t0ruKjgrWicAK8PwcLSkVCcNzWaxYtYbTAssxHHikAiaLcrADWIACZheiTMkgAHH%2BAQaAAnJ%2BGhVH%2BTY7hwki8CwEgaHWB5HieHC8AoIB1k%2Bh5bqQcCwDAiAgGsBApOc5CUGgex0PEkSsFsqh/lUs5VJIFzAMgeJSC8Zi8Jg%2BBEOK6B6PwggiGI7BSDIgiKCo6g4aQujTAA7sQTApJwPDbru%2B7PsenAAPLnGRQqoFQFyMcxrHsZxFzcWY7IeNR9BkuY95LLw2FaCsEBIFRKQ0WQFAQP5gUgMAUgNjQtA7MQGEQDEekxOELQAJ6abwyXMMQqUGTE2iYA4GWkFRbCCAZDC0OlClYDEXjAKctC0Bh3C8FgLCGMA4g1XgxCFY41IInpxKFecWwPuEOzQUetB4DEak5R4WB6eCeDwa1pCDcQFJKHKuydbNRjPisVAGMACjvHgmDKQZKSMMVonCKI4hSY9slqHpSn6J1KDnpY%2BhzRhkArKgKQNC1s5gugxxyqYljWGYKFbUJQ3A90/VZC4DDuJ4HR6KE4RDOUIzTAUmQCJMfik%2Bk5MMHMwyVOjDi9OMbS41MTMNH0rT08TjPYhM7NUzMPOE/MJMrAoV6bBI2kcHupDIbwqEWUxLFsRxXGSDx7K4IQJC3u5nnHSsCCYEwWAJBAb7%2BEcLzAUciSSBoki/lUiEBFUwH6JwsGkPB94vFU1R/sBf7VAEkhcAEDs1Er%2BlobYmGPsdeGEb5xHGeRwWhS5dFsJwLQsNSiSzkw%2BIGEYdnAS8XAvEe/H60JImyOJL3SG9SgfQpugNqp6kZXLCvx6hRmkecFxmU8xDF6X5fIJXwDV7X9eOagznxIbZgeSnOE%2BX568BS5FEhYfYVFyXs4L51XDAVwdbRbF8WJQpWVpcVb85XlBVFRtpWMAQCqVU9K1Xqo1ZqxV2oHS2EefAfVmaDRag3VQo0djFUmnUPSs15ppSWjAzy4p1oPi2jtTAe0OpGEOqAPefAzoXSujdO6B4HyPTbpJDush3rySPL3b6R04ZWH%2BtgoG1tjxgyyBDKGMMBEIyRvEFGIjJZ1Axs4CArhKb42xrzBY1NChZA0bo2m2iSacxZv0AxpiBDcwGGLBmegBZs1yMLBxxjKiS2lpJIeukFIqwvnPCunVl51w0LrASBs3JcB3l5F8pAzYWxGKI6CfsA41xdokGOiREhHFdpIVi0wR6cHQsnaJPl05IBIiZE%2BudaL0ULjPayLAFDUjxNSW%2BLxtRgj4mE5u0xWHPXYdJeQXduE6BAE2fuGlWpeMVnpUeWdTLmSLg0ppLS2kdKFBAJyR9N5uSOFE1OGdqlBUomfFy7ZkApBSK6W%2Bzp1klnqR3OgT9KAvyPJ/aqD53nf36sVf%2B5VKrVVgZgOqDUxAQI2lAyh%2BDSBwIxog4aKDkBjXQYITBClsELVSnglahDiokPSGQ/alDwjUO8rQpg51LrXVuvdDafSJISA4TJYZn0xl8OMH9Gwwj4Ag3EQIFqkYoa/XhpYRGytkZ4CwIoyxfg1HYwsQTUodjDENAsWTBorj7HKOZlY1mFi7AqMaKzTV0wHH6uNbYvmstVjrBlpEn28tvEoU4NPFgyzmk0jWTiBEGy9aCUNpE42e9Tbm0tpQOWySQBmBrkcI4AQgJR0QrGxIEEZk%2BMKUnLCJtSDvkkIkHi6SuBSGAmkh2XBkjQSOE65WGaSly14mm51ic62bXiBkZwkggA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_less.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_less.test.hpp)
