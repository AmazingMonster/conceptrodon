<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-inject">To Index</a></p>

## Description

`Typelivore::Inject` accepts a list of elements.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new elements and returns a function.
When invoked by an operation, the function injects new elements into the location and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, Args..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: typename...
 -> auto...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<template<typename...> class>
            alias Road = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `double, double*` into one of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            typename...BackTargets
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_targets,
            // Collect the rest.
            BackTargets...
        )
        -> Operation
        <
            typename decltype(front_targets)::type...,
            NewElements...,
            typename BackTargets::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJiNBk6jXa61ncnXSnYBjEPDIBAW21XZlGs0quFcnmsX3oq4TJUOW6O52umEAdisMfuqrtXrZPvxWQAXpgAPoEAB0Bf1Isuoa84cjLoQ6YI6BAIAiWFU2aUAEdleL8fqC3myYFg8C4yDbsOFSzUxy/dzGIHu1FMAB3bDGxgEBTFke3Uvh6moIgAWU86CHI5McZhVw3G5T7JVF8vw/xx/vV7HN85U95mG7aNukKYCk%2BAB5Z5iDNHJSCfZ9h39ac2G7CwmGQABrAAVVpgEwVdII3ddnzmRxkF/AQJkwAA3MQBSFW48HQZFaGwkcIAY%2B8dh2CNVDSQx0BhAA2DRqVpPBVE7Mk%2BIVVAiK8QQFQQTABWIYAfBXT4qGIVAWBkuTVNkHs7yg4cBLpES%2B0oohu20wRc3QzCFAgvT9NY248gaTTbhpCZdMufSRwQ5C0IUmzv3sjdlmY24AFof2AhIwIEMLH2C58YM/W4sEhGDqDUyzJgw1dljrGDuzsrzvNuOdF2XQQFCKsKrw/QNbl81DrNXAqpyCkr717NVOtjRNAh6yDrzTScAzggtyqXFllNw4cvCyIxbgPWhuNheUd33Q98UmyrV2/Psk3VBNDuBCk7n1BhtEwcNvhBYaJzcZKZwLKaTSwg6Q0VMtJQuq6HAxQd7Pu303EzHMfoYRtZs3L7tzUohlCYDDINPCwT0S6DXxGx76vGvMdumqroY3LdJQ21BlqPDHYx60rR29B7gffMavwLH8/wA7tLmAGlCfe/s6fmiJgFuAAlVAmFWuVUuu2gYNqxiFfvCtXWrWsQBYJgkJzBtMCbVt2y2TtIb13sBbpkcCqx5kpV3CmtrhAm3uqtmPt6umrYZuSaLo/Fud5539uwCAiTa55sxolcUXxV6ZoOwcE27ULqZCk6oNPfrBuppnRtg1n8YXWOibdqChcWynZXW%2BH7ZW7bC92l2ewOgaUeOlv1SB62QcFMyC39zA%2BbXEuRzLkXEYwyvbYRpGQf7weg5OjPF7Om1LRXvZ2NYNk5Nu9ebSBK07mi0DzV3y4c5xlmF8%2BsNJWP2KGGX%2B07iELw0mKTB0FFj4vDl90gVHrcV%2B79Mif2/goX%2Bko1q3Hvo0fEEQCD8nQOsWI9AkEoPoHsfkCCsHUUEAcbqdo9TgMgf/EEgCSF/2gb9a6BB4GCGwfgxhBACFuzrOPEGXBix1kpviZBXhUGYHQQIzB3CQDi0lviWBORCEd2fgcW4KEPiSjPvhF02Z/xKDaCHGsdYFCBg0UPNwlDEFALfh/L%2BP85ZolCgNDgqxaCcH8LwPwHAtCkFQJwNw1hrCbnWJsOSmIeCkAIJoexqwkIBEkHmDQAAOMwZgkhJC4P4OJsSuAxhjNIRxHBJC8BYBIDQGhSCuPcZ4jgvAFAgGKaEtx9jSBwFgDARAIB1gEDSAicglA0CsjoAkKIgZOCqFiTxcKPFJC3GAMgQiUg8xmF4J/QgJAaJ6H4IIEQYh2BSBkIIRQKh1B1NILoLgpB5ygTSJwHgDinEuLCR4zggEEQdMlKgKgtxhmjPGZM6ZtxZlmFuBADwvT6DEBhGCLgyxeC1K0KsCASAelpD6WQCgEAEVIpAMAKQZg%2BB0GZMQKpEBYh3NiBEVoyJLm8BJcwYgyJAKxD%2BrU4JPS3qAQYLQclhysCxC8MANwYhaBVO4LwLAmsjDiE5XgGkDg8CkQ%2BHcvW10ETbGCQg%2BodykSxFAjSjwWA7mKjwAUoVpBZXEFiKAx4orgBIiMGE1YVADDAAUAANXePOaKrjglrOEKIcQ2yvV7LUHc45%2BhDDGB8ZYfQeBYhVMgKsVAaRGiCvCkSNaphLDWDMGUk1zosAxogKsOwtCcguEhtMPwJywgRGGFUUYJzijZAEGWvQ9bGgLBGIkE5hbpUCH6FMTwnQ9BdsaL2wYVbFi1tsJMdo/aCidqnW2mtHaC3%2BK2BIa5HBnElLueU95IyxkTKmTM6J/yIC4CWaCoJkKQm2tWLJSWox82kEiZIQIeYkiBCyRoSQZhJB8Q0P4HiSR9CcDyaQApgQuB5h4lwHisSkjpJ4v4SQKT308S3Yc8plTqnXrqbC5pcLWlPM6SitFIKBlsE4K0FgpEYzhSYL%2BAwi0uBJDzJB9xiyiA5tWbIDZvrpD%2BqUIGw5uhsVnKYBcoV67N2lN4OUx57SES3Febuz5Ey/xMZY2xgFQLEUgrBYEMwV7oX1II6RhIXTUXqV06MdTmLknFJoHLBIBKiWHKpWSilpB3M0rpQyzzzKVysvZXcrlPK%2BW0AFZ5kVobxXuPwFKxwsrBXsdUIq5knnVU5PcRqrVyIdXbHcfqw1wSTVmqUBamLwtbV8Adc6117rPNet41s/jsgA0HPcSJkNNq01WAjRqvNcaE05CTSmuUvWM1ZoSDmuVsaehFucBAVwTaK2QwXUsOtmQG25BneW9IW3W1jvbYO%2BoC2mhTpW/N7t535hHcXYOi7u2Hu3YqMdiFawNirvezk6T27OAqf3Qx0NvzNMxIBWezj%2BmIVQpvaQO9WBEiPpyaB8DLGv0xn8EkTJgRv2/uQ%2BhspnAsM1Oq40lpbTnkWbM8Qcj2wqNfJYAoUihFSLMbzDeCYCz8CcZWScprPqWs7PkIJjrOgQDBDExJq5wGN23Iww8ojLy3mqAZ0zlnbOOeSkBVZpF%2BnAhGdJ/CnXIKqfG9GMz9%2B2ZWdJGzJr7MKv%2BO4uc5QVz7jvMcuCe73ztD/PqRZWyjlcXMDct5fywVwTotioK8KyVRakvytS8gJVGXBBqsOTlsl%2BW9XOmK7wUr5qWSVZtbhmrSM6sLga0a/nmyJCtd2SLoN4vuthvTf1qNg2PHDeIpwHYocJuWEzbJ7NkcO9DuLUt0tT3VvoHWxOltORLvz7KHdjbV3h2PfyHtsfPb50r4nXMPtm/nttFn0uj7AS10y9%2B/Ljg7zVfM9uNb9nPoJjg%2B5yQKHBvcO3swPexH66UcQBEk8xAhAh/BUlkMilQCYxYMCdZMidbBsNjNlgIkQBJB/A30MkYwilYlJBkkuB4kzA0MclAg5dCcKkcMYV115k4D7kKDkDVgTUshnBJAgA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/inject/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/inject.test.hpp)
