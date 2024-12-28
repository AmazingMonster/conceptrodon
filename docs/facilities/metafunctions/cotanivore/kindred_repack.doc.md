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

Here, we first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<int, float, float*, double>;

/**** Result ****/
using Result = KindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewVessel>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulyuBEwLHSBnBJkCbgIAE8Xsw2AA6dGw7CgybELwOO5uJjpBReeiwqzXUH/QE0w7A6l3ACSkPobEETCa3yO9NpvPOoNB4JZHMwsPhSMYrEw6NRmOxBFx%2BIA0hF0MRMOgAErPJjIADWdxMSSsSQe5IFf12dwsTCUBNt7AtYIhUJFYqFrphcMRyKlMsxd2QBgUXw87IiCVIdx9krR6OwrMYBAUcuuOLxBDuKoYao12vSur1YrDrQjxDFCYhSYU/sCWLrAuNoLuLejLuhou97bd3olKOlGLrgeDXwA8i9iBzcqmrq27un8U9S7Rm62jRTZ3PW15skZoxLDYEHndxwkpwIK4nBDXB/WN3OjWbAhvVy2PR33d2veLfXHZUOg1tG9USuYB1Sra8ZznHcImAO5NVQJh0EPY8lyYOgxVA8C2WTWtsBAEAY3NSlTWIkFLXgzBkE2bIADdMHtJQQCdd83UpOFXzbYVvxjfs8OHICCVkdDImIK5SE41ieL7P1bwEkMhPDUSbEkmS/0rHCrgUKNVN/AdUQ0pMLG03TY300cCAQBIU3YrE0wVDMs1VdUtR1fVi2EssQThQzBC0vCoxLESEisHyrwIYyApPSzrLwxt71bKTO3hL9kt42T/2weSxwnc8GCg1sF0zNCMOuB8mzKrcWxgvcYxQpycxc/NC04h8OMqqq50JYlSWS3yCH89Eo36yLbwkjrOpbCyrOIYDWrXOsCKS%2BDEPQMVT0nJo5WfTjHzIyTUs/bi0rU/SA0AkMZSwzAIOTArqt3OCEKQ%2BqSpXOFrtuubFsIiV9tInbKT%2BPkfipY47mwVRWChBjQeBkG6SdcxAgiIMvCwQ94S8GGZzB%2B4okwAB3AA1T47C5RHriS91Tqu4hgBTBtrnVABHLw8HVL4IGyAAvTBUCoGUICuemFBWFDYWPSQVnlRVMwJkmyYafb4cOO4hGxko80%2BUlMzhq4argjX0i11ySVoTNJbuBXSZDZW4QiAgoyoWhEKdu4Xbd/Yo3QDZYjJBtAfIm5we1c29e5UFDco8P6uzXNXILdz2LcTjJnQJbsYDtxHcxHSJvTzOcbhT2OWd12OX2PO04IDPCKz5Lfa8f3Ozs7z8JAZ61rhG2lfeu8nQZAAVT4I8prTWkcZAAH0gISAhudrgiFClWfGbcMPdajY3Tc3i3MRl58ODWWhOH8Xg/A4LRSFQThU8sax5w2LYGORnhSAITRj7WPUAkkVENAAA4zBmBSCkLg/ggGAK4EkJI0hT4cEkLwFgEgNAaFIJfa%2Bt8OC8AUCAdBn8r7H1IHAWAMBEAgA2AQdIXgnYUAgGgSEdAEhRClJwVQgCABsABaThkg7jAGQMgO4UhURmF4BqQgJA8AZy4DIQQIgxDsCkPI%2BQSg1Bf1ILoORhNJzpE4DwE%2BZ8L6aOwaOWhNDMwCzuBwnhfCBFCJEf/MwdwIAeCYfQYghozCBC4CsXghCtBrAgEgRh6RmFkHoWEiJIBgBSDMHwOg4JZqUFiJo2IEQ2gIgMbwDJzBiAIlHLEbQVFCHv0YThUcDBaDZKIaQLAsQvDAEJLQWgeDuC8CwCwQwwBxB1PwOqBweB6LtOvpgVQVFaE7Hfo7BomjaB4FiJOApHgsCaIVHgFBHTSD0WILELImAnjdKMAsowX81guyYAzYmHxCankvu/fgCjRDiBUU8tRKh1B1O0foHpKBrDWH0IsvBkA1ioHSE0dp3D06S1MA/SwZgsG7OIDIz48A1h2FKbkFwOYZh%2BDkWECMSwxhyJKDkAQeK9BkqaIsUYiQ5GYqGQIAY0xPBdD0IypoLKhhErpRyqYHQ2WFAZQK2l1QSUYuftsCQRiODnwwaYzgNiuG8P4YI4RoiXEQFwFIrxb9/Ef3OWsKySExgQB/iASQgRUQpECHAjQkgzCSE4Wg/wnC0gIKQaQFBvjUScK4JwwBKRoGcP8JICBtrOEKrqdg3B%2BDDVEOCeQkJlCLG0PIJQaJnjWFsE4G0FgtEkjcKYAJPcXAUioi4AAiR%2BAiAotkaoxRrzpDvMUJ8zRugEm6KJDk2V8rMG8DMWmqxVBlV2P4YBMtFaq0aFce48JnjvGBDMAawJxCU1ZsjFE1AHixiTrieA9BNALbWVSekzJBScmkDyVkopJSHBXoqUmKpNTNENKaS0tpV6uk9L6dfAZWKRmaPGZM8EV7ZkIOvgspZWTVk7GvhsrZ79dn7KUEc39sFzl8AMNc259yr3vKbcoltsg20aO%2BSABJBgzlwqsJYIFsQQXmpvhC3IUKYVHlo9YRFg7kWoqYxihoWLnAQFcJSglOYxXLFJVkcleQhX4oyLJmlvLxX0t6MJ5oArxMaaZVphYqnpO2G0wp/lBnKh8r8esTY0qrMIP7YqjgY7VWlrguWytADXE6rrUuvxASjWkBNVgRIzHPXIJAIECtDqkj%2BBSLAwIjrnXhujVgzgcaCFYdIRQqhliM0MJ3QulhbCOD5vsSwBQtFhG0Xcx2SYNbdUyL0IRl5xHVFka%2BdfXQwRu36I6X2kxMbODmOobQu41jVBlYq1VmrIpJhzoKxEpdgRV2ZdCQtzxeXN2JEqybae1WUjT1qwQaeE2W1JNPRANJdSb2Xu2TdwpxTSmPp3ZU6ptT/2YEac0sQX7tk/pOfBzpHNANorqSB6iYHtkQfmYs5ZCI4PrJRUh3gKGDnoZOZhxN2GrkKBuUTfD2zmtKIkCRwQ7WO0Rd%2BTRgF9HoMCZY5CzguxC5cYRUihI9a0Wgt000HF7hTMSfQFJklSnSi5B09S3Iwv1Ocv6CZgoinZfMtFYZkX8xWUK7M%2B0aXMrrMv11/ZgbqWnOnbuOVyrdx9uoiO152tJBfMrcTcazApqQuyq9Sg0BqJAiBH8JA8NaCfdJEDSlwdaXbDxrXSsC1kh/A2pgUkNBgDJDgK4MAswUaEGBCN2HnBCagmyvEaHm%2B4eo9rF2dkZwkggA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/cotanivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/cotanivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/cotanivore/kindred_repack.test.hpp)
