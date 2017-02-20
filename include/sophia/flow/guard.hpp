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

  struct guard_violation : std::logic_error
    {
    guard_violation(std::string const & message) : std::logic_error{"terminating due to guard violation: " + message} { }
    };

  namespace internal
    {

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

      void operator||(std::function<void ()> const & otherwise) &&
        {
        m_otherwise = otherwise;
        }

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

  template<typename ConditionType>
  internal::guard guard(ConditionType && condition, std::string const & violationMessage)
    {
    return internal::guard{static_cast<bool>(condition), violationMessage};
    }

  }

#endif
