<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Send`

## Description

`Omennivore::Send` accepts a packed vessel and returns a function.
When invoked with an operation, the function extracts the list of items from the vessel and instantiates the operation with the result.

<pre><code>   PackedVessel
-> Operation
-> Operation&lt;Upack(PackedVessel)&gt;</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Send :: typename... -> template<template<typename...> class...>

Send :: typename... -> template<template<auto...> class...>

Send :: typename... -> template<template<template<typename...> class...> class...>

Send :: typename... -> template<template<template<auto...> class...> class...>

Send :: typename... -> template<template<template<template<typename...> class...> class...> class...>

Send :: typename... -> template<template<template<template<auto...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<typename...> class...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<auto...> class...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

Send :: typename... -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct Send
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<typename...> class>
    using UniRoad = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;

    template<template<auto...> class>
    using UniRail = RESULT;
    
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
    
    template<template<template<typename...> class...> class>
    using UniFlow = RESULT;
    
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
    
    template<template<template<auto...> class...> class>
    using UniSail = RESULT;
    
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;
    
    template<template<template<template<typename...> class...> class...> class>
    using UniSnow = RESULT;
    
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RESULT;
    
    template<template<template<template<auto...> class...> class...> class>
    using UniHail = RESULT;
    
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RESULT;
    
    template<template<template<template<template<typename...> class...> class...> class...> class>
    using UniCool = RESULT;
    
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RESULT;
    
    template<template<template<template<template<auto...> class...> class...> class...> class>
    using UniCalm = RESULT;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    using UniGrit = RESULT;
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RESULT;
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    using UniWill = RESULT;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RESULT;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    using UniGlow = RESULT;
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RESULT;
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    using UniDawn = RESULT;
}
```

## Examples

We will send `Capsule<int, int*, int**, int***>` to `Operation`:

```C++
template<typename...>
struct Capsule;

template<typename...>
struct Operation {};

template<>
struct Operation<int, int*, int**, int***>
{ static constexpr bool value {true}; };

template<typename...Args>
using Metafunction = Send<Args...>::template Road<Operation>;

static_assert(Metafunction<Capsule<int, int*, int**, int***>>::value);
```

## Implementation

`Omennivore::Send` uses partial template specialization to extract items from a packed vessel. We will showcase a simplified version that handles `Mold`.

```C++
/**** Primary template ****/
template<typename PackedVessel>
struct Send {};

/**** Partial template specialization ****/
// We extract `Elements...` from a `PackedVessel`.
template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwA9ABUO1sA1MrEeCx1AJ57BJgsCQaXe7tbGyYaAIKX17eYJgDMbgSnCUYrEwByYyAA1ph0AA1TAKOw/bDPF4TYheBx7ISuPYmADsVlxABEflZXsjtrtQfU8GILlcbkw7gpAcgabQ8AAvRlpe67J6vDYbPYAdRBmFUBGIYIIOIAbBpsPQ2IIFAA6dUmeV7KjEVAsPZMOUaZRgyEwuEI%2BWq5HvBmXH5/emfB3/QHMNjq63fbB7ZAGeF7DyCJjTMgXAFAj3qxVXRgEBSI5Go9EyrEMdAOoO1UMOmPK%2BOexPe5F40kvPYVukfRlfX62511iPuzCF72%2B/0KPYAeUBUo6idelb2yYxhMw2doyKHgr2AEkGAA3VCQo096LcgSajR7ADuhAQFwQIK3ebjao1VqnldLey8KSM4cBOO%2BhO7vY3DFzSrPraR3wsOJEiSJaDpW9Y1i6ToQY2brAr%2B7ZMPCnovMAxCYLGKoDuWlZ3sEwB7AASqgTDoM%2Br5jhODooWhGEFhq3ogCArq1mWeLEv%2BIEvBSDwPPyXG7AAKtgQgCXy5I8TxfE2lB9owZGLb0UirwjjKbhMAkChePQwFkq84GyX8TZwYpSaSimb7rh0gEEuxrF6TJtZuFhKkWX2aQOsEBCkHsnlbN5vl%2BT5gi7FhN4TNyyC%2BgIEzigkxB7BEqCeHsC5iF4x74mZXxAf%2BgG2Zx%2BmOcxzbIcQwAJsWry4Q%2BACy45MFQXgMFUAhkZirhUWV55etgjGFYRxEZr8a5uZuxYcbpKK1I4yAAPqIUo9QQHVtSNc1/a/GpGlaY5nn%2BcF%2B0EDsh0heNvUgKl3iYPMJIcIstCcAArLwfgcFopCoJwTmWNYw7LKsx5mN8PCkAQmh3Ys4IgI9kiqhokhcLi3waI9GhmLKspmLE8QPRwki8CwEgaBopCve9n0cLwCggCTYNvXdpBwLAMCICAywEAkXheRQEBoNcdDRKEwKcKosSygAtLKkh7MAyCRVIqpmLwUKECQeDoHo/CCCIYjsFIMiCIoKjqPTpC6C0O5SgknA8PdT0veDH2cF2XOczKqBUHsosS1LMty3sCtmHsEAePz9DxeYwPzLwdNaIsEBIHzCQC2QPNJynIDAFIZh8HQlzENTEARI7ETBGcNu8KXzDEKcXYRNolR0yDfP5l2DC0KcjtYBEXjAGptC0NT3C8FgJxGOIpv4GhVQLnCjvipUXPrCDnltI77IRFKNceFgjuSscFekLPxCJUoY5j8A7JGODixUAY5XQngmA7mur0g1rwiiOI%2Bsf0baiO%2BbfQhhjDWGsPoPAERqaQEWKgBIHQh7iwmENQkpgfqWDMOTY%2BRwsBQIgIsCoLU/AQFcKMZopBAjTCKCUbIyRUgCFITQ3IaRehULmK0do1RJgMPGG0RunDugsP6KUIY3RuEiPqII2YpR8H/TWBIO2HBnqk0dhTL2YtJbS1lvLWGQcIC4FVhHIGXBo6gxvosI8JEBh4NIFDSQ3xVQAE5vi4kkPDMwkh5Qo1lA4/QnB8akEJsDVUsouCyliA42IoSYZcEek42UyjTYUypjTUx9N44swTmzV2XNyCUHTuHIWbBOB1BYAuXE4tDR%2BmAQHBxqouBw2VvgIg2DNayB1t/aQv8lD/1NroHOlt1IVwUUosmvAKYuw5lzPYHsDTEFKeUypBgHxcFqfU7cIc9TJ3DjiIGZgTGxwZpk/J0Rcm802RnEpZTxZVKMCsrgJMaC0HzoXYupsq7l2HqQd5Nc64NwcIfFucY24dy7pgHufcxCD0PqPYBE93pTz4bPIe70F7ICXofVeuN3oby3qcHe6x3r70Jp84%2Bp9MDn1hXhG%2BfB74KEfs/V%2Bh8P7tL1p02Qf8TbvT6UA6%2BqCrCWHAZA%2BAMC4FpAQUgn4KDQHoMwdEbBc9oHsL4c4Yh6YxEUMKEIxhdD0ieCaNqjokjqE8I4QILoIw9VjCVYQ81UxNVSL0OFC1mQyFOrtTMY1MiVhyOMb4xRDtEmcFmfMipCFlmrLhsHfRzSdlRxjmY0gFisAxGsbjfxgTanw1xLE3ESNJDuKli0UZTtKa2BSQc9J8BMnszdqc45xBCnrBKb7FgCgFyRQXCs1UnwJiNIMerVp2sv6soNvIbpnKdAgG%2BKQAZ1th7DIDeTZ22T3ae2bdLVt7aUpdp7TKDZYdoixu%2BPs6lRzznhzreegY7aEgJFmp2hxs1d3zTmVLXOTzogvJLmXGuh9vm13ro3AFepW7t07pPMFvd%2B5Qs%2BTC8eBKR54Gno4JF89VCL0uBiwQa9TY4rOPiveRxiUg1JckclVxKXXzSTSpgD8n4vzdEytpw6JBssNuOgBU6eUgLQTYDeuCRXwM4BsJBKBpUWAwWMrB6sFXWIIR0FwarLVkI1R6thOQdViI04ayhWqTXKs6Fw5TjreE2smEathbqxFuos9IpY3q9YLoSUujgwaW1to7TumsEwo1NJILG4x8a0nmMwJYlNCj00gDMLU743xHqowRsTWLuIwnObGZwZJtME22Meo4x6sR0YOMkA4pGziuDTtxt8Rd6XS0VoUUrNLJagtx0WMfFIzhJBAA)

## Links

- [source code](../../../../conceptrodon/omennivore/send.hpp)
- [unit test](../../../../tests/unit/omennivore/send.test.hpp)
