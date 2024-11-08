<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::Repack`

## Description

`Cotanivore::Repack` concatenates a list of packed containers. The result will be used to invoke an operation.
<pre><code>   ...Container<sub><i>i</i></sub>&lt;Elements<sub><i>i</i></sub>...&gt;...
-> Operation
-> Operation&lt;Elements<sub><i>0</i></sub>..., Elements<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Repack :: typename... -> template<typename...>
```

## Structure

```C++
template<typename...>
struct Repack
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class>
    alias UniRoad = RESULT;
};
```

## Example

Here, we first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

using SupposedResult = Container<int, float, float*, double>;

using Result = Repack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<Container>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::Repack` is implemented similarly to [`Cotanivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Capsule`. After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<typename...>
struct Capsule;

template<typename...>
struct Repack {};

// Base Step:

template<template<typename...> class Container, typename...Elements>
struct Repack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    using UniRoad = Operation<Elements...>;
};

// Recursive Step:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct Repack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    using UniRoad = Repack
    <
        Capsule<ElementAs..., ElementBs...>,
        Others...
    >::template UniRoad<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgMykrgAyeAyYAHI%2BAEaYxCD%2BABykAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxCckKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHASYLCkGeyb%2BbgQAnimMrJgAdPcn2CYaAILjxF4OANRuTCkKXnoJysr2eLz2ByOmBOZ0u1zY91ujzB70%2BBC%2BACVMCkmMgANZfEwAdisRIAIsCwWCAPTUr4WJhKL4NbEgKmvCGHJjHU6cqEwi5XZgIh7%2BbBfZAGBQKH6yJgLMhfQXwu73bD0NiCBTI16o75YnH4mEeQTy8LEGHq/aMAgKRHIsVUklgr6upX7Lk8s4e/m8uHC1VIsUSqUygDyV2I3KyOpebq%2BXgyRi%2BcgYeAxqCY6EJ/jJXwjcWjAktGptdtFT38IJexIpVfZL1pmO6mwyADdMMy9ik2aCOT7udDQacXW6%2BYOBf6bvbg5LGTKTY0FS9SKPXeOvcqAzPxXPpbLTQqbGulVORbcrZqCG9SITXvGt9O1aXBBYFKv72Oz4GwwQEHFtWHJ5dQID59WxXE8WNOVlxLa1BDeHdb0XM04isU5LxtN8kPzP8AJ3J1qwfAdNxI6E/SFJ8g13UN80jIsGFjeNEzCYAUzTDMsxzPMDUgk8YRPeNfn%2BQFyLcTCEPLW5bwkghsIrD843jN1f3/YgpP4sUQBADdO1TdNM3QGECyjOpGMdetQXJSk%2B0bAAqBzHKc6kaUcgAVbAhDcxyXNeaknICuzfJrUEzH8MJJS8LAczOLxDnI4CQvBMjJ0o88XmIYBtUdV5iEwABHLw8DymUIAyAAvTBUCoREIAyrKVm4k480kFYUVAtEDyXc0bKSljkyEOK0iUdAsQBWh0WarrUItU4wgIW8qFoTMFq%2BJaVrs290A2aIgQs6swX6tixsBSbc2bQ0oOHNwT3GdBtIIOK9rcebHlvW6CHunSnrE9buUW5buTst6Pq%2Bx74phbavF2hKqS0kB9M4ozThQhUHQOkDo2QAB9ec4gIMrPu0hQblx7K3BOibb0GlJhswUbMHGghHjaqsODWWhOAAVl4PxuF4VBOBuyxrC%2BBQNi2TtzH8HhSAITR2bWPEQC5yRbg0SQuCJfwNC5jQzAANgNsxEmSTmOEkXgWAkDQNFIPmtFIQWOF4BQQDt%2BWOC0NY4FgGBEBADYCBSLwFooCA0AOOg4giG5OFURIDYAWgNyQvmAZBkC%2BKRbjMXh6cIEg8HurgZEEEQxHYKQy/kJQ1AV0hdFLgB3KMe35jnud5hvnbDUOQ/RaqvgT5PU/TzPs7VswvggDwo/oYhCTCrgVl4T3vdICAkEjlJo7IcOd73kBgCkMw%2BDoPZ1MoaIG%2BiMImnOThZbv5hiHOMNom0bpPdlyOrzDBgtBH5e14FgaIXhgC/FoLQN2/NSBYBYIYYA4gQHwOKt/PAHZYGO0wKoFsewn68HmjUButA8DRCjG/DwWAG6gTwNbOBHZiDRHSJgMk%2BwkFkKMArNYS0mBZQAGp4EwM3AsfNZb8HLqIcQ1dJG1xUOoVBTd9BIJQNYaw%2BhyFu0gGsVAKQzKwKTndZqpgRaWDMI7VATDiDF0ZvANYXQejOAgK4KY7QggMHQIMMoFQ9DDSKNkTwbQ/GFDMt44Y8RS6OLMn0SYQTpjVFqL0OY4SliRNmP0Nxehxj9FSb4le6xNjbAkJ3DgPN7Y904MPROKc04ZyzjnaeEBcCF0XtLFea8eFrH/FmEYEAlYgEkP4W4ABOfwRJJAazMJIA2tsuYGxGfoTgltSDWxlrcA2XADaJBGYkLZqsuBczGQbCpqDnau3dnLHhm9/Zb0Dv3UO5BKCHwXrHNgnAmgsDbESJOTAQxIOziM24XB1b53wEQGxJca4VxkdIORigFEN10GfVufxCGlPKQ7AWnA%2B7B1Dl8Ienzvm/P%2BcmLgQKQUaBnnPXeC8l7%2BDMKvK5ICfbb1QPPOITyI7stpSMIlPy5xGHJVwO2NAJoAWvrfe%2Bb9CGkBfg/D%2BX8HCyr/jaABQCG5gIgVAmBsqEGcJ2I7fAeUehYIbrg/BOxZbEPNo7MhFCH7UMNWvGxDDZZMJYUodhiCjBcNACyvgBhBHCNEUKWVciYVVzhbIBF9clEgDPgYbhpirCWE0dEbR/Snb6KyIY4xuYU3WAsQLaxtjM0OJqBg5xrj4nuJCAsHxIxS7%2BLMlk5toSsh5KbYkqtDBYktFrdkytTi%2B0pIbRE7Jcw20ZOaF2yJDiJbFIKebTFlSOBfH5SSwVbFyXAvVjPFpEL6UdOZd7bpmBenxCzebFZaygUayJEcok2tJDTNTqXLFTtOAXI9tc32Acg4Dy5S8mOccOCfLHiwBQbYs5tl3VCcYYLWnFz0BG6RUaa6xsUY7XQgRUXtx4Bi7uZycUPMHlQDdxAWCQeg7B%2BDg5xjUp5Xvel/gmXr3ZpvNlHL97POYwvEAMHabYzgyM7GCGCC4yo6nc%2B4qr4QBvqg%2BVMq4HKffp/b%2BKr2X/0AcAo1mBwGQLELquB%2BrfXOrQSaxwZrUEWuQKHK1RDBAkNQfayh5wnW0NdbKj1rDvWcNYtcvhwaRFiPDbISNEho2CCw0ihIKjk3qLTfa8t2aDGcGpHdNRZiLDFqdqWrAqXolZBcJ46d9bSgTvbRkVtg7qsBLnUOpJ9Qp11Z7SO/tjWomtdyO4nJs7x1pJKYUyWw2V3EcsVUiDacoMwa%2BKJ24EmD3gpIMe9jXTSA9KwFe0pt6E1Av8P4LmetNa20O0SbZpzJsu1sJcjjKwBmSC5qMrmiRDYjMkCM7W4yZjm38BN7FN37ulLzldwHnSWVrCYRkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/descend/cotanivore/repack.hpp)
- [unit test](../../../../tests/unit/cotanivore/repack.test.hpp)
