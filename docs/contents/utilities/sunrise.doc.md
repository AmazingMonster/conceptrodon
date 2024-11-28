<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sunrise`

## Description

`Sunrise` is a vessel for `Grit`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Sunrise ::   template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Sunrise
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Sunrise` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_3;

using PackedSunrise = Sunrise
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

static_assert(PackedSunrise::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Items>
struct Sunrise
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAQBspAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBoNhwP%2BoIAnqlGKxMAA6bE3Q77JgKBTYzG4/GE4mkgzknEBbB4qlEml0smMkm0%2BkE1kASR%2BChuT3GxC8DkOQi8DGIeCUTxMAHYrA9DkrDrNHMg8QJxphVKliCq8AAvTAAfQI%2BqNECWT2Vx3lh2ImAI6wY5swqCoxIgPNeCitAQstoAIjLZcH/TKHgB6ABUsbj8YTkaeMbjhwAKtghGmhId40mownC3mI48zLsGPsvEcvmgK5hUgQ%2BbSS2DERDfm34R3oa2ewi%2B92kd9Uei2BT2Szx8yGVOOdS2dPObPJ0yBQQhSLvSxjRoTgrHg9e0Oj%2B2ocf%2B%2BfB6e4cO0cwx0y56zKUvHyuF0/lzPVw9BcKzVuxpcHuLYXtenYwleXZnuBA4wSid4Yl%2Br4fu%2BL7zuhz4Tt%2BC5rhuAE/MaZggQ8TwntBN7kZB8HUZRYEIaOWJvjhmHIRh2EoaxP73H%2Bm6EQEJEHvcXiZEYhzKEwyAANaYOgYoSlKmDHAEgaiuKkrSqRpzWsqgEaKQxyKrphFcAZOlKoBZhmUZFn8TKzbhqRv7NGqxqcvEBAQBJ0myfJGnsCAmQWksylhqpkh%2BvuHArLQnAAKy8H4HBaKQqCcG41jWCqawbEpOw8KQBCaNFKxSSAcUaJiZhmAAnAAHBoNVxXVSQBJIZiypIKSxRwki8CwEgaPpSUpWlHC8AoID6UVyXRaQcCwDAiAgGsBCpF4BDkJQaBvHQ8SRBinCqC1AC0SSSIcwDIOqUhVbwsmECQeDoHo/CCCIYjsFIMiCIoKjqLNpC6KZADuxBMKknA8DF8WJcVqWcAA8ht61mu6hzHUkZ0XVdN2SFVhwQB4u30Hq%2BVLLwM1aCsEBIDtqR7WQFAQPTjMgMAUhWTQtAvMQk0QDE8MxOELTIlDvDC8wxDIojMTaJgDji6QO1sIIiMMLQYuA1gMReMAbhiLQk3cLwWAsIYwDiNreAOg4eAAG6YMbKXagrG1bAV4QvD1KW0HgMTg9LHhYPD654ANJukI7xAxBkmCBq8Ft%2B0YxUrFQBjAAoABqeCYCDiN3krb3CKI4jfcXf1qPDwP6BbKCZZY%2Bj%2B5NkArKgDbZMbJ0XCcgamJY1hmKN0eSlgLeWt0CsNC4DDuJ4HR6KE4RDJUIymUUWQCFMfjrxkm8MPMwwJKZdhT70ExtPP%2BQn3UZ8CH0rSH6vx%2B2Bf296LMj/Lwsa8rAoOWbAkDDDgCVSAjV4GNDGp1zqXWuocW6ZhCa4EemTMsXAKaFVTisBAmAmBYASBPMqgRMQ1QCJ1DQ7UupDTikkGq%2BhOB9VIANAIXBMRJC4EkOq9UOFxUkFwOKpCUjgIRuNWwU1MGzRpktWmK0UYbS2izVAJN9qHQ4C0Fg9tZQnSYByMSXAaqYlYS7fARBR6vVkB9Mu0gK5KCroDXQVkwYQ3FsA0BwixrIzWhtQ46N1GaO0bo4A8CDFGMJsTBmpNjhljMBgqmc0ZGs1JgoxJIw/FaPxEYfRXB9Lc15vzQWgNJaiyVkU6Wst5aK0jirRgBB1aa3hjrPWBtaBGyVmbJOWwUr4Fto4R2zt7qqDdi8JWXs6jwz9gHUWwdOmU0lBHAq0dY5KATubIwydQCSL4BnbOud86F0jsXSxX1rGyErgDFKDja4p37lYRuEzx5tw7pqTg3cCDoF7jcwew94ijydvAP%2Bt87bOAgK4d%2Bpkl7lCPnoDeDQwVpD3g0J%2Biwb49Hvm/K%2BO9J5AsaBfJFa9X79DhZ/AY38oXoNWOsQB5KepuPhpAtJASMlBP0YYzEGgkEmJIFElhsSsGkBwXgkYE8eqMOYQYihsoBGyllG1MwXU%2BFgLpZwCa4i4lSPgDI1aqNklKIiSotgnB1EwJYAoe26p7Ysr%2BOMe6nKzGmUOaXY5P15C2POToRIpAnGQxNq4uGgMPFyLRlQQ4RqLomrNYcC1BirVmiJrqxm3KAi8s2Qk%2BNSTmYpISGa1IqRjRRuNDGtyxAWDnT4HQPJlACkpVKVrAqNbylTyVtUtWGstZdMwLrfWhtjYFXaWsmZpBulnz6fDV2yB3YjMEGMwGEzA7ImmaHOZStFlxxWUncIGzqZbKYJnHOecC6MCLhYx1EgTm/VddXD1BhrkNxsPc/5qUnkMGNpGC49cB6WCHhAkez0/mtyxdPEFs84UQpXsi%2BFxRshwphdkPFL9T7YofpfPImKEMNCQ3Bj%2B6KUNYbmKS5%2BQCKW5UIzSv1o1OAhuLca015rLWInGBylB3L0GUz5QK/BlBgGipALVTEAQAhxQqnwoa/HZScMVf65VYjpp8qIQY6VGh9EUK4MkOKsozC8PoRwAIZGIFSbVcAswumRGsckSsaOmRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/sunrise.hpp)
