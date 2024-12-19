<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Ray`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Ray` accepts a stockroom and returns the stockroom via member `Rail`.

<pre><code>Stockroom -> Stockroom</code></pre>

## Type Signature

```Haskell
Ray ::   template<template<auto...> class...> class...
           -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Ray
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

This function injectively maps a stockroom to a type.
In the following example, We will create an overload set of `fun` using stockrooms `Sto_0` and `Sto_1`.

```C++
template<template<auto...> class...>
struct Sto_0 {};

template<template<auto...> class...>
struct Sto_1 {};

constexpr auto fun(Ray<Sto_0>) { return false; }

constexpr auto fun(Ray<Sto_1>) { return true; }

static_assert(not fun(Ray<Sto_0>{}));

static_assert(fun(Ray<Sto_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Ray<Sto_0>) -> std::false_type;

constexpr auto gun(Ray<Sto_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Ray<Sto_0>>()))::value);

static_assert(decltype(gun(std::declval<Ray<Sto_1>>()))::value);
```

## Implementation

```C++
template<template<template<auto...> class...> class Stockroom>
struct Ray
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOwapK4AMngMmAByPgBGmMQgAMwAHKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Joluu/uHmMenewdMRydMXkQAdK/H2ADUyAYKCq/P7y%2BPwUH2aqGQAGtiKhUCx3iYNABBCbELwOD4hTDAO45BGIkz%2BKxIj4kj5nW73a7nO6XB5PVD/QHfJi/f5CTAARy8jC2CnhxNJXiyRg%2BACUmHQPscACKgoiQ6Gwq7srk8zB/N6JbDHIn4/zSnV4vEAegAVOaLZarcaTZaPgAVbBCe1CD6Wm1Is1W70Wj34pHki5XQM0q6PF6az7M1mRvEotEEOWoAD6GilhIJBsSurxIcpedpbnDDMjQJZGoBWrjBFR6LBya46as%2BsNSNtFo%2BADE8MQJg71Yn3UakWgGBNMKo0sQPsWPlQvAwIJjsY1lURU%2B9lk2PsRMAQNgw52IlDr0wa2yOBOPJ9PZ/PF8ucQI1ymuJvt7v98RDzXuafM8OyItI4yDJuW8QEBADCoIm95LliT4MC%2BG5Vhm%2BrLMsrb%2BkBOKgeBbTUAu8ErriJz1m%2BqHNtKGFYe25qgpgo7oP2fZDhe%2BJmIk4TfF4WBSicTx0IQACe/LYaO15TjO9IfMARGPquZHrho74ALSAhM6AgCAVDHpgyYEMJaS0jml5jrsN7SUQsnyQhiluORakaQQWkgL%2B%2BmGcZtFInMIFgb8EFQTBHxYN8nmYNARGadpoW0AAbmIVwKaRDnKfCWoQBhyzaQl3iYJh2aAb5eB4QFBGxeFkWLtFICxblSV2SljlVhlWU5WI3IFRYHCrLQnAAKy8H4HBaKQqCcG41jWB8CjrJsmBSpxPCkAQmg9asEIgP1kjPBokhcP4iQaP1GhmAAbGdZjJKkfUcJIvAsBIGhBMNo3jRwvAKCAQSrSNPWkHAsAwIgIDrAQaRPOQlBoPsdDxJErDbKoyRnapZ2SLJyDIB8UjPGYvCYPgRDEHgWlcDIggiGI7BSBT8hKGoa2kLo5MAO7EEwaScDwvUDUNTPvQA8k8EOJqgVAfMjqPo5j2O42YHwQB4sP0NO5iJFwyy8L9WirBASAw2kcNkBQECG8bIDAFIZh8HQuy9pQMRMzE4StMJ3O8C7zDEMJgsxNojG/ctMNsIIgsMLQ7t/aQWAxF4wBFrQtBfdwvBYCwhjAOI0f4LuDh4HF6pMxOjFPNsy3hLst2jbQeAxBzPseFgTM1ngj2p6QhfEDEmSYNKeyZ7XRhrasVAGMACgAGp4JgrOC8Zw3LfwlOiOItPL/TKjqNHLP6JnKBTZY%2Bh119kCrKgaSNCnqmaTKpiWNYZhvV3JNYKfmU9IHOQuAw7ieJ0ehQjhGGFUUY5NijZAENMPw4DMiQIYAsEYCRyZ2C/gIfoUx/4FBQfUNBTRJiDGAYsMBtgCHQL0HMNoiDQHINWLNDYWwJC8w4INUgr1eDvUlijNGGNgBYxxjtBWEBcCEBIItDWWsVoj1WAgTATAsAJA/ptSQiRngAE5Ej%2BEkHtMwkgzrPX6mdNR%2BhOD3VII9DWzwzpcDOskNRyQbHbS4P1DRZ02EC04J9b6Ui/p62BvrUGItIam3NqrBGbBOCtBYHFfwqkmBlhFFwNRzwuC7QJkTEgpM9AbypmvaQG9FBbyZroG27NOYe2Yaw9hY1ODC3Bk8D44sZzEGibE%2BJzJEnJNSWmJWsIjaq3EWYSROt/oBNCfEKGZs%2BkWyiTE1SHSrZqK4EEGgtB7ZfQgE7aOXs3Ye1IDsn2fsA4OD2SHRgBBw6RyZrHeOidk57PToPbYo1c5f0LinUaJdkBlz2ZXeoTNa71zdk3Z52sSbt2Wl3HuSh%2B4ZyMEPUAvi%2BDjynjPOeC89k5NXjTfJshCmMx3iAG2Bhh73ysEfQF79z6XxyNfW%2BiRpRksfs/eIr8i5n0/vnZwEBXDkPJkAioSC9AQMaHy9IcDGjUKWDg3o6CyFYJgZyxoGDCGCpoRQ%2BV%2BRFWUNVSA6VdC5qMM1iYlh/No6cNmW0hJwAcZdN2orERxNxGa21tI0gsj5GjA/rdMxFjkl7X8C4/wh1JC6PRuTap70vE/RHgDfxSAwai0meM4g4TthRJliwBQcVsZxSSc8C4Ex0miNftk2QuScV03xdvUauhEikDKVzVOlSzVvVqUEsWEsM0YyzTmj4ebkmFsTL0lW8RxGJGGbGsZ0zVbJpnaMHNaQ0jJgHcmIdYEWno1tms%2BIGytmjQOVHZah6jmB1ObCUOFyI5RxeZgOOCcxD3I7o8%2BFoKY49jeUXaOXyfkdz%2BdXXggKG7CRBS3cFeyoW91hYPcIiLdbIqYBPaes956MExeW7FEhcWCGrcUpIe9SWHxsJS%2BA1Kr6cGNNFJllgn4cJfqTdlH9UFcr8Dy3%2BYqBV6pISKnIYqeNlCIUKmVeCVViuY8qghUqSE6rE5JwT6rjX0Pmkwk1VSPEcGaSwTN2bc35qHQ6jJaslqTt8TIuRCjKDMN9US5JiREj9ROvtZ6dn/C2PceazxthvEjIwqQZR/V1H9WSOdNRkg1GHU0Vwett1Eito4Z5nzzD8bubbR9HxutVhdyyM4SQQA)

## Links

- [source code](../../../conceptrodon/ray.hpp)
