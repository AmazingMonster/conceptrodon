<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyValues`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-2">To Index</a></p>

## Description

`Omennivore::ModifyValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Operation
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Operation&lt;Arg<sub>I<sub>0</sub></sub>&gt;::value, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Operation&lt;Arg<sub>I<sub>1</sub></sub>&gt;::value, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Operation&lt;Arg<sub>I<sub>n</sub></sub>&gt;::value, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyValues ::   typename...
               -> template<auto...> class...
               -> template<auto...>
```

## Structure

```C++
template<typename...>
struct ModifyValues
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to variables of indices `1, 3, 5` from `0, 1, 2, 3, 4, 5`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ModifyValues`.

```C++
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = ModifyValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Rail<UnaryMinus>
::Page<Args...>;

using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

using Result = Metafunction<0, 1, 2, 3, 4, 5>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ModifyValues` is similar to that of `Omennivore::InsertValues`.
We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

We will use `Prefix` to enumerate arguments like in `Varybivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct ModifyValues {};

/**** Base Case ****/
template<auto...I>
struct ModifyValues<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        // Note that `Shuttle` is instantiated by values
        // extracted from the template parameters.
        // This is because we will pack every variable
        // into `Vay`.
        -> Shuttle
        <
            FrontTargets::value...,
            Operation<Target::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ModifyValues<OtherSequences...>
            ::template Rail<Operation>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBKSAGykAA6oCoRODB7evnppGY4CoeFRLLHx/hq2mPZFDEIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teVy2EwNhQ%2BUjVQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxeZn2DEOXhOZzcBBuKUwAH0CMQmIQFADnoCAPQAKhxWOO2FUBFcADFiLJjrisRjAUSWCkDETIdDYcw2AA6Dlop7jYheBz4wkksmCU4AdisooAImcrOjnrT6UxGecFQzMJCmJdUBy2fdjocmAoFMchJgAI5eRjbUjHTVEHUANWaeCY0XoqP8D2ePL5BAFRIY6FJskhpotVvV5ydxBdbswCh1AM9gJM4sBxwzx1VSsjbjt2o5EUwAHdo7H3VzM8cvBkjMdlExgB8zpKTebLaDc0XS87Xe6dTay3344nk/5ZS8pTKU89sbjjgBZASoIgMG4U3HU%2BWYOlqjVa45DuNcn38pcMFcCO7o8XHcZKvDIfUCcaYVQpYi2g8ANzElrFFhHvQqbSuOYqgROmKUvWxCYDQqgbjiW5PNmypQjCjCsJgNoZAAXvCBBcmgnYpH6yiwfBnytoilrTnKTxzjiJoIJcBD0IhVI0juipofmo5etyNH8kILEEGxkaQbO0FLvgVA3E63jxhxyGobmzKYeynLJt6Ql%2BjJeByQplrGqmEoQTODHQRYhofHmSjKVxu45vu9ocgAkieumLhgBnyX%2B8aQj8IAgGEWCqHCSjhp2kJufxXKmemmaqUy3F7ucfFadg%2BoGEaxwAPKwki9SVpmp5kWSRAAErIrQiUZglzxVlWyWNU19XnHVbWZhiGLHAA6h8NbNokGjkXBeCqDF9yJiNWaoMcjA%2BHEOanCNwaCAAKs0TYEKiI26q1XWZmN8FTZ6OrrQQW3EDtCikJ1R09f1HzFnQtBZkiDAKPwxAsFmCAfOEhK2jdS2CAdTxHc1GGsh8107fdh1Q%2BpsM6tZyAANbw5gu0PZmJVtfejhPsRr6/u9%2BbHHg6A3LQEArHjGZPREK4fAQCBKqtGgiaxwGzXgxphPeggukS6DHNE67k8ZjPHE9b6IkwDiYOLVBkn97Ns6lK0pM0WFEsQCay09G0IALVPGrEohDccxYvW9xy65jC3fnEUu9seSNVk9YREFz56XmuJj7bLAC0eo82JwFe/jHUx21l3Y7twXS5gA6y1WBXLcV5xJyn/n3PnimI5DUMZujWPbTjChF5aibx58DzjhZR3JelWo6k8wCwTujC49ppdtTWYTAPWjbNv4rZYIc6kQNTtOQgHq53OcXc92wggetg/H0wzzdIyBdEvEjbdQtrvEd5l2WGgmHJr5gvebwT1a1qP1V0FRMGXu/tWr93D8b12nFfek5zL0VPhlNkbkbSQIAFKeV5GeHyhl/IejcEFEKgY3wRXbBGGK/EcIEHQMFUK2DIodm2JCWBwCBINUHlmc%2BalGEuQLLqT019cpZyKlkZ%2BZUv5VRqp1OhrdmEN0hBnbqvUBov2GqNCiE0zrb05LNP2i02BFVkYnKuuMQ4NyrCdBR5wPLnQ5Fom61cS5lyZlI%2B2tB3qKy%2Bj9DWANjhAz9NtMGBAIZWKzDDLCxxiR4ENldbRlirFPWkTbYOcjxqTXOPAkxuoVHzWAPNJWZJcqa2OPgYWlC9GSIljjO2jAszFnmhMW63irEGLiW4BJSi2QLmpugegSc7oSOsc9W2DsHHfRIM4wGCsQbAE8VUsuKN/GmmIugJOYTxl%2BM0myCubTZbPyrETR8z4vpEnJl%2BP2886YMwbuHdhkdxKrLjvQo6Zjbq1zThyOZUMuEPgEJCQJwS84gFToXL5/lHlHSab8Vp2ia6/MUunfJGZnk5zcFMgQMztF3J%2Banf5XVlkgrufXK5scm6SWxRmCBl82T30fv3ASR1h51gbE2T%2B09aCzwOYvZcy9IQksAVvHeKw94TirIfEBnVT6EtcmwrKBojSd3/qSrenVKVvxqp/ci39BF/3Xn3W%2BIqj58rxYxPElVuibAyK7Y4dkPiUhUsw9uwroF7NYbAm0EzFl5U1sQMMFCAoDz4fpFBik0EYNIeFcheCjEELvEQkhWCA24OivEkNTqAYuqjdsdV8U0wnwtWfJyF9hV6jFcaaFPCB7rK8oqgRdAhGpvxQwzN6oxGXJ8REwa9lok1MUTNDQc0FoMCWhormNzq7RLGVDFtRjpqmOFCE8xu1UVtQbd0uxH1DB9N%2Bv9QZwMPGAMHa3BZHx3njFmR0uWNiZFc2HXU0dST21%2B1SbaZAGTjRZJyU0aKkLD2FIIMUhgpTykgs3V1U99SdSApaZgNp06mqztevO3pTiV2uKGeuvuv62oOo%2BHCwM%2B6X0obRkrSuk7US1vJV1DZJMXw7LEDaqmNNDlhz1ASAMQZx0XLcAelD3lZJ%2BR9ZCONcRXURmTYWqxwVVLHB/lxwqLyGBrK6kJxhY8myQnRXhzFmULmEbajJ6tcma2VvES%2BvtycwV1weQe/Nrzzi7onTtJFno7lgarEB4FSnDP3LZHZzMpnJPnDQwiyd1nsBIoI5qhuQrWFsrVVJjMsqtO0u6PSjCc8qNMovCylVADwuJPuLvI%2BvKpz8rTdWlKBXLWsJzTldVYWn4Cci6/ET8qWz8NQKJ1LUrgGQVy9qyknWuvIR1ccDa8ZdoOSkl1kbnF6KvFBO8T4Fwri3HituIreYDzGIEnwuQzBiA3CaV2/Dk4eWlSaMTLZr53yfkpt8g%2B4pQ4eXaymW74D02QIQb6ZivMJIWRC53G60rnhRYXDjJgVAvCgnqJ/L1HGZbojrQd4hIAWBMAxvCf1OCoqUPOFwe4jyMHw8R3CZHgbo1uH8KHLgJPMedWxwjpHEaUdushAAVlDsTjHA8uTBSa24dbzQtthBrGzkA1LcxPG%2B61iyUWhBeBSAUFWeqFBeHpZ/M5wFzjVGOCTm0ZgbRM5tNINX9Okx4qi7L%2BXfp6v/aaEDkHBa3Cq5mMcTXxxAjHF1/rsceLiNwhvnEAgEAMEKCwp7tBxv6U2gl1L9IMv4wm/uNyjgaxaCcHp7wPwHAtCkFQJwZjlhrB3g2FsZswIeCkAIJoOPawMYgHp2YNkoozCSAABz1/pxoAAnFXjQiR6%2BBATxwSQvAWASA0NUFPaeM8cF4DXaoJfU9x9IHAWAMBEAgA2AQFIlxyCUDQHSOgcQIhYU4KoeviRQ6JEkMcYAyAnxSDZGYXgKtCAkGpnofgggRBiHYFIGQghFAqHUDP0gugMwxYSIKQnAPA8eieyepe6enAeUlwa%2BfoqAVAxwh%2Bx%2Bp%2B5%2Bl%2Bxw1%2BZgxwEAHg2%2B9An4ewXAKwvA0%2BWgawEASAW%2BKQO%2BZAFAEANBdBIAwAUgmuNA9KcQNcEA0Q0B0QYQ3OYBvA/BG2NweU0Q2g3Q0%2BReW%2BgCeUDAtANw0BWA0QXgwAeYdiNc3AvAWA8ORg4g/%2B%2BAsEPQrsWhaeb4%2BqRIQh5AggtQ0B1w0QSIm2HgWA0BiIeAA%2B2hpArsxA0QEekoO4hgwA1wRgpeawVABgwACgDoeAJYWcKeReL%2Bwgog4gn%2BSRP%2Bag0BgB%2BgQRKA1g1g%2BgeA0QNckAawqApEWQWhocPwLYpg2elgZgo%2BPhMYWAJR9MNQdQWQLggYUwfgMwIQCwZQFQ%2BQ6QmQAgvRIxhQWQgwQxIwMwXQPQAgfQkwng7QegCx9Qyx8wpQww8Q8xcwEx%2Bx/QMxuxEgawCgee2wZx%2BgkBpAI%2BvAY%2BKBR%2BJ%2BZ%2BF%2BV%2BkgN%2BuBuAD%2BRBhepBxeYRawAMTAWA8Q7RFekg/gbILe/gookgGgkgdeI0Gg9OiQLeNxve/eAQXAbIiQXAneLe9e%2BJ9OkgXA9OMJyQ9xMB4%2BtgIAU%2BYRc%2Bi%2BVBy%2B8B6%2BDBTBhBe%2BbAnAzQLA34ooocTA18dYXALebIOJ5h%2BARALRz%2Bsgb%2BqR0g6RSgmR/%2BugmuwBTAoB2hEBHASedx0BY%2BcBq%2BlwxwSBIMfJApQpBoIpYpEpuB%2BBtBhBpwwIZg/x5Bs%2BzJHJcQG%2BjBqABBIwvJ/Joc1prBLeXA1QHBBs3BvB/%2BIhghXhcZm24hkhDg1hshfc8hihyhmAqh6hYgtAWhReuhQRBhaeRhUheAph0BFhyAlwOwRevsdh/%2BDhThNwLhOwae7hnhRePhfhSgARehwRI8DJERjY0RsRxY8R1hSR8pH%2BipsgGRf%2BaeapORoRdRVglghRxR8AZRFRL4nA1RRCtR%2BRDRTRcQLR8YO5HRFZzgEArghxQQgYJxSwexqQox9QD5BQYxDAz5wx8xtQN5DQBxqx0w15ixQFxxgxpxRxKxuQfRswkFOxL51xFxmwVxJBGJepVJjxgZlpwpo8op4pbI7aEA3x0pzp/gJBZBgJpAwJoJlAOpfepAA%2B/gYpCJoo5Joooo/giJSQpJ%2Bp/%2BY%2BE%2BdJAJM%2BlBTJSAK%2BCBPpXpxAXJOwvJ6BLACg34T434hFao4wd%2BUpj%2BxCMwM5KRc5X%2B8gypS5OgAQpAGpWp4BmFUBglsBrJiByBilZ%2Bylqlxw6lYpmlfoeBfpjpcQFF/gbpDJnpfldBMlYVhBXyyAUucInlcI3lnuv0p%2BfAdAUZlAMZaeiZShCZAhSZEhUhaZfpchChOVZZOZahGhBZ1hxZ%2BhHZOhQSFZVZ/%2BNZdZ1hjZPeaeLZ3O7ZbhMY3ZvAvZ/hgR%2Bhw5YlfAkR45cRLI05cphlCQxli5WRFlBga5J5NgDhbRu59QWhGIQU651gjRDxzR1Ml5pRYF9Q3R7gIF8FAxSFf5b5Ux4xN1kx35v5cxF1vQwFcF6xAF4FWx71r594sFaxMF2xiwf55xlxH%2BOpWFBpnA5pSlKlalGlOY4wXxOlvxlFwVYlQJmAIJIw7RPeTFA%2BZgYp/g/g9OzepJQ%2BFNooneAlo%2BnAwl9JuNpAEJooN%2BHFXAUgLe7FMJXAooGJ/gdlTNNJ7pXKGJt%2BjNDxzNolFBawPhGQzgkgQAA)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/modify_values.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/modify_values.test.hpp)
