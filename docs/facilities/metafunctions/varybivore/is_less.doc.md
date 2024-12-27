<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsLess`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-less">To Index</a></p>

## Description

`Varybivore::IsLess` accepts a target and a list of variables.
It returns true if the target is less than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &lt; V<sub>0</sub>) && (Target &lt; V<sub>1</sub>) && ... && (Target &lt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsLess
 :: auto...
 -> auto
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQgZlykAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3EwvERrgAVZrATAEUjXGFEAB02IAas08EwYvQFJDsICxsQvA47goQpgFCSLiYAOxWC7XDnXGaOZDXNAMMaYVQpYjXGKoTzXABuYi8mEBnOuLIs1wg2Mx5gAbFqIIjiMiCEqodc8cQCUT6YtFkrmQARSFsgF2h2AwHA0GveVQjGoBFIlFon3q03m4mkwH8wXC0XiyW3Wn0hQAfSlrtZqvVWp1eoNRrcJvxhOJVpt9ohjsB31%2Bh3%2BVeu2FUrEemHeJ0r1b%2Brou3LwyCTTAZ8QIEHjdIZkLcGjRZjRELRklJIBAMu8mEWLu7TR5/cHLQgYDANLHJKhU%2BuAFpktcZ9cIYvl7K1w6OMtaJwArw/BwtKRUJw3NY1hcqs6wtuYEI8KQBCaC%2BywANYgAEkiYhoAAcZhmAAnJhXABGhqFcMyzLSG%2BHCSLwLASBoU5fj%2Bf4cLwCggFO0Hfi%2BpBwLAMCICAqwECksLkJQaAPHQ8SRKwmyqKhmrnpqkjXMAyC8lImJmLwmD4EQZroHo/CCCIYjsFIMiCIoKjqGxpC6MkADuxBMCknA8K%2B76fjBv6cAA8rCAmGqgVDXNJsnyYpynXKpZiqh4on0KK4FcIsvCsVoywQEgIkpGJZAUBAmXZSAwBSDONC0MCxBMRAMQeTE4TNAAns5vC1cwxD1V5MTaJgDhNaQInPAQXkMLQjVWVgMReMA0K0LQTHcLwWAsIYwDiGNeDEN1jhSvSHlCt1sKbJB4TAqRP60HgMQOW1HhYB5BBmpR82kNtxDikotogst51GDByxUAYwAKDieCYLZXkpIwvX6cIojiCZ0PmWoHk2foy0oIBlj6BdTGQMsqApPUc3nmM6CQrapiWNYZh0S9Ok7bjXSbVkLgMO4njtHooThIMFTDMkhSZAIkx%2BPz6SCwwcxDAkoy1EzAi9BM7N5DL3Ty%2BM/Tc/MfO2Orwt6DMLSS7z0vLAoIEbBIrkcB%2BpC0bw9FBTJckKUpKnIVFEC4IQJBKmYEFJVBv3LAgmBMFgCQQPB/gQpimEQsRGiSGYkiatRASaph%2BicORpCURBmKalwmqoZhBGakhuFx5qtsefRjHMYHbFpdx6W8b5gm5flcUSWwnDNCwUrMueTB8gYRgRZhmJcChGlaSQeC6ck0OGXD0gI0oSNWboM72Y5TVWzbdueRwPn8bC1wBY7IUKcgY/ABPU8odFqCxfEvsQmYAcpexrdd/EQl5RfllOKKA75cBwlOUq5VKrVSsi1BqvV4FtQ6l1HqT1%2BqMEGsNUaP5xqTWmrNXqi0vqbFwetJm205o/j2sgA6vVjq1A8udS6DUbqkOSg9XqL03qYA%2BktIw31QBNz4ADIGIMwYQy/JBZesNjJr1kIjSyP5t6ox%2BhTKwmNmE40jr%2BAmWQiYkzJuoqmNN4h020abWWDhmYQFcHrZIXMyhSz0ALeo9jUhi3qEbBYKs5YNF1krEWjNrFq1mJrZxowAm5CCQbDWTjjaWxWGsC2iUs7W3clZB2wVnaj2Wg/aeGhVRe20u/RKyUg6kBDmHYYOjSI5zzpPROzIAiYSIhCJOKdJDJCPnXWwDdv7N3gK3PifkAF/2ID3TY/dQosAUFKXkUpwGYjBPSAgs9vY6T0rIFecjTLyA3konQIA5y7ycvNA%2BGS6LeXbv5QKqgZlzIWUslZYxn6v3in7CEX9focQykA7KYz/kgPmSkFIKZwFJheQQJM9y150GgZQWBP4kGjUgiilBm1eoYMEENEaHk8FTTEIQp6xCBHsNIPgDa1jKG7VUPtYE9DBCMKsswq69U2F3U4U9bh6ReGfQEeEIRqURFMEBsDUG4NIZPRkUZCQ8izIHORsc1RxgMY2C0fAPGeiBBzS2CTdGlNLDU3trTBe9MdF2D8SzNm0TOas28drVxWR3FOpKOEhJviQn%2BL6O4y1XqFZxJ5j4nWPrAn63Vg6k2STQKJNIofWunAgoPPmdKZ5npXmeznh8/25Sm7B1DuHSgVt6mJEnhCCEAQ8JdOouW5kxca6ZM4PXFiFSEKBFjoRZk1FUKSBwlwdCZhq6kQhJc%2B2TbG6pStupBtVyGITtgs9eIGRnCSCAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/is_less.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_less.test.hpp)
