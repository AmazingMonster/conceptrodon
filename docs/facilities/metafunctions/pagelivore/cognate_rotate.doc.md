<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-rotate">To Index</a></p>

## Description

`Pagelivore::CognateRotate` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function relocates arguments of the given amount from the front to the end of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper
   &lt;
       Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>,
       Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
CognateRotate
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 0, 1, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<auto...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    // Note that `Operation` is invoked by values extracted from
    // the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<BackTargets::value..., FrontTargets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        
        template<auto...Variables>
        using Page = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbgA1JjIhkHJkstlMDlwwVEHWtPBMWL0EWXCZKhxW1HqgDsFluc0cyFuYommFUaWIAqFtwAbmJlTDPbriDa7Sr3fdVbHU4E1cCKQDc98NZSAJKs%2BhsQSmnIGs4FvO1oE1g63IQAdzwEfqVaNJdNKrhXJ5rF76KuTq8LpbbY7Jk904zWZBzO7ZrcWQAXpgAPoEAB0u4AUg7R%2BPW%2B3aPiiSAQBEsKoN0oAI7K8X4ve77dkwLD4Ezq63P8K412V7NwQX/MCAKXYCLVQN80X9AwFE%2BAB5Z5iArARSFA8C/2pWk8FUF80TfAAxYhZAAFVaYBMAIBRMN/bCFW5RhBzfCwmGQABrSjiGo2isL/B0wJ9PA/QDZlg1DaDbjwdBkVoCBlgE24dh2W4olQZkFQQTBbmKbIBH9BBDGo25UCoGEADYNFIiiqJohRYOsgUGHQKyNHYrieL4xyTGs5TVPUzTdIIYzJT8jQUISdCGAimTPgiCNUE4zA3NifUo28D5biDRUOOZNyqDIlgArU0KQsAns9NaQdmWIXyGL/QLyIQPAEs%2BeJRC8JRbmbXTW1oWhqq4nL22IfVCBZUqzIsiL40TehHN3OKIktOa9Qi99GtuABaOCorQxp8U87j7Noy9MuVN9%2BVswRvIci7o0wWDP1VDEUze9Uc0bDxgGYZkACVNKq/MrkXE1l3BoD8Wgl7sHgphENuA6YsPRUx0lX7/swIGWg5D0szAqGe3PPB1y3W5LhYdZBCE/8j0lalNNQZQmGo5Tp0JxjlKJyrl1h3d5ttRa6ew7qImAKk2d02F5SwSF%2BxVbawIgHnGInU9zwIdBLxYJgUo3a8gzvTBH1eYCqZpggPy/RjwMvYmtNk%2BT8RRxp%2BV1VE4SFpMFCI5bP0UtW/yUzMOY%2BsOvsuXnIJhoU30uYAaRZRh%2BNe7bxaMKXTNlqVmdZ9m4UT5Oy1ouHPu/OdyWuWtAQbLVsFUVg2V00Ga9rxlq8xCEoRluExS2NI06/evkdQmLOwXPmoPjgOvwZsfoqOyPs3bxshC8NJilSgGPi8WhJTbzPJY3rfMh3veD9leU3ZyfEzH5DR%2BS4fkzA/edvq1ABZGimCoLxsSNEnmDaecciAJ14n7dOlxj63B/i0f%2BgDKy5yxj2XGJM4S3wEA6S8BdgKBBwSAPB%2BJLiQPLivUeu8FD70Pp3K4sCqE0OvnA3%2BiCHB3zhE/W4L9bgP14e/aumpbjkQ%2BLQw0IIRLIA3IjJQbQIAXhAAoQc0ioFuEYQffkp9t7oHUdbT8ocLAcFWLQTg/heB%2BA4FoUgqBOAgUsNYb06xNgyzBDwUgBBNBGNWJxAIkhtwaCSGYMwABOYJXB/ABKSFwd07ppAmI4JIXgLAJAaCfhYqxNiOC8AUCAJ%2BHjLFGNIHAWAMBEAgHWAQNICJyCUDQKyOgCQoiDk4KoJIlkdqWUkLcYAyA/RSG3GYXgqVCAkFknofgggRBiHYFIGQghFAqHUAU0gugX7NjQmkTgPBjGmPMZ46xnAkIIiqZKcytxWntM6d03p3C/FmFuBADw9T6ChkxFwZYvB8laFWBAJAdS0gNLIBQCA/zAUgGAFIB%2BNAD4JByRAWI%2BzYgRFaMiLZvAkXMHGkhWI2hMAODRaQOppckIMFoKi5ZWBYheGAG4MQtAcncF4FgPWRhxAUrwDSdh7YGVWKDHihE2w3GrXqPspEsQ0LjQ8FgfZio8DJMZaQMasRz6PBZcAJERhPGrCoAYYAChtTvGbFFCxbiJnCFEOIWZZqFlqH2as/QJkUDWGsPoPAsQcmQFWKgIeOQGU7SJLLUw9jLBmAyWNBMWAPWKR6HixoLhXLTD8C/MIERhhVFGC/fSjRE16CzTkBYIxEgvzsLGvokx2ieE6HoEt7CBD9DaAW9NRbbDlpzcW8tjaljvLWBsLYEgdkcDMaQdJvBMnnLaR0rpPS%2Bl3IebgEZrzXEfPcVq1YOkmBYESNGnxkhAjbmCYEWJGhJBmEkNZDQ/hLLBP0JwRJpBkmBC4NuSyXBLJJGCVEyy/hJDhIPZZYd%2BzMnZNySugpPzSm/PKcc6pwLQUvKaWwTgrQWARndDtJgCMs5cGCduJ9vL8BEAjeM2QUzLXSGtUoW1yzdAP3WUwTZjKB1DpHQcjgRzKkIhmuOy5XTIQmW4ThvDDynkApeTCMEZhl1fMKZBuDCQakgtQM80YfGjDYa4E/aFdU4UIuWRilFBL9NYpxbGglRLU4krJfsyl1LaWDQZW45lJk2VWPwJyxw3L9l8uQAKglwr4lWLFRK5EUrthWNlfKtxSqVUsmcxLLVfBdX6sNcaglZrSMzPI7IG1SyrE0YdZqoNVhLCuvdfAL1PqBB%2BoDXKIr1hQ2jvDbJD45WY21r8BAVwbaQiuU7Rm9ImQDK5ErQUTNg3Gh9ebTWxo9aK35CTW1mbHbU2LH63MKYI2FvrcGCtwt/ae3OP2/E5jgHODccnZhyW2HcP%2BLnQRkg4nH1SdXaQddm7KADrvQ%2BnDx73T%2BGCTEwIJ6z0/oA8soDtgQPSfA/ASDFSTkKbk8QBD2xkNXJYAoCMfoIzXaAhMIZ92iMv3SxazLcz5CUdyzoEAwQ6MMe2TewdezweHOg6ciyqh0eY%2Bx7jnsExhNKdEwkR7gRntgaKX8wXgLEdS5eSALHW8Nw4%2BCRuPHBANyc/I3QbTlBdNWKM%2BStxBvsW4vxQq8zghLPktc5gKlNK6UOaZbF1lYWmUctLZ55Z3nfMKv86Kt1wXQsyoTJF3g0WlCqri5q8XOq2bJcwEankaWSOk4kFl%2BZlO7U04K8YZ1JWxVRoq40BlOwLx1ZDWGhIEaWuesWzkeN7hNt6BTRUPbY2Sg5G63msou2m3VvqKWutram/FoH%2B12bk3q3D/m1P%2BYveu2rAUE4vt3bjvM4yWdzXtwMdY8jLz5k/OIDzsI4995nyXtvdGNG%2BJX2QAhO3IEQI/gIk/tSY/90b6wcb6yZDvJL2d3%2BD7rRLuipJJCSBhJcCBJmD/rxKBDr6jqcDn5gYDqDJf4IE/7Q6rBjRZDOCSBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rotate.test.hpp)
