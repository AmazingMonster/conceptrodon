<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-left">To Index</a></p>

## Description

`Mouldivore::FoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Operation
-> Initiator
-> E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Operation&lt;
   Operation&lt;
        &vellip;
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
FoldLeft ::   template<typename...> class...
           -> typename...
           -> typename...
           -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
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
template<typename A, typename B>
struct SubtractHelper
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldLeft<Subtract>
::Mold<std::integral_constant<int, 1>>
::Mold<Args...>;

using Result = Metafunction
<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

static_assert(Result::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldLeft
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements>
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Initiator, Element>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<
                Operation<
                    Initiator, First
                >, Second
                >;
        };

        // Recursive Case:

        // Fold twice, handle the first two parameters,
        // and recurse using the rest.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            = ProtoMold
            <
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Detail<Others...>::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAcwQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHASYLKkG2yb%2Bbtu7%2B5iHxwCeqYysmAB0j4fYANTIBgoKLwDyN8RM9QYzxMGgAgmNiF4HC8AGKedChTBUAgg0EmADsVjBLxxLxOewB5yOBGutzYLwAkgwsgCSMDsbiIVCCC9lMRUEQALLw1G4l4YrGgvl8/FnC4km7MNiPe7YehsQQKelC4U4pnQgAimCadH5mIxGsOgt5qpeAHozS8LEwlC83Db2KiTaqLbD4S8BBt7s7haLCeLSVLMC85TtGCj/NgfXz1SytTraBdQwqI1GGaqBdHTV5MkY8aT%2Bf4NT8/gDshcqTSiGQQ/Lw8D/ILTXrDY2nenha64bR0HiAO54L1ZnF%2Bg7EwN3WF4YhjUj5yWToSYNAMdDK5uxl7xph0C4w6ezl5LldryPDvVN5u4nMRYDz84d5uHYs434JMsCC7n5tv/6Ar%2BPleqqVo4tI1vuM4ooBQHPHOx4CGu0FXg2l4ZuirbGkhroAErLmsmQAG7BvaSggO2Koupa3a9gQA4bHOCCGOg9B4ggwY0JB/aoC8qTNHc2wzqQ56ukxLzEHhM7BjeeYEGxYmYGM3pIaORJXAu5IQYeEpksG8GrnO2lBjK3yyQkSpnkhm7bruRyaQQcHLghc4mWxM4yuupqZkhfLSXe2nfriz6suyXI8t5gVHAFqq/h%2BQKReF0Wlv%2B8UUUBpogXgYFznZUXCrBR6OauuV8h5MGRiAIAqVu2o7omRwuWZ7nlZVpJGueBptWC54qQG6kPI8oLAOJYaKqVwq%2BS83I9oWxbWXVbiDcNKYKE12AVf5bYdh1m1oh2PXjn1MqLZgI0EOZaapRNU29kFbIcqg10XMdp0rU8Z47dtmGgmaABUf3/QDgNmqiv3/S8AAqClnS8APA2CoOA4jf1w7taJmP4ETvF4WCFm4XiOLQhCXMqqL7WpOkvKCBkTuSVgWeCBCQtCQheLEjNMA4AAStR/E6%2BodhN2kzS8YzoBVETbENYgAPorjMgg%2BhcEtzqCFUEWIXjBgAtFaasa0SUYfehnWo2Thl3EdxDAOdqITSzbP/NCQX2%2BzXM8wkT1W693rNRtX1mzT/X3KCXvKldNVUF4DAONk/JdUWbo9oiyIXC7jupqiFWPUcovi4ImBS7QssCPLEZuMrLxcA2F1ZzyRwh9bq0m7buZ3rhCheLQLJBZyEdRzHn7x24Pq5yAEsF/8Rdy00CtHBX/iwSPBBi2P%2BeF8XDCl0rghzpIi8dqP4/r9Phhl/PJPvV9MyOMg0s2koLQQO3ncEHr3jBs%2BQVawAnIsRocMsWgnAACsvA/AcC0KQVAnBh6WGsCLVY6wP7ox4KQV%2BECAHLAANYgGAZIe4GhJBcHRP4DQwCNBmECIEMwSQkj6E4JIXgLAJAaA0KQcBkDoEcF4AoEAbD0FaGWHAWAMBEAgFWAQVI%2BNyCUDQLsOgCQoh3E4KoFIWtAiSBeMAZAyBK74LMLwTA%2BBqx4DFlwGQggRBiHYFICx8glBqE0DoPQfZ/ipE4DwQBICwFOKgZwb4%2BMpEslQFQF4qjAjqM0do3RUh7hmBeBADw8j6DEH5CgxYvABEANIBAJAcjUgKLIBQCA%2BTCkgGAFIMwfA6ACV4RAWIvjYgRGaJcDxvAmnMGIJcb4sRtDLnQaguRKZvgMFoK0jBpAsCxC8MAe0tBaC8O4LwLALBDDAHEBM/A4kY5EUWZAzAqg8LbDaeQfOQCJmE1iP8LpHgsC%2BMZngZhSzSBEWILEDImAtSrKMITIwTjlhUAMNbAAangTAfY3zgNQfwSxohxC2JhfYlQ6gJm6HMQYP5pg4GWH0HgWIvDIDLFQKkQEiytai2fFiqwlgzCcNecQUxCl4DLDsP07ILhVyTD8OYsIERBgVGGOY9ImRARcr0MK4oDA5hDESOY1lA8GC9AmJ4doeh5WAiVf0Pl8xBW2HGK0FV%2BQ5X6ulQK2VLLEEbAkF4jgoD2G%2BK4WEtRGitE6L0XEhJuBCAkDSf4LgGS0H/OWGxJgWBEgQGwSASQ/h7jf38OiSQhCzCSECKw4BgRv70I4Iw0gzC/X3ECFwQISRv5JCLXgrgwC43BA4bwLhPC%2BGBowUI0RuTxGBOkcU0pKSlFsE4M0FgBF0RayYG8DFd4uDf3uFwAhhjjEkFMXoRFVj4XSERYoZFvjdBVNcUwdxSybV2trX4jgATJH4w9KEgdQ6R1jrWZXKdM6NAJKSQUlJvqzABqyUIvJqBkkJBkSUv9b7hjXuHe8NZk6uBsJoF3MylAGkTI6S0k5yGuk9L6Q4E5QzwwjLGb4qZMy5kLJOSstZGzIFbLZbs3xByjmbFQePc5kDLnXMuLczYkCHlPNQa895SgvnkdvP8vgQKFCgvBZCk5y64U2LXbIDdjjUUgCqeOlA1hrC4vxcyqBJLshkopUWKl1haV1vpYyglEauhsucBAVwYqeWrlNQsIVRRRWGu5aQCVgJnO6vVT0fVDnrMKs1b52Veq%2BhBZmC0ML1qVhrCtf6rNR6HWcBeGB29EG8yTunQQz187UnmD9V%2BoNpAQ1hsoDanNeap2EPRFW9EJDJDJo0eY499bbCNu/Tk1tSAJFBMA92xRyiOADpdSwBQBFdEERy2cMYc7vUMrMXYldcm7GKZRZA3Q/hSC7v3Z45LPiJlcLPUEy96XiAsHG5N6bs3CRjBfcBwpvr/AlebTk39/6imyKeykkAU3UipGljN7%2B0s5sEDvpdjR1S4MzgQ405pXTUOI%2B6b0/p2G/3DNGeMyjmBpmzLECR55ZGfmceWdOajTKJl0eQPjBjvAmO%2BNYy0jj9yGU8d4Hxj5gmfnCfe4CpgIKwUQslNJ2Qq2JDycEBtrdAR9BrPU9imwlzLNEr0yXTgZpc7GZpXShIS2mWEuC4CDl7gPN6F5WUGV4q3PZCC957IsW5W1Bs4qwL5vnfdAaCa7V1vjWRY9xFmLvuzVxYUJamxh6jucLS2NzRE2psvBB/ccH%2BXFu%2Bv9Zk0r5XhhWfOdVlTU7/D%2BGAeQohrDi/omLfa47nAG38NKzgyQwDY3AKSJQ7%2Bkhv4kPjVwHb5z/DR7rXXptgibUGJrzH7ho/MEvLMuyyQQA)

## Links

- [source code](../../../../conceptrodon/mouldivore/fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/fold_left.test.hpp)
