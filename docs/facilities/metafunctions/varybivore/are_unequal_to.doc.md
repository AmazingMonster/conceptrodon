<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreUnequalTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-unequal-to">To Index</a></p>

## Description

`Varybivore::AreUnequalTo` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are unequal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreUnequalTo
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreUnequalTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(! Metafunction<1, 1.0>::value);
static_assert(Metafunction<0, 2, 3>::value);
```

## Implementation

We will implement `AreUnequalTo` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreUnequalTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        { (...&&(Variables < Target || Target < Variables)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Variables < Target || Target < Variables)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQgAMxBAA6oCoRODB7evv6p6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMiTcTC8RCuABUmsBMAQIdhAaNiF4HFczsRMHIIgBHLxiOGoQEmADsVnOVzpV2BoJemAhUJhqAAdFyAGpNPBMGL0BSowH0q4YrEEK7KYioIjKJhI0X0qk0s5isXTRzIK5oBijTCqFLEK7Q2EANzEXhZtI1dNVVwgXI55gAbG6ILziPzBZgFFdWfDEciA5S3FS3EHiEipYGvT6hQsFqGACIQtViqlpxIZlW2umMh7M1lmzlcs7APEgxgEYWJNH5q5eDJGaWKzABxIp6Wy%2BXt1kVqtPWvOkU5imNwtglmQ0vO%2BMCoUixtavA6vUGo0mmKoTxtpEAfXNAcbDqdXLdHoXvv9gYR0ZDEYjUZjncj18Tyaz6YplOzasBb5fgOf4gKubBVFYB4Ow%2BQDgL%2BCcLn2K4AFlkSYKgvAYBwsneY5ASnYtZ3ZZ1cWAOsGzOZtwmAVD0Mw7DXgpLscTxAlMGJUlyUhLhlzOEAQAVJVITIhRR3rH9zjg644T9KVYPOVdkAPJgFCUZoIDAMA6MaBicIEVkuFIK4uA5DRUQEy1vEwBZJLOJSVLU%2BICAgNDdKw/SGFZDRjLMYzEgskArOtWycw4JZaE4AJeD8DgtFIVBOHDSxrHFFY1g7cxEh4UgCE0cKlgAaxAAJJDMgAOMwzAATmqrgAg0cryq4SlKWkSKOEkXgWAkDQfNi%2BLEo4XgFBAHy8ri8LSDgWAYEQEAVgIFIYXISg0HuOh4kiVgNlUcrXQAWldSQrmAZAdSkDkzF4TB8CIb10D0fhBBEMR2CkGRBEUFR1Em0hdCMgB3YgmBSTgeAiqKYvyhLOAAeRhZapVQKgrj2w7jtO86TLKsxHQ8Db6BNLKuAWXgJq0JYICQdaUk2sgKAgWn6ZAYApD8mhaGBYhRogGIYZicImgAT3B3hBeYYhhbhmJtEwBwxdIdbhzhhhaFFv6sBiLxgChWhaFG7heCwFhDGAcRNbwPEcPNP0YcNeWYQ2HLwmBDr4toPAYhBqWPCwGGCG9HqjdIW3iB3JQUxBM3PaMfKlioAxyO5PBMEBuGUkYRXnuEURxA%2BnPvrUGGAf0M2UGsax9C90bICWVAUleQ2DtGdAIRTUwUssMxBrDh67brzp5deFwGHcTw2j0UJwgGcohiMtIMleCY/AXwpXlmQYEiMuxh%2B6MYWgnvId5qPf6gPze5%2B32wD5XvRpmaS/5lJ5ZVnWCRIY4aLSAG3ghrR/aR0TpnQurjR0uBCAkADGYbKZNcrxyWAgTATAsAJAgEVfwiQOTVUSG1DQkgzCSFdH1AIrpqr6E4F1UgPVsocldFwV05VqrNVdKVeqODXQ/xhkNEaY14GTSpnNamC1EYrUZszIm202CcCaCwc0lIDpMF1AYVsXBqoclMvFW6kCHpPVkK9fO0hC5KGLn9XQflgagzFp/b%2Bv9YYcARktGEVwUYAIxidZAKjaJqI0WZfGqBCbxGgYkMwcCKZTWERI%2BIq0mYBLpkTFAXi1FcB8pzbmvN%2BZ/QliLRW2SpYyzlgrEOysayq3VjDLWOs9YG0VibGOGx4r4Gto4W2hstGqEdsCRWrsagw09t7EWfsGnkyDorMOEdMBR1NkYWOoABF8CTgoFOacM5ZxDjnAx70jGyCLr9eK5iy5x07lYSw1cYi13QQlRuWRm6t3bsc6wPc/59zwFgC5Sxd6eVHuPXIq9ghjyfvPUgi8ijZCPn8kFG8Z5zCBZ814PRxjgvvqfTyCK%2BjQq3vfW%2BSKd4XwxVfD%2Br8MqEo6rY7hnA3FAOUWbEy6jNHgLulAkmYSEGkCQSgoYlyOpUJoeo/BlIAjVVaokAhRDJBGTsTw2wfDwmCPgMIxaSMYlROIFIjYsjMYsAUOaHU5ofHTlGDdRluijIbLzlsz68gTF7J0EkUgliwZGxsdDP6Q1HFIxcajVQmrtW6v1cyUY/jAnExgYkFl8zIlxPpsqqNCSdUpBSEeNRB4DUEAPN6oxdB0mUEyfFPJGscr5oKcPRWJTBBlI1o0zA2tdZiBqSHOpMzhmkCaXvVp9sOnICdt0wQvS/r9J9sLIZAdRkh3GekSZ0cZk0XjgsxUSzU7p0zrFHKZq3oSG2V9a1Jc7VeIrl3Gw/T3lXKbpwTYrd90nIsE8hKLy3nwA%2BSikeEBXB3yMtPUomK15LyyG%2B4F68siAuvnC/evQ/0gfPjMfFz8b5gZxbBx%2B0H54fPSu/F%2BpKXWDQpRmq4WqdVXD1eo1NDKdHBNJuTVl7LUGUE/jykANUOSJGSA1cVfUmOUkYVw11nBeHjVZcVQI2CWqUj6uVSQdUuCVTMJwjqiRMN/x4/wymn9rpcaw8NJTBVQ7xAyM4SQQA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_unequal_to/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_unequal_to.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_unequal_to.test.hpp)
