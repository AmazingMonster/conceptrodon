<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-modify">To Index</a></p>

## Description

`Pagelivore::CognateModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<auto...> class...
 -> template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to variables of indices `1, 3, 5` from `0, 1, 2, 3, 4, 5` and invoke `Operation` with the result.

```C++
/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateModify<Operation>
::Rail<UnaryMinus>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateModify
{
    template<template<auto...> class Hormone>
    struct ProtoRail
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<auto...Variables>
            using Page = Send
            <
                typename Send
                <
                    typename CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::ModifyValues>
                ::template ProtoRail<Hormone>
                ::template Page<Variables...>
            >
            ::template Rail<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIGBAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnthVARXAAxYiyf5ncFMljpAxMkkEDEfZhsAB04up90WxC8DnpjJZbMEiJSVhSLyRVnukO5vKY/ORur5mBJTFRqHFouxTzhTAUfyEmAAjl4vphSE8zURLQA1Np4JixegKSV3aWygjypkMdCs2Qkx0ut0kv3EANB36W6mBHHa1WQp6Fp5G/Um5Fei3iqKYADuqfTwdDRaeXmyRieyiYwEwiMCLyeiddBLLbmrdf9geDlo99cnmYlOc1uPVS%2B1tOefoxHNOXMwPONpvNT1nGdD4blm%2BXFiei31eGQNoEi0wqnSxE9R4AbmJXSqLCf6BMFdAmvICNRAmkHjpZRiEwGhVG3a4dT3PUDTcQVhVYd0PyIUM0GHdJIxguC8AQpF%2BwIGUyy1CF11OAcEFRAh6EQ3d91LQ9vQXXMw0oiMGKYwCILXKDngAeTYBgGDwT8SHYEAAFkMDwKgMT9bxflYyERV%2BdImH2J4JMYaTZNgv9IJLNCMMYLCs0XKU%2BLlJT8FU9TXT%2BIC1XAmjIWBY4ngsO0ezcIKtPuSyRwrS0AEkz0cyNnJUtSf1%2BElyRAEAIiwVQAH0lCTYcSWiuycXsiF83uZsIoFFCD3Lc0SptAx7UMj5iDvAQmyLc8iLZIgACUmDoAsi08kbm0LarKomwsSXGmai2snSngAFTabsCFIeaFuLIUbLFcVAuQABrO5iGAENppmrqZtvRwH3w59v1oHDUCePB0AxWhtqLCAfpmw5DnlPSY0RAA2DRiPgorsSzCHizetAvGVdafEYAg/nifgzIIBAexmDarSunaO1g6HkVinNXstKglQIHL1oULbiZ2wHVvahgFGxlhizxp5IkZT1zrRwQibuEmizW87ME2/6JrZ/J%2Bl5ntYMWMWJcLI7TvOhQsxZosNjlgBaa0hEYghmJNfXZuROXmywOFrOoOmGZ1jYMue11pztosxLajqGBJKWNo9lLsVDjTmfFjWtbOi6I69iVrd7UqfOT6r6q40U7mAWC93RkMyp21sImADsux7cingd2gnY%2Br6IEvZEc7zySMepfN1UtDZDeE6PZuAtP%2B%2BLWqOMNUe0Ki7imrtXXxRbzB88EQueObEv20Guhe37GDUAGobvub3PF7buerUXPuwNXWi7gzkKGvFaKPSn0UACk4plJzlNclLC7cdLMoxhfHlZ0Q59hFRKh6ABWVgH5TASOV%2BJVQxjWJnfO%2BL9rS2han7BIAcbo3niqTPeqBN7fWJig4eVUJ5W0oaNW2ycqp7WWsyPAxBFjBxllHDWu1MJsAHI0AQ6AOGywYYtJhtlDr6W1hdOW%2BDmx3XvI%2BTmTJnqvXep9MhtDCx/VEYWNmDIQboHBpDMmpEYY5jhhoBGj5kaRlRqfJ4WM5LKyeDQNhkYCYy3VhrKGZiKbWhfrTWQrsLpcI1mzFaHMuYkB5rjHsAs7HCzbt4iWLD3HCLCRLfRr5DBGJMBDXxqgSTvwsRKeGRAnjADevpNkLU4nVzwLeYcjiZY1kXgwYsNY3qeIxikkmhTikBIfqKFgH10D0BCUzH2eigaRMMNE4gsS%2BYJKFsAEWBA%2Bk7UdPhIR61OHTKeArTwSt6mqw2Qc2OOs9ZaKeIbZOJsqZm0EjQnac1dHV0aLXPaztgmM3diAT2mBvbvJwe1AYJI0nsL2QQBOZZsCwsySTGuTtRkUgmX82FwKbnNlBXg5E2zBHCNheHAFKVEU7UufHUlGlrmvIvkPHa6DhkLyXu3IuC115l07N2beHzHbfPrrQRuTAsRH1bgXDuXlu69xos2K%2Bl9UHUJquxSewzMHNTPiy0%2B%2BDOVPFIby3e%2B9hpipPgXJBl9B6QT8nqxouxsifmCqFAEyEVWRWGU/am4pX4eiWhI0UYk4nEEHG6FekIepPESj/DSf9oFANynA5MFNIEEPQBlGB8bQGJrcIg7iHoA14yDZm4cZ9kEVWHmgpVmdKzn2wDPbB/twXssLOGw1JCD7zQoYypVyc3nYrEbwnskKCAZIOb6vhBKYwjveWOoFkiTpx0ujcuR3VWj3SUU9MQajBVyx0X22a7zsmGOMQM/xpSrTlMRjsFGSSC4tOxvjPmbjFjFmhZshaJ63CU1rYEl2jNyULQiVE7mLiVn2PRm%2BmaQ6p17sOUDAxuTj2mKKciEp2BLHWKqZ6ZAtS/j1PwE0gy8QCBtMYJ07p0LdYHI/ahz1Iyxnop1v%2BgGsygMxJAy%2BRJazkkHInbs6WIiYNHNoCcvmZyIMTUpSW5OdybkPNrQyaMsY6ayPoTB5Fe0Dm7u4c2SNyVo0knzQkYNxakHvObBlCKer23IlxY21e2nCxpo0RASTY0u7ihk9wzzC1l2OZAJZ7lLyfOqe4epj4PzBCTP%2BYCrF3DbO5AhawqF/HiU5gRQcsLmAICovGZgKLmLxRMYmvFzq%2BKBGTuhal%2BF1LXQqdTpBLtrrOLVq1RKptE1dWBd5ZliAgrhWircK15ekqwLSuvnKy1IkqFNfHjN%2B%2BWd1Wz0tENtl9nCy6v1VXVtpCSQrZLfS5c3lIJXxEtakK6QFBeBYs68Klb0LiIOjWsNhDzuXaEkPa1jpQY3dvndmdpneKf0jF9vJncjsiQrXNjBVMsEOiLfsZ%2BwyAKpTKuGkHCZ4cjmR/t0qPFO2LT%2B3d6HtbYetVwXZ%2Ba4a3itGGuQstxc2xl2srykrgdkTY/NbK0ak2b7TdQiOJlC2YcauW8fVlobiYbYPry6n1nBti9PiVCzGmLXg5vpD/nAoHuzprXWv4HhBBDUiGQHh%2B0dfYHoNq1HhD0fIgNzT43JILfi/NXj%2BnBO5toO141UnrP8FU5lu2unXOZq6uZ1XP3yJneK%2B4uN7nav5oa7qvdgdPuRfzwV21tbLZGd6tQEwPJfZXiB%2BNfL8Vy8lf%2BZVz5Hnvk6QrSFPeMQyhUDpDCncHSCg9IGVTBiWIMlnEUJdZrqtAPw0N/SE32gLe29uYT7dqHR4h0f34hPqfM/EvuNLSHnPpdTe8qeRbISbhsw1/n79xfFSh2I4qbxlfco1%2BiGn63zfiwPR37Kvj9bufw9F8P5bV/AgU/Q7a%2BYfZPCsJ4a/NRXjG/atQzNhe/SMR/ZvF/ZEKAmAwyQNHHK8eaMPDTchIvBTRUeMQ0bXVaRvJ/DfGzLAyvayfBCzahcubsQA9/crdAYAvMc/E7G%2BM7VAYAZgJkR0YANudvJPMeebatRbetcnBLa3IHJ4Dwfg0sIQtuHAxVObbIAALzy0jA9S0J0MtFQ0p0IVl1p2Hi/wmjvn0Jyg2XFAAGlfMnhYIXRWFNIIAswzAwZzAwYIA7Dew3AnhX4e45ZdUAAJMZRgGwlnBtWQz9D0V%2BI2OwznDtWvdQkfCQ0XcvVbXA3PLrKuW3FPM3Y8NoPvAfWCDKZA5/dIXbTPCvbiZXD4eg/zRgnbZEUww%2BMvU1OomtBg11J4cIikSIoAg7U7IGaKGMe8TSUQDpMQBQN6eIJ4PSe0TAIxXVfJDQWNbKEBAqcBCGPpL3Adf3QhAYrADpOfUAtI5Paw3QqBPAbQmwwwo4%2BQk4xgNKAgVNQBLYhNQqCmeI13FInfPnK4u4gw%2Bwxw5wrwVwv4dwiUTw7w3w/wwI4I5OXVdoqIiPGI0rOIwIxI5IqbDlH/PaA/VwLXAdYo4gUo0yeSSoqg7EnNHoqvRo9rczZovo1otwNE4Y%2BrOnc/IE8Q/7DPLIiXYeXVJSWgQvfsF4tnTol3eoxk6iEAhVUSUEFUzkOvZ4aKfcVlAOdvPyVU0EcEMA/konNVYXWeMnMFWQnicNRQgQzAXTNQ8tQnS/SQs0lqUImJAQOFYw%2BQ7bIPcw93GaKwkEqIvQkM2wt%2BRw1EkvWgdEovV7K7EcABFgJgY6PLdNbY%2BBcxbAKBd4jKFMtMnKDM748BFDI2LgWGWPJUxrdI64mKRwltPqVAQLWRQMkmQXatbHRwteXIiuYkmMA5XtBzSaMg9HMzOhE/ccoMsg205QzAYQ9GEkTk7sjWXo/nJgkcYqWPKclONc40PPAvAzSSEyOSDKXTNyFHbPbhPc0sIhI1Doj0xZL0lcmaG8pkDclMCcDMbA95F8p4N8nsdkyPbkpdVIm5DszIro7IlE3snlLbJslsk1WUp7PuCbXkj3dIiC6eWHSC8XHVXPTbIvP00vPbPE8qc/PU/U8Ea1BkVgXkHsH7Si1Uw07UaEWEeESuZEfCfYQiYU9U%2BiOQZgCkhSCIVsUQk0ipL9Z7eQwSkokShgVsR0%2BRVdRRR6JkV8d8CAwFAEo2WKWvMC61VncSl0sfQhSPD7OkBSQPKgZGJoAQYy9Il%2BBdUMUU6y2ygYXlWcpkB0mzTEtnHiDKdk2S4S0S4UjKRCtwLgD0YIJ4fwUMcKiuXbK5Ksiy54IQLwdIEoFY/qX4K7SMH7XVdKzKrIbK3K2uaImQrEjQD0csj0MwGqmK6QJ4I2OKkYngukHKt7fKtU%2B4DbMqyMKuKy1oGygkRtNwaqp4KKp4eqp4Rqj0VqkC/i/yFaX4bqncZ7O8ZABmZY9oCAABBQLCbakkTqvK9/DKrK9AE62ubEGVDgLYWgTgfwXgPwDgLQUgVATgE/SwawG8HYPYSuaEHgUgGFV6u6rYY6AISQUUDQAADjMDMAAE4EauB/BYaYauAUgUhpAHqOBJBeAWAJANBqqXq3qPqOBeAFAQBqqQatAtg4BYAYBEAQAdgCB0hURyBKA0AeQ6AEgogsJOBVAYawYjYwZJBKlkAHwpBRQzBeAVjCASAPo9B%2BBBARAxB2ApAZBBBFAVB1BQbSBdAoqax2p0hOAeB7rHrnrNBeAyaxJUQ2bIxUAqAnhBbhbRbxbJaoazAngIAPBub6B3w8QuANheAaa7rSAIAkAubJ9/aOaIAo6ebEhgApB6qaBa4EhKaIBYgrbSB%2B8hKMRTbeBc6SixJYhtBGgQagaua24xIGBaB869asBYgvBgAQphNKbuBeAsAUyjBxAG7XCmgHV263qXxbUmQC7yBBA%2Bhs70RYh2oKSPAsBs7KI8ACaO7SAHViBYgSq3hu7gB0QjAratgqADALofQfgawcEXqgblbhAn91bpAb7ta1Bs6Db9BDBjBrBrB9A8BYhKbIAthW8Bh26jZyRyJTBvrLAzBSaN60wsA/6IAtgGg7K/AIBXA5g/AoqwgVgqgag9ASgcgBB0G8GsgCGGBRgcGJgoqkGBghhZhPAug9BqHmglhyHxhEgqGlgiGOHhhWG1h2HEG/r9gJBzaOAnrSASbrbOBnahaRaxbgAJbJrPbvbcB5aA7Abg7gbD6tg8YC8JgEHSAIbJBAhRQEbUhJANBJAzBJAIYNB/AwYEb9BOA8bSACbAguBRQwYuAwYYaEb0awZ/BJAUbTGwZxHs6yaKaqbNHQa6bGaI7ma7b2aKA47UA/beb%2BaOA2gWBPwUgjYmAZ52wuAEbRR3Hh78AiBYGlbZBVbxANbH6lBn69bdB6qjamATaO6RGxGJH3rOBbbWbUQnhHbpHXaxbbQCmimSnvbfbo6EhERoQzANHQ66bI6UnpmyAkn47/aUADAjBCmuBqrU6mQ2FKAs69ai6KTx6zmMQS6y6HBx6q70Ya667s7G7m7W7aB26gau737e63r8BYIB7fhs6R7kBUQDggaIgmQca3qZ656MQF6Dg3rl7V6gaN6t6lAd7vnS5D6%2BAT6FAz7axL7x6b7qn77Nb5B6nda3qmm36D7wGrBLBv7f74AAHCJchgHQG%2Bw6XrAoHraYGPpAX/7eh%2BhcgXAYwuGQgYxeHcGor8GBhxXZXcgpXKGhXy7mHhhxWmGBBaHlhKg2HGHOH6HChuH2glX%2BHthdghGg7HHRHLa9ayahnZH8my5CninoblGymSBZm3GFmtHSAdGsBEh9GcbnHXGimLGUh/AEbMbAhLHrHAnQm7XOAInqbsX6amaWb7bY6Nm0m2BOBMm3aWAFBPwHxPwXXjRFhZaPWKmoriW76JAH7ZAn7KWdAkhSAWm2mzbrXOmwmemEmHanbVAC2i2S2y3Sxn0faVmE6vXAgfXonw7lnUm1nObJ3Nni3MqcpS2Eacpy36ZB2H66BDmM6Tm3rLmLmIhi7S7y67mUnq7a767fnMAm6W6xB3nx6vme6EXO7%2B7HBB6gXVBR6wXeAIWp69aYWSj4Wl60xkXeBUXt69xMWD653j6uw8Xz7CW17a21b62yWm2X7W3tmP6IGbAZ74GWWgHOBDh0ouXIHoGEhYGBX9HNWUG0HDWMGJX0BTXiHShch5WSGBhOOqG%2BhVWtWDWCg2OmPtWBPph1XWP9WeHsG9WrW5iLX1aOnbXSapG92nhC3i2nhN3RQd33XVGvWg6Q7fX/W9GRGQ2QBEbRRkh/BUbAmia6hvGE2NPybbBInFnwaQBJB/ATGMaUgiaYbJBkauA4bPDrXAh1PJGPPvPrWZa3PYuzPomtgN7shnBJAgA)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_modify.test.hpp)
