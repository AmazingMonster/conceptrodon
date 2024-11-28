<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalPop`

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n-1</sub>, Variable<sub>n</sub>
-> Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n-1</sub></code></pre>

## Type Signature

```Haskell
TypicalPop :: auto... -> typename
```

## Structure

```C++
template<auto...>
struct TypicalPop
{
    using type = RESULT;
};
```

## Examples

We will pop the last variable from `0, 1, 2, 2`.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<0, 1, 2>;

using Result = TypicalPop<0, 1, 2, 2>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPop` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**

  1. Preserve several variables from the beginning of the list.
  2. Invoke `TypicalPop` with the rest.
  3. Extend the front of the resulting list by the preserved variables.

Here is a simplified version of the implementation:

```C++
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...Beginnings>
    using Page = Sequence<Beginnings..., Variables...>;
};

template<auto...>
struct Shuttle;

template<auto...>
struct TypicalPop {};

template<auto First>
struct TypicalPop<First>
{
    using type = Shuttle<>;
};

template<auto First, auto Second>
struct TypicalPop<First, Second>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Page<First, Second>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJ/tJ2mA6ZQgRMxATZPn5Btpj2RQwNTQQl0XEJSbaNza25HQrjAxFD5SNVAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIIPjwD0r0cA6phHAO50tCOXiURwICDwCiOVC8DDqAlBqBe7yOaFhTAIjHRPzBP2SxEwSmIADdMOgjoYyfjkBslGTkv0FAA6F4YljJAwY05uAjXZKYth3F4zYheBxHbCqDEMdAAMWIshOAHYrIqACKnKxPFmYNkczBc1nsrFcpgXVCMi13FEGBSQoSYACOXkYW1I5LNFsZADUmngmLF6ApBU9haKCOLJa45bIufanS79WcfcQ/QGCZ7BYF7lrlS8jvnQTqjZyzqaiJ6LJhgBEGBFgEGs3mC8C60dlExgD9TqqjnHnbDE25K9WGLWjEyLW7k6nAxnG4FNc81RqXtrdcbSx7LY2QwQRWKhAgLgR6CutU9DXqTVvmTvHqGxQAVXl4US0ZSoZJKlXqheri9Flem5EEcMp4MQMzBvee5hkcz7JK%2BYgfskXJgRBBBQSYuZPAWQLpEYoK8l2gQ9oex6nmcmaLlhv7UQB64lm4ZaoKB4EzG6zG9rUAjoFBD7hvBiHvp%2BqFsQQbr2qivF3lhi64S2BE8nyJwkb2R4ECeg5oZB87Ucuf7no8l4bkxZqsehHFmZJPGWeWFoAPI4hBfEwU%2BL5vshokWVxUluo5CAJBOt7ZkucnNvhwCEXyTb5t2EZSrK8qCAaRHMGwcHuUhIlnP5gVztgIAgEpiYhbhhXGRibYdlpYkSdx0pUau%2Bl0W8ABU7UdZ1rxIh1j7YEIj4dd1TyvJ1Y2tcNzxamYeywocxHnJcNyYfRxaDsx%2BVCq54ZkRpFEtQpkVCF4yQFKSABKBJeLQ4ZxbtmlchobpcG6ZiNYZh1HJdCjXbdqmCR52VuE9RwvUcZivXc5VEWeU3Qeir4APpMLaCQEBAMzoIVCisJgyMNm432/RJJ1negRM3Xcywahwqy0Jw/i8H4HBaKQqCcG41jWEcCjrJsXYzTwpAEJotOrAA1gEZiMoqZiSAAHPL/gaAAnP4ZgaAAbPLwT0xwki8CwEgaE9zOs%2BzHC8AoIBPSLLO06QcCwDAiAgOsBDJBc5CUGgbJ0AkUS45wqjy5rAC0muSEcwDIMgoOSIyZi8KShAkHgWMvfwggiGI7BSDIgiKCo6j26Qugvb8xBMMknA8HTDNM6LbOcPZFye%2BGqBUEcIfh5H0ex/HidHBAHh%2B/QxAnILyy8HbWirBASC%2Bwh4/exAS/%2B4kwBSBDNA3YFlCxE3sQRE01y17wx/MMQ1z2bE2i1HbQu%2B2wgj2QwtBn6XWCxF4wBMbQtBrbcF4FgFghhgDiC/uBB%2BeASRANZpgVQtQLjbCFhEDEetWZXFiFXa%2BHgsBNz3HgI2wDSAkmILENImBVQ6nAVcIwotVhUAMPWL0eBMC/HsnyZmQss7CDfHnaQfCi5qCbuXfQ4CUBc0sPoPAsRraQFWJ%2BHoQCw6Y27KYSw1gNa8FQOQlMWAFEQFWDUOEfgICuEmH4F6YR5hlAqHoAoGQBBWMcWkZxDBBj2JGC9UxPQ%2BgTE8G0PQfj6izC8cMRIvjZiuOif0CJiwokmL5lsCQ9cOCM1IGbXRnBu6hwjlHGOccpBDwgLgVOE9dhcGnsLRhqwApMCwIkYxpBJaSECIyFWgRFSSA0JIOWmsTb%2BE1irfQnADakCNoELgjJNZcG1ireW8yqhcH8F0zWWSm4WytjbWp9t54uwXm7NuXsKBr1QGPAOQcOBNBYESRUYcmDWnAaDFWjIZkIPwEQAxeg%2BE53EPnYRShRGl10BDSu1dz7pMydk5uHBW4ewuEcTu5JiB3IeU8g4LyuBvI%2BcPUey8EiT0CGYGps8HZHPXivM5VKRi3PuWHLFRgcVcCervDEEED5HxPtfc%2BpBL6n1vvfBwfLn6MAIG/D%2BTdv6/3/oAvloC6HbFZvgKkjg4FN0QcgjEfL0FdCbtg3B1x8HKpnimEhQtyGUKUDQsBRh6GgH2XwFhCg2EcK4YwPlfyBESCEbIERJdWZgokQwzRVgZHYKMUo5IKjOBqIINJVUYbtHm30enAk8ATFdBgc4Cx0pYkhGlAkhxL0nE9ALWWzIxafGdG6GE/oBbQkCACXMUokSQkxKCbkOJzRq1JLWBsVJ1SxkZMbqXC2qL0WPOeQRHF7zGQaGHuU75xLqkzzqaQBpTTKDpImVMt5fTFRrMVIqQI/TJCRxerC7ZthdnkoOfAI57t26r1pcQQObBOC3L7iwBQRI45EjnXqGYycvlpwzgXfhudfWQYDWIkAwQIU12AdCsd5sW4nI7l3b9Udf3/qOIBt5wHwwjwuYSypM1AhksYY7ReZGN6vvo%2BPEA/7TqI0I4jYjyM0WRz4HQDl1sICH1LgK3lpDRM3zvg/UVFyX4Svfp/FVmAf5/zEPK0hir7WmtIKqmBGrS5aupDq0herMG8ENafE1hDzV8qtVQ21dC6w0eYR2V17DOHcK9bIf5gjYPAsDToBDIbjDSJsJGzNbMY2ZCAa8TGUitGWB0WzNNhiItNvMZYrt1jC3oD7W4womQK3uJ6Hl3x2azEtsbeV/x4S7Htp7S0LLHb4l1cSWkgd/N2t6xhVs3JOGjh4YA0BrEMwl1gYo9M6j%2Bz6mYEaSMFpes90gDMG8wIgR/DK0kKyjQa3FTa02eOzgOzbYbraYqROR6uBSBVoerpXBFQjsCGhnJls9lz3SUnA76HXv3tWOQ9IzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/pop.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/typical_pop.test.hpp)
