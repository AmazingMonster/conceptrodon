<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRightLast`

## Description

`Pagelivore::FoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Operation
-> V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>, Initiator
-> Operation&lt;V<sub>0</sub>, ...
   Operation&lt;V<sub>n-1</sub>,
   Operation&lt;V<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
   ...&gt;::value</code></pre>

## Type Signature

```Haskell
FoldRightLast ::   template<auto...> class...
                       -> auto...
                       -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRightLast
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
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

template<auto...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Page<Args...>;

static_assert(Metafunction<1, 3, 4, 3>::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRightLast
{
    template<auto...Variables >
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Variable, auto Initiator>
    struct ProtoPage<Variable, Initiator>
    {
        static constexpr auto value
        { Operation<Variable, Initiator>::value };
    };

    // Fold twice.
    template<auto First, auto Second, auto Initiator>
    struct ProtoPage<First, Second, Initiator>
    {
        static constexpr auto value 
        { 
            Operation<First,
            Operation<Second,
                Initiator
            >::value
            >::value
        };
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {
        static constexpr auto value
        {
            Operation<First,
            Operation<Second,
                FoldRightLast<Operation>
                ::template ProtoPage<Others...>
                ::value
            >::value
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAA7BqkAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG7bu/uYR25MXkQAdPdH2ADUyAYKCk8A8ilxTPWPJg0AEExsQvA4ngAxTzoABKeGACH6TDGgKBJgSVmBTxxT1Oez%2BF2O1zu9wAas08ExovQPgDsbjQeCCE9lMRUERlExgJgnhirAkACJHLHohk4gD0EqeFhRvKuShAaLRuKeUqhMKeAg2txVuPx50uJNQTwpxCpNMwpCexqeAEkGJk/iR6UDVUyIWyOaguTzLmaLfRrQ6nURiK7Vfy9aqcTNHMgXgIxphVCliDabiaAG5iLwXcUx/lfH7EP5Zf2U6lB%2B2OxzO8OHbAgEA57y8jHCw6iyNCkXKgvq6G0dB4gDueB10bxOwJB2JmaheGIY2ttqEmDQDHQq4XIbrYYjjIIYM97M53KJbkhS5XT3Xm%2B3NdDLsbU6jBfdTXjiYYydT6dtVs8z5D9cSLKcY1xb5fn%2BY5r2XAhSAgyDixg8tjnvARt2QlDcT3KkD1AyDHmbID8zdXCwMbUjc3I3COz7AsGK7fsKMlaVYQ3NYMizeU5SVYEp3VAB1c1ti1G48QQXk3hZAhRxNfhhwUa0EEMdB6Ck3kaAQscTRSZpWEwbZlyQgdpXUp5iC45deS8DIjC0qzMDGPETVQaImjCJywmfYhdQLA1CSNBd4NvNcNywndSVuT4CGk5dD1jY9mVZM8fQvS4wsQu9Iq3a04oShR7l1V8mMxHCnjjCcfz/NMMyIJ4yMq982Mo6DS1gq8b0QyrVQ6ssBEuTD8r6lChzhBEkWCFECEuAbYOwMbIObILxK9c8/WOQq4mKh4yrayjcRottlr5aiW1os6SMu06iL5XsWPKztRSnNbL2NEqgWAaydkYAgFCSp57LCYBWQvc7BTS71fUvb7frYQQ9tKpanvRR7XuBCUACpcbx/GCYlNEcbxp4ABUXIBp58aJrGCfpmnWPekLGqBaKTSsA6PRZIQvE80sHGVCqC2qhNNzqgCF2a8qLCeN0AFoZQel6hZVwTgWZ%2BcYqBYhgEBg6QccgBZYymCoLwGAcLIQPRQ4oYm%2BFEWRVEML548mEFg7m1hy4db1kqATRtFRYAfRRJQWggE2mnNy2uq4a1DmtaQnkOG6yMho4oflrhFhFDhlloTh/F4PwOC0UhUE4NxrGsKrVnWdszEOHhSAITQC%2BWABrfJbg0SQuASQ4NH8DQzAANnHswAA5p/0ThJF4FgJA0ZIy4rquOF4BQQGSdvy4L0g4FgGBEBAVYCBSG5yEoNBdjoOIIiMzhVGn8f5fHyQnmAZAEykW4zC8EwPgMMeB0B6H4IIEQYh2BSBkIIRQKh1AH1ILoBOo5SwpE4DwQuxdS4d0rpwT4Nwr4slQFQJ4r936f2/r/J4/8zBPAgB4e%2B9B0zmBbosXg%2B8tDLAgEgO%2BKQH5kAoBAQRwiQDACkGYPgdATI7wgNEAh0QwjNAAJ7YN4Co5gxA1GfGiNoDc%2B9W530RgQT4DBaAaJQVgaIXhgBXFoLQHe3BeBYBYIYYA4gbFLiMXgXiLiK4pi4tsTR5BBC1AIbQPA0RSy6I8FgAhx48DL1caQXixBojpEwIKHYnjolGA7ssKgBg9ZkjwJgUc0Ey6t0gcIUQ4g4F1MQWoAhaD9CeJQLXSw%2BgYk70gMsVAKR6guPlmMdAWdTCWGsGYDeGTzRYH6RAZYdg/HOAgK4SYfgE4hDCIMCowwE6FEyAILZehjn1DmEMeICdVlWwEL0CYnh2h6DufUR5/Q9nzEObYcYrRnl5FuX8q5BybkrIbhsCQuCOAl1IOvXgm9KFvw/l/H%2Bf9JAAKYbgQgJA%2BTN1ztwopyxpJMCwPEZZpAe6SEOLcAAnIcBIkh%2B5mEkOPVe/hx60vnhwRepBl4t1uOPLg49p60unsKwIXB/D0vHnCghm9t67zbkUo%2Bp9%2BHnxIdfUR4i2FPzYJwZoLAswJHlkwF4BhHJcFpbcLgfcgEgJIGAiBshoGNOkM0pQrSUG6BkRgpgWDXHQthfCwhHBiGX0kuQm0xAjUmrNa8Tx9DrW2o0EwlhQi2F4sOGYLhyqD58IEagVhcQb5iKLRm4YhrjXywTUYK1XBkg0FoPIygSiUHaPUWEjtuj9GGIcGE0x/0LFWIIbY%2BxjjnFhPcfkzYFd8DWStgEghwTkA3E2K3MI2wi4oOibE9RCTZ3cPNKk1uGSslKFyR4owBTQD5r4KUhQ5TKnVLCXU11sD3WyBacgiuPqOmFKmVYHpu6lmDOGVkUZ4zJndIsLMhF8ywEuXgCs2oay/AbK3GcnZW4QULCOekE52QAXbNSARy5XzrmvNQ/chofysNdDQx83DPyZhPNyCR1jnyyiUdzisNYkLePbuDfKzg0bY2mvNYmq1Nq%2B5Yodew/FuaeGd1ICSsllBoW8v5da/uCRpUJCHpIFln8E4hoVbYJVym%2BFqqQBfUhpadWP2fhwQ1NCWAKCzAmLM0nzhjHtTihZzqoENI/fA%2BQnqf06BAEnP1AacHcuEygze4bSFagoa5r%2B7nPNNR84SVyzDy3CKzYcJTKr1WOZEbfQrbCWzIBSCkEO3naUh18wQMOMbP6yObbtVtyjVG6K7f1vRBijEDqLWY4d1i52YDsQ4sQk60nTuvYe0g86/FLpQSutdYTN2RJ3TEuJaiD1JOPWEs92TL35NBiqkp3JH0VKqT8GpvA30hYkJ%2BhBEW2nRf/cYGDvToigcruBpMnAJTjK6dMywcHK4IcWchhjNGXCYeI3oXZ3HQXnLI1kejFysjMZuYj95dHUe3Oo8T2YFHMdAr6PRzjBOoV8cbozoT%2BCkuiYy08LLXncvbHy9isMWaCV5t4cSzApLhgUu3VpkAZhrWHEOP4UeA9V4K4SCKuV7Ot4Wb3kSylIBJD%2BDpf4aeE9aWSFpUPBlXAk7bsOGzjenBCX5uhYAzXjvtdWeWBkjIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right_last.test.hpp)
