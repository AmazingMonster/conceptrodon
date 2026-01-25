<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Concepts

- **Prelude**

- **Introduction**

  - [Hello World](../introduction/hello_world.md)
  - [Vocabulary](../introduction/vocabulary.md)
  - [Functional Nature](../introduction/functional_nature.md)

- **Facilities**

  - [Metafunctions](../facilities/metafunctions.md)
  - [Regularities](../facilities/regularities.md)
  - [Utilities](../facilities/utilities.md)

<!-- Typelivore -- Start -->
## Typelivore <a id="typelivore"></a>

<!-- Conceptualizations -- Start -->
### Conceptualizations<a id="typelivore-conceptualization"></a>

<dl>
  <dt>
    <a href="./concepts/typelivore/all_passed.doc.md">AllPassed</a>
    <a id="typelivore-all-passed"></a>
  </dt>
  <dd>Conceptualize a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/all_failed.doc.md">AllFailed</a>
    <a id="typelivore-all-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/any_passed.doc.md">AnyPassed</a>
    <a id="typelivore-any-passed"></a>
  </dt>
  <dd>Conceptualize a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/any_failed.doc.md">AnyFailed</a>
    <a id="typelivore-any-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/passed.doc.md">Passed</a>
    <a id="typelivore-passed"></a>
  </dt>
  <dd>Conceptualize a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/failed.doc.md">Failed</a>
    <a id="typelivore-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable type predicate.</dd>

  <dt>
    <a href="./concepts/typelivore/nice.doc.md">Nice</a>
    <a id="typelivore-nice"></a>
  </dt>
  <dd>Conceptualize the validity check of expressions.</dd>
</dl>
<!-- Conceptualizations -- End -->

<!-- Entity Examinations -- Start -->
### Entity Examinations <a id="typelivore-entity-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/typelivore/different_from.doc.md">DifferentFrom</a>
    <a id="typelivore-different-from"></a>
  </dt>
  <dd><code>true</code> if two elements are different.</dd>

  <dt>
    <a href="./concepts/typelivore/false_probe.doc.md">FalseProbe</a>
    <a id="typelivore-false-probe"></a>
  </dt>
  <dd><code>true</code> if the value result of the argument is false.</dd>

  <dt>
    <a href="./concepts/typelivore/true_probe.doc.md">TrueProbe</a>
    <a id="typelivore-true-probe"></a>
  </dt>
  <dd><code>true</code> if the value result of the argument is true.</dd>
</dl>
<!-- Entity Examinations -- End -->

<!-- Arithmetic Examinations -- Start -->
### Arithmetic Examinations <a id="typelivore-arithmetic-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/typelivore/all_negative_one.doc.md">AllNegativeOne</a>
    <a id="typelivore-all-negative-one"></a>
  </dt>
  <dd><code>true</code> if the value results of the classes equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/all_nonzero.doc.md">AllNonzero</a>
    <a id="typelivore-all-nonzero"></a>
  </dt>
  <dd><code>true</code> if none of the value results of the classes equals <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/all_not_negative_one.doc.md">AllNotNegativeOne</a>
    <a id="typelivore-all-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if none of the value results of the classes equals <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/all_zero.doc.md">AllZero</a>
    <a id="typelivore-all-zero"></a>
  </dt>
  <dd><code>true</code> if the value results of the classes equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/typelivore/any_negative_one.doc.md">AnyNegativeOne</a>
    <a id="typelivore-any-negative-one"></a>
  </dt>
  <dd><code>true</code> if there exists a class whose value result equals <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/any_nonzero.doc.md">AnyNonzero</a>
    <a id="typelivore-any-nonzero"></a>
  </dt>
  <dd><code>true</code> if there exists a class whose value result does not equal <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/any_not_negative_one.doc.md">AnyNotNegativeOne</a>
    <a id="typelivore-any-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if there exists a class whose value result does not equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/any_zero.doc.md">AnyZero</a>
    <a id="typelivore-any-zero"></a>
  </dt>
  <dd><code>true</code> if there exists a class whose value result equals <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/bounded_by_closed_interval.doc.md">BoundedByClosedInterval</a>
    <a id="typelivore-bounded-by-closed-interval"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is bounded by a closed interval.</dd>
  
  <dt>
    <a href="./concepts/typelivore/bounded_by_left_closed_right_open_interval.doc.md">BoundedByLeftClosedRightOpenInterval</a>
    <a id="typelivore-bounded-by-left-closed-right-open-interval"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is bounded by a left closed right open interval.</dd>
  
  <dt>
    <a href="./concepts/typelivore/bounded_by_left_open_right_closed_interval.doc.md">BoundedByLeftOpenRightClosedInterval</a>
    <a id="typelivore-bounded-by-left-open-right-closed-interval"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is bounded by a left open right closed interval.</dd>
  
  <dt>
    <a href="./concepts/typelivore/bounded_by_open_interval.doc.md">BoundedByOpenInterval</a>
    <a id="typelivore-bounded-by-open-interval"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is bounded by an open interval.</dd>
  
  <dt>
    <a href="./concepts/typelivore/equal_to.doc.md">EqualTo</a>
    <a id="typelivore-equal-to"></a>
  </dt>
  <dd><code>true</code> if the value result of a class equals another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/greater_than.doc.md">GreaterThan</a>
    <a id="typelivore-greater-than"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is greater than another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/less_than.doc.md">LessThan</a>
    <a id="typelivore-less-than"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is less than another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/negative_one.doc.md">NegativeOne</a>
    <a id="typelivore-less-than"></a>
  </dt>
  <dd><code>true</code> if the value result of a class equals <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/no_greater_than.doc.md">NoGreaterThan</a>
    <a id="typelivore-no-greater-than"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is less or equal to another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/no_less_than.doc.md">NoLessThan</a>
    <a id="typelivore-no-less-than"></a>
  </dt>
  <dd><code>true</code> if the value result of a class is greater or equal to another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/no_less_than.doc.md">Nonzero</a>
    <a id="typelivore-nonzero"></a>
  </dt>
  <dd><code>true</code> if the value result of a class does not equal <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/not_negative_one.doc.md">NotNegativeOne</a>
    <a id="typelivore-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if the value result of a class does not equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/typelivore/unequal_to.doc.md">UnequalTo</a>
    <a id="typelivore-unequal-to"></a>
  </dt>
  <dd><code>true</code> if the value result of a class does not equal another variable.</dd>
  
  <dt>
    <a href="./concepts/typelivore/zero.doc.md">Zero</a>
    <a id="typelivore-zero"></a>
  </dt>
  <dd><code>true</code> if the value result of a class equals <code>0</code>.</dd>
</dl>
<!-- Arithmetic Examinations -- End -->
<!-- Typelivore -- End -->

<!-- Varybivore -- Start -->
## Varybivore <a id="varybivore"></a>

<!-- Conceptualizations -- Start -->
### Conceptualizations<a id="varybivore-conceptualization"></a>

<dl>
  <dt>
    <a href="./concepts/varybivore/all_passed.doc.md">AllPassed</a>
    <a id="varybivore-all-passed"></a>
  </dt>
  <dd>Conceptualize a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/all_failed.doc.md">AllFailed</a>
    <a id="varybivore-all-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/any_passed.doc.md">AnyPassed</a>
    <a id="varybivore-any-passed"></a>
  </dt>
  <dd>Conceptualize a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/any_failed.doc.md">AnyFailed</a>
    <a id="varybivore-any-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/passed.doc.md">Passed</a>
    <a id="varybivore-passed"></a>
  </dt>
  <dd>Conceptualize a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/failed.doc.md">Failed</a>
    <a id="varybivore-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a callable predicate.</dd>

  <dt>
    <a href="./concepts/varybivore/nice.doc.md">Nice</a>
    <a id="varybivore-nice"></a>
  </dt>
  <dd>Conceptualize the validity check of expressions.</dd>
</dl>
<!-- Conceptualizations -- End -->

<!-- Entity Examinations -- Start -->
### Entity Examinations <a id="varybivore-entity-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/varybivore/different_from.doc.md">DifferentFrom</a>
    <a id="varybivore-different-from"></a>
  </dt>
  <dd><code>true</code> if two variables are different.</dd>
  
  <dt>
    <a href="./concepts/varybivore/same_as.doc.md">SameAs</a>
    <a id="varybivore-same-as"></a>
  </dt>
  <dd><code>true</code> if two variables are the same.</dd>

  <dt>
    <a href="./concepts/varybivore/false_probe.doc.md">FalseProbe</a>
    <a id="varybivore-false-probe"></a>
  </dt>
  <dd><code>true</code> if the argument is false.</dd>

  <dt>
    <a href="./concepts/varybivore/true_probe.doc.md">TrueProbe</a>
    <a id="varybivore-true-probe"></a>
  </dt>
  <dd><code>true</code> if the argument is true.</dd>
</dl>
<!-- Entity Examinations -- End -->

<!-- Arithmetic Examinations -- Start -->
### Arithmetic Examinations <a id="varybivore-arithmetic-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/varybivore/all_negative_one.doc.md">AllNegativeOne</a>
    <a id="varybivore-all-negative-one"></a>
  </dt>
  <dd><code>true</code> if the variables equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/all_nonzero.doc.md">AllNonzero</a>
    <a id="varybivore-all-nonzero"></a>
  </dt>
  <dd><code>true</code> if none of the variables equal <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/all_not_negative_one.doc.md">AllNotNegativeOne</a>
    <a id="varybivore-all-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if none of the variables equals <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/all_zero.doc.md">AllZero</a>
    <a id="varybivore-all-zero"></a>
  </dt>
  <dd><code>true</code> if the variables equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/varybivore/any_negative_one.doc.md">AnyNegativeOne</a>
    <a id="varybivore-any-negative-one"></a>
  </dt>
  <dd><code>true</code> if there exists a variable equal to <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/any_nonzero.doc.md">AnyNonzero</a>
    <a id="varybivore-any-nonzero"></a>
  </dt>
  <dd><code>true</code> if there exists a variable that does not equal <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/any_not_negative_one.doc.md">AnyNotNegativeOne</a>
    <a id="varybivore-any-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if there exists a variable that does not equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/any_zero.doc.md">AnyZero</a>
    <a id="varybivore-any-zero"></a>
  </dt>
  <dd><code>true</code> if there exists a variable equal to <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/bounded_by_closed_interval.doc.md">BoundedByClosedInterval</a>
    <a id="varybivore-bounded-by-closed-interval"></a>
  </dt>
  <dd><code>true</code> if a variable is bounded by a closed interval.</dd>
  
  <dt>
    <a href="./concepts/varybivore/bounded_by_left_closed_right_open_interval.doc.md">BoundedByLeftClosedRightOpenInterval</a>
    <a id="varybivore-bounded-by-left-closed-right-open-interval"></a>
  </dt>
  <dd><code>true</code> if a variable is bounded by a left closed right open interval.</dd>
  
  <dt>
    <a href="./concepts/varybivore/bounded_by_left_open_right_closed_interval.doc.md">BoundedByLeftOpenRightClosedInterval</a>
    <a id="varybivore-bounded-by-left-open-right-closed-interval"></a>
  </dt>
  <dd><code>true</code> if a variable is bounded by a left open right closed interval.</dd>
  
  <dt>
    <a href="./concepts/varybivore/bounded_by_open_interval.doc.md">BoundedByOpenInterval</a>
    <a id="varybivore-bounded-by-open-interval"></a>
  </dt>
  <dd><code>true</code> if a variable is bounded by an open interval.</dd>
  
  <dt>
    <a href="./concepts/varybivore/equal_to.doc.md">EqualTo</a>
    <a id="varybivore-equal-to"></a>
  </dt>
  <dd><code>true</code> if a variable equals another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/greater_than.doc.md">GreaterThan</a>
    <a id="varybivore-greater-than"></a>
  </dt>
  <dd><code>true</code> if a variable is greater than another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/less_than.doc.md">LessThan</a>
    <a id="varybivore-less-than"></a>
  </dt>
  <dd><code>true</code> if a variable is less than another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/negative_one.doc.md">NegativeOne</a>
    <a id="varybivore-negative-one"></a>
  </dt>
  <dd><code>true</code> if a variable equals <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/no_greater_than.doc.md">NoGreaterThan</a>
    <a id="varybivore-no-greater-than"></a>
  </dt>
  <dd><code>true</code> if a variable is less or equal to another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/no_less_than.doc.md">NoLessThan</a>
    <a id="varybivore-no-less-than"></a>
  </dt>
  <dd><code>true</code> if a variable is greater or equal to another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/no_less_than.doc.md">Nonzero</a>
    <a id="varybivore-nonzero"></a>
  </dt>
  <dd><code>true</code> if a variable does not equal <code>0</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/unequal_to.doc.md">UnequalTo</a>
    <a id="varybivore-unequal-to"></a>
  </dt>
  <dd><code>true</code> if a variable does not equal another variable.</dd>
  
  <dt>
    <a href="./concepts/varybivore/not_negative_one.doc.md">NotNegativeOne</a>
    <a id="varybivore-not-negative-one"></a>
  </dt>
  <dd><code>true</code> if a variable does not equal <code>-1</code>.</dd>
  
  <dt>
    <a href="./concepts/varybivore/zero.doc.md">Zero</a>
    <a id="varybivore-zero"></a>
  </dt>
  <dd><code>true</code> if a variable equals <code>0</code>.</dd>
</dl>
<!-- Arithmetic Examinations -- End -->
<!-- Varybivore -- End -->

<!-- Mouldivore -- Start -->
## Mouldivore <a id="mouldivore"></a>

<!-- Conceptualizations -- Start -->
### Conceptualizations <a id="mouldivore-conceptualization"></a>

<dl>
  <dt>
    <a href="./concepts/mouldivore/all_passed.doc.md">AllPassed</a>
    <a id="mouldivore-all-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/all_failed.doc.md">AllFailed</a>
    <a id="mouldivore-all-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/any_passed.doc.md">AnyPassed</a>
    <a id="mouldivore-any-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/any_failed.doc.md">AnyFailed</a>
    <a id="mouldivore-any-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/passed.doc.md">Passed</a>
    <a id="mouldivore-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/failed.doc.md">Failed</a>
    <a id="mouldivore-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/failing.doc.md">Failing</a>
    <a id="mouldivore-failing"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>
  
  <dt>
    <a href="./concepts/mouldivore/passing.doc.md">Passing</a>
    <a id="mouldivore-passing"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>
</dl>
<!-- Conceptualizations -- End -->
<!-- Mouldivore -- End -->

<!-- Pagelivore -- Start -->
## Pagelivore <a id="pagelivore"></a>

<!-- Conceptualizations -- Start -->
### Conceptualizations<a id="pagelivore-conceptualization"></a>

<dl>
  <dt>
    <a href="./concepts/pagelivore/all_passed.doc.md">AllPassed</a>
    <a id="pagelivore-all-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>

  <dt>
    <a href="./concepts/pagelivore/all_failed.doc.md">AllFailed</a>
    <a id="pagelivore-all-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>

  <dt>
    <a href="./concepts/pagelivore/any_passed.doc.md">AnyPassed</a>
    <a id="pagelivore-any-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>

  <dt>
    <a href="./concepts/pagelivore/any_failed.doc.md">AnyFailed</a>
    <a id="pagelivore-any-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>

  <dt>
    <a href="./concepts/pagelivore/passed.doc.md">Passed</a>
    <a id="pagelivore-passed"></a>
  </dt>
  <dd>Conceptualize a class template predicate.</dd>

  <dt>
    <a href="./concepts/pagelivore/failed.doc.md">Failed</a>
    <a id="pagelivore-failed"></a>
  </dt>
  <dd>Conceptualize the negation of a class template predicate.</dd>
</dl>
<!-- Conceptualizations -- End -->
<!-- Pagelivore -- End -->

<!-- Omennivore -- Start -->
## Omennivore <a id="omennivore"></a>

<!-- Entity Examinations -- Start -->
### Entity Examinations <a id="omennivore-entity-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/omennivore/all_peg_nonzero.doc.md">AllPegNonzero</a>
    <a id="omennivore-all-peg-nonzero"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of the types are <code>Peg</code>s and the indicated values do not equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/all_peg_zero.doc.md">AllPegZero</a>
    <a id="omennivore-all-peg-zero"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of the types are <code>Peg</code>s and the indicated values equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/all_pegful.doc.md">AllPegful</a>
    <a id="omennivore-all-pegful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of the types are <code>Peg</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_unpegful.doc.md">AllUnpegful</a>
    <a id="omennivore-all-unpegful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of the types are not <code>Peg</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/any_peg_nonzero.doc.md">AnyPegNonzero</a>
    <a id="omennivore-any-peg-nonzero"></a>
  </dt>
  <dd><code>true</code> if there exists a type whose underlying template is a <code>Peg</code> and the indicated value does not equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_peg_zero.doc.md">AnyPegZero</a>
    <a id="omennivore-any-peg-zero"></a>
  </dt>
  <dd><code>true</code> if there exists a type whose underlying template is a <code>Peg</code> and the indicated value equals <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_pegful.doc.md">AnyPegful</a>
    <a id="omennivore-any-pegful"></a>
  </dt>
  <dd><code>true</code> if there exists a type whose underlying template is a <code>Peg</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_unpegful.doc.md">AnyUnpegful</a>
    <a id="omennivore-any-unpegful"></a>
  </dt>
  <dd><code>true</code> if there exists a type whose underlying template is not a <code>Peg</code>.</dd>
  
  <dt>
    <a href="./concepts/omennivore/peg_nonzero.doc.md">PegNonzero</a>
    <a id="omennivore-peg-nonzero"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a type is a <code>Peg</code> and the indicated value does not equal <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/peg_zero.doc.md">PegZero</a>
    <a id="omennivore-peg-zero"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a type is a <code>Peg</code> and the indicated value equals <code>0</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/pegful.doc.md">Pegful</a>
    <a id="omennivore-pegful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a type is a <code>Peg</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unpegful.doc.md">Unpegful</a>
    <a id="omennivore-unpegful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of the types is not a <code>Peg</code>.</dd>
</dl>
<!-- Entity Examinations -- End -->

<!-- Member Examinations -- Start -->
### Member Examinations <a id="omennivore-member-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/omennivore/all_typical.doc.md">AllTypical</a>
    <a id="omennivore-all-typical"></a>
  </dt>
  <dd><code>true</code> if every class contains a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/all_untypical.doc.md">AllUntypical</a>
    <a id="omennivore-all-untypical"></a>
  </dt>
  <dd><code>true</code> if none of the classes contain a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/all_unvaluable.doc.md">AllUnvaluable</a>
    <a id="omennivore-all-unvaluable"></a>
  </dt>
  <dd><code>true</code> if none of the classes contain a static constexpr member <code>value</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/all_valuable.doc.md">AllValuable</a>
    <a id="omennivore-all-valuable"></a>
  </dt>
  <dd><code>true</code> if every class contains a static constexpr member <code>value</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_typical.doc.md">AnyTypical</a>
    <a id="omennivore-any-typical"></a>
  </dt>
  <dd><code>true</code> if there exists a class containing a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_untypical.doc.md">AnyUntypical</a>
    <a id="omennivore-any-untypical"></a>
  </dt>
  <dd><code>true</code> if there exists a class that does not contain a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_unvaluable.doc.md">AnyUnvaluable</a>
    <a id="omennivore-any-unvaluable"></a>
  </dt>
  <dd><code>true</code> if there exists a class that does not contain a static constexpr member <code>value</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/any_valuable.doc.md">AnyValuable</a>
    <a id="omennivore-any-valuable"></a>
  </dt>
  <dd><code>true</code> if there exists a class containing a static constexpr member <code>value</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/typical.doc.md">Typical</a>
    <a id="omennivore-typical"></a>
  </dt>
  <dd><code>true</code> if a class contains a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/untypical.doc.md">Untypical</a>
    <a id="omennivore-untypical"></a>
  </dt>
  <dd><code>true</code> if a class does not contain a type alias member <code>type</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unvaluable.doc.md">Unvaluable</a>
    <a id="omennivore-unvaluable"></a>
  </dt>
  <dd><code>true</code> if a class does not contain a static constexpr member <code>value</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/valuable.doc.md">Valuable</a>
    <a id="omennivore-valuable"></a>
  </dt>
  <dd><code>true</code> if a class contains a static constexpr member <code>value</code>.</dd>
</dl>
<!-- Member Examinations -- End -->

<!-- Packed-Vessel Examinations -- Start -->
### Packed-Vessel Examinations <a id="omennivore-packed-vessel-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/omennivore/moldful.doc.md">Moldful</a>
    <a id="omennivore-moldful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Mold</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/pageful.doc.md">Pageful</a>
    <a id="omennivore-pageful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Page</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/roadful.doc.md">Roadful</a>
    <a id="omennivore-roadful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Road</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/railful.doc.md">Railful</a>
    <a id="omennivore-railful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Rail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/flowful.doc.md">Flowful</a>
    <a id="omennivore-flowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Flow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/sailful.doc.md">Sailful</a>
    <a id="omennivore-sailful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Sail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/snowful.doc.md">Snowful</a>
    <a id="omennivore-snowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Snow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/hailful.doc.md">Hailful</a>
    <a id="omennivore-hailful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Hail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/coolful.doc.md">Coolful</a>
    <a id="omennivore-coolful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Cool</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/calmful.doc.md">Calmful</a>
    <a id="omennivore-calmful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Calm</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/gritful.doc.md">Gritful</a>
    <a id="omennivore-gritful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Grit</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/willful.doc.md">Willful</a>
    <a id="omennivore-willful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Will</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/glowful.doc.md">Glowful</a>
    <a id="omennivore-glowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Glow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/dawnful.doc.md">Dawnful</a>
    <a id="omennivore-dawnful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is a <code>Dawn</code>.</dd>
</dl>

#### Un*

<dl>
  <dt>
    <a href="./concepts/omennivore/unmoldful.doc.md">Unmoldful</a>
    <a id="omennivore-unmoldful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Mold</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unpageful.doc.md">Pageful</a>
    <a id="omennivore-unpageful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Page</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unroadful.doc.md">Roadful</a>
    <a id="omennivore-unroadful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Road</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unrailful.doc.md">Railful</a>
    <a id="omennivore-unrailful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Rail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unflowful.doc.md">Flowful</a>
    <a id="omennivore-unflowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Flow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unsailful.doc.md">Sailful</a>
    <a id="omennivore-unsailful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Sail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unsnowful.doc.md">Snowful</a>
    <a id="omennivore-unsnowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Snow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unhailful.doc.md">Hailful</a>
    <a id="omennivore-unhailful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Hail</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/uncoolful.doc.md">Coolful</a>
    <a id="omennivore-uncoolful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Cool</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/uncalmful.doc.md">Calmful</a>
    <a id="omennivore-uncalmful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Calm</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/ungritful.doc.md">Gritful</a>
    <a id="omennivore-ungritful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Grit</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unwillful.doc.md">Willful</a>
    <a id="omennivore-unwillful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Will</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/unglowful.doc.md">Glowful</a>
    <a id="omennivore-unglowful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Glow</code>.</dd>

  <dt>
    <a href="./concepts/omennivore/undawnful.doc.md">Dawnful</a>
    <a id="omennivore-undawnful"></a>
  </dt>
  <dd><code>true</code> if the underlying template of a packed vessel is not a <code>Dawn</code>.</dd>
</dl>

#### All*

<dl>
  <dt>
    <a href="./concepts/omennivore/all_moldful.doc.md">AllMoldful</a>
    <a id="omennivore-all-moldful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Mold</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_pageful.doc.md">AllPageful</a>
    <a id="omennivore-all-pageful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Page</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_roadful.doc.md">AllRoadful</a>
    <a id="omennivore-all-roadful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Road</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_railful.doc.md">AllRailful</a>
    <a id="omennivore-all-railful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Rail</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_flowful.doc.md">AllFlowful</a>
    <a id="omennivore-all-flowful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Flow</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_sailful.doc.md">AllSailful</a>
    <a id="omennivore-all-sailful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Sail</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_snowful.doc.md">AllSnowful</a>
    <a id="omennivore-all-snowful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Snow</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_hailful.doc.md">AllHailful</a>
    <a id="omennivore-all-hailful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Hail</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_coolful.doc.md">AllCoolful</a>
    <a id="omennivore-all-coolful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Cool</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_calmful.doc.md">AllCalmful</a>
    <a id="omennivore-all-calmful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Calm</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_gritful.doc.md">AllGritful</a>
    <a id="omennivore-all-gritful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Grit</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_willful.doc.md">AllWillful</a>
    <a id="omennivore-all-willful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Will</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_glowful.doc.md">AllGlowful</a>
    <a id="omennivore-all-glowful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Glow</code>s.</dd>

  <dt>
    <a href="./concepts/omennivore/all_dawnful.doc.md">AllDawnful</a>
    <a id="omennivore-all-dawnful"></a>
  </dt>
  <dd><code>true</code> if the underlying templates of a list of packed vessels are <code>Dawn</code>s.</dd>
</dl>

<!-- Functivore -- Start -->
## Functivore <a id="functivore"></a>

<!-- Function Comparisons -- Start -->
### Function Comparisons <a id="functivore-function-comparisons"></a>

<dl>
  <dt>
    <a href="./concepts/functivore/same_type_signature_as.doc.md">SameTypeSignatureAs</a>
    <a id="functivore-same-type-signature-as"></a>
  </dt>
  <dd><code>true</code> if the type signatures of two function-like types are the same.</dd>

  <dt>
    <a href="./concepts/functivore/same_variadic_type_signature_as.doc.md">SameVariadicTypeSignatureAs</a>
    <a id="functivore-same-variadic-type-signature-as"></a>
  </dt>
  <dd><code>true</code> if the variadic type signatures of two function-like types are the same.</dd>
</dl>

#### All*

<dl>
  <dt>
    <a href="./concepts/functivore/all_same_type_signature.doc.md">AllSameTypeSignature</a>
    <a id="functivore-all-same-type-signature"></a>
  </dt>
  <dd><code>true</code> if the type signatures of all function-like types are the same.</dd>

  <dt>
    <a href="./concepts/functivore/all_same_variadic_type_signature.doc.md">AllSameVariadicTypeSignature</a>
    <a id="functivore-all-same-variadic-type-signature"></a>
  </dt>
  <dd><code>true</code> if the variadic type signatures of all function-like types are the same.</dd>
</dl>
<!-- Function Comparisons -- End -->

<!-- Function Examinations -- Start -->
### Function Examinations <a id="functivore-function-examinations"></a>

<dl>
  <dt>
    <a href="./concepts/functivore/const_qualified.doc.md">ConstQualified</a>
    <a id="functivore-const-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is <code>const</code> qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/function_pointer_probe.doc.md">FunctionPointerProbe</a>
    <a id="functivore-function-pointer-probe"></a>
  </dt>
  <dd><code>true</code> if the function-like type is a function pointer.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/invoke_result_in.doc.md">InvokeResultIn</a>
    <a id="functivore-invoke-result-in"></a>
  </dt>
  <dd><code>true</code> if the function-like type invoked by the given arguments returns the given type(the corresponding object type of a member function pointer is treated as the first argument of the pointer).</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/invoke_return_as.doc.md">InvokeReturnAs</a>
    <a id="functivore-invoke-return-as"></a>
  </dt>
  <dd><code>true</code> if the function-like type invoked by the given arguments returns the given type.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/lvalue_reference_qualified.doc.md">LvalueReferenceQualified</a>
    <a id="functivore-lvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is lvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/member_function_pointer.doc.md">MemberFunctionPointer</a>
    <a id="functivore-member-function-pointer"></a>
  </dt>
  <dd><code>true</code> if the function-like type is a member function pointer.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/noexcept_specified.doc.md">NoexceptSpecified</a>
    <a id="functivore-noexcept-specified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is <code>noexcept</code> specified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/nonoverloaded_function_object_probe.doc.md">NonoverloadedFunctionObjectProbe</a>
    <a id="functivore-nonoverloaded-function-object-probe"></a>
  </dt>
  <dd><code>true</code> if the function-like type is a nonoverloaded function object.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/result_in.doc.md">ResultIn</a>
    <a id="functivore-result-in"></a>
  </dt>
  <dd><code>true</code> if the function-like type returns the given type.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/rvalue_reference_qualified.doc.md">RvalueReferenceQualified</a>
    <a id="functivore-rvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is rvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/variadic.doc.md">Variadic</a>
    <a id="functivore-variadic"></a>
  </dt>
  <dd><code>true</code> if the parameter list of the function-like type is variadic.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/volatile_qualified.doc.md">VolatileQualified</a>
    <a id="functivore-volatile-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is <code>volatile</code> qualified.</dd>
</dl>

#### Not*

<dl>
  <dt>
    <a href="./concepts/functivore/not_const_qualified.doc.md">NotConstQualified</a>
    <a id="functivore-not-const-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not <code>const</code> qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_function_pointer.doc.md">NotFunctionPointer</a>
    <a id="functivore-not-function-pointer"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not a function pointer.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_lvalue_reference_qualified.doc.md">NotLvalueReferenceQualified</a>
    <a id="functivore-not-lvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not lvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_member_function_pointer.doc.md">NotMemberFunctionPointer</a>
    <a id="functivore-not-member-function-pointer"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not a member function pointer.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_noexcept_specified.doc.md">NotNoexceptSpecified</a>
    <a id="functivore-not-noexcept-specified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not <code>noexcept</code> specified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_nonoverloaded_function_object.doc.md">NotNonoverloadedFunctionObject</a>
    <a id="functivore-not-nonoverloaded-function-object"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not a nonoverloaded function object.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_rvalue_reference_qualified.doc.md">NotRvalueReferenceQualified</a>
    <a id="functivore-not-rvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not rvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not-variadic.doc.md">NotVariadic</a>
    <a id="functivore-not-variadic"></a>
  </dt>
  <dd><code>true</code> if the parameter list of the function-like type is not variadic.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/not_volatile_qualified.doc.md">NotVolatileQualified</a>
    <a id="functivore-not-volatile-qualified"></a>
  </dt>
  <dd><code>true</code> if the function-like type is not <code>volatile</code> qualified.</dd>
</dl>

#### All*

<dl>
  <dt>
    <a href="./concepts/functivore/all_const_qualified.doc.md">AllConstQualified</a>
    <a id="functivore-all-const-qualified"></a>
  </dt>
  <dd><code>true</code> if all function-like types are <code>const</code> qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_function_pointer.doc.md">AllFunctionPointer</a>
    <a id="functivore-all-function-pointer"></a>
  </dt>
  <dd><code>true</code> if all function-like types are function pointers.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_lvalue_reference_qualified.doc.md">AllLvalueReferenceQualified</a>
    <a id="functivore-all-lvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if all function-like types are lvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_member_function_pointer.doc.md">AllMemberFunctionPointer</a>
    <a id="functivore-all-member-function-pointer"></a>
  </dt>
  <dd><code>true</code> if all function-like types are member function pointers.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_noexcept_specified.doc.md">AllNoexceptSpecified</a>
    <a id="functivore-all-noexcept-specified"></a>
  </dt>
  <dd><code>true</code> if all function-like types are <code>noexcept</code> specified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_nonoverloaded_function_object.doc.md">AllNonoverloadedFunctionObject</a>
    <a id="functivore-all-nonoverloaded-function-object"></a>
  </dt>
  <dd><code>true</code> if all function-like types are nonoverloaded function objects.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_rvalue_reference_qualified.doc.md">AllRvalueReferenceQualified</a>
    <a id="functivore-all-rvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if all function-like types are rvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_variadic.doc.md">AllVariadic</a>
    <a id="functivore-all-variadic"></a>
  </dt>
  <dd><code>true</code> if the parameter lists of all function-like types are variadic.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_volatile_qualified.doc.md">AllVolatileQualified</a>
    <a id="functivore-all-volatile-qualified"></a>
  </dt>
  <dd><code>true</code> if all function-like types are <code>volatile</code> qualified.</dd>
</dl>

#### AllNot*

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_const_qualified.doc.md">AllNotConstQualified</a>
    <a id="functivore-all-not-const-qualified"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are <code>const</code> qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_function_pointer.doc.md">AllNotFunctionPointer</a>
    <a id="functivore-all-not-function-pointer"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are function pointers.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_lvalue_reference_qualified.doc.md">AllNotLvalueReferenceQualified</a>
    <a id="functivore-all-not-lvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are lvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_member_function_pointer.doc.md">AllNotMemberFunctionPointer</a>
    <a id="functivore-all-not-member-function-pointer"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are member function pointers.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_noexcept_specified.doc.md">AllNotNoexceptSpecified</a>
    <a id="functivore-all-not-noexcept-specified"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are <code>noexcept</code> specified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_nonoverloaded_function_object.doc.md">AllNotNonoverloadedFunctionObject</a>
    <a id="functivore-all-not-nonoverloaded-function-object"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are nonoverloaded function objects.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_rvalue_reference_qualified.doc.md">AllNotRvalueReferenceQualified</a>
    <a id="functivore-all-not-rvalue-reference-qualified"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are rvalue reference qualified.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_variadic.doc.md">AllNotVariadic</a>
    <a id="functivore-all-not-variadic"></a>
  </dt>
  <dd><code>true</code> if the parameter lists of all function-like types are not variadic.</dd>
</dl>

<dl>
  <dt>
    <a href="./concepts/functivore/all_not_volatile_qualified.doc.md">AllNotVolatileQualified</a>
    <a id="functivore-all-not-volatile-qualified"></a>
  </dt>
  <dd><code>true</code> if none of the function-like types are <code>volatile</code> qualified.</dd>
</dl>
<!-- Function Examinations -- End -->
