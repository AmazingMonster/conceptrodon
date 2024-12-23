<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::TypicalPaste`

<p style='text-align: right'><a href="../../../facilities/metafunctions.md#cotanivore-typical-paste">To Index</a></p>

## Description

`Cotanivore::TypicalPaste` accepts a list of packed containers.
It concatenates them together and uses the first container to hold the result.

<pre><code>   Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
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

Here, we paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** Container ****/
template<typename...>
struct Container {};

/**** SupposedResult ****/
using SupposedResult = Container<int, float, float*, double>;

/**** Result ****/
using Result = TypicalPaste
<
    Container<>,
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed containers.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed containers at the front directly and place the result into the first container;
  2. Invoke `TypicalPaste` with the newly packed first container and the unhandled containers.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
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
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQAcpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIsqfRsgkx99yeXN3fnAPOv2uV2uBEwLwM4JMgTcBAAnqlGKxMAA6dEw7CgubELwOe4AFUReFEtGUTDmmHuJgA7FYaQARGFWG6gvZ7e4WClUtzckCg0HgyGfTAwuGI5Fse7k5AAa0w7lkTEWxEx2IIuPxRNSJLE5MpYpl8sVHxVatZdNB92t9y8mSM9wRSOpgQZ0qYcoVHlNkVVgRZIMZzIFfw5ACV6ltMgA3Hl8kNgiGvEUC2FWm1C5PQ2FOyVojGBbD3ZAGBQKe7e5oq66kdPWzNQ0U5iXMNjo1GY4ul8uV5W%2Bmx1x0tlHt7BvRgEa4KUjUm42odI1v51FjiETizTwe5pftgDyBAQCQUqaxNxxeIIhOJpP12bcverYtX70nCnbmJnD/7T/Hgg378LGd90PYg3wLU9AwDec7QiYAFypGE3W1XUyQpaE5xtMVB3nL8EhBWFnwnKd2xnQi/zAjtAOwm1gKPd8MOtTEQBAXNgwtJl/QTf5AVOYFuPubBVFYV4qR%2BNkeKBBNzECCISy8LAXThLwRPNEE/hOCslRVb4LkFJNGzFbcR3A9VNUvXDiGpS0g041l1IeIRlKKBUIwULxaEvMSbhgh1HNSZz0Fc9zL0QzSfQSMUIgIGcqFoVBPhiuLPgOGd0E2WJ6DVWy1NuDSgo8nSjmBHy4PykLXSvHUbzQ0VWTTBiwqrX0sKohq5nQZiCGUzLYSij9Z2ued2s67qmzcWL4ui%2B4JuSj9B2GljRrFNKvAypsIKYliJTYnL%2BIJTA5kKg5gTmT4SQAfQpJRWggBaFBRS7j1hMqZz8gKysxVZmQ4dZaE4fxeD8DgtFIVBODcaxrHuBRNm2BCzECHhSAITQfvWWUAkkVENEkLgaUCDR/A0MwADYSbMJIUj%2BjhJF4FgJA0DRSCBkGwY4XgFBAJmUeBn7SDgWAYEQEBNgIVIvGiigIDQF46ASKIUU4VQkhJgBaEnJHuYBkGQe4pFRMxeAVQgSDwDquBkQQRDEdgpEt%2BQlDUVHSF0C2AHdiCYVJOB4X7/sB522d3CXxcvVAqHuZW1Y1rWdb1rGzHuCAPFl%2BhLOkrhVl4HmtHWCAkBlnU0/IShC7lxJgCkMw%2BDocFQMoWJndiCIWnhH3eGb5hiHhXdYm0eoeaRmWX13BhaDb3nSCwWIvGAXlaFoTnuF4LAWEMYBxEn/BiAHvBYyXkHMFUSNwXb8hBB6Z3aDwWJPe7jwsGdjU8Hp5fSFjYhYgyTAGQhdfr6MKjdYsUmDAAUAANTwJgN2u5Fxn34FbUkttpAIIdiodQk9Xb6HXigSGlh9A305pAdYqBUh9CXqrdqiFTCWGsGYVmH9iBmwOvAdYdQGjOAgK4aYfgLZhEWBUKoegihZAEDw4RGRREMGGIIsYFt2F9AGFMTwHQ9AKMaPMGRoxEjyPmOI3RgwtHLB0Ww2GOwJB%2Bw4ADZmgdOCRxVurTW2tdb60ThAXAJt04I0ztnIB6xDxMCwIkCA6MQCSECKiAAnIEGkkgcZmEkCTRm/gSaRP0JwWmpB6aI1RCTLgJMkiRKSPk/wuN/DRJJjYyebMOZc2RkA/mQt84ixDhLEu0tUCp3lorDgLQWDRhpKrJgXZ1560iaiLg2Mjb4CIEw829trbiDtqgxQ6Dna6Grh7L27dLHWJZrwIOrSw4Ryjo4kZDouDjMmRoJOKci4JGpAjMwWd6m8zzgXTp9yyBSzLmnFABgjCXK4EzGgHkjwNybi3buZ9O6t17v3BwZ9h4TlHuPZ209Z7z0XmfVe/9dgg23rvfezsj4n12EjKKl9J7X1vq3B%2B%2BLs5MNfkjD%2BX8lC/zXkYABoA3l8AMGAyB0DYGMHgbIRZyD7arKdpgkA1cAXGDwTYGlRCQmgzIdkChVDXQ0KsJYehBzGHMJVWwnou9OHcJUfkPhDB0BGKERbERfR9FpEkX0O1cjui9A0YMZ16iBBKIWOUbRai9GWt4RMQxAjg2Zw2FscxMbqZ7NsRwex0dNYllGZciZ2Mk4eNmY8xGLyc5o1IAEoJlBLGZOyeMnGNJyk0nxpIBJGsLb7NBpwWp3MGkC2FqLUO7TfndLYJwPpMcWAKGjLraMWbGxzGmZ4s2ehUHiokCg2QUqMEg10MELZ3tl67IDtUzgwcxYS3uOHSOY6J1TpnSKQ6ydPnlwLYEIt3aPldO%2BaXR9fzJ3%2BXOtOyJ51Z0EHOqoDWNcwX1wgI3SesLoVvzgz3PuA8kWdJHmPCeBLMAzznmIbFb9cVcoZVPPAO8GjEsnqS5AEtyW8EpdTEGNK77wnpU/JlZ9WXfw5f/WCDSQECqgTAuBb9l1INXZKx2m6dAgGCPK3BtD8HKtYWq8hnA9jDR1XQhhCQ5ksOIZ6s1fguE2udfwoNxiJHFGyM6x12R3U6IMxw/ooa8jhr9c5yN5n7URuUa5kNnmlj2tMXG22B6qmszsWBzW47J33AA6iYDuaZkkALT415ud/GYECWMVV1Mq2yvGYEQI/gia40ZkVmkBTwsHI7bYOpxbVihMkP4KJNRSaRMkJE/GMSuCyc4IEQ9EX2bpZLdTQ21X23DYa%2BsD%2BmRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/cotanivore/paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/cotanivore/typical_paste.test.hpp)
