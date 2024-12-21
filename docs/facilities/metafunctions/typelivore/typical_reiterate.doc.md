<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-reiterate">To Index</a></p>

## Description

`Typelivore::TypicalReiterate` accepts a list of elements and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.

<pre><code>   Es...
-> N
-> Capsule&lt;Es...<sub>1</sub>, Es...<sub>2</sub>, ..., Es...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate
 :: typename...
 -> auto...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalReiterate
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };

    template<auto>
    using Page_t = RESULT;
};
```

## Examples

We will repeat `int, int*` four times:

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

using Result = TypicalReiterate<int, int*>
::Page<4>
::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalReiterate` using recursion over the times of iterations.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

Here is a simplified version of the implementation:

```C++
template<typename...>
struct Capsule;

template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArIEADqgKhE4MHt6%2BeqnpjgKh4VEssfHSdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJbfWNzblctsM9YX1lA5IAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc393cEmBYyQMAMObgI52SjFYmAAdPCfnd3sQvA49m4mMkFF56IcrHdfgB6Ql7ADqzwA7nRaHsvEo9gQEHgFHsqF4GB0GAzUHs0BymADmACGRSeclugpYb8AUCQZgwRCocw2PCpf5rkiCCi0dhVIL0BYmMgANYHADsVjNABE8b9pYDgQL5Udfns3QyHXKFZDoSqEereQYFCyPIImNMyK73YrfXD4dh6GxBAo7erfsjUQQ9rr9YaTWDQ/UI2CE4DGARJf7rmmCRao26ZY7QUcY8q47DbsBiJgy8nEbd3bT0kY9gBZTzoF5W9GycPhYglxPlyuw0h7Tvd3sV1U/fz4%2B7W20E/6ep3epUw1WlpMV/sZtEAFUheFEtAASphCHEz7X94PG16RxMCcqA7jWA7uveWbKMQqBEMoTDAM8Jh1oee52ncxJ7Ia9J1JgyQgPWHqymeQEgXsACS/aDt2ACOXh4N2LIQBRU6HNOGjzERUF7DBcGoAhSFglR4GDihf6Du6dJhMADI%2BlO6KYtiuIumm6F3GJaH7kRAGkRi5EiRqEFunRDFMXsLFsf405cFxGmQVqma8bB8GIc6biGUR4lEYO0kjjGCkYliOLudey5gdWEluihNrqX8txYR%2ByArOkABuzx4QROmns2%2BlEJR1HuqZjGYMxZgvG47GUXZxl7DxfGuUJRyefZ0V1q1kl%2BbJAVVTmrh5sa56xs5/GCe5rEALR7GYVwgCAMaFZJexzbpwrjrQ6CLluK5rmFyYRUetUxYd2UkblwFEKqG49jeKaiVJw6yWNCkNQJblgtd20HXFx0/ZhABUgNA8DhJEkDD7YEID5A6DAPA/DsPxQ8HJPBVJx0Bc/b2md7mtpeVbpo5aJBcpzraXcXV7EIXjJPkmDoB%2BylZlVJMhWCRFhAQa6c/9pAc4I3OCLz/Nc3sPN8x1nOCwQ/2ppFGG3JTjM4sz1l7E%2ByQvmIH5fsQelS2LQv9nNY1gpIxvzT6J2agKL4APpMMGcQEBA7zoHNCgwg7d1uMrtCi9TtNpPTfsEFcXF7hwiy0JwCS8H4HBaKQqCcJVljWHVyyrMhZj%2BDwpAEJoUeLMaiRmLCZpmJIAAc1cJBoACcCRmBoABs1eBDHHCSLwLASBoGikAnScpxwvAKCAg%2BF4nUekHAsAwIgIDLAQyQnOQlBoECdBxBEMKcKo1etxNreSHswDIMgexSLCZi8PThAkHg7vjPwggiGI7BSDIgiKCo6gz1ILocYFI9YEW4LPLucch5F2TpwAA8icNeWZUBUD2IfY%2Bp9z6X2vpIW%2BFkPDb3oMQA4udbK8GnloRYEAkBb01sQjeEA6E73iMAKQZg%2BB0ABMQCeEBoiwOiGEBo5xOD50EcwYg5x4HRG0NUae%2Bct43ngQwWgIjAFYGiF4YAGJaC0AnhA0gWAWCGGAOIdRJUajpX0UnTAqhqgnHWPnTmmAu5JzONEPWkiPBYFgVqPAfcDHpWINEYOVpAQmLOEYIuiwqAGGAAoAAangTAFJ4FKlEbwN%2BwhXxf2kFkv%2BahYHAP0CYlA1hrD6DwNECekBFioGSIUBg%2BiJpu3YqYdOlgW68FQEE4gz9SrwEWO0RpLgGDuE8C0PQIRpilHKHkNIGQBCjD8OMfIiyGC9FmQMcYwzaiTGWXoXZnRJibP6PEHZ%2ByJljAmN0U5sxzlDKzmsCQ0dY7x1gaPdBR8T5nwvlfG%2B5UIC4EfiQzY5CC7RMWAgTATAsDxAgCXEAkh/Cwgbv4M0kgNCSCrq3AeCRW4N30JwHupA%2B551hK3Lg7cG7VypQkSQXAEhotbjAwBo9x6TwhTPahi8aHLyQevCgTDUBEN3vvDgDQWCpTNBNJggYTHXwbrCLgsIbH4CIH0l%2BP9smfwkHk2QBSAFJ10Bw0BmIMmvI4NA4e3SEECpQWgyV0rZXypHFwJVKqNAEJFfQuIpD/BmHmBQ6Jc9aE%2BpYYw5hxCQBOplTsEx7quCDxoP7OIvD%2BGAPEcIjJpAs2SOkbIhwObFHlmUao2BGitE6L0TmoxET1hJ3wN2SxAzAG2PsQCHNzjXG8HcZ4843iG0UL6QE/OQSQlKDCcYowkTQDcr4HExJyTUnpIMVkj%2B4hv75KUIUwBJqSlRPaVYSwlTqmDOTg0zIzTWnWSPdYLpyden9JqQi2wLi5GZFGeMnIKyghjLuXM1ZCzGkHKAwUTIAHtlvvsI0roIwrm/qOQwODUwShnMOZcn9GHbkzPQ7ZJYKxnn4age8tlnA9ixpdfGt1HrVUWWBRq/14LKHF1INC2FAxX1dxJWSpVWKzRMrNGafw2LJCn3GDauBY9bCcpYzy%2BAfKV7IMjeG4he82CcElVglgChUpX1Su62Ecp3j33VU/LV66cl6u1YaopARSBmvATwS11qPl2tXicPYqCKPEBYNp3T%2BnDPGazBAQhvrQW538EGrlVDQ0oFU3EFTor4h6dpnbAzDc7bBYdr50%2BnDU08MoBmpOea1FiKEfmmRcji0iqUSotRjbMCaO0WIGtBi60zqHYYixjgrGwPbclTtBju2wL7cIwdviR05vHaE8JM6ZIhtiYhJdKS0mMBzZZ3VW6DU7qNToezBhD3lJPe4l9dTL0CH0YSN2ZSOkWAfT0uImqBm1Ogx%2B5wEBXCgb/egSD5zSBrJAwh%2BZ4Gii4fuYc99nIUPfaQyhv72H4NYYuThtDEP8MKCeV/FzpGR7ka02fHTem9gZaM06d49GzMRbztFuTUKYVwsoJanjIAzBKv8P4BI9cGUDw52adurK8fSYnlPSFpBS6SDNLfATXApAN342irgZoiUcH8Lj210m6cq7voLjXwbuWLCCekZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/reiterate.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_reiterate.test.hpp)
