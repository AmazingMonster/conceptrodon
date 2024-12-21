<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::ClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-classic-plume">To Index</a></p>

## Description

`Varybivore::ClassicPlume` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into sequences via a process similar to pack expansion;
then, it collects the type result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;::type, Transf<sub>1</sub>&lt;V&gt;::type, ..., Transf<sub>n</sub>&lt;V&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::type, Transf&lt;V<sub>1</sub>&gt;::type, ..., Transf&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume
 :: auto... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<auto>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::ClassicPlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto I>
struct ZeroStar
{ using type = std::integral_constant<int, I>; };

template<auto I>
struct OneStar
{ using type = std::integral_constant<int, I>*; };

template<auto I>
struct TwoStars
{ using type = std::integral_constant<int, I>**; };

template<typename...>
struct Operation;

using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

using Result = ClassicPlume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

using Result_1 = ClassicPlume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

using Result_2 = ClassicPlume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct ClassicPlume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct ClassicPlume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variable>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEEmbSAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJtpj2xQxCBEzEBDk%2BfkG19VlNLQSl0XEJSdIKza3teV3j/YPllaMAlLaoXsTI7BwEmCwpBjsm/m5MXkQAdJcAai14TLH0CkfYJhoAguPEXg4A1G4GCgyyGUuUwrzeJgA7FZ3j84T8APQIn4AWS8tEc%2B0wPxuxDuD0wT1h8KRqPRmPoPyEmAAjl5GJsiW94T8dnsDmDjmz9kxDsdThdLs8fsgAQpLucPAo2I5kE9/C9iXDPt8CD9lMRUEQAEpMOg/cEsqEWA1Klms3Y8vlubkco42gCeKUYrEwEuFoqYgJ%2BAHlncReVlnobzcqCF9fgARTDNOgh0PG%2BOh%2BFeDJGVlO7FHSO%2B/2BgT2giZ5hsP7pGV4OX23H4x7PEAgIvO90Ko4w5nJqGRtvgpMs228zk2y12rnF10t7AisUSt7AYiYXaMAjyxUd0OpiLAH7a1BMdAG/w56Ox2j2ucLpeCcVChUNpuc9tGyHd/ztpOktEYvBYnG3e51mapI%2BpEVK0vSDCbEmA7WjBQ4Cqgk7Tl6ChltKMaVsGZoqr8GpaqgupxscUoVqYrZmsaprruacGFiOg6FuObBIZ63p%2Bgk%2BYMFh1EsjhaonnqZ5ms%2BT7Jiym7pg%2Bh45uxAYNIxzoltiJEYWRbg1gBhL1o2maTj2wnwl2%2BkQgZcK0Vy9GwUxbq3lOrE3ucF6Lmw17cWJEnbru%2B7ST8AlEW4TlXiuk73pmxnPq%2B75muZw7sgx/JnIhtnIYCEoqbKq5Jh5O6CT5eE6oJ9rpZWDnBm%2BvYvsZ4IxQhf54pp3F8X8YqViCPhDhpBLcYmQHIiB2KdfQH7Il%2BFLYtSdIMlp0WWUONWJSxM6XMVVbkdRTX5QRuVJpRfbwjFB3WYtKG5hx8lrWJTV%2BUJPGGdCe0bmm25Sdmp1yUGY6Ka6aGkfK6n/l1d46c2tnhZ2lXle8D0WnFsGzQpLrMcl9mzvOznLplpk/NlXkHq913nmjQWlUDD5g3CRmQyZ1EHfDCWCucHpLZK5aqZj1E49tR7qpqBX%2BStJMvFTlNRW8CIAFSS1L0sIuCEuSwAKtgQgK1LsvvPL0sy72UNmP4ESil4WCHm4aCQZgKQrt17zzUQPwAJKNeGqo/AAWgkqB9MQFUmtlL3c%2BM6ANhEOzzmIAD6ZuzII9oh6QDtlSaIs628tuoAna1Nf1Xs%2B9jT0Zs6PmB8HgiYGHtCRwI0cELHgjx47Cri22BoQ6LacZ2uTUKwA7p7ExMpRfuZkXBBByAIdlwGFdR80MfHHHHeS83ydQzbdOOl9SOM5nzu/LJnFVRryIK4SaoaCn2VCF4KSFJg6DaoS5I%2Bfv8lQ8cSbF%2BPpfl5XDDV7XBB47nwVKQD%2Bo8S6hynr/f%2B8864/GAdgcWoDsLgK/pAiOM9DA11gYA%2BBzwl5vyFqLHGj8MQ%2BX%2BChVqoJ7QIPBA2QiZ5jju01F7eO2cJjxx7n3Fo7N6F7nQPaF%2BH0iEp1mLKcOKEEgEAgJ/BQroJF/Qfgock8cr433SHfJR5JnhLEPmLY%2Bp8fhcAvvnNRt976kIIOHLgz88yvwhO/FBY8J4/0wXPNwC8EFILAc47%2BUC3HYI8XA4xjdkHrVQS4/xVdZ6BIXmYfBvZWzC3eCQ5RGJrHkJasCahxwNDxy4PHeJa16GFWOOwlo3E%2BH7kEXY4ReixGVgUUoVoMjUFyLYAo%2B0Wj0kFKpNfcx3SrEhOwLo5J%2Bifgn3GD8eJq83iX36RoixaSrFmFsWdIMb83A%2BIgZPDB0SsEAKAc8MJvEIl%2BL2X/GJhyjH4JOfCT%2BkSLkwKCbgopiCm6EL0ak8k4dVmvQoYCKh7UaH5MKZUkADD7TMO4WQX0kRWETN7l7XhEL%2BE1PWQWJJosGnICaVI1pY92mYE6ccQZvzVELKUEsn5bzRkWA4CsWgnAACsvA/AcC0KQVAnAtmWGsD8BQawNhZj1jwUgBBNAMpWAAaxAMyyQ5wNCSC4JCfwGhmUaDMIEQIZgAAcur9CcEkLwFgEgNB5PZZy7lHBeAKBAHkiVHKGWkDgLAGAiAQBrAICkM45BKBoD2HQBIURXScFULqwIABaQIkgfjAGQMgIxCqzC8DvoQEgeAg4FP4IIEQYh2BSBkIIRQKh1BOtILoAp3cAwpE4DwRlLK2WSq5ZwH0ZwfVqlQFQH44ao0xrjQmpN5xVkQA8IG%2BgxADSiqWLwR1WgVgQCQAGlIQayAUAgMu1dIBgBSDMHwOgOxiB2ogLEZtsQIgtAdHW3g57mDEAdD6WI2hMAOGvaQANLkCAgVoFe8tWBYheGACcWgtA7XcF4FgFghhgDiD/XgBcDg8AADdCTNswKoF9Zwthionky8ttA8CxADPejwWBm3hjwKa8DpAUPEFiBo6MUGjAEaMJKlYVADDAAUFcPAmBu7sXZWKnNwhRDiELcJktahm2Vv0NBlA1hrD6EI3ayAKxUCWyyGByNgdsymD5ZYMwVraN4iwCpiAKw7AvoaC4Bg7hPAdD0GECIQwKgjAKYUTIAgph%2BHc%2BkTzDB5jDCqN0KzvQJhtHs3kAplnEMCC9gMZzCw3O2HC95vQsxWiBdc1UCzQrNgSAbRwVlpBLW8GtT2iN0bY3xsTVIYdPwIC4HTZO8w/guAzvFWxlYCBMD7hGOZ0gsrJD%2BHOAATn8JCSQSrkiBHNcywIo3DUcGNaQU1bXziBC4IEXVo3dVbflVwZl43gilZbTa2w9rOtOoXe6xdnr22%2BvXZuidIa2CcBaCwJDkJI1MGQumLgo3zhcEVam/ARATN6GE3msT0gJNKCk%2BW3Qe7q1MFreBwrxXTvWrbd6s4Pwu0/A%2B19n7f3twA6B4qhrY6V0Tqnf4MwHW53Oru89hIfqN2oHHSMIn33PRGAB1wPJNAMQJGPae8tt7L1vsl/ex9z7X3UY/cub9v7OX/sA8B0Db7IPQdg2r%2BDoWUNgc5ehzDOw324ebQRojl7SNbE5RRqjYraP0aUIx3XW42N8E49x3j/HFJvqh6JgtsPZCSbLZypHsnWN6asJYJTsQzNqY01XTg2nR66YUwZozCQTOodUyF2LfgICuDSwUpzZQgt6A8w0MvpAa9ZCy4saLdRQtxdS5FnzheGjxab8ljLEXchd4H33nLqx1j5fa0tzHzbys85J3zsngPgcaAa018HdP2uzq66QHrfXEgDbwyttbgOlWQiO5CVVkgZvKpK7PzgtrLtM5u/AO7XqO3s9Z8QV7WwPv9pYAoEhomkhuThyOMKDs1pmpDrINDiHkWvIPDhHjoAEKQCjmjvWtPk2uWtjg9p2t2n/rGgAUAT8CAYDmAWqKOpzjTgkHTv4Izl7izlQaup/kwROiAEATfOHKQeHOQRIsQCwDGvuiLkepQOLpyjLr%2BmKhIXLlZm%2BkroICrs2urkBmIFrtRjrsxvbhBgbohkbmhhhsgFhhbqXHhpytbsRg6HbuRniE7rwC7gxrsB7qxtdt7kwFxjxnxgJoHjAcHhIKHsWogdJigQYDHlnjYNbknlyinn/JwAiMXLHtYIZmVsZpmvngNjFtZiXrZnXhXi5s3vXn5rXp3tXoUY3ollXi3j0O3v0HXhkWFnMOUdlulh3kPs0Q0ZXk0VPoKhPgWhjlgVapwITvwf/oAcAaAYOFMo1mDiQJvvQddt1r1lgAfoVsfiAGYIDv4P4MyhqsquapsZCNtnftgQ/hdg6jvkNsymNsyrqlqqNpIKNqqhNlwP4Etv4P0WVicc/oVimkcQMedl8TRqLlkCAJIEAA)

## Links

- [source code](../../../../conceptrodon/varybivore/classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/classic_plume.test.hpp)
