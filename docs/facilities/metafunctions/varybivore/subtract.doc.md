<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Subtract`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-subtract">To Index</a></p>

## Description

`Varybivore::Subtract` accepts a target and a list of variables.
It subtracts all the variables from the target.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Subtract
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Subtract
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Subtract_v
{RESULT};
```

## Examples

We will subtract `1, 2, -2, 2` from `3`.

```C++
static_assert(Subtract<3, 1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `Subtract` using a fold expression.

Note that the initiator is on the left side of the expression. This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub>
</code></pre>-

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct Subtract
{ 
    static constexpr auto value 
    {(Target -...- Variables)}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEgBspAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIsqfRsgkx99yeXN3fnAPOv2uV2uBEwLwM4JMgTcTC8RHuABUWsBMARSPd4UQAHR4gBqLTwTFi9AUMOwoLmxC8DnuQi8sQIxCYDlBJgA7BZ7qD7nz7nNPnhkPc0Aw5phVKliFiEah7gA3MReTA8m78nlciAo4hogj3AC0eJxBvuhOIxNJmAUq05ABEYdz2RyHYErDdQf9AadgV77thVKxXqqfp7vUD2TdBY5kAB9JgKJStCAMpkstmw4L3LiYsyYg15%2B5mCkgEBK7yqmGuu33DS2t0cda0Tj%2BXh%2BDhaUioThuazWAWbbaVsyBHikAiaRvrADWAUkOI0AA4zGYAJyrrj%2BJeLrgcjnSZscSS8FgSDQaUjtzvdji8BQgC8TjuN0hwWAwRAgTYEVII8iUNAXjoBIolYXZVEXJIDSSSR7mAZARSkHEzF4TB8CIC10D0fhBBEMR2CkGRBEUFR1GfUhdBzAB3FlUk4HgmxbNtJy7TgAHkEV/fVUCoe4IKgmC4IQ7N5zMe4IA8ID6BlcxR1WXgny0dYICQQDUmAsgKAgNSNJAYApDzGhaHBYh7wgWIWNiCIWgAT3o3grOYYgbLY2JtHqJ8x0A94CDYhhaDs8isFiLxgDhWhaHvbheCwFhDGAcQgrwYgPLwBVrRYyV6gRXYxwicFD07Wg8FiFlnI8LAWOZPBT2i0h0uIWIMkwO0IXi4qjEndYqAMYAFHxPBMCotjUkYeyiOEURxEInD5CUNQWMo/R4pQPtLH0Er70gdZUFSPoooNOZ0CrUxLGsMxrwazCMu27pemyFwGHcTwOj0MJFgqKo9CKLIBGmPwcx%2Bvphk%2BlY7tSgQBimF78hzOoGkh%2BYQdGaoJkGf69EFVpkeWap1gUQcdgkRiOFbS8WJvPjIOg2D4MQ0TxNwQgSB5EcuHk8cuvWBBMCYLBEggGcQEkQIcVXQJ9w0SQzEkJJz38JJV30Thj1IU9RxxJIakXVcdySfxJE3cWUivXgbzvB9OefZSPxUr9OL/LSdOk0C2E4FoWAVDkDSYUUDCMbNVxxLgF1Q9CSDwLCc1mvDpukWaSIW8jdDzGimDo6KSbJ03WI4DifwRe4eKpgTYOQf3gED4OF3EyT1Ok1nAjMDnFJfO3nYSf9tNQKSxnL%2BKuA3C8jJMsyLPIxzbPGyfnNc9yHHG7zGF8/zAs7YLQvCyLxti9rdnX5LUvSqLOyy5AcvG/KehY4rStsir94Ui1arHBqmqUVq4qMDrQGtvhev6oNYao12xjhjlNAi8dZCJzIp2FOy1OqnSsOtW%2BW1BZdj2tkA6R0TprQsBdM2V1I43XQfDPoj1np5ABiEJ6OMvqAwyL9HIMNqFA2yHQsGZDGjzAxnDHoEN%2BhIw%2BijTGPCWGiMGBwvGGwthE3ZsrUmzFyKU34jTP28Uq4hw0IzcOMk2Yty5qQHmfMxjoMPKrdWQcpYcn8KuPcgRpay0NuTZRnALaPi6q%2BW2SBvxcS7h3Ygrtdge0EiwBQCoRQKkHjiKE1oCBh2ZphbCshY6QImjAxaIBghpwzgxBR2cKbsQdtxXiqhQnhMidE2Jcxa493rgkRugQDF/3bnUjS/i2nSTLMgVIqRYxRNXLGapBBYxlPjnQUelBx6dhnoFMcsy54eUXj3HyfkAosQ3mFMQ286q72/o/Ug%2BAUoNGPplVQ2VwSX0ENfcit8yo2QflVZ%2B4037NU/u1CIv8lL/yYH1AaQ0RpjTquA/CEgoHEXmrAnQWSEHGDwRtWIaCdqYIEFFPYR1VpnUsAQrsRCsBIvBgjPwEBXC8JoegKR31GF9DJWw0owjcaY34USqGbRxF8PuojSRDL6Fo2hlQiR2MeUrHxoTAiWclHXk4HxcpETFRVM%2BHEnRiTG7swUoY4x/NKAkwsSANcOJAiBH8FuQ255DUciSIuFxUrby2Etq3VYQtJD%2BDFruDk55FySA3FwZcZgUiHkCJKs2birZKRJiha1wbbUOvWA1TIzhJBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/subtract/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/subtract.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/subtract.test.hpp)
