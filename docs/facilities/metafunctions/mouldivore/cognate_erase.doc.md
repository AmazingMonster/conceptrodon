<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-erase">To Index</a></p>

## Description

`Mouldivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the element of index one from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateErase<Operation>
::Page<1>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = CognateErase<Operation>
::Page<1, 3>
::Mold<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

- In the case where the second layer of `CognateErase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Operation<FrontTargets..., BackTargets...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateErase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted elements.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the elements we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Operation<FrontTargets..., BackTargets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZiSEWQ3iwdxMSTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bCkg87gRiF5MHCrNdQf9AdrDsCtXcAJJs%2BhsQRMJqM3WanU284Um5Uh6EZAIS1264s43m1Xw7m81g%2BjHXSbKhyPZ2ukyBKyBB5q%2B2e9neglZABemAA%2BgQAHS5g2iq4hrxhp0EF0pgjoEAgCJYVQZpQARxVEoJBtz2fJSSDIOjoLuA8VrKTnOug7lbn748HiY5PrcfsYAY76LuUKYCi%2BAHkXsRzTlSFPp9K6XhVG30R2AGLEWQAFTawEwBAUh7Hx8VPKX/KP08XfMwDsLCYZAAGsH2IJ8X1/Atx3mRxkDXARJkwAA3MRBWFO48HQFFaAgFZfwAWlXHcEn3AQCRve9H2fBQOwFYCwIgqD6NzLt1V7OMkk4617mwVQ0i8IxMDdZlhznLkvwAgV/wDAsizDAShJE2E%2B1jeMNQ9CTk3hNNMxzPMBX0rMOwAKQUpViylZThKfCsqxrBg6wbTBmzeed23Y7tjMrata0wesmxbbYCTMlduwLKNOPHWdk3fAcCV/WKdM5X1pOXbzsDXAxNzuMi9yaN8rg/O5dl2O4AHVRK8JRYQANg0GlT3PeF827FdGsVVA7lpEDXQIBBRPmdo7lQKhFSGu5hIAd0MFl0DuBpWUYF9OwS6dmvpC8OtzajBBYujitK8qqpquqTEarazzCy92K6ogloYHxyJZSbROW00XzuGbRLmwRuqWvclHWkqP2u1q3As3bs2Oj85LYICQPA2joI22DB3gvBEPFFD0NoTDHpwvCCOI0jdwohgqNvA7UbY2G7iYlHILoiKMR4zENI5rSHXuDxgGYFlsGB0SflBOK0oXVL5wRwCspyjdtwpppLNDKV%2BcFnARc5mKZ2llM8HTUyst/RSpRpVAiGUJgnzUmNuN4jaJfnEypQNZzAoxgczelS3UGt%2By2o91qe3HaLkr1r1JdljtsBNVaFC96daoiYA7gAWU8Ra4QVLAoUXCOBwgQvp1Lcs9L8kAWCYUDMwCoK3JCzzg67UPSsHatnew3DaAJArKYFOOVsEen0VJjbx0I7mwcSrnHZnoco5dw2DLuAZ2mMleszubBnKT2lmzwWkvggdepSS%2BUd%2BcwiNp9i2rZt%2Bcz8HvfIvRvsJ8jkcZYyxHcyHr6ic34L3HCnIwGcs5ylzpgfOX4S7F0/seWyIkHLVmrrXDM9dXLuVbPCM%2B6JfKOXQXXYO2Cm4El3ugIi%2BDIrAPbh3EAXdia93hP3IqO944jzZuPEBg4p661ng7e0KUl4EiFEQDsVxgC0mHtBOhg4wFpwDqJHOvsH6BzcFImRgC2aaS4novitoAR6ipFeI%2Bkwd6qFYOyUWTJDFGNOMCTE4JITQhUfCcU2w0hyJ7PY/KyschiXFvrdK/o/6dmAT7NhOQDGUnuEILwaRiiYHQAAJU%2BF4WgUoxbXEUWvRJyS0kZKyVA/xr0YnwgiAQAUVTDg1MEIcDi9p9Tp2fEwKgwkHCBJyVcZ2Ukwly2zFcSCQCex5Naa0DpOILSqI1t6YWG55zRMosA6syiCRcALNWTOtB0AEmGcAUetD576nSQoTJ2S7G5KyOAs5FzSkTPaZ0lWlTBD1IIPsd5dTsINP2E0nm%2Bo7yfEuVaYMrQEIZkVgkAgEBiTVgUAGSFQC3AJKSZkFJdyskCkxQQdE/DmkOMBCY%2BJMCBCLQEtY%2BgQS4mEscQS%2BJBT0VFPOSUnpeTUWFJxRmLgpTllU1edUn5Hy/nHPpYcDObSpldIENS3pISFy/0GQc0ZoJxmSueTkblpS5lC21qwgJKyexrMfhsgUSQtkgB2Xs%2BEyrdHTz8Ti2VeSuU8tUY8qVTRuUEiqV8r5nyhWNNFQCqkQKLE9KxsgJFSh2iwsrgitgSKCQcqZS67FxSCBeu7PwjgaxaCcH8LwPwHAtCkFQJwSclhrB3AUBsLYKjwQ8FIAQTQOa1igQCJIbMGgAAcZgzAAE5%2B1cH8D27tXBAiBGkHmjgkheAsAkBoVIRaS1lo4LwBQIBUjNuLTm0gcBYAwEQCADYBAhLVIoBANAbI6AJCiAGTgqhu31SIvVSQdxgDIEQlIbMZheApMICQHCeh%2BCCBEGIdgUgZCCEUCodQO7SC6C4KQGae40icB4Lm/NhaW2ls4FuREZ6xoTUfc%2B1977P13G/WYO4EAPDXvoMQWEDaVi8G3VoNYEAkBXrSDesgF7uO8ZAMAKQZg%2BB0BZMQDdEBYg4diBENoKJ0O8Dk8wYgKItyxG0DA7djar1fS3AwWgin4NYFiF4YAbgxC0A3dwXgWBq5GHECZo%2B2m8CoU%2BDhwKMDEQ7EbVUhoOHkSxD3GpjwWAcNKjwPO2zpB3PEFiOip4DngDIiMC2tYVADCHIAGofBmmRItjaQPCFEOISDxWYNqBw4h/QhhjDWGsPoPAsQN2QDWKgbxOQbNEWJDnUwlbLBmBXXF4gOEPNtd6K55wEBXAzD8EhsIEQRhVDGEh4o2QBBzb0OtpoixRg1Em9K5oUwOieC6HoOwU3jsLCW0sVbtgTtbaQyNIYt39sSDWDWzY2wPv6Cw6QZdvBV13BIy%2Bt9H6v2duoxAXAAHGNYi4Cxpt6W1hDSYFgRIBFSDtskEkbM/akiTo0JIMwkhGoaH8PVftf2Z1zpAEkLg2Z6pcHqt2/tY76r%2BEkMOgn9UAc4dXeuzdyOd0ccPZx49BHETkEoAJhjd62CcDaCwVCgQiJMAVuArg/bsyM5Lf%2Bogo2qxIeK2Bsr0gKtKCq/B3QomUNMDQ7ZzDHAC38/g6u/Dp7EREZB0%2BsHmu07a9112mjdGeMMaY0kMwSO2O7ol3LhIMvL2oHo2MdcRhtdcFSDQLJCQpMyfgyphTSnSBF7UxprTDgS96dWgZozOHTPmcs7QazJf7N1acyW/AtIunuZs/r1Q3mWQl/89OktQWQsojCzsEtkXouNriwlpQSWO%2Bp3S3wLLChcuYHy7yEvpvSsQYt7ISrcGS229q2l/rVhLBNZa/AdrnXkKcB65WPrDXBvDYSEb8bWPLtHZcGciexCGcj2xWwOx2xyGAMgLKDe3AIu2WiOzPmAP/yaDPjAOWGe0ezOwKCwJuwqHe0R3WG%2Bwg2d1d0B1ww4F91IzfXT0Dx1z1xo1h0N0j0R1YxR1IDRwx0oGd1nVIHnSSB12J0CH8H7QnSSBJzJ25zdxXU4CFy3XX33SPRPTPSTwT2IAVx2GVzIxYAUFQkQlQiDznEmD/XwENyAxN1kDNyPyg3kCtzPx0Hp2Q1QyUzIOw3dzwylylHGhBx0L0IMKMO9AsVoxT3DwSEjySBj0UK41CN4zUNiIYxAH0KSQzEMP7QzGMIzVUFfTE1z0k0oALxLTL2M0bWKIr202rxT300M2My70wDMwsysxs0bXb0cxnzsxc17w83gy82QB8xH0EAC3gwnwU2nwi1G3n14EX0S1ZFXzS1Fw3xti3zywK33ysMPwkGP2g3sOqycIMCvw/xsCC1ayxw6yaBs12DhWv2sCGyBxGzGxOM%2B0QKaEAPcBwPmxAPQAwPuxgNyHeO20yA2wYG%2BIO1QP6GwPyA%2BLBIEHQLgMwIe0GBQJOxBN%2By%2BzrV%2B2nXIIF04F8LfV0P0LuDSOzEyKYLMJIFYKiNF1R0wHRzGCx2nT4PnQHWzCSCSH8BHW50XVZMCFZxkKBzkNsGF1jxWDbRAEkH8Hx3HUCEXW7UkCHS4F7TMD52nSSHcNkLXRF3Y2d1/T5MoPYKpNizzxyDFKAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_erase.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_erase.test.hpp)
