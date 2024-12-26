<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-agent">To Index</a></p>

## Description

`Raillivore::Agent` accepts an operation and returns a function.
When invoked by a packed stockroom, the function extracts the list of sequences from the packed stockroom and instantiates the operation with the list.

<pre><code>   Oper
-> Stoc&lt;Seqs...&gt;
-> Oper&lt;Seqs...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<auto...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Carrier<Seq_0, Seq_1, Seq_2>`.

```C++
/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2>;

/**** Result ****/
using Result = Metafunction<Carrier<Seq_0, Seq_1, Seq_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Raillivore::Agent` uses partial template specialization to extract sequences from a packed stockroom. Here is the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
    struct Detail<Stockroom<Sequences...>>
    { using type = Operation<Sequences...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArABspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCmF4iAA6dFg7AXZAGBQKdGozHY3EKC4AeSS0SeGUxf2GxC8DguJ2AjAIfxMAHYrKcLnyLpCESDwQQAJ6U5hsWm8/n0xkEC4AEUw9ToFy5Vk5irBPN%2BMr5guBMJF8KNsMNiPByLRGNBWJxTDxBKJDrxFzqqGQAGtiKhUCxSALTZa3NbUM67cTHfj0UJMABHLyMVYKaUnfkXOVM5Wq2iwj3e33%2B/MJpMMFMR7BpjMai5eNJGAXizDq0GK8mU4jUgQlxPJzAxwl2nXqrU6v41/VBqHCiHNyWYAks4iYQFs1PDqf14LAC4AWU86Fb7ZzTDosOXq4eBEHmJAIDFlPHpy52tBur%2BHy%2Bex%2BX4u2FUVg7hbV5P2/b4ORfMxQWCHEvCwVs3DQctMCSG80zAy5Q2IYg8GiF5Dj%2BC1Z2I41QxRcNbXtElKzpAgGSZbDcOiZ89TOXZmWIYAfHXAjth%2BUikQo2jTizBU43jAB9DRWKI4NZzDESTjE90E0krhZNOQSrWEqi6IY8S1LMTT2MuCkqWeUCtPksjtPIm0h2o6MlJU8yuxqEy/z3FUmCoLxy0swjrJnWz51YRd0ROLiNyrU5t0bbz6j8gKMmPZlWUEWE3O7Bg7xAA9aHQC9oto99INM7Z3S8JI8kwdAACUBy8WgFSsk54t3IRqtqhqmpatLso88EJOkwMRraVSpOM4cypfd4OMahRmtaoL2obXdFuWtLEt8/yHBpcEmLw4he1Gyb1LGozaRmj95suAAVAcVv4ujqWQSTo2iAgIGGdB7wUcKPo3NxNpasbutSOrQfZO05hMjgFloThYl4PwOC0UhUE4NxrGsTMlhWFtzFBHhSAITQEYWL04kkVENAADjMMwAE5ma4WIGfprhOU5aQkY4SReBYCQNA0Ug0YxrGOF4BQQDF8n0YR0g4FgGBEBAJYCCSFFyEoNBbjoaJQnCzhVHp%2BIAFp4kkC5gGQZALikVEzF4OrCBIPA/rafhBBEMR2CkGRBEUFR1EV0hdDaAB3Lskk4HhEeR1GKcxzgyRRbWFVQKgLjNy3rdt%2B3HdpswLggDwDfoYh1Wgrg5l4BWtAWCAkH1pJDbICgIDbjuQGAKQzD4OgAWIWWIAiFOImCBpRXj3gp%2BYYhRTJCJtEwBw59IfXrzJBhaFn8OsAiLxgFDWhaFl7heCwFhDGAcRD7wFd9oANwHFPMFUdeUTWUnggBfmGNaB4AiF2JeHgsAp3ongYWV9SBv2IBESGypb5GGAUYCmCwqAGGAAoAAanhKO5k0akx9sIUQ4hA5kJDmoFOkd9B3xQLjSw%2BgQGy0gAsVAaEMiXwtr9MEipTCWGsGYSWCDcJYHYRABYdh141BcAwdwngWj%2BEUdMfoMQ2h5HSAIMYrRkipB0QwdRpQBgTCqHIzoIwmjKPGO0SxAguiNBMbMCY1i9F6EmM44IfRTGaJkQTVYEhE4cBRuLFOUtc7mytjbO2DsnalwgLgd21diZ1wbpghYCBMBMCwDEaRpBqaSFBKiZmoJeYaEkGYSQ8RRYJGZvoTggtSDCxJqieIXB4j02ZlzeIsRJDszKYkCWvApYyzlmTTBys1Ytw1hnHWXce5V2NmwTgDQWAv05BbJgUZGxcGZqiLgdNXb4CIBIvQZC/aUOkNQpQtDw66EHjHJgccr4hLCSM1OHB05axRBcbOUT842wdHsg5RyNBlwru3KuNdQRmHrpMxWzdW7%2BmhdEXW3dUW9xBf3NmYsaAtWiGPCe4cF4z03mSpeK814bzgdvNku994pyPifM%2BF9N43zvg/DG%2BBn6ODfpfDGn9v4Ak3v/KoKdgGgJnhAtYGNoGwNJggpBSgUFcp3FM7BTBcEEMwEQiUm9LkUIDjc2QNCw4Y0eQwjBQirAsKlVIzh3CBC8P4W2W1IixHRAke/Dh9j9rOAgK4DxbRAg%2BJmGYgx%2BQMghqjUYlxkbZEBtqO42x%2Bik01CcT0cNGjPGpuyOm6xCb/GLGWEEuujTQnJ3DpEvOMTdm7n2YcumZdklnNhekxFTcsk5LyZQEJzTWkHMqZyWIzMeagiqTUgZ4Sa2cHGfLKZKt1aa0zhipZRsTYcHWQXFgCgX4Oxfk2o0wwTkpM9hc2QVyTVB3kHci1OgQCglIM815CdK0fIiWneZWcc6qF3fuw9x7oTDEhVimFxNQQIsbkrWZG7O563AwMA9NVJJHuZpJE9BBJL/pucPIllASUY0pQfUmJHqVyM3vSwQjKD48swMfU%2BYh2VwM5WguV18n6WIFR/L%2ByAf5isEBK8OUqwGillVA3CireDKuQYCdVGCkV8BwfgwhxDDVXuNRIU1wd710Kfda4wzCbAOvgE6mol91i/SYcIywojRniM9r6gpGaMgKKUQW1R6Bi25EMTUWN2iag%2BfMR0Rx%2BaVEhYcSmqYOa/F5u6LGrx2bii5orQoQJAd3nVslpwXOAGD0XHQ6iLDrbTkkA7dBzJpBsm5IGAU/mg6QAs1RKCUEsQOYDNFq1zkXTZ05elrYCZMG5hUxAJIWIpTuaclFvTSQbMuCMzMIkfmoJsujPnV2ymlaXZ9fWwN4bCwEFpGcJIIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/raillivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/agent.test.hpp)
