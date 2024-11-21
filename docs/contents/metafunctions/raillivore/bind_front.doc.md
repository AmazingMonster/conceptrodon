<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindFront`

## Description

`Raillivore::BindFront` accepts an operation.
Its first layer accepts a list of sequences and returns a function.
When invoked, the function adds the sequences to the beginning of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Sequences...
-> Operation&lt;Sequences..., *&gt;</code></pre>

## Type Signature

```Haskell
BindFront ::   template<template<auto...> class...> class... 
            -> template<auto...> class...
            -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindFront
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

We will bind `Seq_0` and `Seq_1` to the front of `Operation`.

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

using SupposedResult = Operation<Seq_0, Seq_1, Seq_2, Seq_3>;

template<template<auto...> class...Args>
using Metafunction = BindFront<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

using Result = Metafunction<Seq_2, Seq_3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

While this is possibly one of the most useful metafunctions, its implementation is straightforward. The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct BindFront
{
    template<template<auto...> class...Beginnings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Beginnings..., Sequences...>;
    };

    template<template<auto...> class...Beginnings>
    using Rail = ProtoRail<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJL%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRye7%2B0yHx0xeRAB0L0fYANTIBgoKL09vn2%2BCneAHlUglbtk3iYNABBcbELwOd4WCLoABixFkMNhJgA7FY4e9ie9Tjc7lczrcLvdHqg/gCvkwfn8LJhgBEGBFgApoUSSQikQR3sosUQAEpMOg4knvfGE2Gy2Vk86XFXUy4PZ6vQIfJksl5CTAARy8jE2vN1MqVxK8mSM70ldDlgQAIqDwcRIQJLmyOQwuUZfi9SO8jabzZhg/8rYEFbL8a6jgrrcT1RT0zS3Fr6Tq9UDWezOdzLdhU%2B87dzHVLaC73aLUBKa76iwGSwzYym8Um4zicQB6ABUw5Ho/7A5HABVsEJJyPx3Ch6PlwvcXDzIEIl8vFgXW40AxNqkCKW%2B3DM5q6R2y3DBcjwwB9DTJs%2Bwi%2B07Uxm/wgiI%2B8mh8uBfddz2uVUP1zL8cTvYVHzMYC1zfMCNQg69oN/IUwwAwIEJxd9KXJLMc2vQFmWjPkfz/YUwQhBpcLhSsHSELxUiKTB0HFKMvFoYUjndGivTo45Hw0UNHy4MSALMSTjQfHDO1ffD8OIvNSINJ5YWIHkKMY4B3gAWUwZoqC8Q8GjrFE0UxbFjgE70GAokAQCdWhLhEmTAMc5zm2OTSeTQ3sQNhXTHS4niLMM4zTIcKFhKkjz5LLQLENmRxkAfMiEgICBxnQJyFFYTAMstNxOIUbiCDEli2I4sKCDeJZkw4FZaE4fxeD8bheFQTg3Gsax3gUNYNkwOUzECHhSAITRmpWABrAJJCeDRJC4PFAg0fwNDMAA2HazAADgO/ROEkXgWAkDRRM6rRSB6jheAUEBROmjgtBWOBYBgRAQDWAhUkechKDQPY6ASKJCs4VQDp2gBaHbJHeYBkGQd4pCeMxeHYwgSDwPKJP4QQRDEdgpBkQRFBUdQ3p0PQAHcvVSTgeBatqOpmu7OBBR4AeFVAqHeaG4YRpGUbRpazHeCAPFB%2BhiDGiall4V73tICAkBB1IwbICgIE17WQGAKRpJoHiEieiBYg52IIhaABPZneBt5hiDtkFYm0TAHEd0gQbYQQQQYWgHZp0gsFiLxgGzWhaCerqw92QxgHEUP8GIL3HAANyjDnMFUL3Hi2SaIh2VrQ9oPBYi9V2PCwDnfzwC74%2Bz4hYgyTBXUTowK6MGaVioAweQANTwTA6ZozrJsJ4RRHEMnp8ptQOd0CSDF70xLGsfRK6eyAVlQY9sjj2Hcr4jerEsMxbtQFviDxnO9%2B6DPshcBh3E8Do9DCCIhkqEYJKKFkAQUw/AAIyEAhg8xhiJAknYZ%2BAg%2BiTA/vkWBdR4GNAmAMH%2BCx/62EwSAvQsxWhQL/jAlYQ11ibAkKzDg7VSA3W6pwQWMN4aI2RqjdGksIC4BxvLDcXAlZTT7isBAmAmBYESBAeaSRAhPAAJyBDxJIFaZhJA7Suv4HaciTocDOqQC6E0ng7S4DtA6ciDomP8KtfwCidr0I5vdR6z0hE0w%2Bt9dWv0eaA11vrOWEM2CcBaCwTOeJYZMFIg6LgcinhcGWljfARA7743JjPEmEhpALyUEvUOuhpIMyYEzLqNC6EMM5hwbm/1HjvH5u8IJISwkRL0lEmJy0pYyy1nLBWZhBEq2amrDWqBZYJCBnrQZHSRh1NCUyIwUSuCiVNjsYgFsrah2dvbH2azXbu09t7eOftGAEEDsHDm4dI7R1jj7LALAk4p1umnZ%2B2c463TzgXHYPsS51A5hXKu9ta5bFug3Juk0W5tyUJ3a53duR9z4IPBQI8x4Tx9tPYmc8MmyEXtTW6uT9BJxQP1Sw29Yi7ykXdQ%2BAhj6nzdOfawV9uq33vsS8haCYrOAgK4AhElv7lGgXoQBDQOVpHAQ0EhixUE9AQfg5BoCn4sowXMbBPLYGSryNKohWDuWkOoasShpNins1DvdWpxBgmhPCdMpp0TYkaCljwxJCsBHK2EaQUR4iRgkrLnogx0SVp4hsXidakhVEIwkqUxxthnG9LcfADxf1eYjN8eDSGHAgkixYAoTOqNM7NPOOMeJvC8Z6GRbPUmaKKZZMxbTYI%2BTCksx0SUhxXMvF8wFimxGaaM3vCzdEnNwppZjO1grQIPToUeITTrYG/a5YgAzaxB8XaHw9oysahGfA6CLOWdbW2rsNlbrdh7DOPt9kByDiHO5mAI5RzEBc%2BOVybn/N4PcmKjzc752QIXd5ghPnl0rtXO2fz653yBbwEF7dwU3Kha4mFTBh6j3HuCSevAi1pPnui8ty8QDBDXsYfFNhvmMtJQ0OO/Zcp4s3pfa%2B9KsD4bgbK1%2B78VVfzfiK3BfLsgCtY6UBVmqxXoMQW0KVhDmUND48xmBeD%2BgCrVaJrVFCRparLvWg1TDW3vHbZm7N1Jxg2oSSQe1w7XEiLERIygNDPUgDMNEwIgR/BbVWldKzeJTH2KUw9cNL0nULWSPI/wB1dpyMkHI9aiiuCYc4IEfV19OCOoMzozGznIuucjSsFumRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/bind_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/bind_front.test.hpp)
