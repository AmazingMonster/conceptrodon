<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Reveal`

## Description

`Raillivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes the alias member `type` of the operation.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>Operation -> Rail&lt;&ast;&gt;=Operation&lt;&ast;&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal ::   template<template<auto...> class...> class... 
         -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Reveal
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

template<template<auto...> class...>
struct Carrier;

template<template<auto...> class...Args>
struct Operation
{ using type = Carrier<Args...>; };

using SupposedResult = Carrier<Seq_2, Seq_3, Seq_0, Seq_1>;

template<template<auto...> class...Args>
using Metafunction = Reveal<Operation>
::Rail<Args...>;

using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Reveal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Reveal
{
    template<template<auto...> class...Sequences>
    using Rail = Operation<Sequences...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgKykrgAyeAyYAHI%2BAEaYxCCBAA6oCoRODB7evgGkyamOAqHhUSyx8YF2mA7pQgRMxASZPn5cFZj2BQy19QRFkTFxCbZ1DU3ZrcM9fSVlCQCUtqhexMjsHASYLIkGGyYAzG4bWzuY%2B4eb20y7B0xeRAB0j/vYANTIBgoKj/fPbx8KLwA8ok4ld0s8TBoAIIKAjELwOF4AJUwADdMGJIVCTAB2KzQl6El5HS7Xc7HK6nG53VDfX7vJifb5CTAARy8jFWCghBKJXlSRmRTDoL32ABEgSDiGCBGcWezOZgvk89tgQCACABPEH7fHYnFi3VYrEAegAVBbLVaTabLQAVbBCO2Wm3Q81Wj2u7HQ8x7MLvLxYUUHNAMVaJAjc1XG6Ekk5nW4PFXYLGw%2BGI%2BUAfQ0Rp9sYu8epSZ%2B0ehaYRBBeWa4ue9ULjlITNLppZhcIrVbZmbMtaxDbJidpydT7YzXb2vfzFLJ/apbkHLdeDKZw7Lo8rygQhiILEn9YLjYOs6bxfp/2%2BUOIwCjKbX6crwNBnWNeJe/LCwGJ2swwYlm%2B3qC7gcl7Xouuqigae7voKQheIkeSYOgKIKF4tCVuKLz/oIgFyl2ZikJ2rKZnsBFZhopFdjW0Z7HqfYHjO9FzguyZ/Iyyr3CBN5YtBn4ALKYHUVBeGGnS/siaIYrQZyPtKz6tuqSLClJwFXuxEI0TGUI8eJKFoWJ/GCcJ1SygcWb4YRxEUUR5EWVRKYaXmbZgsgmZsXEBAQLC6DqgorCYK5UZuMhqEEKRcEIUhSohc8cy6hwCy0Jw/i8H43C8KgnBuNY1gvAoSwrD%2Bvo8KQBCaPFCwANYJJI9waJIXA4nsGj%2BBoZgAGxtWYAAcXX6Jwki8CwEgaORqVaKQGUcLwCggORpUcFoCxwLAMCICASwEIkdzkJQaBbHQcQRH5nCqF1bUALRtZILzAMgyAvFI9xmLwiGECQeDeVwMiCCIYjsFI33yEoahlaQuhfQA7tKiScDwCVJSloOTYCdxbZWqBUC8p0XVdN13Q9NVmC8EAePt9DEKKZh7Fwcy8PNi2kBASB7YkB1kBQEAs2zIDAFI%2BE0GhcQzRA0Sg9EYT1JqsO8OLzDEJqgLRNoVTzcVe1sIIgIMLQUsLbwWDRF4wDzrQtAzWlpBYCwhjAOIeuW3gxAq3g6Lm%2BNmCqFUdxrMVYQbIl9u0Hg0TSvLHhYKDcJ4ENFvosQ0QpJgYqbDbQdGGVCxUAY14AGp4JgEOPqlxX8D9ojiADpdAyo6j2%2BD%2Bg2yg2WWPowczZACyoBG6Tm%2BdXniqYljWGY42oHHxAfUq8ALJUxl%2BBArhjC0QQMOg0wDPEX15GkAhL3o2%2BdOvpSDF9s%2BdN0oyeM0ehnzUIy9GE/TH5vkyX1ky%2BwlMj8zCfM/5asEh4YcGSqQMa6VOBYzOpda6t17qPSJhAXAb0KZFVpiVDOCwEAYiwPECAlUQCSD2PcAAnHsHEkg6pmEkG1Ea/g2rEL6hwAapAhrU3uG1LgbUurEK6pw/w9V/CkLaqApGnBpqzXQXrJaq0mbrVRttDmXNyZHTYJweoLBUQ4nOkwVigouDEPuFwWqL18BEAnp9QGv0K7SCrooGuoNdD4ShkwGGaUgEgLARNTgKNNp3BeBjF46jNHaN0Z%2BfRhjarE1JqzcmlM9hmDQfTeKjNmaARiXEHanM0ncyCVohkRh9FcHIgLDYxBhai3trLSW0tSBVPlorZWDganq0YAQLWOtQYGyNibM2NSrapzWONfATtqiu1Bh7L2Gwal%2B3aKDIOIdJbh0GXTCeMdipxwTkoZO1sjBp1AFIvg2cFB5wLkXGpVcrH/RsbIOxIM64gHwgYdOg8rAt3me3PBE1u4CF7v3PYYoXnD1HuPSeHyZ7tGds4Beq895fRCN/De%2B8Ug7wyFfcYuRkWHwRc/G%2BEK54X0aGij%2BeLz73yPrMU%2B99YWvwfsURFNNFjLAAQygOHjREcECcQDRWidH5LCQYoxGhiZILMXEmmdMMGkCwUwHBlAgHMNYQYuqOJBE4kapIKhV0vqeMmuIuaGdGYyKQBtNGmSlGHWOhwdRuMWAKFRPdVE4STiwhMcgj6egLnlyuYDW5tdxq6BIs41xcNGFsvtsjeR6NMbWuura%2B1LxHUGOdZWEm2TYm%2Bj2Ikg1sjzXs12mmwY9r4KZkTZmZNrkuVXT4HQUp5SxYS3ljUupCslYq2aYBDWbTta6yGZgQ2xsxC9Itv03ZyyHYjMcGM%2B2EzkDe2mYIWZgdg6h01EsyOqyakbMTts1OH4DVZyYLnfOhcQTF14J6v6EhrmCF9Q4kAJEnnGGbjYd508vmdHNiaLyTch6WBHulEFWAwW2BJekFwMKiV6HhXSnFW9MXpGpQfdI5KT4gY6HfHo1Lb4CAJShl%2Bn837X0pV/GDFK/5Mv%2Bu4xG4aIExpeHGh1TrKSwmFaYkgYqs1SMwdgwYnyA4KoeQYvYex/AtXqiNYTOIuEiJo1NWwEiklzHwZIfwJD/BdXasQyQxDGpkK4A%2BzgexqOjzEZIxaQDnoyZM3JxTCw46pGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/reveal.hpp)
