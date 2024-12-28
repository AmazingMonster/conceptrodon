<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different">To Index</a></p>

## Description

`Varybivore::IsDifferent` accepts a target and a list of variables.
It returns true if the target is different from every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target `different from` V<sub>0</sub>) && (Target `different from` V<sub>1</sub>) && ... && (Target `different from` V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<1, 2, 3, 4>::value);
static_assert(! IsDifferent<1, 1.0, 1>::value);
static_assert(IsDifferent<1, 1.0>::value);
```

## Implementation

We will implement `IsDifferent` using `Varybivore::SolitaryIsDifferent`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAdIADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJSbaY9kUMQgRMxATZPn6B1bWZDU0EJVGx8YnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimMmujMh4mApX%2Byfnl0c/B59npzOBEwLGSBmBJgCbiYXiIpCuMKIkOwgNGxC8DiuQk8hCaAE8AJIKG54KhUeKMAiAkwAdgsV2mjmQVzQDFGmFUyWIVxiqE8VwAbmIvJgrrSLAR0ZhaTdIfSZXLqedgaDwdKoYjUFcAGpNPBMGL0ZGoyUYghYnFjQnE0nk4iUyFuXXEfWGzDw52uo0BFHncUMxpMlkCdmc7m8/lC7yi8VUMRKBUBeU02VJpUXX6Zv6A77bK4E1UgylMOrvPb/XNZ37/QEqsEl9XQ2FagAqTWAmAI8M1ADo%2B56DfQFMbzmizfmbWSKYJqXTAVcFwGS3hmazQ1yeXzaILhdLzouxXSIH2e%2BYAGzn7G0XHEa0kqf2mdQgduhTwtvEDtUn0gEBRkULImVh%2Bimip%2BsqIL1hCGrNlcH5ft2zYni%2BQ4jmca7AmGm78kS952pSAD6AqzhYx59uel6WviuG2tO35Onqg6vO%2B7adsiv7/pggGgWm4EZlWHw5vsVzYKorBgqKglfAJUkAqOgYrgRTAKEozQQDRD4OlCXDwmY8JBFckjsX%2Bu6AbxZyMopymqQQEBgGAE54XRjo6VcXA9ho8JcMZnFmcBFkKcgSkqfEtkafhT5uK57kaD5plyhwSy0JwACsvB%2BBwWikKgnBuNY1gMisawxmYAQ8KQBCaIlSwANYgClkgeQAHGYZgAJxtVwKUaE1TVcDSNLSMlHCSLwLASBonkZVlOUcLwCggJ5lWZYlpBwLAMCICAKwEMksLkJQaCgnQ8SRKwGyqE1Z4ALRnpIVzAMgzJSD2Zi8Jg%2BBEC66B6PwggiGI7BSDIgiKCo6graQug6QA7sQTDJJwPBJal6VVdlnAAPKwnt5qoFQVyXTdd0PU9bmNWYVwQB4x30Ny5hlQsvDLVoSwQEgR3JCdZAUBAnPcyAwBSHpNC0MCxALRAMTozE4T4kjvCy8wt6YzE2iYA4CukEdbCCJjDC0Hi6NYDEXjANCtC0At3C8FgLCGMA4iQ/g9oOHgAqvOjHIa7CGzleEwLDVl14xPDt4eFg6OSng4026QHvELySh3PbRjXkYVVLFQBjAAo2ovDDmMPBl5V/cIojiMDZdg2o6PQ/oDsoPllj6HgMQLZASyoMkdTW9dozoJCNymJY1hmDNCffZ7nedBrdQuAw7ieG0eihOEAzlEMOkFBkAgTH429pLvDCzIMCQ6XYc/dGMLTL7kF81FfAg9M0p%2Bb%2Bftg3/vejTK/69zFvJYCgirrAkCjDgaVSDTV4LNQmV1br3Ues9CmVNcCEBIGKUqXAmYVUzksBAmAmBYASBAWqeQextQCINDQkgzCSDPJNFKZ42r6E4KNUg40yo9jPFwM8TU2p9TPA1LqlCzxQPRrNeai1cErTZptdm20cb7V5vzOmZ02CcCaCwAUNJrpMBZAYIwbk2o9hiu9T6JA8A/R0mXAGldpDVyULXSGug9JwwRgrcBkDoEYw4NjXasIrj4zgcTe6yBDHAGMaYjyVMaZczppggIZgcEs1Wgo1R8QDp81QLTIY4SHZcE6p5UW4tJbS0hkreWcdKkqzVnPLWOtKT60NsbTAptzZiCtlrO2DsnZZRdlfD21ssre2QL7LWAcajoxDmHPEEcNhZWjrHcqCck6YBTr08IoBZF8BznnAuRdGBa1sRXIGDjZA1whllVxDcM4jysC3EOHdSHZR7pkPuA8h73LHhPeIU9nlAMfm7ZwEBXDfx0mvUoZ89A7zqOC0gsLMhv3mA/Loz8v53wPrPYF9Qb7Iq3p/Xo8Lf59H/tC7ByxVigIpcNbxEjOAhIQQYh2USYqoIsfTLBKS8GkAIUQoYLzhrsM4SYmhNIUptQGkkOhd0dI%2BMkbYaRqS5HwAUTtXGWSMnEHURsLRJMWAKAFMyAUhSexqlGOY9B31fqyDsWckG8gnFXJ0IkUg7jEY2y8WjSGs1/G4yCQTVQ%2BrDXGtNea801McnxPiIkgI3KdnpKjdzTVSa6Z/mQMkZIRFCkEXDQRINDi6ClMoOUrKNSjbVLlrU9Wms46NL1gbCt/S2lmwtl0uOPS04LNtngV2jghle1UD7YEEzBBTMhjM/E8yo4umWbwVZaR1kgk2RnHZ2cmC53zpgQuxdjm2tORIc5oMnV11dREpuo9HltwBa83unBNgDwvQ8iw48YGTysdPF5l8cULyXjkLFkKN4ooRUfOFmKYWgaRWS9%2BP8gV1Bfrff9sG0W4pmNB4DJLiV4vQ4AylxUwGsIgd6maDKC1XANUawUYaGyjHZVaxJ2DmY8r5cQyg4DhUgHaj2AIAQUrdUkFwSaPGaR8PET6zgUilo8rqpIFKFD%2Bo0kmk1SQnUuAtTMGI4aARiMwIkzI1m4C3piZI3NfT1V47xHSM4SQQA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_different/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_different.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_different.test.hpp)
