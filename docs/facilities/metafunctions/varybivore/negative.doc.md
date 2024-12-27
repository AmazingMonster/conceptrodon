<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Negative`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-negative">To Index</a></p>

## Description

`Varybivore::Negative` accepts a variable and applies unary `-` to it.

<pre><code>V -> -V</code></pre>

## Type Signature

```Haskell
Negative
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Negative
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Negative_v
{RESULT};
```

## Examples

```C++
static_assert(Negative<1>::value == -1);
static_assert(Negative<-1.0>::value == 1.0);
```

## Implementation

```C++
template<auto I>
struct Negative
{ 
    static constexpr auto value 
    {-I}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iI8YdgQbNiF4HHdIphgB88AA3TAgkyJCx3EF3Sl3WZ45B3NAMWaYVQpYh3eGI/FiLyYcnXKnk0kAWgeJIAIjCycTEhLoVZriC/gCTkClXdsKpWC9ed9FcrAcTrjTHMgAPpMBRKFoQbG4xyEmFuLjIkAgLneXkw2Viu5CrgrSWopom82W%2BIEG04vEO2F%2BgB0Ghdbu5nuh3ruXATAblHDWtE4AV4fg4WlIqE4bms1mpGy2nrM0J4pAImlzawA1iAApIEwAOMxmACcg64AQ0vd71US0nzHEkvBYEg0GlIxdL5Y4vAUIBXLZLudIcFgMEQIA2BBSCPIlDQzzo8UirB2ql7ADYha/JHdgMg6VI42YvCYPgRDEHg6B6PwggiGI7BSDIgiKCo6j7qQuhcKQADuxBMCknA8HmBZFq2ZacAA8gil4EHcqBUHcL7vp%2B36/hmPZmHcEAeHe9BsuYjYrLwe5aGsEBILeKT3mQFAQOJkkgMAUhmHwdBgsQ24QDEJExOEzQAJ74bw2nMMQulkTE2h1HuTa3m8BBkQwtD6ahWAxF4wBwrQtDbtwvBYCwhjAOIzl4MQlkEpg3mlsydQIjsTbhGCs6lrQeAxDhJkeFgJEEGBi4%2BaQhLEDE6SYGK4IBSlRitmsVAGMACgAGp4JgmFkSkjAGQhwiiOI8FQfIShqCR6H6AFKBVpY%2BipdukBrKgKS9N5QqzOgXqmJY1hmOuhVgVgM0QGstT1M4ECuFMfgYaECzlJUeiFJkAjnXd6QPQwQw3csXQ9A0cxPRhR29P0LTvSMVTjAMf3g8D12gxIh21tscP6ERq4kRu9Fvh%2BX4/n%2BbEcbghAkOSDb%2BoJ1VrAgmBMFgCQHaQnaSNCcaDtC04aJIZiSK%2By4BK%2Bg7I3OC4gI2cavlwr69oOk6vt2o4s6%2BqOoRuW47s21WHieolnpRV7SbJPGPmwnDNCw%2BKJEKTD0gYRgZoOcaZlFIEkOBkGyDBvXSP1SFDahuhKdhuEGYRHCFor67kTr1G0RjjFfsg1vALb9sJhxXESTxxPQmYAlq/uIliag3HxNeMmF%2BnozxwFXAjiuNC0Kp6maahRl6Z1LcmWZFkOJ1NmMHZDlOaWLluR5XmdX5FU7EPIVhYSkVAaoMVgp1CXdCRKVpXpmVT4JuWdYVxVKGV/lGJVoB53wdWNc1rXtcWTb9e7cGe7I3soaWfujVV61WJNG/7XNBaWQlorTWhNCwW1eCoB2uBCK8BDrdDCidM6nh2h6CumUWGGF7q9EhjgrIIMlhgwBj9CGqC8j/UQcdPocxCG3X%2Br9chF0obzEwUQpGCgEZwWDqHNcUDOAxyxlbAKScHb4ydrxEmOchJtlIJTamow6aznnKQRc0I7bs0SAEQciREjQg5lzSQGE%2BGkU3LYVWMiRKayQOeKiJd9YPifMbYgLAmIsAUPiOk%2BJq5xkhBFAgQEJEuwwo/Hqz8upv2GsLLCOE8I%2BR4cRJWEcLwIhonRVQbiPFeJ8X42Yqcy6SUztCaR6stYOKkjeApPE3TIBSCkU03jBymlyQQU0GTPYqXiI3LSOkTJt16aZcylke6F1svZRyJFh7uTEGPfKE9T471IPgUK9Q54kWisgWKK9BBr1QhvdKult7ZT3vlA%2BJVj4VXCOfYSl8mD1Sai1NqHV8qhNghIF%2BiFBrvx0NEhO40Np/2mvAssQCBDeV2Ctf5v8IHbXiLtOBs0vpIL8KdBg7gmHoLRXQz6%2BDHoYuwS9Xo2LiFUMBow3IzCSECCBqwxY9CWGQxpNDNh9D4abERv6AWvC0YCPaXcdxni7iNN8R8fx4jCaSP4mTPOFMqY00oMHFRi4hxxmhNCAIY4jHLjVYkCWYd%2BFmO3Lucm9N8jMynMuXskgRxcH7GYBWs5oSJPDmYyxwdAL6tMdK4SaxCoZGcJIIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/negative.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/negative.test.hpp)
