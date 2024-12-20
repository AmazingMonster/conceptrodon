<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Clarify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-clarify">To Index</a></p>

## Description

`Varybivore::Clarify` accepts a callable predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Pred, Vs...
-> Pred(Vs...)</code></pre>

## Structure

```C++
template<auto, auto...>
concept Clarify = REQUIREMENT;
```

## Examples

`Clarify` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(Pred_0(***))` and `(Pred_0(***)) && (Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (Pred_0(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (Pred_0(Args...)) && (Pred_1(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjgRiF5MKCrGiwcTHk8KQcjgCLpcuLcjg9nq93p9vgjULSrgzQRCoTC4ZzkYjURisTi8QSiSCSWTZRSqXdjlQvLi7syngRMCwUgZtaC3MLkU9iMAFKDsBTzgBHLx4c4KY4QM50jQQU3mkUrVEsgRsr7HGKoTwqtUQMWYzDY4i4qhiJTk0mK57a3X6mVGv6oEWei0gq3PW32x3O11Aj1mhTelaQswANnM9bLgPpla9KN9L392vZQZDtDDDAj6KjMdx%2BMJSbJzyVNIAKphZozDprdrtjthiMQSBTZkxHMhLkwFEoWtQ1YauJaI6jZRw1rROAFeH4OFpSKhOG5rNZjgoNi2TA6xBHhSAITQHzWABrEAAnrRFEnrKQAjRetJAAThBNCzBBfROEkXgWAkDQNFIN8Py/DheAUEAyIg98H1IOBYBgRAQA2AgUj%2BchKDQXU6HiSJWB2VQkIAWnQ45gGQZBjikREzF4C5CBIPB0D0fhBBEMR2CkGRBEUFR1EY0hdC4UgAHdiCYFJOB4R9n1fSDP04AB5P5uIIY5UCoY4xPrSTJGk2T5MkRTnQ8AT6G%2BcxQJWXgGK0NYICQfiUkEsgKAgdLMpAYApDMPg6G1YhaIgGIXJicJmgAT3s3hquYYharcmJtDqBiwP4thBDchhaHq0ysBiLxgCNWhaFo7heCwFhDGAcRhodTq8AANyXFyPjqP4djA8JtSfUzaDwGIbJajwsBc/E8GImbSA24hgyUMEdQWk6jEgtYqAMc0ADU8EwSy3JSRgGoM4RRHEfStPkJQ1Bc8z9AWlBf0sfRTtoyA1lQFJemm8TZnQPlTEsawzEox7iHUzbsa6HoshcBh3E8do9FCBZykqPRCkyAQpj8Czed6IYueWenVoEfpJlZvILNqeopbmUWRiqcYBgFvR9xaFWliqNYAM2bYJEcjgX3IlyqP8iSpJkuSFLMZ1cFU2LcK4BLwK%2BtYEEwJgsASCNSFgyQQURLC0UkDRJDMSR61I%2BCMPwjhCNIYiQTMREQXrNFEhBRIAgCLhsIw5IKN4KiaLoz3GJStjUo4zyeOy3KYuEthOACoLjmQAwjHkjDES4REPxUohqY0izYZ06HpFhoyEdM3Qius2yGtN82y9cjgPK4v4fL8zupJ7hb%2B8H4fItQaL4hAswPaSpj65b%2BJeJyy%2BMpilBe4KjCuDImhaFKuVSqpkmp1XBqAlqbUOoOHBj1RgBB%2BqDRciNMaE0prgzmu9HYH58DnHqBtaaI9VA7W1ODA63QXInTOnVS62DErUzumBR6z1MCvXmkYD6oAa58F%2BgoAGQMQZg3ulPKGelZ6yHniZD8S9kafVJlYdGVCsaB1xvjTghMCDE3BPI8mlN4jj1poHBWvQmYs1yILYIzNdbcyFukPm2RZYWOFlkax4tjENDmJreW3RJZ9GVpzVWWtPGOKCQMVx%2Bt1hGz0uvZypkraH2CsfPuXAB5DxuBAZ2Y8QLu0Sl7UgPs/ajEDrBX%2BZEjopzTgEREmEAgYTMHUhsiQi7oQtnEzgld6JfWYnXJAnEvIvyfsQNuOxmgsCkiwBQa05JrRSYiDMsxlL4DHupTSshp5iIhpIxGIA8IrzsjNGJrTKLuUbt5Xy/lxmTOmbM%2BZ3kIBRXftfOKII75dMfm/TKAyPkfymSkFIlwZkYUuLcy4qgWn/0AZQYBH4IFDTArCqBnVYGX16gggaQ0cGYFGuNMQ6D7qYI4XQ0guDVoEK2sQ5Au0yGCAocdU651aq0Ougw8GzD0isLehw8IXDko8KYP9QGwNQZvjAiI3SEhxGGXhlInQOzZHGDRjYJR8AcZ4yyNNXYRNUZk0sBTcuVMabKINj4xWfgICuC8ZY9A4SeZ2N6Ja5xJQAl6y1ia3o0tWghO8QzJWYTnU2PVjLcxoSdb%2BuWAbQCxt3ZJw3pbTgFzgoTKmccQFcyDxLjuZkkg2TXk129r7f2lBTYVJ2RnZpuEzCVuqBoestSjnl3abYKu98fRBxACHQeecAjRxBAEGtuE0JJxBLE451Fq7JVNkpetW9cl5oevEDIzhJBAA%3D)

By turning `(Pred_0(***))` and `(Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept Clarify = Predicate(Variables...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdzcBmIeCoAE87jCACJIlFoj6YCCE5kksl4nErGFWa4gv4A84y453AAqmFmCi%2B8t%2BcpOQIV92RqIA%2BhoNYcgdTZphVCliFiEageUaTVyOQErAFORBsagxRKAOwWFEETYMO4EYheTCSkx%2BznR6Va/W8w1cU37c0CS3W23ex3oFMc6Hckxukue72%2BmOBzDB4ih8OR6Ox%2BPAxOHO5ULyh74gsEQ/kwuH2sVXYjAcnQynXFEARy8eBR6sZRLZg4N%2BY0mNH47FFKpmbB2buMVQng7XYg/urtdDVDESibcYToPBLwHsIreO3E6no8wc4XVUGSZFlWTXZNNzub9d0nDkzAANnMeDgJXMDYXXFMtzHBQYN/C1DxtY9T1oc8GEvKsgxDMMIyjaErGbZ9ZWVVV6R7a5Zg%2BPBkENJgFCUFpqC7QcuApS8JTojg1loTgAl4PwOC0UhUE4NxrGsO4FA2LZMDg6EeFIAhNEktYAGsQACeCcUSeCpACP14MkABOaF7LMaF9E4SReBYCQNE3eTFOUjheAUEBN0MhTJNIOBYBgRAQA2AgUgRchKDQZ46HiSJWB2VRrIAWgcu5gGQZA7ikHEzF4VFCBIPB0D0fhBBEMR2CkGRBEUFR1Ei0hdC4UgAHdiCYFJOB4KSZLkoylM4AB5BFkvpVAqDuPL4MKyRitK8rJEqu4IA8DL6Ftcw9JWXgIq0NYICQdKUkysgKAge7HpAYApDMPg6DBYhQogGIZpicJmlZcbeGB5hiFZOaYm0OoIv09K3gIOaGFoMHeqwGIvGAOFaFoULuF4LAWEMYBxCxwD6gAN1VGarTqBEdn08IwWk3raDwGIRuhjwsBm8M8B84nSDp4gTyUTlwXJrmjCMtYqAMcd8TwTBBrmlJGHBjrhFEcR2qa%2BQlDUGb%2Bv0cmUDUyx9G50LIDWVA6SyIn8tmdAuVMSxrDMQLxeZLB7cvLoeiyFwGHcTx2j0UIFnKSo9EKTIBCmPwBqT3ohnj0YBtqeoBH6SYo7yXPugRho5izkYElzuZU70DiWirpYa7WTTNm2CRJo4WTSAC3ggrWgqipKsqKrMA7cFq063K4C6DIVtYEEwJgsASYOzMkaEcWcv1JA0SQzEkeC/IsxyPI4LzSB86EzBxaF4L9RJoUSAIAi4FzHOSfvZuC2wwoXpFG6cVboJUWilZ6r0TrZTYJwdam07jIAMEYcqjkcRcBxIpGqRAA6NVkC1A20gjZdVNr1XQX1hqjXBt3XuP8goLSSgiO4K0h4bSKkg8mqD0GYIOkdB6J1dJmHnldKKoCoHxFSi9VAx1RgcKMFwRyXBNw0FoL9f6gNeqQ1BjrLR0NYbwwcDrZGjBUbo0xopbGuN8aEx1qTWWOwLHU0cHTImWDVBMzBDrNm3QZpcx5qDfmDjLrMhFvpcWktMDSzJkYOWoAgF8GVgoVW6tNba1FkbAhbUiGyBIT1RS5CLbyy9lYG2fig6O2dpmTgbsCAeyLMUn2ft4gB3pg7EO5dnAQFcPXAascyjV0TukZO2Ri5p1SEMzOccBml1DgXOuoyG5l3zn0SuUyW4N3mbkMZjd5j9PWXPdYHc2o0Omr1Qe8D2HIOAFwjBJoIBTxwbpOel1F6kGXqvUYG9fKbg5lfG%2BAQcROQCI5MwIKEKJA/g5PuM0gohQASI4B8BQGJSWpI8RxAYE7GaCwIqLAFA0zKjTBROJIQsWqvgHB9U8HNX1lk3WuSzYgHcpQsaxMTnQrOfNcBy1VqqFxfiwlxLSWzF4dI/h8RdLQmEQraKd0xWPTRfKk6IACUpBSIaIljlDTCoIIaPlRCfrxHUUDEG0MdGmphnDBGRjpEozRhjGali8ZiBsaLOxMSgmkHwCiWm9NeqM2QMzLxggfGc25rzVkgTBYhJ1uE9IkSZYxPCHE66CSmAqzVhrLW8l9IZNpRIbJnUTZ5J0EywpxhrY2DKfACpvQia7Hdlbb2lhfYD39vVVpwc869HDpHLZMcI7NwTunCZWQenjKKFkIdOd2nLMLq0BZMyOkrIGNOmu4wBjjp2WuruhztK7o5rQmFnA1r8oJXcTVJL%2BQivuRSkgTzpVAKXivNelBu5/KZXfSFbkzC/q4IkDQ8FgUcsCpwOF4VXmb23h/V%2Bh9oQBEA25eyF9oSnNA3/BF3cqogYHmBwB101jiwyM4SQQA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/clarify.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/clarify/implementation.hpp)
