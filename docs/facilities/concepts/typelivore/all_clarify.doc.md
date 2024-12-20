<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllClarify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-clarify">To Index</a></p>

## Description

`Typelivore::AllClarify` accepts a callable type predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&Pred{}(Vs))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0{}(***))` and `(...&&Pred_0{}(***)) && (...&&Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0{}(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0{}(Args)) && (...&&Pred_1{}(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCXhlGp%2BdXNyYAzAAixywyFoBAAnilMBATAErAE/hAmF4iAA6VErEwAdgs5wImwYxwIxC8mF%2BVgxf3RPysz0eTwORw%2BF0uXFuRwez1e4WAjKuLN%2BAKBIPBkOhsPhiJRaMx2MwuOI%2BMJxNJmIpyppz3ph2OVC8%2BLu7KeBEwLBSBiNvzcEtQqORT2IwAUv2wtPOAEcvHhzgpjhAbeYAGwBs5MjTSlUQO0Olbo55oBizTCqFLEY4xVCebW6iDorE4vHasRKZXk2m0o0ms0kn6WpHW1GRx0/Z3PN0er0%2Bv1mQNd4NfMPkiP2hTR44BgMd1FjnufZn9%2BEN6O0uMJpMptMZnUMbPSvPyglEqtkv6ljV3Y4AFUws1ZhwNu12x2wxGIJFpsyYjmQlyYCiULWouoWlwTrZpSFgcGstCcAEvB%2BBwWikKgnBuNY1jHAoGxbJgo5mD8PCkAQmgQWsADWIABP6yKJP6UgBBi/qSAAnD89G4fonCSLwLASBoGikHBCFIRwvAKCAfGEfBEGkHAsAwIgIAbAQKRIuQlBoCadDxJErA7Ko1EALQMccwDIMgxxSMiZi8BchAkHg6B6PwggiGI7BSDIgiKCo6iSaQuhcKQADuxBMCknA8JB0GwURiGcAA8kiykEMcqBUMcen%2BoZkjGaZ5mSJZPoeBp9ApuYeErLwElaGsEBIOpKSaWQFAQPVjUgMAUhmHwdBGsQokQDEMUxOEzSguFvDDcwxCgnFMTaHUEn4epbCCHFDC0GNvlYDEXjAJatC0KJ3C8FgLCGMA4hbZ6C14AAbleMWJnUSI7Ph4RGlBvm0HgMQhdNHhYDFhJ4Nxx2kPdxBpkofzGud31GERaxUAYDoAGp4JggVxRCcH4U5wiiOI7n415agxf5%2BjnSgqGWPoP2iZAayoCkvRHfpszoPypiWNYZiCRDxD2Q9jNdD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BAFyu9EMCvLKLN0CP0kzS3kAW1PUBtzNrIxVOMAxq3o74tFbSxVGsGGbNsEiRRwMH8TFQnpQZRkmWZFlmD6uC2aVuFcBVBGI2sCCYEwWAJNmpBkZIPzIsxGKSBokhmJI/q8RRjHsRwnGkNxPxmMiPz%2BhiiQ/IkAQBFwLGMckAm8EJIlifHkk1XJtUKYlKnNa1JXaWwnAZVlxzAud5mMciXDIghNlEILDkBfjLlE9IJNKGTvm6F1wWheN3u%2Bz3sUcAlSlIilaXz0ZS/vFwq/rzcEBFQ1JUcK1zjlVKSo8p7xFUi1VAxVRgfw6oxLgfEaAgniP1QavlJqjXGqQLB01ZrzQcDg5ajACBrQ2jFbau19qHRwadOGOwEL4HOPUe6R1N6qGekaHB71ugxW%2Br9UaANGGVUFqDfCEMoaYBhmdIw8NQBDz4CjBQ6NMbY0YDg/ehM3JH1kKTHyCFz6UwRtzKwtMBEM3TszVmnB2YEE5v8UxvN%2BbxB3sLdOZtegSylrkdWwRJbO0VhrdIKtsjGz8ZrLIgTdaeIaHMe2ptuj6z6JbeW1sHbxPCRkgY0TXbrA9m5G%2B0VfIBzftleBK814bwjvgbeQDY6VQTqQJOKdRjpzIkgvin0q41wCMiJiARGJmCGV2RIHcGJ%2BxKZwfu4lEbSRHkgRSSUoEQOIDPHYzQWBGRYAoW6Zlbpf2RJWWY1lal2V3h5AmrkJC6M8ifAxOgQA/CCiFMKx0imTMEvFceyVUrpW2bs/ZhzjnJT/jAgB8QgE/BAXM8B4LGorPhSVEAeyUgpEuAcxilwQWXFUBMlBvV0FDRGtNHBeCZpzQWsQmBK0yHrU2kwzAO09piFoWDehciRGkGYTdNhj1OHIBejwwQfCvo/T%2BqCYRQMxE4MkekaRsM5FcjmcjJgaMMZYxxpo2QB8dGXP0eTJ5xjjA0xsBY%2BATMWZZCOrsDm1MeaWD5r3AWQtLFuySebPwEBXAJP8egXJSsQm9F9ZEkoaSXYOw9b0Q2rQsmJLFhbHJ4agm2yNr47JTtk3LDdphT2scK6339pwf52Udl7OOJio5H4rygsjnUsqDTB7VUTsnVOlBvY9KeXXcZuEzB9uqBof0gzPm92mbYAeoDowZxAFnNeLcAiFx%2BAEQduF6IVx%2BMUr5wkm3EQrlZEd99GlDzWBDDIzhJBAA%3D%3D)

By turning `(...&&Pred_0{}(***))` and `(...&&Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AllClarify = (...&&Predicate{}(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4CABPFKMViYO7KYiYfCiMGkO5MLxEAB0xIAas08EwYvQFDDsCC0AxtikCHcrrRaG4DMQ8FR4XcYQARO4QYmE8wANgl6MxeGxmBMAHYrAqBRAydzKdSVisYVZriC/gDzgbjncACqYWYKL7G35Gk5Ak33aXoAD6GhthyBXgyRjRGLdHsFdywyFoCKREBMASsAVV%2BKJxJ1SoxBE2DDuBGIXnl0OVAp1eZBTsO/sxrq4nv23t9wDLbsrwdD4cRmCjMej8YJqFFyYsqfTmezufzhb1wLt9yoXgz3xBYIhH1zbgTPeJV2IwBp0Lp1wxAEcvHgMda2RyuTz4TC3C73biN1vRbT6QJZphVCliHcYqhPHdpwwEB9gOxAZlQYhKLqioCsW1wLi8S7XquooPtuu4bpgh7HparLspy5K8tet4aPem4KE%2BO78mYkrUbh54EVesK3lwpGPsSz7XAyb4fl%2BP5/gBQGKv2mBpqBQ45lBKqwTcpoWrMVZArMHyyq6TAKEoLTUDO15cLSQFjhway0JwAS8H4HBaKQqCcG41jWHcCgbFsqLmNCPCkAQmiGWsADWIABOKhKJOKUgBAq4qSAAnNC4VmNC%2BicJIvAsBIGgkeZlnWRwvAKCAJGeRZhmkHAsAwIgIAbAQKQEuQlBoM8dDxJEKKcKowUALQRXcwDIMgdxSISZi8DKRDcugej8IIIhiOwUgyIIigqOohWkLoLEAO7EEwKScDwRkmWZXlWZwADyBLVSyqBUHcbXip1kjdb1/WSINwoeA19Bfq5XArLwBVaGsEBIPVKSNWQFAQCDYMgMAUhmHwdBgsQuUQDER0xOEzTwrtvAY8wxDwidMTaHUBXufVbwECdDC0NjK1YDEXjACu7K5dwvBYCwhjAOI9PYfUABulpHe%2BdQEjs7nhGCxkrbQeAxFtBMeFgR1ZngKXs6QQvED%2BSgCuC3Ny0YXlrFQBhbiSeCYOtJ1IuZ7mTcIojiHNjuLWoR1rfo3MoHZlj6PLuWQGsqDMlkbPtbM6CCqYljWGYmXa2NwvB10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4LEl70QyF6MLG1PUAj9JMOd5PX3Skw0cw1yMCT13M5d6EpLQ90sfdrI5mzbBI%2B0cKZpAZbwWU3R1XU9X1A1mMKuCECQVFub9Hkm2sCCYEwWAJEBpB%2BZI0KEtFCqSBokhmJI4ppQFkUJRwSWkCl0JmEJNCcUCpEjQkSAEAIXAYqRWSIvY62VbB5SPoVQGZUgYVXOjVCGUNPrNTYK1VeD0wzc36pFQkXBCSWRGiQPA40WKO2mi7aQbslAexWroeGm1to41nvPeBWUzpVQJHcK6K87pdRIX6Lg5DKEeggO9UGn195mEPv9IqGDcHxFqpDVAH1RhSNhpFLgJEaDhniCjNGK08ZYxxqQGxBMiYkwcHYimjAqY0zppZBmTMWa0DZu5TmhsdjeP5o4IWbNqGqDFmCOxUtuhHTlgrLGysQl/W5Brdy2tdaYH1lzIwRtQCoL4ObBQltra20YHYxhztZosNkO7ZallOHe2NrHKw/sklByvqHXoEco4xz9hYBOS8k50JTlfBuvRM7Z1yBXYIWdR5F0rukUu2RW7zKrlkJZdc06dybgPDZQ8O6Nz6N3Auvch6HLmVcgYOzx7rCnrNPhh0VrL1uvdO4hiyEUKodvfAo194/T%2BsfUgp9z6jCvn5ExJEZa/3/gEQkUUAiRTMKi6iiRoERQXkdLKOVkHqLQfADBlULo6K0cQfBOxmgsC6iwBQAs%2BoCxkYSSEloCDDQBbQ%2Bh80nYzQkPUhabCmk6BAPFbhO12YvJxW806WDLrXVUHShlTKWVsvkgovRSj4j72hGok2xVgZarBuS41n0QCMpSCkV0zLIqunVQQV0SqWGIwsZQKxlkHF03cl6pxpNXF6MptTWmR0fHMzEP4uxQSClpNIPgDEgthYrVFsgcWcTBAJNlvLRW8JUmqwyXY7J6RckGwKeEIpAMSlMAtlbG2dtqmyCYXU3ljTPZitacYIZAcYjdJDmHV8nBdhR19nHSwIyrJjKwL2vZpyZmDxYvnMolyVlFCyPO1Iqzq4XLHsc9OByBjrqmV3O527lnjAPUc/uJ6l07p%2Bo85yM9v78NxZwG6yrGV3FtaypcGqd6Au%2Bvq1BJ8z4X0oLPeFYrAFYrimYWDXBEgaHFCimVmVOD4vyqCm%2Bd9oEQJftCAIiG4rhW/tCV5qHEGEtnkNFDS80MoIBmsbWGRnCSCAA%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/all_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_clarify.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/all_clarify/implementation.hpp)
