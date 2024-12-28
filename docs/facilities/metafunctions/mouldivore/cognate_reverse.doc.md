<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateReverse`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-reverse">To Index</a></p>

## Description

`Mouldivore::CognateReverse` accepts an operation and returns a function.
When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>, ..., Arg<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateReverse
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateReverse<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the entire list is turned over, we transfer the elements from the final `Capsule` to the operation.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several elements in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<typename...> class Container, typename...Elements>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Endings>
    using Mold = Container<Elements..., Endings...>;
};
```

We will use `TypicalTurnOver` to turn over the element list.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** TypicalTurnOver ****/
template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};
```

We will use `Send` to transfer elements from the final `Capsule`.

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

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateReverse
{
    template<typename...Elements>
    using Mold = Send<typename TypicalTurnOver<Elements...>::type>
    ::template Road<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhpcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOt2wqgIrgsTGQAGsvocgVCWKkDFCTIE3AQAJ7PZhsAB0xMx2BBE2IXgc4Mh0NhCJMAHYrIz7pirFcQSi0UwMViQbdBbduejMJjsXjGKxMMTCaTbsgDApPh5BEwIglSAKhbj8dLZdh6GxBAoQaTyQRKdSIVCGOgYfDxaqWhriOLDZhjQQFLLzYEyZzmdrBSLeWKsbqpUTiZdgMRMJ7GN7zVchbcvJkjLcALKedC3TH3W7O9WRN1Yj1en3E0i3WPxxMm33%2B9lm1mtzm/MFuJipBReeiIg7Iz08vkSvXRuUtq4UqkEYu9/v0DvArt3AAqktoeAAbiR2CAt6k8KJaBuNgwAPK7hJDs4ggkfVKwzC3Y/1PcHgtBzuXUPjpGT7NgGlxztSx6nmIF7ENet7ED%2BLJsoEHJrv%2Bo6iuKQHSrcABieDEBMKZgZa87vniUHnpeN4JOK%2BGEQQxFMqhaYZhEwDCpKBaBEWPZ9gO4ZuPRREtihbbIahXIYWGWGSk%2BeEERMtbYWwtxCJgaB2sR4ELpBZ4wXBtFYsJBC1upmnoExv6XKxmYcZG3G8UuAniuZAjoLWJl%2BpJ7ZiX%2BAGCSpb4mcpck4W5dqhZOMrEleBAIAkpoziRVq6RR%2BnUfBdGKaZakae5tZxQlhEgW2LFCmxWYOcGjk0ra9r0rJ0XkSeGWwTR5ZuEViUgSAICRsRaZ9QFOZ5q5%2BWRQpDHeeJq6zX%2Bfx7Hldr3iOqKYRGYVTtppHUupK3MUyElmlcAVYdJgFbTF07YAqSoqrIpaapx0UGkaSZJaBOnLZZWIlq67rvU2JKiaBh2pjqF2BVDTVRtd8qKkwyq3FezzELy2SDUK32PC6tA1eDNlphVdkvW%2BhYo2jGMCIDjbeqVflE4KR1zRDIYwxGHMTnDIF3Uj1aEvWCZVljgqVRxABKqBMPmFO4%2Bq%2BNYkLdMC6Sw2SnNvmSeuAK60iIKLbcACS6109TDCrQbevWw%2B/lc2dm2vSDt2I8jqMJObO2pcWqDAMwUIS5g8FKGVNUO9zwHEpWH2i%2BmpO5rQss8T9sPyR%2BO77vGfV6dBmVGW40fAzd6vPLHw1Q7cUsy%2BK7vo40M2BsdC0298Vt3BCrBom%2Brc6y3QJmmYgQRIqXhYNxbiaVsqTJslbcHJTHuNJbp321dpWzrtC6157jNz0tQheKkRSYOggfLguPeXOLamH8fp8fAOC4U9v9dYhEBAHLW7%2Bf7c39f4IDc0KG2zJgFoVAvAMAcNkZe6F1oyUdjzGMxBgCfRBNfEBYCIFQIELVDwfswyB2DoJF%2BmN/R9QTr9NwlxkGq1EtrUEdwz6PxgdfJhtAn7JwwUwcBkDX5uHfv/D%2Bgif7fz2IAve74PgX31hvDGyAAD6/MEgEAgBMdAfUFDSkUUlNwB8j4ZBPmw3KRjSTLHZBwVYtBOD%2BF4H4DgWhSCoE4G4aw1hbgKHWJscmg8eCkAIJoCxqw4QBEkISDQAAOMwZgACc0SuD%2BAieErgjJGTSCsRwSQvAWBJA0KQOxDinEcF4AoEAuT/H2IsaQOAsAYCIBAOsAgqQvCmQoBANAqI6AJCiNKTgqhwkADYAC0/TJC3GAMgZAtwpCEjMLwE%2BhASB4HUSkfgggRBiHYFIGQghFAqHUBU0gugUgAHd0apE4DwSx1jbEBMcZwK8zSmkLlQFQW4fShkjLGRMqZoSzC3AgB4Dp9AELmECFwZYvBylaFWBAJA7STzAvIJQeFnTEjACkGYPgdAoSEUoLEW5sQIitBxBc3ghLmDEBxFeWI2gNLlN8e0r0V4GC0BJQcrAsQvDAB7LQWgJTuC8CwCwQwwBxDsoInSvcHxbmYFUBpZp2xfHv3qLcncsR0aUo8FgW5lo8DZIFaQeCsQDGPGFUYHcRgAmrCoAYFBAA1d4xz3Z2N8as4QZ5NnSDdbstQtyjn6BFSgVxlh9B4FiCUyAqxUDT2yPywZajCymEsNYMwBT4LECWdKyNPRJXOAgK4aYfgUhhA1IsUYKQihZAEIWvQlbGgLBGNUHN2CmiTHaJ4Toeg7C5tbfMUtjau1tpreMNtDbKjltWB4jYWwJBXI4DYvJtzClvIGcM0Z4zJnTL%2BRAXACyQU%2BIhX4q1qwEoy1GBAIJIBJCBEJNEwIqSNCSDMJIfpGgND%2BH6dE/QnBMmkGyWCwk/SuD9PCdEpJ/T/CSHiXe/pi6DmFOKaUo9FSYW1NhfUx5zSkVtNQECrpPSOCtBYLuRkgymB8yzFwaJhIuBhLmfgIgGblnbPdRsiQXrZA%2Bv2Q43QmLTm9lJXOhd%2BTeCFIeY05ptwXkro%2BaMxGlHqO0Y0P8wFCK7ygrMIeqFlT0MosRa0vTox5Poribkmg7DEp4oJUSylpLSDkuJdS2lDg7OMqTMy1ltyOVcp5XyuzQqRViocfgeMUDbz8ocbK%2BVUI7PKvSQ4tVGqcRau2A43V%2BrfFGpNZ6QL7ErV8FtQoB1mAnX4js269Z4gtneqUL6g5vGA2WqTVYENaqI0XscTGgQcaE08WaymtNCQmNZo692ltLg7TDpCHaMdSwK0ZCrTkDt%2BR5vFGyLN8tzbGj9CmMtotW2%2Bijv7eOptcxdt5H22dwYx25uTs8TO8F37503Pg5wGTa6KMcSozRsJ/zd2MYLAeyFx7SCnqwIkDr6Tf3/uo4%2Bxk/hokpMCE%2Bl9UG4MFM4Ihsp%2BXql1IaU87DhniDdLYJwIjnyWAKF3JM3c33RQTHo3upZegKsevYyxrjfqQDBH4%2BcgVQmXsY44OJp5UnXmqAp1TmndOwwTBU7htT%2B7AiBC0zjuFCvUWE418CkA1Oj7yNp9E%2BR9OCDyIl167FlmID4oOQ52zBq7dUppXS1zuGmUsrZcFzAnLuViD8wagL5rUuColWF6VByovIAVbFwQKqDmJeJSlnVGaMu8Cy0oU1uXLUoYK0we1jrnXldkJVz1HPavcZ0Nzxrxhg02Da/AKNXWGD8p2GooNybLCptE%2BmzN7XJ31B7RN9we29AlvKAO1bi2pt1vWzdzbY3ttDpH%2BMAfLadvXfHydwdAwptXY29UO707NkC/R6Jt75vbiU%2Bp7cQ3hITd/YYyQQHYLVcoZPZgM9EO53Q5ADEwkyv/AEkoM31ldGQQNT87kilbAkNtNlhL1JB/Bb1klGQ31wlJA4kuBIkzBYN0lAhBcz8oDYC51ZkICENkNoVVhg5sgr0gA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_reverse/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/cognate_reverse.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_reverse.test.hpp)
