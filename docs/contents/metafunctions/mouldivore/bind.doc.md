<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Bind`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications">To Index</a></p>

## Description

`Mouldivore::Bind` accepts an operation.
Its first layer accepts a list of elements containing pegs and returns a function.
When invoked, the function replaces the pegs in the element list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Operation
-> E<sub>0</sub>, E<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., E<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>...
-> Operation&lt;E<sub>0</sub>, E<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., E<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind ::   template<typename...> class...
       -> typename...
       -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Bind
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Example

We will bind the second and the fourth parameter of `Operation` with `Vay<-2>, Vay<-4>` and reverse the order of the first and the third parameter.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = Bind<Operation>
::Mold<Peg<2>, Vay<-2>, Peg<1>, Vay<-4>>
::Mold<Args...>;

using SupposedResult = Operation<Vay<3>, Vay<-2>, Vay<1>, Vay<-4>>;

// The `void` at the end has not effect.
using Result = Metafunction<Vay<1>, Vay<3>, void>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Bind` is a special version of `CognateTransform` as it transforms pegs into elements from another list. Hence, their implementations are very similar.

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

We will pick out elements from the argument list of the finally-returned function via `Typelivore::TypicalAmong` in the following helper template.
It detects and transforms the pegs by a partial specialization, which is specialized by constraints.

```C++
template<typename Element>
struct Hidden
{ using type = Element; };

// This specialization will be used
// if `Pegful<Element> && Nonzero<Element> == true`.
template<typename Element>
requires Pegful<Element> && Nonzero<Element>
struct Hidden<Element> 
{
    // `Replacements...` are the arguments of the finally-returned function
    using type = TypicalAmong<Replacements...>
    ::template Page<Element.value - 1>
    ::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct Bind
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<typename...Replacements>
        struct Detail
        {
            template<typename Element>
            struct Hidden 
            { using type = Element; };

            template<typename Element>
            requires Pegful<Element> && Nonzero<Element>
            struct Hidden<Element>
            { 
                using type = TypicalAmong<Replacements...>
                ::template Page<Element::value - 1>
                ::type; 
            };

            using type = Operation<typename Hidden<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYA7KQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcXBq2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQlJqQqt7Z0FXLZTQxEjlWM1GgCUtqhexMjsHOaBEcjeWADUJoFuyJPoWFSX2CYaAILPLwD0AFQ/X2fKmGAZ1%2BXw%2B7wImBYaQMEIuVyyAC9MAB9AhnACSj3ek2IXgc/0B7xMyQsZ0mTEcyDOaAYk0wqjSxDJeCRqLOADcxF5MBcSZjkgARS6k4lCwJWV7vb6/AnAKheWjA35g14QqEwzCXNwEACeaUYrE1gSerxxeLR6IUAOARJJ7zODrJrUp1IEdIZTNiqE8HK5mtejt5FioYiUouFtrFEreqsh0IpRrcTC8RAxWNNBFx%2BMt1q1uaumON6bedoDjvJLpp7sZZy9Ps53n9L0DxIsme54fFkYjktj6oTWt1%2BuYbDOL2INqLrxpezSaOt8sVlwFGKthKu48n2BAIAbHa7vc%2BILOUQESOIqCVPxVLzV8Yhg71BtHm%2BLM8wc5PZ4Sl%2BXZwgm47nuPJgGAf4bD2MZHjKAAqep4KItAvCwAhAiCN53hqj7DoaAB0%2BHYPQbCCAoxZmvicFpAhYjIahQadtG4JxlhVxDs%2BPIAGJ4MQkxke2FHwYhtFGFqXE8QQxatvajqYQO8IsiiFrFoG5HzheRDKEwwA8lJgqQdJDqyQ%2B8mskpU7No6xCYAAjl43GYAo/6FmKAoQWWDqqf86moJp2laoWJoWQ6rZnF4WRGGcbFwiuYm8eKvJRkS7mRcxclJimqD4bhLzAFZkKMAQpHmYGYURECvk6YEK7KN5FVajleXEYVWWPDubH6XpB5QUZiZsSOnHcZMpCRU%2B/VnEImA0ugw19Xh%2BEAPIEAgCRFYFnmUdRSEoSJVyxQQw0TVNw2LctPEteZUnJT1WqIopabFeW/FqagGlaTpyUhaVEVRX%2BG1Cdtk5uCdK3nduIA9V5L0%2BW9/lnAAtGcZiteDT7Cgl%2BlXalxluLdbIBQZZxWbZ9mORAznLm5QVOlmz2vX5BbKY6n3hUCP1VWce1owxSVU9dJl3fjyVE3ZVmk%2BTVVcOsBOeTVUN1QzD3BSSoUsyN%2BrReNk0COgXOdYxmP9tjyZEFlDWYPlJGMw6X3lW9Guy3TiZmxbzX4ViXXc4e0o/GcFgROgV6gkxhu9VjvWjXNuGPNSBgKI5836sQFI5HxNO%2B/7trRoGfPahHbBZYRLurdLT2Q0QACyng6x9pZU9nYfYexWUAEofgYexNcXyUqaXAqYK0dAEy2teBqPMkN6xec8oXTVW2Pj1pwAEngdyMBc3fz8zZVq5VK4zwVuuJYe8%2Bjzns2jvvghzyfwsk7Ki5apfEnGhcZgAGzmG/X4MOeqCP0RB9FYn2puaM4y9V4MH/i7a%2Bm9lZD2AdbVWbMVx/RogDLUrd4wdwKgoUG8CEFtTDv8GGVwn5AT9PDM4XAYEEJRvqLmG8x6eygggxB29kFnATgkZOAhG5jXAVgSBpCAGW2NG1J8eCuon2YfglKIc%2BGR2dp3GhKtt6V1oAHP8fcB60Hqrlc2ndQbiPoVIpmeseb13kZPHC%2Bd8JKJwXPG2Zx1GaPZg7VALi9GNRwZIxi5ivYgkCUEm83s/gwQcoVQOISgkxOvDzQ4xxTiVWuAIWchVJJ9nvImY2l5BYvE8pXBgUMGA6kzk6ZOVIqwQg9GcHJvpGxBn5FGdGHtMksVzjYzAeCMxpy4UnJoGNbwTw6U3OxE4u4vCceXfuTB5QMAcDkDWfsGA6yuH0nhQjAo7k8VcfMbgkbGmGoU4ppSrhwwOdgYaezqGHOcQIE5Wo4aSHdlskAOy3CblwW7IsrTJmqyEF4NIRRMDoFbgoBUaI/zrIGVcY5RASlakCI8I59z4WnLcOc5Fdyiloq1Dcy52KHlnOeT8p4vyPgfDODBZaFw34aHZKgFeJg6W1LREtHkrgzgICYI5HFZxMBUCoJNAgUdXhOLBRCjW0zWhzIWbw2FqKBDovxSinFSrEVYoZUyn5%2Bt8nOgQsiHlSh2gQFuDuBQhpDVFTcBK2g%2B1xqAuBaChyELHhS3FBwTYtBOD%2BF4H4DgWhSCoE4G4aw1gyTbF2DpMwgQeCkAIJoT1mwADWARJC4Q0JILgyRAgaH8Bod%2Bb8zAAA5i36E4JIXgLAJAaDqP6wNwaOC8AUCAOoCaA2etIHAWAMBEAgG2AQNIKZyCUDQFCOgCQoiGk4KoYtb84Zv0kGcYAyAqRSFwmYXgILCAkBXnofgggRBiHYFIGQghFAqHUB20gug5gAHck5pE4DwL1Pq/WJqDZweaKYh1olQFQM4s752LuXauqh6azD/g8OO%2BgTJDiS14O2rQmwIBIDHVRWDI6IDoYnYkYAUgzB8DoBCHilBYgftiBENoOpn28Eo8wYgOp5qxG0MK2jpAx1NXmgwWgNHr1YFiF4YASZaC0BbdwXgWAWCGGAOIfj9kFnsgch%2B%2Bkk0Uz7DjRECE3rr20DwLEJOjGPBYA/ZmPA1aJOkCU8QL0Sg%2B7SaMHpowibNhUAMMABQAA1PAmA71cP9XGg9whEInukEFi9agP23v0DJlAYbLD6H0y2yAmxUBzhyOJuGtxlymEsNYMwDbrPEBXsplLvRhU5BcCsmYfg5hhCWBUKohRMjZAEDV5rxQcjDEa6scrcrmgLHa3MOwFWBADHaN10Y1R5iDCGzNibDWpsSE2AoSNexlvlo4L60g9beCNsA3OhdS6V1rog/%2BXAO64MxoQ/GlzmxlpMCwIkCAKaQCSECLhAAnIEZIkhM1mEkHSvNb9PubcraQatsbcJvy4G/Ytn3i2w/8Fm/w32347Y/Y25trbbsdpQ721D/af3DooNh1AMHJ3To4G0Fg7JkhwyYDHGTVDPu4S4Bmrd%2BAiDFfQPu2QR7xCnvC0oSL17dCEYfUwJ9EnX1bffdext37B0pjOP%2B2pxBaf08ZycZnXBWfs40FB8nGGEiv0CGYdYiGXNdrQ8b3DWGcOwZADTuncMddGD17UIjdqVpkYo1Rxj7H6PUeY6xhw7HOMFW47xj9AmhMibE%2BxqTMm5OBvwFZRTynr2qeQOp9jWmGgfr0wZ6jxn9iBrMxZuN1nbOYHsynsq1u3NaS8z5vzw52NBYF6Fs98gRdXsDeLmLznctWAS8X5LL2g3pbdJwLLBBVkClH/lwrCQeelanyN/rVX3CeC6Hoer5QltzCKK13Ie/ZjpBa00SbKxptb6aONjoF/at9cfwsW/TXhuDZf3ockC2j878NtVsdh1tJZNtttdtP0OB1dNcGcmcIo9c2cM1zsucSAzcbskMk1SAHsntKBZdwdIdWdM1khUdkgc1JAAdF05goCsdbAccsD8d4BCcB1f0Hc7dYMp02BOAacQMWAFB2QqR2QkCNRJhOdLs905gu8QsJAwtZAIsB8dAQBghJdpcX0ID5cG0v1ic/0ANeCl1%2BDBCOQRCExJgjcKcrtAhAhLdcdkMbcUAOCEh2CLDdxkAgVkRhDPtkRRCCBDUNdF1vcSMW0IByNr1g9A9LNwimMWM2NLNI9BBo8%2BM09MBBNhMxBE9LNk9HNy9JMFNHAlNxNA0c889LMC8dNA1i9DMdQy9TNisq9eAa9Mg69IQG9nM8c%2BB3NW9fN/NO9%2BcZChd5D%2B8otlDh9jB4sbAJ94BUsZ9aROAPgzVl9LACs9sisStJ8VsGhRs/AIBXA5tD9lgv8r9Os2tf8T9r8utFsgDhtNj%2Bsn85sH9%2BgP9LjDj/9n98hX9XjP9VgVs1sT1ZdIDMdOBYC%2BCBChCTCIQzCIALtucMCbDGD7tMBHsxgp8dNCCQAzBWcrD/B80s1a0rDkg4cMcFdOBsc207tSBU1JB/Avt/Bi135PtJBPsc0fsuBggdNAhNC9sSTbDsCdNN0iStCm0eT1hNhrMshnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/bind.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bind.test.hpp)
