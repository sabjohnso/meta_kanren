/**

   @file metakanren/core.hpp

   @brief This file contains the core relational system.
   
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
#ifndef CORE_HPP_INCLUDED_1063693198211381943
#define CORE_HPP_INCLUDED_1063693198211381943 1

//
// ... Standard header files
//
#include <cstddef>
#include <type_traits>

//
// ...  metakanren header files
//
#include <metakanren/types.hpp>
#include <metakanren/list_processing.hpp>

namespace metakanren
{
  namespace core
  {

  
    using namespace metakanren::list_processing;
    using namespace metakanren::types;

  
    template< typename ... >
    struct mplus;

    template< typename y >
    struct mplus< nil, y >{ using type = y; };
  
    template< template< typename ... > class f, typename y >
    struct mplus< procedure< f >, y >
    {
      template< typename ... >
      struct g
      {
	using type = typename mplus< y, typename f<>::type >::type;
      };
      using type = procedure< g >;
    };

  
  
    template< typename x0, typename x1, typename y >
    struct mplus< cons< x0, x1 >, y >
    {
      using type = cons< x0, typename mplus< x1, y >::type >;
    };

    template< typename stream, typename x, typename y >
    stream&
    operator <<( stream& s, Type< mplus< x, y >> )
    {
      return s << "mplus<" << Type<x>{} << "," << Type< y >{} << ">";
    }

  
  
  
    template< typename ... >
    struct unit;

    template< typename x >
    struct unit< x >{ using type = cons< x, nil >; };

    template< typename stream, typename x >
    stream&
    operator <<( stream& s, Type< unit< x > > )
    {
      return s << "unit<" << Type< x >{} << ">";
    }
  


  


  

  
    template< typename, typename  >
    struct bind;

    template< template< typename ... > class f >
    struct bind< nil, procedure< f > >{ using type = nil; };
    
    template< template< typename ... > class x, template< typename ... > class f >
    struct bind< procedure< x >, procedure< f > >
    {
      template< typename ... >
      struct g
      {
	using type = typename bind< typename x<>::type, procedure< f > >::type;
      };
      using type = procedure< g >;
    };

    template< typename x, typename y, template< typename ... > class f >
    struct bind< cons< x, y >, procedure< f > >
    {
      using type = typename mplus< typename f< x >::type, typename bind< y, procedure< f > >::type >::type;
    };




  

  
  
    template< size_t i > struct var {};

    template< typename stream, size_t i >
    stream&
    operator <<( stream& s, Type< var< i > > ){ return s << "var<" << i << ">"; }

    template< typename >
    struct is_var{ constexpr static bool value = false; };

    template< size_t i >
    struct is_var< var< i > >{ constexpr static bool value = true; };

    template< typename, typename >
    struct equal_var { constexpr static bool value = false; };
      
    template< size_t i >
    struct equal_var< var< i >, var< i > >{ constexpr static bool value = true; };




  

    template< typename ... >
    struct extend_state;

    template< typename x, typename v, typename s >
    struct extend_state< x, v, s >{ using type =  cons< cons< x, v >, s >; };

    template< typename ... > struct walk;

    template< typename u, typename s >
    struct walk< u, s >
    {
    
      template< typename ... >
      struct f;

      template< typename v >
      struct f< v >
      {
	using type = typename std::conditional< equal_var< u, v >::value, v, nil >::type;
      };

      template< typename ... xs >
      struct g
      {
	constexpr static bool value = not_null< typename f< xs ... >::type >::value;
      };
      
      using pr = typename And< typename std::conditional< is_var< u >::value, u, nil >::type,
			       typename assp< procedure< g >, s >::type >::type;
      
      using type = typename std::conditional<
	not_null< pr >::value,
	walk< typename cdr< pr >::type, s >,
	Type< u >
	>::type::type;
    
    }; // end of struct template walk







  
    template< typename ... >
    struct unify;

    template< typename u, typename v, typename s >
    struct unify< u, v, s >
    {

      using ux = typename walk< u, s >::type;
      using vx = typename walk< v, s >::type;

      template< typename ... >
      struct aux;

      template< size_t i >
      struct aux< var< i >, var< i > >
      {
	using type = s;
      };

      template< size_t i, typename vy >
      struct aux< var< i >, vy >
      {
	using type = typename extend_state< var< i >, vy, s >::type;
      };

      template< typename uy, size_t j >
      struct aux< uy, var< j > >
      {
	using type = typename extend_state< var< j >, uy, s >::type;
      };

      template< typename u0, typename u1, typename v0, typename v1 >
      struct aux< cons< u0, u1 >, cons< v0, v1 > >
      {
	using sy = typename unify< u0, v0, s >::type;
	using type = typename And< sy, typename unify< u1, v1, sy >::type >::type;
      };

      template< typename uy >
      struct aux< uy, uy >
      {
	using type = s;
      };

      template< typename uy, typename vy >
      struct aux< uy, vy >
      {
	using type = nil;
      };

      using type = typename aux< ux, vx >::type;
    
    };

  
    template< typename ... >
    struct equate;

    template< typename u, typename v >
    struct equate< u, v >
    {
    
      template< typename ... >
      struct f;
    
      template< typename s >
      struct f< s >
      {
	using sx = typename unify< u, v, typename car< s >::type >::type;
	using type = typename std::conditional<
	  not_null< sx >::value,
	  typename unit<  cons< sx, typename cdr< s >::type > >::type,
	  nil >::type;
      };

      using type = procedure< f >;
      
    };





  
    template< typename ... >
    struct apply;

    template< template< typename ... > class f, typename ... xs >
    struct apply< procedure< f >, xs ... > { using type = typename f< xs ... >::type; };





  
    template< typename ... >
    struct call_fresh;
  
    template< template< typename ... > class f >
    struct call_fresh< procedure< f > >
    {
      template< typename ... >
      struct g;

      template< typename sc>
      struct g< sc >
      {	
	using c = typename cdr< sc >::type;
	using type = typename apply<
	  typename f< var< c::value > >::type,
	  cons< typename car< sc >::type, datum< size_t, 1+c::value > > >::type;
      };

      using type = procedure< g >;
      
    }; // end of struct template call_fresh




  

    template< typename ... >
    struct disj;

    template<
      template< typename ... > class g1,
      template< typename ... > class g2
      >
    struct disj< procedure< g1 >, procedure< g2 > >
    {
      
      template< typename ... >
      struct f;

      template< typename sc >
      struct f< sc >
      {
	using type = typename mplus<
	  typename g1< sc >::type,
	  typename g2< sc >::type >::type;
      };
    
      using type = procedure< f >;
    
    };
    


    template< typename ... >
    struct conj;

    template<
      template< typename ... > class g1,
      template< typename ... > class g2
      >
    struct conj< procedure< g1 >, procedure< g2 > >
    {
      template< typename ... >
      struct f;

      template< typename sc >
      struct f< sc >
      {
	using type = typename bind< typename g1< sc >::type, procedure< g2 > >::type;
      };
    
      using type = procedure< f >;

    
    };


  }// end of namespace core
} // end of namespace meta_kanren

#endif // ! defined CORE_HPP_INCLUDED_1063693198211381943
