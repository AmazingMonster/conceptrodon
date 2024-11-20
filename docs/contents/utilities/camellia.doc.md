<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Camellia`

## Description

`Camellia` accepts a `Calm` and returns the `Calm` via member `Calm`.

<pre><code>Calm -> Calm</code></pre>

## Type Signature

```Haskell
Camellia ::   template<template<template<template<template<auto...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<auto...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
struct Camellia
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT;
};
```

## Examples

This function injectively maps a `Calm` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Camellia<Op_0>) { return false; }

constexpr auto fun(Camellia<Op_1>) { return true; }

static_assert(not fun(Camellia<Op_0>{}));

static_assert(fun(Camellia<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Camellia<Op_0>) -> std::false_type;

constexpr auto gun(Camellia<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Camellia<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Camellia<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
struct Camellia
{
    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    using Calm = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9dMXkQAdICTtgANTIAwKBSA/7AsEQqFApKg8FMSHQ2EotGI5HwkEAeXSCXuuWBJg0AEFJsQvA4QW5WA1aHgmGTySYAOxWCkgnkgp7fT5vF7897XEXCr6i06/AHYuGohEwpHyrFKnEK9HKzGK8nEYAKUnc3lebJGOliFggk4AEXxhOIxIE111%2Bs12BOXLZ7OtHtZrIA9AAqYMh0Nh/0B0MggAq2CE0aEINDEYpQbD6ZDKbZFPFH1ezzzubFkolQrzMtQbpViox8Kr2vrdexrKpNIIdoA%2BhorZyOT6kp7WUXBQXi2Wx6ORwL6X9K3KG/Om2rq42Nc2Ka3aQSO1we1Zvb6KZGQyCAGJ4YiTGOYK/Jv0UtAMSaYVTpYggisgqheBgQelsWgmRZU5tw0YEVj3EFiEwAhNgYL8xCUD0ex9I8HwEZ9X3fT9v1/f9GWZa5ty4cDIOg2DiHgghqQ%2BCwUPvSlWkcZAOwVBICAgBhUHbXC/wZQDCJA9Iu1JXtvRWFZD2zRjiRYtj2moH8%2BIAoCiOEkikQ5fdrQkqTj2DEEhEwR90GvW9MwY8wkgicEvCwK1Tj%2BOhCAAT0NaTH0wt8P1nEFgCU/CBOAtxQNIgBaWFJnQEAQCoRDMA7AgXMJPT0KfPYsJ8og/IC/jVKEndwsighopAaivASpKUoHBj5mY1jIXYzjuJBLBwSqzBoCUqKYra2gADcxGuQL8pC4SwM0pEIAklYYsG7xMEkmq0Jk%2Br5I4vqOq638epAPr5uGvLBLGwrJuwaaJLmsQKqWiwODWWhOAAVl4PwOC0UhUE4NxrGsEEFA2LZMCtMwkh4UgCE0e61gAaxAJ7JH%2BDRJC4dkkg0J6NDMfx/DMFI0kejhJF4FgJA0DRSDej6vo4XgFBACnIfe%2B7SDgWAYEQEANgIdI/nISg0AOOgEiiBlOFUFJ/DC/xJD85BkBBKR/jMXhMHwIhiDwaKuBkQQRDEdgpF1%2BQlDUKHSF0HWAHcHXSTgeAe57XvNmm8T%2BXn21QKgQQlqWZblhWlbMEE/1QIX6HfKyuBWXgma0NYICQQX0mFsgKAgZPU5AYApDMPg6D2S9KFic3YgiNoXPt3gy%2BYYgXLxWJtGMpnwcFthBDxBhaEr5nSCwWIvGAelAPp7heCwFhDGAcRe/waCHDwfqb3Nl9jL%2BHZwYiPZCY%2BplYgdOuPCwc3qLwUmx9IJfiFiLJMGtfYp6ZIwobWKgDH1AA1PBMCtglGCr42%2BtxBG34IIRQKh1C90tvoKeKBfqWH0HgWI9NIBrFQOkJoo8wpRRtKYSw1gzDUyvprLAKDpq9GbrkFwDB3CeC6HoMIEQRjVDGDrEoOQBAzD8GwrIHCGCLFGIkHWdhKECAGNMOhhRhENFEc0KYQwmFLFYbYeRXC9DzHaAIlhQi1gA02NsCQjsOAvUpi7TgPtJbS1lsAeWitEbBwgLgQgJAQZgxjhDF%2BawECYCYFgRI5C4aSCSP8QISR2SSGRmYSQ/hyZPR6ITYmpBSZg3%2BP4Lg/gUiBBSOkhGXAnqhP8KY3uNM6YMw8czBOHNE5c3dnzdOmcI6izYJwNoLB%2BrsjCkweUZouCBH%2BFwJGqt1YkC1noUBwhRDAOkOM8BZsoEgDzjbJgdsx5GJMVTXgrtame29q09pnTunAEVn0gZ3ZQ7hwSK4sw7i44s2qQ0hI/MM5hxThHEAeyOkoiML0rgFMaC0ELvTCAJde41wrgAsFdcG5NwcAAtujACCd27ubfug9h60FHuDCej8dgfTnpQpeo8Pqr2QOvABW8Gjmz3gfFyR9cWx01ufcGV8b5KHvpPIwT9QAVL4O/BQX8f5/zeuDcZQDDbTNkLMyBH1dB5wMM/PBVgEF7zIWgjBuQsE4KSNaRVBCiEJBIcvVBFCF7OAgK4NROtGGVEEXodhTRLUZF4U0LRyxpF9DEaoyR3CTVNHEQom12j1FeoKD6jRAbmFut0YDAx0d9BOyKdTcxHyDlfKOb0/pSMQ5OI1q46OsdPGkG8b4sY5CEkk2SH05G7J8nsjRpIKJMsdYbM%2BpwUpjMX6syqUgbmHsnkPOIE0nYrT/YsAUP1BW/UM2XEmEM5xJCxmyDFRICVYDTbSp0MkUgSyVkO3jcY52xTOBux5n8EEXsPzEBYKO8dk7p3vCvOc15lyrJJBuZ2%2B5LzU79q/W8id6RhJTsCB2GdBBWJXplvnAFCQgUgo%2BpCnu4MEPQubnCsO7dEVdx7nizAA8h5iAxQA7FnL6V9wvAS5evcSVkovhSnevBqUVzpSfRlACWW33ZY/CI3L468qYJ/b%2Bv9CTCt4KKyZ4rjZSvNroJIMCFXwJsCq%2BAarMGcH9D1XVlhCGbOIVrI15CRGmr8OamhjrrWRuUfa3IjqrPlEUba91sj/WOsM36%2BRrrlHhpc%2B5%2BzQa416KBoY/d6yzEcEvde2WY6J0giA/8UD2bhmR1Bvm8p8cvE%2BL8ZQIxiTSZmD6UkJIT1MYo3JgV9kGTE2bLbbYMptyJKkECU9EJT0UjY0CJIQIaMwlcFk4TJIh6k201S9DfdKtKutqG3VtYV9sjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/camellia.hpp)
