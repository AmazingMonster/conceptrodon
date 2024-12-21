<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left">To Index</a></p>

## Description

`Typelivore::KindredFoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
KindredFoldLeft
 :: typename...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeft
{
    template<typename>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will left-fold 2, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A-B>;
};

template<typename...Args>
using Subtract_t = Subtract<Args...>::type;

template<typename...Args>
using Metafunction 
= KindredFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract_t>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              Operation<
                Initiator, First
              >, Second
              >;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct KindredFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredFoldLeft<Others...>
            ::template Mold<
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElwAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgAdPfY9GyCCifYJhoAgpPEXg4A1ABpCLoYiYdAAMU86FCmCoBH%2BJgA7FYkQARE5WL4fT4Aelx/wsTCU/zcxPYOJx%2BP%2BUNo6H%2BAm2txxewOR0wJzOl2ubH%2Bj32jAIbxxPz%2BCOBDFB4NpMLhQtO/Oe8ve2JROP%2BGv%2BrMOTGOpwuV2YvIAkgxsrqSMKvpr/qKAcpiKgiABZaHqzXIrGfG027Xszl%2B3Uc/Xco13e5vf7IAwKBT/ADyV2IupyVu9Po1doRaMwrTo7oznoLGc1XiyRi13MR1pLNpOaITSZTAk5pvNRDIfKeguFgS9teRGL7lJrGcDerO%2Bx1E4NPPDzMC2CjMYU91un2AYIFLzTtbLEWA/wASqgmPT6/8c3naJyN1ulauI4uQCBZ5ji4P39jR1qp/6Q4aNxrnemDbgQryLsW%2B4Vq6dKIoEDYOk6qCwegt6bqBD5rr2XqfsO354gSMpagA7ngTIsn%2BQYBqGNw0ngxCTKQlaAbyQiYGgkpplmQIgmCkLQrC8KchCDFMf87GcWhkGqv2mrjsGXKsZg/xto4FrELumo8UhLpuj%2BRY/r6VEziZimzmG2GLsuxJxomCTNgwWkZjxV5MPmRkemqnkZtBh6ztW6a1hqF72cmTScsWwWNg5EWnFF0WqWa6kdsxomMUKPklm8zGSQIaFZYWkH4UFPp4bhWUKQGZk0cpVlLtGtnARhYEQSqpU2n5x6nueCGXrm7k3qcIGtfVL5viVdbol%2BnzFlVAFzs196Cm1UHloeqHwYhjp6XS6HLS89UzeVI6EceHGbFkABuKlkkoICndSxEEGR2zMQghjoPQWoICpNAZaRqD/GkbQ3HsjGkFSBKff8YLIJdKldQQv2w5gkzMl881KXO9EZcxFl0Xlkr47RbBrvGyMJKtXw8RKUoCXSQnym46XiUT6DMRTv2MUdslzTVC1hkl7aWjJpU6TtKH6aVhkdfJAuTmy1GC0BT4NSuMXhamYu1q5A0eXLIXeYbPpI1WCVFQ2dP8TKTOclzVO8ybNrjWZ/yoZFhUlmFjme873tNnFbgW4lGpqXgGlpWJmX%2B0V2C5Rx%2BUhwOOuJW8rtK3s3Vnvbgfa%2B8k3ZdNJUh1jZek/OkaNbGS2YStzmm%2Bt2e9Q2bn5sNLVYWr43cjNU1DhVpXl3V9wjQ%2BDddZtF66VLe0dwd4FHSXxeD7iABUG%2Bb1vuJUpvAAq2BCHvm871869bxfp%2BzdiZiBBE0ZeFg8FuJx2xpOBaaUZn5kV/8nwk8pQk3ECC/ABEILwsQQFMAcJSY2nUm5vgMn1SY6AXwRD2JuMQAB9Ti8xBCcnQcxT4L4rpiC8JgAAtBYEhZDgwF1wivU6w9Fqj2IMAamnwurgMgcmBwWCEQXm4VAmBw02GPgXNgHuVxjqYwVgTMmrD2FpkngNKgXgGAOByIFC81tpSCTlH7G0KC0GCEwJg2gOCBB4OZoQ/4gQcrFmMSAdBZjkwWNwa0fBpxbGSAcT%2BJxLjzGWIYNYghghmL2NTunEAHtRHsKXoPLhXg0jFHBEeNGXhaAxwvAE0xQSPGGBseE/4FCACcOFTpdXSQoTJAi%2BrOlUeozRLZTi5IwW44JoTvHFK4L2dqL4Tw51OEI3hBB%2BEVIIvMRwyAsG2QSAQCATiFA3FmRBNw1Tam5WSak9AGyslvBWJiDgaxaCcH8LwPwHAtCkFQJwYOlhrC2g2FsFS5hAg8FIAQTQxy1gAGsAiSFuBoSQXAkSBA0P4DQZhkjJDMAADjhfoTgkheAsAkBoDQpBLnXNuRwXgCgQCYq%2BVc45pA4CwBgIgEAGwCBpC8AQcglA0AHDoAkKINxOCqDhckChyRJD/GAMgZA/wpC3DMLwcEhASB4FQVwGQggRBiHYFIeV8glBqG%2BaQXQcqSLJjSJwHgJyzkXM1bi%2BM9K6UIlQFQf4XKeV8oFUKkVgKzD/AgB4Fl9BiCIlvlwFYvBiVaDWBAJAzK0isrIBQCAYaI0gGAFIMwfA6DgwJRAWImrYgRDaOcA1vBM3MGIOceMsRtAcWJR85lSp4wMFoDmklpAsCxC8MAMktBaAEu4LwLALBDDAHEPW/AcNHA3Q7dczAqgLp7FzeQUxpz620DwLEZMhaPBYE1SAvAaLO2kBusQWImRMA5h7UYBdRhvlrCoAYdhAA1PAmASL2UuR8/gCrRDiBVS%2BtVKh1D1u1foXtKBrDWH0IuglkA1ioHfjkDtFCUH1lMA8ywZgcW7uIDKtG8A1h2DLTkFwkoZh%2BDlWECIIwqhjDlcUbIAgCN6Eo00RYowai9BwwIAY0xPBdD0Nh5pzQphDBI0scjtg%2BM0blfMdoDGyM1Cw887YEgjUcHOVi01nBbXct5fywVwrRWuogLgKV3q3l%2BoDeetYv0zxjAgH8kAkhAi3FKYEJEkhgVmEkMkDF/hkilKRRwFFpA0XvNuMkFIcLSlwpSP4EF/gHOpGxbwXF%2BLCWfPPWSylIbqUWvpYy6NqBPVso5RwNoLArpIgoUwGyFYuClNuFwIFEr8AdhlXoT9ir33SE/Yob9mrdCJt1UwfVnaFNKbizczg5raX0oZDaorJWysVcPFVmrQK3UevDV6n1gQzD%2BuSyS4NobctrYSNlmNXqQAzdK41IwVWuCYpoFkqmlB031vzdm6dL3C3FtLQ4adlbBTVtrZqxtzbW3tund23t/brmDpwyOzV47J07A%2BS4ud1yF1LuzaunY1yN1bo%2Bbu/dSgj0Q4PCly9TAb13ofYaadLW33Kva7ITrGrf0gETQYM9CGrCWBA7EMDVmblQasZwWDBBpJok59YZD8XUPob51hhoLG/AQFcKJkIkpJPLAo5kKjuQOMFC1yUHIGuhPcaaGxjoevCPMZ4%2Bb43THxMW/yFbh3dv5PrE2HJv1PnhsqY4P8c7c3LsLeq7VjQbr9Mdg28ZnbQazOYAs4kfnc6/MBeq8CpE0WkRgskK5vlcqRsJdsElwNpLyVUppZa47B2I3srYJwIrDqWAKCusKq6i32STHqwZprcradKokAzwQTOf3XN0MEPrA3DXe5NfWs1mWrXTeICwRvzfW/t6DJMFb1f1tvMCNtkve2UDb6O1Gk7YwW8pKwW30pWCO9jIb%2B15ND200ZqzYWt7b%2Bi0lrLT93LVaa11pQ6YBNotpiCg7brg4npY5doMQw4Yb1rw7wxTrbrI6apo7LrnCY7rpoa468D44HpE4nok67Z8BXoKC3r3qPo06yCtb06qrD7dYgDBDs7GBAbc5o5y4C5NAdq4jGIS5IYoYJBoZYCcGm64bK74aW56DEYVCMa0ba5NCq50ZG4CZyFiYK424iZSHqF9CsZ8au5iZaFO5cb6GqFSZu4KCybKpDYz44qqYP7/BN4t7/DX63B37h4NYkBR776makDmZYCJ4KYp6s7VaBCBD%2BCQogoYphFIjJCIoF6cCJZEq%2BH/KSD%2BD2b%2BBwrQqlKSClJgqOZcDMGcCBC2HxaJEx4/I%2BbirKaz7lEH5rC7pZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left.test.hpp)
