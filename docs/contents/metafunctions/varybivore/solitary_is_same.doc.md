<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsSame`

## Description

`Varybivore::SolitaryIsSame` accepts two variables.
It returns true if they are the same and returns false otherwise.

<pre><code>Left, Right -> Left same as Right ? true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsSame :: auto... -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsSame_v
{RESULT};
```

## Examples

```C++
static_assert(! SolitaryIsSame<1, 1.0>::value);
static_assert(SolitaryIsSame<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEtIADqgKhE4MHt6%2B/onJqQIhYZEsMXFStpj2jgJCBEzEBBk%2BfgHllWk1dQQFEdGx8ba19Y1ZLQqDXaE9xX1SAJS2qF7EyOwcBJgsCQbrJgDMbkxeRKQA1IdEe9gmGgCCY8ReDidCnoR1AJ4AkgpCrJjXNxMAHYLCcxkxHMgTmgGGNMKoEsQTlFUJ4TgA3MReTAnYEWKhiJTAgAie1BJLJAIB60223%2B%2B3OqBOADU6ngmFF6JcAfdHgRnq9Bl8fn89m5WcR2ZzMKcJVKubsrrc8WDapDoQI4QikSi0ZjvDi8QQHv8gaTduSzZTlbcAPQAKkdTudLttAIdTpOABVMGMFCdnW67S6Q4GqbdwZCAPpMBRKeoQMBgAW0N7EYW/NhirinLgAOg0lxAIH12Nm1ruarwyBjcdiBAgL1TQu%2BmfpbhzJy4RZLWMw5YtHHmtE4AFZeH4OFpSKhOG5rNYwYtloazLseKQCJoh/MANYgUeSAuSLhA3YaUcaMwANmvZgAHPf9JxJLwWBINBpSJPp7OOLwFBAL8tynIdSDgWAYEQEBFgIBIjnISg0E2OhYnCP5OFUe9rwAWmvSQTmAZAoSkPMzF4TB8CISV0D0fhBBEMR2DKej5CUNRt1IXQcwAd2IJgEk4HhhzHCdOL/AB5I54P5VAqBOLDcPwwjiK7I8zBOCAPBQ%2BgkXMddZl4ECtHmCAkGQhJULICgIAsqyQGAKQzD4Oh1mIQCICiTiolCD4hN4HzmHTCSom0TAHH80hkLYQQJIYWh3k4rAoi8YADloWhAO4XgsBYQxgHEUDSHwYhwscdFfU4%2BFwqOVYN1CdYRyK1Mon49MPCwTjjTwd9stICriBRJRiQ2fLUyMbd5ioAxgAUZk8EwHiJISRhItYxjxBY2RFBUdQiu4/R8pQBdLH0PAokAyB5lQBIqlhTgcLGdA9mJUxLGsMxfwGmjKqu1oyrSFwGHcTwmj0YJJiKEo9CSFI7uGPwc1hvIGG6KGZn%2Bhx2nGBG9DsAHqnGNHelKAZOlxnNwXqYnplKeYFGXFYJBEjhx2/cTOAU7C8IIoiSPUzTcEIEhcTXLhDM3Sb5gQTAmCwOIID3fxdjzABOXYgUkDRJDMSRr0/Udr1V58OFfUh33XPNry4a971V%2B8bcPLhR3V692aKv8AKAyXQNMqCzJg6SEJsuzdPQthODqFh0SBHCmGhAwjC7VW83zadKOFmi6NkDbmOkVido4/aQGcviBP8lm2Z/XhJKD2T5KjmO44T/Lk9TgtNO0yzdNF3YzAl4ywID0PYkQ2zUB0vpG9j5BE8c1WuC/GhaDcjyvKKwK/L6zfgtCsrIuixgCDihKkswFK0rETLItysbVmnEqAYqrL09UGr1kihqKk4lq2veDr75GUlL1DcA0hqYBGnlIw41QC%2Bz4DNOaC0lorUnBudaohNr522uxPa05dDOTnsdd6p0WqXUVjOW6aQsqPQIM9XYr0ToWE%2BjXb6eAsBkPphUAmfgICuApqQCGhQSYw1yPDUGWQkaiLSDTaGlMuFY0JuTcRiNMZ3Q6NTSGwjKY42UXjImmjabMwWEsJm4sTZVw5hwM4xBo6x3jrPVuXAU5p0FlREW%2BlxZGSlqQGWcs%2BjkKambC2KdtZAhdkCM8Os9Ynndr%2BTgXtgKTXAv7JAsEZJjxHsQcOqwo7KRYAodEUJ0ROLzHSMYFE3FZxzOgpi/QC44M4roXYpAy6CWypXMSHtOBSTgkcE4clrEsDyQUopJSyn8i0hPbusRe67AHkk4eUyrIZKWbpEsyAEgJCjMU1WUZxkxhsfhFyK9Yhr28r5dMkUd7vBCmFCKfVD6xXiolIqyVUrpWvn1W%2B0DAHFTwKVLGz8qpv2QLVT%2Bghv7NXOn/ABXVgGRTAckCBo1oGhFgSZeBTBZrzUWstVafUamYJkIIQuuCdAgGaYQt6VgSHnQ4RQu6WVbRPSITSphX1Yg/XpfjBRPC%2BG6JzIIqYsjSDIzEZkFRYrpEGJFTytROiJV43kfKzoMiMZUwaAKsmGihGGLMQzExzEOmxJrpzXJBF8mFIxGMiEvoJlC2or3TxPsTLS1lvLSgLMgklxTrsXYo5Lwnk/H6oEtsTUznibYb2g9ZhK0kKONWo57w3lVpIVWZ4NZcEpZwXYnS4n/hdTuE25Fw2e0LbG/qpzAaSCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_same.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_same.test.hpp)
