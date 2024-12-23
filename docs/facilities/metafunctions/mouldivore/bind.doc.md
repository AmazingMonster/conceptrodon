<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Bind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind">To Index</a></p>

## Description

`Mouldivore::Bind` accepts an operation.
Its first layer accepts a list of elements containing pegs and returns a function.
When invoked, the function replaces the pegs in the element list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> E<sub>0</sub>, E<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., E<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., E<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind
 :: template<typename...> class...
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
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Bind<Operation>
::Mold<Peg<2>, Vay<-2>, Peg<1>, Vay<-4>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<3>, Vay<-2>, Vay<1>, Vay<-4>>;

/**** Result ****/
// The `void` at the end has not effect.
using Result = Metafunction<Vay<1>, Vay<3>, void>;

/**** Test ****/
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
/**** IsPeg ****/
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

/**** Pegful ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEpIAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJUql2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSXUtbR0F3QpTwxGjVeO1AJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimGmujMh4mAoPp1e39wuQLO/xu1zBZkCEWQ3iwDxMgTcyHm6CwVAR2HB4MBhweABUAJ5vWh4ABuJHYIEJaTwoloNxYAmAvxOoOYbAUaSYu3xRN6ZIp8IA7FZbuCCJgWGkDBKEW4CHz2ZgAHSq7D0NiCBQY8HzYheBy8ml0hlM4VWIVPBGisG3CVSmWYOUKt5Kh4AMTwxHmOtueoNBCNtLEpqMcs93oIvrBIvBD3jD3t0qYssRWQAXpgAPqBgCS0YTD39huUxFQRGUTGAmHNJkt1qxt0LScdcoz2bzBYTxEwAEcvF7vg8IPnAlaxxo1nGE8XA6Xy6hK9W5aPMU2E3WLA8vFkjIm%2BfCxx6vT7Alu6%2BObdP4y2U07EUwvERVcqbsAe5LGARtYE1zdCzuETMkuNYIk8DzzhWVb3m4b4fpq34vhiIAgC695XvWZ6Njct6pvKiqsDWEbzKQ%2B6uoRDxCA0AjoKRaFKi%2BADyBAIAkP5/rOQYmoyYaIsRBCkVRaAMLRDzMax3pIb%2BWKxuuN6SsmeHtjmDyrteRYEPqJZllB1bwnJ5rbruzJoYe4HUsG9I8cAcriWxUnYChuE1pBi7QSuDwALQPGYyGoXy1rCpe2HNgprZpngmYqWpBk9v2g4/COYFgZO6mca5IErl28abkZQFkaBR78YFF4NmKBnOW2kUdqp2UPHFA49olo7jk8XBTgZ6U6W5y6IjF/4biKeV7qZYGUdRIklZhV4VWFd5yo%2Bz6qnBmCflqdWAXuIFmRB3WZYiK1rYhqo6lhYrTdhpXlXcpwQZgzJ/OKc0SoebjKZ20l%2BppAZ3TZ51bvMKa0g8wnzJgqhpMQRbVSppJiF4oEivm01BWVto3Y8uYKMo90sscoKVYi9GEdGnFYzjf0xjahaA44yAgwIYMQ1DsSoJ4Dxw94ToGZuVBiEopVnTGwXXYTbiLagtWfTcZPY/dcoU1l0nS5uaUtHTDMMEzkMPKz7Ocwj6mbt9ToXedIvoziv1UF4tB45cT0OvNRMEWwDw3MQNnS8JuxpHO9023bY3k/LB2e35BvodhVtRAImZlvbBPPTBxNux7Xt/j7ryBrHDDx5LY0QOnKGRw8YBgGNqVC9iwK1yCNeYw6R1AwIicN3Xdegu3uIWBE6Bt3ayfOkPLvkWwDkgwYCg/IxbzEC3DCk99hq95N/3qWLqcqmqGpfuxataXO3UALKeOgRuyQNhbyU7eFby%2BABKrwGLsCH7wZNPL4GLwtHQ6mFqrD%2B18b6KRTq7Gs6ojp1WAfGTiAAJPAqJGD6SvjAnKQ1NomQPGNSBCEpoW3/jAze4CHi4K/NAmBDUErW1tnKMhggMTwjMMkcwyQHi53znQ3eDDpZoM/ofB4CCkGL0RPQqMvC%2BHoPPEAyRmCCo7WpPyckPYUIWW4kyOUT9kyvz3g5QhkinLJwgu5UR3CCAl3hjWbyXAKEGP8m8EqMjr6CxmqgtBcjRpHlngkBezoSFCKwCItwYj2JOT5HooWaCXEhSISPfCY9t6vnfKtN%2BtjhrMlPrQfuY0f5MD/gdZJR0FAOTCQ4yJg0CGzVvmAhJL5DqpIkfGORmTslHlci0uU9TdEnWVhhSpGMO6sm7qQ1QrBpQ1kegCQZkz0bmChAwGEXg4Ryizn7d%2BltboADUmAEgHjhOJEspYcS/g8bZBIZIA3VsDUGEpmYPEOaXTcyNLyo2rlMx43j579D2cQ2pPTjkCM%2Bb4t5AzcTH0wC0G2CzvkzN%2BYwQidTPbrOaRCpgULGitzGqvc%2BiIgX9GjChDpiJFaIl8r%2BUiZy5SeTJdgUiJK3A2PJacnZVLJCnT/ISs%2BnSkURNcVbIQXg0jFEwOgJ%2BChbaBhmXIgVQrMgirFRKnaeKchykpYiQIGIKUssRNSzVzLzmIkZbS/VrL2Vo2GQq2gkqhkAn2PiVi8JkgaHJIgkwTr7mBhYjWVwDwEBMB%2BAwcsDxMBUCoA0AgypwRyMtYGMa4LIVeGhSqxEaqGV6tTRqplLqcWYhBVbPE3xrX411Fc5AWZ/VKDaBAFEKEFCEXLT%2BNwMbBKCuFaK74EqMRTjPBwDYtBOD%2BF4H4DgWhSCoE4G4aw1gixbB2KBSEPBSDmJHb2jYABrAIkhlQaAABxmDMAATgPVwfwu6d1cCFEKaQ/aOCSF4CwCQGgNCkGHaO8dHBeAKBAM%2B5dWgNhwFgDARAIAtgEDSE%2BcglA0BSjoAkKIhFOCqB3ckTyyRJAPGAMgemUhlRmF4CKwgJBEF6H4IIEQYh2BSBkIIRQKh1ArtILoLgpAADu880icB4H2gdQ7NC8HfYxJ84HAyoCoA8JDKG0MYaww8HDZhhweBg/QKGcz2q8F/b20gEAkDQZpMpyDEBdOwcSMAKQZg%2BB0AlN6SgsQ%2BOkFiBEVoBJOO8Ac8wYgBJGKxG0OGlzpBoMIUYgwWgzmGNYFiF4YA4taC0C/dwXgWAWCGGAOIMLg5Gikm%2BHZ8GDQnx7EXRECUN7R0kliPPDzHgsB2c0ngB98XSCZeIKzJQLwktGBJEYPjGwqAGGAAoTZXwWPeOHYu0jwg6SUekGN2jag7NMf0MllAU7LD6DwLEL9kANioD9jkOLnkURgVMJYawZg32NeIIgrLm2eh9ByC4ESMw/DMbCEsSo1Q9DFGyAIR7H3MhfYYCMN7qwbvhqaAsH7zH6gYoGAsQHYwai2HB54ToehAZtDhysGoGwFCzt2BIbjHBB0vrs%2B%2B8TyHUPocw9hrd8mIC4EIyphdax1NdY2KxJgWBEgQHXSASQgRlQHsCFejQkgzApCff4ZIB79CcDvaQB9gQuDKmSFwZIO6D3nuSP4SQJ7BepFffxzgn7v1Lq61poD2mQNCYgxQQzqAlNwYQxwVoLBSRCk8kwSeyXZMHuVEr0dBGiAXfQCR2Q5HxBUem0oWbDHdDmbY0wDj8WCdE4N2OzggmwNPgeKJsnkn0Mwm91wX3/uFP270wkJhgQzDM9Nyu/9Ony/GYM0Z5TKADBGGL1wZ9NArVsRs3ZtzTm/ND4815nzDg/MBa/EFkLdnwuRei7FvziXkupdHfgHsGWssMZy8gPLfnCu9Ds6V8rBJKt7FHTVuri7GvNcwK1tfQEzc9arP1wbw2/NjfD5N6j8ho/0ajpx4LadZHZWAralYbbc5jo7aMycD7YEA4pPBgEnZnYJDB5XbQFQ79D3buDI4FDPYiQY7vbMafb9AQ7pB/b9DEHA7YFg5DAUF0ECCDDo6vbw6o5I75BPaI5DA0FY6bDbB47tQy6E68YMak4SYU5e57jF5%2B7brDj05B5V5qZ15/ps6YAc7jDQE3py4K6%2B4i5Cj%2BAHqXqBCi4pA67E7iFG62Am4ab/oW5ICgbCYt5N7KbwZsCcAu5SYsAKCkj0ykiyGOjzD4b4BB7EbMbf4TZJB/4zaAE6AgDBAJ5J5cYiGp4k4Z7W4iZiaqDeG%2BH%2BGBF3jzBl4O6M6BCBC152FaaN4lEuElEgB%2BFCpZgBEHpZhBEEBZg5FTaWb94QC2YMaj6haLoDHj6%2Bb1bT6CCz6hYb6YARZRZiDL71ar7taX4JbpaOCZZxYB6qC5YSiH6CDH4Man5OYX7VYXY368B35yqP7tbP7158C9bv6YBDauhf5h5RGR6yCxFzYJEgHGDLY2CQHwBbawFaycD7A1ooGWCnb8bnaXZQHY69Cg7OAQCuAUEvYVDsGkFUE5AUFkE5B8Go6InQ4sHtD4HcFMEw68FsGY4cEMFkm0msEYk0nCE46CGUYp5iFvqcDia5F%2BEcwFEShFF06hEkDKEVGs6kDs6c6UAE66EgCHrKhlH%2BCno65PplFChq6WFckfo2E/oSkbqSD%2BAC4XpChPo7qSDHpcB7rMIiGBCcmG46l2EE54ZakOks714bCNZZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/bind.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bind.test.hpp)
