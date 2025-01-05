<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Bind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind">To Index</a></p>

## Description

`Pagelivore::Bind` accepts an operation.
Its first layer accepts a list of variables containing pegs and returns a function.
When invoked, the function replaces the pegs in the variable list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., V<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., V<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Bind
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Example

We will bind the second and the fourth parameter of `Operation` with `-2, -4` and reverse the order of the first and the third parameter.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Bind<Operation>
::Page<Peg<2>{}, -2, Peg<1>{}, -4>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<3, -2, 1, -4>;

/**** Result ****/
// The `nullptr` at the end has not effect.
using Result = Metafunction<1, 3, nullptr>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Bind` is a special version of `CognateTransform` as it transforms pegs into variables from another list. Hence, their implementations are very similar.

First, we will create `Peg`, which is similar to `std::placeholders::_1, std::placeholders::_2, ...` in terms of functionality.

```C++
template <size_t I>
struct Peg
{ static constexpr size_t value {I}; };
```

We will detect the pegs using the following concept.
Since we cannot specialize a concept, `Pegful` will redirect its argument to the helper class template `IsPeg`.

```C++
template<typename>
struct IsPeg
{
    static constexpr bool value
    {false};
};

template<auto I>
struct IsPeg<Peg<I>>
{
    static constexpr bool value
    {true};
};

template<typename Arg>
concept Pegful = IsPeg<Arg>::value;
```

We also need to ensure the integer stored in a peg is not zero, as we will subtract the value by one to obtain an index.
This is to conform to the behavior of `std::bind` and the placeholder objects.
Hence, we create the following concept.

```C++
template<typename Arg>
concept Nonzero = (Arg::value != 0);
```

We will pick out variables from the argument list of the finally-returned function via `Varybivore::Among` in the following helper template.
It detects and transforms the pegs by a partial specialization, which is specialized by constraints.

```C++
template<auto Variable>
static constexpr auto Hidden_v {Variable};

// This specialization will be used
// if `Pegful<decltype(Variable)> && Nonzero<decltype(Variable)> == true`.
template<auto Variable>
requires Pegful<decltype(Variable)> && Nonzero<decltype(Variable)>
static constexpr auto Hidden_v<Variable> 
{
    // `Replacements...` are the arguments of the finally-returned function
    Among<Replacements...>
    ::template Page<Variable.value - 1>
    ::value
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct Bind
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Replacements>
        struct Detail
        {
            template<auto Variable>
            static constexpr auto Hidden_v {Variable};
            
            template<auto Variable>
            requires Pegful<decltype(Variable)>
            && Nonzero<decltype(Variable)>
            static constexpr auto Hidden_v<Variable> 
            {
                Among<Replacements...>
                ::template Page<Variable.value - 1>
                ::value
            };

            using type = Operation<Hidden_v<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBKSXKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFS8XaYDmlCBEzEBBk%2BfuWY9nkMNXUEBWGR0bHltfWNWYNdPUUlAwCUtqhexMjsHAD0AFQbm1vbO2srJhoAguubANQAIpgJrozIeJgKp1v7Rye779svhwffZgDMwWQ3iwpxMfzcyAUBHQWCoYOwPx%2BbzWp2UmGAT02XwImBYCQMONB4JSAC9MAB9AinACS8J%2BUOIXgcqPRiIA7BZTlCmI5kKc0AwoZhVAliFy8GTKacAG5iLyYUEc2ls85gzkmFVqxGvLY0hRojHPH44vEEzBgtwEACe12YbDpRwZTKp1P1rKOGqsR1OPq5tV5/IEQpFYoiqE8Mrl5u9vs9VDESg1qr%2BXu%2BmpT2sOJvxPPN4KYXiINIdhydzNdBotlfBtL%2BCLr7NTvr9PLwfIFwdFpzDEdl3mjh2bnoIjPN6dTSa1Hp1ZwNVC8tExG2xuJzOIt1ttrAVh2IwBLAqWCSpc4XRPOeurbl3%2B7rIBAfflU%2B%2BM42p1CAjJxFQS72xtXZobjajDbqcN4HgIR5Uh%2BDBfj%2BYIXhAN73o%2BCpgGACGnBo0zPkiuqHCwAiGli/6mrmFoFkQAB0NEAGp1HgTARPQCglmWVIEURipWOOmbZoB%2BaFj%2BABieDEFCbEjs6YGEUYFqieJBAlp6PzNvx5HEhKFIuiWzbsai35EMoTDAAqKm8dOg6%2Bup66aZKOkNjGPrEJgACOXhiQ8pwQLWybnNhqm%2BvpyiGagxmmRatYIk53EtgGHY4iGpyUT%2BqHcQpEnjoqyYTjFNl5m4KU0VRhzAC5uKMAQrGOVZPpeCkRioiZZl/BeIWoEZzUWqV5VsIICjFXSGYehZL5ZgBGmFUJpwZQQpDJdNQiVAI6DzUVNEAPIEAg0TVdFpZScynFyeCs3zUtAqracW07eJg01SpeUTbZbiktpxY1Xph0nqF4VmTFnqgjFX2tu2QaJV2KWRv2QO1c23HHbebg3bt93YPe%2BUGR1YVdTWpwALSnGY8IoVGk7DXD5O5XD%2BUWm9UpRYFzluR5LmPD5CEIQFMXBb9uNuIzAMcnFbaBoKENilDaWerNVPZbhT1kS99MOftzYue5nns75CFcDhPPfVjnURTWumxsL3LxeDwqQ9N0schdK1y1TmZqc9BXrSVZWYBV/Vm3VDUYn955GzjJvXt7vtVWjuGjXhHwJ0ar4otSppR62Ai/l8yKJx8XykWuBW04J1E0fC/IGAojwbdcxAZwwkmMsyFjBOgjZM6cxdTaXVH0cQjHMQ8/t%2Bk3P3Y39HePXDbtKx7QnFQASlcBhLH1VXD19o8XJgtR0B3Q4cvv8M%2Bl3UN9wP9Ab8fItg%2BLNuS9NAASeAwow5LStx59MZfo3X/DR/H1PtNL%2Bg8r7Hw1qzLyp5aAWiwECTcmAIAgPoDhT6f9YxmAAGzmEwe%2BT80RUCwMqLQBBSCGLf0wKgtW6CfSW1Fgle%2BC0izP1fgwd%2BFpkF5mwLDGhPop68PhojC0S8cyr0qgNMuaCBE%2Bgxu7Jq4dOFUTSoTLgYD0Gk37AA/%2BcdgbX3qsEDECCQ412iPXC0LCsBsOlBw8hg89oxwpn/F2lk/5AJ7j1H2a89paP0Y1YOmFLi7xgeCDxUcJFURJiABBz4D45VdtZd2FF540VCV44evig7NRDu1Y2BVUniIcROHRxxc6fHjm%2BbAqhWD4gVEnEppSSKWXMACBgQIvAggtIeK468HrJ2urXeuWcC4CW7qgGOjpDYmLru0BW9S3wAFkd5MHnK09oQyjhuLGSkvc3ijgZNOIs2oKyqiZ0wi3BgbdwRTLMTVe8E9wRXmJg2Q%2BKp5r4zMPNK8qjnk8XOG8yQJY7n8xvOEoa1NkSnCEF4BIORMDoCXgoBcVI6n7KhTC5IcKEVIuMQMmZ4I/hvI%2BaceIBMAUNgpuUlEWKSHrOOCsU4AAVHaoJMEaAYAuWgx5iAmFZclKk20FSuFOAgJgjwGAdVOJgKgVBKgEAiXswOpxqVUkwoc5ZXhVlpAtCSglpx2W0E5SOMFmYIUMoeMixpB1QbklFUoeoEAoToHvAobcNrqpuGVedaFsL4UPCRfCVB1MOCzFoJwAArLwPwHAtCkFQJwNw1hrBcnmIsMy/weCkAIJoYNswADWIAw2SCohoAAHGYMwABOCtXAw2lpLVwNkbJpCho4JIXgLAJAaA0KQKNMa40cF4AoEA3as3RuDaQOAsAYCIBAPMAgCRCzkEoGgPEdBoihG3JwVQJbMH40wZIU4wBkB8ikFRMwvA4WEBIC/PQ/BBAiDEOwKQMhBCKBUOoMdpBdDxAAO51wSJwHgIbw2RuzbGzgG1CwLqpKgKgpxt27v3Ye49xKi1mG8h4Vd9AxTNL1rwUdWhZgQCQCuhIa6yAUAgKR8jIBgBSA%2BTQEhu1KARDAxEYIdQrSAd4Ox5gxArQbQiNoWV3HSArrXhtBgtAuOfqwBELwwBCoGqHdwXgWAWCGGAOIWTnkqjSgeGB4UlRCzLAzcEHELaY20DwBEOu/GPBYDAyOPAHbVOkH08QMMShLgaaMNZow2bZhUAMMABQtF7g/pMVGjNd7hCiHEM%2B2Lb61Bge/foTTKBE2WH0DZodkBZioGPGkFT%2BNHUIVMJYawZg%2B0ef7lgPLEBZgVBOX4CArgRjNFIIEYIvRij9HiDkVIAgOvZGSENhgEw%2BilFsK0WV1QhgNE8E0PQzX2idHqJNvr03uTDCW6MWwC3NtTD1nMBYSwJDAY4BGntYH%2B3wZ3Xug9R6T1oe8rgK9OH03THw4F2YO0mBYBiI10g%2BbJB/CohWv4TaNCSDMJIVlGgw2YIrfoTgbbSAdr%2BFwKimCuCYJLRW%2BtmDC01sh5gm7n7%2B2DuHZmwLE7p3EdnVBxdlHqPYY3WwTgdQWDSjZPjJgFdNPEorVRbHMbL1EDq7e2QD6EvSCS0oFLn7dAfL/UwADqnLvXd7bwftkH52FlOLB%2B7iGD1AiF1wEXYuMOoCw9EUE/wzDfdp2OojJHbdkew0uqjHuaPm6MJbrg3bGM4nEixtjHH%2BOid45xwTwmHCifE5VST0mwNyYU0p2gKmM3qc09pmN%2BAXJ6YM5%2BozyATOifM60MD1nbOcYc8sGNznXMZo815zAPm88GLp8FkyYWItRdE7F2XT75eyGSx%2BmNKv0sBYq1YbLteGsFaK0GTgpXoTlayxYaruvasvwM/lmbbQ0guAuSN%2BI3XChTdG7kNI5/EhjfaEd/rR%2B5sCHW4tzInXVvzfGD1yYL%2BO2n%2By2YwG2/%2B1%2BJ2CgKa52J2La2ut2nAJuj2gujUluouxab2%2BAkuDuWOzuBGOapA/2gOlAl26OmOIuMObIYaFajafwsO8OcQFOfanA1OI6dOk6M6c60G3ubO66m6HA3OSGLACg0ofI0oaBZoUIF6WB16Tq8Qw%2B8Wo%2BL68giuk%2BOgIABKauGuQGqOV2oGlOEGzOMGcGqgQhIhYhEhuYUINudun2fwfweB7B7uthPBvu2GD4yAMK78lu5IkhBA5Iph8udAoeQ6EArGn6MeUebmkRAmQmImbmSeggKeMmBemA8mimYgWeomuefmjeamumjg%2BmKm4uqgxmOIlegg1en6tedmVoDeTm/cLevAbeGKnefm3erufAIW/emAkWtoQ%2BMuihsQyhE%2BqWGhM%2BxgW%2BOWEQS%2BsaK%2BgonAKwjqmWlWlgO%2Bsae%2B9W8ATWs2LWp%2B7ge2nWl%2BvWx2D%2Bt%2Bw2hxN%2B42z%2B22uxa2C29%2BP%2B7%2Bh24BW2K2DxlxoB3Qrxx2TW0BT6Wu%2BhzBHA8GZhohMolhOI1hEA722BuGjhruf2mAAO/QwOLaZBIAlaVE9hYatacQXa9hbI%2BOTBuuLBtgNO%2BB0weaIAkgYaEODabIXaJakg1aXAZaWCuhfwQJpJA6LuhGl256JJ4GvJlJswHmKQzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bind/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/bind.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bind.test.hpp)
