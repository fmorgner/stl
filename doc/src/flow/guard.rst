Guards
******

C++ provides two main facilities to check and validate programmer defined
conditions. One being classic C-style ``assert(...)`` and the other being the
C++-only ``static_assert(...)``. Their main difference is that ``assert(...)``
statements are evaluated at runtime, and can even be disabled, while
``static_assert(...)``, as the name implies, is evaluated at compile-time.

.. note::
  In this section we are only concerned with runtime condition assertions, thus
  we ignore ``static_assert(...)`` for now.

One major drawback of the classic old C-style ``assert(...)`` macro is that it
is impossible to handle assertion failures to any degree, preventing clean
shutdown in case of a violation. This is where the :cpp:func:`guard(...)
<sophia::flow::guard>` function comes in handy. Similarly to guard expressions
in `Swift <https://swift.org/>`_, :cpp:func:`guard(...) <sophia::flow::guard>`
makes it easy to write runtime condition checks that cannot be disabled or
easily bypassed. It also gives you the ability to attach a lambda or a function-
pointer to the guard so that you have the chance to do any special clean-up or
logging. As soon as the attached code-block returns, your program is terminated
by throwing an uncatchable exception.

Reference
---------

.. doxygenfunction:: sophia::flow::guard
