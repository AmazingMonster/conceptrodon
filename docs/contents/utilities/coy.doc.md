<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Coy`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Coy` accepts a `Cool` and returns the `Cool` via member `Cool`.

<pre><code>Cool -> Cool</code></pre>

## Type Signature

```Haskell
Coy ::   template<template<template<template<template<typename...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<typename...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT;
};
```

## Examples

This function injectively maps a `Cool` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Coy<Op_0>) { return false; }

constexpr auto fun(Coy<Op_1>) { return true; }

static_assert(not fun(Coy<Op_0>{}));

static_assert(fun(Coy<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Coy<Op_0>) -> std::false_type;

constexpr auto gun(Coy<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Coy<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Coy<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Cool = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9cEAJ7pjFYmAAdKCTtgANTIAwKBSg4HgqEwuFgpKQ6FMWHwxEYrGo9HIiEAeQBxHuuXBJg0AEFJsQvA4IR4xDQFAgqdSTAB2Kw0iH8iFPb6fN4vIXvH5fCUi54fM7/QFsbFopGYlEIlW49U45HKglq%2BHU4jABSUvkCrzZIxM1CeCEnAAixNJ5IE1yNJr1J15nK5Du9HI5AHoAFRh8MRyNB4MRiEAFWwQjjQghEejNNDkaz4fTnJp4rFUsLorlBdLRdLCuYSvxqrxGv19Z1BtrWq9NLpDIIzoA%2Bhp7Tzuf6kj6OWXJSWJ7Kp8LXtPHlWgXq69rNbrW%2BuGyv27SCPTGSSe1wB1Y/QGaTHwxCAGJ4YiTeOYB9pwM0tAMSaYVTpYgQpheIgISoLwGAgZlaFZdlTkPDRwRWE8IWITACE2BggLEJRvQHf0LzfARP2/X9/0A4DQPAyDrkPLg4IQpCUOINC9y8D4LGw19d3JZAezVBICAgBhUG7UiwNQFk8DZSj0j7SlBz9FYVnPPMOMcLiePaagQJEsSJOgqTqLRblTwdeTFMvMMISETB33QR9nxzdjzCSCJoS8LB7VOAC6EIX4zSU98CJ/P8ANQCFgE08jxKgtwYJogBaRFJnQEAQCoDDMB7P4AVMvCPz2QigsAsKyNEiDIsko84oSggkpAJj0sylj2PmFTuNhXj%2BMEiEsGhBroE0xLku62gADcxGuCKdOiqTYIMtEIHklZktG7xMAUkcmtaFq1L4obeqKiABpAIblvGkqKN0irZuweb5KWsRmLWiwODWWhOAAVl4PwOC0UhUE4NxrGsCEFA2LZMHtMwkh4UgCE0Z61gAaxAN7JGBDRJC4Lkkg0N6NDMfx/DMFI0lejhJF4FgJA0DRSC%2Bn6/o4XgFBAGnYe%2B57SDgWAYEQEANgIdIAPISg0AOOgEiiIFOFUFJ/Fi/xJFC5BkAhKRgTMXhMHwIhiDwJKuBkQQRDEdgpEN%2BQlDUOHSF0A2AHcyXSTgeBe97PuthmiQAwXu1QKgIRluWFaVlW1bMCERLF%2Bhf0crgVl4NmtDWCAkFF9JxbICgIDTjOQGAKQzD4Og9nvShYmt2IIjaX5nd4SvmGIX4iVibQrLZ6HRbYQQiQYWga/Z0gsFiLxgDcMRaGZ7heCwFhDGAcQB/wJCHDwYan2tr8rIAnZoYiPZSZ%2B2g8FiMlG48LBrb3PBKan0g1%2BIWIskwB19jno%2BjDhtYqAME0ADU8EwHbEkjBa7m2NuIM2/BBCKBUOoAett9BzxQIDSw%2Bhj7M0gGsVA6QmiT1iolR0phLDWDMPTe%2BussAYPmr0NuuQXAMHcJ4LoegwgRBGNUMYBsSg5AEDMPwXCsg8IYIsUYiQDZ2FoQIAY0wmGFHEQ0SRzQphDDYUsThthlF8L0PMdoIiOFiLWCDTY2wJCuw4B9WmHtOAB1lvLRWwBlaq1RuHCAuBCAkAhlDeOMNP5rAQJgJgWBEjUKRpIJIwJAhJC5JIdGZhJD%2BGpm9HopNyakEplDYE/guD%2BBSIEFI2SUZcDepE/wliB4MyZizHx7Nk48xTnzb2Qss452jpLNgnA2gsGGlyWKTBVTWi4IEYEXA0aa21iQPWegoHCFEBA6Q0yYFW3gSAQuDsmBOynmYixdNeCe0ab7f2nTum9P6cAVWQyRn9kjunaOnizDeMThzepLSEjC2zqgKOYwjk9IxEYQZXAaY0FoCXZmEBy4D3rtXUBkLG7N1bg4UBndGAEB7n3a2Q8R5j1oBPUBM8347B%2BkvWha9J4/U3sgbeoC94NGtkfE%2B1dz4EoTrrG%2B0N76PyUC/WeRh36gBqXwH%2BCh/6AOAV9aG0zwGm3mbIRZcCfq6ELgYD%2BRCrCoLpVQrBODch4IIUkB0KqSFkISBQ9emCaEr2cBAVwWiDasMqKIvQ3Cmg2oyIIpoejljyL6FIzRsj%2BHmqaNIlR9r9HaN9QUf1Ojg3sM9YY0GJi476DdmU%2Bm1jvknN%2BWcwZwy0YRzcTrTxccE6%2BNIP4wJYxqEpIpskIZ6MuTFK5FjSQcSFYGx2b9TglTWaf05nUpA/MfZvJecQNpOxOnBxYAoYaKthrZsuJMMZ7iKFTNkJKiQ0roGWzlToZIpA1kbJdkm8x7tymcC9gLACEI/Z/mICwCdU6Z1zveA%2Ba5GdPFJAeT255HybmvOaT%2B3O070hSVnYEHs86CDcVvQrIuwKEigvBT9GF/dobIbhW3RFHyu4ot7v3QlmBh6j3HpPaGeKeVMsHneYl68B7kspbfalB9eB0tPr8Rll8WWgPZU/Llb8Ih8qTgKpgf8AFAIBGK3gErZlSvNrK62ugkiIOVSgmw6r4CatwZwIMA0DWWFIbs8hetTXUIkRavwVqGEurtTG9RTrcgurs%2BUVRDqvWKKDS60zgblEevUVGjz3nnOhsTUYsGpij3bKsRwG9d7FaTunRCUDwIIN5vGTHSGRbqlJz8QEoJlAzGpMpmYIZSQkhvVxhjamJWuQ5JTbszttgqmPPkqQUJb0IlvRSPjQIkhAhYyiVwRTpMkgntTYzTL8Mj0a1qx2sbTW1j32yM4SQQA)

## Links

- [source code](../../../conceptrodon/coy.hpp)
