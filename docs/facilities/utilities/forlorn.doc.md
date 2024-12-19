<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Forlorn`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

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
Forlorn ::   template<template<template<typename...> class...> class...> class...
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
template<template<template<typename...> class...> class...>
struct Item_0;

template<template<template<typename...> class...> class...>
struct Item_1;

template<template<template<typename...> class...> class...>
struct Item_2;

template<template<template<typename...> class...> class...>
struct Item_3;

template<template<template<template<typename...> class...> class...> class...>
struct Operation;

using PackedForlorn = Forlorn
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using Result = PackedForlorn::Cool<Operation>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBAE9UoxWJgAHQIm6HfZMBQKBFwpEotEYrEGHEIgCSPwUNye42IXgchwAYiRaCQGE8TAB2KwPQ6cw6zRzIZECcaYVSpYjcvAAL0wAH0CGLJRAlk8ucc2YdiJgCOsGHLMKgqBiIMTXgpFQELCqACLMjlcsHA/6g15AkHfJ3gx2/e0At1e0FQmFsXEBbDI/HoxHB0Oo8OYyPYmN46OHIR0RibMk2zkUqmyi0aph0FXmryZIyHAj%2B44BC3J1MMdOnI0sBPBk7m1lWs3W%2B7Ku0uvsO12e/s%2BkfDwcV6HMQMRkPxoNzsMLqME2OL6MYlP0esO26Zw4l8LAQ4eTxVmt55p0L5btPw2cgECTh3sx4szuvp4AegAVH//wBgFft%2BAGHAAKtgQhgUIhwAcBDy/oBSH/vBjwPDsewHJgVZnAImypAQpKtuhDwDt647kc6E7%2BtO95riuLbrquGb3Nm1JNlKGhtt2ZEelRlHut8NGwsu86zgxC7kgQlLsT8UpcNxJHPKOE4qQJvpCVOIniWJ9G6SxbGyhxZiKWhykUXxgm8ZpAZ0YmzFxkus5STJRlyQEplPNZ3lqZZGnPrRolOXpwX2YxLk5ocADy0LEMC2SeQhoE0ngxDjIc2CqKw7zYXB3aHmWyhMMgADWmDoHSxAMsQ2onDWlXVUy6GnEqXIcRopDHPuHEpF1PZtXJZida1nIcR5zW3F2SkFceQheKkRTlQASpgCheLQsp1dFsXxQIzItd1ckdX1yo9cNh2vFKQ0nQNl3jY8rZTWZM2HCta0beehxFaV5UNYyj6nrQXwxfEu1Mo9n4PDyeDIFK0bxAQEAXI%2BCiwnDRFuG960EJ1c0LRky2rdjNympD9yIX%2ByaYGgDDoBlWW/LlKHdtDsPw60EDfWVFX0v9ICZPKSznltkik08HArLQnAAKy8H4HBaKQqCcG41jWNyawbNhOw8KQBCaBLKwlSA0saHCZhmAAnAAHBolvS9biQBJIZgspIiT6Jwki8CwEgaB18uK8rHC8AoIAdfrCsS6QcCwDAiAgGsBCpF4OMUBAaBvKmxCRLCnCqI7AC0iSSIcwDIHyUjm7w5WECQeDoHo/CCCIYjsFIMiCIoKjqFHpC6CkADucWpJwPCSzLcsG0rnBRanKeynqhwF4kxel%2BXleSObhwQB4Wf0KKOtLLwkdaCsEBIJnqTZ%2BQlBX9nIDAFIQ00Bt8RhxAMTTzE4QtBCY%2B8B/swYgEIooxG0NTSOutM5sEEFFBgtB/59ywDELwwA3BiFoGHbgvAsAsEMMAcQyDUqQLwAAN1WtPIU1NU5bF1uEF4Us%2B60DwDEOKICPBYGntJPAvscGkAocQGIBM8z4KMCwowBsVhUAMMABQAA1PAmBB4g3lrrZuwhRDiA7ho7uahp4D30AQlAatLD6FYWHSAKxUAEWyNgwuFw6qmEsNYMwQdBHEAbpQqx3RSHOAgK4KYfgUihHCEMSoIwUhFCyAIIJehokNHmMMBIYw6h%2BMaBMNongOh6DsOkvorQkkRJSbYTJcSxiZKKYsLgKwFCa02BICeHBZakEDrwYOy8i4lzLhXQ4VczA71wHXQ%2BZgAg1JPlIlYCBMBMCwAkBUpBjaBDhJbAIbsNAu3dv7aWiRLaew4N7UgvsxlwmSIka2NsuCJGlpILg0tVkezaTPEOthw56ykTHeOF9E7z1TrfDOqB97xFzmwTgLQWBkJZIXJgUYyxcEtnCLgcJFa1yIJ4xuKQNGt20dIXRSh9F910ENYeTBR44KaS0p5wc57J1TocJe4LIXQthceeFiLkU7z3tfA%2BxxRlmGPu8qO59L6Au5fEf598D4gEZVClERh4VcA6q/F4aVKBfz7kAv%2BADSCapAWAiBDhtUwMYAQeBiDp4oLQRg2gWDtV4IIUQxW%2BB1QOHIZQvu1DkC0O1Qwuo08WFsL/pwrYiseF8N1oI4RShREOqPB8mRTA5GKOUao7VWKtHt1xbIPRvdFZEqMZI5xVgzEBssQsmxDR7GOOrEW1x7j4jou8QsvJrr/GBOyfkEJtMqmRLSBkGJOQO3BL7cUbIPaSktoaAUrJeRh2Tt6JUsJCxe2zEmEO3Ji7yjJMaasdYDSan7MpdPDpMrmVytZQipFGhBn4DRbysZArT6G1INM2ZIwFlMMOcchFGyWT3JZCyZ2Zh3a3Nacezgoc3lPvPl8pAScF4StFdnEFWxwXdObGQvkZC2V/HGDXW99cMWd00W3CQWau74tzToEAQQSVkvHoeqefdqW/MXlQQ4aHS4Yawzh%2B06Vd5IZ5TsAIj6PnfMleK9OEmEiYYWlKbDlspS4YIHDYgLAS58DoCqj%2B6rFa6qQbrfT%2BrIFGsBbA01CCkFOswKg9BmDsG63teIkNuCSGuoodglFqgaEvB9YIP1zDWHsIhMG7hnjw28EjSI14sbJFCr4LIhRSiVFTjTbIbFmbiM5oMTRgtxhTE2FLfAaxtiBScC/MjWtlg3HtI8V4sttS0mtr8AE2m5TgjdqXduqJ/aGjtYSWOrrxTclNanWU9dqSegCGneOjd/R2uroGEN6ptT6ntwpUxoOnAONqfQwoTDhwFNwmUze4Z97xmCrPlMmZczKBNK/SAK2cIAgBGlqbW5/sXssnOWB5jEHXkR0mYs/wCKAMaHhRsrgARrksjMDc/ZARNvtP%2B9BppZgkfPImUKlYgjMjOEkEAA)

## Links

- [source code](../../../conceptrodon/forlorn.hpp)
