<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-bind-back">To Index</a></p>

## Description

`Raillivore::BindBack` accepts an operation.
Its first layer accepts a list of sequences and returns a function.
When invoked, the function adds the sequences to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Seqs...
-> Args...
-> Oper&lt;Args..., Seqs...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindBack
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will bind `Seq_0, Seq_1` to the back of `Operation`.

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
struct Operation;

using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

template<template<auto...> class...Args>
using Metafunction = BindBack<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

using Result = Metafunction<Seq_2, Seq_3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct BindBack
{
    template<template<auto...> class...Endings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Sequences..., Endings...>;
    };

    template<template<auto...> class...Endings>
    using Rail = ProtoRail<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxAGkAA6oCoRODB7evgnJqY4CoeFRLLHxXIF2mA7pQgRMxASZPn7ltpj2%2BQy19QSFkTFxCQp1DU3ZrcM9fcWlAQCUtqhexMjsHASYLIkGGyYAzG4bWzuY%2B4eb20y7B0xeRAB0j/vYANTIBgoKj/fPbx8KLwA8ok4ld0s8TBoAILDYheBwvCxhdAWJjIADWkKhJgA7FZoS9CS8jpdrudjldTjc7qhvr93kxPt9sAx8EYFBCCUTYfCCC9lMRUEQAEpMOhYokvXH4qGSyUkk5nBWUs63B5PPavBlMx5CTAARy8jFWHM1ErlhK8qSML1FdClewAIkCQcQwQIznrDcbMF9HqQXiy2cA/T8zXsZZLcY79jLzYTlWTE1S3GraRqtf9maywiHObKiVbc7axbQHc6BULUHbaGcg7nQxCI1jo7GW9CAPQAKh7vb7Hax3Z7ABVsEJh72B52%2BzOu1PsdDzHswu8vFgHW40AxVokCKbsO2ocnVTS6WboTyEV6APoaNuL6HH6nqsMHi8EOFXg3Xrj3hdHi5FWfdNXyxS8%2BRvMw/yxJ9U1PDMwI/XkXhvPZoMfQCVQOWC0zPTNGUbc8YSQhFgVBTp0KhIsbSELxElyTB0GFX0vFoPl9mdMi3Qog5IIDVD%2BO/DRBP1H8mzjDCKSTTCyVwjM/gI74oWIPMiOo4AXgAWUwOoqC8bdOnLRFkVRDEzi490GHzEAQBrT0hJEsSiJsuyDmUkM8Mo9TbRYtijO03T9OqD1eO/MxHLQ8MJOIsFkGvAi4gICBhnQGyFFYTB4tNNxmIUViCH4uiGKY3yCGeOZYw4BZaE4ABWXg/G4XhUE4NxrGsF4FCWFZMClMw9h4UgCE0KqFnREBaske4NEkLgcT2DRao0MwADYVrMAAODb9E4SReBYCQNGExqtFIFqOF4BQQGE4aOC0BY4FgGBEBAJYCESO5yEoNAtjoOIIgyzhVA2laAFoVskF5gGQZAXike4zF4RjCBIPBUq4GRBBEMR2CkTH5CUNQRtIXQMYAdzdRJOB4aq6oa4nzsBO4Pr5VAqBeYGwYhqGYbhqazBeCAPF%2B%2BhiD6ga5l4W77tICAkB%2BxI/rICgIAVpWQGAKRwpoNi4iuiBomJ6IwnqABPaneGN5hiFNwFom0KpbsGn62EEQEGFoc27t4LBoi8YBU1oWgrqa0gsBYQxgHEb2w7wYhHbwAA3X1icwVQqjuNZBrCDYapj2g8GiN0bY8LBiY/PADtD5PiGiFJMEdTZI4LowRoWKgDBDAA1PBMDJsjGsG/gsdEcQ8eHgmVHUGPSf0SOUHayx9ELq7IAWVBd3SEPQZSjjTEsawzFO1Aa%2BINGU7XtoOnSFxWTGFoglZaYBjKJIUjSAR770XIP4YZ%2BSkGBjSowUugjEaJ4ZoehgGdG6A0f%2BswgFgK/ogqYYR%2BgALKAsLqyxVgSFphweqpATrNU4BzEG4NIbQ1hvDAWEBcAozFkuLgkshptwWAgTATAsDxAgGNEAkg9j3H8HsHEkgZpmEkCtI6tUVqBDzntUgB0Br3BWlwFaG1/AbTUZNLgtVhErSIQzTgl1rqsO9g9Z6ctXrM0%2BirNWosAZsE4PUFgiccSgyYApG05R7hcGmkjfARAz7o3xtjMe0gJ6KCnsTXQ4UKZMCpk1fBhDiFnU4Ezd6dwXhsxeC4txHivEaR8X4jQgthaK1FuLMwLDpZVVlvLVAIs4hfVVo0ipgw8nuIZEYcoXBhI6w2MQfWhsY5WzNhbUgYybZ2wdg4CZLtGAEHdp7Ymvt/aB2DhM8Ozc1inXwPHaoycQ6nTThnDYEyc7tGJgXIuZtS67KlmfKug0a51yUI3CORgW6gHMXwTuCge59wHhMieYTcYRNkFEomM8QDhQMK3feVgl43NXrws6m8BDb13k6RFh9j6n3PqirB7QE7OAgK4ZBj90DwMAW/PI6RKU/06DS1%2B0CahIIgeMK%2BpLQGoKKC/KBHKsgP0mHAtBMxAFYO6rg5hO0CH0xjudXJxBXHuM8d0op/hfHTUFvQoJ4tmFSzYaQDhXDBhovkftEAewtUzRxHonE81JASIhhjVJ50TE3TbrLSxSA3osxafY/6gMOAuO5iwBQidYaJx8ScYYASGFoz0KC0e4L8ZQunqdXQexSDxMSTTOVKSjEcAySzbJ7Mw2QwjVGl4MatVxr5ELNpStxZ7Bqd6qxQblbfWbaLEAUb6LXjrdeBt8UVUQz4HQQZwyjYmxthMqZtt7aO3mY012SyPZez2ZgP2AcxCbNDtsr5DzY4HMcEc1O6dkCZwuYIK5%2BdC7F1Nvc8uTyJmvPrh85uuZvUdyYN3Xu/cQSD14CmnGEgIWCAzTE61c8EWLxsCi%2BA68MUMBDh2FKC8D6WCPs1AlWAiXcpAbfdwnKH4hHFQKjGTKGVke/u/ZllGMFQJJSA2B4DhUsevgIdjLLBU9EpaK3oTGEFSpwbjZJCrj6kMrS8at0bY2UmGLqwJJADXtvMewzh3DKD4IUQdMwWq9h7FqktWaR1jM4nUYYxVxjbCmNqXMPhkhapCNqhtVa/hJD%2BHmiIrgOa857CkyQi6Zj7r4MRjZ6ToXHMLBrqkZwkggA)

## Links

- [source code](../../../../conceptrodon/raillivore/bind_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/bind_back.test.hpp)
