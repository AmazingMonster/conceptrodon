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

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAHACcpAAOqAqETgwe3r4BwVk5jgLhkTEs8Ykp6XaYDnlCBEzEBAU%2BfkG2mPblDK3tBJXRcQlJabZtHV1FvQqzoxHjNZP1AJS2qF7EyOwcAPQAVGfnF5dXJ0cmGgCCp%2BcA1AAimBmujMh4mArPF1uDye11BlyB9zukLMgQiyG8WGeJkCbi8jlohAAnsjsFDzLCGPCvIjkW5kEt0FgqDi8cCLs9lMRMDRVADzhCCJgWBkDJzSQRMZ9mGxSM8mGjUDSHmhCR8CAymSykYFXs8CMQvJhkVYHlCQSdnm4mBkFF56GyzhyuTymHyUQKhaxMAA6V1S%2B5LDUOQ3G030bW0x707CqTkMdAAMWIsgtNyhnO5vK19sFjCd7s9Xm9IbDkejgiRAHYrIXXgHdQ8Eza7W4q0n%2BanhS63YFsM94UwFP8PIImKsyGrG07Xc7sPQ2IIFBn1Vn5TnXFHZKSe21%2B6Sx1zGAQFCOaa28cWoc9j2rrfWU462COLJhgBEGBFgFP9w8T88vDkjM8ALKedDK1UVz7SJiFJG87wYB8jB3V1RQ3Cdt13fdAh1SFS3LSFKzPW1k1rbCa3FIgkLbDsu2eIRMAAR01WVRUI1ARwANXaPAmFiehn1xB5M2zUMF3zAhSQo6jvlw5jiFY9i/mI90TEPV8TzrHDSXo69b3vR9OKPE8P0fBkmGATAAPIqiaIOMD1MgzSR1FcTJI4mSUIPMsnIrIMXgAeQnB8ADcSHYEA3AMLs8GQX98CoTEABVU3%2BQEoSbBQMiYA5ni8xhfP8otUPjfDcIdNMrxbLiPRnb0ACUuVQHzMBiz5/jkksXJyukXgsTsjKNJRYytRNlJRVTXQASWnL15Uqlhqtq2LSQpEAQAiLBVAAfSUETZVJIbHJKxrtOPJSawKptrxSgBre5iCfd03yWW1QvbAQlkwHyxDFCVnjwdBMVoPbnggX63yOI5nhDZLwyRAA2DRGWZPBVE2nFdyhtVUGeJkUoQNUECMrwGAAd0MTl/0ILlnQBk8YZZBHWzeojXSoATlvaJ9SHJ48geeCapqxozIlDMVLp8LcyYUt9j3o1nRbFjmCgGHm0b%2BeVmaFycRfuMWT3a5BzsumC1bfTZfoAWhxH0TTNLUpdJNnB0vIysHhArqEZ5mFE2eaCpsm2jqdZ4tZ1p8PdTXcreQlr1cUvKGztkd7mAJlN0na6dM/YAfz/YyHdoJ3Pu%2BiA5pAArls%2BrcsVJOOE4QrTD1LEdNkN1y0OawMDtwwbnSGuiJRHAApUbZ05qqarqv5ZoIdB5sWzAVrWszcK24rRQLqeZ9M0TSR77aD1Qt9W%2Bjwrm2df2Lqul8I%2BPW7HGQB6GCel7aFp1Hc5%2BqX/qlwHgdBwx/xMKHKbh6m2AkYaBRgrDG8saDECWO%2BfGhNMDEwTPrDWCpYbwxRCNGm7cGayCZrrSW59pbAy5jVeWfMlaCwQkgjWEsbYcy/uDX%2B0NFQAPQYjN0yMiBgOQJjAg2NnhKBlP%2BXGBNBDwI%2Bogm2/80FuD7pg7uroWCfXQPQXBLNaFEKHkZXhvNp7kOACrAgVCxY0PfieGWng5baIVtA5WVcjFvmPrrEOBDDZSxNjTI05t/ShzcN7IcbBnhZydtgwQqi3ZB0%2BF7Ux%2B1/H2yaNnVMEBFGUhUa7d2hdg6wT8XbP2Z0T4KAiYfX6e5w67yjheA%2Bsd46YETtuZOx5dJfl/LQH%2BKpAnxJzl9Wg%2Bdx6FOLlgQQZcUQVxqVXGkNdXh1wbjldCjc9T0kqsgPYOQSFdSMvFLCfUCLyI7l3Omzoe6ih9kVZ0HltHEGEnPLS3EyrjU0SPZ8bhl7hmnqtNeG10HESXr0haLzV7rXMiiTei80rnMuaJPWsl5IEL3hU46rpHGnxKjdNoV8b531evRD6XTfpvwIR/EGqgwY/z/sw6RGCgHsJAZw9G3CIF4CgfKYRcCEGk0kWSwBj8RwhIIGE/ByDngc2IVovhZCBb6MoTbEx%2BKzGfyJd/SGTDUGAOAaA2lPC%2BECIEEI2BojWUsHsRTDlQLTbt2ScozAfL1GD0miQqxYrbHCylRKflyDzG0EsXwpkNiKFbh3DbRFkKpauIIe4ts85wyLkEMUlENsgmphtnigVb5hUPNJGc7GFz3kHEhWfZNJ5J5dIgIG3atdXQhoFRWk89TngezyunFpMbfHRNtgfdpjtEk8rCekz2WSW3HLiR2z4SSlGpN1j2zJRiSmBjKVs/KsSqmVz9TWxpadmmtNVPG4dz8ekTwyZ8fppcBTl2qbU6uTUpkYTks3Ny17Az6nIggNEBBzQbPuLCo0Oz%2B7eiEE%2BggL7kzhwfeJTEsQ8B%2BSZPNOqoUxDKFQBkHqCUnRJRSkZEDYGINGV2m5D97dv3ymg6IWgcGEOlpvZhd95TP2cIjAypY%2BHniEdg/B0ktHGVQp3inPSBVjK/uff6WNYdnJXs2dWNu702NLD2ajCigiGNMeIyxlEkmCCilk9qjjv1V2tt43%2BgDrG6OCSE7qWZ4dcMScM9JkygjpMjgzQka5pUxqMcFDBxTGQDOMrU00bVop7NQJkiZzjDTU6tpjaqCNeYlxwt9gpkj6bzm5uwIUmtda536UMp5qT1mNPGabiJ/LbkH0UXBm%2Bj9A7AtOYHiVn%2BEyCvlao3hmmpF/jgtoly10dk2IcQYzVoS2axIsW69JYqmmpYNbnSpL9zXgr/A8p8Ygd0BA1p4vKd4q4X4EOwzKkL3HUzGXmwkJbDBSRdakkljCb471zPG1R8z%2BzTYtcXaM5deauNfnKn2B%2ByJVTra%2ByepdqtiopbmaZlud27sLuKu2WbhpZDAQSEcqHo5xyvZKqtky4Zlzw7XCieCfqt5Bd%2BhNsT%2B94Vkxm52ObC3jsrduW8TAG3inQoFdpnjP20o08GOuVHQOKe4kbldsHblZ2k/tJDmO0OnuuhGWeldoXyqoCYBuhnTPhmnrscD/dgHhM3fcmcDL/RwP%2BXmh4YAzBOQUWAAhRDDxErJVSsoAyRvMPZXB5N8XHvqMMSl7Dw7i3udnwx2bi3mArcIW3sTqjOQABelr5Sd34XgOPy1DGulkcik8GO/t0GZ8FsWH7Y/x5HAAaRrW%2BJk1EGV/D%2BruMwENzAQwgCX5Ubhng93rjbbTAAJJRjBU8Ha53kTaooe5GxL45fP13SmRy9%2B3WXYy3u7a/E7wyvHXBk99uh43kGQBxaU24BfBOtcFVS4Xetn3c8ohzz9dXgPEIn/rb3yk/ejMC6A8DIa4ZQo19EAwMUtACgqM8QzwyUXYYi2mjCzyS0byAKWoUMRi5WsSdOzmz%2BAybuwuFGou54Tyye8ezwieReqevcKBA8aBjAY8e6K8sBc8I%2B7ehOW2LOyCheeBxBroZeS%2BYsleXg1e/wEAdeDe9ezere7eneLa2mN%2BA%2BHO/utO6Co%2B4%2Bk%2BM6yCbO%2B2HOfWMWAS2%2BmGUGrmRG8Wch9BJ%2BCanBb4aWYmnM/21%2BjOX2qe06VsmBUeXuFWMuGuaOWmoW66xk5BJ2d%2BL2fOOIIOMy5GwmRWYIYR4I8yLwQ0iYtSx2tu%2Bu4RYREIuUThEulSvuVOnOR2ge6O9OIeOEwqket2XuRBCeS8rBaeBy8uekkh8oHOnifouEBcLATAp0lq1Bs868rCrY3ye6LRbRxcfyNBXRMiRsXAbC/OBW2B/UuBKelRFKv0GOjIqARAq%2BlsjB%2Be0xh0yO%2BOScJh72a6GcahG%2BLa1sLau8sSmO6ANsV2sa5xzBlxaxGI2hgUqA5uOE4eW4pItR5e%2Bata5%2B6Waxm0lWfxyoyWAJ5hiuyu6a3kO%2BAUqaM0%2BxGsZhSYDa1xeOvOD%2BkxpxSJ/xrcnMSu6JbgMhORl21aDhxRYu3uz2cunB2maxxkyxqxzuAOfhWJdh%2BWeu%2BoiRcYrUBuIYrAPI6y7IkRPJlogY%2BIcICIWGKIMoBwGQdSZ8opBozEmI8R92qMCxNyzmqp28/CqK90MoT0RKxAj8zw98mo2UI0pmRYwRfJBoJJeQ6paR5ODGjpy2XJ9I341hVAuMzQAgzpThyO%2BS7o2m3pbQvphIgwxk%2BRnIhRKI7pPhJU80QJKIXAoowQzw/g7o80665cTio2npLwQgXgGQpQ8ClUfo8ob62mJZZZ2QFZfwZodRbSiZp2TA2IKIGgOItkHZpIZgPZzwupKIkge47%2B96CyTZ2c8R2mlZzZxk4ZTAkZ/pPhbgw5bg3ZPRQ5fZKIYxg565A5W565RsgQ%2B5O5bgo5R555Rs2ZyE45oRLwUUis8Rl8oUTM4BHQu680CgTo75QkpZ5Z6Ac52coowFb%2B0yHA2wtAnA/gvAfgHAWgpAqAnAvilg1g/Cuw%2BwWGMIPApABAmgkF2wp0AQkgzoGgyQZgZgqQqQXA/g5FyQXAhYhY0g0FHAkgvALAEgGgGgpA8FiFyFHAvABSPF%2BFCFkFpAcAsAMAiAIAuwBAGQaI5AlAaA3IdACQUQTonAqgyQEMRsEMkgzwwAyA18UgzoZgvA8ChAJAn0eg/AggIgYg7AUgMgggigKg6gYlpAug6ZeMi2GQnAPAUFMFcFBFSFnAHkaICl8oqAVAzw2lul%2BlhlxlzwplZgf0Hgql9App%2BIXAmwvAolWg2wEASAKlGQalZAFAEApV5VIAwAUgZgfAdAnIUClAsQoVYGzAxAmIAVvAHV7QmIHksQ2gTQoluFKlCEHkDAtA3VnlWAsQXgwARoHqBS3AvAWALRRg4gs11ezQNUK1iF08TQaIhwuFEQnIrFiFGIsQi2XVHgWAoV6oeAnFq1pANUxAsQDZ7wG1wAGIRgBF2wVABgT4jEvweMh28FuFdlwgRGTl0gUNblagoV3l%2Bghgxg1g1g%2BgeAsQBSkA2w8GgwK1RsFIP2pgaFlgZg/Fb1EkWAONEA2wjQK5Lg4Y8wfg6ZYQqw1QtQegpQuQAgLN3N2QvNDAYwnNkw6ZDNgwwwcwng3QegEtLQywItEwiQ4tyw/NqtIwSt6wKt9NmFBwEgQVHAsFvFoVAlcVOlelBlRlJlpFaVEAuAVl2VOFeVeF/12w2MyukwdNpAxFkggQzoqQgQzFGgkgZgkgUMGg/gEM6QrF7FpAnFgQXAzoEMXAEMaQDFEM/gkgtFgdEMJtnlAlQlIAIl/1El0lxVslkVillV1VWVGlbAnA7QLAPkhYRsTAMOqNKVqQzoSdB1%2BARA1NtlsgDl4gzl8NSgiNnlugDVvlxoPVhtxtfFvAAlEV8laIzwMV5tCVBlHYX4XA3dvd6VqAmVCQSIMIZgLtBV4lFdtdiONdx9ZVWVKABgRg%2B9XAPFNA2cDmrV7VEQ/VPVpAfVXVg1w1DgAD41W4k101oVc1C1S1gBAD61qNW1iF%2BATIu1fwoVh1SynIADZ1/QoVV1N1mId1hwiFj1z1uFb1H1SgX1yDj4pdgNBkCgINmAYNQoADUNI9sNLl8gE9HliF09KNf1pNVglgmN2N8AeNCpeQhNxNKooj1gFNy9VNJctN9N/QI1eQTN7gMtRQbN4YWtXN6ZPNgw6tmQgtgwRjYtfQAwCtIw5j8tAgUtKwVQytctatejrNMwmtHN7juVOwew%2BtATrFi9ptnAW9ltHde9B9ZFf0DtA9Z9idl9btpAHtWAiQ3tsdHFIAgQ3dIdhY/gqQTFgQod4d2d%2Bd/FnARdJdYlRV5dSAclUVSlVVD95V9dhwTdiVLACgPk18Pk%2B9zoSYSwFl/d1lE86ZXDMNEgcNsgCNAjOguTpAs9/lq1C9IVBd4VVd0VsVqg3TvT/Tgzwz8oEAGVj9p9%2BIgQKTdTElJVbTWVLTt9iQfTZZy0AzqQy0xzy0ezcNTV39EAbVnlQDM1uFwLIDI14Dx9E1U1M1qDmA81i1YgCDL1SDm1ZDa1O1jge1WDqgR1uDL1%2BDF1vARD/VpDD1EklDvA1Dn1XI9Df1NzTDwNoN4NnDw90zY9cz/DSNSzL9aNZNNgV16jSFMjj0nARwc0ij5NlNCQ1NmDuNtjWjzgEArg5j7Nbj2tAtZQeQ5jpjeQ1jKtCrK5LjjjmjRritfjGrGt0thQ3jt0HQ%2BrBtgTWFjroTGzVTHAcV%2BzfT5pRzOE0C9tYzTtyT%2BVqT6TXthtcdnFVFzogQgQ/gdF2d3FsbhYadlTy91TtgxdrtdTRFIAkg/gAdjFhY3FyQkgNFXAFF9e%2BgnAgQbr6bgl2bhVht5labYVDbV99cr1Dm2jkgQAA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_remove/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_remove.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_remove.test.hpp)
