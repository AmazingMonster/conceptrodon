<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Monotony`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Monotony` accepts a variable and returns the variable via member `value`.

<pre><code>Variable -> Variable</code></pre>

## Type Signature

```Haskell
Monotony :: auto... -> auto
```

## Structure

```C++
template<auto>
struct Monotony
{
    static constexpr auto value
    {RESULT};
};
```

## Examples

This function injectively maps a variable to a type.
In the following example, We will create an overload set of `fun` using values `0` and `1`.

```C++
constexpr auto fun(Monotony<0>) { return false; }

constexpr auto fun(Monotony<1>) { return true; }

static_assert(not fun(Monotony<0>{}));

static_assert(fun(Monotony<1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Monotony<0>) -> std::false_type;

constexpr auto gun(Monotony<1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Monotony<0>>()))::value);

static_assert(decltype(gun(std::declval<Monotony<1>>()))::value);
```

## Implementation

```C++
template<auto Variable>
struct Monotony
{
    static constexpr auto value
    {Variable};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BeqnpjgKh4VEssfFctpj2hQxCBEzEBNk%2BfoF2mA6Z9Y0ExZExcYm2DU0tuZUKo31hA2VDXACUtqhexMjsHASYLMkG2yb%2BbkxeRADUAGqNeEzR9IfYJhoAglPEXg5nALICqEQMAE8ns8TAB2KwvM5Qs5TJiOZBnNAMKaYVTJYhnE7nABuYi8mGB0LOYIsV2INzuBNBABFDhZiS8wbT/BCQS8APQAKm5PN5fPZwK5PLOABVsEIRUIzryBRy%2BfKZcDBbyzgAxPDEKaizBaxUvJEotEYrGoM5ULwMCA/Bh/ARAo4aB6LYngs7ETAENYMM1iJR0l20xn6gSG9GY06m82W622wGHNxcJ0u%2Bnuz3Eb0Ed4ElkBpUvWHwgD6TAUSiaEBtBDNFqtv3%2B9rcjv8j3BTMWizpedeDSLJbLBGoNZj9fjiebJLbHZZXaF3LOQk6AnQ2t1PNlILM/jCyG8WGJR1OdEI9seQeeBu2RvD52AQ7rdvjTewzoAtA8YQR0CAQFRfZhCwQALJNmrLAheqJhiaZy3tG95xkcY7Pmcb7Nh%2BX4gJm%2BIAUBIFdgWeDIMWpZxAOlZnFgO6AcB0A1lM6EUbQuK0PGw4Pg6DwPBA7aLN%2BTH4lOoH5j2BFEf2EAMVRmA0ZadHfgxTEsXBDaIZx3G8XimACRwyy0JwACsvB%2BBwWikKgnBuNY1gwqs6yYMSm48KQBCaNpywANYgHpkgAHQaJIXCgv4Gh6RoZgJAkZgAByRfonCSLwLASBoGikEZJlmRwvAKCAKXOcZ2mkHAsAwIgICrAQySnOQlBoLsdBxBErCbKokUJC%2BCSSNByAIlI3lmLwmD4EQ5JfpU/CCCIYjsFIMiCIoKjqPlpC6JUADuxBMMknA8Dp%2BmGS5pmcAA8qclVVqgVBnC1bUdV1PU%2BWYZwQB4dX0Bi5j%2BEsvB5VoywQEgtXJPVZAUBAgPAyAwBSGYfB0NsmqUNEB3RGEjQAttvAo8wxAAkd0TaJ0eWObVbCCEdDC0OjS1YNEXjAMctC0Nl3C8FgLCGMA4jUxqhN4NiOoHainSnJsjlhNsulLbQeDRBtOMeFgB2ZngiUs6Q/PENEaSYNSOwc9LRgucsVAGMACgXHgmCrUdwFGY543CKI4gzQ781qAdK36BzKCWZY%2Bgy9lkDLKgyS1MzL50Yc1KmJY1hmOlGsjQLQdVDUmQuAw7ieK0eghLMpTlHkaQZAI4x%2BJU%2BQlww/QFwsqe8wIPRjNnEz110jfTDXgwVCMvRl3osJNF38wVMsCg2RsEi7RwBmpQdGVXa17WdcA3VnL1j0QLghAkPZn2LN9RvLAgmBMFg8RcaQHmSP43kAJz%2BKCkh%2BWYkgJMlekJHfsUcPFpCJZ9byCQuAJEinfSKICvJcD0g/JIaVeAZSyjlJyRtColX%2BmVU6VVQbgzeo1NgnBGgsGxKCF8TBEQGCMOvO%2B3kuC%2BQGkNEgeBRqzUdlNCQ0hXZKHdktXQMN1qbQxtPWe8DDocBOhVU4ZwLqYmIMQ0h5Cdwc2obQ3yT0XpAzenvMwB8UH5T%2BgDVAr04jVTBkYzRQwiEkJfEoowXA75cBSjQWg8NsoQCRktLGaMMakC8TjPGBMHA%2BJJowAg5NKYHRpnTBmTMfFs31psEy%2BB3RdH5szEyQtkAix8eLaoB1payzRgrRJ31ySq0chrLWShdbsyMAbUA%2Bi%2BCm3Npba2tsfEO0ms7Thsg3aLRMnwr2hsY5WD9gUwOl8Q5h04BHT8UcRlxwTnEJOEyx7VAbn4CArh%2B6VDziUbuRcCiZB2SkYutRh6F0mOs9udRpgnI6DcpuMx9kjwHnclu5de5D3zgcpYKw1iTz%2BZLER89OCyPkWQihyj7GqI0E9bew095fT0b9Y%2Bp9z6UGnn/ABNC/KghgaCQKkhX4dUqKIxBthkE/QKkVUq5UzqmNwQ1JqhC5G3RYAobECJsQwv2DqAgDCd4jT0J0p200elzW4f0nQARSACK2izYR%2B0loZQkWdaRl0iHss5dy3lcJ%2BXqPMcDPe/hdHUoMSgI1b1GVWqGFy5IyRCw8rvoWPlUxixss4XDOIbiPEmT8VTRyAaAmE2CUY0mYSKZUySZgWm9MxCxLVvEupJTSDJN5mkwWqhhbbByYIPJUsZZywBMUpWZSfGVO1jU/WYQGm/SaUwM2FsrY20YB02QXTxWsL6R7WVlDjC%2BxsOM%2BAwdQ6ZGZuyWSCzLDxwQYnZhydL4PNqBnLOORPl7LmJc05RzS4fMOVXC5ddl3dHeeuge1zahPKPT3QezR92TE7j815fzx4AumkqueKqwVas6hyrlZxnXeTdVWLejD3oOTNUfUgJ8z5DEvpLbFIAzA0P8P4PSIV/LJTQ6CUBX70qcCQblaD189L3z0pFMKd9JB30Co/LggRJb%2BGVQRzKKLXI/36vhhBhH2PtnVj69OkggA)

## Links

- [source code](../../../conceptrodon/monotony.hpp)
