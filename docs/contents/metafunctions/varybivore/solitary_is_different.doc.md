<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsDifferent`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-4">To Index</a></p>

## Description

`Varybivore::SolitaryIsDifferent` accepts two variables.
It returns true if they are different and returns false otherwise.

<pre><code>Left, Right -> Left different from Right ? true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsDifferent :: auto... -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(SolitaryIsDifferent<1, 1.0>::value);
static_assert(!SolitaryIsDifferent<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQS0gAOqAqETgwe3r4BQSlpjgJhEdEscQlStpj2hQxCBEzEBFk%2BfoFVNRn1jQTFUbHxibYNTS057QojveH9ZYNSAJS2qF7EyOwcBJgsSQZbJgDMbkxeRKQA1CdEh9gmGgCCk8ReDudCnoSNAJ4AkgoAIngqFR4owCHd7iYAOwWc6TJiOZDnNAMSaYVRJYjnGKoTznABuYi8mHO0IsBGemGh/0OsOptIhEK2Oz2VKOV1Q5wAao08EwYvQbhCni8CG8PiNfgCgSDiGDDm4ecQ%2BQLMBclSrBQdbg8yXCGojkQI0RisTi8YTvCSyVQxEp6Qc6VCaY7GQ8APQAKm9Pt97ohXu9ABVsEIgz7/R7fdHPZHIQ94YiAPpMBRKJoQd60T7EKWA4GgwQKrgXLgAOg0NxAIEtxIWDITBrwyBTafiBAgYDAWZzeZlhfBRxL5y4VZrRMw9cdHCWtE4/l4fg4WlIqE4bms1jhKzW1rMBx4pAImhnSwA1gFJBXJFwoQcNIEzAA2J9mAAcb/0nEkvBYEg0QRLiua4cLwCggEEx7LjOpBwLAMCICAKwEEkpzkJQaA7HQ8SRKwGyqG%2BT4ALRPpI5zAMgSJSGWZi8Jg%2BBEMq6B6PwggiGI7CVKx8hKGoJ6kLoJYAO7EEwSScDws7zou/EgQA8qcqFiqgVDnARxGkeRlEjleZjnBAHhYfQWLmAeCy8FBWhLBASCYUk2FkBQEB2Q5IDAFIZh8HQWzEOBEAxPxMThN8Em8EFzC5nJMTaJgDihaQmFsIIckMLQXz8VgMReMAxy0LQ4HcLwWAsIYwDiNBpD4HKDh4PimAFSu6KxacGyHuEWxzhV2YxKJuYeFg/EUngf6FaQdXEDiSj/NspXZkYJ5LFQBjAAoXJ4JgQlyUkjDxdx7HiFxsiKCo6gVYJ%2BilSgm6WPoeAxOBkBLKgSS1AVRGTOghz/KYljWGYwHjUx9XwEsdixbULgMO4nitHooQzKU5R6Pk6QCGMfglijtR9Ij8wdODXRTOjehgzVAjdE0OMDBUww9MTJbwpTCPUxIoM7usrNfhwC6kEBvAgWphEkWRFFUbp%2Bm4IQJCkvuXDmUeC1LAgmBMFgCQQOeICSAcZYAJwHFCkgaJIZiSE%2BAH%2BE%2Butcz%2BpB/geZZPlwT5vrrb7O/4N7%2BPrT687JnBgRBCvQdZCE2UhiloU5LnGbhbCcI0LD4lCRFMMiBhGCOutluWjUMSQeDMSWe2iAd0jccdfFnSAnkiWJoVSdzMkVfJkfKapifJ6n6elVnOcVvphn2cZMsHGY8uWTB4cx/E6HOagRmDJ3KfIBn7m61wQQ0LQPl%2BQFFXhSFo2H5F0Xg/FiVgilaUZZgWU5WI%2BXxcVs0bCuVUE3VDV0aozVbPF7Vqj8W6r1L4/U34WWVCNQ841JqYGmiVIwc1QAhz4MtVa61NrbSXIeEuHEhgV14qdFcuhPJryur9G63UHoa1XC9DIb0PpfR%2BlYSw/1%2BaA0LsDR6%2BMyZ%2BAgK4emwQoZUzmDTLGGQhESKKMzMRJNqgE3JkTGGOQGYKL4RTaYJQWYM2UdkDGtMmbaLkXLZYqwOamM6jzPmq5OCXGIEnFOadV69y4NnXOEt84mVlhPRWpBlaq0GLQzqtt7bZ2NlCb2UI7wmzNjeP2LcA62CDpPUO8Bw7ISUnPGexA44bETppFgCh8RInxG4ssrJJh0S8YXFish9qcXLkdIh/FdAHFIHXcShVG7WP9hwBSKFTjnBUvYlghTimlPKZUsUBkF7D3iKPA4vjUHTzmQ5bJazjI1mQEkJISYym6yTNMlMDjSJeR3vEPegVgq5niifL4UUYpxVGpfZKqV0oVUytlXKT9RovyQRAyqeBqqOC/vxJqyAWoAMEEArqd1QHgMGlA%2BKsDUjwJmkg8IKCrJoKYCtNaG0to7VGngsuMhBCV2IToEA7TyEsOsLde6IM6GvU4O6D6FDWEWHYauThWAaGg3URDARUMhHw2MUjTGqRUaZBUQY6RDBRGSt4bUTRQjSaqqmEqvGjNmhypJlq2Rkq2bmM4j05uwE7EFLIkUkpBIpkInqjMyWjFR5ywsn4gJatKCN1CTXbOBwDj%2BECDeACgaoQuwSZa0CyTIJ%2BIvJIfwet/BvmfLrSQus7wGy4LSzgBwLX8ySakxutEo2FpjcWsalyMhayAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_different.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_different.test.hpp)
