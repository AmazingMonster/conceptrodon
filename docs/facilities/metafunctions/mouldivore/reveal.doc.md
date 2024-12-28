<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-reveal">To Index</a></p>

## Description

`Mouldivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<typename...> class... 
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...> class>
struct Reveal
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...Args>
struct Operation
{ using type = Capsule<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Reveal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Reveal`:

```C++
template<template<typename...> class Operation>
struct Reveal
{
    template<typename...Elements>
    using Mold = Operation<Elements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctwASpgAG6YMTAkwAdisV1ufNusOe8MRBBRaLYWIx2BejAICipvP5XiyRluAFlPOhblCACIkskUgSI6Vg2UKSU4kAgUWoqE8oGcnV2jk/f5/QG/Pa3bCqVjPTCfM7Az1uoNXDlmQIRfFeLDa6FoBhbNJyhVA113NxMNIKLz0QMHQGCiEI6E28WY7GBbDUgi0%2BlZnN50v24NHfUJQ0MAt7ItgoWQsti5gSrGXYjAeXV2v1ggd8mNDnc27KiLAAVi%2BN6xu5%2BiI8eTi3TwIWbWO53hjMHW5CLxpYqYdBM3dzr7A1eq2/3zKP595ue6rcO7NoiEQEKQtxgXsEFQdBkGCAcVIni61ztmqmAtFQXhJh8b5XMWwpDqiI6VhiB5TjWVwfuu6GYdhDg5FujIsmytCIqSnaLtOVxWhqtDoPuE7mlWNbIZeqF3H%2BtCvmGlzUcxL5MbRTBYThlLQmBMEIVpBAHDpiHHq2V5egAKpgEw9oCcyOMgAD6TCEgkBAQBM6BWgo6L2VObhSeBN53g%2BT7mf%2BOLLHaHCrLQnD%2BLwfgcFopCoJwbjWNYtwKOsmwBuYgQ8KQBCaBFqwANYBJIGIaAAHGYZjJMkXD%2BFVlVcJynLSFFHCSLwLASBoGikHFCVJRwvAKCA/UFfFEWkHAsAwIgIDrAQaReOBFAQGgTx0AkUTopwqiVQAbAAtIdki3MAyDILcUgYmYvCPoQJB4G5XAyIIIhiOwUjvfIShqIVpC6G9ADu5JpJwPCRdFsWA8NxKrStc6oFQtwHSdZ0XVdN3lWYtwQB4W30MQ2qRlwyy8JNWirBASCbWk21kOt9OMyAwBSGYfB0KCxBjRAsSA7EEStEikO8ELzDEEixKxNomAOGLpCba8BDEgwtCi1NpBYLEXjAFmtC0GN3C8FgLCGMA4ha/gxDy44rLGwlmCqPLq3bHlYH1IDtB4LE5JSx4WCA3WeA9SbpCssQsQ/jqYIWz7RiFasVAGJOABqeCYCDHFxXl/AfaI4g/fnf0qOoWvA/oFsoKllj6L7Y2QKsqApjkxvHa5uqmJY1hmENkfEC95nwKsdh2zkLgMO4nidHoYQRMMVSjG9xTZAI0x%2BCvmRrwwCwjIkb1jwxAj9FMM8FIf9TjyfkyDAvizL7Yt8b3ocxtHvS8H6PmVbBI0McDFAacNOBoyOqdc6l1rq3TxhAXAT0SY5XJpTJOqwEBsiwIkCAJUQCSECBiZIgQ2oaEkGYSQh0%2Br%2BEOqkDqXVSA9VyhiQ6XBDqVWSM1Q6/hJANQIYdIBWthqjXGvlJOM15q00WojVa5BKAs2JrtNgnBWgsGZJyY6TA8QGFVFwZIGIuAVQevgIgg9Xq/U%2BkXaQJdFBl0BroTmYNsxi3/oAwavB4aSORqjdG4CNEWxujovRGh8aEwZsTUmgQzAU2EVNGmdNUBEwSNIjacSQmjHxBbbRXB%2Bo0GkgkPmAstYSxForQpUsZZywVuHZWso1Ya0BjrPWBsjaKzNvHbYCUbbjwdoDZ2rtQSK09h1BKPs/Yi0Dm0ymg8w55UjtHJQsdzZGATqAaJfBU4KAzlnHOisS5mO%2BhY2QViAYVxAJzTRxha42GGY3LBiVW4CHbp3QIOpu5WEsH3VxA8h7XNHlfY%2BfgICuBfm9eeFR956FXo0IF6Rt6NA/ksS%2BvQb4DChUfRop876gs/q/Z%2B59N5P3mPfMF5M1gbF/sSjqzjgEcFARjc6aStH%2BIqvjOBRiwlIKidTVB6DRg3Jod1MYFVJCcn8MkVqgQSFkK4XwoanBBETREbNBaS0kaJNkTtPaHAlGYxYAoZk11mTaIxCWCYBj4EvT0DswuezfqHPLglXQwR7EQxNk42G/DOAI2WqtW4KM0bat1fqw1xq5wE2SYzMJgRIlU2muItVTMZFhuJiAPV95bIGuSLZYNtlVBnS5jk3mlB8kJRKZrPKJayl20VlUwQNTNbtMwLrfWYgmnhxaYs8Z2s8C2wYl0rWPTkBu36YIL2Wthn%2ByRGM4OkzFYzJjnHRZa4REpyYOnTO2diLbNkLsiQ%2BzBC2psUkKuicXnWHrrEb5tzGjGx2K5GuPc3n9wSMY4eTcejX3%2BYC3Fc8p5wsfhCnIUL/1lEJVihF770Uot%2BWi2%2Bv6D74rPvkPFb8MWL3hd/Ul31XXStcSAnN50dV6tuOmo18ILKwMMSQNlUaUGkDQUwDBlB/60J6rVDEgRAj%2BEalwvq7HOQsOw4lWVtghHRuWNgyQ/h8EtU5H1Sqkh6pcGqmYXhHVAhuplSNDlRV9CcHugJgRWmxMR1yRPSQQA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/reveal.test.hpp)
