<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SetContains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-set-contains">To Index</a></p>

## Description

`Typelivore::SetContains` accepts a set of nonrepetitive elements and returns a predicate.
When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Es...
-> Arg
-> Arg &in; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct SetContains
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**`.

```C++
/**** Metafuntion ****/
template<typename...Args>
using Metafunction = SetContains<int, int*, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every element we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

Since fundamental types are not inheritable, we pack every argument into a wrapper--in this case, `std::type_identity`--before the inheritance.

```C++
template<typename...Elements>
struct SetContains
: public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                std::type_identity<Inspecting>,
                SetContains
            >::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjE/gDMpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXGSiXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMUR0bEJtg1NLTntCmP9oYNlw5UAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYSa6MyHiYCjeHZ5fXJ39H3wu5yBZnioWQ3iwNxM8TcBAAnk8APoEYhMQgKGHYYHA37/fH7QF4m4ASRYSXobEETG6nwORIJjNOOMuBEw5IMbJhcMRjFYmAAdELsJTGARMfFsZdpsQvA4bkJMM1ZOiGJjLiAbkkvFFaHhkDdpugQCAEci8FhBIR4dyReyxRLsEKBTiAOxWS43L03NkcmmYblmvlsUlqp61IxY4Hew2ouUEG7KYioIgAWU86Gj3pM7uznpj3umNP1NzQarZqiSxBuUVQnhuADcxF5MND8wXoe6sx2Y0aTXgFEiokwlEjUFRuz2vdzJ1PewRjabeUiLWLrdySWGao5I5LSLO517FcrqaF1RdD9PJSam94A%2B2Czm7jCPRfs67n/FX5PfRT/YHeWYNhnQuYBiEwe1BEdScvDSIwbnTWh0GheI7kTZM0wzblQPAyDxWdKMvzdT9vx%2BJkvlxQ4bmwVRWApVsKLI8jCRZK4qNTJUmCoLwrQEOkWNZdk/y5WEgyAwUhQuYhgGgy5YNCYAEM47iGFqPiYTQ48PFPNVuVCAhSBufTdkM4zdijDUQEQzNYSkmSCMlF9WOJAAVd5xX45lpQaRxkCREclCaCAOIaFS1IYPTBHM68QFvFslic7ziz8gLYgICAwDAJTQp48LuQbVALSxG9m0wBKvw4FZaE4ABWXg/A4LRSFQTg3GsaxDTWDZW3MeIeFIAhNEqlYAGsQBqyQBQ0AAOMwzAATnmrgapm6auFdV1pGqjhJF4FgJA0DRSAapqWo4XgFBAI7BsayrSDgWAYEQEA1gIbUDIoCA0HJOhYnCflOFUaaADYAFpgckG5gGQA0pAFMxeEwfAiGIC09H4QQRDEdgpBkQRFBUdRbtIXQuFIAB3NEkk4Hgqtq%2BqhuazgAHkvDetmbnHG4gbBiGoZhm44bMG4IA8H76GrXquCWXgbq0FYICQb6kl%2BshPuV1WQGAKQzD4Og2WIS6ICiRmolCRp4Rp3gzeYYh4WZqJtG3K3SG%2BqkCGZhhaEt4msCiLxgDcMRaEu7heCwFhDGAcRfbwcDagbd5GcwVQajZrZ%2Bv0zpGb1KI0TtjwsEZ1E8H2sPSET4hayUB5I6MPUjCGlYqAMGSADU3nJ5mnga/qMeEURxFx/uCbURnSf0KOUHayx9DwKJLsgFZUCSbpQ9Bo0NNMSxrDMU7K9RrBF4gFZqnClwGHcTxWj0YI5lKco9HydIBAmPwyef7oBgf4YybP7pejjGvjkP%2BnRtx1BmN/IYcQ/4zDfnoIsTQoELBgafLqmwJB0w4HVY6jMzrcxBuDSG0NYaTWFhAXAhASDQlBNLWWTcVgIEwEwLAcQT6kDGpUAU814ibQ0JIMwkhgaHRqsDea%2BhOC7VIPtPqApgZcGBtNeaa1gYTWWjw4GuDiZnQuldAaTd7pPUVi9Nm71yCUA1hLf6bBOCNBYA2V0oMmClgMPBLg80BRcCmojZGJA0Zk37ljIe0gR5KDHsTXQutKZMGpmHLBOCTq8DOqzdmCYuY8yIS4qOgsPFeI0CLMWKsJY0PiGYGW%2BjboKyVqgcWsRzFfRqUU4YEIo7uK4EdGgtADZGxNsTG2FsXb9Ltg7J2DgXZuzFJ7b2jM/YByDrQEOLsI5Rxjk1fA8dHCJ1Dk1FOac2QuyzttJqud87wkLlsJqJcy79UrtXTAtcVkKQMS3Jg7dO7d0YC7QJg8cYhNkKPImTVImT0btvKws9c7H2XqvDI69N6oTBbvfesRD5JyXh0LoGQL5X2yO/Ugd8SjQKfqkF%2BmRgF4s/hkZBj9QGYoEIA5UuKEFgPCgy6lv9Rh9HgbAvo7LUGrHWBg6WEjsEM20ZwAhvNIYtLcbkqaItKEoxKXQip8tGHMNYZQLBUiZEeP4a6Gq80NrxAEUIyQZNElM3OrYPRcs7oPWeq9Mx6tGmq2sVsOxfMWAKAbAaBs7iBScncj4qhh90ayCCb8vG8gwmAp0CARI0TYm0xFQkvBLNTEc3SV6n1fqA1BumAU11xTerxHKXaqpKBi11JdbUuIvqkhJCRP6%2BaSIC0ECRKoCGesumxB6abc2dtBmDvto7Z25cJmCCmT7NZmB/aB2DqHfqyz64XPDnHcBWzk6p2QOnA5ghs7ExORbc5xdUbXN4Lc1I9z2SPMbpUvgrcFAd0wF3HuXyI0/IkH8/Gsbx4JpBcYGeNhIXwGhWvTg2w%2ByIssHvJJB9VxQoxeA5wEBXDcvxZfPlxKCgZAw5Soo98iW0pQz0OB5LmV0rI7yojKCEHkaZTypBtGaVoMFTjeJYrToSq7ZDb1vrGz5v9IWihvjJa0PLQw0gTCWHDHYdtHVIAFoCniPEGqK1zWHVU66RRWjuPWsutdKTnCarcPWq6Q601JBLS4LNMwmjtrxC40kzg9DKlYIRnplz1qK0rErmkZwkggA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/set_contains/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/set_contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/set_contains.test.hpp)
