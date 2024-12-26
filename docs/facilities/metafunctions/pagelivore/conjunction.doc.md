<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-conjunction">To Index</a></p>

## Description

`Pagelivore::Conjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... && Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Conjunction
 :: template<auto...> class... 
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Conjunction
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

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Conjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (0 < I)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<auto...>
struct Pred_2
{ static constexpr bool value {false}; };

template<auto I>
requires (I % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2>::value);
static_assert(Metafunction<4>::value);
static_assert(! Metafunction<5>::value);
static_assert(! Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert(Conjunction<>::Page<1, 2, 3>::value);
```

## Implementation

We will implement `Conjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Predicates&lt;Variables...&gt;::value
-> true && ... && Predicates&lt;Variables...&gt;::value
-> (...((
       true
    && Predicate<sub>0</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>1</sub>&lt;Variables...&gt;::value)
    && ...
    && Predicate<sub>Last-1</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>Last</sub>&lt;Variables...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Conjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...&&Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEEsEADqgKhE4MHt6%2BASlpGQLhkTEs8YlcwXaYDplCBEzEBNk%2BfkG2mPaOAvWNBMXRcQlJtg1NLbntCmP9EYNlw5UAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsyfRsgkzdDDeHZ5fXJ38n3wu5wuBEwjwMoJM/jcoPBb0wULcTC8RAAdOiodgbsgDAoFOjUcpiJh8KJQQpMcDpsQvA4bh4GNovAxagJgSYAOxWS43Xk3WFPeGI5Fo9EANUaeCYsXoFP82GBfJu1NpBBuRNQRGUTGACJ5fM53IuSqV0zeeGQ2IE00wqmSxBusVQnhuADcxF49caTbzDRACeZAoGiSSLfC5W4JcQpTLMPiMfKQCB3d5MEtOQARKFGpWZ7OKg363kCiEI6Ei1AEqMx2WUos3LzpIzqnWYG5QjPq4ia1Da3WI6vS2UB%2BX5y55/xG4G/f5HQEzm7YVSsJ5tr7T2cA9k/Q5dkkAfQ0n1O0%2B2NwASpgCOsGAp%2BTS23gqPyEG3GsAfIw1Xg77K7wQEEMG4uA0VFgRLIVyxRSsEwVS4VTpEN0EPdkuWVBpHEtNBb1BO0HSdF0U09dsuSoMQlAnCwSKzSdtxBMFBUhKCiHuOsLmJABHLw8GJO8IDudtoWAjR03gggaUQ4lkI0RE7jYw10PNLDrVw%2B1HWdWg3Q9NtDXEz1KOoscgR3W4kP3Lhj32ecz0va9iFve9iKfF832ID8Xm/O9gGJeEHQAoDQPAhjS2FaCRzgi4ELVMyuFQqizUwq0cNtNSCM0oidNI8iEQ5GiqMouiIKYpFoNY0dLk47jeJuCAj0Re5RMivTJIPWLoTk8qgTQhKLSSm08PUwjtJIiw9JyvLDNo8cTP2PdkLMSzdmsi8rxvf8HxuZyANc9yv02u9MFdRgwMuIqyxK0UwM6qK5v3Mw4sUxLsP61KNK01MRrI2gKNy7NJqnU7gsgi7UDKiLKp4uMaoE8wAFYbgWjsOxuESqWa6KpLu2T5O6jDeue1T8LejKRrGgyCumq5dwAWSvJgqGZVkPnXQG4WKisCXY4A5QixsImAG5aYaBmWXeQTOwZJlRcyREzI0Uhbq4BWzPuzqkz7c6ufjK6FSm4yqduAAVOMCDvFmmqU/cmDxBICAgIX6cZ95EVV7Akwy9M9Z65ArZtpp7bpkWmcRSRMXd7TPaNb3faUf2wDAQXA6dmXoVhsPkwjozo%2Bt2O7fjxPheTtloQAWld8PU0jujtjPO5nwYUH7VDMlHzve1UFdPAsHQUhTxc96nLvMQAHcmAATzvExAg0Mnp5Oi3MJj22IElouGERdONcRJWEYV/x0497MOBWWhOFh3g/A4LRSFQTg3GsaxlTWDYdLMfweFIAhNGPlYAGsQFhpIVEGgAAcZgzAAE4IFcFhqAkBXAOQcmkKfDgkheAsAkBoeWl9r63w4LwBQIB5ZfyvsfUgcBYAwEQCANYBBkgonIJQNAjw6AJCiKwLYqgQGBBLoESQNxgDIEtFIVEZheChiINGdAeh%2BCCBEGIdgUgZCCEUCodQpDSC6CVsPYgTBkicB4CfM%2BF9v4304AAeRRPQtUqBnxcJ4XwgRQjgJAIWivVALD6AOnMO/JYvASFaBWBAJAzDkisLIBQCAoTwkgGAFIMwfA6CgmIIQiAsRTGxAiI0MeBjeCZOYMQMe5jYjaBqCQj%2BzCPLmIYLQHJGisCxC8MAJEtBvq5NIFgFghhgDiHqZDWoR1CEaNtDUFEWwP4RFBCg6%2BtA8CxF0YUjwWBTHiTwBg7gvAjrECdEoDMYJumzKMN/FYVADDczFHgTAw9zHJEYO02RwhRDiCUQ81RahTFaP0N0lAD9LD6DmYQyAKxUDJHeEMku0x0AdlMJYawZhcFbKkXGeAKxqhMxcAwdwnhWh6DCHMUo5Q9CpHSO8CYfglbEsKAwAYBLFgdC6HUGYZK9BoveL0JoNKhgVFGH0ZlSszQcvxVyiQqLn6bBFfoYxpAcG8DwTcexvD%2BGCOEa4mquBCAkHbG/LgfjP7HJWK%2BJgWBEgQD/iASQ/hUQQP8EgjQkgzCSGnhoWGgQIGStQeggIXBUSBEqCAiB8DAiAJgda4IMqzH4NsEQvVpCglUOCTQqxDDInRK8ewtgnBGgsFdByEuTBsQGGbFwCBqJvXXwkSQLuMjZDyOedIV5Sh3kaN0AknRejclGI4OfaVpi8GWLoSiG4tj5XcMVQW7pwES1lpqh4TxCQtX%2BDMLqgJZCE2poSIwqJHiwleJQIWuJ0D5Y0FoMk1J6SNH5Oye0y9hTimlIcO0ypX5qm1NMQ0ppLS2kbI6fsowvTr74GJAM5FwzVCjNBO0yZnRTGzPmdkpZWxr6rPWR/LZOzMB7K6X%2B/mxy%2BBnIUBcq5Ny7nfoebWxR9bZBvPUdfFtXyjkwqsH82DgLTU31BZkcFkLoW/IsPC2ViKu7IqBfSspmQMVYpyOSkImLOULG5ZS0l2LcgUoKO8OThL%2BWdDEz0JlynpOssZX0DTdKBXNH0yymYJmKiivWOKnV7ru3hrlQqxxOIJ3FtLcAtV%2BBJELp1f4/VpBDXGsoJ2tBpAMH%2BBLXajksMIGIP8Pax1kglbOc4AQ6NK643wATbQ6xm713EHTVsLNjiWAKFdJaV0nnSzTHEb5yt0ilZkaeRR5R8hG00Z0AEUgbb9EbM7U53tFik02LseVyr1XavhjVO4ud3i37%2BGXbhtd27wmFfW7uqryRkj7hqxA/cdWCD7lUHwxJJ6EhnoyVkwp17btFJKWUx9Hiqk1LqQBzAjTmliC/R/TpBzEO8EA2JwZpiRnIDGZBwQ0GNGwYWWPBDKzowoc2QkdDmGDk4djXhnUBHLnXNuZfD%2BrWFESEoyorrHzev7p%2BbC5jAKUXsbBZwbYkK6dMb4wihISLWOou0%2BiiArg%2BUyfQNZolanMgi8U5kcXWmGW6d5RZ%2BXOmGDstmCUYV/K9NScs8ZoV8mJUKDFYoobJiNEucm1Vt0M3yRzfVX5nxAWY2BINZgI1ww2MoIixgyBqJ/D%2BFhrA1LWCA8ckCCAntFuMtRuIUF/%2BkhYZWoQRyLBIDJDQK4GAswwQUH%2BHN7gmP2XO1iKj4XyNxfSBbPSM4SQQA)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/conjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/conjunction.test.hpp)
