<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateModify`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Operation
-> Transformation
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Operation
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove ::   template<typename...> class...
                -> template<typename...> class...
                -> auto...
                -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRemove
{
    template<template<typename...> class>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Monotony<0>, Monotony<1>, Monotony<2>, Monotony<3>, Monotony<4>, Monotony<5>` and invoke `Operation` with the result.

```C++
template<auto I>
struct Monotony
{ static constexpr auto value {I}; };

template<typename Val>
struct UnaryMinusHelper
{
    using type = Monotony<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

using SupposedResult = Operation<Monotony<0>, Monotony<-1>, Monotony<2>, Monotony<-3>, Monotony<4>, Monotony<-5>>;

using Result = Metafunction<Monotony<0>, Monotony<1>, Monotony<2>, Monotony<3>, Monotony<4>, Monotony<5>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

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
struct CognateModify
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...Elements>
            using Mold = Send
            <
                typename Send
                <
                    typename CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<ModifyTypes>
                ::template Road<Hormone>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGE6a4AMngMmAByPgBGmMQgZgDMABykAA6oCoRODB7evv6p6ZkCwaERLNGxCcl2mA5ZQgRMxAQ5Pn5Stpj2jgINTQQl4VExcUm2jc2teR0KEwMhQ%2BUjVQCUtqhexMjsHObxIcjeWADUJvFuXo60hACeZ9gmGgCCewdHmKfnyLPoWFT3jxeCTeXhOZzcBBuKUwAH0CMQmIQFADnoCAPQAKixGOO2FUBFcADFiLJjtiMWjAQSWCkDATwZDocw2AA6Nkop6zYheBy4/FEkmCU4AdiswoAImcrKjntTaUx6ec5XTMAyoYxWJg2Sz7sdDkwFApjh5BIjQmRjoyNay2dh6GxBMj4g9nlyeQQ%2BQSGOhibJwSbGgtiOC7ZgHQQFNqAc7ASZRYDjonLWH5YqIermVq2WFMAB3UPhp0up5J45eDJGY4AWU86E%2B4uNsjNMXBOfz9sYEe1pFxHcdUZj8WlLwlUtjspTKoZk4VqvOTEuqAH2D1BkNxyEmAAjl5GNsewuiNqAGpNPBMSL0IuAt28vFen2Cgjgzc7vdztyn4jny%2BYSPswdizjYdS2VWdwUPJc2QsTBgBCBgQmAa9nlLctEOOZQmGAD4zgbV9dwYbZwRguCGAQox/xZHsvx/K9lzHVFRyHccnkxbEMOITAaFUMlsUpCcaSnJUM01HsMgAL1hZ8Y2eNBCMwFIPWUTjuPrS1uTnYd0XJY0mBSBQvHoXisX4p4wLTK1M3o114XdXT9MMzSWLYrFqwwPAqBuAAVdUjXJUzzI/SzNWszlbN5Gt8E8nzoSNYC40lZiZVYnSLAND43HS4yKSpGc00g7UAEkOVvD1Io87zfPBH4QBAEIsFUGElDfeTwUK%2BiZJHECk0C6dBPA4SmRCgCV31dcAHloQRHoGA5UtSo41AiAAJVQJh0ATJN4pQ0sery1Udt2z43E2o7SzRNFjgAdQ%2BcscIANg0ZSuLwVQ2vuKNHstVBjkYHwYlnU5Ht9QQvKabCIxMR6dUOs7E2e7j3udbUQYIMHiAhhRSFOuHjgu66PlzOhaHUwwFH4YgWEtBAPlCfFjnB/7BBhktccTYK2GOdGIex2G4Y5rMWTS5AAGtucwSG%2Ba2zq4dmBU8GQPUBFmTAADcxAZxdjjwdAbloCAVhx0sAFpdUyhz6CN6WTqlo7UfFrs2V51m2cmgGZvBB37mdtnE2FsXwYlyircTaMtNt5N%2BoskSbRZJ5gE4sNO2Ql3drQysa1oOtcOOLBDitCAdb18F48TwtlwNw2ktThKGJeWHeqVfa1SG2PdTGyjS8wJPHTmpN0%2BAY5VvWtTlKW1Bh4284u57x2dUHLSmPDszm/nRcioPde2QAKRK8Kyvc6KqvOGq6u9TBGuagiiPOdqRrEgh0Fq%2BqL6a7dr4/beOqA%2BMG9XiF/4C2XKuA0Ro3bTSyH3RMC0x4rTWhtWG21U6gWbhHcEIddr4xumWJQQMnoqVekjbAn0NDfV%2Bgwf600HoaHtoHSG0MMGlgRoQ2%2BH02S0IxkHH2vssGE2JqTBg5MSBUwIDTY4dMPSM3DCzX2loY4fEJHgYgswHbcLZrwnB1DmFvXOLvZG7IvpEGOMAH6TBkAknXKIj4%2BA5atQjudS60QCC5m7gwS0uYfoTExjI322jwR6OIWyKsOt0D0AdljRhSYNFE1oCTeEZMKYiLERIhmGMmYEB8WzAWG5agCHQKoyJ7N5Han9uEjBUDdpy0cIrOSKt1Yk0gtrXW%2BtDYR1Ns6eyBlLZoPOIU44HDvFOz6eA%2BWAhwSKOUWjOh3s%2BnBN%2BGEuhlE1G4xGR7c4m45L5Omc6ZZcNSmLKjD0h41cMGN3TK3QWM9CwVNQhWQemds7xAbHnWgBci60BLgnbu5cRqVzrqWWuJy/5RyCoA4pI0QGGm1Fc5OFSB5D3gaPEkcD1qfLLsnDqi9ErLxcjiZatRNgZFVhlLK/lcogoglvFkhVN5Hh3j2IBbJxpWOIPhd8KcFrlSPrFaqj9n7n0vu/d8bVlwPyfmfBqb8Wo3zcF/e%2BxxmU01ZUK%2BSwdOpIJQRSpuWrznWkFu3NcYCpqjNmjLJMMDkUT3gTjDVZ1eo9Jtsgs6Gi7p4L8aw/ROpDE/T%2BmwKheCBlByhhoTJuN3VuGKp6wNEZdnOsutgmJcSESCMSdTWmF9JFpOkX07JEyVF0NjUdF1uDg3hoCSQshJiGbmPSEaKxuc8C2KIvYqJjiJYuMYO4zxBy%2BllrYSyOZoTMDhMLZg%2BNfDYkCKEZTNN4iM2pOAOk0N/N5E5M2QUltRSLklLMQHThksnWhzNUdKpCslaCIJPUzWRj3kGwwe0lc94BR%2BgdTm1dXLKo8vOIqmIbLVWhVkbVQKCLUXfuNWs4sgGQDAYecRXd4SANnRuUmID%2B03JZ3Kb0zd/SnwIaGdh1ZkDzh5qmfumZ2HB0LP3Us4Z4GiNuA2Xkr2x7dphxYvzMF262Qwt7ix256EHlqReW85paLvkYt%2BSsKu3VQ5L3Y3tHVZzGXz1Goa6FXzZ4p345WSeSLx6TzE5pzFsY5PJVxVzKECsxDKFQCkbKAV/4FRGjefeG4ECXAIJbIFK8dVOZUy57kvIYpWdoDZuz8VTP1x86mD8jSSN70Cx6YLohQu2fGUo2YHJbWJnhVaNSQh3MEE8x%2BNjjFsUsTOXFjLBBaU/UY96BLdlkvWbS8R6rPZ6tTx/jJnB6E8s5wKx5rzbh4sLxM%2BV5KlWtYkdq2uvJtXtQ/uUY1oLlmUthfS5MjruTvQ9iW2q7rONcvqhtU8z0z7BAtz1RZlIIWNvfpZQdoDJ2WOoZBRhLCH4ZtzYa2NsrddtLsU3N6ez5KYtXass5myiWckg4ixNqLSnON6uAR3RspogwMvBSyAssLOoLWB1PNwAZmzBnOLj/szn1W/1TkjxT2ODWgIVXRsZLGFrigloiD5iCadw2O9CNShHWduAp3PUrNdIs4zp%2BDwaKOIUd3U%2Bi3jkH%2B53JA48hsHPAwfOnhpn5KnnvQgB5LgSMuAG%2BapYz9cf79zXqgiyGiF4rwrY9ITl8KqZWO9/AdrLvOFNm6m3SlTkKjXuyIyr6Brmtdc5tX7o6/OcJnaF6az8Z4nd/mMzzhHUvAGOctx0hX3G9d44j71nTXO1LR7oIZ/X9xDdOX%2B958zHhgDMAJJuYA4ZQem6Eubs3fmreh4gaz4sC0W9t8wB38MJmetnIklJY4NLjjz7hNqAJON2ec%2Brzznrmqzcr4yWyAA0shxMnEdxKL/McCAUYzD3XMPdCAR/jrHG3lJjB8KAASITGBwkFyzlPJfbeY2I/TPCXbPYFfvKlHjSGFjeFTCbCfLVwCHTUG7O7VrNwGAp7aDF7UvN7GLIeGPc4KvHXTA4vSnA3aDNDb/X4X/aSY5HFS6Qqb0BWK/UQNxMQBQH6aIY4FIUBTAOseFYNU%2BF%2BQVaVVUBhSA3vAWCpBaGgrANxeHAHKQgaNwA/RfMSPASSVfHeWQ1zeQxgXlcVUQqVD%2BNqHsOVfzFjbLXaOfLQqSbUE/PjJMc/LwS/I0G/dkO/B/J/F/N/VpQ9MvQeEgv/HOZPcw1/EAsAj/NXfrM7N3WXTMNA9bDAoA5cevU/Y4fAlUQg6vYgrfWgOEcXAFE3WnZHSHOOcg2A0veFQTHOAwlPLA9InAo3E5Uo5vVAVvWcD9bvaLaQ8o4aYPNHcI/HVzcfbow%2BO4RiWfXPenLjIYw1Y4T/YRAQOcUvC1fTa1HfU5f%2BdQpfA/NfTI%2BFEIj0HOc2LpD8U%2BFgJgEWWEEwq%2BYVD1bAMVWqa424mEe4j3T%2BY2LgftcXHYnVA4tkSNUveaVzWBVABAg6QImwjjOYuXHHPsaovpWo2sJAhrbDdBbDUCVdN3bE62PpFdC5RsLo9vWCaffI7XIo5w2RRMbIwGKEkVKHQIuGOvKg97Azc4D9GKP8TIuGekgkdXcEZYymVYvks6AUj4WDcnJEn3TEmk3aSUoUsDMPEff5JDUouEqAoPLAo4tXKEvTIgRk3XJXMXP7cA5QsoxTAYtuAvNTIvU0rTVXdCXTHOCEzksgx06I9o8kX0v00yczLyP8CMXo3FP0300yWMYEQid4Y6S4OgW4LLHvVQxpEEgLOyGsBgceBgKYrqZfRoapc9FWVQFIYgO3Y4epXcEUCwYqJeEUCAvo1Q7JU8HXUfVzOQZgYgG4YJChBQT/LoKaGfI7WI9UNSTM7Mu4c4Y2Fs2qSstY43BspTbHJ4DGFOeFDspobskIcsNSDcrsns8sfs2gQc6eVc5oq0S0pc%2BYl3TpRyS8m0y5VcjkWoznKgLwQiGaMcyYnk5EVELDVOK4m4u4gVUwx4twX4nZDfPlEAN44CyVB41qc4eIH4n48jAC6C2Cj4kChCmVAAVmNmQogqAk6lqg9L3K3N7I5FqmlMwLPKp2XnhSEC8BSDSCUHQHxS6VOLO3OLvK5IEAnPBA0G9jcizKIBzPBFQp2REoEvODMGEvHLEsnLcAIvkv4sUvBEkFUtEoECUuNlwujAYJYnhQ4sMi4obCrFfPfLqGFwUp0sEq0pkvAocvUtkucrsqQrcvEvOE0qktsq8rcH0sAktNPWQBhH4OaAgFPgUE1DCqdDcBMteQ62YtYoEISvoOkw4DWFoE4Fwt4D8A4C0FIFQE4BOksGsGXw2C2BwgSB4FIAIE0EyrWBFhAFwrMBZGFDMEkESESFwo0AAE5WqNB7pEh4h9BOBJBeAWAJANANBSB8rCriqOBeAFAQBZr6qCrMrSA4BYAYBEAQANgCAUhLhyBKA0AaQ6AYgwhNROBVBEh7pjZ7pJBjFkBFYpAWQzBeABDCASAdY9B%2BBBARAxB2AOh/r5AlA1AGrSBdAuBSBcwEQUhOAeAsqcq8rIbFrxpLgjqPRUAqBjhbr7rHrnrXrJB3rr8PBzr6Ayy9guAVheB1qtA1gIAkAzrbtKaTqIAWaLrYhgApAzA%2BA6ACRlFKBIhIbIgQhNzEbeAxbOybhxpIhtBah1raqzrwxxoGBaAbhIasBIgvBgBMpYkVruBeAsBrijBxANrSB8BOI6hiVDbCqL4CUCRJbyBBAuhIbrhIgEQuyPAsBIb4Q8ApqjbSBiViBIh0hMAOdTbgBrgjAGq1gqADAkJjw8A8w3Z8rarQbAbxAQbZBFAVB1ALbob9BDBjBrBrB9A8BIgVrIA1hbMZpDbjYfhcJTAyrLAzAFqQ7vwsBq6DZOhugsgXBvQph2hSAggFgygKg9BWKihshPA2gp7CgZpBgJ6RgYaahrKGA%2BhJg57pg%2B7Fb6g5hl7hhYg165hh69A5Zmgj6lgT61guDNhtgJBkaOBcq5q0bOA8a7qHqnrgAXrjg3qzBr9cBvqqaaraa6q461gaZ1oRhe7mrJB4gWQ%2Br4hhRJANBJBOrHoNBcL7o%2BqxqOAJrSApr4guAWR7ouBhq%2BrEgKHcLJAuBcLkH7o36LbFrlrVqIGNrGbdqmb9rMbjqKAObUAKbLrrqOAmgWBVZhRjYmAQFKwuA%2BqWRSH7b8AiAu6/rZAs7gbpBQa86IbC64hYb4bJbn7X75reB0a%2BHsbcbxHJHpHZHB55HFGWRSEIBybWaYhTgEgzBwH6bNqeHOa2aBGAmRgbGpH9QjB5GuBZqaBXkYgVqIARaLbpaJag7kmuy5aFaHBnaVbOw1aNatbMAda9axBaBDbaqTaS7zbCqrb97bbIaHbkBLgdhaqQgCRsqLaPavabgfadhCr/bA7aqQ6w6lBI7KnEI46%2BBE6FBk7U6mRnbM6UstGZBBBdGC7CrdA%2BaDBY6W6rBLAK6q74Ba7FIsgG6m6nkdnrB27zHO6dY/xDm96N7B73Ad6R6x7Shj6F6MgZpz6Ybp6l7x6Pm16uh97egz6XmL7gWN6t75h3mb6L6wXcgR7L6YXFhJ6ab1gH7gaTHUaWGP7Qm7HwmHGFGlGgGVGSBPGSGfHIHSBoGsBYhe72nCHiGFH0HhQGHhRhR4gMHJBHqYazGirOA2G1qJntq9qDqsb2bgniArq2BOBxHCaWAFBVZFZVZHGVRZhPqyW1GYaFmgb8gdHwa1mdAQBRq4a9JjH8HTH36OAMbDrLhjgcbUkWAFWlWVW1XZxZgyahH3HQH4h4gqXOGtrmbvWubJWQ3KaQBlWWKYRVW%2BqYR1WCAwrKZHr%2BbYmhaEnRbxauzna0nZb5bFbsmhHVb1bNaLbtbdb9bSnnaKmzbenjbL8ba7mLaGmmnnbWm3aOnK6umem/bvwBneAhnw7RmzbxnA2E6sJpmU7cw075mNHFn9Xc7DXIbdBRqtnS7W6bAPae6jn67OA0QaoLm26O6Ygu67ma6HmZonmfnR7vRr60WCgvmshr2/msg73V6L2D7%2Bhr316ZpoW32T7xgv3wXT7%2Bh/2n6MWqrwP2mrXcWOAnWXXlWKz3WCRPWIBgHVGKWaa6bqXaXYHn6mW4gFG/XcLeq6GZq/XhRhrmGFrBXbB2HfGpNSB4HhR3q2WuApA%2BrWXkGuBhR8H4gcWaOlqOGGbn6PrqPzHaOGO1gQ6MhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_modify.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_modify.test.hpp)
