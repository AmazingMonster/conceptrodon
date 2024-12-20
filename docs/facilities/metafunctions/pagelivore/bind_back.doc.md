<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind-back">To Index</a></p>

## Description

`Pagelivore::BindBack` accepts an operation.
Its first layer accepts a list of variables and returns a function.
When invoked, the function adds the variables to the end of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Variables...
-> Arguments...
-> Operation&lt;Arguments..., Variables...&gt;</code></pre>

## Type Signature

```Haskell
BindBack ::   template<auto...> class... 
           -> auto...
           -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct BindBack
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `-1, -2` to the back of `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, -1, -2>;

template<auto...Args>
using Metafunction = BindBack<Operation>
::Page<-1, -2>
::Page<Args...>;

using Result = Metafunction<0, 1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BindBack
{
    template<auto...Endings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Variables..., Endings...>;
    };

    template<auto...Endings>
    using Page = ProtoPage<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDMpK4AMngMmAByPgBGmMR6AA6oCoRODB7evv5ByamOAmER0SxxCVy2mPYFDEIETMQEmT5%2BgZXV6XUNBEVRsfF6CvWNzdltQ929JWUSAJS2qF7EyOwcBJgsiQbrJgFu65vbmLtuTF5EAHRXu9gA1MgGCgq3APKJ8Uw1NyYaAIJDxC8DluFnC6AsTGQAGsfr8TAB2Kx/W4o24HLafY57M6XK7YBj4IwKb7I1EAoEEW7KYioIjKJjAY6klEIpG/VEctEbDE7bHnVBXC4ANQaeCYMXoxIC2FhnNRXlSRipDMwt12ABFXu9iJ90icRcQxRLMApBaRbvjCcBTddpbs2RyEer7bDZaj0UcTjiBXiCeFrST2fLFcBlYy1QFNdTaah6YyTpb/TaLt8AmynS6/rCAPQAKnzBcL2ZzBYAKtghKWC8W/nnC/Wa3Cs4Fwg8vFgI240AwVokCFKZVm/h7MV7%2BYLA%2BTgW8Pl8066/gr/bchF5EnlMOgAEomry0SkarWzvV7DTmiq3AC0F8vZlT6eH3M9fNxF1%2BxADdsXIduAFlMPUVBeD2NQRpqoIEhC0InDOOpzoOvwgCAcZYm417mregZIShJzvtaE52vOQ6/EuSo7goe4HpGf4AUwQEgSebhnrcXD3gu/z1I4yAAPpME88QEBAQzoEhCisJgvFSm45GUeaq7rikm4yfuNyzPaHDzLQnAAKy8H4HBaKQqCcG41jWLcCiLMsqrmAEPCkAQmgafMUIgNpkgXBokhcPCAQaNpGhmAAbEFZgABxhfonCSLwLASBoZ76YZxkcLwCggGejkGRppBwLAMCICAiwEIk5zkJQaCbHQ8SROJnCqGFQWXkFki3MAyDICxHlmLwm6ECQeAiRU/CCCIYjsFIMiCIoKjqNlpC6BUADuOqJJwPCaTpelOUZnAvOcpWUqgVC3A1TUtW1HVdRcZi3BAHhVfQxBqoEXCzLwWVaPMEBIJViTVWQFAQH9AMgMAUhmHwdDrMQ6UQDEO0xOEDQAJ7rbwSPMMQKMvDE2iYA46OkJVbCCC8DC0Gj81YDEXjAKctC0Ol3C8FgLCGMA4jU3gxAE44ABuJo7ZgqgE%2Bcqz2eE6xafNtB4DEOrYx4WA7QQhpxSzpCC8QMSKeqGwc3LRhOfMVAGNaQp4JgS0zvp9kjcIojiJNDszWoO2LfoHMoGZlj6PL6WQPMqB9ukzOXsJGqmJY1hmMl2uGlggcQPMdh8%2BkLgEqMfgVKE4R9KUAwVHkaQCNnSQpKXDBTP05TtOnAhdCMngtIMVQN7Uww9Pn0xF7YXflxUEyNDXhflKnVkrHMUUcLppBJbwKWnY1zWte1nVSDdd24P1z22W9H0m/MCCYEwWAJCnpCuZIAQXAAnAE8KSF5ZiSEFCXaUFd8zzFpBxXZFwgpcCCmFO%2BYVgHuS4NpB%2BQV547RSmlDKDkTa5QKj9IqB0ypAxBk9WqbBOANBYPzeEl4mD3AMEqLgd8LhcE8r1fARBE56AdmNZ20hXZKHdvNXQkMVpMDWizTas9trzRSvtEq5xbjHVuIQ4hpDyEcxYtQ2hGg7oPX%2Bk9F6AQzDvWQdlb6v1UCPXiOVYGRiNEDFkSQh4HMqFcDPDQfc8Q4YI3mpjVGRN3HY1xvjQmmsSaMAIOTSmO0aZ0wZkzImbNDarEMvgXmDg8CC2ZoZEWYt1hEyllUHacsFao2VrEj66siba11kofW7MjBG1APovg5sFCW2trbImLCnYTXYbIN2c1DI8K9sbaOVg/a5OTsHUOAhw6R0jAM2O8d4iJyFkHeuiTnAQFcIPYIBJR4zGLpXGo6yS41C2X3NOyzO7dHWScmoTdu7FFroMAeLdshDy7kc8eCwlhTzejPOeC9docBkcQIhJCyE2Mocozy28GEkC0QfPRX1j6n3PpQIRv9/7UK8vCaB8JfKSFfi1CovyEG2CQZ9HKeVCrFUOqYnBNU6ocEIRdFgCh%2BadX5lQi4Rwhj0N3oNZhshWHtKmvITh3SdAgCCHwgRG1vkiOSntTBR0ToMtakylltw2XUM5ZSe65iAZaICLo0lBiUC6qetS01AwWXrm4hq7iWreKApalDJxsNKCuMMl4qm9lPU%2BL5kTAJZMKZUziZgWm9MxCRM1tEqphTSDxPTsk4WotkDi0yYIbJst5aKxRgU1WxTNalL1gbKp/oUFmwZA0q2Nt3h214K08aEgOnTRFR7cVfTjC%2BxsMM%2BAoyajM2zMJH2MdLBx0XgnQaCzL6XIzqsrOjyc4bPQK8iu%2BR0j7N2ekZdQ926nOuRcndVyXk9zuc885877mTGPWPaelkPkTSET8%2BBnAAUsEZcy1l7KtWQt3jCw1R9SAnzPgMS%2BMtUX%2BGoQEAI2kAreQSpB%2BEIC4GiM4IgzK/7r7aXvtpMKwU76SDvr5R%2BXAggywCLKxeKG4XORnj1JDcrUpUdmPMbWqRnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/bind_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/bind_back.test.hpp)
