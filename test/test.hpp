#ifndef PQS_TEST_HPP_INCLUDED_12_11_2019
#define PQS_TEST_HPP_INCLUDED_12_11_2019
/*
 Copyright (c) 2003-2014 Andy Little.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see http://www.gnu.org/licenses./
 */

#include <iostream>

// count errors
extern int errors;

// return true if no errors, else false
inline
bool check_function( const char* filename ,  long line,const char* pred, bool pred1)
{
   if(! pred1){
      std::cout << filename << ":" << line  << "( " << pred << " ) failed\n";
      errors ++;
      return false;
   } else {
      #ifdef QUAN_CHECK_VERBOSE 
      std::cout << filename << ":" << line  << "( " << pred << " ) succeeded\n";
      #endif
      return true;
   }
}

#define QUAN_CHECK(x) check_function( __FILE__ , __LINE__ , #x, x);

// best show we've been on success
inline
int epilogue(const char* file)
{
    if (errors){
        std::cout << "TEST FAILED     :  " << file << " FAIL: found " << errors << " errors\n";
    }
    else{
        std::cout << "TEST SUCCESSFUL : " << file << " PASS (no errors)\n";
    }
    return errors;
}

#define EPILOGUE return epilogue(__FILE__);

#endif



