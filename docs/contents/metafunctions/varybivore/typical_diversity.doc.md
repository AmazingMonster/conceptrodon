<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalDiversity`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::TypicalDiversity` accepts a set of nonrepetitive variables and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every variable from the previously provided set and the arguments;
- doesn't contain repetitive variables;
- preserves the relative order of every variable;

The resulting list will be held inside a `Shuttle`.

<pre><code>   Variables...
-> Arguments...
-> MakeMathematicalSet(Variables..., Arguments...)</code></pre>

## Type Signature

```Haskell
TypicalDiversity ::   auto...
                   -> auto...
                   -> typename
```

## Structure

```C++
template<auto...>
struct TypicalDiversity
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };

    template<auto...>
    using Page_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `0, 1, 2` to `1, -1`:

```C++
template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = TypicalDiversity<1, -1>
::Page<Args...>;

using SupposedResult = Shuttle<1, -1, 0, 2>;

using Result = Metafunction<0, 1, 2>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

This function used to be a helper class for `Varybivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Varybivore::AreOverlapping` as we won't worry about short-circuit here.
After instantiating the first two layers, `TypicalDiversity` has two lists of variables to work with.
We will implement the function using recursion over the length of the second list:

- **Base Case**: When only one variable exists, the result is:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.

- **Recursive Case**: Pop the first variable from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.
  
  Then, we invoke the first layer by the popped second list.

To check if an variable is in the first list, we use a method described in `Varybivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...InspectedVariables>
struct TypicalDiversity: public Vay<InspectedVariables>...
{
// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            Shuttle<InspectedVariables...>, 
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQAcpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnufYJhoAgk/PBJgsqQYf525MV1QJwAai08ExYvQHm85sQvA4TgBZASoIgMe4vEwAdgsJzmTEcyBOaAYc0wqlSxBOAKIJwAbmIvJgzjjQcRwZDMNiACLnXE8vlvN4fL4/LkXGmoAB0MuhL1h8IIJyECCuBChgSsmJeIu%2BBPF/0BMqlAElSal6h90GyOfQFHLngqEQAVW6pPCiWjcvB0hLFW4gE6pLyQj1IlFo%2B4XM0KC0OTDWsEQu0PY1CnFvAD0mZOACV6ltMr6Tv8lCA3idKyddWK/pKTjG444jDbk5hSNSjTL83NW5z7YFHi8q3iCHCEcpiKjUMomMAucOq9itc8RyOvJkjNW3czztzR%2BgQCgBPg%2BmIK2vK38L5eR3NDyA8AoAPqxJhKZ%2BoKh/ZEMafov5G0tCJgD7DVsA7V13U9b1fWIf0HiPBlvHbM5F1vKsoI9MRYL9O4OxvDCTiwmCfTwggozcID40Tdk2wUY0O2o5tQKTTkHQwxCQAoi0jxrfUTknadZ3nP4ewIMDMAY2VBz4ndBXQlleU1IUXmzE4LHfZlS3YQj%2BN%2BCVAQbc1gJbNjwMIp0lSEogRINZiQMkjilwzRT103YBtwtM5An3e8jxJU9snPNylwuQiMP8x8XzfD8vx/CMBEohyzLo9jB0gt1sK9Mj4LuLjkKZAjQsvFU1Q1KiTJoyTpKlB5itXIjKzKgh1XsqqrRqxjjNjUzWLSiySp87A5ItBTGqvLFlJXPTPj1AzDSIY0aucysNxAwS513XzBKnWytr%2BLqZMeFTMSm8aswAKmum7bszK7rudbAhGdG77rU27Psu97XkxMwDgYI4vFOP4rjofLB1U945trQyluOmEx0VZVVVajUZp1GH9TrLspWeYhgAHIdnnWrdEUwZoqC8QG%2Bh8/cSJw3KEIuLgOwAWi4B0jzsv58cJtNIdO36SY85UvFSIoEx7LxaCVPcUfKg1WZODmOw0DszGhIW3lJzzpdlumkQppgqZp7I/nVk5lc12TuPk7X5WaQln3fJRWggKKFFYTAXYHNx9YIDshHFyX0ADh5Vj5Dh1loTh/F4PwOC0UhUE4NxrGsPFNm2Xd/p4UgCE0aP1gAawCMwpSxMxJCSJJ/A0ABOfwzA0AA2JJgljjhJF4FgJA0dXE%2BT1OOF4BQQHVwuk%2Bj0g4FgGBEBATYCGDQOKAgNAvjoBIom9zhVCSVu2dbyQTmAZAiSkKUzF4BNCBIPBD1Z/hBBEMR2CkGRBEUFR1Gn0hdCswAO7ECYKkTgPAY5xwTkXFOnAADyVxV4nC/CcA%2BR8T5nwvlbSQ18TgQA8FvegVJ9hcFWLwKeWh1gQCQJvd0xDyCUDodvRIwApBmD4HQD48FKCxFgbECILQAzcF4AI5gxBbjwNiNoS0EDeCbzYIIeBDBaDCOTlgWIXhgD/FoLQceIjSBYBYIYYA4h/74GIMBX0%2Bjk7kgLB8OR5BBA9FgTcWIoCJEeCwLAsceA%2B4GLgrEDImBuSfBMTcIwRd1hUAMITYEeBMBAPgRaRO%2BcX7CE9B/aQ6Sf5qFgYA/QJiUAZ0sPoPAsRx6QHWKgVIfR9Fs3vHuUwlhrAt14KgOC7IsCVIgOsOoDRnAQFcNMPwrMwiLAqFUPQRQsgCBGdMjIsyGDDEmWMVm/S%2BgDCmJ4DoegNmNHmCs0YiR1nzHmacwYRzlgnL6dnHYEgoEcHjqQIe7TOBoMPsfU%2B59L64LMPg3A98SF53IQXKJ6wECYCYFgRIvTSBl0kIEKUDdAhYkkBoSQ1dW4D38K3Bu%2BhOA91IH3QIXApSty4O3BuSRKX%2BEkFwfwKLW4vNgSPMeE8wXT2oQvGhS8kFXEYRvVARCd57w4C0FgdIsRsyYMSAwW4uANylGS2xp4H5Py/hk9%2BEhsmyFyX/ZOugOEgLAXIx5zzXlwI4IgleVwUFUGpMQSV0rZVHBMVbJVKr8GEPoQkM4/0zCgsoTPXlzCGHrzDWMCVUq2ZuqMIqrg6saCyz9Lw/hgiJGOLEUIqRMiHCOIUYwAgyjVGwI0VonRejHFGPCbsdReBLENGsbAuxyAri7HzhED4Xdk5uI8bcLxdaKHsn8fnQJwTQnGKMBE0AXK%2BCxIUPExJyTGCOPSW/cQn8clKDyf/I1hTInNKsKUtxPTqm1OyPUxpvkj2tOHp0x%2BUl4B9J6MBQZwydn5DGQwdAVypmsxmX0c5aRFl9D/Ws7ovQDmDGA/sgQWyFjlGOXss5n7RkTEuRM5DZCNhbHuThruFrWXvOjS6uV7rFXKqlBoAFargWkqDeC0gkLoVjDhV3IlJKlUYqxIyrEWJAiYskCfVmlq2W2A5cG7l8BeXL1XoKyNxBd5sE4BKzBLAFB0iJHSSjYo5i3zo4/PQ67Mk6s1fq/JIBggmvASI81MD/4jxtcg1BanT4aa0/SXT%2Bo5jeuFb6%2BjgRGNztDf5lhCmwvEJAFpiWz4dMN2fHpggLsnUn04SmnhEA%2BH/2zZmgxuXJHSNkQYwtSiVFqN4OW7RYgq0GJrdOodhiG1WKff/Vt7bHFdpcf/PtQjB0%2BJHY48dShJ3hJAlE%2Bdc5F0JKSSktdsgN1ZPMzug1OgrMHuMCUmwp7n0pwvQIfRmZ/K3ssG0lOD7um7bg34IZP7gPjKQ9chZxRsjAcA9kcDJzINvv6KhvI6HrsIc%2ByhmDaGQetGBzhhQdyP72ZZY5kjqX3Oae095j4vmICAqIPRshFCmMsZhZQR5nGQBmCVYEQI/h670oHhTrE7d4fD04OyyeTGEVYmvrxrgUgG48ZRVwLEBKOCBAc0z0enKqGPJvozt54upPrDgpkZwkggA)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/diversity.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/typical_diversity.test.hpp)
