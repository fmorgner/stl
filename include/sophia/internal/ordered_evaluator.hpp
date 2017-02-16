#ifndef SOPHIA_INTERNAL__ORDERED_EVALUATOR
#define SOPHIA_INTERNAL__ORDERED_EVALUATOR

/**
 * @internal
 * @file ordered_evaluator.hpp
 * @author Felix Morgner
 * @since 0.1
 */

namespace sophia
  {

  namespace internal
    {

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief A meta class to guarantee ordered evaluation of a variable number of expressions.
     *
     * In certain situation it is imperative to guarantee the order of evaluation of a variable number of expressions. This
     * requires the expansion of a parameter pack into a list-expression. This could be done in 11 different ways of which I
     * deem two to be sensible.
     *
     * The first one would be to expand the pack as the arguments to a function call. However, ISO 14882:2014 [expr.call]
     * explicitely states that the order in whiche the arguments to a function call are intialized is indeterminate. Thus the
     * expressions provided to a function call to initialize its parameters are evaluated in unspecified order. As a result,
     * function calls can not be used to guarantee the order of expression evaluation.
     *
     * The second option is to expand the parameter pack into an intializer-clause of a braced-init-list. ISO 14882:2014
     * [decl.init.list] specifies that the elements of the initializer-clause of the intializer-list of a braced-init-list are
     * evaluated in the order they appear. This definition even holds if the elements of the initializer-list are interpreted
     * as the arguments of a contructor call (8.5.4.4, ISO 14882:2014 [decl.init.list]).
     */
    struct ordered_evaluator
      {
      template<typename ...ExpressionTypes>
      constexpr ordered_evaluator(ExpressionTypes const & ...) {};
      };

    }

  }

#endif
