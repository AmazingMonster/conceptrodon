<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-insert">To Index</a></p>

## Description

`Mouldivore::CognateInsert` accepts an operation.
Its first layer accepts a list of elements.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided element list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             E<sub>0</sub>,
             E<sub>1</sub>,
              &vellip;
       E<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, E<sub>I<sub>0</sub></sub>,
       E<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, E<sub>I<sub>1</sub></sub>,
              &vellip;
       E<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, E<sub>I<sub>n</sub></sub>,
              &vellip;
             E<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert
 :: template<typename...> class...
 -> typename...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will insert `Vay<-1>, Vay<-3>, Vay<-5>` to indices `1, 2, 3` of `Vay<0>, Vay<2>, Vay<4>` and invoke `Operation` with the result.

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
using Metafunction = CognateInsert<Operation>
::Mold<Vay<0>, Vay<2>, Vay<4>>
::Page<1, 2, 3>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<-1>, Vay<-3>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateInsert` by combining `Pagelivore::CognateSegment` and `Omennivore::InsertValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.

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
template<template<typename...> class Operation>
struct CognateInsert
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...NewElements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::InsertTypes>
                ::template Mold<NewElements...>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIArKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYCa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW4vI5aIQAJ5Q7AA8wghhgrwQqFuZATdBYKjI1GfPaXZTETA0VRvXZ/AiYFgJAwMnEEBH3ZhsUiXJiw1DEs5oDF3AjkynUyFA66XAjELyYKFWM4Ar5bS5uJgJBReei0nb0xnMpis6HszmsTAAOhtgtOE3lDg1Wp19CVJPOZOwqgZDHQADFiLJ9UcAQymSzFWaOYxLXaHV4nd7fQGg4JIQB2KwZ67ulVncPG01uQuRtkxrnW21A7CXMFMBSvDyCJjTMiyiuWm1W7D0NiCBTxuWJsXJ1yB2Q45u1Ns43uMxgEBTd4k11FZgGXLeyo1l6MWtjdiyYYDBBjBYCDtdnbeXLwpIyXACynnQUpl09bIWIOOPp4Y55GMuNo8vO/ZLiua5Asq/w5nm/wFruJpRiWSHFnyRCQbW9aNpcQiYAAjgqIo8hhqDdgAanUeBMBE9BXiiZwJkmPrjmmBA4vhRGPChVHEDRdEvFhdomBuN7bqWyE4mRR4nmeF4MZu273he5JMMAmDvnhhHEWsv5yQBCndjyfECfRwnQeuuaWfmnpXAA8v254AG4kOwIBuAYjZ4MgL74FQCIACoxq87wApWCgJEwayXI5jAuW5mYwWGaEoeasaHtWjH2sOToAJIMEo9TBfcryidm1nJaSVwWA2mmakoIaGhGUnQjJNp5UOjpigVRUECVLw4viIAgMEWCqAA%2Bko3EijieUWdl5VKVuknFullaXKEmAAO5gYuPLrV2WXLZczFihSqBEC%2BtDoCdS3ibeK2peWB5VlatXIAA1qcxCXnaj3bhMJo%2BXWAgTJgzliLy/KXHg6AIrQJ23hASMA5cGwbJc3pRX6kIAGwaBSVJ4Koc3EgTsqoJclLRQgsoIJpWApJSb45KkAhWqjANE9SZM1tDmE2lQ7ETXUl6kFzj0YxqnjtPTmmUhMvK/T4i7LpLt4fd9v3AZzD2PfMksALTIs62q6oq%2Bu3jiGsSZ2bCXFgYLpdQItiwo8wjelxm21uW27X2%2B2%2Bx2r2XFrP2Xl7MYrlb26rlVpxozuLVrfbb2nMAlILgO/1oypj7XW%2BUIyk7tAu3DCMQMNIDpRNcOLoiOIZ1n4GKRuObdvMhs2YncdwT3J2rWlafds3mDZ0uudbvnwDPq%2BWkXVdr5N5n4%2BtxZyX9wnQ/Sfy3Z5aRe82gAUl1I6XL10T9SFQ0EOgI1jZgk3TbpKHzVlPLV4/z86TxOLHwtdcMFbw733BlTS/o8DEAmP7PaggDpp20sKdAsDA7wJDuA4S%2BszrikuqgQud0xK9wBqAksI8bThx1lPR6QNHDIFBoVBkkNaACyphXRGsctwo04VLTG2NDBFwJjzEmfMUQUyINTTAtN5aXDZh0S4/BiAyJoNAsUIRtqXDaBPPWxCk7imJqTaEnV%2BbtStMLWQosdYSx4beaW/DcYmCERKER0JT5rnEVTGmyA6YEAZrI5I7MGAKJIDIpQyDLjqM0WgggOi9HbmEYYtwbjaymJYHDdA9BLHi2DtLDIctfEKxeGKMWqsByxLiWHaK2tLwx10beQ2PCTb801ObN0PCbY2LtqHUuLtzGCCyR7KO9wfadK3JA1RqCJ7WLqWjQ6DsekxggGkgkmT3aexrtHECwd8LIMmeBaZFSMEbUoZHDZwzbTtKggnJOpC5np1XhPRSPCZ5zxulpBZ9wIDsKrnfIZmA65YEEI3aEY9HnEnbtcTu3dgF90qh6EBz0wGVlHg81u1CXmFwXkGJeN0V4tzVhvKy8FVRkgAEqVBWCkZy9U6pNRSinFCpiD6sO7MfBBr1uz2QKcQLir8nk5W6hfQqV8BpXjcF/P0T8pq/1mkYrCn9fmjUlT/GaelXHytity3lPFdYiSIQihlL1wGXHGTAnacCCDsuNTsgQKDzXRKtcim0XKGbED2WrahODF74OXvre6MynqGqRUdd6VSI78qTrQkGwpwbMNYbDeGHCA2XG4cm2xfDVA40EYTZxiTjFiI0JTSR0iCn%2BNyGkYJSjS0qKVpErR4FylxISaIllQs3ZWJyRmrN%2BMc0GP/uTQtEivE%2BL8XIitijQmVFtREnaUTtHB2ba402qT0mrI7aM9GmM8mVDFKWxWxSVbr2Dic3VPCGnJqabWMcfoJyCElh0tN24PmW0fVw4Ot5L7FRvtCF10RtUil1deV9j0vapVebdH93L3VlOOhu28D9E0QBPUtDuNpz2HPQ2jah8Ga5gYIZctwwc7mO0qGXRZfSCADPWd7LZG7TUEGg5aojiDn1LNXf8tZfyRnAZtX6Rj96rnwtmYishHKbSgrRUBpOGL57FxI87RZ3zq613rkC9keK14erXBCqF8FrZbyE4Gosw8xNWgk1p7Kt4ZNvLk96ghILUUEuOgPAztlRK5lsmqPCCBYQED1GFRCQbNRH05kBnBQgfMED81GBOXm%2BIIgiHgVylIRolR8mIZQqAEh0rOBFKKMV4uJeS5pf19LjO70FqF7KOC0uiFoJl7LKG4W2VIWRE1UCJhnydLVjLWWcT0b1TC6eD5Z7pS0hF3zbpoTxyJQPQL5W2ow3o4fCRvGIPVdymKHr9W%2BvQmW0g21g2TovLG3JibUWptuAG4JlUrmEKnFa0tjrlr41rZW%2BRZ13L%2BU1Y5OlnbCR%2BvPZ5G9zVrrAOLX1cpEbGC7rSixqxG97EjUbW2w1nEv7oFYT%2BdQ0DDK1IaUB6o4HU6/Qzdu81%2B77mPRefwrjALD2RN3KwQK8%2BtOi4QuJfNvcqEgumNNjhV4/61jvcotRWi9EutijZ5xGVaq3CmXF0JZzEOhvJwWzz9XfP%2BYC9ivcYgwMBCes2zcTAM4k36dV1Z6Hp24f2T1wbhgOIFeCXB3p2FnPdG3JE1r7CXldbmZzlJqHqlSWthYXJ24ZuNOPKx2cmLs3t6M8Z%2BQqrdY/cyxbG2R1IaLXfeN9L6En5ZzQlz4A27quvdBaZ1lNPDZXh2%2BiA7o3grI9h8IZb4Pj4bcygb/rjoc5omu57vping8k9V5T/zv3KL8WB8s532epLUBMCLnD1vdBo/ryytjlzo/qo7Hx20JLbkRoeGAMwBk%2BFgDgRy6cPL0VNLKHUkf4rSUPSV81yFqfdfdeN/72F43M/C/TAK/cCIBMfILFIAAL3%2BR6k/jwBgImhiRPmb3PnX3Nz7g7yM252gNgO7AAGlsNtxKQiIoEXgU0VwzA8ZzA8YIB8CpQ3BLhj4u5JYXkAAJdJRgJArSXvJvIxHkY%2BI2fAwlP1O7CAz/SrAPSeIPYbVSJ/DScbVwZHS0S4QrY/FLEAVHXbNwKQ8HHfefLcXHYzS4UPDfaEdAzfJzKrIwyMS4DggkLgjiG7e7aWAqfANYV4UQIJMQBQKmKIWROvTAN8F5RxDQCVcaaVVVRUAmRtNXbnO5VAp0ewwFN/MQ/WUhXA7g5lTI5Aq0ZJE6HBZIxgW%2Be%2BJVCIl%2BP%2BfgpgsvXRf1G5ETHIggogrcEgrwMg14CASg6gqgughgpglg55aHdA7guTXg//NwZlQQ4Q5za5POa3GMRQ0nYNB2NQ4rVLX7OrNHKogBbfOPZoy4Gw5CEwtvcw03MPJAsnWotIz3ZPUzXQ9FaHTFOTIox3BzWfCCXY9KYla4qnTzH4f434ElK4PKCMCeB3W/NUAEn4P4MreI24zBGvHXMYtISXGWc/ZCT9DicvcQ%2BIlPXPRI86bFH1XFUQrAuI1qcVBA2Ai%2BeAxA3I/IwY1SYYsUOTFpV0FCauFgJgT6f5b%2BSI1%2BURBVUorknkuuZVfkyopJZEEQ%2B7eoyAqkpA/efYr1Ik%2BQl9JOOoipW5FPRjCNCpazVfGUaXDdB9Q5EBRBY04Da2abODWZRBNU%2BENYjyVAdEy/E8MA04s3C4mQs0nDIeQ/OaZnX0rcZEQ4hkEw5fCDNwOKQyJ0zE0VfYpOMMzSezNwXUoM4M5M8DAfGPWDYDRM7cLMpfFfdHe3f/FEYfLDa4uUiQj7MzRzOfVg6HNUrFPBNUywmDKrN3EM6siSeEp1es94vU2QguWTOHOzZeN4zTTsy4qnObOyKEukIEg/b0VgZkTSenSEqEmElUYEUEcEEraEYUNYBIaQxaffdUKiBEW/R7CRfNAEHBK8oBU6WoOhBhcGTNJRNrZhBUJKTqLeTMPfBc9UZEgQG8/skNVE0C142LMkJ8M4qgLwDEeRenbUu4qhIDDFBCpCqoMC1kl04AzE0sv/FEoDEaVMp86EDQZEEyJgJEaEMwGi1QuinESQVcbKEads6EFoS4MwHkIEO0ciycnQnWGU5c9UIQLwBIHIII8lV0MUenF5SS6S5IWSl4XUFk23MslElUaESitwaimsWi%2BitwI2LgJi/Sxioy5ikyo2AS6y/Stihyli6EI2WIdij3LzOSjS2/F5bysuLSeC2oRC5C0i%2BXFy0y8y5y2y%2By7AYynENyjy%2BcrzQKIpW/KNZAUWRsK%2BH5UohQS0LKziKSmS9Afyl7Mq5EaFDgRYWgTgWIXgPwDgLQUgVATgQjSwawU6ZYVYErYEHgUgAgTQaqxYT6EAWISQK0DQAADjMDMAAE45qyhpqpquAMwMxpBaqOBJBeAWAJANANBSBGrmrWqOBeAFAQADrBqmrqrSA4BYAYBEAQBlgCAEhYRyBKA0AmQ6BohQhLROBVApq8YjY8ZJBLhgBkB6EpArQzBeAgjCASA4Y9B%2BBBARAxB2ApAZBBBFAVB1BrrSBdAWhtp9cEhOAeAaq6qGqhqWrOB7JYRXqxRUAqBLgAagaQawaIbLgoazAU0PAvr6AlE0QuB5heArqtBFgIAkBPqEhvqyAKAIApaZaQBgApA%2BKaAy5ohzqIAIgqbEtmBiAERSbeBda6gER7IIhtAd1DbSBPrwJ7IGBaADa8asAIgvBgBNRaBaBzruBeAsAuSjBxAnayCqhqUvbmqn4KUGQrbggGRNrmr4QIh9d9aPAsAqa5Q8BdrvbSBqViAIhVLbg/bgB4QjAhrFgqADBLwKJnhtoG9Gr%2BrkbhA6t0bpB67sa1AqaCb9BDBjBrBrB9A8AIhzrIBFgssOgvajZ8Ri5TAOrLAzBjrs7%2BImZ4BFgKhcK/AIBXBRhmhSBAhpgigShsgAkOhN6D7y18hd7%2BhShWh2hqhJhj7xgtFV6uh6heg965ghhug7737n7z7ZhShl7uq1gJByaOB6rDqqaTrmbAbgbQbwbIaJruaIBcB4aBa%2BrhaBqS7FgGYV8BgIARqQBJAgQrQ5qgR1qNBJAzBJACYNBYg8Y5r9BOBtrSBdqgQuArQ8YuA8Ypq5qVq8ZxqyhiG8YwG8aTqzqLr0HrrxaHqJanq6a3q5aFb%2Bbfq2BOA6gWBnIMwjYmBa9HwuA5qrRWGw78AiAF6kbZBUbxAMaW6lA268bdA%2BKiatRDbgHQGjreATraaXrYRLhGbIHWbQb6wdG9GDGebUA%2BbohIRgQzA0HRabrpGFHoh3r5bQnpb%2BaUADAjBdGuADq1aGRoFKBta8bjb9arainTbzbLbM6bbFw7aHaqbnbXb3bParbfau6A7mr8BKRg6Xgqbw7kBYR1h%2Bro62gqb47E6ERk71hmq06M7%2Brs7c6lB87WmLwS6%2BBy6FBK6doa6rb67zGm7Mb5BrHcbmq7HO7i6p6rBLA%2B6B6l6WrTy0gx6J7pRznrBZ63H5765B7cGr6d00gXA/RP6d7CgL6T7AlP6x0z6gXf69AV6Ogn6GhPAmhoWH7YXJgX7gXxhb6EWxgv6phIX96halgVhAGCXNqXHwHOBfHoHtHZ5dH9HJqU0kHjGImWHomMHSAsGsAYgvnNrGHmG9GyGMxYg5q1qgRyHKHJAWhXHqbTrbAxGYnJH4BpHnr6bEn4m3U/qOBVG2aWAFBnJ6FnJaXIwJhYajGEb74WgdnG6JBm7ZBW6jmdAQAgRSAHGSbvbnHKbhGabZGGambVBtXdX9XDXkIlYIBeaUnwm0QgRWWJHbrJbkmZbVX43Um9XpKJoDW5qJojXKM/Xm66BcnNaCnmrSmSnggTazaLaHAraqnBAanHb2nMAXa3axAmnM6Wn/bJmfag7HAQ6enVAI6BneAhnY7eBRmTaJnU7%2BIZneA5m87GQlni6Y2y71J1mq6tnM7LW0brX9m7X27HXTnu7p6bB47Pnh67mwZOANhhpnmZ657ogF7umh7vnV6/n3AsWt7AWZh8XEhD60gwWf2IXP236YWb6P632kXr6BA4W0WoWMXQPMgt6gZv68W5h/6iX0b3WhHjqKWc3LgdW9XLh02rQs2GXTWUGWWRa2WOWcHgHeWQB5qrQgQgRYhYgyGsmNBGOMxOHMO3HOBRHLq2XRrJBYgiHVqMx9qprJBFquAZqqD6GOAgQPWsOZX5XgGYbuPpWKOJHFhs6UhnBJAgA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_insert/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_insert.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_insert.test.hpp)
