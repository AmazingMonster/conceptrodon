<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::KindredRepack`

<p style='text-align: right;'><a href="../../../index.md#list-modifications">To Index</a></p>

## Description

`Cotanivore::KindredRepack` accepts a list of packed containers and returns a function.
When invoked by an operation, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Container<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Container<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Container<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Operation
-> Operation&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack :: typename... -> template<typename...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<typename...> class>
    using UniRoad = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

using SupposedResult = Container<int, float, float*, double>;

using Result = KindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<Container>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::KindredRepack` is implemented similarly to [`Cotanivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Capsule`. After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<typename...>
struct Capsule;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<typename...> class Container, typename...Elements>
struct KindredRepack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct KindredRepack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM1ykrgAyeAyYAHI%2BAEaYxCCSgQAOqAqETgwe3r7%2ByanpAqHhUSyx8Ym2mPaOAkIETMQEWT5%2BAZXVGXUNBEWRMXEJgQr1jc05bcPdvSVlgwCUtqhexMjsHASYLEkGGyYAzG4EAJ5JjKyYAHRX%2B9gmGgCCw8ReDgDUbkxJCl70%2B1YPd3uGy2O0w%2B0OJzObCuFxugKeLwIrwA0mF0MRMOgAEqYJJMZAAa1eJgA7FYSQARP6AwEAelprwsTCU72Z7BpD2B2yYuwOXNB4OOp2Y0Oue2wr2QBgUCnesiYYTipFeQqhlyu2HobEECjhDwRb1RDHRmJxeMJ4I8ggV4WI4M1m0YBAUMLh4ppZMBr29Ks23N5hz9Ar5kJF6th4sl0tlAHlTsQeRk9fcfa8DUiKZh6nQvT7Sf8U6mfV40kYVZDiXsKa843FEwJ7VqnS6xbc9gXU6Sqe2OYXvfyeWC%2BUHB4LQ%2BdXZGpcyWxd7sAMY6dcnUyWwsBXljUEx0JXq5ns7RwfPF9rnZPsCAQKrqQDKbf7nSGTjkMs0gA3TCspQgXsD3YAgcub9iOAaqmGF5RjOcrWoqxD3KQwG%2BiCo4hsKE6tlBMowdmto2Eh4EYRcDpno8yoEeOorEU2ggWAoiEPKmhFUTGBAIHEuqAbc%2BoEM8hpohi2K4viBKWvKcGPgcJFOo8F7KlauFxFYUk0QQdFyTWbEcReHodj6/5DoGKFgZR4Y3FhsbxvWDArj66avAeCpHoxeaei5RavGuZaqnuKICaawkWu5RbgkhHneh8Xw/IZ0mCLJVzKrFamzjcDF9uF3qsexxApcFnbileBmbtu6DgrWCY1DZ7o9sFXYPgRoGGQZY7oVR5nTjKMInpgS7OrZ3peRuW47r5jk5gc3W9SlBXXpC9X3jVj4PLSABUa3rRtm20nSG2vAAKpgwyyht23LZt50nb25h7GEUpeFglaHF42xDtxS1Ao1LVql1xDALq7oPBiACOXh4BisoQGkABemCoFQMIQPcv0KHMe77NWkhzPCvGIjhNpxPVDyDa8QjPSkShCd8tBIujeNweCYQEMqVC0NuTOvCzbMrcq6BLNEvzVQWgLEziVM01WfnGoJZoiTSQHBcM6CFc9AtuIzqXEgrBBK9eKuGZzPLM6zPIralSGK8rL3grzXj869cuXiAw2lQcCn43agu9pMjjIAA%2BjOcQEJD2tXgo5z%2B/9biiz87Ok0k5MBWLNxY%2B2HALLQnAAKy8H4HBaKQqCcG41jWGmSwrF%2B108KQBCaGnCwEiAmeSBcGiJCSewaJnGhmAAbL3ZgAByD/onCSLwLASBoGikLn%2BeFxwvAKCAM%2B13naekHAsAwIgIBLAQSReEzFAQGgWx0HEETnJwqiD73AC0veSK8wDIMgrxSBcZi8JihAkHgStAj8EECIMQ7ApAyEEIoFQ6h16kF0IEAA7gmJInAeDpyzjnOuBdOAxiPofJEcNXi3wfk/F%2Bb8P4tzMK8CAHhz70GIMSMwewuBzF4GvLQCwIBIDPkkC%2BZAT68P4SAYAUgzB8DoBsHKlBojYOiGEBoRw0G8HkcwYgRwYzRG0JgBwyjSBnzPDGBgtAlFwKwNELwwAPi0FoMvbgvAsAsEMMAcQZiwY6McJ%2BOx%2BdMCqB0UfNY1dGZVGwbQPA0QEzqI8FgbBvE8CT3saQT8xBoipEwJmJxRgwlGDrgsFmTA/oADU8CYEQbWXO1dgHCFEOICBVToFqGwQg/QziUAl0sPocJy9IALFQEkSqdj76K3RqYSw1gzDz2ScQABh14ALDsB4jILhjRjD8IEEIioZgDDyGkSqqy9DkwKAwaY/R4hDCqIs2oIwmieBaHoBZDhOjXJOaUbZthrn7KGM8zZpyJDzPLqsP5o8ODZ1ntghexC76P2fq/d%2Bn9qEQFwH/RhVc2E11yQsdiO4BgQAbgkPYFwACcewSSSDbmYSQvdp6Z17oS4F49SCTxYRcXuXBe6D0JYPNlzcuCZ2Jb3MFcCF5LxXui9eXCd7cL3vgo%2B5BKBCIYVfNgnAGgsHfCSe%2BTAoJli4ISi4XBW4/3wEQaZgDIHVLARIaQ9SlCNLgbocRyDPjKIwSCrBQrcEysIVQV4qr1Wau1RuXV%2BrW40LoXwhhTC9hmDRRwjeUqFVKkEagehAw/UaunEYXVXAZ40GphxGRciFHqL0aoxRmjtG6MSQYp0RiTHYPMZY6xti9GOOca4/O%2BAMSPK8dg3x/iNh6OCRnOBYSImKOiWsfOcSEnV2SakpQGT23rlyXwAwRSSllOFHoqpoDanWtkA02B%2BcHUtJyaMqwHSx3dNxQXfpGRBnDKrBe8Zky4imtmT09oly/AQFcJ8oIxoXmzB2UcgDhzKrAbeQ8yqXRRi3JyOcjoVypg/NeWc953QAOTEaFBs5/zliAtYcC0Fc9eAQvTQGzNQa9UGo0DQpFJqo2sPYRi0gWKsDxFvSOhlTK9VtxJHykkHdJAUqfoEMjODF62FFXGiV8ApX7wIXK0%2BKaI2X2vhwVVZCWAKHfO/d8wbQTDCNcigBehd01PAQeqBtrj06BAHsUgTrUH2NdaR8FnqD5H1eEQ7Tz9dP6deIZvVxmkS0LU/wqNexY2roTZFhhKnE3xH0/HX2IXfZhf9sQFgT8JH5ukRAWRcCy0lsSaVjRWiPF6JrYIOtpjO2YAsVYsQLbEltqyVOhx7ie2zLgf218g7EnDtCeEyJRxJ2xOmbO3g860lLqySu8Va6CkKGKaU8pO7ZB7us%2Bao9TTHNnuMO0mw165l3oGZwWkFsX2WAmeRqZMyb3zIuY85wf6VkIbWYB9AeGDn5D2V9/7uyMh/aQz%2BuDNzsjfZg081DxRflfKw0DpHuG0MgYIxXIFI6PMeo4L6nLOm9MGaM4OYYDHjUkGY7F8VmLMDYq4663j/g9V7D2JnbuiRp5s5JOywV89OAitXmxxukhM5EszoPPuhLJCEo7iSrgTmR17HdQL6TcnXXf35%2BRwXYrOELGSWkZwkggA)

## Links

- [source code](../../../../conceptrodon/descend/cotanivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/cotanivore/kindred_repack.test.hpp)
