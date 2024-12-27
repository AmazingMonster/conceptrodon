<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-right-interview">To Index</a></p>

## Description

`Varybivore::KindredRightInterview` accepts a list of variables.
Its first layer accepts another list of variables and returns a function.
When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;V<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;V<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;V<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredRightInterview
 :: auto...
 -> auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredRightInterview
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;

        template<template<auto...> class...>
        static constexpr std::make_signed_t<size_t>
        Rail_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = KindredRightInterview<0, 1, 2, 2>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);
```

## Implementation

We will implement `KindredRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct KindredRightInterview
{
    template<auto...>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        { static constexpr auto value {-1}; };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First>
struct KindredRightInterview<First>
{
    template<auto...RightSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First, auto Second, auto...Others>
struct KindredRightInterview<First, Second, Others...>
{
    template<auto...RightSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredRightInterview<Others...>
                        ::template Page<RightSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredRightInterview<Others...>
                        ::template Page<RightSides...>
                        ::template Rail<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSAMxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8UkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMiXCyG8WFuJkSbgIAE9ngB9AjEJiEBSw7Ag8zghiQrzQ2FuZATdBYKjY3G/AF0wEgv57W4ASRYqXobEETEaX0OQKZ9IBQJBBEw7IMYpJTC8RAAdArqVcJsQvA5bgBpcLoYiYdAAJTwwAQBBZgniADd3gB3XEAdisV1uztuYolPMw0tlqAVcqVlxdtxVaoIt2UxFQRGUTGAnqdLpMDpBgcDbo5HpJaclnrhMvlisS2FukKYCgUvvDerwojFWMLyZTzuD6vDkdQ%2BoxtAbjcTFiDLUcyGLAgmmFUqWItzzqFuFrEXkwMIdAFouIn7rC%2B%2BvNzSA43XeL01K4VmM7nvb7scWDGXfZdgLrxYwCHWcfHG15MkZbh26DDEvcYYRkQv5dnC96PlyL6XvWiSOnuzrbnBu6poe2ZevmcqXMQwCvt2tyfuEwBhjGi6woBrZRqRJLYbhME4shVxIfBopoWebjTrcABieDEBM/rNqGWoMDqeqGsaprmsQVqYLacI8XxBD%2Br2%2BGnseHEXgq4kmkIeBYHh779qqLbAag0axvhKmGah7rqWpOYaZhV4lreCqVvgNYfP6%2B5GSGQFtqB%2BGBr2CbWfucyDsODCjuOk6cXO3hkWFPZJslPkwgArFYGX3BAyy3MuV7kiAIAsEwADWmDIpkwAROgqIkpkABeVVKfWaU%2BVZCHpT5eBUFFMUTjCHU9bcUCXmYATmAE7nVh6dZuApEykD%2BRo6XpHz0SVCULssyxBaNwUOrcuoEBsDC3Bom5LhuTEjT19RKAdh2Icdp3nQVa5wTdz3peueW/UdG6Md1QM7ndoMuvZmZsep070depblgqEGYE%2BggGZDzqEd%2BoH/hRpmBeBD5o1ByN%2BrB8FgyDqmww58MozhmOBjjxHmWRAH%2BVRFngUz9Hg8CdrAyxVzQ%2BeRDcbxy1Tt6txCJgaAiStDNygA8gQCDxJjgmatquoGmtklitJNokktBArfLivoCt6ua3x/NMal3Vi45PpaYbun6d5Lo65RZnUYZXU%2Ba7rsq85N7k7NnnM%2BFaJ%2Bf7gVpSFiH3f2PLVgNYqxTLEs7UlWMpsHL2IVlJg5XlBVFQQ6AlWVlXVUadUNXCzWtT7JfFyXgZ9VnY5DYDo3jYqk3TdH81m1LFurRJXubQW2DbfOmB7YPPUhe9xAXVd33bhD3cpo9i694rg2Tmv6XD36o%2BTePtYklbAg2zP636VtID56vaedW9mBnVvtwvpbiFihA%2BLoj63BPiObOE4L4%2BQgHA0awlRIGwkmaY2Mk5JuDtlrR2hcD4lXsiRHmbhtLCA2uTDuYDAyELpj%2BTsJI77zwpm%2BfB3cl6JVuGAMA5FPqIMbPtb%2B%2B4Qr8PSpvC6ZgYSWF1iJfWZD0GWlNnCHBDsF6iJ8rQ2yi52YkjIXPSh7U2El00UeRcRM3BMIMaw6hjYOELmuuohMID942KPo416fZxF8N3s4oxRchYAzTsxX6wSXGNlDnTDC7sWGI1clhEm6MXxUJZl%2BYieNeGJwYcTSCz4rEC2piLF2kTxbRNorHbGqTiEcwJm2HRvM6JqJpiAmmtIhTfEZEcW42BVCsA5IudprS2kHBFIM5k2AACOXgxB8mGaxLRUTWTK1lgAKQEvHdUEypldidlTX2A5M6nxgZOGIqBPCzmXpZB0LJ8a8NWc0li9zdxMluAAWT/kwKgXgCS8gGZcMOmksJM39KzV57zPnfOyPjGRKD5FSUwSSDQK0Ui3DMCtMw/oSp1LcGU/mLTridIACofBfDMs4IIIrVmREjeISkrgQDeS0cFDhsgknRYWEq5jNliGxHY6pvCzD7RBhS5AVKyw0pBPSsFXzmUCBJKuHlIBOWTO5eyj%2By8bmc1XIKiwHBVi0E4BlXgfgOBaFIKgTgbhrDWCDOsTYZEwQ8FIAQTQurVjlRABlSQcoNAAA4zBmAAJwBq4BlX1PquB2jtNIfVHBJC8BYBIDQiLjWmvNRwXgCgQCIudSa3VpA4CwBgIgEA6wCCpFlOQSgaB2R0HiJEVg2xVA%2BoCMuAIkhbjAGQEOKQcozC8CrEQYgek9D8EECIMQ7ApAyEEIoFQ6hc2kF0Cka06JUicB4Hqg1RqXVms4KrWU5bQyoH6k2ltbaO1dsAV6yREAPA1voOfB1yxeA5q0KsCASBq2pFrWQCgEAv0/pAMAKQqKaC0GNpmiAMQd0xHCK0BE67eCweYMQBEqsYjaAVjmx11aoKqwYLQBDC6sAxC8MADitBaCZu4LwLAZUjDiGI7xLDeALQfB3WOBWsptiOvCGKGNpraB4BiOiVDHgsA7rRHgBNNHSBseICcpQjx6PACE0YF1qwqAGFwgANRtKrZ4xrHWjuEKIcQU6TOzrUDupd%2BhDDGCtZYfQwnM2QFWKgVIjRqPLnJORUwlhrBmFTfJod%2Bl4CrDsCx5wEBXDTD8CkUI4RhiVFGCkIoWQBBxb0OlxoCwRjVB6FFpokx2ieE6HoSLMrivzCS4sVLtgStZfGCVvLKXqgRdtVsCQm6OCGtICm3gabbintbe2zt3br1jVwIQEgUjkjPqdRp1YmsmBYASHlUg7rJCJDlAGxIUaNCSDMIEJNGUAgBv0JwONpAE3JDlAELgAQfUBvDQET1Ia9tBAG7u9Ntgs2Ldze%2BotH6S0HorX%2BgDD761sE4K0FgFo7TLiYIjb8XAA1yi4N6/t%2BBB3DpSCZ8d5npCWaUNZhduhUUrqYGumjPW%2BvfbTfustspbjHuG820bKPiJo4x96sad7v0PrmwKl9Gn82ftQPe%2BIlb/2S8F6MEsRg0dcERWBiDlBoMLuQ/BxDpBteofQ5hhwuvcPPnw4RndJGyMUao7ruj9nGOmvwLqZlbHqOms48gbjuu%2BP1B3UJkT8HxPbFNVJmTjr5OKcwMph3RExdaZjAoPTskDOMF1wTszk7ieyCs/O01FO7Pqf81YJzAfXMbY815zgPma5%2BccxYILg2QsUPC4VqrLgRJNeCCJVrSw0sZAyzkMr%2BR%2B/FGyL3%2BrlXGj9CmMP%2BLbfp8tdq/lirjW5%2Br5q%2BUFfXAOsbC6zvy7vXt0LqGyN89ivufo8xxoKbOPZt4h36LwHy3MCrdGBtmN13bvo8O3aDKAbI1EgjtAhJAUgGdOAM1/tX080C1i1S1D0ZdIc60G1YdiAWBz0WAFALQhwLQedswJhscZtQsR1ZBCcs9p15BSc88dAQBEhSAqcacN1D96cd1Gcwcj0T0MCsCcC8D5pQxb05cf05tEgFtoD30Jcpdf0q1BCH0P5kBUhUhkRcCA1kR8CCBkRVA20%2BA6B1coMYM4NUNdd9c0MMMsMTdJc8MCMiMndMBSNyMxBbdZN7cGMQ9aNmNXd2MF1PdvdZNfcBNeAA9RMERg9JMh1w9eBI8Mho9xRY91NAc%2BBtMk99NDN09SDM8JBs8Z0qCbNaDC8HMAtS8XNW9K9shqMdhipi9Atgt4hQt2M3MF9sgO93B18Ese9l82tssB9Ggu8ctx92i%2B8GiBAZ9Ss8h58p8%2Bgl8t8OjmsBgu85g2gJ92s1g99J06dj9U1OBhsuDsDZxeDax%2BDptB05tH8Ac30X8391sesv8QBA05REhEgMpQ1QCk17i7Qnt%2BtWCIC/ts0ltNt/AMpdsI07Qk0fVJBg0uA/VJpD9Eh1jBsvixCes%2B0PiT94Tfj5NMhnBJAgA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_right_interview.test.hpp)
