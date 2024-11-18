<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::LaboriousPress`

## Description

`Omennivore::LaboriousPress` accepts an operation and flattens its inner structure. It returns an uncurried version of the operation. Check out **Examples** for a detailed description.

`Omennivore::LaboriousPress` functions the same way as `Omennivore::Press`.
The only difference is that `Omennivore::LaboriousPress` has more base cases.
This function is provided to compare against `Omennivore::Press`.

## Type Signature

```Haskell
LaboriousPress :: typename... -> template<typename...>
```

## Structure

```C++
template<typename>
struct LaboriousPress
{
    template<typename...>
    alias Mold = RESULT;
}
```

## Examples

We will press the following operation:

```C++
struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage 
        {
            struct Slash
            {
                template<auto...>
                struct ProtoPage {};
            };

            template<auto...Agreements>
            using Page = Slash::template ProtoPage<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

Note that the type signature of `Operation::Mold` is as follows:

```Haskell
Mold :: typename... -> auto... -> template<auto...>
```

After composing with the instantiation map of type signature:

```Haskell
Instantiation :: template<auto...> -> auto... -> typename
```

We rewrite `Mold` as follows:

```Haskell
(Operation::Mold) :: typename... -> auto... -> auto... -> typename
```

This interpretation indicates that if we pass `int` to `Operation::Mold,` we obtain a metafunction:

```Haskell
(Operation::Mold<int>::Page) :: auto... -> auto... -> typename
```

Then, if we pass `0` to `Page`, we will obtain another metafunction:

```Haskell
(Operation::Mold<int>::Page<0>::Page) :: auto... -> typename
```

Finally, we pass `1` and obtain a `typename`:

```Haskell
(Operation::Mold<int>::Page<0>::Page<1>) :: typename
```

By 'uncurrying,' we mean we would like to pass all arguments together via a tuple-like structure.
The type signature of the resulting metafunction will be like this:

```Haskell
Metafunction :: (typename..., auto..., auto...) -> typename
```

Since in C++, parameter packs are not transportable notation-wise, we place them inside suitable vessels, which will yield `typename...`. Since `typename...` corresponds to template member `Mold`, we will invoke `LaboriousPress<Operation>::Mold` with the results.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

using SupposedResult = Operation
::Mold<int>::Page<0>::Page<1>;

using Result = LaboriousPress<Operation>
::Mold<Capsule<int>, Shuttle<0>, Shuttle<1>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `LaboriousPress` relies heavily on recursion.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename Operation>
struct LaboriousPress
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
// There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
// We invoke the corresponding template member of the operation
// with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
// We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = LaboriousPress
        <
// We invoke the corresponding template member of the operation
// with the extracted pack.
// Then, we pass the result back to LaboriousPress for further invocations.
            typename Operation::template Mold<Contents...>
        >
// Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = LaboriousPress<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElxmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcBJgsqQa7JoFuBACeqYysmADUAPKXxEyNx9gmGgCCE8ReDjehTFiJCcXgUymImAUCneHxMAHYrJ8bsibrt9odMMdThcrmwAHQE14wlE3b6/Ag3AAimBadBu8KscMpx0RsM%2BAHp2TcLEwlDdREoQDDiSi0QdnpikSisSKScixRisedLsx8YTAth%2BQYoTcPIImBEEqQYZybgAVBAJW54BQ3AS0M52yI3VKta67YgupjIADWN3oVAIeNlcuVuMwBLxet2gmhUuRRPjpIIPz%2B1NptCx0YNkWIWdkjAICkjRI1IYZJq5AHVrQwAG6oH23AiW/kkCEKdIMfBGVF7cW7G5sSoJO1UVGt1CPZ7ZSs3ADuhAQE9umFUKe9u3QXt9waTJNBEWAqJx9MClPu08aIBAColNwAsp50PnBIXi%2Bq3oELPSk/Dmd%2BwpJneRx/icIYkiBmInEwXhECWGparytpCJgACOXiMFsxr7iisHwQS0bvuWZZJmSaY0gamYnKhGFYdBbhEbGCFfm8f4Ijch69mGZ4Xg8CQzs4t79hiNzKEwwAMUxRYsSy9JMiyQEfKaABKmDIBsmR1rcArsEpkEiRKJFuBBoqGUcJxhqqEafkhOrZoaZBzjWpKYK6TyDi2tw0MQExek8bAejufpUMQqAsCudpeb5e4fHKoo4tZkbSQoOFxfFJ4qtckZ3NFcbpQmpEFcmqYUumVGvrSuaVe%2BLGkPceWyexrIZZxmTcaexwXgCQLECCYIdvlrUyhy1a1g2TaRWgxAdl2PbHlBQ57FUY6RVOAkvKNC5LpFa4bg4mDbq6u5zhajD1fOtyujqXk3B2Xi0BSsTen6RD/ICwLrANkK2vwnpUBs0U3BEDaiI0xamfFVnXJeG3ZDei1PrQL4nClTXFSSibKVycgMKCh3BbarS3BCyBnMg9Dbn9NwA20lqeiDqBg9kEO4ciCPmbc5V0FiuX0x%2BwYagjOKKexAGsiGUHGZDfbokZMFwagLF2Sh6GYQw2Ey/hSuEQWsZpa10NqnifMJEN0pFSS5FlZRPM0Wr9E1cxn71abMWfuWCIy1xC2dee729f14I/UqiUw/xHnw8JcuDuJklOzJHuWxlHMx1ztvUW4bsC68wuXKLxX/gXmPAZzodZcbHzABCezEcnyI%2B4%2Bz68VSGdYlXNdsM7gvYHn0ESwpgGfCaABUY/jxP7Kj2PZrYEIZrj1PHITyvI9L2ysJmIEEQU14WBnm4cF0IQZxYzC1uw5HAjCl7pdp%2BX4bo1bKbkmJYVEEjL7NTLUsKwRPcywvuCVARA463BlhWNmcoL5CG1AgGWmNb4Y1amZe%2Bf8dYAKga1IB79UBgPkoycWCDpSDwllg1BA4GLa0jB3TAtdYxYxQSiRu%2BCuo3FgbyJA0dKFvxAXgiSDFaH0MTgAoeyCEykP0hlX%2BbhqEEiEV3IsjCMosIES3YBoCBHt2rnQxROcyxiMQUQ4ed9KEPySvInRwjoT1zakeJuyN1G4M/tozutUk4D2MRvGRRsbKYK%2BC/P4sjUgKAev3JSMi5H%2BJgQgOCBB6AFxhI3IQXhUhFEOmpUJj0W4R0EgwGEN4XEnAiAQXOIAwFYg0GUipJwuCljIR8RumSHoUjYT1T6oJg5Ql5leWcRVCnPizEwEJYSsQlNePVIQsSCDxIYlUjUkzpmzKxHUgxX4GlzEcMgAA%2BshBIBAIATHQDeBQ1xdk2LcM0x6kzUnpPQFc0pGplgFw4KsWgnB/C8D8NwXgqBOAmUsNYUk6xNjgK3jwUgBBNCvNWD6AIkg8QaEkFwOEgQND%2BA0GYAAbFiswAAOPF%2BhOCSF4CwCQGgNCkG%2BVoUgfyOC8AUCASlUKOBaFWHAWAMBEAgHWAQVIcFyCUDQPsOgCQojXE4KoPFWKAC0WLJA3GAMgZANwpB4jMLwQ6hBgTHK4DIQQIgxDsCkPq%2BQSg1DQtILoPV84nipE4DwN5HyvmWrpXcOC/KKSoHHFK2V8rFXKtVQiswNwIAeBFfQT05hAhcGWLwFlbLSAQCQMK1IoqyAUAgKm9NIBgBSBSDQR6ZtKCxEtbECIrQzgOt4OW5gxAzh3FiNodSLKIXCsUXcBgDpLVYFiF4YAsjaC0EZT80gWAWCGGAOIVlvB8Ck0cNpEdNK1zqTgtsCFJT6iWtoHgWITx60eCwJalMeAyWju0sQIEShqQTqMDuow0LVhUAMMABQAA1PAmB5z8W%2BRC/gBrRDiBNf%2Bs1Kh1AzqtXoAwD7TCAssPoXdjLICrCnODTgMqjldVg1YSwZgaWoAvX1LASGICrDsC2%2BGEBXDTD8HqsIhpFijD1UULIAgaN6BY40BYIxqg9AowIfoUxPCdD0ORhwfRJiDAYzx0Tkn2N6rmG0bjI5qhkZBVsCQTqOCfKpa6zgNxfVyoVUqlVaqQ0QFwNqqN4K42QsfasS0TAsCJFI6QOFkhAh4gAJyBDhJIJFZhJBYopf4LFXmiUcBJaQMlMa8RYq4FivFXm8UJf8Mi/wPmsW6Yg3ShlTK7MzvZVy5NPKPUCszdmyN4q2CcFaCwOscIZVMCQr2LgXm8RcERZq/ARAiN6BA4aoD0gQOKDA5a3QKRbXDOrVpnT1LfmcHdXyuCq06sNaay148bWOuItDeGtNkb6RbzMLZhNryk0pvCgdo0FWrs5rW41imk62tcEpYWj0jKIClog7Wyt1bSC/frY25tDh/vtsLJ27tEHe39sHcO/747J3TppXOiji7LUro0rsf7m73kQZ3Xuyth7tg0pPWeiFF6r2YBvUjo8j6%2BAvvfZ%2B79Kp/sDcA8a4bshRsWogxN/Qk6UDWGsAh2IJGUOpDQxwDDBAUaUmw9YPDvzCN4GI/AMj9R%2BN%2BCo92eTIRuzKaWMxjIrGcjCfyMb4o2RDdMb4%2BJgTcnze0bt40QTUnygyYU47vIzvFPu%2BGCpzTawNgadjRFubemOA3Aextp7rX2udY0KGyzvWjsxtO/Z0gjnnOUC01FmL7WkVwgy3CVFkhAvyr1fN2lnA8vMvpxy7lvLPWCqzXdqrEqOB1f9SwBQdYVV1m2xiCY3WrOq/67IQbnPTU8/AzS3QwQpv2p%2BbNl1OXFtla9eObvCre/95uIP9rw%2BKRhvb6OaNgQM%2BFYuygM/GahV35AP3tJ2zD/bOP7s4gLB5V8DoB9ktZaFa9a/2gODaTaLaYO4UHaXaVa0OmAfaA6Yg8Oo6iOd6JOs6eA86eA6OEGmOa6OOb4eONKBO%2B6ZwxOx6fU5OvAlOGQ1OewtOD61%2Bz6EkTOX6P6bOk%2BHOEgXOggs%2B42IAwQ0Gxgwu8GBO4utKkuLMnA7IRyQucGFgSutKKuauyGLulG1GTueg9GHugelupueunG1u0muhahDuAweuYmrukmNuvGfuFh1hxhRuamIexqq%2B2W%2BG%2BmO%2BQ4feA%2BQ%2BEofkFmPWJAaesa8ame2eowrmeO%2BeIAZg7WgQgQ/gGKyKFKCRcIiW7hC29Ktg%2BWZ2ywsKIAkg/g3m/geK2KXmkgXmqKvmXAghnAgQa%2BHh2ReRWmGqmRNezRmeF6mQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/laborious_press.hpp)
- [unit test](../../../../tests/unit/omennivore/laborious_press.test.hpp)
