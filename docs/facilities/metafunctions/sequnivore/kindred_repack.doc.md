<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-kindred-repack">To Index</a></p>

## Description

`Sequnivore::KindredRepack` accepts a list of packed sequences and returns a function.
When invoked by an operation, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::KindredRepack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<0, 1, 2, 3>;

/**** Result ****/
using Result = KindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::KindredRepack` is implemented similarly to [`Sequnivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJmAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhugsFRIdh/uZgQxQV5wZC3F5HLRCABPRHIj67C5CBA4gj0V47X4ETAsRIGelYpg41AAOi5RNOw2IXgcZIpBCpmEhVlO/0%2B3xl21%2B0ouAElGfQ2IImDUaXKpbLdYdiWdSQBpYLoYiYdAAJVuTGQAGstfrTvSVRqxVCCPi7sw2FyOTyTnyBQQLiaGGaLdbEraHSYAOxWONXcUG9brC4WJhKC5uLPsA0uplurGF5nu3Psv2Ii6grMvISYACOXgemFIFzZRD9ADUGngmBF6AoA0HBWGI1abfasQ3m62sb3iP3B88q4CkevkQn/hddxdS8WPQyiyyoZ3Odz1zWDAoXgB5O7EDXpAN7i6jkM3ep0Hd7%2BMSk43zfLxUiMfcvUwCFASuC4H2iZ8BAXPsByHNcNwAt942TQEAN/XcD1PNwCPLc80OvOs/ROYBzQZRgCGHTdTmA0DgAuS1UCYdAoJgr8mB/KEqJotV6LQkAQE9O4U0lJMpL%2BZ1jzLEsFMPIiIJ9NsO0rS9sHI28ySbFs0Q0iTGFYSCABUIPbUiuUXZchxHAh%2BTHU1zUnaNpyhWdDNWLFLLuds7JQ1dtIDf88P3ZTCOI1ktP9K9az0uCnxqV89w/a5MG/WgIvCpigN3EDglYkzuNgx8EIYCLMKhSZHGQAB9URhixWExJYJg7UwBrUmAEJ0AaghWrwAAvbqhs3dcICClcFDmNDZMwmScINN8YqPV1CJs%2BKdMShRKOozBaMEBikXywqWLYjiuMhHisr4nKBMO46RO0sSTNkrDPo%2BdNrWQZZUgAN0g3MlBAAsorFSUoQi9aKy7bTdPrAzWxOUhYch2KEZ2pH9LnIybAi7aZvoQN2yJuKScwCwFHR87wO9My/TvAgEGiYdobOwMnODUNXMjKc7RnFGjL%2BKEqcDND2281srHF5CVxpqXYNZ9mFukjC9zhuHturPbyvg1LGMA9KecFXif3pvKTYKoqwNK26%2BfDNyoxjaq/xh%2BmCt3clKXoJCl2CyWuUChX6CV7S6Zt73dxZtniH27kvY97B3shq7OKxZLKqJFareW3D6e1zGzzivWb0TjlBKO4TToiu3WPYziyotx63Grl7K8Rd6IM%2BguIc2qGxbcDHB5LNSzOssuEorvGfMwNHR5PcsTPUqfsfLus59lqO1ontgLnMxei/3izCfp4mw4X2mIQvymr5p3etdP5nVYT5FjYy8cXcF4X8dWYeR9Q6BxXMHHa0sRarDlm4cyNgLhUwjuAlW8cu7G2tmtEuRFMG6xnlvbORsuZvgyq3XK25k4XWKgzSCjtv4Cw8kLchUER6MKIQQdAYlgj0mANEHqkCh4xxqsw6OAjTbsJAB1LqPU8B9QtINVqbCxKpDGnI9cT8RGsOfI1ZqE03BtXEZ1bqvV%2BoqN0QokASjxq52wNNK%2BgZ5oh3diIuqeAtFZh0XoiRhjpHGPcWYixKiNzWIQXNKsLCU5qIEXHNWSdhEpzToPDO6As4VQIYtP8/dJRF0wTraeu0K4HSEnROu9MG6JJbvdfi7dnq11EuJXuec/gZLkoaPUtIdSXGwKoVgTJIJvHaa0p0zSFShEwAAd27M8Owjo6SYI8QYqRMiBq%2BLEf4ia2BKLEGAMUk45pmx4HNC8CAFjUBUD9BAHZWy5jcUdpIOY/wMojPGZMqo30WnbDJF4RIuQBYKC8LQEMfTTilKEJ875k5fn/LKo8iZt4XlQg0O2NoFwzDtkBLnQubzNhsWeH8gFbSgWXWtBCkMND%2BbuTdtDIRrCxGcMwNw4gvD/7lk4e2DQiJyb0z0aaTAqhGXzyxEisw7KIpcvDDyvl84oRorQeuMSTcklQmhc8x66FUyknMs8PF2peT1Hqg1Os0QCBHL8WZfVDE3BEtxdLUFKQfm4sRHchp/wOALFoJwAArLwPwHAtCkFQJwEelhrDviWCsahQIeCkAIJoF1Cw7QgHdZIDkGgAAcZh4hxC4O61NKauBxjjNIN1HBJC8BYBIDQCLvW%2Bv9RwXgCgQAIujT6l1pA4CwBgIgEASwCCJBxOQSgaBGR0GiKEMynBVApoAGwAFpJ2SAuMAZAyALhSA5GYXgFpCAkDwOwto/BBAiDEOwKQMhBCKBUOoZtpBdBtFGU%2BRInAeCuo9V6mNfrOB3hxL2kMJyLgTpnXOhdS6V1JrMBcCAHgh30GIBCCNcxeBNq0AsCASBB2JGHWQCgEA0MYZAMAKQKKaD/PZpQCIb6IjBAaPiR9vAKPMGIPiO8ERtCYAcDR0gg7hJ3gYLQajV6sARC8MAXMtBaD1u4LwLAHUjDiH4/s1jjhgbid9Ty1jOI1iRtpUW31eIIhPgYx4LAb6nJ4DLRJ0gwNiARFtTcaTwA8RGBjQsKgBgtndieKMuC3rI37uEKIcQJ7fPnrUG%2Bm9%2BhDDGGsNYfQeAIj1sgAsVAiQajienbCW6pgg2WDMNWyzS4sDxYgAsOwCn0guHDGMVopBAjBD6CUAYbRchpAEJVnIKRmsMGmP0Mo7RSsCC6KMTwLQ9AlYcJ0EYPRaszAa7YCbrWJgTa6/VsoxXQ2rAkM%2BjgnrSBVt4DWv9U7Z3zsXcu1dYGIC4C3TBlEXB4NRqcwsNmnEBhFdIPGyQgIORxEBAWjQkgzCSEnRW91k6EhFpLaQMtgIuAcknVwSdKa4i5snYmrN33J07bfTWutDb7vNuQx2lDXav19qwzh6Do62CcAaCwQGcZp1MHImBLgcQOQw5U/gIg%2BW9C%2BcPQF6QQWlAhavboFFd6mAPok5t7bu330cE/T2nEFxf3/qO0z1iLO2fJvA5B9D0HYOAjMHdxDLaifk%2BiP27DqAoMDFrEYFnXAEVEfpAnUj5HKMMfY3RqjTGWNsfM5xui3HeNvoE0JkTYn2NSYi7J31%2BBzRjaU2%2B1T/16Tsa02%2B3T%2Bn8SGbWL6kzZnI2Wes0oWzMfipOb4K5hQ7mxlefY7z/zx6BeyGC5e31ovwuOcy1YSwMW4vwES8l9IqX0vQR79YHLe28s7ueIP3rY3nAQFcPN6r4YluzEa%2B1moq%2Bms1A3zN0bNQBtNCG%2BMBfx/FtTe6yNubZ%2BquTEaAflbixljrdu/oF9mOr37dV4Bu3GurO7O4Gl2XOBut2CGD2pAT2WAMQr24OpaIAgIrOf2cY7qcQ%2BagI/2gOkgbQsu2OtguOJuBO8ARO3a36lu5uxAlOawNOgGLACggMy6gMmuZYwwG6nO26u6p6fmR6EgLeZ6Qu7eOgSBpA4ukuT6n%2BW2r6P%2BH6JOP6VAf69BjBzBrBbowwOu1ueu0QBugIxuleZuWhGGlBRh0GIATBXyDULBcQDUbBBADUqgc6fAdALu9aEAZGV63unu5mXhjGzGCm7GgeggwefGcemAgmwmYgke5m0eMmeekm8miec%2BV6Ke6m6eggVQmesW2euexmS4hevAxeNmDI5ejm%2BOVeTAbmHm9e5mjefBgWreQhoWohBg3eUWfeumhWQ%2BKWnA6wbUE%2B2WuW0Q%2BWc%2BCWF%2BZWy%2BFW9%2B/g6%2B1%2By2bWeQ6Qu%2B2%2B6Qz%2BI2VQfWtQd%2BWQD%2BGxi%2BWxUwcxm%2Bs23Qq%2Bj%2Bk2RQN%2BH%2BCga2x60uMh1anASh86DBTBFw1hHIdhIBnB12cGkB%2BOj2mAz2cBm2EOZa8QHIgIgI7q2auBFaUJcYCO3%2BjxtahBjaUB727qX2eacYFaKakgmaXAaaZgGORagIDxe2nA/xSGm266yJlJqJxBCwlmqQzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/sequnivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/sequnivore/kindred_repack.test.hpp)
