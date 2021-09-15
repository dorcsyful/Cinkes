#pragma once

/** @defgroup CVector3 
 *  A vector consisting of 3 elements
 */

/** @defgroup Constructors
*  @ingroup CVector3
*  All constructor functions
*/

/** @defgroup Operators
*  @ingroup CVector3
*  All overridden operator functions
*/

/** @defgroup Other
*  @ingroup CVector3
*  All other functions in the class
*/


/** @defgroup CMat3x3
 *  A 3x3 matrix, mostly used to represent rotation in a matrix form
 */

 /** @defgroup Constructors
 *  @ingroup CMat3x3
 *  All constructor functions
 */

 /** @defgroup Operators
 *  @ingroup CMat3x3
 *  All overridden operator functions
 */

 /** @defgroup Other
 *  @ingroup CMat3x3
 *  All other functions in the class
 */


 /** @defgroup CQuaternion
  *  Used to represent rotation in 3D space
  */

  /** @defgroup Constructors
  *  @ingroup CQuaternion
  *  All constructor functions
  */

  /** @defgroup Operators
  *  @ingroup CQuaternion
  *  All overridden operator functions
  */

  /** @defgroup Other
  *  @ingroup CQuaternion
  *  All other functions in the class
  */


  /** @defgroup CTransform
   *  Represents both position and rotation, does not contain scale
   */

   /** @defgroup Constructors
   *  @ingroup CTransform
   *  All constructor functions
   */

   /** @defgroup Operators
   *  @ingroup CTransform
   *  All overridden operator functions
   */

   /** @defgroup Other
   *  @ingroup CTransform
   *  All other functions in the class
   */
#define USE_MATH_DEFINES

#define USE_DOUBLE false
#if USE_DOUBLE
#define CScalar double
#else
#define CScalar float
#endif
