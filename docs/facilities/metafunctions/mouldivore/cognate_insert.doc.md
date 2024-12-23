<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-insert">To Index</a></p>

## Description

`Mouldivore::CognateInsert` accepts an operation.
Its first layer accepts a list of elements.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided element list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             E<sub>0</sub>,
             E<sub>1</sub>,
              &vellip;
       E<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, E<sub>I<sub>0</sub></sub>,
       E<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, E<sub>I<sub>1</sub></sub>,
              &vellip;
       E<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, E<sub>I<sub>n</sub></sub>,
              &vellip;
             E<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert
 :: template<typename...> class...
 -> typename...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will insert `Vay<-1>, Vay<-3>, Vay<-5>` to indices `1, 2, 3` of `Vay<0>, Vay<2>, Vay<4>` and invoke `Operation` with the result.

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
using Metafunction = CognateInsert<Operation>
::Mold<Vay<0>, Vay<2>, Vay<4>>
::Page<1, 2, 3>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<-1>, Vay<-3>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateInsert` by combining `Pagelivore::CognateSegment` and `Omennivore::InsertValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.

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
struct CognateInsert
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...NewElements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::InsertTypes>
                ::template Mold<NewElements...>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9lMRMDRVH9TmCCJgWGkDOziQR0e9mGxSI8sgAvTAAfQIVLuaHxbwIdIZTIRgWejwIxC8mERVjuEKBR0ebiYaQUXnoLJObI5XKYPKRfIFrEwADp3TLbgstQ5jabzfRddT7rTsKp2Qx0AAxYiyK1XCHszncnWO/mMF2e71eX1hiPR2OCBEAdisxeeQf1dyTdodbhrKd56cFbo9gWwj1hTAUvw8giYyzIGubLvdruw9DYggUWc1OcVedcMdkxL7LUHxInHMYBAUY6p7ZxpYhj1PGttjbTzrYY4smGAEQYEWAM8PdzPjy8WSMjwAsp50FVdU1wHSJiGJO8HwYJ8jD3d1hS3Kdd33Q9Aj1cFy0rcFqwve1U3rXC6yYFFUBQjsux7R4hEwABHbV5WFYiiDHAA1Vo8CYWJ6FfbE7mzXNwyXQtpSRai6M%2BfC2OIDiuJ%2BMjPRMY93zPBs8OJJjSPdSDH2fHiTzPL9nzpJhgEwICqNo%2Bi9gg%2B8dNgsdhSkmTuPktCjwrNyqxDJ4AHkpyfAA3Eh2BANwDB7PBkH/fAqHRAAVdNfn%2BCEWwUNImD2R4/MYQLgpLdDE0I/CnQzG8214r0519ABJBglDaBL3l%2BRSyw8gqaSeCxuzMk0lHjG1kzUpENLHarZx9RVavqghGp%2BYkyRAEAIiwVQJSUcT5WJarXIqlr9NPVS6xKltHiiTAAHdEJ3YVjtHcr9pFKrFXpVAiH/Wh0AevblI/A6ioej9iQB37TwOA5HgAdTMr8zJMAA2DR6UZPBVC2rF9wRjVUEeRgfASPCEQR5dBDi1pTN3eGNFdYGQaRpk0fbMdiZmsnMF3Ugad%2B26ytdLrkAAa1J4hyZnH7fs9EHTwWe1Is7AQFkwAKxEeDTHjwdB0VoCB1k5gBaLE/TNC0dTFwGkU5j9maFkWHIts8zsuydrrt08%2BcF1nkI9U2zwPdrbkl89BqOkceduYAGW3acJclwyf3ewDEXVLBYRKiB1c14kw4jpC4Op9ttZ1zz/Z9zCi4ew7ipD1tXSzzBI4pt9i9PWPgD/ADzJet6AMz8O65z1yCtLv2K/UkjRsYsf3QAKXG%2BdHimhIZsS%2BaCHQRblswVb1qs/DtvK4UFqWyNN7WyyJOJKedqPdCPxHq9SrMqM8GIBYHauwQbqriy5XQN%2BnY/4c15q7Rylk9JUr1UDxy%2BkpJuXN/re1PEDBBv0waQ2hn1SmdMUYM2wBjDQWMcYMDxsQAmlMrYexnAjamyCPxYNRkiMajN3TkOFmzBQHMaFnlQVDT8GCEZ0IvujD0mMiCPGANjDKsZKIEAQGZfA0tNqcNBuDeIBBzp1wYBqc62Npg2xdkqZG9C3AzyYa6X86t0D0GtmwjhsCA7c2rm7axFNkEgN%2BtLRwyA5Z1XZErWgKsSJqw1lrHWyD9btkNgGE2difbmyUY8FhNt4L6Kfi/Agf9662IDh%2Bcx5IrEUNtvE6iP8MlISydk12GV3asM9tQmJiDUJ%2B3sf9e%2BLYxy13rnpZBLc24fXMsnWgqd060B7tnHcucsQFywoDIewZb4tPrFXdpvdOluJ6fHDusYu4fVGX3cZA93JYQNLSAASg0HYWQAo9W6v1QqQd8IjXdNVCezFp6fyAWOHyMiEhiR3l0yqE1551UXrNV8bhD4by3mfTaDCyIH1XuvY%2BUKNrWSRJffeWVvnEF%2BRJCZjdvqwLvosoBCTn6vwuu/Ag7yH7fwEL/Cl/8qWAIfp8rFpTxluP4s9LZkDu5iwJc0%2B5nMkH1JQeDHhMNCaI2VNghhQjqYiOxrjNgJD2RSsSWwymdSKmngEXK0xGr2b6O4eg2G/CZVGJMbg4R%2BDRHiJVsgKRvxvmPHkS0RRoqPyoNUeoxgWidEFP0Xq4x8rcmWMwM49h%2BiHG3iqZG4VjcA4eNlnKBWfiAmiOGdrPWBtFyRmZgmtw0av4LwasvJEXzZHYuhXsPFFUdWPEWhXXpn0K1soZZ0%2BS8Sm1FRbRBONBT7quMTZLHt9y%2B3DqLfEw1udykVNSeSx2mT9FhvyTU2d%2Bjil0vZYIBN2Iy7IKJTG90HSc5uI/Os9uidXUNEGemNOwTdmdvKlMouMy2pzJUgs49NcVlnpHc3b8rcNnXs7rynZSJT37PumXWZXlFIVi8oaKiCAUQEEtMlHCQrhqTzzhVLlKG0OBgPd5E4jwpLoliHgIKDJFqNUimIZQqA0i3LuKldKmUKNUZo7DGBdzawPNw7PX09HRC0CYyxvacHsK3CJarBdIl8NgNE4x5jxIFMKRgReoDzLzJCFQwQdD%2BFfaHJI3JwJCmXnYy3ZGYTioVPibU0iSztLbP4q0wZHTJU9MGaM%2BpslimjnSf45eE0FmAtWdc%2BgKzrKq3/IIw5iT/m0nChs9FzFcWu0YRvp5oyJUvpqkeHmgsK5WkukeIlpzbhK0JDrU29Mbix0CeMqZZLCxUsNDpSZ/UwWeuIZk8h6ikZWOye/UsodAK55DYTseXro3sMEQW48vDnZwq/BxQxDNmlXROU4txOzFk3NuA26itwu3ZJ1s0zlv6C3zOvJWxRX4Pl3iqpyJysBrx1wjP5R5kGPTvPXue/jfoxJzsuRg9dksH6vLzNuws5bBtHvLLGVHADvCjInIHP469n2sdPv7uVer7wgvQ5k0esbHzyqre7L2WQoEEjUrae6Sl8WwHTdXHTjcSIWdXx65D8nt3xsPbW1lF7MsBDvcBbjug0DIfaby%2BmcyQPXsS%2B54yy7b6S6k/Lt%2BinLKqdI5PX%2BjlaOeknNQEwBOhXpcjMg8b6cZEiepkHtrjqZHlAmV6NR4Ki0PDAGYOyaiwAkIjfYxlMyHvTJoh4/lYMAuBOj3u4jkXyvxcMAO37gPmAg9IWvjrhbYpJSTQPngcUUoxxWoegRm3svOZEsL%2BX90ABpc9Z4GR0Wfj8R4EB9xmDhuYOGEAm%2BqjcI8Ke6xQmip6QACQsYwKUSuxcg4YcKKeusm8HJ%2B67wl8PcNQdR/W3LP5I%2Bw0K%2BzsrbByOtEo972jIBKtpHx9BvDTvGsgGbZjmXSIa925R7UrETWKYjws%2B5I8%2BgWJGqCtU%2BAtanYhgKstACg2M8Qjw6UPYmAgEPSlMEKSKp8KKOoVC%2BeCeF%2BqYh%2BoCgKIBWAmiUm2%2BsORB4KpeRe88JeZeBAFekuc8FBjAK8a8R8K0uBO8W0q%2BvOsCAqks9eDBjeroLeaOH47eXgnevwPeHofeA%2BQ%2BI%2BY%2BE%2BnMPSNuC%2BgOS%2Bb2K%2BY%2B6%2Bm%2BMmAc/2iu165%2BxKNKXGt%2BIUD%2BghY%2Bju7%2BDWMhZ4gBBMn%2BtubgOh4BkOCGRyYsR6Qu%2B%2BDcpB6OccV6hWnB6ev%2BeyDuhOLhxOsG2%2BARSGIIGRoIxyTw1UyY9caeI2homRIIYIIWQ0i2dBP6yeNOouwOBhSmgKmeeEpa0ofOhBoWP6LO7BvoYGUCP2cuX6BeEhxeIowxbBbhgGRkvh5kJoRsxG4KCKIALATA/MkokK/B58%2Bq2A8KPByxqxEo6x28mxIapi3WphYhCyDerBTyreZBc8YGJ%2Bwqv22SwRlOroO6YR%2Bil6fSlhrg%2BiIqDat8X87O8SZsU6nqOqDiLWXuPGvuqA/ueEOeO4xIvhtxgJHhaqjxsKE2gJsS2AGJZk5uluxI2U0Edhi0LRoKaJAcBJfaSIHxl2oJ7h7%2BvaUCauz6eG/xExv0tJRJra1W%2Bhqu%2B6AxiCc2gqdBy2oR/yZhOmJ%2BmyECWJbgUpJh76gRO%2BgubxUpayOmIGhWvR3ccRHJZxAREBxRWRbuRoYYrAXIZkmGpGZpCY8GUIMIcIp%2BJIAgewaQnx6RTwbE6II2d22MjCDRc8fp18j0MsXiqa7IqgaQxAW2jwfi2o%2BUY0Q8UOapyGqe/QAZeuTOnJfEYCWZBhfsyGv4bMTAVAXg%2BI2Zdprx%2BuNcws/y6y5ZlZ1ZOQMx8JWeLRJJgpsRFUi0bJZ2TAmISIGgWIjkw5xIZg45V%2BI5bgkgB4/ZIAipXAwoqQjwgQnoA5BpSpjZJh2RZGQgXgaQxQ6BZyAYiodpPSR5J5mQZ5PwFoioehdREu%2BoSIYZo5M5H5bgusXAX5k5SI057YE5c5usm5wFs5xIC5EF35us/gi5GZpyD5gyI2ZuyFT5hWZZLQrZjQquQ5oFf5MFAFP54F2xkFSIcFCFppTwcUPwl5rIEIyayAEoNOi8EAh8CgLoLFYKN5p56A55j5woAlgyWIhcFgHAmwtAnA/gvAfgHAWgpAqAnARalg1gIo2wuwsMUIPApABAmgElmw/MAQkgroGgAAHGYGYAAJxWVcD%2BDmVmVcDFjFjSBSUcCSC8AsASAaAaCkByUKVKUcC8AKAgC%2BV6XyUSWkBwCwAwCIAgDbAEBpAojkCUBoCch0AJBRAuicCqBmVwy6xwySBiLIBeJSCuhmC8DoGEAkDqx6D8CCAiBiDsBSAyCCCKAqDqARWkC6CrnnQkJpCcA8CSXSWyX6WKWcA%2BQohJWKioBUCPC5X5WFXFWlUmVmDd4eDpX0Dxm4hcDrC8DhVaCbAQBIBpVpAZVkAUAQCnXnUgDABSCpA0CDK1aUCxBjVUbMDEDoiDW8DvXX4%2BSxDaANDhU6VpVIQ%2BQMC0BfVdVYCxBeDAAmi0AIHfWkBYDLFGDiDQ2d6NBXIhVdWbznLsjI0RDshuUKVoixAkKfUeBYBjWah4BeXcC8BXLECxB3mvBo3ABohGD6WbBUAGAvgsTfDnRA5yU6X1XCBibNXSDi3tVqBjU9X6CGDGDWDWD6B4CxAhWQCbDMb9C426xkiJymCqWWBmABXM3SRYCa3aw9B9A5AuCRizB%2BCrlhDLCVDVB6DFDZACCO0e2ZBe0MAjBu3jCrn1C4UDCLA%2B0h29BA1NCLCB1jCJAh0R2eCdB6DSxtDx2rCJ2bCIE7B7ASDDUcAyV%2BVjWBXzV5UFVFXAAlWPBlVrUQC4DVXbXaV7W6U82bCyKW7jDW1GWSCBCuhWWBAuUaCSBmCSAIwaD%2BBwxWX6CcAeWkBeXJCuhwxcBwxmVWWOVwz%2BCSB2WD1wwl1dWBXBWhVt0RVHWxXHXxVTXJWXXXVbVZVsCcCtAsABTFi6xMDU4/hcBWWuhcCmWVX4BEAW11WyCNXiAtUy1KBy1dW6CpB9WmjfWF3F3%2BW8CBWTWJUoiPCzXl2LVFVdhf0/1/34IQAbVnVbUIhQhmCt0HWRWX130M632oCbXjD4N3W2W%2BWPXsgvwvVvURDX7I2/WfX/WA0ODI2g07jg2Q1jUw1w0I1I2M0o0chK0Y0KX4AMjY0/BjX43IAoj7A6XE29BjXk2U3ojU37AKV00M06XM2s1KDs3KPPg818D80KCC0XQi3I3i1gNS2tXyBQOdUKWwOK3c1G1WCWBq0a3wDa1ek5B60G1qihPWCm2oPm3qyaNa020x3OAQCuCR0hCRiZ3u2rme39B5MlM5CFPB2ZNh2DAzAp0FBR220CC1NLAVAJ1p3J35BO1TBDCVPZ1bB53NVIOjWH2cA4OV2f2tzf2/2mXd6N1AMUPJDUPt2kCd1YCJDW1uXz2L0/0j3Fj%2BBWXOWBCj3j070H0BWcDH1hVOPRVxUJXTUpVXVMNkOZXZUcDP1LUsAKABReIBTTMpgLAANN21WrleOS0SDS2yCy0BM6BJCkDwMDWM3DPnOoMTXX0zVzWqCfPfO/P/N4QLDrXPPnWLOBDLNn1RUnVEtbWPP0OJA/MnkSh/NWUSgAsEAShYvS10BcMhUQCvVdWCNQ06UCvCNA1iNMNg0Q1Q2qOYCw3w1iDyM6Wo3KPmO8BqMx041aOqAE16O8AGOk28DGPX5mO03SRWNM0JC2OYD2Po2OPkt80mSuNC0eMKNgtNUQu%2BPQvy1wsGAhMq3hPk1W3RO62cAHALSJMm1m0JAW3pPW2h39D23uD1PdMu1tNZ2%2B0lA5BlN%2B39B9Np3R01OdOp2NNZPh29Ou3tNJ1DB5Pp2tMrBFM50aX527Wz1F0jMXMcDzXYs/OJl4vsgEsN2AMkCLO7X7UrNrPd2F3bMgDWWuiBCBD%2BD2U70%2BVzvFhr0ovjVBW2An00MT6kC93%2BAD1OXFg%2BVmWSC2VcAWV94tuBBtuoubs7uF0VXrtH2n2HWbDM1ZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_insert.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_insert.test.hpp)
