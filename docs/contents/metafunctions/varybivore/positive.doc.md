<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Positive`

## Description

`Varybivore::Positive` accepts a variable and applies unary `+` to it.

<pre><code>V -> +V</code></pre>

## Type Signature

```Haskell
Positive :: auto... -> auto
```

## Structure

```C++
template<auto>
struct Positive
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Positive_v
{RESULT};
```

## Examples

```C++
static_assert(Positive<1>::value == 1);
static_assert(Positive<-1.0>::value == -1.0);
```

## Implementation

```C++
template<auto I>
struct Positive
{ 
    static constexpr auto value 
    {+I}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOykrgAyeAyYAHI%2BAEaYxCAArKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJtvWNzbltwz1hfWUDCQCUtqhexMjsHASYLMkGGyYAzG5MXkQA1ACS%2B9gmGgCCCgTEXg4nygWOAG6Y1zcm/hYn3xOQJO9yYjmQJzQDHumFUyWIJyOp3eYi8mABt2BAL%2B1gu/gAIvt/t9foS9lZbt8APQAKjp9IZVOp9IAKtghCz6UzbrSGXzuT9bqDwQB9JgKJSNCCvdIfL4HLiXEAgFHedH7Mn4k5cOZE77CvDIMUSuIEaVvPCffZuAC0XAAdBolSrUeq9pqTnbHbryRwFrROAleH4OFpSKhOG5rNYQUsVuqzHseKQCJo/QsANaJMz2/xmSQADgLCQ0AE4EmYNAA2At7fScSS8FgSDQaUghsMRji8BQgNup0N%2B0hwWAwRAgJYEZLHciUNBbOhxCKsNaqAtVm1VyQnYDICFSe1mXiYfBEYh4dB6fiCERidhSGSCRQqdSD0i6LikADuxCYyU4PD%2BoGwZpuGnAAPLHNOBAnKgVAnGuG5bjue7apIh4nBAHgLvQCLmEmcy8AOWgLBASDzski5kBQEAUVRIDAFIZh8HQGzEL2EDRKB0RhA0ACeAG8DxzDEHx4HRNo1QDsm85sII4EMLQAlvlg0ReMAhy0LQvbcLwWAsIYwDiCpeDEFJlqYDpYawtUxxrMmYQbAGb60Hg0S/qJHhYKBDx4M2umkJ8xDRGkmD4pshmuUYaYLFQBjAAoABqeCYF%2B4HJIwgmPsIojiA%2B17yEoaigR%2B%2BiGSg0aWPobm9pACyoMkjgCDpNr3OgGqmJY1iVrwqBBeeWC1RACztE1fgQK4ox%2BJ%2BIRTKU5R6KksqZFNi0WkUc39PEn6jbUEyrTtmD2GNXSNL080DDt%2B2eC0eigmdm0zNtI1xqsEhARwQbtqBXYIeum7bru%2B7oWYmG4IQJAAomOpETFCwIJgTBYPEw2kFmkh7PapZ7P4kgaJI%2BZVq2CRVqW9YcI2pDNkm9pVlwNalgW9MJJIXAJNjVbfW%2BXY9n2KYxcOY5kROUEzjRdG4cubCcA0LDvP4NpMJCBhGNqpb2g61mniQF5XrIt55dIBXPsVb66MxP5/oJH1fR2vUQaLMFwYixBywrSvICrwBqxrjqYdhlG4VDexmIR/ODqR5GoDhcSzrR0eBwMsvyzanuGVwpZcG2NC0GxHFcW%2Bwn8VlReieJkkOFlsmMAQClKaBqnqZp2lZfpkVrGG%2BBmTUnxWceqi2RsWWOUdoGue5/FeR3RHnv5yZBSFSjhQZRhRaAEd8PFSUpWlGUhsmBUG/eRuyCbr5hubZXRZ1VhVePQ31Y1mQtW1HWVRYPXhv1F6WfAI1HeZZwE0GDuBurkGaIDzpbTWstAQB18iwIYFAp6d0AEdAYKdJoYDpq2DQSdCYyCFpXW6PA%2B6kwSjQJ1IsZYb0qHOVtj9TgLs3aK2VoZH2mswbazwtDMOxF0ykARkjAYqNnKU2purfG/h2b%2BH8HsAmkgtyfjtmBbstg%2Bb8NIkLJAk5oJxwlkuFcMtXbIRYAod4EJ3gZ3tDsSyBBjzcN1p%2BQ%2BuVj7ZTPiVEAdZLb/l0jbEC3MHZTmOLBeCstTHmMsdY2x9x/YJyosHPYfCBbCwMdROc8TcIqmQMkZIIorGlhFDEggYoTFG1YnEfO3FeKiRLjUsSEkpJV2jnJWuillKd0wGpDSYgW4BTbqvaepAu7mV7qBGyyA7LD0EKPFybkPJ8Snj5WeWUF6hWXpFMI68SKbyYAlZKqV0qZQCi4u8EgT5PiKufHQXir7GHftVaID9wxP2apwKkbUKpdUsJ/PqcQBq/zqrg46mQXAgPgbNChKDPxLUKFkbBMC4WEMusCwBGDro5BwbtToBDHpEKGCQhFxCHpQqIS9Gh95/Fc07Ew8J24zEWJOAUmxYI7FcIhjwgisMI7w0RsjSgH1xEgDMOrPYewEgllZq2MV/gazUvtmo3s/Y4ZoxAJIfwh5pFcCkKWKR2MuCBGcnsAJNK1GaI%2BkeeVqjuUkQWEFdIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/positive.hpp)
- [unit test](../../../../tests/unit/varybivore/positive.test.hpp)
