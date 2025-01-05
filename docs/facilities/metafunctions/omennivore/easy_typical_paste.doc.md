<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyTypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-typical-paste">To Index</a></p>

## Description

`Omennivore::EasyTypicalPaste` accepts a list of packed vessels.
It concatenates them together and uses the first vessel to hold the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

- We will paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_0 = std::tuple<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyTypicalPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyTypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Ware_0<Con_0>`,  `Ware_1<Con_1, Con_2>` and `Ware_2<Con_3>` together:

```C++
/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

template<typename...>
struct Con_0;

/**** Dummy Arguments ****/
template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = Ware_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyTypicalPaste
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stoc_0<Seq_0>`,  `Stoc_1<Seq_1, Seq_2>` and `Stoc_2<Seq_3>` together:

```C++
/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = Stoc_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyTypicalPaste
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyTypicalPaste` by uniting `Cotanivore::TypicalPaste`, `Sequnivore::TypicalPaste`, `Stockivore::TypicalPaste`, and `Warehivore::TypicalPaste` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyTypicalPaste` to produce partial specializations.
Hence, we create the following helper classes.

```C++
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::TypicalPaste` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyTypicalPaste
: public Sequnivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Cotanivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Warehivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Stockivore::TypicalPaste<Packages...>
{};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACsABykAA6oCoRODB7evnppGY4CQSHhLFExCcl2mA5ZQgRMxAQ5Pn5ctpj2RQwNTQQlYZHRcUm2jc2teR0KEwPBQ%2BUjVQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxuxzuHkaDDwADcSOwQAAVACeKTwoloyiYs0w3yOwOYbAUKSY2whqChsPhdxMAHYrNdQQRMCwUgZmSZYm4CKjGKxMAA6IWc7Cg2bELwOO4otEYrE4mn0ukPTkMkF/XZ3CzY3FuHUgUFMllspgcrk8l6E3FY5AAa0w7lkTAWxBFYoIEqlMvRYnlZrcNvtjsEzpCrtiosZSuud1jdy8GSMdwtuM5DzugYdHhDLtVhtpKtiatBu01ACVapsMjDdfrDddmaz2ZhDVzQXHk8bm5zubyrUKBSK7sgDAovtnGi6rqR23HGyb/Sn%2B8KI8PR%2BOnS6bLPY0v%2BQPsPQ2IIrgpSDSY3O%2B/uhYeWYwCBYzzvk9e2AOAPIEBDRBStyOnh6koENKqI%2Bpi2L%2BhOobRCCXJ3seBCngOIrntBW49ghD5PihEbnl%2BP7EAouEAXSaodgmwTAK%2BLw0rE6benKkEtpesY9i%2BHboWGcFuFhJ7EUK558Y%2BAmDnhHFxgRv4oaxdHYCAIApnmUaFsWKn1mC9xCJgACOXjQnCxAIoxvrMXihwEvyxKkri2l6QZ1JkRp87duab6CiuAHisBoGyqZCpOQWynqjcmrakoEJ1oyDZdqaLZuZa/IZqSQZ2V4bzxV5QFemBTE4j2mboGlGVulG5FxpRSYpnR6aFcVDDbMFypNRqdwVsgVawrWSgGtFVwuXFrZuC%2BA3%2BkwXhECRa7Yl89XbNOI2xWNE2oFNI4zXcc2YNusnjZNQoAGpNHgTARPQp7ni%2Be2rYdx2nfQT4zrJe7vkKUlEf%2B7qeiBJkQflXJbTxR3ECdZ2YMhnnnltVhcsDoMPaJqF3O9iMRvm5WxpV1HVWmvngX6LFXB27GyR2gM9nD93g6J56U2DOGQxJsYozJRNxiKClKUW%2Baqc5S2EyTbO7vzPYvZg57XWt66bbp6UNeDT1C52TaDQlfJsBLK1Sxt0OKx2YvSgtz3udKO1K5Lt0g1TF0XubWuW/D23PsbiWvQKKOfdc3k5X5f3%2BuTXKItOdx0%2BdqPYFDssZTDbiIjYId3fT4f4d%2B0meejL5YzRqb0XjeUcrJgsdmTUfyzxQfnrMprogA%2BqIsw9kHIoQKH1MrAOleNI4yB15BjdwdgLeJwj7eM6Tkmp0RrPExGnO8k1QXc31zV9f8%2BybUQdpUkZCm/QT5nnKCVrWWSDSoFvhmptGIWjfFvaux5YlZd9ef%2BcyipWIvamhVqOqRT1fMVaLhNnVTepVAIvz3sxAqKUHRn1MGjMqmdEzY15DVZKdo4FgKXiCL%2BGlSxtUrERLq/92CAIXALNsz0RbmhoXqe2T9ppjm1mODe58jZK1vqLOhFtGHrWYZ5Jhs1N5m31jwhhQ5%2BGiUBmeW2YigF314ZI9cA5obO04e5T8k8/yMkQRAnyUD/puHgTxGRJEoYiJ7Go8xyNtEkQzrJLOONc4G0MQXJWRdi6xhMVY0u80aYyz0tHZOTNbGEURoXWeil544OarE9Sq9wQAHUmiYAQNvYyuU364h%2BEfKyJIyQpKMuky%2BH9yGuXvurR%2B4DvY/SyX7K%2Bn9earzCn/PUAC%2BpcLVlaDBQYimZS%2BgY%2BpBMYGYPQP08BTlHEoOzugwqEzYl4JaYQjqxCaykN6jfEWujhrUIUdw/Z3Sbx8JUYIqRdx%2BkcPkRQg5Nyjlu2UTNFhXx%2BmiLnHQsWzyBxcVgrIxahzKnLhOU8oUPziCPRGpot62jPb6J9vjaBXJLk9jBRDJ%2B55Xkos3GGBm6Kwlpyfg4pWTi0G41ccM6BkTdlKw7MirkqKAlgtxahUJLNhSRPktEl4C9mkhRXiFNedwACSCgACynh0BUC8LQA%2BwICFPGZFKApQYaQADYNDitoOgEw6qjQArFjU7KIERWasldK9Gdwq7d2HAIHEqgUjEDuBEVAng7gwjEOlD%2BVAxBKDiRYRUvK9V3O5B8qFwLWFgvPJ828R4Hx/j0bU4VYqJVStoFinMYZMKxsEOHSZ9JLVd3RDahgdqHVOpdTK913hGlARbF/ANLVNKHCTViYAmBU2ypLJqBVtQQLKodGqjQraWy6pivq9yhqX4iuHami1Vqi1oBLcye1jrnWuqrZ6si3raC%2BvrX68pqsQ0AqUauc5W1Nb7QFK3eNz8fLTqYG22dAM/F32vfYvRZEC3V2QMW0tq6K1uo9TWiUdbVINviU29eIqyyoCYGamVuTWo9qVbA9Ag6YNwZ1RoINFSDUJqNUmjD8G52Fp/Yuv95b11Aa9T60DqpwPfy4Ts/5waumAuOY8gR4aXmpL1u88dD8vmguxb%2BWFiboOweI0i1J6bJxhlzR%2B/N86yO2uXWWtdlbqNkVrX6hj%2BDwTQedLQDtiGf7Ib7ah9DRmsM4cPXh29UpDN0FnWVL91ryNqf/VR6tNGd10aLHpzp2yeIsdw%2BIy9nHw5CLYcgPjwtj0SNPacgUW0dED0GY5hQZYjNPuMdg4xL6FOkSU6R39nnKOaZ89pkDun92JMBA10zgqhVNnvCGHona/iNe64fILAmqkDkDA%2Bz4k6fLYGxMiNxhMQB3BSF4M6Ra0oOR3kiClRihtttzUgpZWz%2BtAo2yNvRRk9J4CMl8CAKEzCqvMKqk1KbzVcgOzehSG7MArAyyBcbChJtrf9E9%2Bx1wZtzYWz%2ByEhgMm71%2B3ff76dtuBrHaxsNT3wHHa8Kdz4dwLvCiuzdiTcHcvI6ia997XsCNfZ%2B77EZj2UrDa21cIH83aBFv6SU%2BEkPKeIoDDTzbAPcFNMbWx6NApCcAVR%2Bj87l3rtXac8Zh7XO7S045iAYnH27jk6m6M20tPecM5BzF20EPVsc/W9zz4vPArw8gz104crwQADFTuzDV6oVgbIcn4hLNbwEwJDRmFiMEEcXgsB0W5F4N3kyutaTDwUB0FYFDSpAqZrOQho/pFj58BPNcNDoNmOgTmYf6A9mCAQc8VBaCwZL3cMvFf9jnnQBsMGboIOCrjwnzrVws6t9oAQLP6D1dQ6Gi%2BXP%2Bfw9cmL0jIfBA8%2BKQL3favppS/l9NPsFlslh8z9H24evjOBm6M5Vzb%2BgrESfETx70n36a4zWiAQCA6%2BFD8kv/GtwXee8aChqnpQ6AX9Z5FO95vXvvdPctJagBA0NsAXdWt2814ADTMgDm0U8UgY8v8M9u929k8P90949u8a4uAc8p8FJi9MA21iAa4lAgl5Yi9BBzw387gOg7gzBzxYgm9D9wQX80CZlv9cDcZ%2B9jd3FPFYx19CDiDSCX1KDK9sM8I5E4xBCGAsBVARDyDGouQ6CzBV8lYZC5CFC5YlC3AmCP0okD99N7hj8ndTNlNH8lBmhb98CQB782BH8exOD39EC09kCsCe8uBf9G1oCYDetINpR0liAwCIC3coDfCgQjDm0WcNglAvhTNBdQ1BMzlktRspR%2Bkf8IMEi9sOMksQVCVScX50jPDMiPlEiBtki8jUiQJ0jVCSjsiHl8MX5swMiWD7gHgfAWBkQ7grhiBgAfA4129Bcw0qjyQGAcCBcyigURjmjajGNJiciHMQJmi9DWj4CMC3C28k8ZkECkDv8zB0F0iJC3BmiaDmi6CZi0IBAa49DRR/97g2CtiqJCF3Ca59juCJsNdmNZJDj00MiI4pDYwijfjzirjaiI4Xwajfibj/w55uU7jm0TDT8LJ3QL8r8rC78H9sRHCUCe8GDNp1i9ivD4TwjkTI9m07cNhmgEBndXd6AwiSSz8BVwR4FbRiAXUWA4jGSsjg0T1sAhFedE14EWiD1FxwsbpuMBSCMhTii5j9UxShN8i4UQIhTZjIj14ei%2BjEJOTST%2Bp5TYclTAlhS%2BseTEtFjDSZSRTFFTTVc7JXiJiEsItGifJbSVi1T8SXDP8HjGT0CPTMDM9Yh0EhSjjbSaDbS6DbS8SXTmC3SvSdTO8cTri%2B8PiB8vilYgzfEdI/jLpZJpSMycDI5MywS4sYs7Tn1MzoS99YT4pVj15ET29zC0Sb8MT7CsSuRv9YhnDdiEybi/81QOA1haBOB4heA/AOAtBSBUBOBhpLBrBLVKSyRzBYgeBSACBNB%2By1hbQQB4hJABQNBEgzAzAABOQ8rgeIPcxILgWkWkaQQcjgSQXgFgCQDQN/Uc8cycjgXgBQEAN/Vcsc/s0gOAWAGARAEADYAgObEvCgCANAVkOgaIUIfkTgVQRIVVAAWlVUkDuGAGQB/SkAFDMF4AdEIBIDwDzw6H4EEBEDEHYCkBkEEEUBUHUD/NIF0A6AAHdiAmAUhOAeAByhyRy1yJzOAPwJoIK7hUAqA7hkK0KMKsKcLaCdz9iIAPBYL6BHVFyuAVheBfytA1gIAkAYK0Q1LyBKBDK4KYhgApAGCaBu9fxKAIhBKIhggmhkQeLeAnLmBiBkQPwIhtBe03LSAYLEIPwGBaBXLmKsAIgvBgA9RaAd0AqsAWBDBgBxAIr0c6gawvzmLMBVBKxmQArCDbzxymcIhOKvKPAsBBKPQ8BHzuBeAaxiBnUlAngkqjAmcjA1y1gy8H0FADoPg2KPxLQAqKLhAMQaLpARqGK1BBLWL9BkqUBrBrB9A8AIgvzIA1hUAUgegsrULc80xTAZzLAzA3yGqQYsA1qIA1gag6hnAIBXAph2hSBAgFgygKh8h0hMgBAHr3rCgshBhXqRgZguhe16g5hvqgbuhQb%2Bh/rhgYgZgwbPA2g9Aq5mgYalg4arr5yaK%2BKOBhzSBXzeB3ypKUL0LMLsLcLFLMdcBiL1K/dNLtLOq1gfw4MRhLrSBNzJBYgBRDzYhryNBJAzBJB1UNB4hVVDz9BOB7zSBHylyBRVUuBVVEhDyLzVVtzTyebVV8bBL3zPzvyVzOqALgL9LQLRKJoTLoLUBVL4LEKOAmgWAYRaRUKmBpokwuBDyBQuBdzCL8AiAzq9ARqqLxBaLJqlBprmLdAGCOKuK3Kca8aCahKOARLwKJpxLJLpLSaXbqI3aPbdzMcVKjLogaQ/czAtL9a/y9KDLLaC6yAoKzK1KUADAjA3auA38bLmQiJ7LHLnKvKAqPKXKfK/KHAAqgqHwQqwrBLIrorYr4q6rSBErkrUrxz8AjIMrPhBKcq8qdhlzCrBKSqyrkQKqdhxzqrarlyGqmrMAWqF6qIDburgBer%2BrBrGBhrZBA7xq6L5BQ6mLxyI65qOqDqrBLBlrVr4ANqtqsgdq9r6IAHrBjrCbTrSK171rOhIbbr7rEbpgnrZC0a3qOgChPrsgMHHr8GegcHAaUGQaBA%2BhJgiHkbgabreg5gyG4bxh%2BhwbWHUaXrYaJBMbNhtgeGJbcaBLmKib07ZL1pXb3bPbs8IBqbfai6lzS6dL1zSBmasAYg2bbypaZb3b%2BbaR4hDyrzYgBahbJAOh46dbbA9blG9KjakAwKILza67ra2BOA7bZKOSYQf0YRs7mxZhvaabSL/bX6xqJAJrZAprv6dA4hSAo7uK6rY7hG3zhLTaQIJKpKPGFAvG3VfG4ondlKq7zKFHYglGDbjbnGa7TLCn66vHECa4fHDya4/Ge9VAMK%2BA6B26vyIAHLmK%2B6e7Z6%2BnvLfL/LZ6R7BAx7wql7MAoqYqxAZ7lz562qj7eBl6QbMr17cqOp8rZ6d7mK96XLD6qqQZT76rogL6r62qb7y6%2BADB76%2BrMABqhrZ6A7Qng6Imv6ZqYnG7jBFqgGSqLqwHtrOBdhh8YGjqTrogzqkG2brqegXBZD2HnrShuG8GPqeh2GSG/quH0a6HUHGG2HaGIbKH8XOHkWcX4aCXchHqUb5gyXcHeGthsbBG47tbOAMnMLPHvHcnmR8m5GSAFH6ay7dKmbMAWaNGcbtGQAjyBRYgEgzyzHnzZXaRFataRHOBdafzGb2aQBJB4hubLzaRnzEhJATyuB9yrtBHYgknCb1WhWVHbyCLVXkmPy7WVg1gGqMhnBJAgA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/easy_typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/easy_paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/easy_typical_paste.type.test.hpp)
