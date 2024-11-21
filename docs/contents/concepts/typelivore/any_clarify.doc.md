<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AnyClarify`

## Description

`Typelivore::AnyClarify` accepts a callable type predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...||Predicate{}(Variables))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0{}(*))` and `(...||Pred_0{}(*)) && (...||Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto...Args>
requires (...||Pred_0{}(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0{}(Args)) && (...||Pred_1{}(Args))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHF4ZRgDUysSY6AD6GgcmiQAiB1jItAQAnimYECYBVgE3EExeRAAdMCViYAOwWE4ETYMA4EYheTDXKxgm6gxJWDQAQRM2L24WARxO5y4V1u9zqT1e70%2B31%2B/yBIPBkMw0OIsPhiOR4LR3OxuKxBEwLBSBiF1zcDNQwMBWOIwAU12wApOAEcvHgTgoDhAZeC3PrjqcLsyeRA5QqVqDsWgGLNMKoUsQDjFUJ4DlQvAwIKCIVCYR6xEpuaiBQKhSKxUjEpKAdLgRbFYlldi1RqtTq9WCDdmjecNKbUeb5QorVczAA2cwVzPA/WG4lnLiF36Jq0C232x3O13uz3e30stkchHRlE3MPY2ZMRzIM5MBRKFrUL0S5vJn3oiwcNa0TgBXh%2BDhaUioTgGyzWA4KDZbTDlxI8UgETQ7tYAaxAAQrgIAHBWpACMEK0kABORJgLMZI9w4SReBYCQNA0UgjxPM8OF4BQQGQl9jx3Ug4FgGBEBADYCBSAFyEoNARToeJIlYHZVH/ABaECDmAZBkAOKRATMXhTkIEg8HQPR%2BEEEQxHYKQZEERQVHUPDSF0LhSAAd2IJgUk4Hhd33Q9X1PTgAHkAQoggDlQKgDmYis2MkDiuJ4yQ%2BJ1DxaPoZ1zEfFZeFwrQ1ggJAaJSOiyAoCAQrCkBgCkMw%2BDoIViCwiAYkMmJwmaZ4dN4DLmGIZ5jJibQ6lwp8aLYQRjIYWhsqUrAYi8YBJVoWgsO4XgsBYQxgHEerNVKvAADdMHak8HTqAEdifcIhRgk9aDwGJNIKjwsEM%2BE8AQjrSBG4hXSUG5hR6xajFfNYqAMBUADU8EwNTjLeI8n3E4RRHEGTXvktRDJU/QepQaxrH0JasMgNZUBSXp2pY2Z0GuG5TEvSwzDQvbiBE0b4DWWp6mcCBXCmPxVNCBZykqPRCkyAQicp9JqYYIZyeWLoegaOZadU3Hen6FomZGKpxgGTmhb5smBYkHHb22SX9H0lDDPQmzWPYzjuN4swdVwISvKgrhfOfc61gQTAmCwBIfVIT9JESQFwLBSQNEkMxJArJDv1AuXYPgkBH0BACK1/UDfy4CsAkkLgAnAisFaU9DMOww28MC4igtIszKIiqLPIYthOGaFghrBFimAOR4ep40DAS4QFxvwIgMdE1TXskj7pC%2BpQfqU3R4o0rScr0jgD1jtCTIziyrIOAui5LsuDEOLgq5ry4IHc0LPIfMwDf8/C0%2Bz%2BIqMi1APNGafi/LoxF64ZCaCeeIUrSpS8qynLSGfgqipKhxX4qxgCGq2qhkGpNRam1V%2BXUTo7BPPgE49QRpjQEqoSaQpX6zW6IZRay0sprSgX5DG20nx7QOpgI63UjCnVAMnPgV0FC3Xuo9Rgr8W7vWku3WQ31FInh7v9M6SMrCWBBjEMGltIbQ04LDAg8Nbh8OsKjXgqB0aY2ETjbog18aE08O0PQpMygS1UlTXoIsDFZH5ksQW3N2bC00XkLmqi8Z9DmKYimXMObWOJqLeYuizGyxvJsGW%2BsvbD1QvIzgU9iCF2LqXC%2BhJF7V1rlreuJAHz6z8kbUgJszajEtjBOCpAEKJCrk7MEUcwRgkSM7V2EcR4hIwrYROO8U7wDTmRcyh997EFzjsAu7EWAKCGtxIasSoyzAEokxuYlZCt1YbJeQndOE6F9upTS2kOqDyCYrMe5EASWWst0hyvT%2BkHEGVXYZFlV7H3XvEB8iRt7nQIsFC5YU2mPM8iAfpKQUhnGOWcU585wkgQSnfZKlBH4nnfnVJ84LP6lR/sfSq/8ap1WgZgRqzUxBgJ2hA8huDSAwMGvAwyE1kBTVQYIdBSlMErWeDgja%2BDX5EPSCQ465CCR3MukwG6d0HpPSYZMlhEg2FyTmb9RZ89jBAwEZg5Rp4oZZHagAejhoDZGFg5GnkUVgaVFj1EMHcG47RuqnEs2MTTfV%2Bj6a9CNeYuxPNXG5HcdqhxAwrV6GnJMM1HiXUBN8XeWWMF1lx1CXsg4ByBlDJnKNM52sG7JNucnY2ptzaUEHrkhCZgq6JESAEAITtr4aEzcBX81SjK1KwjhNJ1tbbVF/OHKCOaKxQWAl7RIBlA21IaYPfixb45JwCmsPaGRnCSCAA%3D%3D)

By turning `(...||Pred_0{}(*))` and `(...||Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AnyClarify = (...||Predicate{}(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgQQAOqAqETgwe3r4ByanpAmER0SxxCUF2mA4ZQgRMxARZPn6Btpj2jgK19QRFUbHxibZ1DU05rQojveH9pYNmAJS2qF7EyOwcBJgsSQZbJgDMbgQAnkmMrJgA1MrEmPiiW6RXTF5EAHSfAGr1eEwx9AUh2wJg0AEE0Ax1kkCFcwQwTm4DMQ8FQTldDgARK4QT7vEwAdjchLct3ueEemEJVgJmIgPxR/0BCwWhys4NBYIA9AAqPn8gWCrmc3n8q4AFUwkwUVwFwvBosFSr58rBnK8aSMNzu6AA%2BhoMQdsVhkLRTucICZ/FZ/HTXh9PqyCRY7gRVgwrgRiF4qQcaZjWX7OerNcBtfddVxDcaqmazphLdarXa3qg8U6XZg3cQPV6fWzCQGCxzwVsdntfW57WnPmDiMAgQcQeC7gBHLx4O4y%2BGI5Gok6HUk6/XPOsNvHAzmQyaYVRJYhXGKoTxXKheBgQDOu92rsRKAu04Ol7a7Jj7I7VvFjxvNuuYdudqVwhFI35owdkvUaUf1hQTpsYmYABs5hAc%2BvZvgORyfpGP7jp8k7gtOWxzguS4rmuG5blmO55r6/pHmCkxnhSupMAoSgNNQ66DlwwKboGFgcEstCcP4vB%2BBwWikKgnDEpY1hXAoKxrNc5gHDwpAEJozFLAA1gEkjvBokhcASBwaP4GjAUBZgABx6fonCSLwLASBo36cdxvEcLwCggN%2B0lccxpBwLAMCICAKwEEkbzkJQaA7HQ8SRJcnCqHpQEALRAZIVzAMgyBXFI7xmLw5JECi6B6PwggiGI7BSDIgiKCo6jOaQuhcKQADuxBMEknA8CxbEcTJPGcAA8m8vmwqgVBXBF0WxfFiXJUpZg4h4QX0Au4lcAsvBOVoSwQEggVJMFZAUBAG1bSAwBSEENBmvE9kQDE7UxOE9QnE1vDXcwxAnJ1MTaFUTmSYFbCCJ1DC0HdFVYDEXjAFWtC0PZ3C8FgLCGMA4hA4%2B1QAG5Su1s5VG8GySeEWysRVtB4DE9XPR4WDtV6eBmdDpBo8QS5KJi2zw0TRgyUsVAGA2Xx4JgNWdecnGSblwiiOIRWi6VajtVV%2Bjwyg1jWPoxP2ZASyoDCGRQ1FkzoFipgCZYZjWfTWXo%2BrbQdBkLgMO4njNHooQzCUZR6CkaSdJkDs5NVHsFAwfSu4M1WVNUXRTGMfih%2B0H01FMQcDAkoeRz70fDD0idzMnSzCas6wSC1HDsaQVm8DZg2RTFcUJUlKWTRAuCECQgESYtUkc0sCCYEwWAJJupAKZIBzvAAnAcBKSCpZiSEBFn%2BEBo9GRwJmkGZEnvEBXBAXpo96dv/iqf449AaX7U2XZDkd85q0eWtXk9X5O17bNoVsJw9QsCjBJRUwVymvDZKo93hcGUulfAmU8DZWqqLfKEtpBSyUDLCquggh1QavdIuJcy4dQ4N1Hybwrj9ReMQL%2BP8/4AK1FwYBoCDQQGmptWardFhLQ5q5daqAZrxH8rtThjDBif2/lFShh1R5cG/CdLYxBzqXQqo9W691SDyOeq9d6DhFHfUYAQP6AN2rA1BuDSGijYasw2NxfAdxUbowqpjZA2NFF43aO1ImJNbrkzMUtFENNJL00ZpgZmcMjBs1ADfPg3MFC835oLRgijYHi0Kgg2Q0tyrcVQfLdmhsrCWBVjENWA9NZex1nrA2Stjam3iObPJudY7hz8BAVwUcnZ2yzm7P2%2BQvaNLaZ7DILSQ5WzjhHHonT%2Bm1O6A0XpycM6jDTnoYi4yXZJ0LssfOhUsFtQqhXQR5D/4GCoTQ5SOIm6ZVbgtVhN8u49z7pQIuq917AJUgSY%2BBJ1KSBnrFaqOCL62CvstFyblPLeV6jwl%2BIUwocE/iNFgCgUZJRRtQ94FZJjgObllHKsg4EJOKvIJBKSdAgAOLVeqjVoZrLPhsrqj8%2BoDQhXFKFMKrhwuAYi2E9C%2BFbVbgcduvzVocK4dtAKbLZogBhUkJIupGW6mZWRUhsU%2BB0CkTIq6N1nqKOUS9N6H0NGcJ%2Bto/6gNzGYBBmDMQRjaYmKCR40gFi45oyhtxWx9jaaOIJtxFxpNEQYEtVTbxvBfGpH8SzIJ4QQkrTCUwHmfMBZC1iei%2BJEhEklRxbLfF6TjClJsC4qpPEtYCChlyPWisjYWBNuXM2UCLYDzDl7W29tsjp2dsURZXSA7DP9l7CZsyalezGY0GZMdraDPmY27OszU51tHZnBZI6FrLNEksgm2Dz6cBISwSF0LYXwuZYciBLd5pcs7qQbuvdBgDwJrcxIwCDgHH8FpVSFkr0Eh3mS6ynBL6OQPUPfwY9/B6WAqPSQo91ITy4ASgmBx1kvtstfFaRc0rPvLq%2B6Dsk6ZnRtpIIAA)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/any_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/any_clarify.test.hpp)
