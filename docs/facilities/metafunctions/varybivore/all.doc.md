<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::All`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-all">To Index</a></p>

## Description

`Varybivore::All` accepts a list of variables. It returns true if all variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (bool)V<sub>0</sub> && (bool)V<sub>1</sub> && ... && (bool)V<sub>n</sub></code></pre>

## Type Signature

```Haskell
All
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct All
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto All_v
{RESULT};
```

## Examples

```C++
static_assert(All<1, 2, 3>::value);
static_assert(! All<0, 2, 3>::value);
static_assert(! All<nullptr, 2, 3>::value);
```

## Implementation

We will implement `All` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Variables
-> true && ... && Variables
-> (...((true && Variable<sub>0</sub>) && Variable<sub>1</sub>) && ...) && Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<auto...Variables>
struct All
{
    static constexpr bool value
    { (...&&(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool All_v
{ (...&&(static_cast<bool>(Variables))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmAMykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMcTcTC8RAAdNCAGr1PBMCL0BQg7C/IbELwOc7HWi0X4mADsVhO5zJ5wmjmQ5zQDCGmFUiWI5wiqE85wAbmIvJhfuTzkSLOcINDIeYAGwSiCUvDIAD6oiGILcrM8qIgcOICKRmAUs31AsJABEQSSfsbTQSTv9AY9eaDwVDYfDEcjUb9afTGczVbQcXi5RyCcThaKJVKZfLFQRlb71Zrtcj9bNDSa4mbfu9PrtvlnzthVKxbphngdM9mvlbjpG5UwFEoGhBcfjQa1zmZSOc4qiQCAud5MLNLSca3WGwQIGAwP6W24NJ2O12e33uYPh9W6lTa/XohOpzPlQwvHjEgQyO3O924the/2eUP078OPNaJwAKy8PwcLSkVCcNzWNYFKLMsJbmHEPCkAQmjPvMADWIBvpIkIaAAHGYZgAJyYVwb5oahXCEoS0ivhwki8CwEgaPOX4/n%2BHC8AoIDztB37PqQcCwDAiAgIsBCJBC5CUGgNx0NEoSsKsqioeKAC04qSOcwDINSUiQmYvCYPgRBaugej8IIIhiOwUgyIIigqOobGkLorQAO7EEwiScDwL7vp%2BMG/pwADyEICQQ5yoFQ5zSXJClKSp5xqWYwoeKJ9DMuBXCzLwrFaPMEBICJiRiWQFAQNluUgMAUgdjQtD/MQTEQBEnkRME9QAJ4ubw9XMMQjXeRE2iYA4LWkCJ9wEN5DC0M11lYBEXjAGCeJMdwvBYCwhjAOIE14MQvWOByuqeQyvUQqskHBP8pE/rQeARI5HUeFgnlnnglELaQO3EKyShGgCK0XUYMHzFQBjAAoMJ4JgdneYkjD9QZwiiOIpkwxZaiebZ%2BgrSggGWPol1MZA8yoKe6TzbJQzoCCRqmJY1hmHRr26bteNtFt6QuAw7ieM0/hs1MfQxK0uRpAIowtEkKSCwwPMlP04yVMzAidCMHNjEzDgdMM3TBL0Ut87Y6vC3oEwNJLMzJQsSwrBIbkcB%2BpC0bw9EhTJ8mKcpqnITFEC4IQJACvEyWpX98wIJgTBYDEEDwSAkhxJCmFxMRGiSGYkjitRb7iph%2BicORpCURBkLilw4qoZhBHikhuFx%2BKtuefRjHMVBf0cdxmW8X5gn5YVCUSWwnD1CwHKErJTA0gYRhRZhkJcChmnaSQeB6a0MNGfD0iI0oyPWboHYOU5LVWzbdteRwvn8RCgXBaFzujytE9TyhsWoPF0S%2B3EZgpY3bEZVlT85QlQkFV/kVZAY8So4XnOVSq1VarWTak1fqcCOpdR6n1Z6g1GDDVGuNH8k1pqzVoPNSCS1vqrBwRtZmO15o/n2sgQ6/UTqVE8hdK6TVbqkNSlqJ6kFXrvUwJ9ZaRgfqgC/nwQGwNQbg0hl%2BSCy84YmTXrIJGVkfzbzRr9SmVgsbMNxhHX8hMBDE1JuTDR1NabRHpjo%2BYdg5Z%2BAgK4fWrRAia2mNLUWeR0gOLceLY2rjrGq3lnrJWIs/HVAVhrIovMDaBKyME9WPi%2BZWJAhbU2pFD6104I7MKikQG3y4JPaeGhhRex0q/f2n90pBxDmHSgVsc550nonQkb5MJETiEnFOkhWhHzrrYBuaV2KcR4nxfyACu7iUkn3YgLBwosAUByakHI8mQiBLqAgs9va6X0rIFe8izLyA3sonQIAEi72cgtA%2BHlrL0VPv5C%2BIUZlzIWUslZQxH7P0SvEOIH9%2BnfxQEA/%2Bnd/n9HmYkRIgY8lyheQQOUqgFJ8DoFAygMCfyIPGpBVFyCtr9XQYIEaY1PK4JmmIAh/ViGCPYaQfAm1VaUL2qoA6/x6GCEYdZZh11GpsPupw/qPCUh8K%2BoI4Iwj0qiKYEDEGYMIZQ2erI4yEgFHmQOSjY5ajjCYxsNo%2BA%2BN9F0k4GsUmGMqaWBpvbOmC8Ga6JCSzOxbNPFOIidrHIYtqieIFtUeJBtZb%2BJqNEzmMt2gBMmM4yJ4xfXK0NuErWJtEnmxMhcmuVyMmwsUrM%2BZnJnl2leZ7OeHyILfMDqQYOod%2Bi6NInU2Ik84hxDfHhTp1Eq2EmLgmuinB64sQLQhSQb5Y6EUJNRVCkgcJcHQmYaupE4iXJbQxcpsEs4cA0s2%2B2raZ36hetEVIzhJBAA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/all.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/all.test.hpp)
