<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-find">To Index</a></p>

## Description

`Mouldivore::Find` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
Find
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Find
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<typename...>
    static constexpr std::make_signed_t<size_t> Mold_v
    {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Find<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

`Mouldivore::Find` is implemented based on `Typelivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<typename...> class Predicate>
struct Find
{
    template<typename...Elements>
    using Mold = Typelivore::KindredFind<Elements...>
    ::template Road<Predicate>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSXACspAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn5BdpgO2c2tBGVRsfF6Ci1tHfndk0PhI5VjXACUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpiprozIeJgKd8cX17dnAJOvyulxBZgAzOFkN4sHcTOC3AQAJ4vAD6BGITEICnh2FB5khDGhXlh8LcyAm6CwVFx%2BL%2BxzuABUUfU8AA3EjsEAAaXC6GImHQADE%2Bd8jsDmGwFKkmNsmSzaOzOXCAOxWa6ggiYFipAxasnIl6SzAAOjNtOuE2IXgcd15DH5gpFDvxatBdw9dy1Or1mAN2t1TH1CMNjFYpvN4Owd2hTAUCjNJuUAvwoi1OKj7s9VptBDuydQRAASqgmOgsx6TGq7hMg3hkDGBBNMKpUsQ7kwvEQ7myxF5MKqLABaLhVh7wiyq8fg9Ug66er0B33%2Bn1Bv0hlnGxO4mMGeOJq7AAXaxgEDN4%2BeeryZIx3EtluHgh754iF1D38sIw/HtiCBORvEZ1dadZ01Jc1wNTdwzuEViAmC0rhzW17UdYU%2BTJWD4MzDU3UvD1vUDYNEXAojQy3ADdzjf8kxTes13PCsawxXMXzfD9GKrSdKzwhcmLrBs0AYZtW3bTtu17bwB0YhdOOk3jKySKwkgeCAVjuIcd0pEAQBYJgAGtMFRTJgAidB0TJTIAC9DIIBD5Pk2SePs3i8CoRshK1ES7igbczH8cx/GTQU6PTDC8Dg2yo20iT%2BxWFY5OcytqwFAhNgYO4NAnKc6SuRL7PqJQEsSzi7hStL1NHGdsqc%2Byx1UoqxwnDiVRAnKFwI5cQxI9dESgthtyjSj9zNb9MBPP87KvG9gDvUt0EfZ8C2LOayVG8azwGwDQJapqNWuDqII3I1oMwghSC9PqByEXoBHQc6yPDRMAHkCAQeIGMtZjkL5FNnU/NxTvO67BLuu4XreuDNtdWd2u6ldCJ6h7%2Boo2Nhpo4K00%2BSaPSQvMlvfFaeJK7jcvs2tHAEptPLbDsu1QHs%2BykmqkphvK4UUkxlNU9TNIIdBtN0gyjLwEzBXMhErJs7Hitw0m2c9Vz3OEtsiucnzzT8gKgtTeiwoi3FosZuLVdq5LMFS4h0syqrGr2uX5buAqB0VwTleIE35PVk0Aq12jMYzNxgdug2QBizBjeZmXJzKy27kqydbbne35adu4XaplsVcjtWPcSlDfvQhFwfeqHs7Z7SDq1VjlrLMltZCz5S%2BTh2PUNyS7jAMB4WfEdc4XeKy4c6s%2B/smP0rMOFLDtH6nULtxi8hgCR/kivuurgna4Rev/abluV9DxmsuX6qk73x3aEKwfeJKseKqPnar7qgfm6S1qiZ2oC7dh1dSLho6w2Rt7QaqNqJrV/GeaW15wgzQ/Atde7EvxHjGuA6itJP4gg/qBHC447b/EBPgw4wI8F3AAJI%2BnWnWAQYpCGgjwQQwEwIwI/0Rn/Xqx1AE7hAS%2BDGh0LyIS%2BnmP60NGKV0RpdRM2B6AoMgdNO4ABZTw81u7yheIqDkAptL51ni6BEkj1qoOwvbVezDZqbzcNvXhu0MFvyTnQ%2BhRCGTYFUKwXUA4fi0PoUCHKxCSEKBIYIB4GwYj0AGO2dx%2B1WFIwHHo8BCFcakL8QEoJITJighAHcVIXhgn1iYvzEAeAFBGXDGSGJp5zrhAIIcHcslMHeIZHI82TAqBeCJI0ah5wmEI0guwiMJorjEGAB9K4UDbwNJaM01p2Q4FCIRL4/xBBAlZJSa0BC2kFG0H%2Bv0wZUN0EePuIyT4Z52nAnJvWVEVF4gEAgGMppLS%2BgCDJBU8pgh9jPMqa8tOLyqlRQPu3buyizDxXQac5A5z4yXOuY0iZ9yGCPMEG8j5FSjghzDgtZRI4gUWA4GsWgnAki8D8BwLQpBUCcDcNYawNYNhbCkhCHgpACCaGxWsPSIAkiSBNBoAAHGYMwABOPlyRuVcq4CqFU0hcUcEkLwFgEgNAaFIIS4lpKOC8AUCABVjKiXYtIHAWAMBEAgA2AQTJZ0KAQDQDqOg8RIjhk4KoLl/ghz%2BEkHcYAyAGxSBNGYXgwUiDEDwPzII/BBAiDEOwKQMhBCKBUOobVpBdBBAAO6YlSJwHgOK8UEqZSSzgT0uymruKgNyDqnUurdR6uOHKJ4QA8Fa%2Bg7YCSrF4FqrQawIBIEtaka1ZBzVdp7SAYAUgzB8DoFqOClAYg5piOEVoSJ028BncwYgSInoxG0L0LV9LLXgKegwWg8741YBiF4YAbgxAXwXaQLAukjDiCPeFTd7JPg5pbL0LsOx6UVPqDmxUMRMQro8FgHNGI8Cyu4LwNk8QYgZEwE8W9wBFRGCZWsKgBhBkADUPhJqekaK9IbhCiHEJGgjMa1A5sTfoQwxgKWWH0HgGI6rIBrFQKkRo6qOBDkpN3UwlhrBmGVVB4gAasBMdUnUBo2QXAOmmF0YIDphgVCqHoIoWQBCyZUxkNTDBFOjGqBJp9AhQntE8J0cY9RDNNDmLppY%2BnaxTFMzMWw1mFhKeWGsBQ1LtgSEzRwfFiqc0qruKW51rr3Weurd5XAhASCT3BM2hlKG1hvTLGMcTrLJDghNHy8E4qNCSDMJIfw8qkj%2BD5foTg0rSCyviyaQI/guV8pFf4dlyQcv%2BAC/GlVaqNWJe1e2g1HajUFq7OQSg/aG22rYJwVoLA2QqiHEwSit4uB8pNFwTlvr8D%2BsDXoAjYbiPSFI0ocj8bdAjpTUwNNEHfP%2BaVbwFV%2BaTVdiLSWx1oXlszVW%2Btzl3k63dobXFwFLaUO6s7aget8QxsWohwDsYsYjCra4AqmgtBx3qogFO%2BNS651XpxyutdG6HBXp3aePdB6c3HtPee2gl6IPXu1NR%2B9xL8ACj6FBjjxK33IA/Ve79kriV/oA0iIDOxiWgfA/SoTMGlDwaZ9A0HaGmCYew7hxg%2BHZAHYjUd2QZG43EvO1R5DvGrB0b/WJljbHsgca43zHjtGLACYe0JkTL7mMGZhdJ9wjm5OhFc3pzTxRsgacKFpxoNnlPdAszC4zIePeNGMxH5YznBhx/s/McoAfVjrE2N57Pkq7uBc4MF975aEdfbWxtjQUXtuxabSsEH/XkuYFSwkcTkqqs1bW/llUSQ%2BVivBAVorkggj3dzaq2wvXW06r1Ya41procTZtXajgs3y0sAUGyBsbJvu%2BgmFtmLIm9ua6I9rqN8gTv650CAcEpBLvXYzRVvz2aut5pG3mYtwX1%2Bb%2B37v%2BieZa1Yce04twQG8%2Bs20wcUAgCG1F9oCxgt9UhUhUQd8%2BVUQ98CBURVAXVR00d3pJ1p1Z0V08dCDV111N0ScIdd191D0WdMAT0z0L0ON6Ub0mcxdeBWcn0OdX1VB30tQ%2BdBAf140hc51RcQMA1JdINoNYM5c70Fd%2Bs%2BB0MFAsNMAcM8N6d9tT8JAddo1L8KMb8jcaM%2BMzcGMLcSUrcmxOBdgtITd%2BNBN4hXdTCehPcIBXA48/dM9bNA9tM49VNw9/dPCo9JMjM5g09o8E8XMPDI8U8HM8g5N08k9qgPMvMI1bsX9lVi8sDXUN8t8ew/90wADot/U4sEtp84pSAUssA29fNO8QB%2BUTRwRwQkgkh8tkcNAGiVQGtOt0iJ91VNUktSAMskhstRUVR5UuVJBBUuAeU/In9wQ0iHtOBG821fMfUuiFiJ9Si1ghNMhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/find.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/find.test.hpp)
