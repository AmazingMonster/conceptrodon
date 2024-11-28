<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSegment`

## Description

`Pagelivore::CognateSegment` accepts an operation and returns a function.
When invoked by a list of indices in ascending order, the function collects the differences between adjacent indices and instantiates the operation with the collection.

<pre><code>   Operation
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> Operation&lt;I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSegment ::   template<auto...> class...
                 -> template<auto...> class

--The list can also be provided using `std::index_sequence`.
CognateSegment ::   template<auto...> class...
                 -> template<typename...> class
```

## Structure

```C++
template<template<auto...> class>
struct CognateSegment
{
    template<auto...>
    alias Page = RESULT;

    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will invoke `Operation` with the differences between adjacent indices collected from `2, 3, 6, 8, 10`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation
<
    static_cast<size_t>(2),
    static_cast<size_t>(3-2),
    static_cast<size_t>(6-3),
    static_cast<size_t>(8-6),
    static_cast<size_t>(10-8)
>;

using Result = CognateSegment<Operation>
::Page<2, 3, 6, 8, 10>

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will pop the last variable from the list and then subtract the new list from the original one. The process can be described as follows.

<table>
  <tr>
    <td style="text-align: center">Original</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">New</td>
    <td style="text-align: center"></td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n-1</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">Subtraction</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub>-I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub>-I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub>-I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub>-I<sub>n-1</sub></code></td>
  </tr>
</table>

We will use `Varybivore::TypicalPop` to remove the last variable from the list. Then, we will employ `Send` to utilize the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

The result of `Varybivore::TypicalPop` will be sent to `Detail`, which performs the subtraction through a fold expression.

```C++
template<size_t I, size_t...J>
struct Detail
{
    template<size_t...K>
    requires (...&&(K < J))
    using Hidden_t = Operation<I, J-K...>;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateSegment
{
    template<size_t I, size_t...J>
    struct Detail
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Hidden_t = Operation<I, J-K...>;
    };

    template<auto...Agreements>
    using Page = Send<typename TypicalPop<Agreements...>::type>
    ::template Rail<Detail<Agreements...>::template Hidden_t>;

// Indices can also be passed using `std::index_sequence`.
    template<typename>
    struct Hidden {};

    template<size_t I, size_t...J>
    struct Hidden<std::index_sequence<I, J...>>
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Detail_t = Operation<I, J-K...>;

        using type = Send<typename TypicalPop<I, J...>::type>
        ::template Rail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMQSGgDspAAOqAqETgwe3r7%2BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5gDM4cjeWADUJrtuXo60hACeZ9gmGgCCewdHmKfnyBPoWFT3jxezwA9AAqcGg44AFRuqTwoloylQqWOENBwMBwOBxwA6h8AO50WjHLxKY4EBB4BTHKheBgObLk1CY7FoelMAiMDkfCkfVLETBKYgAN0w6GOhnFAuQGyU4tSAwUADpAZyWKkDJyzm4CLCuWwAc8JsQvA5jthVJyGOgAGLEWSnJJWJIAETOVmeqsw6s1mG1ao13O1TEuqCV4fux0OTAU1KEmAAjl5GFtSBLQ%2BGlQA1Vp4JgxegKQ1PY2mgjmy2uO2ybXxpMpv3nHPEPMFwWZgG7B6ep2A4798newNa84hoiZiyYYDhBjhYBFrt9gekufHZRMYAfM4u4515P0xtuSfThizozK8Np5utwsdxe7D0vV3uwFen1B0cZiOLo0EE1moQEEuAh6BfT1ngDX1gy/FUfxLP8y2hWF4TEJEURMXtnwfV8IKHKDPyIY4bTwYgJmLUszRhOEETQ7ViNIghiwwx8BxJTIjHJPVPh3QDgNA85O0fDC3Ww8Cnkgj83DHVAiJIiY02k3dMDZdByIQyjkJo5E6Lkgg03jFSmN7Z5WJXDjdVSLddh4oCCBAw96LI%2B8hKwoTcPfEcpNDWSGIU7yDIEdA/PHcMAHleVItT/3LKiUMRbTzkcvSlJUtNwoQeIL1g7snxY5d2OATjLKXfttwrK1bXtQR/T1Zg2CQ6jUIStx0syu9sBAEALMbHLWM6iTOTXDcHN0/TlMCwTX1cnCnjBCElOtVEIQxdzh0Pbq6swdrAQo8t40W5jhLAoFxLwySBsPaT2qjAxYyU%2BsD2CsNw2vfNCyixD9tU849wbbVXrbLLOxyw6TIHC7/TOzyru/bAbpjalQss4gOWyYtWN244XUwFo6BKx08tY/szMK7ruOOJH4lRgR/tzN721h47WKO0STtYiHzg5ryQuy%2BHY0zJ5gAFb1GAIBdevy1cACUmDocnsdx2htUF4W2EEIGu36vVjpZtzZrRY4PGAZhOXjYA1fLNEVtOjz1qhy6YMjaM7splHGg%2Bs0jZNzAzYtqbCcHW3tUyAAvTAAH1ywASTTUOI4ITMACl0YHTGFdlpWwdK4yniJ8H7eDvAw8jzMAGkU7zgUkxIwVjggDszAANnMRuIFLz43GORPlmWfHTIK44AAk8F%2BRhI/J13qYYbUY67gBaUvttZ5nprE9mC4I56lRVzARfViu2NXddN3Jr6asszaGri2jzh3vexfarXirgvquvt44Zbx8506/tw74tjWHU362yHiPLADBI6TTEliY4UdrTwlrqIBgEpaAKBknEY4CpYxikPhxEwjcNA/E6uELAqhw5KAelsfBGgVRZ0Dmtc%2B%2Boer40xsPUeyDDqrzZvnIO5w47j1nvwhO4Zk4v1TupcsbDwHBwIOgYh1pMBkIofuKh5xZ6JyXhLbOAd168LcEIsuB9WJVy8DXak9cIxNxbm3DuXce590lhxH%2BtBx5lUnu7NRaZE4LyXnrPOxMB5kzKmfTmtVWAfFilpVIM8vGPy6trMRed%2Brv0/krb%2BOMM6QOcvjXWM1dEMNCRfcJAsha7wAQfEmxwACynhxRlSkYwZWpT76AKfo2FyIk9ZzTRD0q2mIDZQkFGLJa4JrbdN6b062r4zD7HpO8Dulw6C3CYqtfC3Mt4e3LO4tGrNASVKEF4VIRQxRS0FF4Wg5Y3HIynq%2BASdC5iOGQOHUQTl9FF3jvcCAZhVgsJaI855MZGJ8PeVk7AEBdhz2%2BaQX5qMnkvKBW84uQKwWNznrsH59y/nwgBa8oRnyAAcc9G4YtzuI2FOKEV4q7BAGoc98W909NksSlTTkKHOZc6yhtUDG25L7UW2ptk0zgp1Y%2Bh4zBpl2GmRuaZ8VphqFAk6DzsUI3iAQCARCQAKHCeHGM2pWXsv0oc456B9UXPuL3VmHBVi0E4AAVl4H4DgWhSCoE4G4aw1hjhoI2FsU4MyeCkAIJoK1qwADWIBbWSCVBoSQXAki7A0LajQTdG5mHxbKm1HBJC8BYIkDQpBHXOtdRwXgCgQD5qDU6q1pA4CwBgIgEA6wCCpEuOQSgaB1R0HiJEcJnBVD4tRY3SQxxgDIGQMcKQSozC8DFIQEgI89D8EECIMQ7ApAyEEIoFQ6gq2kF0FwUg%2BIUapE4Dwa1dqHXBpdZwUKlwW3llQFQY4/bB3DtHeOydZg64eE7fQYgfrdhcGWLwStWhVgQCQB2uEf620QCg12hIwApDipoBczKlAYhXpiOEVoNxT28Gw8wYgNxQoxG0MpStAaO0W1CgwWgeHd1YBiF4YAUlaCoPw6QLALBDDAHEIxmuDJRRlt3Yo5SlxtgBvCJyTNzrrgxBRsRjwWAr1/jwLm7gvBRTEBiBkTA2MeNGGuEYYNqwqAGHnFmPAmB8SU0dQGpdwgERrukI5rdagr37v0LxlAHrLD6DwDEMtkBVjIkaCJuePxtymEsNYMwRbtMtiwMFiAqw7AUeyC4a00w/AHtCOEYYlRRgHqKFkAQOW9ClcaAsEY1QegZYEP0KYnhOh6HSwyRrkxBgFcWMV2wXWKsHrmG0GrRXqhpfWJsNd56OD2oLVe4tz6B1ErfWOidUav0QFwHO/9ewgMgdM6sDKTAsAJFS6QcNkhdhKgCLsJIkgY1mEkAQxNjcgiZuzaQXNgGlSNy4I3fFAR8X/cjVwW1t3pWFt4MW0t5bA2mZrfWiDja72tooHB1Av7u29o4K0FgwokhzyYPDDiXAAhKi4NGmd%2BAiBJcXbIFd4h11uaUB53duhxVHqYCezTM25tQ%2BvRwW9zbLjHEfRKYg%2BPCfE%2BjKT8nlONDfsx9B%2BIAHvkHareByDyuEOwfg3%2BkAeOCdz1l0hgINQ%2BB0E5KRDDWGcPEc44R3DpHyMOE49R0WtH6NXqYyxtjHHNNce9Lx/jzr8DSkcMJq9YmZSck49J%2BoV75OKZuMp7Yzq1MaYDdp3TSgDMh7nAj8zG4FBWZs3ZzjjnGcuY3fIVnO7nUc%2B8yZmLVh/PyZS6F1I4XOCRdkdFvzFh4vQ8SyPQU8A0v1Aa34CArhBvBGtKNpYJWMhlZyC1/IK/ijZCX319rjQmvtA37l%2BrHWmhdd33V4bR%2B8gn%2Bv5fiQE2fXTf0Be%2Bbu7FtG%2BlyTwqZOKfRrrm21pwA323h01yO0wBO1GHOw%2BxzRAF2HJxjSSHBySHjUkCeyHQPQFxh1sDh1A2rVrQbSbXvT1x1z/R7TYE4DxyHWOBYAUGFHHWFD/19AmGpx2wXQPSr2cwkFc1kHcwbx0HgMPWPXwz50vQ/xvVRwfSfWoOHToIYOOCYPJxYPLAgB/RV12xmXRQ1zAxrW1yxzIHR311GAYKOXDiUPDhUJ1UlyHUtzQxtwgEw13Sdwd0DxcJIzIwo3d0xxozowYzD0wGY1YzEADwDW4xD3T14HDwyyj1E1UHEzj0DwT1k14GT1wzT1UxbCzy03iFz302DyM0L01z4As1L2s1swvkrwZ24OZz4Pr08yEIMBb0HwCyCwnxdW72yBE2BCIVbziwS3iCS3HxC1P0aCy3cGPz0Hy3KFq0q1X0aHnyqx3x61mKGynzP0P3n33z6AvxWLGzawG0mKG12JmP2KAzWGf0f1f1m3EKLU4AlxYBoPkMYOYO5AmEAJpxIBAOAzALAwgKgLOxm0%2B1zUCCVF2F2FtSTVjQ0A0HBKSAB3fzuJLVwIrUOwuxAEkFtRu1tXxSbgCEkACHjTuy4ElUzV2FuOh04B0JDWuOnURMpORPwJ7lIG00yGcEkCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_segment.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_segment.test.hpp)
