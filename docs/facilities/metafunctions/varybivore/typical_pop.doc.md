<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalPop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-pop">To Index</a></p>

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>, V<sub>n</sub>
-> Shuttle&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalPop
 :: auto...
 -> typename
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
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2>;

/**** Result ****/
using Result = TypicalPop<0, 1, 2, 2>::type;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM9KuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXGJdpgOGUIETMQEWT5%2BAbaY9oUMdQ0ExRHRsQm29Y3NOW0Ko32hA2VD8QCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIphJrozIeJgK1wenF1fHv4df5zOlwO1yECC8BAI9A%2B%2BwBBEwLCSBnhJgAzG4mBDUAA6XFo7BAqbELwOUHgyH0NFWC5An47a7YVTwhjoABixFkML2AK2W2uAHVMNcAO50WjXLxKa4EBB4d5ULwMGoCaWoWl8tBKpjM7VCmVCpLEN6xABumHQ10MFqNyDWSgtSV6CmxQPhiORmDRbgIAE9Hsw2PjCQRiaTGcy2RzBNcTAB2Kyx25UoGuhFI3Vet3plHozFEXEu1HYa7IAwKd5CTAARy8z0wpEtWILADUGngmFF6AogxciSSCAyma52bIvZWa3Wva3iO3O28C0Giyn40DrmvpWmPV68zjcRZMMBQgxQsBu0uLuuJWkjNdlExgEK0bdQdXa0rPej94eGMejM7cQ206zl2C5Lqi1KAomyY0t8fxwf8tIggAku6CKMPUXRciciHwbhAKpu6Ga5k2eLnucfakgAKn6eCiLQyioEkMYrlB4EphcWZbsRRDXKyeDEFMPbkSG/bXNRSS0WIDFJF6fECQQQlxhBl6Sie0p%2Bo%2BqLPmCEJQh%2BbiLhBcZJmxMHnJxREYlivH8VMDY7i%2BmroEJFEDuJkn0Yxsm2QQDaVk5ikrhe66qTevqPDGWlkrplLonJglgUZrFGRxm6WQ58W%2BY2PH%2BQI6D2SR2IAPL6gJLkiVRNF0dJ3nyX51R5Q2JUILE/6FgSNJBecKnXsA6mPKu65PoOEYjoImYaQGQrudVXnos1rWgdgIAgOFH4dd164rRZ8K3ve%2BmZfVAWJcuJkpcCuGfDheyDqwSJCldsGXbC7GAmYqKhKWXhYJFbiahsSQEGeG3XfSOkUg9L2pYROZWfmpEba50UQ9BgJPTdQheEk%2BTmgASm8Xi0AOj3nKFfWY9jqR4wTRORdp5J6V6GgNlwDZmIZr10tc%2BMKITxNQ6TvXczTA7DTNUlzW4zPXKz1xmGz%2BLbRpqOg2Jbz89ywbarRAD6TDlrEBAQFM6ArQorCYHrZ5uDzfN%2BVjOPoLbRP4osVIcMstCcAArLwfgcFopCoJwBmWNY1wKKs6yPu9PCkAQmge8sADWIDe5I2IaAAHGYZjxPEXDe9nWdcLGsbSF7HCSLwLASBozP%2B4HwccLwCggMzCcBx7pBwLAMCICAqwEEkELkJQaCInQsThBbnCqFnABsAC0C%2BSNcwDIMgMsZ2YvDmoQJB4KbrP8IIIhiOwUgyIIigqOoXekLorPCsQTBJJwPCez7fuJ0HnBFRCEeA5UBUGuPPZeq916b23tiMw1wIAeEnvQYgMZY6LF4J3LQywIBIAnhJZBY8IB4KnnEYAUh5Y0CJq1SgURf5RFCA0H0H9eD0OYMQH0RUojaGqJ3OOE82CCCKgwWgTCH5YCiF4YAGJaC0DbtwXgWAWCGGAOIMR/EeF4DNHIwOmBVDVAhJsOOoR4SV0DrQPAURX7sI8FgX%2BIY8C13kaQM0xAohU3uEoow5ijCJ2WFQAwp5myvGFEVf0zDr7CDopfaQp95BKDUL/J%2B%2BhlEoGsNYfQFi26QGWIxLocil4myfKYMOlgzBNxcTOLAWSIDLCqMqPwEBXDjD8KzYIsxSjlD0PkdIAhmldNSD0hg/QOlDFZnUroPQxieBaHocZtRpjDMGHEMZ0w%2BkrN6Is%2BYyzalRw2BIL%2BHBfakEbrwZuYDF4rzXhvLeUhYHwNwAfFB5hURcHQfHXxywWpMCwHEGppBU6SFRNieIqJy4aEkAEBe9dvYL0SJXaupBa4vOxAvLgC8s7xBLgvdOhcQUL2Ob/Zurd27vK7tg/uODB6ANHhQIhqAkHT1nhwBoLATSxiXkwEsBgbxcHiNiLgmc974CIJUvQsTz7iCvrE2%2BCSH66Hli/N%2BzCDlHJOX/DgADh4QmuCA85EC16lmUTLPlAqNDwMQfg2IqDURmDeZg7ulLiEENpU6oYhqjC8q4MzSh8IBI0LoQw9h4TWGMM4dwhw4T%2BHoSESI3%2B4jJHSNkeExRyjVGB3wDaRwWjf66P0fCcJxiOi/3MZYxhNjNiB3sY4uOLi3FKA8amk8vi%2BABIUEEzAISwlOPFVEiQMTZAyvvoHeVySfHFKsJYDJURqk5MBhkfJhStLjusGU05FSj5vHgLUjoGjnCNJZGs0gbSShLP6QUDIh7uldE2Z0sZO76mTKaNMnId7OjzI2e0096ypnZBaSMD9J6tn7JWGsPZrz9DfwJQ/M54DLlcqNby/lmd7nCpINa15GCPmkC%2BT8ygByEVIr5eC2M3t4hl1RBCyQq9WZqqJbYEl9ryXwEpUPIBhDXXEBnmwTgLLIEsAUCaLeJpEMeimEKx5R8xWyAldEiJg7EkgFRKQRV795Eqp/tB/%2B1LgGgNUHxgTQmRO6imOa%2BllqnnvVRHa5tjqzMkPY3Z5BIBBPYx1sJ%2BIOtRMEB1npmJdBfVtwgLQh%2BIag1ONCxwrhPDI30oEQQGNoj02YAkVIsQSanEpq8RWhR6iajZofrm20%2BanGFtMbwEtVifTlrsTOatvBa3uIRI2nxZKW33jbcE0JjBwk9ovn2uT8Sh06EU6O4waTJ0lpnUHOdAg5FbBNqkkpFhV1B3XVUrd7Q317qac%2Bv9x65i3uSAMrol7jsZBvaMzbu7uirN27M%2B9EyFmfqA9%2Bp9v7ZlPcA7enZoHL7qag03TgYD9OCeuO57EXmUOPPQ9ZslnzMDfKGH8%2BFNd/B8tRKib2RdJBeo0Bj2M6KAenM4MSjuWGAXe2BaXWM9cs6SALlwHOZh8WV1RBpwHLdSVYIObvIn6rMNw%2Bca1DIIBJBAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_pop/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_pop.test.hpp)
