<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::KindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLeftInterview
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
using Metafunction = KindredLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `KindredLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredLeftInterview
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
struct KindredLeftInterview<First>
{
    template<typename...LeftSides>
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
                    ((...&&Predicates<LeftSides..., First>::value))
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
struct KindredLeftInterview<First, Second, Others...>
{
    template<typename...LeftSides>
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
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSXEEADqgKhE4MHt6%2BASlpGQJhEdEscQlcSbaY9o4CQgRMxATZPn6B1bWZDU0ExVGx8YlBCo3Nrbkdo739peXDAJS2qF7EyOwc5gDM4cjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcBEuyUYrEwADoEb8HqNiF4HAcANLhdDETDoEKYKgEACSgniADc8JgAO5/EwAdisDwOLIOgOBoMw4Mh0OYbARcKR91ZBxRaIIB2UxFQRAAsp50H8RQymcKRaz2SCmGCTprOdyoTD%2BYittgDnsmAoFAKpXi8KJAQoherWWL0VKZagAEqoJiK5kuo6M0WNRzIc0CUaYVTJYgHJhnVAHcliLyvFUAWi4DIAIscLEG81tVUrA3rtVzdUCtTqIYa%2BfCTWaLVaBfdgLigYwCE7TaWXV50kYDj6/W8c5LpURR4qTu3O2xBNam/n%2B4XVw81%2BXazyjY24fdiMBe7cAyzB%2BFgAd5bR0OPJ56b7O3IfjwLfsW6fSiyWAdX9bq9awgcABieDEKMQpuhKWIMDieIEkSpKAsQlI0uCYEQQQQoqlu/4VgavKwgKiHCHgWAnmu0EPnKCprrhZ7qtulYQvhO5AcagqmuaBitgitr4A6mCUYxIrUR606%2Bv6aouiqrJroGIbavaEYMFGMZxgmRDJqm6aiYGDEyYp6omP4Vj%2BDmEALAcGY3CG6AgCALBMAA1pgAD66TABE6DudhJzpAAXh5/mnkZxnyYyCkReqeBUKp6mxkc%2BkxayUDvmYABs5iZQJ9oVr2bikUI5HCQKpCgeBkGmo5KbeJgCwLNFqUsnJuIEKsDAHBo%2BbrpuKUtTUSjNS1bWYB1xBdVmvW5iNim5lZc2RT%2BI2zZ%2B/XhRqbEscxhF7u%2B3EtsuB4dpgXZLs6gYXsOM73hJ3pSeC85nYuPYHbc61GWtv5GbtgFEZxr4iUZ11Xk%2Bd1TqgT5PUex0fiW34bv89x/XWAOvJhowVbuDYHEImBoHB2McfuADyBAIPEwPUbB8H4oSJJkqhVK0icmMEBV%2BOE%2BgFXk5TEHvV%2BqoiqjOPEQixWlcDYkEKi7qQ9DjGGYpovbXtDbvTxlrHXlQnS4G4mQzOq3Bq1A0y8p4aE4lmmJjp9XJZtslRebBlmaZlnWbZ3GfI5zluZ5eDeXifngkFIWXS1QbC1HsXxdbgIaY7sfquliJZTlusFeCksUeVlVYTctW6Y1S0RWNE1dT1xZ9cjKcikNrxxQlidJWXxlp4KGdZVnjo5wzJV5winMEwIs7YMX9Wl675fBu1nUHNmNezRt9eso3BzNwn0axu3ikQHvMW07i9NIUzaGs24fNU4LM8tY5zHXnRJy52VK536lD/bSOj0nL3b9cTCmvF0k80wHDAGAY4E5pof0DE1WBzsCyHwivPSaBwzBHEsJibEJ9SLIQpCzcE18BbvydvXL%2BHIKxP1vP3Ikg8AGR2ASyChNZXjGz/iffKjpb5kJTqAysSCEEmURqvYBjdkHCILKgqaS8kEiN4QZb8i077fRNitURLpVaUPYujTWR02ynXOj2RhIpQY/zHFAmiD0/RPUMa9OGfZPrKkRp9PC2idokzbLDRhZjwaWPutDOcsNBauJcT9AA9AAKmiTE2JcTwl/CiTEg4AAVYSPYDixISQ8JJcS8nROycjJ4DA9heEOOCM4dArg4T/O49W4sDzeL7A8Xx40mBUC8CUuoXVLHHwQgzfBzN0InHCBzTeghIkVVGdEqZEzIlCkcoEl8wSVyuORKGe07ltbxGwg8CAso2kdK6ZkcE0z5k1RAOwtwvsQB4AUJ5WERcQB1TAVAyxZgmqfWmGGLZVodl/H2YczpDgTknHJKgciTyrk3LuQ8tgTyXnpi2EWaBXBPkWA4EsWgnB/C8D8BwLQpBUCcDcNYawooVhrHTGYLYPBSAEE0JipYLkAj0jhFsAAHJlekWxuUaE5TygAnFsfQnBJC8BYBIDQGhSD4sJcSjgvAFAgBlQyglmLSBwFgDARAIAVgEGSGccglA0DAjoPESIsJOCqC5RmTKkgDjAGQOGKQcIzC8DtEQYg5E9D8EECIMQ7ApAyEEIoFQ6h1WkF0FwUg1JiBMGSJwHgWKcV4sZUSzgpMziGolKgeKNrMp2odU6l1kg3UHAgB4M19A4zbDRbwNVWglgQCQKa5I5qyAUAgG2jtIBgBSDMHwOgKFlUQBiOmmI4QmiXCTbwSdzBiCXFJjEbQBM1V0tNa9UmDBaAzsjVgGIXhgBuDELQZV3BeBYGckYcQ%2B7wJrrwOSYS6bowEzOBsOloyajpouDEeNi6PBYHTbLPAkqL2kCfcQGIaRMA5iBIYYAFwjCMqWFQAwx4ABqLNSa8lnSG4QohxDBr9fIJQah03Rv0AhlAZLLD6DwDEZVkAlioGSN089GZPhQNMJYawZh5WQe9RReASw7APucBAVwEw/AxtCOEAYZQhgxtSOkbp0m9AqcKAwWYgwKidHEwwHo4xPBtD0GJkF9Qxh9Hk3MJTtgrPqZjdMZoOnFMVFE5S9YEgU0cFxbK9NCqDgFqLY651i8y0YIgLgQgJBMG0oWA2lDSxKZ%2BiGFZUgLLJBbDhMK%2BkkgNCSDMJITK0r/CZUFaKjg4rSCStpXCTKXBMocsFRyxr/hJBJGFZlfzkaFVKpVfSlDmqdUtr1dmo1Xae01stWwTgTQWDknpBmJgWthxcEFXCLgcJCWepID6mNJGA1EekCRsN5HI26EHXGhNs6fN%2BblbwBVWaDVnAOHm%2BMxAFtLZWxaNbG2tsaArVW9tNa4sfMS%2Bq5trbUDVviMa7tMOQdDHm4tjMv3%2B2Cq4DKmgtAR2UHHZG%2Bd068NE8Xcu1dDg8Obu7Nu3d6aD1HpPbQM9eGr0IdvYS/AuIQVPvPTt1Qb7AR4a/diyNv7/2XEAxsQlIGwN0sg9BpQcHr2IcvENtDTBMPYdw%2BBw7hGg0ndkGdiNhLLtUeQzxqwdHf1MfS6x9jnBOMEFnDmS3fGBPxCE8%2B5j%2BmLN%2BEk3BRzwQ4KufmMpgoamTO5HD6pzIoe7Pme6UZloUeZO%2B6T1Z%2BPennMp5yGnnPWfvPLFWF5tFlX7sBc4B9r7y3VtXnW5t7bFboteri/WwbkPkuYFSwkdLovqu1Y2wV%2Bk/hBX0h5YV4rHWevys4P11VQ2tW6v1Tm%2BHU2LVWo4PN%2B1BwWAKHJOGckDfOSjA9fgL1%2B38NHYN/h43FGQAiuu4mi9d2029czeN3N8Vt8Or3wf5Mx%2BBUEolaiOHacWWwCWHeTamq0OsOnaJqoBNazyyAyQyQ7kR%2Bgq7kJ%2BBAWyn29qQ6uOVM%2BOE6U6i6JOpBS6K6a6VOMOW6O6e6nOmAh6x6p656dKbON60ul696POz6kar6yA76wuZIouhK4u06UuwG3qcuvACuMGyu7OaukOfA6GCgWGNIOGjAeGeugaEghuoaZGJuOgD%2B5uxgtGNgNuImRKbGmQ564Svsbulg/Gj2gmUsVhiemQLggeqeegcmJQumGmEemQQemm3SheTmNQBmyeQeHhlmMwNmARTmDmPhSR8R/hbmReCgnmQar%2BM%2Bj2VeP%2Bu%2B%2B%2Bh%2BgBjowBLesWdakBjaTKpAKWWAvePmA%2BIAZgG2WwWwgQBWWO/KWw9ITWeRGaiqtgA2NRjUGWIAhW9WXAWwWUMxgqDWWUGg9IlWWwb%2Bs%2BQxoxPm7qAxfWUBtRkG6QzgkgQAA)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_left_interview.test.hpp)
