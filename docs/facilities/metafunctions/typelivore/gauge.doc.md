<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Gauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-gauge">To Index</a></p>

## Description

`Typelivore::Gauge` accepts a list of elements.
Its first layer accepts a list of transformations and returns a function.
When invoked by an operation, the function instantiates the transformations using the elements via a process similar to pack expansion.
Then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transfs<sub>0</sub>&lt;E&gt;::value, Transfs<sub>1</sub>&lt;E&gt;::value, ..., Transfs<sub>n</sub>&lt;E&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;::value, Transf&lt;E<sub>1</sub>&gt;::value, ..., Transf&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
Gauge
 :: typename... 
 -> template<typename...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename>
struct Gauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};


template<typename...>
struct Gauge
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};


template<typename...>
struct Gauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Gauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= Gauge<std::integral_constant<int, 0>>
::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddOne>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::Gauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Gauge
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};

template<typename Element>
struct Gauge<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Element>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEpJmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlSKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQlJtc2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIsqfRsgkx99yeXN3fnAPOv2uV2uBEwLwM4JMAGY3AQAJ6pRisTAAOgx2DejAIClh2FBc2IXgc9wA4kwvMBMKCTIErDd7kz7ns9vcALJeWiOV6Ye5YiE4vGM5msjlcnn0e4eD6LYjC67M%2B7gyGfGlwlWvNWw%2BFIlFsDFo/H3ZAGBQKQ0AEUwADc8Ds8TCCSKmUSSQR7spiKgiAAlVBMdCgpV0iz3YNK5maqHq%2BEQrXQuGUoiG42mpjm%2B4AeWRxE%2B2XxEcj9zdpOtzToRcjofDLuLzK8mSMyr14ZhluzufzAh11rtDp1AveuPxIBANrEXnRGMLMIZivrdMtsPnVaV0e1GvjMZ1ydQqadJrNFox12AxEwgsEjudC%2BLjYiwHuvqYdDbHfLr9oOrPF6vuIPbAx0RZEVyrJcwJuKsxU5bk8F5flsWvaC2QEPkZQrSJiCrDdEzjVU8JA/VpyNQ900zPt7XVW8lVLD0vR9VB/UDXtbSows6xrNco23Td8ITWM90Ao8MwUTsEm7BgOLvSM6PuT9KzrEN6VrGT63uB9myI99xLzPpWP7WMhyFUdx0nEjZ3ndSILnWklJ4gjY1wwSvBTGcyOPQ1f0vYcb24plNKfF831hD9MArb84W8/8T1IoCQCIyCZJs1c62cnV0o1PVmANdzsBE80rTYgcnSrQLnwDdAdIYv1KoMqjYss2lAmXWyoJuTLdWRHK%2BWMwRpLkikqSMpCCGk0MUOzSJEP/SbYMldDZFfLCFXXXjCPWpzstRYTyNiyiSpo5k5Jqpi6s4lT/OVTaMpupNXP3PKCrEnMJP00r7NdAhiTLcKvyurjPsjcrtNC3TJPqkq3D6sanTHCdvAs0q2rU5kUrs1GmU6zqhKevavPPHyTI%2BzGNKbIKvx0hTIrcaLfMA4C9SS5TWtSmTsburriN2zyMQOzA/LrcrmKqsHTpFyGBcApL0fa25AQVn5QX%2BA57gAMTweUPWwVRWAQpW/kVo3gVpMwYQiU0vCwNs3DQBgdlSEcSeVk57gAFTzBgFH4YgWEksSDbBTmiJ6mbhwG773Xua50HQAAtBJUFUwGZLmfNkBNAQ5kwVRUmIe493uBGp3A%2BkYfh8yUuTlqZY64PtrYMOcQjn6PRj9As0iZqwyrNPHAzu3s9z/PC%2BLmkLoscuzMR8NLHuLgq%2Ba1mMexhvetGluo/bt2AHdUG71TaOafvM698Fh4Lh6i8riep7H2ewzMReoJrlGXYeV69Oyb4LlBHGHuljcOSn8IZv0Ng8IQXhUhFEwOgX0AsJQ/yOMCcqkDoEZFgfAhQiCwYgPem4DQpB55EKfsjNmKtnwIO5Egg4KDyaUOwdQ2k7ZySUmpDqOY6AxwRHBOeMQAB9QezR%2Bpwh4UQjQs5bxjgllFWOCdvREPbp3TAijY6733iTaR/04R4ILGQjGFC3YCw9IHPu9p%2BGiQSAQCAnCxwKFRBYx0bgsESiIWgmBcCqGw2wKsWu8sjaK2BBQoQ9QBBVR1nrKUgcVYBKBAY127iMGeMYSY3%2BNxUFQI8S47k/CuA6V0T2OEXASFEJhE1OWFDsmpOQaCYWXjck6SGuwuEvcCBcJADwzAfDaCCKzsI2GbgxH3AkU6UgrT2mdO6b0s%2BhgBlDIXqM8Z3DBBdLzD0oRsydRDNIbeUyMjaax2UdJLRlYdFdnegSMB/ijju2MTQ4EZjkCOKUK0GxbS7EOIzDqKpuS3GZKST8hZPi/ExNidE12bsECa3CbrSEfJwVgriRUhJ/ylDJMQYHDJ6C0U/LMPk85eiCElPuJIcpIJwE3Kqfc2p9DcWNLYbGJZHSVlTI2SIwZghxH4jGXWWxzLeFrOmWndl8zuVMsmYKtlczOX3B2cw%2BK%2Bz27yNQKojukRVXqOOSAYKNMClSX0cih4Ri5jUqAcfcxljXl8vsWwRx3z6kpHuIknFDr8S%2BLnBwdYtBOD%2BF4H4DgWhSCoE4G4aw1gSybG2HycwMIeCkAIJoT16wADWARJBog0AADjMGYAAnLmrg/gs2Zq4IEQI0hvUcEkLwFgEgNCEP9YG4NHBeAKBAIQhNAbPWkDgLAGAiAQCbAIKkVy5BKBoBeHQBIURUScFUJmgAbAAWgXZIe4wBkAZykGiMwvBYGEBIHgLhxT%2BCCBEGIdgUgZCCEUCodQXbSC6GKTvPMqROA8C9T6v1iag2cCzK5EdHpUBUHuPO5dq712bvnumvFEAPCTvoPnGNXBVi8E7VodYEAkATtSFOsgFAIA4bwyAYANQ%2BB0HBPKSgsQf2xAiC0BE77eB0eYMQBEWZYjaHqJ2uNE7hyd1oIxh9WBYhUjcGIWgbbuC8CwH7Iw4hhOa243gG0Asf053qK5XYcbOmVsDbQPAsQ8xsY8FgH9308C1uk6QVTxBYgYOtHJ4ABmjCJvWFQAwwAFAADU8CYB3q9f1cbT3CFEOIK9IXb1qB/U%2B/QhhjBhssPoQzbbIDrFQI7bIUml2cNCqYSw1gzBNts8QI9am0vdF6NkFwDB3CeA6HoMIiwKhVD0EULIAhph%2BGKe1vowwWsrEq8pgQAwpj1fyMUuoDQRvzH66Maoth5hdb0GnVoc3ljVHWAoSNOwJCfo4L60gjbeDNtA4ulda6N1bpg/cCAuAD1IbNihtDbn1gIEwIGMYEAU0gEkDCNEuaYTlo0MkSQC763%2BAXbm/QnBq2kFrbGtEC6uALszbmktC7/CSELYDhdR2f3Ntbe2%2BNbme39qw4OgDo6CNEcQzOtgnAWgsBtIEJdTARLNi4LmtEXAM17vwEQUrx7r2hYvUkEXUX72Bt0CkF9TA33Sf24d47v6OD/uHa5e4wGzvgbXemTn3PecaFu/B3DiHZ4wjMKhknXbMPYdQAhhIY7CMO7N2MfXpGC2EJoNyBIbaIA0YfSxhjTHSDB7YxxrjDhQ98ZxAJoTgaRNiYk1JuNsn4sKcT0phoqmpOBo08gLTofdM/oM0ZhjpndiBos1ZuNtn7NKEcxnx8pOPNMC875/zgXQ8hfPeF6QkWlDRYfTLuLrn8tWCS2X1L32g2ZazpwHLbS8uJYsEVk7JWysz62z0YbfgICuGW8Upr5R5ttYyB1nI43utpAv315rZ/Ju7%2Bm/0Jb1%2BVvP76KNhYp%2BNsrbf3kDfqtj/ksK1ihhsFsLtuAZWsrgTpwDrhdhzk%2BFzjzhmrdvdoLhbs9jbhhm9h9lgIkLPpWnDgjtziDoEP4LmmWjCKDqusUiroTrYMTuht2r2gOkOoBs7rTtOrOhwEzhBiwAoDaBnDaCgTGHMPzg9kenoL3mFpegPrIJLjFiADCKQHLgrh%2BjDgdt%2Bg%2Bs2uroBlriBqoAIUISIWIWqCanBq7nhhbjCNbiwXbigNYYhlwc4WMMIdAvwqIbmvwuIQQPwsYQPhRn7tRrRvRmxqHuHuxpxtxjHg7vxgwIJj%2BknsAOJrQJJqHunvJlXjJtno4LnupqoJpuCMXisnprwGXsZgiJXuZqVrXrwPXg5hCM3q5rbnwJ5j5n5gFt1D3rIH3vIRLkPlLjoCoWPglgVlPilvAOlvPl7JwHsLYhPoVsVgkELuVrPlNn0DVnVoAY1rVutmAbfsUNkEfkcZfgcYNpsY0AAQ1k/lVjNoMBcQtsAaccAU8XthAVGh8TAToU2vAYEfcIIcIUXOYeCJYRgSQFgfYa9qQO9p9oQftiQSAHmmiDCDCP4EWtjvWmiYEKjvjroZwETh2jCampIP4ADqWoEPWpmpIAWlwNmmYHjpWjCL8SdoSTgUmlobuviX8S2hyasOsLZpkM4JIEAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/gauge/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/gauge.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/gauge.test.hpp)
