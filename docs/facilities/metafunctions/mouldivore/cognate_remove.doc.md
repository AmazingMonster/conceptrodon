<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRemove`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-remove">To Index</a></p>

## Description

`Mouldivore::CognateRemove` accepts an operation.
Its first layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function removes its arguments at positions indicated by the index list and instantiates the operation with the arguments left.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
             &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
             &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
             &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRemove
{
    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will remove elements of indices `1, 3, 5` from `Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>` and invoke `Operation` with the result.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateRemove` by combining `Pagelivore::CognateSegment` and `Omennivore::RemoveTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename Send
            <
                typename Pagelivore::CognateSegment<Detail_t>
                ::template Page<I...>
            >::template Road<Omennivore::RemoveTypes>
            ::template Mold<Elements...>
        >
        ::template Road<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAHP6kAA6oCoRODB7evgHBmdmOAuGRMSzxiSlpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnspiJgaKp/mdwQRMCx0gYOSSCBiPsw2KQntkAF6YAD6BGp9zQBPeBHpjOZiMCLyeBGIXkwSKs90hwOOTzcTHSCi89FZp3ZnO5TF5yP5gtYmAAdB7ZXdFtqHCazRb6HqaQ86dhVByGOgAGLEWTW66Qjlcnm6p0Cxiur0%2Brx%2B8ORmNxwSIgDsVhLL2DBvuyftjrctdTfIzQvdnsC2CecKYCj%2BHkETBWZE1LddHrd2HobEECmzWtzSvzrljshJ/daQ5Jk85jAICnH1I7uLLkKeZ81dqb6ZdbHHFkwwAiDAiwFnR/u56eXmyRieAFlPHQNUNXXQdImIEl70fBhnyMfcPRFbdpz3A8j0CfUIQrKsIRrS8HTTBs8PrJhUVQVDO27XsniETAAEcdQVEUSKIccADU2jwJhYnoN8cXuHM8wjZcixlZEaPor4CPY4hOO435yK9EwTw/c9G3wklmLIj0oKfF9eNPc9vxfekmGATBgOouiGP2SCH10uDxxFaTZJ4hT0OPSt3OrUNngAeWnZ8ADcSHYEA3AMXs8GQAD8CoDEABUMz%2BAFIVbBR0iYfYnn8xggpC0sMKTIiCOdTNb3bPjvXnP0ACVOVQQLMESj4/iU8tPMK2lngsHtzNNJQE1tFN1ORTTxwASTnX0lTqlgGqapKSXJEAQAiLBVElJQJIVElxrcyq2oMs81N5FSzxJI7PyeQ5DieAB1czv3MkwADYNAZJk8FUXbsQPN7NVQJ5GB8BJ8MRN6V0EeK2jMvdXo0N1Ls/D7mR%2Bjtx0hghoeIWGFFIJHzxu%2B7zPQON0k1BBzMiCMnhhkHBERs6rtK1t8aZz8WbHbTMoAa2x3HLq9T9FgdKKuwERZMECsRadIp48HQDFaAgDZLoAWmxf1zUtXUmYu9nz0x/nMBQhCCbPHrkD5mGTfgxm7k/Q9Ood1TiubG82zdO5gEZHcZyFwyf2Af9AIsrA4VKiAFaVklvd95C7exFXVa8zCOpDE6CLGj1xqY0jxwAKSmhcnlm%2Bbmt%2BJaCHQFa1swDatusgi9oqkVltWqN682qzJJJAv9uPDCObdvXkXN67boer8BvhlGvrR7A/o0AGgYYEHiDB%2BGjZtuG3vtq7zzn77kUm9GPW3nHbbZl2D6JqfSdQcmCEpp5qaVOnkP3g%2BRw96/v4n4m09npvSPn3X6np/pECeMAQGmU4xUWfiTPAIsdoGzPETeIBAADumBGCaiwYDGYuMv4H1AciIuZ83R/gVugegxs9x/2/nfEmZMKZU3ru/HG9MCAkOZqOYU49OblTdJba2l84aj0qsLVojhkDiwYJLaWtBZZQOjsrVWTMNYdi1oGXWN81RuHHhfYhZs0H/hoXQnedtGEH1EfQxOkjsKXUzu7Mqns464ITgHM8RlfwAVoEBJEGpw60Ejmo2OPtPG7kTh2ZOTisKp0NHSOqyBdjZEav6AaKVcLDWIvnHOecWIegLiKIRntfKIOIOJJu%2Bl%2BLVRmvVRqFc3xuHbnXBuPcdon3Im3autdO4dO2jZchPTsqVOqZJGJB1lL6JcaPQxZjmFAPBu9FU88T7gMRpAwGwM2Abw5Cs4xtt4a8ORms4%2BbhT6L3PiJexNirpLIfk/F%2Bb9aZcM/oI/hmB7mfiWU9FZZC3AUOuVs5eUCYG02QPAv4iCnj4BQTZRZt1ME4LwdgwhVjTmH3OWAyh1CKSWPEXjcejzWGwteR/XcWLjpfJ%2BapL5d5eb2MFu%2BfRItZHyMUTLTS8tFbqPVprJcUZMYsoWfojmXzS6NIWi1EkFTKZVM6fsKZ48VqZxDgEyCTLMUVRZVI88arioavQKKoxtydVujpWefFtCmoWr1U4pmLjrxuPHB4v2cNWWfl8cHfxgT1RwsaKEjMUc%2BURPjtE8icTEkJOdkpSs3kjTUQQKiAgVpsl3GdaafJiNWUCSVEIFNBA01pmdkm6SGJYh4GCoyFazUopiGUI/QaqVXTpUyuZCtVaa3PRmUVXJWcc3Fz9PW0QtAm3k0OrGjObtRpy2jHgYgixh1KlHY2x%2BJIF1LtEtMoegdjKlQsoW1NQYx5oUKtO7yWaeVbsWIUwGNF5QmrzfUp4a7x0buRLeggIpH0CGfbuy6Pqf7PQDce4tp63Dfqdh5R1mbZ3Zqgd%2B%2B9lkn33vHPKhItSqrTTfQKBtH70ibsXXe1D/6RSYaXQpA0MzvVBxAyyjUQrCyrhda2PD6QCMTrlZUqZaqMzeKeIagdJkzLEe3b%2Bxo/6YM0fTt5eNIYk00SjC2nJdYSoMt1XU3DynAknkvTheDA6%2BQIezrmiiEU/gTMYiorSbpnJcR4iuyyUYSTWeGW4BzckVWssOk6hD16h3aMon8XyHx9m5EE/m14JtBy0EFrR7%2BwHD1BOyuF0WAgSRedcrq1OjsDPOIC6ZoLFmex23dV4r1%2B7fw1TixZN4G54vIgq5Giq/GPjxLk4ZrNPXNPma7JZk0sgwIJFKX1pC0TnO6bXMNzcyIJszgHjRvdx0ivGbY1zfrIW0ugwGFF19DW4sJZW1dZLGYLJhd25F%2BbU5WvmewvlrrhX1uERe2U8iA2ytusiR67DdHjI1VQEwf1GpDt0HDVExbbWQClU63BpNyhTJ9GrSFFaHhgDMA5DRYAyFVN3DShlLKiOzLoh7QVGdb3itFK24Ny7EXMsvtw%2BjzHmBsfIUHs99TS08ASmlE8XOooedSh4cU/buGwfxb1olg%2BWbxTC/HAAaUE5%2BRk9FF2/CeBAA8ZgXrmBehABXBingFw2Bo8V1Xg4AAkaGMD56lunGWGC7RFAXNWCu3InYU4k/zL2zMtf9lVnx9HiegY1NNjbbAnhdpR7WkA77uPNZ%2Bwnci7W0z6rPMJ9TpcjvIglxD37KeYdGutxSW3O74e3XGlGKKGvRAMFprQBQgN4hPAyr2TAQFgPwzaQM7uQzdR7051eBsXyxclxL1gevU6ns%2B658iOXfOBcL5F26YFl1osT8YFXGuHd1p96bs743S39F%2BfN6tl7y/FfK/PKrrw6u/ha89DrvXBujcm7N//YDEu7cBod3tk%2BLubuHuIYn%2B9GKWYGrgri7G0ePada%2BGY6CelyLuhesOgeV0meqY2e4OuesWdA0oMmJ%2BBWs%2Bw%2B72Ho/unq6e08xkfqFkm%2BTuieEaUO5mqecO3uacimoInBYISSzw40KYHqjueORoXBoI4I/ac%2Br2EhpBNOZWO29O9BlU0WzO%2BEZcjUHOxBI0rSQui%2Bbc2hK%2Ba%2BTMX%2BuBtAP%2BIEAYOs2%2BK0LATAPMUo7S%2B%2BvcGyHYvSO%2B1hthko9hjcjhQKasXAmyBBQ%2Bmhl%2BOcY%2BfoDIqARAIex2giAW42t2AelB/2fiocqW02Zi%2BsZ%2BfCHsLmJqZijsY8eR38ZSomyOsBYUqAGO%2BEbOu4JI3%2B5ehRB8GBYMUR3SWmmR%2BR2ATRBygOwOcqAUMeoUqhMqlcaB/8XR5kfqW48Rps926RoxBqReImPRz6bgf%2B12OIeW54Xuzsw8vuOa5Bf2FuJRFk4RkRSO%2BeyeuWF6M%2BPkIhbIPBpwTw4YrA3I5kGawhIhYhBo0IsI8IoGpIAg%2Bw6QFBHBzw7EGIeOgWUCVykI0W4Jg8ooMiYs8oksqg6QxAtmTwSiOoBUk0sapYNxSaaxAgkJsRHs1GOGJcxJ9BZadIf4sWVAXgBIAwpJb2fWdwOM2GwG9JrQjJzJuQFkyhHIQxcq6W/%2BlUK0LRbgXAIowQTw/gXoK0kxzWnJwBiadIQgXg6QJQHedUgYSoGawGmp2pWQupvwloSo9uYp12nmTAWIyIGg2ITkdpJIZgTpUeLpyIkgh4GxtJzwepFpeOwGAZoSFkPJTAfJTQDOtp9pbgjpzhHpsZvh7p8JyIbpCZqZbgasgQKZnpbg3pGZeZasCpaEvpoJjx8UvwBp9xdSosyAkoZWCQBAEA7cCgroDZLSxpOp6AIZP6Uq%2Bp2IKcFgHAWwtAnA/gvAfgHAWgpAqAnAhilg1gooOwewz00IPApABAmgI5WwPMAQkgboGgyQZgZgAAnKeVwP4EeckFwCWCWNIGORwJILwCwBIBoBoKQFOTOXORwLwAoCAB%2BVudOSOaQHALADAIgCADsAQOkKiOQJQGgFyHQAkFEK6JwKoMkC9GrC9JINAsgHIlIG6GYLwB3oQCQArHoPwIICIGIOwFIDIIIIoCoOoMBaQLoDKVghvOkJwDwKOeOZOdubOZwL5KiLBUqKgFQE8BhVhThXhQRQeWYJrh4EhfQBiXiFwBsLwEBVoFsBAEgIhZxqpfBRAAZchYkMAFIGYHwHQByEupQLEIJVWswMQBiDxbwE5W0BiL5LENoI0EBRuYhchL5AwLQK5axVgLEF4MAKaLQI3m5aQFgNYUYOIOFerk0I1P%2BaxfXI0KiAcBuREByI%2BTOeiLEBvC5R4FgIJVqHgK%2BdwLwI1MQLEKaW8ElcAOiEYNuVsFQAYK%2BKxD8FgpdlORuVRcIGOnRdICNUxWoIJexfoIYMYNYNYPoHgLEP%2BZAFsI/AMJlWrOSEEqYIuZYGYN%2BQ1TJFgGtSrL0P0LkC4FGHMH4DKWECsFUDUHoCUDkAIHda9VkO9QwKMM9RMDKQ0FGYMEsJ9YDX0H5c0EsH9eMIkIDaDZ4F0HoCLO0DDWsHDVsE3rsPsBIHxRwBOZ%2BYJT%2BVJZhdhbhcAPhU8IRYpRALgGRWpeuZpZuZ1VsJTMDhMBdXuZIIEG6KeYEPeRoJIGYJIG9BoP4C9KefoJwM%2BaQK%2BYEFwG6C9FwC9MkKeTeS9P4JIJeXzS9ITaxT%2BX%2BQBczcBbpRBXpVBaJXBRQCZagCpShWhRwG0CwIFCWGrEwJ9r%2BFwKeW6ArTOaRUQKdZRbIDReIPRZNUoNNaxboFZZxWaG5XjQTV%2BbwD%2BSJTBaiE8BJSTTJbhd2J7d7b7UpbbYZQkIiNCGYEzdpSBebaZUZdbTXRMLnRZReR%2BTQKElhvZY5REJ5fFR5S5d5b5Q4PFYFbuMFaFYJRFVFTFXFXVQlZyPNSlTOfgIyOlb8IJdlakhyPFQVX0IJSVWVRiBVQcDOdVbVRuQ1U1UoC1fPS%2BJ1XwD1QoH1ZgANYKPFSNSHeNQxfIBHSxTOdHXNR1ftVYJYMtatfABtcCbkNtbteqIA9YEdcnSdQrKvetZdZDc4BAK4GDSEFGGjS9TKW9QMFgwQ7kLgwDag8DUMLMIjYUODVdQIJQ8sJULDcjQjQUPddMMMKQxjdsNjXRQnQJfrZwFnWTR7cHF7T7YeZrnTQHaXfLRXSzaQGzVgIkBdY%2BTLXLd7YLSWP4KeXeYEELSLVrXrd%2BZwIbYBbfWBZBdBWJcZfXcQKhWwJwE7bJSwAoIFHIoFOI6mIsCRfgAHRRTKW/WNRIBNbIFNT/ToCAMELHdxXVfw8Y8ncJZbeJZJaoC424x414/hIsIXXbQzYEIEPIybaBfpUXWZbY2U6pSAO49qZKJ46eZKN4wQJKGkxNTZe3RAA5axb3WFRuT0/3X5UPbbUFSFWFYvZgJFdFWINPRuYlfPUfbwEvZDRlWvaoDlZvTPdvUVbwHvZ5YfVVTJKffVQkBfZgFfclTfcU91aZA/f1YNa/cHcE2HWE9/TNVE//QtQdTYCVedeA1tZwIcMtLA4dcdQkKdcgxdUDQMDde4NQ%2Bw49Uw%2BjV9aULkEQ99QMFw8jRDRQ6w0jbQ2gyDZw09cw/DcMFgyjYw6sHg5jSuTjRpVLfjQIyYxwFJek%2B41iVkxyDk7TX4yQLIxpVpQo0oxzXjeo0kN7QU/4FeVre%2BQUyWCrQk0Jb%2BbYEbZXabqQFzf4LzbeSWO%2BckJIBeVwMeTrgy4EEy4k8q2q3jcRYqwbcbTpVsA1dkM4JIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_remove/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_remove.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_remove.test.hpp)
