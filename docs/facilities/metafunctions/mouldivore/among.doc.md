<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-among">To Index</a></p>

## Description

`Mouldivore::Among` accepts a list of containers. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the container at the index from the list with its arguments and returns the result.

<pre><code>   Con<sub>0</sub>, Con<sub>1</sub>, ..., Con<sub>I</sub>, ..., Con<sub>n</sub>
-> I
-> Es...
-> Con<sub>I</sub>&lt;Es...&gt;</code></pre>

## Type Signature

```Haskell
Among ::   template<typename...> class...
        -> auto...
        -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will pick the container at index `3` out of the list `Con_0, Con_1, Con_2, Con_3`.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<auto...Args>
using Metafunction
= Among<Con_0, Con_1, Con_2, Con_3>
::Page<Args...>;

using SupposedResult = Con_3<int, int*, int**>;

using Result = Metafunction<3>::Mold<int, int*, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the container before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual container in the list.
It is not quite the same as the actual container.

```C++
template<template<typename...> class...>
struct Vehicle;

// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the container at the index is returned. Otherwise:
  1. Drop several containers from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<typename...> class...Containers>
struct Among {};

template<template<typename...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<typename...> class First,
    template<typename...> class Second,
    template<typename...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<typename...Agreements>
        using Mold = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Mold<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArACcpAAOqAqETgwe3r566ZmOAqHhUSyx8YF2mA7ZQgRMxAS5Pn7VmPbFDA1NBKWRMXGJKQqNza35XLbj/WGDFcP%2BAJS2qF7EyOwc5v5hyN5YANQm/m7IY%2BhYVKfYJhoAgvcPBJgsqQavp26v75%2BY3wIAE9UoxWJgAHRQ25HA5MBQKKEQjyCJjzYgKW7PMbELwOI4PFgCYAnADsVlJABFTlZHs9fh8mF8zgz/oCQWC2EiYXCEUcAGJ4DEELGPHF4ggEolGb6C4Wip7k55HFVHVlMgFnTIAL0wAH1JQBJBWqo7i/HKYioIjKJjATBkinU/y0p6PU3q5luHX6o0m1XETAARy8QswCiOEGN/mdlI0y2VqvNkst1tQtvt32jd3dqpMStzppVns1Pw5zC5UIewEDb0YBEx/hzDyLqq8mSMRwAsp50CcYwKhWNvtXa2xBIjoU2aYmVfnna7Z2q3oyvUwvEQkaPMHWJ/6Ve2wiSMw7TpSjqmbXbS9vdw3udOXc95zO6Y8S8%2BzkuPyzy%2BCH9gsIGHycpjKQ34rmyv6ghWkJToBvIRkItQCOg4GFsufwauyMH/vBQHwpOEIAPIEAgcSYnS05igQuL4oSxKykOBCkEcyFoAwaFHKR5EYgBz4Fi2qo/t6eC6gaRzZkuyYXlaV72icGH5q6rbFpB2HQZycEQre44NvuRaHp2Pa0H2Z5SoxZw8RR/EYaaIAgCWslpieWZHAAtEcZgGfZjnqa83a9iONY7npRFYk%2BSlUq%2BbpCWpWFej6ElSRhgYhmGEZRmeZ7xtJtESs58mlilcWOkuHr%2BaWwK4ZWOkhXejbNqpRxGSSJlmQOoEimcun1uFj4qXm0WRbFFUJaWSV%2BtRpVpaGgaZdGsZcAmGEyZe6bXlmBnKeVwmVThWlbvVYU%2BW2HZtb2/bnuxqHBWOfX8SNpoviNEHjd866blWx19QZrUXteV2FRtmY9T9E6PYuw2Lo8AD0ABUiNI8jKOw88CNI0cAAq4YNkcyNo3DKPEwTz50mYewMAcXjHN8HFbKk%2BnTfS%2B2abBtkPDJKJ6hoMUs%2B9bN4RCCpcwIepcHz76s2WNXaSL%2BX4tz3mvVLAsy4d8HYgrkrc/4ksPBjiODsKRzYKorAfA6pNvi80ufagW7EMAjXPP9XaYI0VBeFT3SfueDEymc3MaKx3PTEcSuh2LevTQ5rk9U7/V3CrDz/UIXipIUmDoAASuGXi0JK5m698YQsUcZfw6xlfwxFMOp%2BdRx5woBdFwO7ue97dQCN8MfYA57Wl4I1eCFXFej7XA1k5zjSOMgeqEXEBAQJcDkKOCC%2BNm4zet6x6eZxk2c74XtwJinhvw2xKGcab5t/FbSOE7FIkv3%2BtU8sBSda3RkoAGqYAgPABxNT11hrDI4ABxNwbhYSoHeHQcMws4bgLcAYTshg%2BxdiEL/GBVA0S0CQTPJkQDN5KGaCvAg6A14b3hN8Jc/9AHAO%2BB3JgXsfbZF7rcAeQUmzoVKgwoB9Bvgl2Zk2M%2BoCUFoJJBg7s2CYFoHgfQQhYDIHQKOHgugiItbEPnovchDBrRmkodQtgm86EYQEUws4LC2HdwYJwps3DTK3D4aaSxQig7RwVKfGKHBVi0E4AkXgfgOBaFIKgTgbhrDWDNOsTYp4KY8FIAQTQfjVgAGtEiSAhBoSQXBST%2BA0AkDQZgABspSzAAA5Kn6E4JIXgLAJAaBDiEsJESOC8AUCAEOKTQl%2BNIHAWAMBEAgHWAQVIG5yCUAUakBBxAIjgk4KoSppT3KlMkEcYAyBkBHCkBCMwvBs6EBIHgKh0x%2BCCBEGIdgUgZCCEUCodQfTSC6GmAAd2IEwVInAeD%2BMCcE1J4TODEQ3BMyUqAqBHGWas9Zmztm7OyWYSMHhFFxBOIk5YvBelaFWBAJAMy5lTIgAS%2Bg8RgBSDMHwOgrwMSUGiIC6IYQmhAh%2BbwRlzBiBAmItEbQtRelJIUXpYiDBaAsueVgaIXhgBuDELQLp3BeBYBYIYYA4hxVhjqAAN3DICzAqhagbm2EksunRAW0DwNET5nKPBYEBbRPAjSFWkG1cQaIh9KRvBVeaowqTVhUAMM7X%2BeBMBvOIjBVldzhCiHELci58glBqEBa8/QKqUDRMsPoC1XTICrFQIzbI8r3KXDPKYSw1gzBtJdcQU5Oqc22E6Hy7ILhOKTD8NMEI8xyiVAKBkLIAhW09qKNkAYXbhjTBqHY3oExPBtD0BO7oU65hlCGPEcdswB1rr6COldEhVgKDiVsXdtSOBBNIK03g7SoUrLWRsrZOy9lIogLgY5xB0X%2BGWli31qxyJMCwPECAGSQCSH8BCJI/hSSSFyWYSQpTmkJFKSkAJHB6mkEae%2BiEpSuClMqUkSpWGEh5OSP4UpZ7AXtM6d05JvqBnDLxaM0FkyKDErgbM0lCy2CcCaCwTVpJ3JMAIp2LgSQIRcByYc/ARBq1nMjVcmN0g40PMTc83QlKPlfNZX8k9ALnntJBeMjcRwIVHC4zxvjAmSRCZEzk5FLG5lvrMJiqjfTcX4ts6SolJLhgmd43CIwQmuAhxoIXCidKGVMs5RG9lzLuW8ocBGwV9ZhWisBRKqVMraByojUqr12wwn4EDFqnVzy9UGteBGk1SGwnmstcym1uWsXVsdUkl1bqlAeuVUYb1oBnN8ADQoINIaw2MAjXG2TNz5OyEU08sJKmU0%2BtLVYDN1Xs0AfCfmgQhbi0xgW%2BWytcQpO1tW/OptEBXAbqCJxbdixV1pF7d0c7hQ%2B0MCu928dDbJ3rpnVMetXR6izBe2OmYfRztjC3Z2ndy01gbEPZDpDp7z1Ao4MZ4g3HeP8d8xZ4TomNCRmfZJt9H6nM4u/ZgX9wxVtIZQ2h4TuTSTJFJAUyQ0H1nTAR%2BR2wlHsX9MGSMsZYKPNubiOx7YXHYUsAUJqnZmrLP/DGOJl9py9CjejeNyNU2k0BFIGp75CrNPw7I8Chj4LIWi42eLyXRxpfCdl5KCAKLWNot2CsT9PW6OebIEx93IBJeZz1FbvUNuF4o/WVS4LtKID0ueVFiLTro9cp5Xy%2BLcChUirFXlzAkrpWyvlUk7LnX6ukHy427V8qwkleQIa8rghTXPOq1aoEdW7WNYjS191nrOtHmo/6u0/Xg2hvDU65X1yJATfuQm6bOhNdSLTWWpbWb4C5vWwweVsNV47csBWi9Vaa0rb3e97ozb3BfbbRd9AAObuPfu8fwdT3z9zv3394H1%2B3u/YEIuu/m7p15BP6D5oH%2B90Ho3J67aZtKcDI4sBi4S5S4y4ahjC44SYkAE6OZc7LAk5k7/qaZU4gBmDCb%2BD%2BAJDFJ5LNJ4GkjYakY6acAUY9JfqkCZKSAJCgYJCVJlJJCSBJAFLgZcCBBIb%2BAgEXqUFE5pLHoHLkGgEdKCGoHOoURNqSBAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/among.test.hpp)
