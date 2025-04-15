<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetVariadicTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typical_get_variadic_type_signature">To Index</a></p>

## Description

`Functivore::TypicalGetVariadicTypeSignature` accepts a function-like type and returns its variadic type signature via the alias member `type`.

## Type Signature

```Haskell
TypicalGetVariadicTypeSignature
 :: template<typename...>
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalGetVariadicTypeSignature
{
    using type = RESULT;
};
```

## Examples

We will extract the variadic type signature from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);
using SupposedVariadicTypeSignature = int(int, int*...);

/**** Tests ****/
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO>::type, SupposedTypeSignature>);

static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicAbominableFun>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(VariadicFunAddr)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicFO>::type, SupposedVariadicTypeSignature>);
```

## Implementation

The implementation of `TypicalGetVariadicTypeSignature` relies on dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIaAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8dnuwuJ2YtAAngAvaKvHa/AiYFiJAxwi4mADMbgIoLuzDYaOw/2GxC8DiBIIh0WUxFQRExdxRAHYrPSrmirKd/nCEUjMCj0bTGKweQAlTAEUgXfk4zAAOllJ2IwAUeIJBCJJOBYnJxEp1OpWMwaLcIoIEHlitl0rmyvZjP%2BF3tFy8qSMFwAbg08Ex8MgAPr8n2pYDMAjLHloq4XY2mhUKC1W1Fsv7M1n/DnwxFMZGGyWCyOi8U5tgWs1K1H406E4kEUmayHaqk0/WGqMli3iuPWpOJh2O53AN0er14X3%2BwPB0O8iMtmNti4dhOp5ML9mnTkZrN8/VSvNiiVbwXFmOdyvqsl1nWNu7N0XR82yuYXNAMYadky2049p3Bfvu4ie71%2BvqAZ4EGmYTuGO63rG94pjaLLLn8q7ptyvIYvubA7gW6EynKR5liqarVhqYLng2epXui053tK7b3o%2BAgvvhNrdg6X4ur%2B/7DoBdzAaBIbEGGqJTjerayrRlqwUm8GJmmXKZgam7YrmABiDDHqqVY1iRAwXIkXgRLQw5aVqF7kQpbiqXiDJMtJqZIXJcLZthFyWUxJwnkRZ7RIaqmbJ2IC6fphnIMZpG6vyPlqWW1lvrZK4nGu3JOUpGEALLwqpWEpTydSEaG6mEaF3noulLCqRcuVVqGIAgH5bkBXpBlGcRJlkRFJUZVF2AxUuMn2eu5mFjyykAPKdgJACOXh4AJLyTdNs0xWYABso01agdzEJmJAQPGNkEZpLV1j5Y31YFTUhUdxVuFgyC0PyEDmKtI3rZt23ELt8bdW%2B%2B0If8nzfID2y/ADFwAJJcvCjD1DU0LA/9QOI4cdkJch8nJQKGGueW7kaSSAAqWLDmIADiooAGqDt6hN3EIIHjgJi4WL2357nSEFXcQkV4jVHFDiOQFjmBjMLr1KMA0jIOAtgqisIiPJvAjSMwij5iosEd1eFgqFPqsiQEKWONK9sFxUF4DAOOkLyK6cwSGSEFzBNWZsMBATvik7mxWoyFwCfxDAXBorIMiytsMPbPJOwOf78z6Ltu4IHuCJsHY%2B37ywB0HCYh%2BLgJMBEqAsME%2Bf0Kb5uWwxcPI6cbH9icBdF8wBmYMp5uTo7ggJ7unsPk%2BjGJrXFyUzH3r14XxfN63AcQU7XdJwQKd0X3BCScbmxlxbsPJE70TWyrYcRxcTBeEQLnmyc6DoMQ1koitLs5whdvBDyx%2Bn8PnHIFPF9XzfT18wB99Yqrw%2BICbeggoSnzYCUKELsK7Pirr8DyFx8bPDhFzZidoHRPwdlHeO7sO4L17gxasP1faigzoHYOQCPxYPDs/Ah0cP5x3NnPAhi9LT0WfCQtO5DiCZyocmOCwCASXFgbDVAERtCYAcHveGFY8bVlGkzTB9oo4bWiO9XarCe6cOGDfdOfDKHZ2oVJYRSD378yURgmhqjBAXHUVtIgH05jaOTnGXR3DmYGP4cYwRpi/ogMuEILwiRciYHQDTTAdM%2BIThticQewTQkpHCZE6JDNBIRlnvgnukkEkhLCegCx1N9RpOFhkghriF7zj6iIk2KDhiyOrrjTMXEmAKCUI0CAwx0A1QUIKH0bTDQ02JrQMmBAinDlSfTMphpbr3X1NQc2X0ar8nFIkgpUyYki2wHtFULTfRtI6SabpvT%2BmDPRMM0QoyKZU0mSU6Z/FzJj0biXFu5seYgFWRVfJySIn3K2QpHZklJiOAOe06IxyCA9JAH0tgAzSxuEuaTG5I87m0wefldEcyHpf0vsQZZnz9RrJ%2BUoP56KAV4l2fI/Z8KjldKhacuF5zEVEyuWMiZyBNnpNmdI%2BZdxHorXqWgmqLsCVfPWb8rlMyyxUuaaC2lEL6XQthZgeFQzWXIvGbczl/zuXoiUWWFZRLvlJNJVKx5lKzEw1aeCzpJyYVnIRUi65WrUU6vJXqm6vKHr/y4qKj54qSXhI5eazFQKEIgptXS%2B1Kq1UXI1S6kNurpVuA5c8ie9Ap4BuNRK0lSaPXSvDYmSNYLo0ModUyp1Cb2XatDSLL1d0HoctxVfMVOag2FNrcmi1MrgXWtLYqmNjr1WJBGTWt1dbzLYoWU9IVAwQC%2Bt9P6w1hK7jEtNcGrtBae1Fr2fKw5g7y2xuZc68dH9J2GmbadbARq10moKfmqJGLtmyo4AsWgnAACsvA/AcC0KQVAnA3DWGsBcBQSwVhhjMKiHgpACCaDfQsAA1iAT9qJpT0k/Z%2B%2BkXBP1mC4AADgI1wLgZhpAfo4JIXgLBYgaFIL%2B/9gGOC8AUCAOj8G/1vtIHAWAMBEAgCWAQPSYoKAQDQAiOg0RQiCk4KoAjy0AC0y1JAXGAMgEKUhpRmF4OEwgJA8A9LaPwQQIgxDsCkDIQQigVDqE46QXQbQADuW1EicB4O%2Br9P6EMAc4CNE%2Bwn7FUAuHJxTynVPqYuJpswFwIAeAk/Qa%2BasuBzF4BxrQCwIBIHE6OhL5BKDZckzEYAUgzB8DoGg1jEAIjeYiMXYgoI3O8Fq8werI1JHSI47B8TbBBAjXDg1uzWAIheGAG4MQtBWPcF4FgFghhgDiEGzNDreBXTPG85gVQ0iT5rFgzvCj/7DIRC2vVjwWBvOqjwDRqbpBVvEALkoG4s2jD21AJxhYVADCKnJk8RzI1sSNcs8IK55npDGfkEoNQ3mHP6DmygEDlh9B4AiKxyACwNo1Emwp7p4ZTCWGsGYRjt2/xYBR7tdoy3nAQFcGMVopBAjPxmAMNouQ0gCBpzkFIrOGDTH6GUcncCuijE8C0PQdgKe1BGD0BnvPReS/ZxMSXPPoFlAWOB5YqwJAeY4N%2B%2Bj3mmPBfk0plTamNOSC0zF3AenEvQeS6lhDcwFgIEwF6AYZOUOSHQ3EVE9JJAaEkGR5aGgNCfuWgkCjVHSA0Zg9KZaXBloEbiMR5an7JC4a98tXXdmmMsbY3B%2B33G%2BOZYE/5k%2BeWxOFxy1JmTHAGgsFdPSBTTBHwGBdFwOI0ouDSn/bppxBm9Bg9M%2BICzYPrOQ7s7oUrzmmCuam1rnXDHeBMb80Jk%2BgWDehZU3dObkX2%2Bd40DFuLlfreojMClvPb3uNZYr4VsvBWEsoBb8VuI5Qyv3V3pQardnmsNAG7B7/rX2sHAAdutoY%2BswRvMhsRsxtaAJsAcZs5sFt/18ABJLZVtJtu9NtkBtsAc9tvNDtjtQRTs1h/0LsrtYNbt7tMBHsEDvx88PsmAvsfs/tGAAcB9gcJBQdZBR9bN/0J8YcjA4c8cEdDtSc0d9YrZOAscoUcd4cLACdF8icDM1tUd%2BcagXAGB3Bhdxg6cNCldZhmdOcah5ckhDD0g9CmdVDOg5ctDacxcBdFdpdldZduhjDJhGhzCVdFh1dzM58vMs9OB18jdm9t828O8u8Ld8AnFb4YMz80tENSAncXcYgydw9qMQBUR28/dMM4h6R6RUR/dJBlM2gF8fNmNbBc84iMtC8kBBNhNb9r8EtpM2BOBa8wsWAFBXQQpXRQjuRhgdNIj9NDNAdB8QdAduCod0jSAp8Z93N9BPNM9GNfMS9qxUAgtVA2iOiuiej5I9FYsGioQ1ZURYj88i879oh6j4sBhOjQkfRui4gfReiCAfR1jQdyt38qsas6tf8msvi2spEgDrsQDet%2BsIDMBhtRtxtJtYN4DntiDpsltUC1s7MNsts4QcDwF9teB8Cf8iDzs/wyDeAKDklqDntaCL96DGDMBft/trs2CzMOCxiIceCdBJjH9BCrBhCkdRCANxCGJOB1gTlccOS5DCdohidlCyc7C1CqcNDjD6cigZcDC8h0hjCWcagPDRcqhxdBcmgbDNSOgBAdSNSFcXC9STT3DHD9DVcIMNdks5jtc/DFiOBgsNjOi3Rti4RdjLcoiktji3tHdncsBkitcI8aMzB29URUQsM/dygNBIz6R48FjF9OAc92N7dkMQBCitNJB/cCNJB6RiNCMCMEz7TURHTkyyjKitdtMkzSi7d/Sbtd50hMygA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_variadic_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_variadic_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_variadic_type_signature.test.hpp)
