<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Conceptrodon

A C++20 metaprogramming library focusing on metafunction composition.

## Introduction

The goal of this library is to make metafunction composition simple and natural.

Both [**boost::mp11**](https://www.boost.org/doc/libs/master/libs/mp11/doc/html/mp11.html) and [**kvasir::mpl**](https://github.com/kvasir-io/mpl) contain a function called 'compose.'
It takes a variadic pack of metafunctions and uses the result from the left function to invoke the right one.
Namely, `mp_compose<F1, F2, …​, Fn>::fn<T…​>` is `Fn<…​F2<F1<T…​>>…​>`. However, since we still don't have a universal template parameter representation, signatures of `F1...` must be specified.
Regarding **boost::mp11** and **kvasir::mpl**,  `F1...` are metafunctions that only accept type arguments, which means many functions in both libraries are not composable.

Conceptrodon expands the idea of *quoted metafunctions* from **boost::mp11**.
It utilizes dedicated member templates to take arguments of different signatures,
creating better candidates for composition and making higher-order functions possible.

## Implementation

The library mainly uses four types of member templates:

<table>
    <thead>
        <tr>
            <th>Member</th>
            <th>Template Head</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><code>Mold</code></td>
            <td><code>template&lt;typename...&gt;</code></td>
        </tr>
        <tr>
            <td><code>Page</code></td>
            <td><code>template&lt;auto...&gt;</code></td>
        </tr>
        <tr>
            <td><code>Road</code></td>
            <td><code>template&lt;template&lt;typename...&gt;&nbsp;class...&gt;</code></td>
        </tr>
        <tr>
            <td><code>Rail</code></td>
            <td><code>template&lt;template&lt;auto...&gt;&nbsp;class...&gt;</code></td>
        </tr>
    </tbody>
</table>

These templates are deployed inside a metafunction to take corresponding arguments.
For example, assuming we want to create a metafunction called `Fun`, which will accept arguments `int`, `std::tuple`, `0`, and `std::index_sequence` in order:

1. The function itself can be templatized.
we let `Fun` take types and pass `int` to `Fun`:
`Fun<int>`;
2. `std::tuple` is corresponding to `Road`,
we add member `Road` and pass it `std::tuple`:
`Fun<int>::Road<std::tuple>`;
3. `0` is corresponding to `Page`,
we add member `Page` and pass it `0`:
`Fun<int>::Road<std::tuple>::Page<0>`;
4. Finally, since `std::index_sequence` is corresponding to `Rail`,
we add member `Rail` and pass it `std::index_sequence`:
`Fun<int>::Road<std::tuple>::Page<0>::Rail<std::index_sequence>`;

We finalize the structural design of `Fun` as follows:

```C++
template<typename...Elements>
struct Fun
{
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        /* For later demonstrations */
        static constexpr bool value {true}; 

        template<auto...Variables>
        struct ProtoPage
        {
            template<template<auto...> class...Sequences>
            struct ProtoRail
            {
                /* For later demonstrations */
                static constexpr bool value {true}; 
            };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<auto...Variables>
        using Page = ProtoPage<Variables...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};
```

For more information, check out [EXEMPLAR](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIAHFykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BgXaYDlmNzQQlkTFxickKTS1teZ0TA2FD5SNVXACUtqhexMjsHAD0uwDUHikAnsR4wAgEB2YaZpIHAGKMwAcAsqhUhiYaAIL7ByEygAIgANAC0oW2DCU4IAklhBHgaCMDr8UkxkAhMOCzAA6DQ/X5EgEAFQQeAUB3QqGQPkY1wA7nRaAdMKoUgYwgcCNiDmwsYY8MgqYZ0NTMBlgAwJchKVkqZ8eXzaHhosRmic8USdWZ/MiGFgqEcAPIRNzYZSkgBKJuBZoA%2BthQdg3spgr9rQ6ABK6/xG%2Bam82Wm12x3O13uz0%2BnV/AHAzA0cLUnwsE4HTmYzAITxYYg81AAa0YVP4%2BeImCY6CY0TohC1foDydJkY9LYdyk9vze2BbXrcvxbAHETdaAJoHJheIiNxOB0lj5TYA5hAizpOYA4ANV%2BwTky4IxC8mHXgbcZpbEVJQlPybhbuCruwV8HcLNK8Et83yhNQiEcIsYIxwdX4HRbB9B2wWN/kOclNzQCsVywJgDiVXlKQOVV1U1FcqSIalKSUBxlU3FJiFpSVFWNZpgHpQQMyYBQMiMUgSUOFgmELMJXilZgCE2SVUONNgmioLwGB6AQqTIzB8AcGt6EnQ0DliAgCDiA4FC8QhZIOMsDjQFg0gyeoGG1ONYL5GhiHGSc1MwIymUYgsJU5VB0zYRZ82QAwmJ5BzM3UvDUEnZBthSa4aLoggqIIqgqDiBkDKYdTgBIPBJXM4k/mYNgFAxbYjgEcLDwwAQDhMAB2KwctYSUCs3X5ojFARZKETxpyyHVqugn8/wAoCQLA1tIKJcYj2I7BVACgxiG6mrfgOJb/KMgx1JMfw3AIE4UkYOq8QO7B6DYQQFA2qC/mWzTDy8YiPlocUqqsSrgQ2hboIBAB1ClFN5Tc8GQ3Dro1C4rjLRlmnQUgSJXVaHIZFKsgOYBMBigyBAANw69TxWcsSJNMqlYkMzcWBIeDUDh1QsrJPkOO5QjjwOZleWVDCmBSMjUExBAgd5FKJSTbjJ35ByKmZwheb%2BzS6oOXLN2cwgqS04hyPE/AjAM3yqQwsta3QREPyOaxrFYiyM3SDJolodN0CZ/Dpfl9HaFVDJypZqW%2BTCbRuhxrXGKpeWacOR4SDZVRWE5dhoKu9TVpSk9NqnIgDrxLdmjwBTJXOokrvG27rmUJgUdz5anrYq6lrjwLE7cZPUFTnPzcr/PiKLlGKp6l6lt2AAqA5sFVkgQHeMWNLADh28wCeDgQZzpYUWWncVtGfID/2jAgTyKgdeWHU%2BB016YlYDl73ZS6WqrXv8d7zd%2BJifGFxkFcQ5AK0RzWUPxySZX565D0MAoMsLA8J8gxhnLOQk7Ii2AHgDGjALYmSRtyFCsD4EyiUAAR2PBJTA0MK6EAnjrIyls1S/RCmELGxYYbf1MipdME9HjiR/htNwpINQwmAYjAQ50QAjynqwuEhp2S8P4cXWuvxiC0ROjFRu/hsB4gnh9Q4JpkwKGxsg4Kk4DZKQ/OpYgbB8AJ2BgXASKlUbPwQdLI%2BoplJKwzORa2DlEbIFFl5LKF8Vo11YdXNatdtq7SDgdc6/smKp0%2Bs0bMGwlBnXkZ41u1xrTc3QJ48ul1K5LQSYCXyvNlp9zRDo1ccRDGZ3UiY4iZ9PFXTSYtDJldfEJx8TNRpm0Al7TYHI5cNjOlVLqVkpJVYKrpLqWXHqwyRktyaI4VxaAYTqQ5PmaIqBPAHHAd4TcT0bonhem9XpGSr67PGdUnZN8Y51L2V4vxTT47rSTtOBuwT5GhIUKnRotJCzkUprEi6tSMn9KYHQIZvzK41ImctcYLj0ZzPZGRFSyzWRrKZpso82zr4LRGQc05fwK7Wm6GIVk0taFI2fszQwft8Jv0rGUysxBVRxDxEC2mm5%2BAu1QMyTWlCiybiwTgwqGFjJW3EAcRhzDTKsPYYArhYr5F8IOAIzaQisCqFEdkxiSAxEl02pI6RDIXmPIUUo7F4zMW3xggcb0bLMDwLIGzKklKE62NQH9fMXMnEsAZXCY0JKwjYnOIk5JLkULhEZHLOqIAzlV2abcraUba7106c815RBkAfOWSApuwL/l0BHikLw1thQHAGSkzaGbjnPTRcowEYRCqO1lmhPkKs1aGmFjYgyc8jCCXwhPa0ALaCkENWa6WRSDGyVKdym6DgzF/00psJt6AqTduSTPDC4lwjbCYpqM2ZqTio2ZuOlks8mDwJcmlZUatLjCo4EIHJM98KYnXaA/6DBfU6XFIuqsE8R4Ruui4h0Ac4gEAgD2ugrCVXXrVbKotoGZUgERZgFYhzspmqENWzc77i1uBVcB2gM856PplmwUNhH558mDTOoe6sW3a2hoYPRxTR3GISWYjC4RZKyWDgcT68FDAMCdaFB9MMfVxFfZe7DM8qDkRYAPaa8d4gj2w1ugEzlu29ug9gSDvaZ7MhdgcCsCV8wOz5LMhJYcwjjErOgDxzcIXTL/UxADQHVMlpg4WpzmGYNwYQzfA4%2BTB7kXzJUo1Zq4JKHMXPDGTgbKTkQrx64Mk5JNCcfQ2eoNwT0HgayIlUkOPKEccLVcIUooyIUMuhg4R8xMYrDrQO3RKI4ViGWTcVq4jplQLtDUploaMgpFiIGhlOTCgTrjOx4R4rCgyoIKzwWVRqg1MQdMENSx4BskyP16kZReGYq8dCVIRI5ksxXDwDAsbeD9hxLE8xziCWfohTbul8IVjJsesOVZxTDpKYxid/EqvM2xDKNddX5sMort9Og/0nJUhpFnaG0tXu6X6/QVQ9ZSWQ6nEiT%2Byk2vGXuyFaWaUxBQI4lxTWIkmBZZlP1wodCMhw2B3fKg%2BjrpeHQCcYWSz0gED4UZLgXAlLikLOAjIcnVrQzhNotrfsUJEQELjTm5EeaKcON14UvM7uilVPPWNpZTOCDiF8QqYpnmXIdXpUzcMZHcLMtBE11udk7KC/LfKWYiq4IiuRGkMoamO4agUiXbUNE8LGUhgEbhsQptQtOGhnhaBsuFuySO4heq/n/IBYCoFwJRhbGNL70nmlzWxUH2OsafE7XaZgVOR14anVLeCnPuWnWoHuo9Y1he%2Bk5/AwoBAFzQVguN9GtpQTtRxKOW3iahdyJECb0C3vnd0Uz9r2P1VneLkYtb/P%2BpxfWml8HzX9fec68T8b7mafe%2By0r73zZgtxn5mwvZwisQSLqpbJtyP9fL/gUz/fyD/dOn9ebiHQ/ArETImOTHTmakIvoh9mUpVoJJEnLLVhuvNuYgQJYjKAYDulFh7DDIvIRkHIyocBas/NatDMxDWqRnWtRDKGIJnHhLGszAIBPNcLEB%2BD7A4LpAVjDK2oQLpomHEMFIrnuslDKBWHdjDE7GZgDP/g2gCuKDYuGkFqfg0v3tvvtAdL8MABWFXjFLvvPptsLFPhtMCEvuqkod%2BIfk3qwuoZocVj0lih/ucicnPvso4d%2BkXjcv4ioR0moRoZgFod8hcnoZrAYf4EYR3iYXQfXpPrmJYT4X4bYU4Z3BWsauMqYSXoEqoXiFYb4cVjoYEa8MEUYZEUfg9DEdYbqvEZWuSBhGwIAmIUehcJbhLOhL/EZtrEIeYilgbAghIVgIJrrsQH/gIfao4J/AcOJMiCQFJqIDpiZMymHBSJcGls1plqKgqPIcCvElMsKHZkoC0BABYc5upiAAce5kcScaIp5ohhXIQc1jagKmQrbPbCFBLngCwHgAAF6NGzLbDEAwgCHdYIIYhMTCxFa6qBpUEa60HuECEFSFjhwYgwhIyiBlZ8bMF3bij6RBoCDgiwkMQagiT0rfqpF3IzjD7Ap5FyriIVQhEHD3juhPgvikhvgRBXEpGb51z3KpzpznBZz%2BHjJZIJhNAgYt4LQAhXQUltLUmFHiKsLcmZxOJ6pD5QTea%2BZDwBbnwt5JHB6HCLQJQhrUGa7uFUhYEyQ0DTTiiO7RZPqlR2zbDih3pYwAxjFlYIGLxIFhD4AVg/wcahz5jx5wzrGeLElbSeHl6HTHS6o6FZLegAyIipJr4b7uHXLeJb7pFeFKlG5HZCnlY6H76L6Cm9qz5jFbY8il5Sku7ZlxCsKV42H6pvSJGsn2GRpJmtLskD4ZEhLdLeFlHV5PL5KKrLa%2BxIysZYD2khRE5oYcBFozybaQImmYhwkwqAJIyBZNnFnCxFrlkFkgZaqxG1lKl8JtKNkjLBmnmhkJqtpZkAo5lkkjIUlyAMB4CbmGEVnXlVmbQ1nlF1kqn9y/BdFjmTiOlvbNpel0KrnHJalf4F6vT25IbmD%2BDqyJgHAZ5tjYAdhdg9h9gOgDjDijhjh%2BiIXGgLhLgEXCLGg7h7g/LwWEVBiXjXikVGi0kPgMmkivhmgMVIV9Qp6DTp4jRZ5BbwWuDIgcBrC0CcAACsvAfg3AvAqAnAmGlg1gmkGwWwGyeoPApAnOHAWgKwawhYIAlU%2BIAAbJIP4AkAAJxGVGUJBGVmBmAJBmD6CcCSC8AsASAaAaCkDSVaCkByUcC8AKAgCeVaU6WkBwCwAwCIAoCUwpBg5kAUAQD9ZxUgDAAKDMApCd5Op8B0D6KBUQDRCaC8C1jMDzacAaXFWagmjRCsFaUaWGQyKqI2yFWkBYDRBeDAB1wuyBUyUtXOJGDiDaW8CelDnwLdU%2BXsjdDTg7AaVFJiWDX6CzaageBYDNWHivFlW8DWpLJKAJgcT9XcSFVrBUAGCpVbgZSMgmiBIbUyCCAiBiDsBSA3XyBKBqDNW6DJAGBGAoAmyWALXRCBWQBrAvFSScDgjjDFrAimCKWWC3AHDggRI6bw3sgAJw1cZqlw27TVhIiuI4myRkrCjghxD%2BYKCyXWrnBYAA0QBrBdA/wuCGhTB%2BDJAhDzBlAVB6DGRFDZAdR5DJAc2mSDCs1LA1B1C9CzAM16A02mR9AtAC3DCVC2Bi3c2M0K39Cy1eQSDU0qXbAa1OUcCSVeXNV%2BUHCqA2XggmXIxhQHAQA3QMCFgnwQC4CEBhzwWrC8AhUiVrDYhVgjBU2kD6WSBcB4hmBGUaCVTiUh2SCVTmWSCSDiW60uWkBuX%2BD%2BB4jiWWUaDh1h1cC2Xh1GUG3zV%2BUBVBWaWHVhWRUQBIBJX0DxWUBV0jBrxGAOg22FjZW0C5WUAFXzUVWlU9Xd0nBVU1XXX1UMiNUnDNWtXtWdW0DdUaVYB7XAADU%2BXDU9CjXNUTV0jqTXWzXNVYRzYnDLU7A%2BVrVuU9VbXpCYC7WGAL0HWDVHUnUKBnWYAXVXU9X8C3XTEPXSBv3PUqDqDzW6COWfXGA/U2BYSU1A0RRrEcBg0EAQ1Q1WAw0aCo34qo3I0aioPo241Y3TIY143Y2E1qkk2%2BVk2SHgPC1DnOAQCuDi1M2Ghq1s281U5ZA0MFBILFAs1y0S21AUMMDS2tBK1cMi0NCzD0NC0QqTACNjAiMcPq2rDrCbDa1yNzX63eWyWcDG2m3m0N2vDW1Hi2322O1ED5gu0rBu2HWe0WY%2B2iXOWuUBAp2SB2Xh3mVmVcDmVh12X50%2BWF22DF3u1rDhVRV1012JUxXJUYzICcwOgYyuMOh%2BLjAOiqAmWt3t35XNV93XV90D2%2BxD2UwNUMBNXzUT0dX4oz1DV9UL2H1DWDkr2Shr3TQb3TW8Db3zW71LUYCVOaXnAn0aVn07XlOqhfW318D32P3P2MDXXf13XiCPXf2KC/1vX5BAPfXQ2gNqhkPA0wicC7Dg3LMIMWCw27CfQPCHMJ2oAkMU3wDU3cO01UP02SNBB0MyMMOsOc0sN81ZCiPy2S2i39AsPfPCOq1PNiOK25DK3iNzClCcNyPqIKMPXWN61SWG3qOJMPAgLhOrKuN4hxPXAO34BGMVTqWmMl230WPe3xC%2B1zUJ1J34jmVJD%2BCVRmVWX%2BDmXmVcCBCqO%2BWcBF3BXmN%2B0gBmCVR4j%2BDh1cAaDJ1suVSVRVBmBx1zX%2BCIsF1cvEs6XwtmC2OiueUcveN%2BNrDWpux%2BCSBAA%3D)
on Godbolt.

All metafunctions in this library are tailored to fit this pattern. This means every `Mold` can be passed to every `Road` as an argument, and every `Page` can be passed to every `Rail` as an argument.
In the previous example, we can pass `Fun` to `Fun<>::Road` and pass `Fun<>::Road<>::Page` to `Fun<>::Road<>::Page<>::Rail`:

```c++
static_assert(Fun<>::Road<Fun>::value);
static_assert(Fun<>::Road<>::Page<>::Rail<Fun<>::Road<>::Page>::value);
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOxmpK4AMngMmAByPgBGmMQgAMxcpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmiW4EAJ6pjKyYAHS3R9gmGgCC48ReDgDUAGJeDI9PJn8VmeH1BHx2ewOmCOJ12%2ByYh2OZwuzDYt2u9w%2ByAMCgU6Pu/zBH1e7wIH2UxFQRAASqgmOhCWDAcCnkSibNHMgsQJxphVKliB8YqhPB8AG5iLyYD7MghvaH%2BAAiRxZjLZ4LhUJhTC8RHxiQeIPVxLlpPJlKIyiYwGhRvVzLVxtBEPhiNhkIR0OOOr1dwNWJxeL9htZTrBJM%2BFKpqGpTDojqdDrtYfZzU53IYvP5guFool3mlsvlgOViRZKdBJZV/wTxpdWqRms92t1qH12ADTFx6KEmAAjlKGJsFATk06vJkjB9Y3QZYlFebozPaDDewPGMP29Wx0ylduATvnU23T627cAGotPBMGL0EcG2ugifhYDk62F%2BeLy3vmGX4jX29MCDDEHzLR0qzA55HXrZtGw9N1kUuNFg07btbg8QQ4wiYh7xDIlnynWl6TnBcoxpOkGWODDmnCeJgIJSCAT3Rj/g5PBkAAfS7JRWggH4/mOe4QBAIjKLcfihJAfMpSWfc2M47j4gIPjfhhSTRLUg1hKtG1NOwYTlxhCTBK0kSKL07Sf1M6TMFkssOBWWhOAAVl4PxuF4VBODcaxrGJNYNkLMxkl4AhNAclYAGsCmuAA2SREgADgATli2LEtiswzESoInI4SReBYCQNA0Uh3K0UgvI4XgFBAUqwo4LQVjgWAYEQFBUD2Oh4nISg0C6%2BgEmABRmFSBQECpPg6B2HDKBicLSBicIWlOTgeEW5biFOAB5GJtEwBw1t4fq2EEbaGFoVbGt4LAYi8YA3DEWhao80gsBYQxgHEa63rwYgDscMUgIWvkDt1LZ1vCHY8oq2g8BiYgVo8LAFrlPAiteoHiGFJRFV2T64aMcKVioAxhvPPBMAAd22lEjpkQQRDEdgpAZ%2BQlDUBbdBSAwidMSxrH0eHasgFZUFSBoXoAWnGSjFX5qxLDMDQPilgB1J7VbVvk5SYLX4kpQUpYudBDHTY3MFNwR2Klg2SAUTysf/LARYgFY7AB7IXAYdxPA6PRQlohYRhSIosgEKY/FDjJw4YeZhgSMY6k9gQ%2BkmP38iTnpU4mAYg4TvRZnTvIo9sXP48qEP3YCzYJEcly3IWqqPlUDKpfij5gGQLkIFNBhIqWD4IFwQgSBlYKuCWULiZWBBMHpEY3dIaLJC4a4zFijR/GczfJH8ZLJEkZz9E4ArSCKxJEmuZzUo0Hft64TKd9isqm84Gq6tIBqmtIFr2v61I3UyAUAgAAoBKBebAA4n3SKU1aAzVqhAeaP0lrMC2vTVBK1dr7UOq9E6jACDnUugtW691Hq0GevTd6BMtgVXwP9BweAgYvQqqDZA4N6ZQzqAtOGCMkYYFoaFf8GN1pYxxpgPGH0jCE1ANdEmZMFAU2prTRg9N%2BCM1EOIVm6j2YqHUD9XQuVPooF8pYIWMRXZiwltkaWssjjy1MRYZWWtNbqx1ojfWxBDaqxNmbdiPjLZ%2BOQLbLx9tHYGzwC7eA7tk6MOcBAVwkcA4%2BwrosaOxRshJPSbHVJIdugp0aLnLJ%2BS4mFLmPnSuicy79GKUXPO5QC6T1WOsWuTS8quVfj9ZurdYrt0kJ2Kcvc3j90HsPfARBBTmGSFPL%2BM9SBzwXgkJeeUz4XyvpILKO9kpJS4MlbeWVOkVSqh/eqxNf5tQgEgMBg1eqgM6oAwaUlkCpFSBxMUuyOJQnGBxVQ8U4EILmgtTB6DXrAp2ntAG9N8FnQuldOhmA7oPSei9da1DpGCN%2BgwwGwMfpsI4a9LhMNeC8MRltZGGK0YiN4GIjIEj8bSJfGc0m1pFGUxpnTV6OimZaOkDoxQeiuZJH0MYhWgteGWMqtYnknAAD0ssTECyVirGVat%2BkqrPqgJ2kTgaixKQ0b2vsS7JPQLkqpYcGjFPNdkU1hdYkNDTm0DOpcPalIdTasYRSnWF3LhUtJ1cWks3rhwDp5VPKcBbh3FgCgxRcnecla4XyyRjNHpMieMzv4RXmfPLASyg2rKSGYa4yVEpcESP4JKaVEjJWSqWw5Ybqq2E/hmpYUUQBmH8NcRIO8uAaEvqW/w/guA5WPnlRIjcunv1mXIoNZhCrFVKqGyqk7m0rCxpkZwkggA%3D%3D%3D)

## Functional Nature

Knowledge of functional programming is not required to make use of this library.
In fact, the resemblance to functional languages was discovered after the library was mostly finished.
Feel free to skip this section if functional programming is not of interest to you.

Before we proceed, let us make a function in Haskell:

```Haskell
charPlusPlus :: Char -> Char -> Char -> String
charPlusPlus a b c = [a, b, c]
```

`charPlusPlus` combines three `Char` values into a `String`. The following is its counterpart in C++.

```C++
auto charPlusPlus(char a, char b, char c) -> string 
{ return {a, b, c, '\0'}; }
```

[Compare them on Godbolt](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:31,endLineNumber:4,positionColumn:1,positionLineNumber:3,selectionStartColumn:31,selectionStartLineNumber:4,startColumn:1,startLineNumber:3),source:'module+Main+where%0A%0AcharPlusPlus+::+Char+-%3E+Char+-%3E+Char+-%3E+String%0AcharPlusPlus+a+b+c+%3D+%5Ba,+b,+c%5D%0A%0Amain::IO()%0Amain+%3D+do%0A++++print+$+charPlusPlus+!'c!'+!'%2B!'+!'%2B!'%0A'),l:'5',n:'1',o:'Haskell+source+%231',t:'0')),k:28.260013001289842,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:14.65577418438985,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:2,lang:c%2B%2B,selection:(endColumn:2,endLineNumber:13,positionColumn:2,positionLineNumber:13,selectionStartColumn:2,selectionStartLineNumber:13,startColumn:2,startLineNumber:13),source:'%23include+%3Ciostream%3E%0A%0Ausing+namespace+std%3B%0A%0Aauto+charPlusPlus(char+a,+char+b,+char+c)+-%3E+string+%0A%7B%0A++++return+%7Ba,+b,+c,+!'%5C0!'%7D%3B%0A%7D%0A%0Aint+main+()%0A%7B%0A++++cout+%3C%3C+charPlusPlus(!'c!',+!'%2B!',+!'%2B!')%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%232',t:'0')),k:39.393368059651934,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:g142,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:2,lang:c%2B%2B,libs:!(),options:'',source:2,stdinPanelShown:'1',wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+gcc+14.2+(C%2B%2B,+Editor+%232)',t:'0')),k:17.690844754668394,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

What if we want the first `Char` always to be `'c'`? In C++,
we have a function template called `std::bind`. We bind `'c'` to the first argument of `charPlusPlus` and placeholders to the rest.

```c++
auto cPlusPlus = std::bind(charPlusPlus, 'c', _1, _2);
```

[Run this snippet on Godbolt](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:23,endLineNumber:17,positionColumn:23,positionLineNumber:17,selectionStartColumn:23,selectionStartLineNumber:17,startColumn:23,startLineNumber:17),source:'%23include+%3Ciostream%3E%0A%23include+%3Cfunctional%3E%0A%0Ausing+namespace+std%3B%0Ausing+namespace+std::placeholders%3B%0A%0Aauto+charPlusPlus(char+a,+char+b,+char+c)+-%3E+string+%0A%7B%0A++++return+%7Ba,+b,+c,+!'%5C0!'%7D%3B%0A%7D%0A%0Aauto+cPlusPlus+%3D+std::bind(charPlusPlus,+!'c!',+_1,+_2)%3B%0A%0Aint+main+()%0A%7B%0A++++cout+%3C%3C+charPlusPlus(!'c!',+!'%2B!',+!'%2B!')+%3C%3C+!'%5Cn!'%3B%0A++++cout+%3C%3C+cPlusPlus(!'%2B!',+!'%2B!')%3B%0A%7D'),l:'5',n:'1',o:'C%2B%2B+source+%231',t:'0')),k:58.71979098628347,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:g142,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!(),options:'',source:1,stdinPanelShown:'1',wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+gcc+14.2+(C%2B%2B,+Editor+%231)',t:'0')),k:41.28020901371653,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

Haskell achieves this by currying.
In fact, since functions in Haskell are derived from lambda abstraction, which by definition only contains one parameter at a time, functions with more than one parameter are curried by default.
Under the hood, `charPlusPlus` is a map from `Char` values to the functions of type signature `Char->Char->String`.

By applying `charPlusPlus` to `'c'`, we obtain a new function.

```Haskell
cPlusPlus :: Char -> Char -> String
cPlusPlus = charPlusPlus 'c'
```

`cPlusPlus` is then a map from `Char` values to the functions of type signature `Char->String`. Applying it to `'+'` gives us another function.

```Haskell
cPositivelyPlus :: Char -> String
cPositivelyPlus = cPlusPlus '+'
```

[Check it out on Godbolt](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AImCgNaZatUkvrICeAZUboAwqloBXFgxABmACZSFwAZPAZMADlvACNMYgkANlIAB1QFQkcGdy8ffyC0jIcBMIjoljiErmTbTHssoQImYgIc719Am0s64oZG5oJSqNj4pJsmlra8zoUJwfDhitHqgEobVE9iZHYOFgxPegBqAFkmcMOAdwR4zABSDQBBe4fkE2JlLwUPzwVDkBBDq43ocALS3PzYQHAsEQqHNUHgyGNYjhYDPV7Nb5fT6HJiHGKHZCHcEAEWJAFYAEJMUj42nIW7kknPdFYrF/AFA%2BEwyFc4gI2HI1Gsz7s0mEt5snFgDjIGUsx7IZTpTIAN0sAE92f84fyeYchUZWSqHOraFqceKlaLpRxbgFKfLHs8WGdfCAAJIAeQgKxdbuJfjJ6FQz0O4cOKRRgkOABIJZibT9DjK5RwU3aHTKM/bHXbHhHI9GCHHCVLk/Ks%2BnK3mwxGo%2BES/GlSa8GaLRXM7XHhw1rROOTeL5uLxUJwABKmCxWQ4KDZbTDEgJ%2BHikAiaXtrMwgSR%2BAB0fkkkgCAE4TwB2AAcJ40J785PJ0n7HEkvBYEg0GlIw60pDHHF4BQQC/dcOC0NY4FgJA0BYFI6HichKBguD6ASYAEGQE9Ei4Pg6AIeIgIgGIN1IGJwmaDVOFXMjmGIDUvRibQeio3gYLYQQvQYc0SKwGJPGAVwxFoICR1ILBXSMcQwN4fBiB6NtMBE39MFUOpPHwljyEESwSNoPAYmICj3CwEiCBRd9RPVYgYnSTASUwCTgD0owNzWKgDGABQADU8EwC4vRSRhNP4QQRDEdgpBkQRFBUdRpNIXQcIMFyTHMSxrD0mIgMgNZUBSXoRNHKyUSwbLfS6OxemcBg3A8do9FCBZykqPRCkyAQpl8HC2t6IZmuWCr5IEfpJjqvIcNqephrmPqRiqcYBk6vRZgGWaliqNY502bYJD7AchxI/9DlUS9EhBRJJEOdCiRPPdEj3LhDggXBCBIJcVxWXhQPAtZriYLAEnK7dqj3DQAmPclEgCS9IYuy9L3PfROFfUh3y4T9Qc/LHsaxnCf1HThAOAtdXNISDEBADYCBSdTEIgZD4OISJWB2E6zouq6MMOW77tXTB8CIEq9BC4RRHESKRZitQSMS0gLkMlIWL2jhB2/Q7OC9dSaZLVAqGO07zsu67ubuh6nvcWDGferhPpJ6SVi3EBLz3E9IY0PxXfdq9b2SZ8Ufxv9CZsYnvt7MmYAplS1MFunmk85RDEsIQEFQC5h1XBmDF6BOIloZPU4DzPRmurCcKLpmWaD8vNeEFO05IqPkAeYhPKDxvGnwYdeBFsLxekSWlGl%2BLZeS4wp3S/R9LK3L8qyQq/2KvBSvgNZiE8QQ8DYAAVVAPGn9Ztoi8ZO5zpO6/Tr65PYL95aYRWR2V1WA//bBVOQdS3rZw3OZu03HogScaUrC0heoLa2ttQ4O1INuFcd1zyPg0EeAIUhEgaF9sjA68V/xExAq5ZWAQ3wfi/M/IOkC1hWQyE4SQQA%3D%3D)

Let us go back to `Fun`.
Like the Haskell version of `charPlusPlus`, `Fun` can be applied in steps.
Feeding `Fun` `int` yields a new function `Fun<int>::Road`; Feeding `Fun<int>::Road` `std::tuple` yields another function `Fun<int>::Road<std::tuple>::Page`.
By using dedicated member templates accepting respective arguments, `Fun` is automatically curried in a functional fashion, similar to what Haskell does to `charPlusPlus`.

Here's a representation of `Fun` in Haskell.

<table>
    <tbody>
        <tr>
            <td>Fun</td>
            <td>::</td>
            <td style="text-align: center"><code>typename...</code></td>
            <td>&minus;&gt;</td>
            <td style="text-align: center"><code>template&lt;typename...&gt;&nbsp;class...</code></td>
            <td>&minus;&gt;</td>
            <td style="text-align: center"><code>auto...</code></td>
            <td>&minus;&gt;</td>
            <td style="text-align: center"><code>template&lt;auto...&gt;&nbsp;class...</code></td>
        </tr>
        <tr>
            <td>Fun</td>
            <td></td>
            <td style="text-align: center"><code>Elements...</code></td>
            <td></td>
            <td style="text-align: center"><code>Containers...</code></td>
            <td></td>
            <td style="text-align: center"><code>Variables...</code></td>
            <td style="text-align: center">&equals;</td>
            <td style="text-align: center"><code>Fun&lt;Elements...&gt;::Road&lt;Containers...&gt;::Page&lt;Variables...&gt;::Rail</code></td>
        </tr>
    </tbody>
</table>

To make it work, we must be more creative about what makes a type. Details are included in the documentation. Here, we only introduce general ideas.

We are working with four types.

<table>
    <thead>
        <tr>
            <th>Type(In the Haskell sense)</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><code>typename</code></td>
            <td>
                A type constant. Every class in C++ is a value of <code>typename</code>
            </td>
        </tr>
        <tr>
            <td><code>auto</code></td>
            <td>
                A type constant.
                It consists of every value that can be passed to a non-type template parameter in C++
            </td>
        </tr>
        <tr>
            <td><code>...</code></td>
            <td>
                A higher-kinded type of kind <code>*->*</code>.
                It is a list-like structure similar to <code>ZipList</code> in Haskell.
                For example, <code>int, int*, int**, int***</code> is a value of <code>typename...</code>; <code>0, 1, 2, 3</code> is a value of <code>auto...</code>
            </td>
        </tr>
        <tr>
            <td>
                <code>template&lt;*&gt;</code> or
                <code>template&lt;*&nbsp;class...&gt;</code>
            </td>
            <td>
                A higher-kinded type of kind <code>*->*</code>.
                It has a special property related to C++ template instantiation, which will be introduced after the table
            </td>
        </tr>
    </tbody>
</table>

In C++, we can instantiate a template by supplying suitable template arguments, turning a template into a value of `typename`.
Namely, for every value <code>f</code> of type <code>template&lt;a class...&gt;</code>(<code>template&lt;a...&gt;</code> when <code>a</code> is <code>typename</code> or <code>auto</code>), there exists a canonical function:

```C++
f :: a... -> typename
f a... = f<a...>
```

[We can summarize our observations using Haskell on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AImCgNaZatUkvrICeAZUboAwqloBXFgxAAmP1IXABk8BkwAOW8AI0xiEABmAFZSAAdUBUJHBncvH39A9MyHAVDwqJZY%2BOSbS0x7bKECJmICXO9fANq7EoYmloIyyJi4xJSFZtb2/K6JgaGKqrGAShtUT2Jkdg4AWh2AandUgE9iPGAEAn2/DT9JfYAxRmB9gFlUKkMAUg0AQT39kJlAARAAaO1CWwYSh2AEksII8DRRvtfqkmMgEJgdn4AHQaH6/QksDCeeiPTwMBoCMQRJgEDaYfYAdyxxEwhMJAIAKsdUoxWEyTAp9gxUPsAG5iTxMsL7AASpgsVlxXIOsIIIqlXiZtDwmBFctcXz8ACETabVX8AbCGIcLRbSPtefzmGx9ngRQQ%2BQK2IT0PSmM6fW6OX81ftbfazY7UZ4iB6RUx46h/YG40ROdaDsaY2b9ujiIKCHECxizIn9kG9RMdnqLPsJsRPPZGVb/uq7bnzWandgrHhUplDSLcWO0819v29UPPVX9l8EsCpyxUt6FwB2VyHARJ/YQaeD4dV5ZZjuRrsO3vOzCrgwlyslu/0jkJVwAKjHqoS2H2JH2T6pPer4fvsyAGAoChfou2ARlGBBYvs/BWKgzJhC8WAktCBBFr0TrMkyaFWH%2BLCEPsYAcOBpgKBRSH/pkd54MghDHO2AaTtyt5AS%2BVZngC3YWgBXHAR62GGA49LZBGYRzIikkCPsIAgEJz4lourhMNBP77DsMFVl%2BOl6d6rqCoSMnNHJvSKcpnGqUyQa6dpDl6S6vphr85niXg8l2ouy6UlgNDhOgfEHL8%2BxsM0VCUtSdpGlepqVmICjikGgHAe2ALsvwyCeCKSn7ppY6Odg0TLIZ2npS%2B6lFd%2BsF/NlqC5flykHgOs57iV%2BxlRVv62dxD5tTOx5MKeDWYDleULku%2BwBRNYSYCF4bZqicUsEwwBhC0xyStKTIfABiHGUyFECfmhbFqW6LIGYFFDUenrlXOqTEKSWzoPs6AbOh%2ByYBKcQ7ZFTDRVSVlhBKTU%2BZlBzg6gFgAOqEAg1nzl1tVmQwEMI0jKPOdph4dbxfyw9jCHTf5DCBQtS1EitABKmAvQajDNFZB0PJSokKkqli0BGIMo8doYGV1VVqW%2BQuClp2Ai3pyZELLlXCdVb7y6g0vQX8AsFQTx6uaGvVTu1x4QP1In3YT%2BuCss5Vdbrc6/Cmhv2yKpvK4NLsZqgNuEgLfmzZT83BaF%2BzBJgBAUV6PqYvUt1gBGdoFZLbAGYSifKZ7Vt%2Bn8vkzXNQWLSH%2BqC%2B7IHJ5gGtjguxNMjrxtzm7dn7pnIbW2NHlMv7%2BfUyHxC4ymqcNSjnuO5mQ9d4HBc0xGLxJ6X6nl5XuKG2riu/mLIGr%2BOP6a78s8Z/XrtmzxFt663bA287h9e1fw0N8fHvX6P3vty8/sCwwIfIwVW/L6L8%2BqwHtvGWVdCTfwPnfEUz9b4PSPqXZuT8Uw%2Bz%2BMjd%2BnM4ruWkiXOyNUgF1UHh5Ye19G4DSZKfB2SD254HJkhdBHomTEBDtobBpCF7nwrsAteVY8GGw3rghWnDxwrQeHgYgEwnTxTzKaJ0CEmRKCuAdIGINYojjArIJg1Nuo7VkY2cOf4qAqVIVBNUAJ4YMMWqI%2BoCiNh0WagBcUOiN6inpIyfR5EOAIAoouRKEYhD1AEOgfCsoxKWROh42iaEyYUTIBEhATFkYMmINCdxniOCiQTEGM6iUqKQW8RGbkcTiCBJZIRIsqQUm0TCBktaG0trEB2hdSKV1yx5OESQBCQTRKyQkg%2BCiIMIk4x0ddMwrTfjMLrpA/cD8yEtxMhfW2ekR5OztsQ6ZCDJnP2QWMmhAsAQPHaQgQk%2Bxjn7iOSc85JNMCIzJjyQpNNznnIgGch5DzPKWWyDpA4fi0CU2eS8k5Ty/j/OBfsRqdjkZ7NERMP5wLyqMKBf89u5z24cFWLQTgSReC%2BG4LwVAnBFTmF5o2dYmxO5%2BASDwUgBBNCotWGYEASQND6E4JIXgLAJAaCZdirQpA8UcF4AoEATLqUcC0KsOAsAkBoFXHQOI5BKDStSLK%2BIFxkAAE4ABsXA%2BB0BLGIyg0QaWkGiHU44nBKUmuYPUgA8tEbQVjzW8GlWwQQ1qGC0DNaK3gWBoieGABpKwgqcWkEwoYYA4gvUhssQ0f6QaeWYFUPUeM2xKVVMsEavU0Qiz1PcFgI1OE8DsuDf9Yg0QMiYGBLeMNeojA0tWFQAwwAFAADV9TMmta6R1MhBAiDEOwKQ3b5BKDUEa3Q2qDC1uFMqawmbBWQFWKgNc2Qg24pLWcLAc6ICrFsFY7IzhKbTE6AkIIlMFgjHiBuDVaQMhZAEIe/wx6ii3oYGeyooxL3dF3QIfoUwPAdAfZ%2B2KP7BgLUWO%2Bq9cxf15CPTYSYIHyjnpAJe7dJKtgSDRRirFRq%2BX7FUAADg1TsDV9xVX7DVbiDVuIuDN3wEQPuJoKXLF4CKsVqwsRMCwPELdpB6WMuZRwVlpBuW4s4AKoVVK60YY4H4LDka%2BXMck6QEtmQnCSCAA%3D%3D)

## Documentation(WIP)

C++ template is not a complex tool to make use of.
Convoluted tricks rarely see the light of the day.
The most helpful thing is always the simplest.
However, those simplest things never get explained.
This doesn't seem right.

[The documentation of Conceptrodon](./docs/index.md) will focus on the library's implementation details and explain the mechanisms with testable code.
It will assume the reader is a C++ programmer who may not be interested in metaprogramming but is willing to give it a try.
The contents will be elementary but not entirely from scratch to bore everyone out.
Functional programming will be mentioned as a comparison or inspiration, but it will not be a roadblock to understanding C++ techniques.

## Speed

Nothing intrinsic prevents Conceptrodon from utilizing a fast algorithm.
While this library requires metafunctions to follow the same pattern, it is uninterested in what is happening within them.
Many functions were tested against **boost::mp11**.
If a function was slower than its counterpart, the implementation from **boost::mp11** was used.
Therefore, This library is generally faster than **boost::mp11**.

## Limitation

This library is only tested with Clang. GCC won't compile since explicit specialization inside a class is still unavailable. Workarounds exist, and a GCC-compatible version is planned for the future.

## Install

Conceptrodon is a header-only library. After downloading the code, move the directory *./conceptrodon* to your project, then use it like your own headers.

You can also install Conceptrodon using CMake:

### Windows

1. Download the library.

2. Open Developer Command Prompt that comes with Visual Studio. Redirect to the library folder. Generate a project buildsystem using CMake:

    ```Shell
    cmake -S . -B "Where to build"
    ```

3. Redirect to the build directory you specified after `-B` earlier. Run command:

    ```Shell
    cmake --install . --prefix "Where to install"
    ```

After installation, add the install directory you specified after `--prefix` to variable `CMAKE_PREFIX_PATH` in your project's *CMakeCache.txt*. If the variable doesn't exist, you will need to add the following line to your *CMakeCache.txt*:

```CMake
CMAKE_PREFIX_PATH:PATH=Install directory of the library
```

If `CMAKE_PREFIX_PATH` already exists,
append the install directory to the values of the variable(note the added semicolon):

```CMake
CMAKE_PREFIX_PATH:PATH=...; Install directory of the library
```

In the *CMakeList.txt* of your project, Add:

```CMake
find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(YourProject PRIVATE Conceptrodon::Contents)
```

You are good to go.

## Links

[Documentation for Conceptrodon(WIP)](./docs/index.md)
