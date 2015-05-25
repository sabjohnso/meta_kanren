/**
   @file metakanren/core.hpp

   @brief A small set of list processing functionality on which the
   relational system will be built
   
   @author Samuel B. Johnson <sabjohnso@yahoo.com>

   @copyright  2015: Samuel B. Johnson.

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/ 
#ifndef LIST_PROCESSING_HPP_INCLUDED_962605848274371951
#define LIST_PROCESSING_HPP_INCLUDED_962605848274371951 1

//
// ... Standard header files
//
#include <type_traits>

//
// ... metakanren header files
//
#include <metakanren/types.hpp>


namespace metakanren
{
  namespace list_processing
  {

    using namespace metakanren::types;


    template< template< typename ... > class ... >
    struct compose;

  
    struct nil{};
  
    template< typename stream >
    stream&
    operator <<( stream& s, Type< nil > ){ return s << "nil";}
  

  
    template< typename ... >
    struct null { constexpr static bool value = false; };
  
    template<>
    struct null< nil >{ constexpr static bool value = true; };




  
    template< typename ... xs >
    struct not_null { constexpr static bool value = ! null< xs ... >::value; };




  
    template< typename first, typename second >
    struct cons
    {
      using car = first;
      using cdr = second;
    };

    template< typename stream, typename first, typename second >
    stream&
    operator <<( stream& s, Type< cons< first, second > >)
    {
      return s << "cons<" << Type< first >() << ',' << Type< second >() << '>';
    }




    template< typename ... >
    struct is_cons{ constexpr static bool value = false; };

    template< typename x, typename y >
    struct is_cons< cons< x, y > >{ constexpr static bool value = true; };
  



    
    template< typename ... >
    struct car{ using type = nil; };

    template< typename x, typename y >
    struct car< cons< x, y > >{ using type = x; };




    
    template< typename ... >
    struct caar{ using type = nil; };

    template< typename x >
    struct caar< x >{ using type = typename car< typename car< x >::type >::type; };



    
    template< typename ... >
    struct caaar{ using type = nil; };

    template< typename x >
    struct caaar< x >{ using type = typename car< typename caar< x >::type >::type; };
      
  


    
    template< typename ... >
    struct cdr{ using type = nil; };


    template< typename x, typename y >
    struct cdr< cons< x, y > >{ using type = y; };




    template< typename ... xs >
    struct cadr{ using type = typename car< typename cdr< xs ... >::type >::type; };




    
    template< typename ... xs >
    struct cdar{ using type = typename cdr< typename car< xs ... >::type >::type; };



    
    template< typename ... xs >
    struct caadr{ using type = typename car< typename cadr< xs ... >::type >::type; };


    

    template< typename ... xs >
    struct cdadr{ using type = typename cdr< typename cadr< xs ... >::type >::type; };

    


      




  
    template< typename ... >
    struct list;

    template<>
    struct list<>{ using type = nil; };

    template< typename x, typename ... xs >
    struct list< x, xs ... >{ using type = cons< x, typename list< xs ... >::type >; };



  





    template< typename ... >
    struct is_list{ constexpr static bool value = false; };

    template<>
    struct is_list< nil >{ constexpr static bool value = true; };

    template< typename x, typename y >
    struct is_list< cons< x, y > >{ constexpr static bool value = is_list< y >::value; };
    
    
  
  
  


  
    template< template< typename ... > class >
    struct procedure{};




  
    template< typename ... >
    struct And;

    template< typename x, typename ... xs >
    struct And< nil,  x, xs ... >{ using type = nil; };
  
    template< typename x, typename y, typename ... ys >
    struct And< x, y, ys ... > { using type = typename And< y, ys ... >::type; };

    template< typename x >
    struct And< x > { using type = x; };

    template<>
    struct And< nil > { using type = nil; };




  
  
    template< typename ... >
    struct assp;

    template< template< typename ... > class p >
    struct assp< procedure< p >, nil >{ using type = nil; };

    template< template< typename ... > class p, typename x1, typename x2, typename y >
    struct assp< procedure< p >, cons< cons< x1, x2 >, y > >
    {
      using type = typename std::conditional< p< x1 >::value, cons< x1, x2 >, typename assp< procedure< p >, y >::type >::type;
    };


    template< typename ... >
    struct is_assoc{ constexpr static bool value = true; };

    template<>
    struct is_assoc< nil >{ constexpr static bool value = true; };

    template< typename x, typename y >
    struct is_assoc< cons< x, y > >{ constexpr static bool value  = is_cons< x >::value && is_assoc< y >::value; };
  
  



  
  }; // end of namespace list_processing

}; // end of namespace metakanren

#endif // ! defined LIST_PROCESSING_HPP_INCLUDED_962605848274371951
