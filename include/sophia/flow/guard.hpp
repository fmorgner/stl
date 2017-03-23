#ifndef SOPHIA_FLOW__GUARD
#define SOPHIA_FLOW__GUARD

#include <functional>
#include <stdexcept>
#include <string>

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wterminate"
#endif

namespace sophia::flow
  {

  /**
   * @author Felix Morgner
   * @since 0.2
   *
   * @brief An exception type for #sophia::flow::guard violations
   *
   * This exception will be thrown of the condition of a #sophia::flow::guard statement is violated. It will be thrown in a
   * manner that is uncatchable to ensure program termination. For the rationale see #sophia::flow::guard.
   */
  struct guard_violation : std::logic_error
    {
    guard_violation(std::string const & message) : std::logic_error{"terminating due to guard violation: " + message} { }
    };

  namespace internal
    {

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.2
     *
     * @brief A wrapper around a guard condition
     *
     * This wrapper class checks the supplied guard condition during destruction, throwing an instance of
     * #sophia::flow::guard_violation if the condition is violated. This ensures program termination on condition violation
     * because destructors are implicitly @p noexcept since C++11. Termination is by design, since we consider the program to be
     * internally inconsistent if a guard condition is violated.
     */
    struct guard
      {
      explicit guard(bool const condition, std::string const & message) :
        m_message{message},
        m_condition{condition}
        {

        }

      ~guard()
        {
        if(m_condition)
          {
          return;
          }

        if(m_otherwise)
          {
          m_otherwise();
          }

        throw guard_violation{m_message};
        }

      /**
       * @author Felix Morgner
       * @since 0.2
       *
       * @brief Attach a function to the guard condition
       *
       * This operator makes it possible to attach a function to a #sophia::flow::guard condition. The lambda will be called
       * iff. the guard's condition is violated. The function will be called with no argument and is expected to retun nothing.
       */
      void operator||(std::function<void ()> const & otherwise) &&
        {
        m_otherwise = otherwise;
        }

      /**
       * @author Felix Morgner
       * @since 0.2
       *
       * @brief Attach a function to the guard condition
       *
       * This operator makes it possible to attach a function to a #sophia::flow::guard condition. The lambda will be called
       * iff. the guard's condition is violated. The function will be called with the guards message string as its only argument
       * and is expected to return nothing.
       */
      void operator||(std::function<void (std::string const &)> const & otherwise) &&
        {
        m_otherwise = [=](){ otherwise(m_message); };
        }

      private:
        std::function<void ()> m_otherwise{};

        std::string const & m_message;
        bool const m_condition;
      };

    }

  /**
   * @author Felix Morgner
   * @since 0.2
   *
   * @brief Guard the rest of the containing compound statement with the provided condition
   *
   * Guards make it possible to 'protect' or 'guard' the rest of its containing compound statement based on a precondition. If
   * the precondition is violated, the program will be terminated.
   */
  template<typename ConditionType>
  internal::guard guard(ConditionType && condition, std::string const & violationMessage = "")
    {
    return internal::guard{static_cast<bool>(condition), violationMessage};
    }

  }

#endif
