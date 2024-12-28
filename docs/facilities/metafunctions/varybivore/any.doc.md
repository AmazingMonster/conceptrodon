<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Any`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-any">To Index</a></p>

## Description

`Varybivore::Any` accepts a list of variables.
It returns true if any of the variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (bool)V<sub>0</sub> || (bool)V<sub>1</sub> || ... || (bool)V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Any
 :: auto...
 -> auto
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBm0gAOqAqETgwe3r56icmOAkEh4SxRMXG2mPa5DEIETMQE6T5%2BXGUVqdW1BPlhkdGx0go1dQ2ZzQMdXYXFfQCUtqhexMjsHAD0AFQbm1vbO5srJhoAguubANQAkizx9GyCTJWnW/tHJ7tvu8%2BHB4cEmFcGvxMAGY3EwvEQAHRQgBqtTwTAi9AUwOw3wGxC8DlOhwYAE9viYAOxWI6nMmnMaOZCnNAMAaYVTxYinCKoTynABuYi8mG%2B5NORIspwgUIhRLc4oglLwyAA%2BqIBsC3KzPCiILDiPDEZgFNM9QLCQARYEkr5Gk0Eo6/f73XkgsGQmFwhFIlHfWn0xnMlW0bF42UcgnE4Wi8WS6VyhUEJU%2BtUarVIvXTA3GoGm76vd7bT6Z07YVSsa6YR57DNZj6Ww4R2VMBRKOoQHH4kHNU5mUinIEokAgLneTDTC1Hau1%2BsERt4pUaDvtzvd3vcgdDqs1Kk1uvRcdNpUMLy0WjxAhkNsdrtA7A9vs8wdptGrmXrscQMBgP3Nty7/eH4/T04aedXkut5HBwsy0JwACsvB%2BBwWikKgnASpY1gUvMizFuYQI8KQBCaKBswANYgBBkgQhoAAcZhmAAnNRXAQRR5FcIShLSOBHCSLwLASBo04wXBCEcLwCggNOuGwaBpBwLAMCICA8wEPE4LkJQaBXHQ0ShKwyyqORABsAC0emSKcwDINSUgQmYvCYPgRCaugej8IIIhiOwUgyIIigqOoEmkLozQAO7EEw8ScDwYGQdBeHwZwADy4JKQQpyoFQpy6YZxmmeZpyWWYwoeOp9DMphXDTLw4laLMEBIGp8QaWQFAQHVDUgMAUjtjQtC/MQIkQBEMURMEtS4uFvBDcwxC4nFETaJgDhjaQam3AQcUMLQo1%2BVgEReMAoL7iJ3C8FgLCGMA4hbXgxDzY4HI6jFDLzeCyzYcEvzsXBtB4BEIVTR4WAxUeeDcUdpB3cQrJKIafxnV9Rh4bMVAGMACjQngmCBXF8SMItznCKI4geXj3lqDFAX6GdKDWNY%2BjfSJkCzKgh6pIdBkDOgwKGqYyGWGYAngw590My0N2pC4DDuJ4jT%2BBLEw9DEzTZCkAjDE0pBK5UctFL0ozlKLAjtEMUsjCLDhtIMnTBN02sK7YFuq3oYx1FrUxlXMCxLBIkUcFBpD8bwgnpfpRkmWZFmkflEC4IQJACmYWHlThCOzAgmBMFgMQQIRICSECELUUCrEaJIcR6bxEF6dR%2BicJxpDcVhEJ6VwenkdRTF6SR9EF3pfsxYJwmiUnEnVbJNXyYlylNS1xVaWwnC1CwHKEgZTA0gYRi5dREJcGRNl2SQeCOc0eOuYT0jE0opN%2Bbo7bBaFY3e77/uxRwCWKeCKVpRlIdr2dm/b2RAqqAirRDjkCMwidKqSTHtPaIKlmrAPqsVFA692p0WnF1HqfUBp%2BQmiNRaeCpozTmgtUGy1GCrXWptOC21dr7VoIdbCJ1YbLBoVdUWd1DpwUesgZ6i03rlBil9H6I1/qsIqpqEG2FwaQ0wNDU6Rg4agGHnwZGqN0aY2xjBbCJ8CbuXPrIEmvk4I3wpvDbmVhLC0wiPTLO8FmYCFZuzTmFjrB8wDgLQ%2BQs7F2H1n4CArgHbNECFbSYOt1ZJGVmkY2asNapBduE3xZsDb2xiY7PWySqgWwSbbJ29Q0mjGyaE%2BWXt3boVKexJ%2BfdOBB0yiZZAqD/47w0MKaO9kwFlQqsnUgqd069DsexWu9ct7F0JBBaiLEgQl0kMZZoz9%2B62EHlAke8Ax4KSSvA2BxBZ7LAXllFgCgOTUg5FwLeAIdQED3jHByTlZCn30Z5eQl9jE6BAECUgd8wpHUftFPygk35JU/ulfZhzjmnIhOcgYQCQElXjkCSBCMpK1UQQ1TZKLkFHPiPEAMpzZSQoILKVQxk%2BB0CwZQHBcFCGbWwlS4hN1FrkMEGtDaMVaF7TEAwxazDFHiNIPga6ZtOEPVUE9X4/DBCCL8sI36uIxGA0kYtGRSQ5Ew0UcEZRVVVFMBRmjDGWMcag10W5CQBivLPLJm8sxxhqZWOEbYxmDi6ScBWOzKmPMLDuPgp4rA9rTaVHFpLDIasQkFBKYrSJlQgkRJyPE4pNt0mtBSR0KNSTKiG0tqG%2BNhTk0FLtuMONrtZgKDQp7N2lTfkCRqUSkyByjmcnBfi1p%2B9YUJy6cPFOacM6UG9kM2IW8gRAgggxSQXBeIDsJC3XufzOADzEt0oikgIL52YoSXi5FJB0S4JRMwPd2JAgrQHGdQ8qre2slOytQlj34TBtEZIzhJBAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/any/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/any.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/any.test.hpp)
