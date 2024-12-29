<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Forlorn`

<p style='text-align: right;'><a href="../utilities.md#forlorn">To Index</a></p>

## Description

`Forlorn` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Forlorn
 :: template<template<template<typename...> class...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RESULT;
};
```

## Examples

- We will create a `Forlorn` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<typename...> class...> class...>
struct Item_0;

template<template<template<typename...> class...> class...>
struct Item_1;

template<template<template<typename...> class...> class...>
struct Item_2;

template<template<template<typename...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<typename...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedForlorn = Forlorn
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedForlorn::Cool<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Forlorn`.

```C++
static_assert(PackedForlorn::size() == 4);
```

## Implementation

```C++
template<template<template<template<typename...> class...> class...> class...Items>
struct Forlorn
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<typename...> class...> class...> class...> class Silence>
    struct Detail { using type = Silence<Items...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = Detail<Silence...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXCCABPZ7MNgAOhlqNukKYCgUMqlcoVSpVaoMGpl%2BI5ClRIImxC8DluADESLQSAx0YkrFdbk7bnNHMh5QIJphVGliC68AAvTAAfQI/qDEGWIOdMPtt2ImAIGwY4cwqCoKogeqZCijAQssfu9MuMd5LO5IsF5YFnOF7Kr/MrtYr7PFjFYmE1AWw8u1ytl3d7iv7qsH6pHWuHtyEdFeFbRjudxtNYceLTosYLXiyRluYueMIC92ns4YWzZ2ZYE%2B7sILJkSRfzxdLDbrZcb9ebNaFLffb7bkqdgOPbjl2IF9mBQ46qO4HDiqM70Ge87Rs627hMAtweJ4h7HmuTB0GyCFzmBIAgPuFYOsCD63sWmK0ic1J3OaeDEBMtzYKorDEpglI4hi9EAkC6JghCUI8WyaBIWkBAGjeVz8Xcl6fN8IJ/r%2Br7qV%2BIoAR2kGgcBUHXgulzLmal7BhoNHyQyGnftWTY/jyOnSgZ%2BkwYZYFGgQJpmRywZcFZwI2Vpn6OQ59mthKumuRBMVwcBXk%2BWG5lmIFqm2eFH5qU5UUue5bmTtBhpXKZyV%2BQEaW/EctwAPLPMQ5I5LxdLBWFoURdlmX/rlQH5bFfXxQNRVySZ3krrV9WNQIlXXNVyhMMgADWmDoLcABqHx2M1QJobu81LStlrENaxAprCx5HSdtryXCKFOuZGikDCi73X5XBPXdBJ%2BWYH0vV9TLBhVN1ok%2B1mzXcQheGkaRKOgABKHxeLQYYqVcu0YZD0OZCtCMKEjYbnRN8RTddwK3X9D2/SWzrme9z3U69AM/fTMbmUDZMg5RCkHLcuP49tILo7ziPIzhtz7ct6CXTapFYbQbJ1cTjSGqDQXgzzAAqHwo1SXmNcgwbDvEBAQIipEKB2huyW4fPI09mPFDjIsEKieZc1VAn/IxPNCJgkmrRxXH0ALHuewxxaungBtG20EAS4dVoyyAWQRssOGE5IbscKstCcMkvB%2BBwWikKgnBuNY1guusmziWCPCkAQmjZ6si0gMkkhShoAAcZhmAAnH3XDJN3XdcIkiTSLnHCSLwLASBoj2F8XpccLwCggI9jdF9npBwLAMCICA6wEGkXgEOQlBoESs7EJEHacKoXcAGwALRP5ItzAMg7pSFKZi8CtQgJA8DoD0PwQQIgxDsCkDIQQigVDqG3qQXQ70ADuDU0icB4DnPOBcm4l04DVM%2Bp8wzpluI/V%2B79P7f1uL/MwtwIAeGvvQP05gAhcGWLwLeWhVgQCQFfNIN8L4QAETfEAwApA/RoMjeI68IAxHwTEcIrRRRYN4Eo5gxBRQ1RiNoP2W965X1JAQGqDBaCqKQVgGIXhgBuDELQde3BeBYBYIYYA4hLEsX0XgAAbh8fB3o/Zn22PXcIjIp7F1oHgGIDUtEeCwPg7yeA55ONIH44gMRsaPFcUYKJRgm6rCoAYYACg1rvFQYrQu9dwHCFEOIGBNT4FqHwSg/QbiUAV0sPoaJ69ICrFQNJHIjiX6InOqYSw1gzDL3ScQEB/i%2Bk9G8c4CArhph%2BHeqEcIwwqijHesUbIAg1l6H2Y0BYIwEjvTsEspokx2ieE6HoK5Dg%2Bi3LOTsi5thblHMua8rZixdmrAUNXLYEgcEcHzqQJevAV7kOfm/D%2BX8f4d3oRAXAQDWF104Q3ApqwECYCYFgBIkZSCt0CFKPuAQJ4aEkGYSQT8F7JCfn3fQnAZ6kDnuwqUT8uBPy7n3UeT925DwpU/SF%2BCV5rw3ti7evCD58KPsQs%2BwjREsLvmwTgrQWA%2BMSC/JgQ5dxcD7lKLgncAH4CILM0B70amQPqdIRpShmlIN0D9dBTBMFOLBRCqFBCOBEJPmfW4ZCKHwv1RhQ1xrO4MKYYIlhMIwRmCxdwne8qVXxGVagZhowFRGENVwR60jGSsUoAopBGiVFqNIOWrROi9EOErUYxgJizEWOLlYmxdjaAOMrS4txHi21eOeX4xxxdAnIGCZWsJ9R8FRJiSo%2BJ2xi5JJSfXdJmSlDZL7ehApfBimlPKZUytNq6nQPtbIJpiDi4urafk8ZVgumzt6cSgZjRhmjKPHeyZ0z4iWvmcSp5jQXAMHcPcgoGzgNvKWHszIBzcigfWekGDpy/nnMefUa5/QpjwbQ70AQmHBgofeY8r52GfnzEI1BwFwLoFerwUgmFIaqE5vDUak1GgGFootfG9hSacWkDxQS0YxKp5so5Ua6lKQ%2B7jwCDSulkh3o%2BolbYKVybZXwHlcfEhGas233vhwTVVCrw%2BPdD4iN5YJhmvRSAsBshbWntgfIR1l6dAgCCG6j12CWXgro8vQhirSFUHIYZhQxnbimaNeZsMjDM2xviNxgIvGZW734TFoRFARGpZYSAYz0NgzheDJF4Mqh358DoEWuRpbi7VosfXartb9ENszcY0x5j8HttsfYxx9de25MXc4wdjhh0BNUEExkk7BDTqQbO2JooF2JNmSu3ga6slMi3fkpLRSmAlLKZgCpEoj22ZPRIM9cCnMtNcze4wnSbCPvgP0wZnpOA7DNp%2BywUzoUzLmU%2BwF6HnnLNWaR4IEGKO7MQyUHI3ywewcg6DgDLyBiQ7h3h35FRUNkaw/kBDcw2gw4uVRjYIKOFee9eKzgQWP5GZM2ZrkbFUXmpINxjhXC%2BMCcJZQMFomQD9ylAEAIyRh7yYXrzxIvKxX0c4JKzefHSXJHJWPRIC8u6SEHlwHuZhRVTwCD56FEvpU8LBf/MXvnV56%2Bbmk2ROR/BAA)

## Links

- [Example](../../code/facilities/utilities/forlorn/implementation.hpp)
- [Source code](../../../conceptrodon/forlorn.hpp)
