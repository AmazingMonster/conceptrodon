<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRemove`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-remove">To Index</a></p>

## Description

`Pagelivore::CognateRemove` accepts an operation.
Its first layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function removes its arguments at positions indicated by the index list and instantiates the operation with the arguments left.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
             &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
             &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
             &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove ::   template<auto...> class...
                -> auto...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove variables of indices `1, 3, 5` from `0, -1, 2, -3, 4, -5` and invoke `Operation` with the result.

```C++
template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Page<Args...>;

using SupposedResult = Operation<0, 2, 4>;

using Result = Metafunction<0, -1, 2, -3, 4, -5>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateRemove` by combining `Pagelivore::CognateSegment` and `Omennivore::RemoveValues`.

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
struct CognateRemove
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
            >::template Road<RemoveValues>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGb%2BAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnlfYJhoAgkcnZ5iX18iL6CwVGerw%2BZmODFOXguVzcBAe6UwAH0CMQmIQFCD3qCAPQAKgJePO2FUBFcADFiLJzoS8TjQWSWOkDGTYfDEcw2AA6HlYt6LYheBzE0kUqmCS4AdiskoAIlcrNj3ozmUxWdcVSzMLCmLdUDyuc9zqcmAoFOchJgAI5eRj7UjnXVEA0ANTaeCYsXomMCL3eAqFBBFZIY6Epslhlptdu11zdxA9XswCgNIN9oJM0tB5xz501atjbid%2Bp5UUwAHd44nvXzc%2BcvNkjOdlExgD8rrKLdbbZDC2XK%2B7Pd6DQ6q0Pk6n04FFR85QqM%2B98YTzgBZASoIgMB40wn05WYJlanV685jpN8gPCtcMDcCJ7Y6XnRZqvDIY0CRaYVTpYiOk8ANzEW0pQsM96EzeVpylSCZ1xWlm2ITAaFUHcCT3N583VOEEUYVhMAdbIAC9kQIPk0F7dIg2URDkN%2BTtUVteclTeJcCQtBBbgIehULpBkD1VLDi0nP1%2BQY4UhA4gguNjWDF3ggAlA9UH/TA3W8ZMePQzDC3ZXDuV5dN/TEoNFJYZTVKAjTMxlGCFxY%2BCLFNH4iyUTS%2BMPAtj2dHkAEkL2M85TPMtTbR9NwARAEAIiwVQkSUaNe1hHzhL5azs1zbT0pzWEsrrc4cRxc4AHUfgbdsADYNGopC8FUJLnlTSq81Qc5GB8BIC0uSrw0EAAVNo2wITFKsNd48tzarkPq30DR6gh%2BuIQaFFIXK6wK4qfnQKl0jzBAfkiUlHUW9rBFGt5xpzXTOXw1aMpw66DUc5AAGsFqW3La1zZ9HDfcjP0A2g/yIc48HQB5aAgDZcvWqINx%2BAgEDVLqNAkzjwKavBzQiZ9BA9Ml0HOWJtwB0LocKr9USYBxMAJqgqRYXb4f4rVznSNo8LJYgUzJ85eoQTGQfNeJRDK85yx%2Bcs6EBtmXtalTiGJwdzzG3N1oiYGTEq69by3TWNDOusAFojVRqTwJV7LrlunM5rezAhsiknMBHa3zie16BvthRHcs1MLd%2BF5pzsutMuuISeTeYBEIPRghs%2BnMGwiYBm1bdtAk7LBTl0iBQfB2Ftc3J5rkj6O2EEH1sGEyGoaDh9bOY0Oiz1A0fIdcOuQAKX8wVhSClSQuTWEIqi0Mvzi7sYyS4SCIIdBIuisf4p7fZYQ7lLDNnGcQ%2BZzz/Zy/21sKkr61cvXJtq6bK95Jrgbatg0TJZHbc9uORtd8%2B6uuPyZp5Z/Fq9laB9VZH02ttRm5wDpBgGidAgBsLpXTwoA86F11rH1FmfGiF9rhdx/oaG%2BLVgAtSplSM04D8A4xXkAnM614gEHFowPM5YWozCWnA8aH9V4NR5CuUG6B6B2yGkgi6%2BUQHnC2qgHaCN9oUyOsAGBbC8oILYEI%2BB908KPSph7f%2Bcc94bzrN9V874GD/TEEDFqucIZQ39sbX07E0bal0W4V2f8lo%2B3Ui7Khq5eH8Jft7EATsPHIPGu7ARfiAm8l0YHWSQS8w70Es3COUdMAx3LvHE%2BScU5tjomIxotBs4WPzuuQusIS7JLLnHXBzxq5MVnPXD4cllyKWQLsbIKlzguR%2BLSLScTCzt1bmYg0HcHRKOdjyAA8lI4gUZl6Dw3peEySl%2B6WTCsPBesUl6Ty/tPJ8s956j3WRPRK2DtkTL2lMw5%2BwUwGREmlf2mVHGu1QaVU%2BlUOFfy4XgjQzVWoMHag/CqGgXFez1gousby3DfyvlyIFgjHmiPEZIvaECZHQPKaCu6HJEFwo2ifAF4KcFQr1t8whjpkAkPNFIsRmNWiJU8TQ%2B29CGCMOYb49FOZ8UfJ4YCHx2jlrYuPgi8BkDZHyNdiMlR40RkaJeqEj6eivqtB%2BkYkxgNiwgzBpY3KNjsDBjFBGB5niRmBUWRZdSYVTkJGmTGK5hp5XjUitpTJhYQm%2BLcbaFKkTcoOp6U6uVTjPEwrCb7HkEq8pcr4ZgUJbrRkKLTNE7eHl4neS5KUlJFSRJ1kTk2FsWSOw5KzjhHOGrCk3mKcXJJaaK5Vw2DXWCc5a71PssuIs6QFBeG4l09yAkdJqP0rakS8z2lMFbe2mSdlWJEktKGNy%2B5E09sxX27ugYuzTrSvW6JjdG7tyNCaUhVrextwSVyMCsyB0BSnegSMFzCwnptWmG5WY7k9LZM%2BsOR6d0GFIWMxED9chpMHbKe26JaAfUfTEzNjZk66Wyd%2BjqAxYS3vXlvXMEEam5U3a%2BpuyaP2mhtam8pFdcpZuTvJYD2TAOtDoCUitBHhIOpwmh9ddkMNzrZL2mNOHSEeEEOiSIZA8zsYNNgegBGl3iVcLCbjlG%2BOwmE5W9eD7kOXUw5uwT1zjSfvNLB39Ah/0BQo8B0DSm8rEYE4iGDP6Xy6euHJ2j1yal1lQw29DKmVNqf7Rp3DBp8Ox0I/7Uz8lUBMAJnmgzVHy2l183RkAulGN1LgsuXqCJXxiGUBImdGFMPbrmQFJL6QUu0DSztNd8XZ3dq8i1ckeAuakRyz3IMeWCtFdhFVmrqUwMQYydBvNptpI5SnHW0rmXWNvuBq1xYh7gaWnIpeury7GuiEKxIlr1WJtdhm%2B14zpnuvpzsWbQs43atRIzExhuWWTyHcmy1abAh0BXYNBarmYmGvJcW8164l31u3YdI9u9G9bkxO2wx3RnYSQhjDOKWr2EF0/AW6l5b1xfvRdi3a843q52%2Bo%2B6tggDobuhjjSdobE72moGAMwMklpgDlIyyx8ro2Swed3Vpyz8G5vCg8GTgslPykneM43IiJFzj9IFyiQZen6vnDCyBveHX4GYZF7AnkABpNJdZEI2mqxpCAqYzDlXMOVCASvfhuHOB3GtrtTMAAleGMBRBZuDf6v4Og7obJXSHQNDYTXTrDDOfOpNR6ZnNadOwXrYzD3mr34fpGo5F8uyOGOo/R92wKhnrhS5j2UqL1yk8s2t4CW3R20OLkKj5UMr4NKiCZWIBQLV4is1wzTdJTY9arP2ePBKK835PpG9DvSsYM0Kol3nrATKStF5ifzvAxE7fC6nyRMXqPB3D8YEPXZI8Yrt5mUlZ3CmjNivl3P0XyvVe5nV14TX5pte8l1/rw3xvTfm88aZqXdu83aaswwbfpvXfu%2BYsIoH5mPWEmGo7GEe%2BWb2COEKO%2B2eMWCeA%2B9qMWPqpG4WbgL%2BheDajmp2jaXuR4IBMO3mNGvmaSpma4tAIWu2y%2Bn%2BEWmeceMBKOg24%2BxOHO5OmAfcnSu4XauBcI522GtiTO5w7%2BrOZ6EuzBBYbBvOLmPeCuQuBEh%2BiuncxBkGkuQGdAr%2Bu2Laba4E1ww8LATAz0yIaym%2BmyEKzwM8c8IAuh%2BhSIhhGyRybgLuXAHyBOf%2BGUB%2B0%2B8hkKuUg61Et4Qee%2BhqPBDOt6J%2BCcShQe2Soeni%2B84Gqi4ekRMR400RwiwiRqohFOmAVOscsIaBIRyROenUfhWy9mnijmvo%2BRj8gWwWsIbBA8fmCReU5RPwhRbgiGxR9RuRjRKeKBghjux2MunurhPe7cfu6aRGYRqc2SPhRAzRIxf2fRtSjBtISxyx6ExOvUyYQ0GWE6yxSx6EGY4IXw0IacNwdwjwqUZWXB2Wwhy6PR1mG6gR3mi0dRJBQGVAXgkIAw2SaRrBJqsItxVBIkkUzRXADowQ5w/gfIQJqcJSTxv%2BjapmQgXg6QJQNMikmhQYb%2BLOjubgGgDoZgDokgzh8JShaJ7aGJu2K4rx7xTQ1mOJDohsIJ5w%2BJ5whsYJ0gLJEJA2dkBiyASIDe7QEAw8CgeEfJYUiJyJWQqJyYZJDopJeSzwtaHAWwtAnA/gvAfgHAWgpAqAnATilg1gT4Owew7Y4IPApABAmgSpWwz0AQZgXIkoZgkgAAHE6f4BoCkP4GYBoOVE6cECqRwJILwCwBIBoLiRqVqTqRwLwN7LiRaZqUqaQHALADAIgCADsAQOkLcOQJQGgEyHQAkFEHhJwKoE6eVIbOVJIOcMAMgG%2BFIFyGYLwDTIQCQKDHoPwIICIGIOwFIDIIIIoCoOoPGaQLoCCeWGiOkJwDwMqaqeqZadqZwGMrcJmUGKgFQOcCWWWRWVWTWecHWWYOcBAB4HmfQL%2BEcFwBsLwHGVoFsBAEgLmfliedmRAPefmYkMAFIPiTQHkgkN7BALEHObEBEG0A8JObwIBcwArGMrENoI0HGWabmeUmMgwLQCBUOVgLEF4MAEWLQLQN7NwLwFgLoUYOIGhZrk0CpHhVqV%2BI0LcAcGaerH0HOfcLEGiArB4FgHOaiHgMGfhaQPLLEJKYBkRcAPcEYJaVsFQAYMAAoC6HgBWLBhqWae2cIItt2dIMpf2WoHOSOfoIYMYNYNYPoHgLEN7JAFsBIgMHhYbACB2KYPqZYF6bwOZMQAmFgKZZDL0P0LkC4KGHMH4CCWECsFUDUHoCUDkAIH5aFVkOFQwKMMFRMCCQ0DSYMEsJFYlX0LBc0EsHFeMIkIlalZ4F0HoM%2BO0DlWsHlVsDXrsPsBINORwGqaQOGU5ZwOuaWeWZWdWbWZIPWQebgM2aeaaReeaeJVsHtMFhMB5TaZIIEFyCkIEJKJIBoJII6ZVBoP4OVGkP6YGaQMGYEFwFyOVFwD6SkE6Udf4JIFwKkIEOVI1XOZGdGSALGeJYmSmbeWmUuVmRQM%2BagMeQWUWRwG0CwP%2BJKIbEwJ5k2FwCkFyPtVRfgEQK5W2bIJ2eID2RpUoFpUOboPiWOcOqBXVQ1U1fORwIuRmbcOcKuUdEDSDWDSaBDVDTDQeUeQ%2BQkJcOCGYENVeQmW9S%2BY%2BV9TzRMIDcDYbLTe%2BSkFwLiV%2BZzL%2Bf%2BUOeBcBaBaQHLZBdBbBQrQhbHEhShXOehZhdhbhQrYRXpSRVqfgIhORcmHOdRc0mSArQxf6VqcxaxQ8OxQcFqVxTxWafxYJQeEbUnM9ZJa2DJXJeWApQrcpcjWpb2fIOjYOVqVjbpWJXZVYJYEZSZfAOZZRLkFZTZenEndYI5dqfLK5RbWZZ5Zlc4BAK4GlSEKGGVSFSCWFQMNXY3bkHXQlWXclUMLMIVYUOlV5QIF3csJULlcVQVQUP5dMMMG3RVdsNVd2fjbOUOZGZTULTTQYHTdDVyF8hAH1fDazXtRzSNaQGNVgIkB5VtUGSAIEFDUtZKKkJKJKIEMtZIBWSCYTfdbYI9cNfGTea9UgOmcuU%2BfzcQIWWwJwIDVuSwAoP%2BG%2BP%2BJDVyFqIsI2XDS2XPCCeHapRIOpbIJpbHToFfaQDjROfhQvbdUvQuR9SuWuRA5WVAzA%2BcHA1DYg0GIeT9czQNYEIEIfT/YmXeWw6%2BUA/wyef4sgMiUiIw0iMw3ycQCwBWXwHQFLZQDLVqUrahWaao1BTBQ4GrT9YhchahSbZgBhVhWIPrbxYbcRa7QRWRY4BRZbaoDRTbbxXbUxcZU7S7ZxQmB7bwF7UoEJb7WJTwwHdJbJfJRyGHUjZg6jTgzHdpQQ%2BvfpfZTYMxe5RnZZZwDiBFHnQ5RGUXaDCXR5UlQMD5e4D3RPYFcPeVVFaULkM3dFQMNPcVRlZ3WPUVX3eXSlVPUFSPflcMNXSVUPasPXZVUaTVeefoDOWQxGS1TQ%2BcHQ7A/A8w71Sgxw%2BeZeUfSfRNXVdtcGWYFDZw/4G6RdaGZw5KD6VM81VGZ/U9T/daSAJIJKPWXfVwFICkLfXNVwJKBMxwIEIvdM1c5zTWt8w2Rc0Tes7c3xT%2Bd5ZIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_remove.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_remove.test.hpp)
