<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-conceal">To Index</a></p>

## Description

`Mouldivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal ::   template<typename...> class... 
          -> typename...
          -> typename
```

## Structure

```C++
template<template<typename...> class>
struct Conceal
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**, int***>;

template<typename...Args>
using Metafunction = Conceal<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*, int**, int***>
::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Conceal`:

```C++
template<template<typename...> class Operation>
struct Conceal
{
    template<typename...Elements>
    struct ProtoMold
    { using type = Operation<Elements...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEapAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRycAnqmMrJgAdE9H2ADUyAYKCq8A8rfETAaLxMGgAguNiF4HK8PAxNmIQaCTAB2Kxg14Y16nfaAi7HAg3O5sJ4PbD0NiCBTA9GYiFQgivZTEVBEACynnQiMxrxRFleXkyRixhJ5gQAIr9/oDspcybtGAQFCTgYE%2BSixUc0UiaRjsedLgTbsxiU85RTFdTQdyBRFgK92bR0KKJUyWagHZzjmaFUrnoFsJrEerA2DEQB6ABUUejMdjYfDMdeABVMONvjH42DI7Gc9HM9qkWZAhEPl4sKK3Gg4ZhUhb/UGwXrcQbCcbHn6A2C6dC/glpQIQwWbUKhF5UkVMOgAEqpry0BlHCW9gFA44RAikV7riOb7c7reCaMqrWIpuHfGt%2B4k0HEYBU%2Btg4d21mYZpULxwhrOmECeG0S7Lv2DCWiAIAepcN53sq9aqg2oJPq8M4KHOC7ivar5MO%2Bn4ymugi7oe%2BEEFGhFHg%2BoKgYaeInl2zSOMgAD6TBfAkBAQOM6CgQo9yMfebhIShm6juOGSTvx84vEsmocCstCcP4vB%2BBwWikKgnBuNY1ivAoawbJgPJFjwpAEJo0krAA1gEkgPBokhcMiyT%2BBoZgAGzOWYAAc7n6Jwki8CwEgaCkinKapHC8AoIApMZSnSaQcCwDAiAgGsBCpF4G4UBAaB7HQCRRPcnCqO5zkALTOZIrzAMgyCvFIDxmLwk6ECQeAcVwMiCCIYjsFIHXyEoagmaQujtQA7gCqScDwMlyQpQ2hT86VpQyqBUK8RWleVlXVbVVlmK8EAeDl9DEPpgRcEsvDRVoKwQEg2WpLlZCZQ9T0gMAUhmHwdA7MQEUQLEQ2xBELRXFNvDA8wxBXD8sTaJgDjg6Q2Xmj8DC0GDMWkFgsReMAbhiLQEXcLwWAsIYwDiFj%2BDEAjjgAG6pkNmCqAj6VbIZ651ENtB4LEALQx4WBDQQxB4P5JOkIzxCxCJYq7BTvNGCZKxUAYd4AGp4Jgo29ophn8J1ojiL1hv9So6hYyN%2BgUygGmWPofMRZAKyoLW2TEyV7GLqYljWGYIXS2LWDOxAKx2HT2QuAw7ieB0ehhBEQyVCM7VFFkAhTH4acZBnDDzMMiTtRHDi9BMbRx/kxd1JHAh9K0Bcp0Xtjl1neizA3ScLKn4c6ZsEgzRw8mkMFvChetxVlRVVU1XV%2B0QLgzWneY52XUZKsrAgmBMFgiRh6QFmSIEDwAJyBMikg2WYkjOYF/jOSf3kcL5pD%2BedDzOVwznuSf7lf/4tl/Bn2ciPeanBwqRXXjFW6iU7rJSWulcglBXonXymwTgLQWD02RCVJg7wDBCi4CfB4XBrKNXwEQYOegzZdRNtIM2igLZDV0F9caTBJok0HsPUeKlOCLVSulV4q1XiYOwbg/BFNarENIRoA6R1HonTOmYNe11YpwJQQkJBWVUDHRGKInBHwKZEK4CkGg84Ej/UBljSGoMkY2OhrDeGiNJYowVGjDGQ0cZ4wJrQImSMyaKy2MpGmkdGbE2UizNmOwkZc1kljXm/NQZCyCVdMWEtDLS1lkoeW5MjBK1ANAvg6sFBax1nrJGNDjY9XobIRhg0rYgC%2BgQ4w9sbAJNDq7d2AhPbe3FL7KwlgA5jyDq1JmLtui1z8BAVwbd2qJ3KIXPQ6cGizLSLnBojdFjVx6HXVulds4TNLrsuYXdFnFz2XkA5HcBinKbgPVY6x%2B4XSftwsBHARHECwTgvBhjCHSOsgdRelCzoXSuhvUgW8d4jH3nEl%2Bb9iE2WREA5E9lJDX3Ku1HhoUIFRRVnFWBSAUrLS0Ro4gaCtiYK2iwBQ9Mar0yIQ8c44xyFL1atQ2QtDql9TqZbZSuhghsI4dNF5c0sYLQQStNalKKrUtpa8elxCmUMkOjohRCQzqBBUXi9Rqqnokt1SdEAtLxz0QVfRJVjFPnlW%2BuYv6lArHKXsZjQyTrHF0yRq4wQ7jMbBMwLjfGhNiaGQCXklJ2M8C01LmE5mrNkDsxiYIbm8S%2BYCyuMkkWaSkaZLlgrPJto8VqyYJrbWusjQVI5VUiQNTBA8uYUkG2yt%2BnWEdrEDpKkukMGJmGdids/aDMDgkYOYz94lwaNHWOlyE4x02anNZxRsirOWdkGdzdR1l36KstdxzO4LLuecjd%2Bz27lxXfc7SjyepcNFSFTgHyWBUppXShlSrAUUJICCrV0DN7b13pQQecLGnEMCIEfwjlbKBSA8ib%2BoCxXgNsJA1RSxzIgEkP4U%2B/h3IuRPpIE%2B9lz5cGCHEwIV6x6wYQ4PBq0Hr1hSgTdFY0tMjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/conceal.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/conceal.test.hpp)
