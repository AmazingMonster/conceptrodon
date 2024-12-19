<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Subtract`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-modifications">To Index</a></p>

## Description

`Varybivore::Subtract` accepts a target and a list of variables.
It subtracts all the variables from the target.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Subtract :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Subtract
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Subtract_v
{RESULT};
```

## Examples

We will subtract `1, 2, -2, 2` from `3`.

```C++
static_assert(Subtract<3, 1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `Subtract` using a fold expression.

Note that the initiator is on the left side of the expression. This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub>
</code></pre>-

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct Subtract
{ 
    static constexpr auto value 
    {(Target -...- Variables)}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmakAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHASYLCkGeyaBbkxeRADUACrNwJgEpJfnRAB07wBqzXhMsfQKJ2wJg0AEFZsQvA5LkIvLECMQmA5gSCTAB2CyXZGXbGXWZMRzIS5oBizTCqFLEZ4XVCXABuYi8mExoJxmPREFuxHuBEuAFp3q9eZcvsQfn9MAoVmiACInDHImVyhWggD0ACoNZqtSrkeqNddsEJrpqdaqtea1aaUaC8QSAPpMBRKFoQGFwhFI07BS5cJ7JPn%2BsyAkAgeneJknWWBaWXDRSwIWDhrWicfy8PwcLSkVCcNzWay4jZbCNmQI8UgETRJtYAawCZleqLMkgAHC3/BoAJz%2BMwaABsLeCKY4kl4LAkGg0pAzWZzHF4ChAU8rmaTpDgsBgiBAGwIKQu5EoaAOdASUVYO1ULb7vL7kkuwGQhKkrzMvEw%2BCIovQen4ghEYjsFIMiCIoKjqKupC6L6ADuCIpJwPDJqm6ZVtmnAAPIXPuPKoFQlxXjed4Pk%2BPqSK%2BlwQB4J70JS5hlisvArloawQEgx4pKeZAUBAHFcSAwBSMkNC0HsxCLhAsRobEETNAAnohvAycwxByRhsTaHUK7lsebCCBhDC0ApkFYLEXjAGctC0Iu3C8FgLCGMA4gmXgxBaXgtISmhZJ1BcOzlhEezDlmtB4LECKqR4WBofCeDjrZpCecQsTpJg0r7I5oVGFWaxUAYwAKB8eCYDBGEpIwikgcIojiMBf7yEoahodB%2BiOSg%2BaWPoYWLpAayoCkvQ2byszoJGpiWNYva8KgSXfl5vVdD0WQuAw7ieO0ehhAs5SVHohSZAIUx%2BL6%2B29EMO3LIt7kCP0kzrXkvq1PUN1zOdIxVOMAxHXoeItG9SxVGsChFtsEjIRwabTmhc4Edet73o%2Bz7kWYlG4IQJCYqWXCMRWOVrAgmBMFgiQQLWICSIErydoEqKSBokjNn2k7%2BH2nb6Jwo6kOOZavH2XADp2Lb8/4khcP41N9lDkFzguS646urFbmxO7YQePF8bR55sJwzQsLSqK8kwRIGEYPqdq8XCvFmH7o9%2Bv6yABtXSPVYFNZBujJHBTAIbZ4OQzO02YaruH4br%2BuG8bjlmxbVuUdRnG0ZjgRmDjzFrsrGsJIevGoDRoxhwbyAm4JnZcFOIliRJUmQcp8mVbXqnqZpDiVbpjAEAZRloaZ5mWdZlX2ZlOxZvgbn1J5NnW6ovl7JVgXdGhoXhfJUXD0xorxeWSUpUo6UOUYWWgArfD5YVxWleVGblvVjtAc7siuxBWYe612XjVYnVLz1pPZgNWRDSNMaHULBTWzLNPAWBv5A26NdPwEBXDfV9FtMo709rpAOtke6x1UjoLOttVBj0YHPT6HMRBV1iG3XmCggGP1SFYNoQMf6u1sbrE2KDFhw5/bQ04M8YgesDZGyLlHLg5tLYaFRp%2BDG9FsZMTxqQAmRNRg/2HJzbm5t6aonFqiVEgQGaSDvL6AO6F5y2DlmnRW8Bla7hwtnTOxAtY7F1sRFgChaSElpCI14RwJQEHfJIu2vob41TvlVR%2BzUQDBC9j7JC7MIaoWlkHPcFxLh4V4SwZxrj3GeO8bMOOucE4JCToEVOOV1zsXyVxWxFTaKhmQCkFIdoPGdjtDkggDo%2BF3j4HQSulBq5ZgbsZcsAym5aVbrnPSHdDLGRHpgMyFkxD9wSoPA%2Ba9SCj3chPby09kB%2BTnoIBekEl4RTkqvGKG9Krb1SnvTKEQj4sRPkwAqRUSplQqglIJgEJD31Ao1J%2BOgImv2MMArqsQoG/0GpwFUI12oTUsKAmaCQ5pgqer0Faa1cjYOQYsZhOCihZDIadLITDLoooaHQjFP0iG9EocSj6v1Wj0Meq9fBNCWHAzYUBP28TZw8KcfeFxbi6TZPxD4iRtsk4yPlixfGhNiaUHBqokAZhzaBECP4DsotJyqtRAOKWPKTGLmXHIuskhUSvk0VwKQnYNHUy4KiWJgRuWBxMeY8Gb49XOtkQrNYSUMjOEkEAA)

## Links

- [source code](../../../../conceptrodon/varybivore/subtract.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/subtract.test.hpp)
