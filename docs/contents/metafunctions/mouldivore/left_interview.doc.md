<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftInterview`

## Description

`Mouldivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
LeftInterview ::   template<typename...> class...
                -> typename...
                -> typename...
                -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct LeftInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = LeftInterview<std::is_same>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

`Mouldivore::LeftInterview` is implemented based on `Typelivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<typename...> class...Predicates>
struct LeftInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = SensibleLeftInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template ProtoMold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQSAMxcpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8UkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5onhyN5YANQmiW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzyeBEwLFSBmBpzcBGuqUYrEwADokf8nhNiF4HEchIxMjF6CFMFQCABJQTxABueEwAHcASYAOxWJ5HFlHYGg8GYSHssFMCFnaGw5hsJEIu5HA5MBQKUXKYiYfCiYEKFGPVlHNEYghHOWoIgAJVQTHQAPVDKZavVrJ5nO5MLhIuRiXuzKtLM1mN1RAAsp4Ta63eaNS1HMgJQIJphVKliEcmBdUEdyWIvO9zQBaLgMgAipwsJ3pucSFtNbrZIN5/Kh9uFiKRj2A8pBjAIKudpbdXkyRiOvto6A%2B2Z1xD1qD7JrODabbEEMqd92LHYLRZLAfLHL5XIFFdtApr8NF4sl0tl8sVm7bLstLK74WAR0NxsHw9Hj4nbjlCrwSswc7F7cXJ4czzOkgR3Tc7SFeEjgAMTwYgJlVD1tWxBhcXxQkSTJYhKRpSE4IQghVXNJcbQg7cNyrQUHTrf9sAlAwTyRT9z2VVV1WQl8DSNf1rwLC0y3XSst2rKDHQRAkiSEPAsEvJcOIIdFPRHH0/Xk1kgxZdS3TmUNwzQ4Fo1jeMiCTFM0zXQSSMswSNIAVisOzswgZYjnTcVvhAEAWCYABrTAAH1MmACJ0ACoizkyAAvQKIqvWyy2sviErdPAqH0yMjJOGyUtZKBDzMfxzH8FjvwvSFJOEGTf1FUhYPgxDnS85NvEwZZlm03L%2BKOeUCA2Bgjg0PNl1A5KupZeolE63Kg16/q3KzYsRpy2ycxc6aNMLECVuAwDATGlkyKo/dxKnTBm1ndiy1vHtx2fL0xzUydG3OmdW0PACBM2ldRvVI6RP%2ByCaI%2B%2Bjjz/M6LtbK6b27e833ulTUDfSEIbev9/j23bV0eQG9zE94CImOrqNrLFMDQBh0GJk7aIAeQIBB4jk1FFK1Mm0LwPFMEq0lgRwqlaTOQmCDq7EKapo56cZhCQbpRlSPAqjFYBmmQYYqU/1Kn9mb4ziHuRtcksE3HROBpFKuk2ToatPXEfHTrNOyg6bZDb8MsMmM4wTMzWqdmb5ZWqyHJMJyXLcjyCHQLyfP8oK8BChVwshaLYut/2vvG9U0vdqNPY2hL8uRQriq18qzgt6q/zq4W7ma8z2vz1bGR6zA%2BuIAahqW4CgMDlLJvebOKcyvPe4LiACqKwrS7Y8vMMtmqkVF8mBAnbA69ahvR6b/M5vbo5Fvzbv9szq1%2B6OQeIw94hG8EiAb5S1D0O5zDeYpAXISlpnZa33KvP%2Bh8eKQmngvOi98Ep/2Vr2J6bgK6yW/s7E%2B69UxHDAGAU4Q5MxgKtB1H%2BiVm5YMErvAaZgTiWHZk/Hm2FcKCzcJ/GW84CFlggZRd4yMzjAPRu2XB4CQD/3trPKSld4En0Ekgrch9uFWiPowiatApqSLNM3IhC1hpHxPmtHBCDvrbWdljX6ZYTYkwPPWF6kMdaCRuveO66CuKPX7CjUxaNZZ7UUT9HufFDHKyBrWNWYNRSoxbOY1kliAFPhsfrQBz1pyBOcSWLamMwIsO5F4vGZs6LqyYgiDhSFWaYkoXzahcsM5CV3KbHxSJX78xpEza2ttRz20NgHZ2hjVZImwPQNGadgmwygf2Z8j9OYYSJJUwpZx2lmOEUw3hkCInGiAWeMqypJlumYcJWx/C3AjIFl/BhLjtEJI8SkspxiETjM6VwviITrGJCHA9DZZyYm7LiW4/aAB6AAVJ8r53yfmvIBB8r5RwAAqv5WxHG%2BX8p4AKfkws%2BZC/aLwGAHC8McSEFw6A3GIok4S3iTmPGIMAHWVzW5MCoF4JFjRnz5LfnhSKkcvJ4AUEFeEqovIbPxYS2Jo1dLfgChreIREngQG9CSslFLsiQnCAQT5tcQAbKlXVKV7zFWCE%2BSq6V7zZUtWQegmxZgOp7R5cgPl0oBUAmFaK8lDgJVnHJKgGSsr5WCHVcq8%2BqrXVKs1U1EA2q0w3JsZmA1FgOCrFoJwOyvA/AcC0KQVAnA3DWGsBqdYmw0xmGSLwAgmgQ2rF8iAOy9IESJAABz%2BHpIkMtGgS3loAJyJH0JwSQvAWASA0BoUgUaY1xo4LwBQIB21ZujSG0gcBYAwEQCAdYBBUgXHIJQNAoI6DxEiPCTgqhS3pn8JII4wBkBhikAiMwvAvxEGIDJPQ/BBAiDEOwKQMhBCKBUOoIdpBdApGpMQJgqROA8FDeGyN2bY2cFphcGd2pUDpXXf4Td27d37skIeo4EAPCLvoLGXYXBliZuzasCASAF2pCXWQCgEACNEZAMAKQZg%2BB0D5n2iAMRAMxHCK0a4P7eDMeYMQa4tMYjaHJoOngpAF1vVpgwWgbGX1YBiF4YAbgxByPY6QLAPkjDiCk/BATeByS/kA1GcmFxthCalfUQDVwYifu4x4LAgHFJ4BbdwXgOniAxAyJgbMIJDDACuEYHDfADCEoAGoC1pkKJTl7hCiHEHeiLj61CAbffoLzKBE2WH0JzPtkBVioFSI0PtHB0zfHQaYSw1gzBduc2e2S8BVh2C084CArhph%2BBSKEcIwxKijBSEULIAhmt6B640BYIxqg9Hq00SY7RPCdD0HV61Ah%2BhtGG510bcwpjTfyOMSby2liYbWBsLYEg/0cAjR2wD3ajhQZgzuvd%2B8EMkIgLgQgJBSHJCw6QQdWh2qkEZsaUYLlSB5skIkBEdb6SSA0JIMwkh/Btrsv4GtDaOBNtIC25ICJ/BcH8MWmtxasd2UkFwOydagidt4N23t/aPt%2BdHROqdYG52kdQKh5dq6OCtBYOSek6YmDqx7FwGtCIuAIhjSekg56UgRevdF6QsWlDxZfboajH6v3seO6dsnQGOAgenRcI4EG4zEE59z3nkp%2BeC%2BFxoJDKHCNode/q7DQ7cP4eZ7b%2BIjOyNoZABzrn6YzeUZrVwdtNBaB0coIxl9nHWNKaj9x3j/GHBKZEy2MTEnAPSdk/J2ginHPKc82p7YMb8DymtTp/LovVAGeBEpkzYaX3mcs9cazhfM1noc0J5zrmlAedU95u8fmqABYUMFmkoXGDhdkNL29svZBxefTGpXSXfMlasGl8zmWAc5by5wQrkdiupYsOV8nlXK41bG/NvwjXKb9da5THbXW0gZF6zkDbLXH/FGyPf1b9RxuLam3kN/ObRoP/L/WbSbG/WwbbdrRYLrWrFNQ7PbOvDXc7TgQ3Y3HnPne8AXIXEXJDJ7U9V7TDR3L7VYX7LABIAHOvFHNHQXSHekYnekctKHGHQnM7F9CnWwKnT7YdWnPDSdUDWdEjT3VnNgTgDnLdI4FgBQckMMckbAzkCYY9fAU9CXe9SLG9CQGfB9eXefHQEAetFXb9RzdXADdg4DAQ8DdKcQ7dKQmQpMeQi8bUZDV3IjV7RId7bg53FAFwtDD3Hw0YGQ1IVIAKOQmtAKBQggPlI3LdGjUPJmcPJjFjbjGPJInjPjATJPZnUTcTSTIvTAGTOTBTfLITFTLzdTIvTTUvXTF9fTZAQzGvMkOvGNBvVjZvWzNvJTTvNzHvMo/vJ3fzJgILELMLXPKXKLafNQufBLfQpfYwA/dLGIDfbLXLbIfLV5TyFfMrCreIKrXTLLc/RoFwa/V/PQNrcoEbAbJ/RoCAwbT/aAi48YH/C/P/CAoAvoKA84lbMAgYV4j4jrXbOAg7W9EwtgrtVA6wyQ6Q2Qhw5UJw/Al7DDDwnDUgzAP7Cg47agkAMwQXRIRIOyOySHIPKtRIekbHUE8nTgSnAdZEwHEAKHDHGoQqRIbEzHQqDQekJHRIUwsEntanJ3Y7I9ckrXYgnNUgZzTIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/left_interview.test.hpp)
