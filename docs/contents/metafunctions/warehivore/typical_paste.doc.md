<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::TypicalPaste`

## Description

`Warehivore::TypicalPaste` accepts a list of packed warehouses.
It concatenates them together and uses the first warehouse to hold the result.

<pre><code>   Warehouse<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Warehouse<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Warehouse<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Warehouse<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

using Result = TypicalPaste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed warehouses.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed warehouses at the front directly and place the result into the first warehouse;
  2. Invoke `TypicalPaste` with the newly packed first warehouse and the unhandled warehouses.

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedWarehouse>
struct TypicalPaste<PackedWarehouse>
{
    using type = PackedWarehouse;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct TypicalPaste<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        WarehouseA<ContainerAs..., ContainerBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyaBbgQAnumMrJgAdPcn2CYaAIKTxF4OANQAKpd4oloyiYk0wXxMKSsKQAIicrK9ni8APRIr4WEFglqYdIgRGIvYHI6YE5nS7XNhfYHIADWmHQAHU2pgEBslI9Ee9PgRfv9AcDQSSqbSGUyWV42YEngjIYivnKvuKIsAvhcruDAtDKUwaXTGcRmaziYF4S8IbDjXjXiivgAlTDITbZABumL2OMtLwJhyYxwRp1l8q9RJJQZ9RtJV2YbHut0eX2QBgUChjcYTIIUXz1BvFmBepADctDx1ORfDqvJdwekvjieTVewNfTmdFhpsBZV%2B29xYjFZT1bTSZjHkETAiCTepHBr3lHcJYZDZKjldj/drQ9ko8ixAsCnz08Di5uMYA8gQEAkFHjJRyCB9vn90gCxPzu1mxUpTadh60x8Q3n3sEnN9WxJb9NwSHcAMnU9z2IOsVylU0ZX3OVFSMFUyXVTVyyXHlHz5EFfReGcSXbGdgJzT83DA39/3uScaK3SD6z3YiZ3lGCLxTFD1WwEAQHLOE8RhISEStAAqSSpOkpFESRKSfmwIQfik2SJOkjS1NNBEzECCIEy8LB1TcNAGG2dICEva8xM9TtgxLOz5xLQ9o3rRtB3rG8725CilAAfQ0UTtNsudu1LBdIyPNyB3g9lXk5b5fMwPyuCC/FHLCjKyxc5dUzXTz4tvLlm31d9krMNLXnC5zItchCvOK4cAsqkKu2y2rcust4iu%2BJrUotGzqp7JcAIa3qBD8iqBuCoacKi%2BrCu8r4msCFq0OVIQvHSEo6TtBQvFobkTk1JLmq/CaNAYiauCuhhJtuvzVuvabEXW21MH2w6sLwp8gUI4k/TcdtTsC867tBwCpzYuVTv66jroeqbAOBlsc0m0CJqexDHn4wSXsKn0AT89MEgICBJnQfiFBuYmrLcPaDoISdNu2rJdo%2BxnHhWIKODWWhOH8Xg/G4XhUE4IHLGsL4FA2LYwXMQIeFIAhNF5tZqQCSRbg0SQuBSQINH8DQzCSJIzAADnN/ROEkXgWAkDRLuFrRSDFjheAUEBLpVjgtDWOBYBgRAQA2Ah0i8JmKAgNADjoBIohuThVHNpIAFokkkL5gGQZAvikW4zF4OlCBIPBKZu/hBBEMR2CkGRBEUFR1F9nQ9AAd2IJgcRFvmBaF1XXc4Y8I/D7lUCoL5k7TjOs5zvOtbML4IA8WP6GIcFdK4FZeB9v3SAgJAY8fNfyEoI%2B48SYApDMPg6D2ODKFiAfYgiNpzk4JWX%2BYYhzmPWJtHtD7JWMc2CCGPAwWg78W6kCwLELwwA3BiFoJ7EWMD9iGGAOIaB%2BB9QODwC6FBLtMCqHtBHHYSsIh7H5tA2geBYidx/h4LAA9bx4Htqgl0xBYhs2hOgowtCjCqzWFQAwwAFAADU8CYDbseSMH9eCV2EICWu0hFGNzUAPXQN0DCCNMJLSw%2Bg6Ge0gGsVAFlcgoNThTY6eirCWDMC7VAnDiBlw%2BvANYdhAG5BcAwdwnguh6DCGOJYYwbolByAIGYfgwlZAiQwRYoxEg3U8XggQAxpj%2BMKMkhoXi0lTCGMExJeh5gZIKNE2w%2BSEnVFCR42W2wJC9w4ILUgztRacEnindOmds653zovCAuAS7rwVlvHeQi1jniYFgRIEB1YgEkIEW4ABOQIKRJA6zMJIJIjt/BJCWdbDgttSD20VrcJIXAkjmyWebC5/hdb%2BBWUkFpA83Yey9srIR%2B8g4HxDiPCOp9o6oFXvHROHA2gsCdCkVOTBGzoS4Es24XBtZF3wEQFx5d65KJrhIVRsh1HNxdroG%2BHcu7yMac01pg8ODDzDhHL448vjgshdC2Fyp4WIu1kvFex8Egb0CGYbeHyW7%2B0PkCnlZAo7nzXiAJlUK0xGHhVwS6NBDoXkfs/V%2BP95GkC/m/P%2BACHDapAYwAg4DIED1gfAxBtBkHaqwCwDBWCXY4K8QQgexDSF7G1ZQhoA9aH0LfkwnYLtWHsKVpw7hSheEOv4UqT5IimBiMkdI2RjBtWKOruIOuailAaOgUS/QGCUDWGsIY2IxjZmu3MQISx1iNS2OsA40WzjXEVo8Tk1JfgICuCiYE3xVTlgxNKLkXtQ64kDtCb0XJzR8mjqnZ29JBTKhFOSbOzJ5SSlLpGNUpJtTNj1K3gcilLz2mypZfKtlCKkUaCXoMtFfLRlCr9hMzAUyxiVuoUck5CKdYpAeSkfWkhNkZxupS15th3m715l8%2BAPzQ6jwBVKkFbBODgpniwBQTpc5OnZUSSYKKhllz0Bm5ROLMX4s0SAYIJLu48HJf3aBbsaWj3pRPNDmcMNYa%2BDhhFeHuTLzFRfPlgRBVQZFSgQTJ9JWSbGFh7afkeN%2BT48TYgLAM631VQ/CAT9oG6q1agvTv9/6AKNUC0BpqIFQOdZgOBCCkEoKVvax1wbeAurwW66BHqHRetQT66hLt/UMPOEGlhLiw28AjTwvhmC43Cr4KIiRUiZFyNQSR7F2a8W5oJa3YIOjjAloMf6ttVamgoKRBTYt%2BiLBNtdi2rAxWUlNB8X4spfb0ATqSRkWJTQ53hKaB14pHamiLrnY1/olTCk7uKWu1rq6FiTcHXuuWDSj0Mccae1T6HMPYdw2GSYt7UUkAfaJ8ZpBJnTMoI0r9IAzAIsCIEfwRtdaO3uykS5zzGOcDed7U7GtJD%2BGWf4c2JslmSCWfrVZXBcucECGttp7sn1qwOYXD762EdibWJw7IzhJBAA)

## Links

- [source code](../../../../conceptrodon/warehivore/typical_paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/warehivore/typical_paste.test.hpp)
