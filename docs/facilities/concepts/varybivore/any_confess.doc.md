<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-confess">To Index</a></p>

## Description

`Varybivore::AnyConfess` accepts a callable predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred(Es::value))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0(***))` and `(...||Pred_0(***)) && (...||Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...||Pred_0(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||Pred_0(Args::value)) && (...||Pred_1(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOBGIXkwQKsyOBBPuD1JewOfzO5y41wOd0ez1e70%2BsNQVIutKBoPBkOhbIRcKRqPRmOxuPx/kJxKlpPJN0OADUmABPOn7BkPAiYFipAzaoFuNmHACSQOwpPGuIcStVctRpMOTsOs0cyEOTO1LK%2BP3ZADcxHiwaizUSSY8UTKrBHHhT9ocqF4sTdNdrdfrJW4CCrUoxWJhBQ9iMAFObSacAI5ePCnBSHCCClFuJsnakaCBFksgEAB7yYJZIxkCZkfQ4xVCeBNJiDCtGYDHELFUMRKElhmNanV6pgG/xZnN5tiF4ul/wWx6V6u1hsIpst/6XDsn7u9vEDsFmABs5k/9cbyObADW05J8ux7QN%2B0HJ5hy9Udx0nRMGBnFE5wXLEcTxNdiQ3OMjgAFUwcZ1VucltkObBiGIEhLWaN1ziYBQlFaagk0NZUVUNLgyzPGckSlDgVloTgkl4PwOC0UhUE4ZtLGsF01g2TAP38HhSAITQBJWABrEAkk/OEAA5PykJJkU/SQAE5/DMsx/H0ThJF4FgJA0IIxIkqSOF4BQQCCdTxIE0g4FgGBEBANYCFSH5yEoNBdToeJInzThVCMgBaczDmAZB3SkOEzF4M5CBIPB0D0fhBBEMR2CkGRBEUFR1AC0hdC4UgAHdiCYVJOB4QThNEjTJM4AB5H4ooIQ5UCoQ5Us/DLJCynLDjysx6w8eL6E%2BcwVKWXh/K0FYICQOLUgSsgKAgU7zpAYApDMPg6G1YgfIgGIhpicIWhVXreE%2B5hiBVEaYm0TAHF%2B0g4rYQQRoYWgfuarAYi8YAjVoWgfO4XgsBYQxgHERGazBxw/UIoa3jBn4tlU8JtSE5raDwGIusBjwsCGnE8GcrHSFJ4hxyUYEdTxxmjA0lYqAMEtFTwTB2pG3MxNUirhFEcRapVhq1CG1r9DxlBrGsfQmZ8yAVlQVIGkxtLxnQblTFkywzA8vniFKsmze6YnshcBh3E8Do9FCcIhkqEY2qKLIBCmPwI4yKOGHmYYEjauxvYEPpJgD/JU7qdPGgmAYQ4WcPbELmO9FmVok7DlOVgUBTNgkfqOBE0h3N4TzZvSzLstyyR8vrXBiu22yuD2tTxZWBBMCYLAEhnUgdMkfw4Ss5FJA0SQzEkT9XL0iz7I4RzSGc/wzDhfxP2RAz/AMpIki4ayLIM9uhs87zfMngKjtC47wvGtFS610tpJTYClHui1kAGCMCtCycIuBwgkkVIgbsyptRVlVdW0hNZKG1s1XQD1OrdV%2Bi3NuHdhocDGpFH4U0ZpzQWh6GBwA4EIKQetVAm14jKTMBPA6gV/4gPiDFK6nCzpbRQMwrgFkuBBBoLQZ6r13rNX%2Bt9CGqjAbA1BuDHmUNGAEFhvDIaSMUZowxhDHGIstgSXwKcBweBSaY2QaoSm2oIa0zqENRmzNvps2sftN23NVJ8wFpgIWuMjCi1AD/PgUsFAyzlgrRgENMFqxqjg2QWsmoSUIXrMWDsrCWGNjEU2i8LZW04DbAgdsQQFOsM7Turt3alPrnnexzgICuArm1YO5Rk56Ejg0bpaR44NBrosXOPQM7l2zrHL27SC5zGLv01OMy8hzKrkXPptdm6rHWE3ceR9yHv04N3eamVoF41YYgq4EBh6oOUuPfaU9SAzzniMReOlZFBHpifM%2BSQ4SWSSBZMwIKvwGSfuZN%2BzUP62C/vw3%2B8B/4RQmiIoRxAwFbBaCwTKLAFB%2BndH6aRcIMzjEKvgVBpVyqyCwekuq8g8HZJ0AEDqXUepYzIYNGFo1AGTWmrNXF%2BLCXEtJZNCAG1xHcJ2v4Ph4sgonTEedNFiqJEEtSKkc4RKLLnFFecVQUL5GKMoMoiSGiEaqTNVo4mEM9EwzhgjGxmBkaozEOYnmljIn%2BNILY72jjyYuOQFTdxghPEMyZizFUfiOaBIhiEjIYThaRPCNEw6sSmDS1lvLRWKSaVpIkBk%2BqjKdYsuYQbR2NhvEtMkpbbImNti2zLYUiwDTJJNKwFWtOCzfb%2B3WUHP24zS6DOyMModpRlk7MmfnTObRZmVzaQ0adA6U5l36MMzZS7dkN32TVTl0KPKnP1YtPFBLDhapJTuQiYr7kkEebKn%2B09Z7z0oC3P5AQL6QtsmYL9XADIaE/MCvdndOCfz8i85eq8n7323v4JIf7bJmSPv4Ll%2B6vLf0Oi3AqgHKHPPvbzeImRnCSCAA)

By turning `(...||Pred_0(***))` and `(...||Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AnyConfess = (...||Predicate(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3K4MLEeBhUTAKBR3aEAETuECJBJMAHY3CK3EiUXg0ZgICTwWSFCAQAA3MReTArFbQqzXEF/AHnfXHO4AFQ55K%2BRt%2BhpOQON90l6AA%2BhorYcgTTZphVCliHc4Qina7uf4%2BSZElZEjyIIHUILtcKLMiCJsGJjiBqdSKedm9TbHciXVx3ftPQJvb7/XHEUXnSXedzIxGY3GEyLk5hU8R0wRM5hs8Lc/5dcCC4c7gA1JhY0tAsEQj4DmE1h6UkGzTMOKczkEdkF3Q93WYfaV3L1gqsB%2BGoO5q7yYblJtdDvPA18jvfj/Z3KhedPfCCC4vEu0JuNiuLMGwgpXMQwAUv4VLXMiACOXh4MiXJMiyAjspyYHBkEjJwQogrrtcF4%2Bn6dwxKgni/v%2BECJp23bplQYhKIOub5qC4IgVCMIQXi0FErB8HkbBmBoRhHKMsyrJ4QhEp1kRYmkUSlLcmYABs5jaXJOFshySnBlwGJqWRiHUhWl7UbR9F/gwTEdimaYZlmn6vjxBpmhac4bk0jjIM6TCcvEBDUP%2BYHTliYFcOuiFMdqI4cGstCcIkvB%2BBwWikKgnBipY1jHhsWyPuY/g8KQBCaKlawANYgIk2kEgAHNpUiJMK2mSAAnP43VmP4%2BicJIvAsBIGhBNluX5RwvBKkENU5alpBwLAMCICAGwECk8LkJQaDPHQ8SRPinCqO1AC0PV3MAyDIHcUgEmYvBSkQxB4Ogej8IIIhiOwUgyIIigqOoK2kLoZkAO7EEwKScDwaUZVltV5ZwADy8J7QyqBUHcl3aTdkh3Q9T2SC9/IeMd9D%2BhVXArLwy1aGsEBIEdKQnWQFAQBzXMgMAUhmHwdBgsQSoQDEaMxOEzRYojvAy8wxBYhjMTaHUy1VUdbwEBjDC0PLENYDEXjALCtC0Eq3C8FgLCGMA4jGzJ9QqhyaM%2BnU8I7FV4RgulEO0HgMRwyrHhYGjfZ4BNNukG7xC0UoPLgg7QdGLVaxUAY8GTngmDQxjkEK8DwiiOIQO/fIShqGjUP6A7KDWNY%2BjB0qkBrKg9JZNbV2zOgvKmEVlhmLN8efVgbdMV0PRZC4DDuJ47R6KECzlJUeiFJkAhTH4Zmb70Qxr6MZm1PUAj9JMi95Cf3Saw0cyHyMCQn3MO96CeLSP0sz9rAopXbBIZGHBMqkBmrwOaBNrq3Xuo9Z6Zh%2BS4EICQLSlVGbVQzmsBAmAmBYASFPRqkh/AEn6sKSQGhJBmEkNpKazVeojQ4GNUgE1/BmAJP4bSwpWr%2BFaokRIXABq9VaqAtGc0FogCWhnNam02bbWxvtHmfNaZnTYBdKBJNkAGCME9XqBIuAElyu9EgX0fqyH%2BuXaQldQY1whroYWsN4YKyASAsB6MOBY12vCO4eNIFE1uhoh22jdH6KpqgGm8QUFmDQczVaMjFHxAOrzUJnNaYoE0YLXqXAgg0FoGLCWUsIZKzlsXQpKs1YawcMXHWZJ9aGzRibM2FsrbFztqnHYuV8DIldu7CGntkDe2Ln7boaMg4hzluHNpTNPoxyqvHROmBk72yMGnUAK1M7ZwULnfOhdGDF0rmYwGFjZBWPBrlWx9d06DysJYFuMRJ4dy7hWTgvcCD9zDJc6wI9wFjy%2Bu7du0877OAgK4N%2BZkV5lCfhvdIW9shX13qkKFB9V4QpvjPc%2Br9YXv1vmfPoD8kXf3fui3IcKP7zHBfihm6xNgAIpQHZxIjOA%2BOJueNJgS9FujlPgD6KCGZMwwaQLBODRj4MmkEAOjDmGJAJH1RIvUzCyp0q1fhPVhEQ1EbYcR6DVlSPgDInaOMElxOIMonYzQWC3RYAoFUj0VRcB0ZCC0b1OVGO%2BmZPZZcDkl2ObXAIpB7EIxtk41GqrMZyNxvjVQ5rLXWttQSe1swQlhLpkNfwUTJGxKSVzA1GaUlWpSCkZ0NrerOjjQQZ0EaLGi3iHk6WssVbFNrardWmtKmhN1jUo27TMCm3NmIJpscWlLImaQDpd83bWwMaoL2YIBmCCGYHYOoccIRwhlHaZvBZnpHmSnJZ4QVksz4OszZBci6xzdQDCQhyQbVxOToH1aTG5DxsCMu5eUHkMGtrsPuD6rkWE%2BXlb5E94C/yxb0OeC8iXL3nl/dee8EVZBBfCooWRoPH3%2Bdii%2BrQMUooBTigYKHn7jAGAhkl%2BHAGUrKmR2lQbZoMvLXcC1Vq7wxpLQgp1SbUG8tWZg7BuDKBAPFQEVhSqhpmFE1wVqGhtIypVTR%2Ba6qJFcdIAQoh/CeEUOqJJoa3V6H%2BGo%2BAzgnGWZANejJ/TcnolajjlW2ekggA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/any_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_confess.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/any_confess/implementation.hpp)
