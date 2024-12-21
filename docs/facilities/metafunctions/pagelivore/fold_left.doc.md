<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-left">To Index</a></p>

## Description

`Pagelivore::FoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::value, Arg<sub>1</sub>
   &gt;::value, Arg<sub>2</sub>
      &vellip;
   &gt;::value, Arg<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeft ::   template<auto...> class...
           -> auto...
           -> auto...
           -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldLeft
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<auto...>
        static constexpr auto Page_v
        {RESULT};
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<auto...Args>
using Metafunction 
= FoldLeft<Subtract>::Page<1>::Page<Args...>;

static_assert(Metafunction<3, 4, 3>::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldLeft
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables>
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Initiator, Variable>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
            {
                static constexpr auto value 
                { 
                    Operation<
                    Operation<
                        Initiator, First
                    >::value, Second
                    >::value
                };
            };

            // Recursive Case:

            // Fold twice, handle the first two parameters,
            // and recurse using the rest.
            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {
                static constexpr auto value
                {
                    FoldLeft
                    ::ProtoPage<
                        Operation<
                        Operation<
                            Initiator, First
                        >::value, Second
                        >::value
                    >::template Page<Others...>
                    ::value
                };
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgABxBAA6oCoRODB7evgGp6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcBJgsKQZbJgDMbls7e5iHbkxeRAB0d4fYANTIBgoKjwDyKfFMdQwPJg0AEFRsQvA5HgAxTzoEKYKgEQFAkwAdiswMemMeJ12v3ORyuREeAEkGJlfiQARisaDwQRHspiKgiMomMBztTMaj0UCsXzHrSIUJXggkfysdyxeL%2BTizhdCag7jcAGpNPBMGL0BRU3nSvmC%2BmM5moVnsx6SlEAEUOPKlesxAHoHY8LEwlI9LkoQEi7fanVCYY8BOsbr69bK8fLrqhHqriOrNfjsGHpQaGUyWWz8W44wn6Dr7RK0SnC9NHMhngJRphVCliI8FY8AG5iLwc3WFvncz7fYi/LIXUnkohkWNqjX5g7YEAgFveTDmq02kv81HWg62zl%2B53Q2jobEAdzwIZXfIj%2BwJ0aheGIo1IDavQkwaAY6ALnbTRsz7IukJvd8eJ8XzfKdTyLHlO35Mtj0rBhq1retGznNtzS3SDuzAwsvh%2BP4Lkw%2B1sL7XCjnwyCh0cClRz/W9ETQyCJSnGdkMwe8gIEN86Po81GNnVt2y4rklw3fC12XYF8P9AAlZ9VgyJsF09dgfU4/l/V3fcCCPdZ7wQQx0HobEEAXGgaMPGMUiaVhMC2W9SAk509MeYgZNvBcvAyIxDIXZzRlDFSz22XEL0uK9qIAxs2Nfe8FSVD4CCM2931LAgwQhL8TSzX9/wIVjn3Y%2B84oShQlSS%2B1JX81NGnLWD4LrB8iWY0jwKa8V1LhBEWv5Gd0tNbNOr1Qj%2BwEPCKq4wbiLcfrO3I9UR3vMLaI7ATxQeJi%2BNy4CppWnjGtGsqePPBdeouQr4mK%2B5QL2vU1vnTrROEvb7og6UnuUpaAtOSNL1uO4gWAZztkYAhtUu96sXc8JgAZLNuMtQCRRnQ702NY6jj%2BgG2EEc7Q1Ah6lte8St0OqMfpudHMEBrHSohzzeth5Hv2zcnKeBkrcdtITNyBB0ACo%2Bf5gXBYdJFef5x4ABVMFGd4BeF4FRcFxW%2Bbl5FgWJ76YyBaKrysUG0yELwYhSpgHB9Yst2gisX1qxCr12/G0UeIEAFoLEXdcOY9t71ZC0mgWIYAQeTYEaahgBZaymCoLwGAcLJUORA44ba%2BFESOA2jb7U2eNRtwuFWkBc/9wO2eTPGkUtgB9N0lGaCAI8aaPY4mg572kR4DgL5jYcOOHnYATgWG0OCWWhOH8Xg/A4LRSFQThJssawBRWNYF3MA4eFIAhNBHpYAGsAkkG4NEkLgUQODR/A0MwADYb7MRJEn0ThJF4FgJA0DRSCnme544XgFAgC/tvaeI9SBwFgDARAIAVgEBSNccglA0A7DoPESIVlOCqESDfZ2N9JCPGAMgCsUgbhmF4JgfAI48DoD0PwQQIgxDsCkDIQQigVDqFAaQXQQQDx9hSJwHgo9x6Tx3rPTgHxrjwPpKgKgjwsE4LwQQohjwSFmEeBADwKD6D1nXlwBYvAQFaCWBAJAyCUioLIBQCAZiLEgGAFIMwfA6A2UARAGIoiYjhCaAATwEbwTxzBiDeI%2BDEbQz4QGb2QZjAgHwGC0F8ZwrAMQvDAEuLQWggDuC8CwCwQwwBxCJJvOEvA8lMkzxrDJLYfjyCCBqKI2geAYh9iCR4LAoiUp4Hflk0g8liAxHSJgS02w8kNKMDvJYVADCB2VHgTAB5sJT03nQ4QohxDMOWWwtQojuH6DySgaw1h9CNMAZAJYqAUh/Eyc7UYIFLSmEXpYMwv9enxiwCciASw7DFOcBAVwEw/BBFCOEAY5QhgFAyH8f5eg0gQqyLMQYCQRg1G%2BQwHo4xPBtD0F8uO9Qxh9GBXMMFtg8VQpGHi%2BFoLEWfJXusCQQiOAT2/qIv%2BcjsG4PwYQ4hR81EQFwIQEg5ozAb30VvcZSwjJMCwAkD5pAD6SAODcfuBwUSSBPmYSQN9P7%2BBvv3Z%2BHBX6kHfhvG4N8uA30SP3ZIN9/Cn38Eqm%2BTLOF/wAUA0VoDjFQJMTAyRCCrE2O0egtgnAmgsCbCiZ2TBngGE8lwfuNwuDH3IZQkg1DaGyAYWs6QGylBbM4boRxvCmD8KyfSxlP9eB/wkXA64QZZEhrDRGqNeSVFxoTRodRmjzHaMFQcMwIrDFgK9f6%2BIiDrGoC0UMet4aXh5NjVwL%2BNBaAuMoO4zhASfHVPXUEkJYSHDVKiUDWJ8TRFJJSWkjJ1SckjI2DPfAzk46lNERU5A1wNib3CFsMenCGlNJ8a0m9Bj4xdM3r0/pSghm5KMKM0A7q%2BBTIUDMuZCzqnLIzUwrNshNkcJnvm3ZYz7lWEsEcmI7yzkXKyFcm5vcCPWCeRWl51CpbwE%2BcinFfhfmvlJcEV8FL5jgqKNkDFeR%2BN/F40S7Ffw0UtCEwCzoKKpNicRcS3oXHpjNEU3S5YqxaV6L1WW5lnAGzEFDeGyNM6Y2tuPuovlI4e16IMWK0gEqpWUHpQao1caT4ojtSic%2Bkh1V4KCOWsR/9bCuoHR6%2BAXrYFSNHcO4ggaNghsUSwBQTYKxNljTcM4owk38teWm%2Bhqz0MsPkDm7DOgQCt0LcWwRemRFOvET66RdbjMpbSxlrLOX6QaPHV2%2BIPaDj9vGeA0xfWLFxfG9o2cyAUgpErpl/ulduvVza1m5xZ0V0eK8UEzdO3gmhPCfu8d0Sj0JNvZgZJqSxAXu6VeqDAHSB3uKY%2Bzhz7X3VI/XU79jTmneP/e0oD1TQMDIgyMyGI3JlsgQ7M%2BZ3xFm8FQ8ViQGHWHle2VVvDxgDlEZ/aR2e5GqycAdDc/ZDyLB0dngxt5zG5NsZcJxmTeggWlARdCwokKmcibhQStnSKui4pU1zunknyW88pViklwu1P4tZxL3TCgaVMNLQ13%2Bhnkv4NS%2Bl5sXW8SjGs8mnRQr7NuqMeKzAkqhgyq/e5kAZg40HAOP4K%2Bp9P6O5ROax1avQuAOAY5uV/hFX%2BESLffukh%2B7n2VVwVuX6Diq4rZwBz7r6VkK9wn0LEWli9IyM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_left.test.hpp)
