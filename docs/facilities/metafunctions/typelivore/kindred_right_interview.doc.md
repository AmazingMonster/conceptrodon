<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-right-interview">To Index</a></p>

## Description

`Typelivore::KindredRightInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;E<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredRightInterview ::   typename...
                 -> typename...
                 -> template<typename...> class...
                 -> auto
```

## Structure

```C++
template<typename...>
struct KindredRightInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = KindredRightInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `KindredRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredRightInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr auto value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredRightInterview<First>
{
    template<typename...RightSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
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

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First, typename Second, typename...Others>
struct KindredRightInterview<First, Second, Others...>
{
    template<typename...RightSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
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
                        ::template Mold<RightSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredRightInterview<Others...>
                        ::template Mold<RightSides...>
                        ::template Road<Predicates...>
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

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSXEEADqgKhE4MHt6%2BASlpGQJhEdEscQlcSbaY9o4CQgRMxATZPn6B1bWZDU0ExVGx8YlBCo3Nrbkdo739peXDAJS2qF7EyOwc5gDM4cjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcBEuyUYrEwADoEb8HqNiF4HAcANLhdDETDoABKeGACAIAElBPEAG54TAAdz%2BJgA7FYHgc2QdAcDQZhwZDocw2Ai4Uj7uyDii0QQDspiKgiABZTzoP5ipks0Vi9mckFMMEnbXc3lQmGCxFbbAHPZMBQKIUyvF4USAhQizXsiXomVy1D41BMZWst1HZnixqOZCWgSjTCqZLEA5MM6oA6UsReV5qgC0XCZABFjhZg/mtuqVUGDbqefqgTq9RDjQL4WaLVabUL7sBcUDGAQXeay26vOkjAdff63rnpbKiGPlScO122IJbc2CwOi2uHuuK3W%2BSam3D7sRgH3boG2UPwsADoraOgJ1Pvbe524jyehb8SwzGcXSwCa4a%2BoNrCBwAGJ4MQowih6UpYgwOJ4oSxJkhSxDUnS4LgZBBAimq24AZWRr8rCQpISSQh4Fgp7rjBj4Kkq654eemo7lWEIEbuwGmsK5qWgYbYIva%2BBOpg1HMWKtFejOfoBhqbpquy65BqGuqOpGDDRrG8aJkQKZphm4lBkxcnKZqJj%2BFY/i5hACwHJmNyhugIAgCwTAANaYAA%2BukwAROgnk4Sc6QAF5eYFZ4maZinMkpUWangVDqZpcZHIZcXslAH5mAAbOY2VCY6lZ9m4WGjKQo5EuRlGiR%2B5rOam3iYAsCyxelbIKbiBCrAwBwaAWG5bmlbU1EorVtR1mBdcQPXZv1eZjcpeY2Qt0W/mN81foNkVahxbGsUR%2B61S2/EroenaYN2y6ukGl4jrOD5ST6MngguF1Lr2R2biZG1/iZ%2B1AcR3FvmJJm3dez4PdOqDPi9x6nZ%2BpY/l9fz/fWgOvKVBDlXujYHEImBoPB2NcQeADyBAIPEIO0XBCEEpVKGAmhNL0icmPlfjhPoOV5OU5Bn1bjFzGozjJEImRwjVSDEkEKinpQzDzHGcpIu7QdjZHXx1qnQVInS0GklQ7O60hu1Q0y6pEaE8l2lJnpjWpdt8lC07pnmZZ1m2fZvGfM5rked5RJ%2BQF4IhWF11tcG6qR26CVJYCWmOzHmqZYiOV5brRWYRBZUVchFFUUd9X6c1K1RRNU09X1JYDf8rvpSNrxx9bCcpWXpmp8K6c5ZnzrgpzAjc3nVWF82xeNaX5txRX3UHDmNfzVtydio3BzN1GrfEO3ykQNvcW07i9PIeSTPoazbi81TAv1zHzmsTeDEnBLBc1auU%2BR3fu2js9Jy96/PERWXkGce6YDhgDAMcScs136mRajAxaIY95RU6rPMwRxLCYmxIfCWJ8qQs3BJffmb8b4fxAPfGGT8GYv3hv2eBcVP5ckrN/f04I/40MAUAzUICqyFiQWZJGS9OGNz4aqEMKDpp2XnrwgRJD%2BGe3bj9E2a1BFulVowzi6NNatlOq9S6vYI6ajBsw%2B8kC6JPRYfOc6ej2FfVEcouuYoRYk3bHDAxRiIamMehQ18cNPqbUeEjfxfwAD0AAqcJETIlROCSEyJBwAAqolewHEiTEh4YSomZIiWkuuTwGB7C8IccEZw6BXFwv%2BdRe1nEImBiKdxk0mBUC8PkuoPVTEH0QgzXBzMMInHCFjNeghQnlX6eEkZQzQkimct44GfjfrTHDJ5bW8QcIPAgPKBpTSWmZHBKMyZdUQDGyCgQJyIA8AKG8rCG43CJymLMC1fxCzHRLJtCsv46zNnNIcDsk4lJUCUWuYcn%2BbhfZnIuQoK5ByGqgMgaY7MDyLAcCWLQTg/heB%2BA4FoUgqBOBuGsNYcUKw1gZjMFsHgpACCaCRUsNyARGRwi2AADmyoyLYLKNBMtZQATi2PoTgkheAsAkBoDQpAMVYpxRwXgCgQCispZipFpA4CwBgIgEAKwCDJDOOQSgaBgR0HiJEWEnBVDMszNlSQBxgDIAjFIOEZheAOiIMQSieh%2BCCBEGIdgUgZCCEUCodQCrSC6C4KQWkxAmDJE4DwZFqL0VUuxZwUmZwtVSlQIlU12VzWWutbayQ9qDgQA8Pq%2Bg8ZthcAWLweVWglgQCQHq5IBqyAUAgA2ptIBgBSDMHwOgTMZUQBiAmmI4QmiXGjbwYdzBiCXFJjEbQBN5Xkr1e9UmDBaBjqDVgGIXhgBuDELQGV3BeBYFckYcQm6IILrwJSUSCaYwEzOBscl/SagJouDECN06PBYATbLPAQqj2kBvcQGIaRMC5iBIYYAFwjBUqWFQAwJ4ABqLNSb8nHb64QohxA%2BvdfIJQagE0hv0FBlA%2BLLD6DwDEGVkAlioGSK0w9mZPiQNMJYawZgJXAZdVReASw7BXucBAVwEw/ChtCOEAYZQhihtSOkVpom9BycKAwWYgwKidEEwwHo4xPBtD0AJ759Qxh9Ek3MGTtgTOKdDdMZoanpMVH40S9YEhY0cDRWKhNkqDiZuzVam1c981oIgLgQgJB0FksrRSuDSxKb%2BiGDZUgtLJBbDhDyxkkgNCSDMJIbKIr/DZS5XyjgArSBCrJXCbKXBsqMq5Yy6r/hJBJB5dlTzQbJXStldFhVtbVV1vVSm7VLa22lqNWwTgTQWCUkZJmJgWsRxcC5XCLgcIsVOpIK60NeHPU4ekHh/1hGg26G7eGyN463MefFbwSVybNVnAOOmhMxApszbm1aBbS2VsaELcWxtpaIv3KrXBpV9bUAlviDq1tYO/tDEm9NzM73O1cq4KKmgtA%2B2UEHUGydo6MM4%2BnbO%2BdDgMPLp7Ku9dCat07r3bQA9GGT1QfPVi/AuJvk3sPWt1QD7AQYZfSioN77P2XG/RsLFf6APkuA6BpQEHT3QavMDhDTBkOofQ4B7b2HvV7dkAdwNWLjskdg2xqwFH300cS/RxjnBmMnNY%2BRiwnHrvcalnxzTRm/DCfgtZ4I8F7PzFkwUBTencgB/k5kP3FnDOtJ0y0YPYm3fR5MxHjTtnY85Hj6n5PrnlirBcxW4rl2vOcCey92b83ryLeW6twtoXnURYrUDnrsXMDxYSIl/npXytLay4yfwXLGSsuy7lprbWJWcE63K4Hyq1UatTZDkbhrjUcEmxag4LAFCUgjJSSv3JRiOvwM6zbmGdta8w7rojIBeWnajUei78b2tJsG2mxKK/LXr83ymHfRUpRFuh02iLWwUW1aiq/WC%2Bzauqf%2BpaIAm%2ByQyQnk2%2BXKnku%2BBASyz2FqPa6OVMmOQ6I606eOuBM6c6C6JOYOK6a6G6zOmA26u6%2B6h65KDOZ6oux6l6bOt6Qa96yAj6vOFI/OWKguo6Iuv6LqEuvAUuYGsujOCuPWfAiGCgKGdIaGjAGGGuXqEg2ufqBGeuOgl%2Bhuxg9ulG1GrulumQh6wSvsxuHGXG8QPGt6tGCemQLgXuceegEmJQ6mSmgemQ3uymrSWeNmNQWmMe3uUe3QSeZm7hNmVmzhkRMw4RDm2eCgzm3qd%2Bo%2B12xer%2Ba%2BG%2BW%2BX%2BzoP%2Bte4W5aQBMWpAcWWAbebmneIAZgS2WwWwgQWWKOHKWwjINWqRiaUqtgXWwBzUSWIA2WlWXAWwOUQxXKVWOUGgjIxWWw9%2BY%2BHR3RbmDqbRHW3WNaSwwG6QzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_right_interview.test.hpp)
