<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredFoldLeftFirst` accepts a list of elements and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first element as the initiator.

<pre><code>   Init, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
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
KindredFoldLeftFirst
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredFoldLeftFirst<Initiator, Element>
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

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredFoldLeftFirst<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIaAKykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkiyJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4CABPRKMViYAB0iOw90YBAUYOwf2GxC8DguAGlguhiJh0AAxTzoAKYKgEMl4YjDC4mADsVhZABEwVZTn91usLhYmEoLm5hew/nyBRTaOgLgJVvC/gCgU9MGCIdDYWxrgw0k8SKQLlCYcwdcjAaiMViCDi8YSGMTSTKqTS6QzhhqrnrHAayBcLQ8CNbeWy/hcI8bAXc1RqVTGQeCTdqEYiMRdkAYFAoLgB5GHEJ7pEMnSMXbG4ggXDmYep0cOR1k80tlyNeVJGY1a5mnVuN0EcvMFosCL0%2BvB%2Bo2Bq2gzGg5tl1lc%2BeS3uR%2BPA9VJ6ObuNas2ppWzjNZhSI%2BEnYAky2CdGzhsR9vBYAXABKqCYcrBg5rddoGsva8gzPNNZxAEBk25SVOSg3l3mlSljQAdzwRVlR3WMk33OFdX1Ih/WTA8LnpRkCCNQicKETA0EdEsK3tIkSXJSlqVpEjPXBb08MNYiPTIi4qJo9ASybB8o1VRMIQwySKLYc900zYUc3zaIRwYEsy3oqtfyYes1wjUT9NbJ9O2THsWz7b8h1UmoNTEvsVMLWzwXsvtcN9fCjXY4MjMs2cjUEgRhN81trRXIyl1g34jI3TCpIkrdNVNOF5OPRTs3PQDMBvNENLbDsX3fT9mQHata10/9wSynKQKPbBwMg8LfhgpqpTfajllSAA3TBRXFEBVzOBDZWQ1DMCNBBDHQehjQQXqaFI2brwuRIGjhAFGVINqpouElkE63qTJfAg5t2zBhiVU5Ypk7CdS4jyeNk3rvPI27esCx1XuSuTEVzE7ojvTFTi0glGOdFi3W8sduP9F6BOooKjT%2BubGVSoHmoXddpMS66cbetGTyU6ynOLe8jJBnS9Is5kwxCx8Cq7GFzLckrBwdJ1mNlVj3VIuy6dbRy1L56mWcF5y3FclmI3uidPN43n%2BcXfz4aEyXQuV5GAfk/mMQa7G3w/YTwTF0m50xgyWubMTcbjbG92%2Bw8FNPTKr2y4C8vp58DeKqzKcqtxquAtGGq1KLIta94vk%2BH4Pk2ANVFYO5etePko%2B%2BQbzFBYJMy8LASqSzAAH1bV03Kyd%2BMws4YHO841GjVkSMv0dTy4hC8CIS7xFOrrtrCHYuE4vpTQU6NtSsBPbzuCAACSqAtoPNi4jsZ9UItK4Z0HA4IASvMRC5oyZBA1bejROcCurELxMAAWgsc/L63M3oOXK2e4S%2B2U0y4hgEBv5l7bjuhY8RWQAVPWetB55VW/rVXWEFQ4RzOLsC4ABZcqVAvDV2eN3f4vd4oJjxg7Am6VaonGgSWZeqD6joMwekcyVl2ZMRdNzKGLlyYEE3iAbemBd60H3gIQ%2BwZwQnwuFwDEW02EcK4TwvhDABHH0EEaUEYixIby3oIbhhZeEH3qEfIRCiLiSGURItRO9NEyLkXo/iSjy4GTAiAIqRsA7QLRmHSOrcvCJFyKSV850vC0CrNg/%2BHivHoB8QoPxPlfjr3YSYjRe9tGGEEW4YR18ACcYVX6IMuGEiJLxDh/wZjk/xrMUFoIwQ4UmbhQFAMEU/OCWTtgXAACrnQCfk4G9RHDIELkpaIBAICqJAAoOEPS7xuCKfxNuniUjeN8f4jEcwoocAWLQTgcReB%2BA4FoUgqBOAS0sNYcsSwVi9UzjwUgBBNDLIWAAaxAHESQ8INAAA4zBmFSakrgcQXnPK4CyFk0hVkcEkLwFgsQNCkE2ds3ZHBeAKBABCy5WzlmkDgLAGAiAQBLAIIkLwZEKAQDQLcOg0RQhwk4KoZ5AA2a%2BVLJAXGAMgZAIjHlmF4KSQgJA8CbzaPwQQIgxDsCkDIQQigVDqGRaQXQbQkKFkSJwHgKy1kbKuTszguY8W4qrKgKgFxKU0rpQyplLL4RmAuBADwxL6DEGZJXLgcxeBIq0AsCASAiWJBJWQAl7rPUgGAFIMwfA6AbXhRACIqqIjBAaJCBVvBI3MGIJCXMERtDUSRecolQZcwMFoDGyVWAIheGAGKWgtB4XcF4FgFghhgDiHzQyNNeAerlu2ZgVQHUASxvIOooF2zaB4AiIWRNHgsCqttHgMFFbSA9WIBEGZNZq1GH7UYK5CwqAGB/gANTwJgJCKlNnnL5cIUQ4hhVHrFWoVV0r9A1pQNYaw%2BgB3wsgAsVAjd0jluvhvb8pgDmWDMNCmdxBuXnXgAsOwjbnAQFcGMVopBAjBD6CUAYbRchpAELBnIKR0MMGmP0Mo7RIO1BGE0TwLQ9AQYqQILojQ8PIYI5MUYZHxi2BI3R2Y9rFjLFWBIJVHB1mQtVTCvV1LaX0sZcyqQprzW4E5Tas5DqLmroWHNT8AwIC3JAJIUE8JUmggBRoSQZhJBUo0PEKlqT9CcBBaQMFoIuDwipVwKlzzUm/KpQ8r5emqWCclTCuFCKlPIpdRi11WLNV4vIJQH11qyVsE4A0FgXUWTXyYITTsXBUnwgc62/A%2BFuV6CPQK090hz1KEvZK3QgbZVMHlRWvjAmoW8BhRqnFeL5S6v1WJ9LL5MvZaeeay1HrrW2tBGYRTTqUVhZi9EKLhLUBWoGIpIwmXyhBv8QDSg4bJXxujV23bibk2pocF2zNqJs25tVQWotJay1dqrTWut2z8B7UcM21VbaO1rHOVw3tvB%2B2DujSOtY2zx2TvOTOudSgF2PefKuvgG6FDbt3furtRWT1CtK7IC9ErtlVZvSu39VhLCPoiM%2BjTOz338M4F%2B9hP773/sA9EYDWByfgaqERlwjpMNtAQ0UfDWG8jpB50kbDNR2MocI1R4j3QReUZqDRnoiGZiS8Y6RrIcG1cS7KOB45PHONAsa0JzgImDX0uW71rLOWZN5ZIKN%2B1jrlOkFU1gGIFOgU2bs1lwzLI4ipP%2BaCIzJnJBtCa2q2FthAuTZC/AML2KtVzZm8QOLaxEuGpYAoLqzKup9c3MMdltuWeFdkMVzHIr5DldxzoEAoJSA1bq4qqz/GVV%2BfVRF7VnX0%2BZ%2Bz7ntUTILULeG9EUboIJvw%2Bm4Pz1ifJ/WpAFnzxhcc%2BpMLnngghdVB0vWyGrbEao2Jv23vpNKa02nYW1mnNebnuYELcWsQd2p0PaXSDytDaKnvclZ9/anap2/dVQDodkIwOY6wG4OvAkO86gIsOK6wWCOTAW6O6e6poaOJeGOEgWOoqleV6NeBOxgDONgAObOlONQ5a6wqiRO1gAGzWQGIGhB8u6QXO7gzGcGfOSGHGouQuGGTBguOG2uFGHO0uiucu/BCubGyuAuEwJGcuoh/O9GvGXGJychhuLe0KJuG%2B9KGeWeFwS%2B8Iq%2BNucm9uY%2BwWKmmAambufGnuIA7y8IoIoIcQ3yIeZmNhLILmvmKhEe8KiKTudykgcQumfyLIZmzykgnyXAryZgPmQKoIyhzWnAjuRhTebKrhMREe0eCwM6qQzgkgQAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left_first.test.hpp)
