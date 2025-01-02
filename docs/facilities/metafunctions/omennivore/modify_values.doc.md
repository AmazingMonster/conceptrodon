<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-modify-values">To Index</a></p>

## Description

`Omennivore::ModifyValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;::value, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;::value, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;::value, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyValues
 :: typename...
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
/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = ModifyValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

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

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the items at the intended positions.

```C++
template<typename, auto>
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
            typename Target,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            Target,
            // Collect the rest.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            Operation<Target::value>::value,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
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
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            Operation<FirstTarget::value>::value,
            decltype(middle_args)::value...,
            Operation<SecondTarget::value>::value,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
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
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                ModifyValues<OtherSequences...>
                ::template Rail<Operation>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Page
        <
            decltype(front_args)::value...,
            Operation<FirstTarget::value>::value,
            decltype(middle_args)::value...,
            Operation<SecondTarget::value>::value
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYa0gAOqAqETgwe3r4BwemZjgLhkTEs8YnJ0naYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQlJKbbNre35XQpTQxEjlWM1AJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimKmujMh4mAoPp1e39wuQLO/xu1zBZkCEWQ3iwDxMgTcXkctEIAE8EdhweDAYcHthVARXAAxYiyX4nUFElipAxEhFuAhot7MNgAOg5mPB82IXgc%2BMJJLJgnhAHYrKKngirLdwdTaUx6Yj5XTMAymMjUBy2ZiHjCmAofkJMABHLwfTCkB4aojagBqLTwTFi9AUXNuPL5BAFRIY6FJsgZxrNFoZDuITpd321XMCWNl4vBD2TDxVirViJtWo5UUwAHdw5HXe6bimHl5MkYHsomMBMPDAk8HsHzQxdgzcwXHc7XdqrYWe9HOXHpdjJaPZQDTg8HWiKccqZgaar1ZqZ92oyXPfzZ2OLA95oq8Mg9QJ5phVKliNa1wA3MTmsUWAeb8eBfcmN8ysFTx7KYiYDQqjzpccpLgqSqMsyjCsJaN5ECWaBtq83r/oBeDAQiTYELyGbfji05CAgyIEPQIGLsu6arraw7xjc27ekRJH0BOP53MCHEggRjwAJLLkujDNH05HcZxnGgmBlGQUyLKwTGI4ejhXoPAAshgeBUGiDreN8T6flK77Yr%2BxwPBYBr1m45kibcaaQVm2o8VuSn8mp%2BCadp5puoi8zoCAIARFgqgAPpKCGyEMjx8lYgpYKJrcZa2RmjLgSumaalFeoGIaDwAPJvMQR4CCWZYMdWZJEAASkwdBJimn7fmWCUpVR8WNcmDK1W1CXQay9YACotHWBCkJ1XXJjJMHshyZnIAA1jcxDAG6rVtcVXWHo4J5Iee960PBqAPHg6BorQo1lhAZ1dfs%2BwCqkhjoPCABsGhoUBEWYjGz2pgdaBeCKg0%2BIJPzxPwAGpgg9ZTENOorWNZXoao71xvt2pUMKBBBYNCgjbDY3XQ8fUFQwCigyw4P1pEhLWotgOCDDpZw8mA2LZgw2XW1%2BO5L05MPAB8z04zyYzfNi0KDGuMpms7MPAAtLqTEEKRaoS%2B1iLS2WWAwhN1Do5jotrH5u3mn26spnlCSFQwDLM0NhsPhm2B2zpOMM4zwsLUtTvG5yKsNtF%2BG%2B4l1HZmyNzAABAmCF5dFjRWETANWtb1lhDya7Q2tHSdEC7oiYcR2wUdcomkramsUuGbD%2BmsaNQfKs1dnpbRmUGmLHJ55gkcENHo1x1WVV0A2Tb/qglXVadufhx3Bdd1F1dfkZNy15ZjdsjxVr2RyABSTm8i56nufbXluD5fkBReIWmq27aIpFtFWif/l%2BufoVX0lm%2BzzF9U1/XSVLxvOrI31Nlc2BU%2BhrWTKVYeo8aqVziq7RqQdfYdV9t1WSbAHjEjwMQeYNtWYu0FqmHqsFmz1AEOgXBbMUEpgmr1bU7tRbS3AY1Dax5TzEyJLtfah1jqnV9hdKhyZ8YEjun6J6L0AJvRvh9TkX0iCnj%2Bt6AG09gaARIJDCGDwaDYO9FDVmAtBavQwkjbAKMORo1kHrJa%2BDBb40JoYEmJAyYEA0ZTRRNNp76MZpg7RFDrGMyEZee6YjDGI0RNvOMn0NDfQeMAA6TBkBkmys4%2Bs%2BBDzIQePEAgeYO4MFTHmA6uiZ6m2TCEhk4STH/xYEddA9BLHY2KQ8WxRMHHECcS4i8bjgC0wIJ4uGxokLkMGnghpnNPDc2Sbzb4PSGn0KWuLeBZYpa%2BzlsjBWStGFqwEaneo6doI6wsVjA2IAjaYBNlskBlsGTeJwUMggXsHb3L8XDNO2sqnoBqZgOpRyTlnIWV1C5YDET9LIRQ%2B5mJHkzPiSLT2xz7bzLGrGAOfzxo/2Dtqdundu6%2B17gnGsdZB7bK1nszOtBs5MAxBPfOQMi4SieKXcuDU6rz0nPApef8V66iAa3UOk9MVMJxQ8fue0U5QNQEKhkGLlEf3wsytiuJBX1G2JkW8FkrJ/EkhBJK/816mLZJvK0NC5Ichysk4gLYLRYvos5b0rkNJaUPgyB%2BZ9gov1DDfKK98CC%2BUfoFC%2BYVr5uHfnfXKprzXIW5SWL%2BsM2WorSjRABJiuW5XypcmKJVrVlRHmKseo0o3ItTKipBmz82oMmvWa5BBfENMNeg4Ffoq1bJrac6aUKPbLXzUw9NR4tpng4WILhJLpb8JLXVLZASREPRMM9UpUiIkyKiXI36/13FAwyaosGEytHzFTLc3pY0Z1uEcsjf%2B5jBB1KeXjG6djiakx5q46mXSPENIrQ2kdgibrCKCVO8RCMynSJ1LIg6sTrQJIyD8CZqTmjpMydkxgeSCm3LFg0g95TdVvI%2BeekZV7mm3omfepRgk91dTrYMlmlC32NJulzeoOiNF82mVs2ZEbfZLPzSskxBJfT%2BnRhstwDSXnQQacOghZZbUHx0kfE1EMzWXwtbPLZZY/KJUFTmxEALsidsFqfHhEAmNfxLhyVjBCjNdU08mJTP9E51l4/xnZ2tT0Y0Ofc35BD1NFURC%2B25YK4wQq2QJt4EB0O1Kc7CnSLnBZuatkC0h9avOhfNOC%2BLysO0jgrmxMa7L42SupWmrqAq8XJ0bIS3ZAWSVkopW4bLhcRzFzpYZhlubZXfykr/WNy942cqytyqrXd%2BWVgTkKglorxWUqnkDaVY4DJItxGJUCxk8QElYLSes6r5uzYkrKSE0JYSFbcEhXYqReuf3mw8OQzBiBohUhECs1lF5tazA8I9dFSpnZaJd677a81ds2mw88l5rwPZOY1iwMtHJNaaydtZZFVt3Za2i2i3IM1Q7wgveVKlWZMCoH9BoAhbuZZDm2ksAr0fNCx22YSKcxP2ok9iYt6bvUsCYLNT5zq/WvwZFwTETyH6M%2BZ0FVnrrwqIkCDLLgouuejR50zlnT8XWyaF24fwMsRec8/jFPyI23CvYu1dhgFYSx%2BQKxK0WE2WXyqEF4VIRRMDoAqt8Lw6dbsCot1bjINu7cKAd96FOyOGQaCtKLq0ZgA/BAeNIWW/hEWo%2BnB7r3Tv%2BsKs947ynGOyc46i24f3DwuBB6tKH8PkfUvTenH1KZt2WHIExoaBIBAIAPwULBKvDJY/pytC763tv7fp0xAyjgGxaCcH8LwPwHAtCkFQJwPjlhrAHi2DsZOkIeCkDuaPvvGxZoBEkGyDQAAOMwZgACcB%2BuD%2BF3zvrgopRTSAHxwSQvAWASA0P7kfY%2BJ8cF4AoEA/uV9aA2HAWAMAiAIAWwBAqQyI5AlAaANIdACQUQsEnAqgO%2Bj0Msj0kgMSyAJ4UgbIZgvANuhAJAR0eg/AggIgYg7AUgMgggigKg6gq%2BpAugOeeYBUqQnAPA/eg%2Bw%2BmgvAb%2BOUyIYB3oqAVADwiByBqB6BmBW%2BZgDwEAHg0B9A145ggQXAawvAP%2BfepAEASAUBqQMBZAFAEA2huhIAwAUgweNA6cCQn%2BEAsQXBpAsQEQb2rBvA9h52aIOUsQ2gNGThpAUB08OUDAtAaIthWAsQXgwAlktAtAn%2B3AvAWAjORg4gdB%2BAAEDQKq0RY%2BF4iqRI3hEQRIN%2BY%2BqIsQBUF2HgWAthOEeAD%2BMRpAKqxAsQbuLw8RwAqIRgXBGwVABgS0doXweY5sI%2BS%2BxBwgog4gFBgx1BagthDB%2Bghgxg1g1g%2BgeAsQn%2BkAGwqAh22Q0RMsPkWEpg0%2BlgyQ3BtREYWAyxEAGwdQ6eLgfoMwfgOeYQSwFQVQegRQWQAgNxzxGQrxDAwwjxYwOeFxfQAw0wngHQegAJjQCwPxowiQ/xCw7xsJgwUJKwMJ5xc%2BuwEg7BHAQ%2BpAL%2B3BnAwhSBKBaBwAGB2ekh0huA%2BBChi%2BKhy%2BbRGwEMTAWAiQZxpAG%2BkggQbIB%2BgQV%2BKQZgkgz0Gg/gj0B%2B%2BgnAd%2BpAD%2BShbIj0XAj0O%2BB%2B5%2Bj0/gkgJ%2B3Jj0OJthb%2BH%2BX%2BdJq%2Bf%2BgBmhwBfB4B%2Bhhh8hcBbAnALQLAt4ooMsTAzcVYXAB%2BbIXA2%2BuB%2BARAxxRBsgpBIx0gYxSgExdBugweTBTALBMRmJ2JuJ4%2BnAvBoByIDwghBJohaB%2Bozprp7pUSMhqAchCQ8IkIZgtJahf%2BWh%2BZOh8hEBBhlZRhmZJhx%2B/u5hRI2ClANhdBLhjh1RXZF27hnhDg3hvhgk/hgRwRmAoR4RYgUR3hcRMxiRY%2ByRNGeAaRthmRyAyIewS%2BuRPQthhRxRaIpRewY%2BFRVRS%2BtR9RSgjR858cbRfAnRCg3R%2BYfR3hgx/p5BgZsg4xtBY%2BYZ0xrRuxVglgCxSx8Aqx6xZ4nAWxXqOxcx%2Bxr%2BRxR03wYF3QvQ2QVx7gIJ%2BQdxfoSJTxOeLxfQ8JpAhF2QeFfxqFy5AgQJbQWFtxlF6eNF5FMJkwgwxFh4rQzFGJmw2w6JyhYpWJnBdBb%2BaZRJTpCcLpbp2%2BFJXpJARZShpZ9JpAjJzJlAmJEpUprpKQoo/gB%2Bl%2BgQkg/JqBOecZ2ptgupZZGhhpSAIB/BNZ5psB8BHANpYhLACgt4J4t4klqo8wnpVJhBOeb5wxH5lB8gwZP5OgIAwQEZUZbBAlsZWpCZJpAhQhqgrl7lnl3l6Y26eZBZ1JgQgQil%2BpGhFZeV9ldZ8hxyyAVuQUXlB%2BQUPlGMaVgZdArZVhHZY%2BvZQRPZDhfZHhXh1Rw5ggo53Vi5E5YRERM51Rc5CRx5sRWCy5q5dB65m5ORggu5dB%2B5b2R55REYZ5vAF5DRS4N5rRxVHRtYj5PRL51RQVZBEgn5VB4VkxUV/5sxexNghRpx4FfQ0R%2BwJ8gF1gBx4%2BiFJxKF4JzgEArgxF9x5Q0JHxxQ2QxFpFpQDxcN/xPQVF/QcJdFYJGNjFkJqNyJYJ2NeQ9FHFiwsNRN/FCgaJ5BMZQlr%2B%2BJzVDwblHlDwdVbIjVMlVJ8lyhqhSlKlYwrJN%2BGlSQrpBV/gp%2BqpT%2BBVoo8pmpwlnAOp3%2BSl7J/gXJF%2BooT%2BO%2Bkgx%2BXAe%2BZgGpN%2BgQDNeJ7%2Bepv%2BmJOBCtjN5tZZGwtRmQzgkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/modify_values/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/modify_values.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/modify_values.test.hpp)
