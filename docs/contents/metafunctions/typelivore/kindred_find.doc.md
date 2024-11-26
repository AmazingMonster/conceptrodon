<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFind`

## Description

`Typelivore::KindredFind` accepts a list of elements and returns a function.
When invoked by predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if it cannot find the element.

<pre><code>   Arguments...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
KindredFind ::   typename...
              -> template<typename...> class...
              -> auto
```

## Structure

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will find the indices of `int**` and `void` in list `int，int*，int**，int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

template<template<typename...> class...Args>
using Metafunction = KindredFind<int, int*, int**, int**>
::Road<Args...>;

static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

We will implement `KindredFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct KindredFind<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCAAHBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxickKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHOYAzGHI3lgA1CZ7bl6OtIQAnufYJhoAgvuHx5hnF8jj6FhUDyerxeBEwLBSBlB5zcBFuKUYrEwADoUYCXuNiF4HCcANJhdDETDoABi%2BKBJn8VheJxpJ1B4MhmGh9IhTChF1h8OYbBRSIeJyOTAUCl5ykJ%2BFEoIUaOetJOGKxBBOYtQRAASqgmOggXKKRZ5Y1HMgBQJxphVCliCcmFdUCcAG5iLyfPUAWi4FIAIud9V6feTqbSWYzmWDWeyYXCETzUXtsAKDMLec9gISwYwCNK4zraV4MkYThqtV9PcriKrUEXtRcU2m2IIRbHHnsqa9/N6WwHnsG2UyOVHuZ9ScRxjKFdi8QwCUTSVPocPR9mXnqczSexH133I1zEbz%2BYKkyixUS8JLMFnHoGaeOlSr1ZrtVezpTaau5Qa2aeTQwzRarTaiAdJ0XSfXVKTfd9XwAVisKDPQgFYTldflfhAEAWCYABrTAAH0MmAcJ0BwghoQyAAvXCSKXWVIPfFdQNouU8Cob9f0tE4oD3MwADZzG448JV7LM3AXKjsDQx1vEwFYVggxjXxfQkCE2BgTg0H1n29ZcGPkk4aiUOTdL1E4lJUpCPRbTTDLo9sEOsv1OyfBzWzfTdQwZXtmQHXcmwTIVGyRWtMHTBsZTlPMwmAQsHxLMsKyraEgpCzM92zRy2w7FyQTDEN%2Bx3NgTlE0g6W8gqhG6AR0GKzlo2RFEAHkCAQOILyBG9cXxcVZ2rES8BHAhivKtAp2KxrmpHVLLzbVs5Tcjkcs8vLasmvzDyRATTyEsLaXau9KwfN9jJpazxk/Y1hrY/9bSAqSzh058Zt0s4YJMOCEKQlCCHQNCMOwvC8AIoliNIvAKOB6inoe6zGOY1jQT/aHaM41EeL4jaz2E0SHgk4CZMRyDjNM4hVPUyy/W0mjIZpfTPlhi74ctfH32RvlUZ49GtouIbKuxkBJOdPH7sYwnMGU4mTgs312y7KnaRpk46dNBniCZuUIFV2jJ2nEkyQuMaWsmjXILQzc4vvLVoQ5qVDaFp6cdusAwHOUt3SNk5ZNtgmXzduUidUswzksDqpy63W3H1iamx92kTYW0Ezf2i2Lit88bcp2WY754CNLd8ngXTyGadzxTRbM12yelz3NLs%2B7nMO6X0tcuOtzm7dlt8g8AqS%2BtM22mkIoLKtYr2hKa1TYKe4CwFG4brLngAegAKmXlfV7X%2BegSXleTgAFXPTMTlXjeXi3tez%2BX4/87eBgji8U5oSuOg7hlIFW5qwcTmwege7HAhMWxAAkgoABghPQbGiPQPoKsXggBOCkLwECvyoRAHgBQeFETQi/slYqYQCDL35CuWeXY36lU%2BFgn%2B1F2pAIAGqoDwI%2BZ4sD4GIONMg1B6C2CYO/hmYq9o6HVnjIQzKxDm7uXDC3UhK1O7JmIMAVqLwB5RQALKiyYFQLwN86iqWdsHbW3VoS4JwYIReRi8EmIVsYxeMo0KjzcM8WRU80pz1OkaHC/k4gEAgCoxo6jNFZGhEAkBBAwEIMgRMXm/MXR7A7KWMwsl0ouNPG44UHivGqN8T0AQASFC0PoRE4CJYdHuniRYDgaxaCcCgrwPwHAtCkFQJwNw1hrDyg2FsF0Zg9g8FIAQTQZS1iYRAFBfwSI9gJG4v4PYEyNBjMmQATj2PoTgkheAsAkBoZINS6kNI4LwBQIBki9NqWU0gcBYAwEQCADYBB4EDQoBANA4I6BxAiIiTgqhxmum4pIE4wBkDGikEiMwvATxEGIPQvQ/BBAiDEOwKQMhBCKBUOoY5pBdBcFIAAd2IEwFInAeDlMqdUvp9TOD1SuLck4qAWIfO4l8n5fyAWSCBRxDwTz6BWn2FwFYvAjlaDWBAJAjyUjPLIPc4VoqQDACkGYPgdBQQjkoNEEl0QwhNFuPi3gqrmDEFuPVaI2huhHO6Y8nu9UGC0A1airA0QvDADcGIWg%2BzuC8CwBhIw4hrV9SNXge054SXmm6FcHY3TcE1BJTcaIOLdUeCwCSv%2BeA1kutIH64g0R0iYE9GCQwwAbhGD6WsKgBg5HULwJgTF9UuSaoRcIUQ4h4VQvkEoNQJL0X6BzSgZplh9B4GiPsyAaxUApC0c610vxnamEsNYMw2zU3gqwP2hC1RahZBcFOKY7QghTkGGUCoeg0gZC0Ru/dhQtE7uGPEDFXRMkMCgS0TwbQ9DXq0Xe89SxL2zH6Meq9cw317u5esTY2wJCEo4FU0gWzeA7JOLS%2Blvz/kS2ZQHCAuBCAkEDl0nlPSC1rGalqEYS7BmSD2EiBZ/hJAaEkGYSQ3ENlQW4nMpZHAVmkDWV0pE3EuDcQSHMhIXGoKSC4FBBZ3EIMkp2Xsg52HjkCouYKq5FKrjkEoBKjlry2CcCaCwe0/hXRMD8gWLgcykRcCRHU0FJAIUYsbTC%2Bt0hG1Ipbai3QsrsW4s1aB8DkHSUcHJTcq4VKWJaZ03pgzUUjMmbM6y1A7K4gYbibygtpyhUxZFRy5TDzUuSuC7pwURgjNcGSDQWgCr9kQGVai7V6rq1Vd1fqw1Dhq2mozOay1JKbV2odbQJ11a3U5s9XU/AhIeh%2BudeZ1QQbQTVrDRU1Fkbo23FjTsOpCak3dNTempQWb3W5siklotTAS1lorVW5NNm61wvs7IRzKK6kufbfmydVhu2RsXYO4dWRR3juiU96ds64jzv9QO5dPrnAQFcN%2Brd6A/0jAxQeoo2QH3TAKIerIMOP3Pt6HMSHmP6i/oWLu2Hn7JhI83adZo6OQOAfaVT2bXnxOcGtMQbTun9N5fC8Z0zGgOKobBRh7liWZO4cwPh%2BIS7ZssbY8Zyj/hhP%2BEmVRmjgmxOook7YKTfKTlnMudc25GXVMvLeRwLT3yTgsAUPaY09oIuMnGCC/AYKrM1ts5dmtN3W0gEWW5vFLrPPEtV2SxTSpqVM5YKb83luHQ26EkqCAbK0txf2HsLDmuBUpdi2KlTWWOV82QCkFIOFrdzJwrbggbjmffLlSVlqSqVVqt1TV%2BveqDVGqazFs1FqrWDcwLa%2B1jrnXdL6x65brrvUjf9aiwNyBg3TcEOGubvaFtLfjeCtbvANsZu2/1vbMm%2BDFpycdytjBq3ndhRIK7iLm23Z0J7h7xgu02Fe/Ad7I7ODz1Qr9ywM6oNzvoUDpduOfg4O66pOegIQBOF6J6qOAgkO8OZ6EB76T6NQoOt62OoBV6yBN6r6CB/6xO96uQZO%2BOpQkBAGCgbSwGAGdO/u2yjOJuPyEeVu0eUosevO6GXKKeOGpAeGWAYuoGkuIAZgxmewewUEUElGhWMyew/g3GKuNBuy6uhynBRGZgHGXAewPE6hcynGPEGggQs2ew1BUGnAgu/KoGwKshRh8hqeawqaGQzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_find.test.hpp)
