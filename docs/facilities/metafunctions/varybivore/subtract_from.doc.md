<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SubtractFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-subtract-from">To Index</a></p>

## Description

`Varybivore::SubtractFrom` accepts a variable and returns a function. When invoked, the function subtracts all arguments from the variable.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
SubtractFrom
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct SubtractFrom
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will subtract `1, 2, -2, 2` from `3`.

```C++
/**** Metafunction ****/
template<auto...Variables>
using Metafunction = SubtractFrom<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `SubtractFrom` using a fold expression.

We will place the initiator on the left side of the expression.
This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub></code></pre>

Here's the entire implementation:

```C++
template<auto Target>
struct SubtractFrom
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Target -...- Variables)}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {(Target -...- Variables)};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAzGakAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMCTcTC8RGuABVmsBMAQIdhAWNiF4HNchF5ogRiEwHAAxYioFiAkwAdisF2u9OuwNBr0wEKhMNQADpuQA1Zp4JjRegKVGAhnXDFYgjXZRkojKJhIsUM6kWa7K8X0maOZDXNAMMaYVQpYjXaGwgBuYi8mHVdM19NVEARxCR0oAtNzOe7rnziAKhZgFItqQARCFqjXqqnhhK087iqNMx4stnmrnc87AYiYEGMAgihJo%2B30rwZIwyxW2iGhmVy1AKpWQrM5vOCBRe0VxyklxkglPgyHpr1%2BgPC0W97V4XX6w3G03pytIgD6FqjTpdbuunu5PtHguFIZjEcpx%2B7F0B31%2Bh3%2BV%2Bu2FUrEeto%2Bl%2Bvfx7lwO1wAssimFQXgMA4WTvCcgLJmCrJDhyI78geQYTucZZhMAv7/oBwFvDWOJ4gSRIEKS5JsgkqIgCAjbQW4%2B6Bh23JdvGb43HCQbSq%2BFxTsgy5MAoSgtBAf5NJhIECGyXCkNcyTblJZhkSAVreNWCSxrWGghnGHDLLQnD%2BLwfgcFopCoJwbjWNYEqrOs1ZmAkPCkAQmiacsADW%2BSchoAAcZhmAAnD5XD%2BJ5HlcFSVLSNpHCSLwLASBoGikPphnGRwvAKCA8UOQZmmkHAsAwIgICrAQKQwuQlBoA8dBxBErCbKoHkAGzug1kjXMAyC6lInJmLwmD4EQ/roHo/CCCIYjsFIMiCIoKjqFlpC6OJADuhIpJwPBaTpemOUZnAAPIwiV0qoFQ1z1U1LVtR11xdWY1wQB4lX0Ka5i2YsvCZVoywQEgFUpFVZAUBAf0AyAwBSMkNC0MCxBpRA0Q7dEYTNAAnutvBI8wxAo3t0TaJgDjo6QFXPAQe0MLQaPzVg0ReMAUK0LQaXcLwWAsIYwDiNTeA5iBFpBjtRoEzCmx2WEwIRYZtB4NEhLYx4WA7QSeAxSzpD88Q0TpJgoYghz0tGI5yxUAYwAKDyeCYEte0pIwRMjcIojiJNDszWoO2LfoHMoGZlj6DLaWQMsqApPUzPumM6A1qYljWGYSUa4NAtB10BP1C4DDuJ47R6CEYSDBUwziYUmQCJMfjF%2BkpcMHMQzxOJdhpz04ytNneQN7UTcCL0LS14X9e2C35d6DMvf5/MRfLAolkbBIm0cLpCU7clZ2Nc1rXtZ1kjdfduCECQ6o2Vw732UbywIJgTBYPEEAuSAkgJJyPkJGFGiSGYkgNXF/gNT5%2BicFFUgMVbKcgalwBqHkfLBQaoEAKz8GpL3mslVK6VT5ZW%2BvlH6hVDqlSBiDZ6NU2CcGaCwC0VJ3RMD1AYCsXAfKci4O5Xq/USB4CGuJB2Y1nbSFdkod281dDJBWkwNaLN56L0SrwZKB1iowmuCdVeF1WrIGoWhWh9D3L3Uev9Z6h8kgn0%2BtlLB%2BC4hlWBuSbRwxlEc1oVweKUMYZwwRvNTGqMiYuOxrjfGhM1Yk3zOTSmO0aZ0wZkzImbN9abEMvgXmjh%2BbM0MkLZAIsibi1qDtaWstUYK0iR9f0qs7Iay1koXW7MjAG1AOgvgptzaW2trbfSdkOFOwmtw2Qbs5qGQEV7Q2McrB%2BwyYHW%2BRlQ5ZHDpHaOvsLDx0kYnVhychmNxEn4CArhh7iTzmUOuegS71DWakKu9Q%2B4LA7t0buQ824V1Tksnu/Rx5bIbuc3IlzR63M2f3OeKw1iz2Pv/Be20kGcAUevKhHMbp0IYRoXezCXpH30WfUgF8r7DCGRFQBwC6FvypP4HyoUEjv0/pIcSEjdopVsKggxGD4BYKKkdUxxjiCEM2CQy6LAFAWl1BaNRUExhMP3oNYashOEtKmvIXhHSdCJFIEIkRG1fniOXvtHBx1TqqBZWyjlXKWRjE0eYgGuiEhwsqUY3Vz06UmuGOylIKRVy0OXNyggy5VXcLoA4ygTjDLuKpnZT1ni05E18YIfxVMomYFpvTMQoS1bhLKTk0g0Sm5xMFqoYWwIUmCDSfNDJcsUbZKVnkomhTtYlP1qhI2VTFQ1KtjbO2asmnjQkK06aYqPaSpUT7WO/SA7wGDiMgQzMtiR3bX0qZCc4hJ0GVPTuSyM5ZyebnTORyi77KKFkPZOysiLoHos%2BoNy9nbubrMO57yHl9D3S3TdHzp5fImmI/5SVAVOuuKy9l1xOV0PtVCvlujj4fXhYi6%2BlB55opAL5TkCQEj%2BECoSuK4GqQQMQfe0laUMrwtcpIfwT8QpUjih5SQ/kuBeTMAgiKCQ72SM4L%2B9B88eoIfI6SilywNYZGcJIIAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/subtract_from/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/subtract_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/subtract_from.test.hpp)
