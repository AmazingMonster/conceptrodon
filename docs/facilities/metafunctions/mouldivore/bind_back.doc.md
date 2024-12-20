<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-back">To Index</a></p>

## Description

`Mouldivore::BindBack` accepts an operation.
Its first layer accepts a list of elements and returns a function.
When invoked, the function adds the elements to the end of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Elements...
-> Arguments...
-> Operation&lt;Arguments..., Elements...&gt;</code></pre>

## Type Signature

```Haskell
BindBack ::   template<typename...> class... 
           -> typename...
           -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindBack
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will bind `int, int*` to the back of `Operation`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int***, int, int*>;

template<typename...Args>
using Metafunction = BindBack<Operation>
::Mold<int, int*>
::Mold<Args...>;

using Result = Metafunction<int**, int***>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIHBAA6oCoRODB7evnppGY4C4ZExLPGJZly2mPZFDEIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW151WN9A2UVIFUAlLaoXsTI7BwEmCwpBjsmgW47eweYRycAnimMrJgAdE9H2ADUyAYKCq8A8rfETHqLxMGgAgmNiF4HK8LBF0BYmMgANYg0EmADsVjBrxxr1O%2B0BF2OBBudzYTwe2AY%2BCMCmB2NxEKhBFeymIqCIAFlPOhUbjXhisaD%2Bfz8edLiTbsxyU9sPQ2II6YFsHyRTivBkjK9ubR0ALAgARX7/QFZS5y3aMAgKCmkV5UmnAG3PZVHIX8jEGt2o1U4sWEiWk6WPWXUiJO%2BnC3Ea8Pann6o1sjmoHW844O8POh7AwJCz3esGogD0ACoy%2BWK5Wi8WK68ACqYMbfCvVsGlysd8uttGFsyBCIfLxYfVuNAMTYpa2R1H%2Bw7EoP3CmRpnQv4JU0CAs90ExrVCLwpAqYdAAJUbXloLKORrXAKBxwiBDLdsf5ZfgnfT5zebBs6J1ylRcnlBYgI1dMFd2AbVMCaKgvHHeoExhOEEWRS5bw3BhIxAEBU0uR9PxLbDcJ5S4QKdJdXVzH0IM1KCzwUC8r0NaDYPghwzQfQRn1eV8y2/GjwSaRxkAAfSYL4EgICAxnQHCFHucSlTcBimLtfdD3SY9VMvF4ljdDgVloTh/F4PwOC0UhUE4NxrGsV4FDWDZMAFPseFIAhNEMlYkQCSQHg0SQuHRQINH8DQzAANkiswAA5Yv0ThJF4FgJA0DRSHMyzrI4XgFBADLPIswzSDgWAYEQEA1gIFIvAIchKDQPY6ASKJ7k4VRYsigBaSLJFeYBkGQV4pAeMxeGPQgSDwOTqn4QQRDEdgpBkQRFBUdRitIXRqgAdwBFJOB4IyTLMryrM4H46tqllUCoV5Op6vqBqGkb/LMV4IA8Zr6GIVzAi4JZeCKrQVggJAmpSFqyAoCBIehkBgCkMw%2BDoHZiHyiBYnO2IImaK4jt4XHmGIK4flibRMAcQnSCahUCB%2BBhaAJrasFiLxgDcMRaHy7heCwFhDGAcRWbwYgqccAA3RtzswVQqbqrZ3MfWpztoPBYgBUmPCwc6CGIPBUr50hpeIWItINXYhfVowvJWKgDCdAA1PBMF2tdzPc%2BbhFEcQVu99a1HOnb9CFlA7MsfQNfyyAVlQScsl57rZOvUxLGsMxstNg2sBjiAVjsCWshcalJj8aowgiQZymGaoCkyAQy/ydIG4YOYhkSaZaiLgRegmTx2j0QuON78Z%2Bir%2BZa9sMem%2BmMf25rzuC6czYJBOjhTMy86coerrev6wbhtGj6IFwKa/vMAGgY8u2VgQTAmCwRJ89IXzJECB4AE5AnRSRArMSQkV0r%2BEip/RKHBkqkFSgDB4kUuCRVip/WK8D/BBX8N/SKW8to5TygVG%2BxUwYVXBlVa6dUGpw1QD9Vq7UODNBYJLdE3UmDvAMFqLgn8HhcAChNfARAc56G9otP20gA5KCDltXQKN9pMEOnzdem8sq8ByldGqdVXh3VeHQhhTCWFCxGhwrhGhPrfShr9f6Zhr4gxKsQ%2BGv1yG2OGFoxhHwhbsK4BlGgl4EiY2xltYm%2BMab%2BNJuTSm1NjZ0ytIzZm502Ycy5rQHmNMBbWy2JZfA4sOLS15pZOWCsdg0xVsZLa6tNb4x1qk4GBsjbuVNubJQltBZGBtqAAhfBHYKBdm7D2NNBG%2B2WiI2QgdNqWUkaHW2acrCRxKXnOOCcBBJxToaCZGcs4JBzjLWOXQe5%2BAgK4WeIRqQLwWHXFu9R9n13qEcqew96h91aAPKYWyR4NHnhPDuQ8Z4PPLtPWYbzF5r1WOsVegNwEKO3pwTRxB6GMOYS4thBiAqfTPnw/6gNga31IPfR%2BwwX5FMgdAjhgV0ToPRCFSQAC%2BrVEURdXKtg8FWMIfAYh1Ubr2MoaY6hbBOB0OeiwBQkthqS3YQ8c4YweHnxmgI2QQj%2BmrXkGI4ZOgkikGkbI46oKzrYMuqQ2690eX9T5QK14QqOGipZF9dl0N/qBEsXbUqENLV2Nhg4xIArDyiRNaJM14koV9VRl4jGlBfGWSCSzdyoaQkSxphEwQUSWZpMwOzTm3NebuWSU0ippB0lFyybLeWyBFYFMEKrYpGstZXHKXrKpNNakWytk08MdqHZMGdq7d2UoenSr6RIAZa0FXB2Vaw4wEcbDTPgLM%2BovMiyyXDunSwmclHZxmhsl%2BNzi67NLl8vQldSjvJOYULI5zTlZCuZ3J5tzPm5G%2BWu0evzd3/Lnn0fZMwWinoBY5IFy15GauyhC/VrxDWCuFWapFvCSCottQQu%2BD8n6UHXvixYHDkj%2BHCkFdKyR0QIKwb%2B2l%2BVCoYrfv4L%2B/hYpRU/pIT%2BIUf5cGCEUwIP6lGcHRVB8B41sOMdpQylYpsMjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bind_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bind_back.test.hpp)
