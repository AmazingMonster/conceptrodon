<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::BindFront`

## Description

`Roadrivore::BindFront` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function adds the containers to the beginning of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Containers...
-> Operation&lt;Containers..., *&gt;</code></pre>

## Type Signature

```Haskell
BindFront ::   template<template<typename...> class...> class... 
            -> template<typename...> class...
            -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct BindFront
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will bind `Con_0` and `Con_1` to the front of `Operation`.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...>
struct Operation;

using SupposedResult = Operation<Con_0, Con_1, Con_2, Con_3>;

template<template<typename...> class...Args>
using Metafunction = BindFront<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

using Result = Metafunction<Con_2, Con_3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

While this is possibly one of the most useful metafunctions, its implementation is straightforward. The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct BindFront
{
    template<template<typename...> class...Beginnings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Beginnings..., Containers...>;
    };

    template<template<typename...> class...Beginnings>
    using Road = ProtoRoad<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmGqQADqgKhE4MHt6%2BekkpjgJBIeEsUTFxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRsfEKtfWNWS2Dnd1FJf0AlLaoXsTI7BwEmCwJBmsmAMxuaxtbmLv765tM23sEAJ4JjKyYAHTPu9gA1MgGCgrPj68fXwUbwA8ndiBc0q8TBoAIKDYheBxvCzBdAAMWIsmhMJMAHYrLC3kS3gdzpdTocLscrrd7mxfv9Pkxvr8LJhgMEGMFgAooYTifDEQQ3spMUQAEqoJjobHEt54gkwuVy0lHE6qqnq2nMekvHbvJks54eQRMYLRXn62XKoleFJGN6S6XynYAERBYIhAhObI5DC5Rh%2Bz1IbxNtXNxCDfytO0Vcrxrt2iutRI15LT1P22oeDP1AOZUd9nO5luwKbedu5jql6Bd7tFqAlNZ97OLgdzZdj2ITSe7sIA9AAqYcj0f97FD4cAFWwQinI/HA9Hy8Hi5xsPMO2Cny8WBdbjQDGWCQIpb7MIzWruOqeerLsMFSJNAH0NL2N7DLzTrzm79jH8KL5cO%2B64XmcarfnSt7RvecIEAiT4CM%2BZggdiX5Zj%2Buowf%2B8FCqGSE7Khn7gZqVwkem2ZYYygIdjhCHCqC0RegwREwpWDpCF4CQ5Jg6DipgCheLQwq7O6jHglUJwvvE%2BEMM%2BLSychIYvoRMbJsRlLpuRmY3Jh0HUQWvwwsQPJ8mx9rAG8ACymC1FQXhHlUdbIqiGJYns4nMWZIAgE6Mp7NJylIcBVqwj5fknMZPK0V2H7mVW/GCcJzk2XZDkOJCAVIWYQVyapnbqXBELIM%2BBbRAQECDOgPkKA8pWWm4iVCQQIacdxyS8U1wmvDMSYcHMtCcAArLwfjcLwqCcG41jWG8CgLEsmDymYOw8KQBCaP1cwANYgENkiPBokhcLiOwaENGhmAAbFdZgABx3fonCSLwLASBo8RjVopCTRwvAKCA8QbRwWhzHAsAwIgIALAQCReC1FAQGgGx0NEoQPJwqh3VdAC0V2SG8wDIMgbxSI8Zi8LxhAkHg1UtPwggiGI7BSDIgiKCo6ggzoegAO7ggknA8ANw2jZtP2cMC8Nw8KqBUG8WO4/jhPE6TB1mG8EAeCj9DEMtq0zLwwOg6QEBIMjCSo2QiMW1bIDAFIOU0MJFqUBE4sRMEdTXELvCe8wxDXMCETaJgDi%2B6QyNsIIwIMLQPvc6QWARF4wBuGItAA%2BNSfrIYwDiIn%2BDEGHjgAG4CeLmCqGH8MrGtwRrINie0HgETgoHHhYOL8F4G92fl8QEQda6udGC3RibXMVAGDyABqeCYLzjFjWtDPCKI4is2vHNqOLugtAYE%2BmJY1j6K3AOQHMqAnmkWc41VonH1YlhxBNA/ELTFeX60JdpC4DDuE8E0fwADJi9BiC0HIqQBAjGaIkZI0CGBgOKH0MYFRf4CA6MMIBowf4ZUwUMLo5opioNsIQ2Behxj1GQdMLgcx5qLGWBIEWHARqkC%2BhNTgCtsZ4wJkTEmZMNYQFwNTPWm46FG0nnMBAmBpR9AgDtEAkgdiPAAJw7FxJII6ZhJBXQ%2BkNK6qinocBeqQN6q1HhXS4FdO6qi7rWP2lwIa6irrsPFr9f6gN1qT1NpDM20Npbw3IJQW2ut0ZsE4HUFgpdcQ4yYPmB0XBVGPC4IdSm%2BAiAfzpmzdezMJDSG3koXeiddA5X5kwQW40WFsI4RLDgUtYbwzeHLN4USYlxISZZJJKTDqa21pbXW%2BszCG28dzMG5tUA62iMEpGkyBl9DabEpkRgklcHiM7NYkY3Yey9oHCO/tvbB1DuHbOUdGAEFjvHcWydU7p1oJnCOWAWB5wLt9Iuv9y5Z2%2BlXGuawI4NwqOLFubdvadxWN9Hufc1oDyHkoEezyx7ch8dPJgc8F5L2vBHNeTNN4FNkDvLm31Sn6DzigGalgz4RAvgon6N8BB3wfm6J%2B1hX4/Xfp/al9D0H4L8BAVwFCWiBGIeA7ICCqgCvgbkNINDSF2AwdUchOC4Fyp5VgohhQRVjEVZkZVhCZUQPoQtJhdDjE1PcVwxZHTlldOSakjQmsRGZP1hI0ZoNpGyKwDEGlTdTHmOSUdXEzjcSnUkDo/GLRakeNsF442/VfHwH8TDGWMzQlowxhwKJysWAKFLiTUu3SjiDHSaI2mehsUbxZni9mRTCU8x2KQcplThamrFonX6DSZbNPlpmgm2bc1vHzckwtwotZzKtvrHYIzY3jJQGO3WKa519FzdxZ8g7nzDtKsQFg%2BM%2BB0E2QDCA7tE4HL2dnE9QcQ4lwjmcmOccE5vMwCnNOGcs5rSeS88FvB3kZU%2BZXauyBa7/MEIC5urd27XDBd3D%2BULeAwuHqPfOSKxl8Bngoeei9l5YtkDiytOSCV7xAPWw%2BxhyU2GBZy2lVQs79iqmSk%2BL9vqoHZVgCjKqqj/0ATqkB6B9WiqlTApVfHEG8bQW0AhnQJVsfaHq4VKCIFkIk4JrVExZO0MNYwlm1TW2MYtVurNOa80FqpIMB1GSSDOqnVI0gMi5FepYb62IySdg7CGhdY6H1nO4hsW4ttnBPFAys7tSQQ01FDTutdVRkhVGnQ0VwIjnAdjac4X9V1W1jEUx8zplL065gDxSM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/bind_front.hpp)
- [unit test](../../../../tests/unit/roadrivore/bind_front.test.hpp)
