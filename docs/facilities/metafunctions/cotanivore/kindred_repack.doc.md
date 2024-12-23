<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::KindredRepack`

<p style='text-align: right'><a href="../../../facilities/metafunctions.md#cotanivore-kindred-repack">To Index</a></p>

## Description

`Cotanivore::KindredRepack` accepts a list of packed containers and returns a function.
When invoked by an operation, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
/**** Operation ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, float, float*, double>;

/**** Result ****/
using Result = KindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::KindredRepack` is implemented similarly to [`Cotanivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Capsule`. After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** KindredRepack ****/
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<typename...> class Container, typename...Elements>
struct KindredRepack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct KindredRepack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulyuBEwLHSBnBJkCbgIAE8Xsw2AA6dGw7CgybELwOO5uJjpBReeiwqzXUH/QE0w7A6l3ACSkPobEETCa3yO9NpvPOoNB4JZHMwsPhSMYrEw6NRmOxBFx%2BIA0hF0MRMOgAErPJjIADWdxMSSsSQe5IFf12dwsTCUBNt7AtYIhUJFYqFrphcMRyKlMsxd2QBgUXw87IiCVIdx9krR6OwrMYBAUcuuOLxBDuKoYao12vSur1YrDrQjxDFCYhSYU/sCWLrAuNoLuLejLuhou97bd3olKOlGLrgeDXwA8i9iBzcqmrq27un8U9S7Rm62jRTZ3PW15skZoxLDYEHndxwkpwIK4nBDXB/WN3OjWbAhvVy2PR33d2veLfXHZUOg1tG9USuYB1Sra8ZznHcImAO5NVQJh0EPY8lyYOgxVA8C2WTWtsBAEAY3NSlTWIkFLXgzBkE2bIADdMHtJQQCdd83UpOFXzbYVvxjfs8OHICCVkdDImIK5SE41ieL7P1bwEkMhPDUSbEkmS/0rHCrgUKNVN/AdUQ0pMLG03TY300cCAQBIU3YrE0wVDMs1VdUtR1fVi2EssQThQzBC0vCoxLESEisHyrwIYyApPSzrLwxt71bKTO3hL9kt42T/2weSxwnc8GCg1sF0zNCMOuB8mzKrcWxgvcYxQpycxc/NC04h8OMqqq50JYlSWS3yCH89Eo36yLbwkjrOpbCyrOIYDWrXOsCKS%2BDEPQMVT0nJo5WfTjHzIyTUs/bi0rU/SA0AkMZSwzAIOTArqt3OCEKQ%2BqSpXOFrtuubFsIiV9tInbKT%2BPkfipY47mwVRWChBjQeBkG6SdcxAgiIMvCwQ94S8GGZzB%2B4NryrlEeuJL3VOq7iGAFMG2udUAEcvDwdUvggbIAC9MFQKgZQgK5KYUFYUNhY9JBWeVFUzAmtsB8ibnBoRsZKPNPlJTM4auGq4IV9IldcklaEzYWT1y6W3AiAgoyoWhEItu4rZt/Yo3QDZYjJBsZbxw5KP1tXuVBTXvdV%2Brs1zVyC3c9i3E4yZ0CW7G3bNwRMR0iaY7jnG4XtjlLetjl9mT6OCFjwj4%2BS52vFdzs7O8/CQGeta4Sl6d3ZfeGvYAFU%2BX3ia01pHGQAB9ICEgIVmi4IhQpSH6m3G1H2o213W59VzExefDg1loTh/F4PwOC0UhUE4KPLGsecNi2BjkZ4UgCE0De1j1AJJFRDRJC4JJAg0fwNDMAA2P%2BZgAAcQD9CcEkLwFgEgNAaFIHvA%2BR8OC8AUCAWBd994b1IHAWAMBEAgA2AQdIXgLYUAgGgSEdAEhRClJwVQQC/4AFo/6SDuMAZAyA7hSFRGYXgGpCAkDwLHLgMhBAiDEOwKQIj5BKDUPfUguhhEAHdJzpE4DwTe29d5yMQaOYhRDMxczuHQxhzDWHsM4S/MwdwIAeAofQYghozCBC4CsXg6CtBrAgEgch6RKFkFIT4vxIBgBSDMHwOg4JZqUFiHI2IEQ2gIjUbwOJzBiAIlHLEbQVF0E33IThUcDBaCJIwaQLAsQvDAEJLQWgKDuC8CwCwQwwBxAlPwOqBweB6K1IPpgVQVFiE7BvubBocjaB4FiJONJHgsByIVHgKBdTSD0WILELImAniNKMGMow981hWyYFTAAah8RRp494334KI0Q4hJGXOkSodQJSFH6CaSgaw1h9DjJQZANYqB0hNFqQwmOwtTCn0sGYBByziCCM%2BPANYdhsm5BcDmGYfhhFhAjEsMYwiSg5AEKivQuKmiLFGIkYRCKOkCAGNMTwXQ9AUqaNSoYmLSX0qmB0WlhRyXspJdUbF8KL7bAkBojgO84HaM4EY%2BhTCWFsI4VwqxEBcD8IcdfVxt9dlrCskhMYEBH4gEkIEVEKRAhJEkG/Mwkg/4wP8H/NIW8OAQNIFA5xqI/5cD/kAlIQCPX%2BHfv4E1f9xUlMQcg1BGqMGeNwV4/BejiHkEoIE%2Bx1C2CcDaCwWiSQGFMAEnuLgKRURcFfrw/ARBoVCKkWIm50g7mKAeXI3QYTlFEiSSKsV8DeA6LjQYqgUqTEsMAnmgtRaNDWNsb4%2BxjjAhmHVe4zBMak2RgCagOxYxB0hJSFwWBNADbWWibE%2BJaSkmkBSQkjJWSHDHryUmApRS5FlIqVUmpx6GlNJaQfNpiKulyN6f08Ex7hkOoPmMiZCTpk7APnMhZN9lmrKUBst9sFdl8AMEck5Zzj13KrRImtsg62yKeSAMJBgdmgqsJYT5sRvl6sPv83IgLgVHjI9YCFnaoUwuo/ChoiLnAQFcAS9FOZeXLBxVkPFeROVooyGJ4lLK%2BVkt6Dx5o7KBOKcpcphYcmRO2BU5JtlmnKispcesTYQrjMOvbRKjgfaZW5rgvmwtr9rHKrLVOlxbjNWkG1VgRINGHVOpdQWt%2BSQA1JE/pIS1zDhEdsPpwMNaDkPYLwQQ/RCayEronVQmhHB02mJYAoWiHDaIOY7JMEtKrBF6Cw9cnDUj8OPIProYIzbVF1LbVokNnBdGEOIXcQxqg8sFaKyVkUkwx0Zb8VOwIs7EveIm/YtLi7EiFZ1gPYrKQB6lYIAPAbNaIl7ogDEkpp6j2LJO%2BkzJ2Sr0rvyYU4pH7MDlMqWIZ9izX1bIg/UpmX7YUlN/dRf9izAOjPGZMhE4HZnQug7wWDayENbKQ5GlDByFDHMwKc5EmHZDYYkLhwQ9WG0gGCCR4w7yKMgc47RgFnBdhp2Y%2BCyFCRy2wp%2BWppoyL3B6cE%2BgYT2LpOlFyKpoluRecKYZf0XTBQpPi6pTyrTfP5g0ql/p9oovhUmcvurizHWEGSt23cfLhW7jrdRFt5zpaSBuZm5GrVmAdW%2BZFQFojBbAiBH8D/d%2BMDXdJE9cG3XSDbDhrnSsfVkh/DGv8EA/%2BKRJApE/qargxPOCBB152uLEaPEip4X7tPAfg9rGWdkZwkggA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/descend/cotanivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/cotanivore/kindred_repack.test.hpp)
